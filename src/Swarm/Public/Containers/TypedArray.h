#pragma once

#include "TypeHasher.h"

#include <algorithm>
#include <cassert>
#include <span>
#include <unordered_map>
#include <utility>

/**
 * @brief Group elements based on type, and allocate them into continuous memory
 * Similar to std::vector but support different types
 */
template <
    typename Base, typename S = std::size_t, typename Hash = std::size_t,
    typename Allocator = THandleAllocator<S>>
class TTypedArray
{

    /**
     * @brief The element definition of the TTypedArray
     */
    class TTypedElement
    {
        static_assert(
            sizeof(Base) != 0, "The size of the Base element cannot be zero"
        );

    public:
        TTypedElement()
            : ElementType(0), ElementSize(0), Container(nullptr),
              ContainerSize(0), ContainerCapacity(0)
        {
        }

        TTypedElement(Hash InElementType, std::size_t InElementSize)
            : ElementType(InElementType), ElementSize(InElementSize),
              Container(nullptr), ContainerSize(0), ContainerCapacity(0)
        {
        }

        ~TTypedElement()
        {
            if (Container)
            {
                for (std::size_t Index = 0; Index < ContainerSize; ++Index)
                {
                    Base* Element = Get(Index);
                    Element->~Base();
                }

                std::free(Container);
                Container = nullptr;
            }

            ElementType = 0;
            ElementSize = 0;

            ContainerSize = 0;
            ContainerCapacity = 0;
        }

        template <typename T, typename... Args>
        T* Add(Args&&... Arguments)
        {
            static_assert(
                std::is_base_of<Base, T>::value, "T must be derived from Base"
            );

            assert(sizeof(T) == ElementSize);
            assert(FGenericTypeHasher::value<T>() == ElementType);

            ContainerSize = ContainerSize + 1;

            if (ContainerSize > ContainerCapacity)
            {
                Resize();
            }

            // Allocate space from the container pointer and initialize T
            const std::size_t NewIndex = ContainerSize - 1;

            T* Element = static_cast<T*>(Get(NewIndex));
            new (Element) T(std::forward<Args>(Arguments)...);

            return Element;
        }

        void Remove(std::size_t InIndex)
        {
            assert(0 <= InIndex && InIndex < ContainerSize);

            const size_t LastIndex = ContainerSize - 1;

            Base* Element = Get(InIndex);
            Base* Last = Get(LastIndex);

            Element->~Base();

            if (Element == Last)
            {
                // If the last element is being removed, just reduce the size
                ContainerSize = ContainerSize - 1;
                return;
            }

            // Move the last element to the index of the removed element
            std::memcpy(
                static_cast<void*>(Element), static_cast<void*>(Last),
                ElementSize
            );
        }

        Base* Get(std::size_t InIndex) const
        {
            assert(0 <= InIndex && InIndex < ContainerSize);

            return reinterpret_cast<Base*>(Container + (InIndex * ElementSize));
        }

        template <typename T>
        std::span<T> GetView() const
        {
            static_assert(
                std::is_base_of<Base, T>::value, "T must be derived from Base"
            );

            assert(sizeof(T) == ElementSize);
            assert(FGenericTypeHasher::value<T>() == ElementType);

            return {reinterpret_cast<T*>(Container), ContainerSize};
        }

        template <typename Func>
        std::size_t Find(Func Predicator) const
        {
            for (std::size_t Index = 0; Index < ContainerSize; ++Index)
            {
                Base* Element =
                    reinterpret_cast<Base*>(Container + (Index * ElementSize));

                if (Predicator(Element))
                {
                    return Index;
                }
            }

            return ContainerSize;
        }

    public:
        std::size_t GetSize() const { return ContainerSize; }
        std::size_t GetCapacity() const { return ContainerCapacity; };

        bool IsValid() const { return ElementSize != 0; }

    private:
        Hash ElementType;
        std::size_t ElementSize;

        std::byte* Container;
        std::size_t ContainerSize;
        std::size_t ContainerCapacity;

        void Resize()
        {
            assert(ElementSize != 0);

            ContainerCapacity =
                std::max(static_cast<std::size_t>(1), ContainerCapacity * 2);

            const std::size_t NewSize = ContainerCapacity * ElementSize;

            // Reallocate the container
            void* NewContainer = std::realloc(Container, NewSize);
            assert(NewContainer);

            Container = static_cast<std::byte*>(NewContainer);
        }
    };

public:
    template <typename T, typename... Args>
    S Add(Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        auto& Container = GetOrCreateContainer<T>();

        const S NewSign = Signature.Allocate();

        T* NewElement =
            Container.template Add<T>(std::forward<Args>(Arguments)...);
        NewElement->Signature = NewSign;

        return NewSign;
    }

    template <typename T>
    void Remove(S InSignature)
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        auto& Container = GetOrCreateContainer<T>();

        const std::size_t Index =
            Container.Find([InSignature](const Base* Element)
                           { return Element->Signature == InSignature; });

        if (Index != Container.GetSize())
        {
            Container.Remove(Index);
        }

        Signature.Release(InSignature);
    }

    void Remove(const Hash& ElementType, S InSignature)
    {
        if (auto Container = GetContainer(ElementType))
        {
            const std::size_t Index =
                Container->Find([InSignature](const Base* Element)
                                { return Element->Signature == InSignature; });

            if (Index != Container->GetSize())
            {
                Container->Remove(Index);
            }
        }

        Signature.Release(InSignature);
    }

    template <typename T>
    T* Find(S InSignature) const
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        if (const auto Container = GetContainer<T>())
        {
            const std::size_t Index =
                Container->Find([InSignature](const Base* Element)
                                { return Element->Signature == InSignature; });

            if (Index != Container->GetSize())
            {
                return static_cast<T*>(Container->Get(Index));
            }
        }

        return nullptr;
    }

    void Clear()
    {
        ContainerMap.clear();
        Signature.Reset();
    }

    template <typename T>
    std::span<T> GetView() const
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        if (const auto Container = GetContainer<T>())
        {
            return Container->template GetView<T>();
        }

        return {};
    }

    template <typename T>
    std::size_t Count() const
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        if (auto Container = GetContainer<T>())
        {
            return Container->GetSize();
        }

        return 0;
    }

private:
    template <typename T>
    TTypedElement& GetOrCreateContainer()
    {
        const Hash ContainerType = FGenericTypeHasher::value<T>();

        TTypedElement& Container = ContainerMap[ContainerType];

        if (Container.IsValid() == false)
        {
            // Re-initialize the container
            Container = TTypedElement(ContainerType, sizeof(T));
        }

        return Container;
    }

    TTypedElement* GetContainer(const Hash& ContainerType)
    {
        if (ContainerMap.contains(ContainerType))
        {
            return &ContainerMap.at(ContainerType);
        }

        return nullptr;
    }

    const TTypedElement* GetContainer(const Hash& ContainerType) const
    {
        if (ContainerMap.contains(ContainerType))
        {
            return &ContainerMap.at(ContainerType);
        }

        return nullptr;
    }

    template <typename T>
    TTypedElement* GetContainer()
    {
        const Hash ContainerType = FGenericTypeHasher::value<T>();

        return GetContainer(ContainerType);
    }

    template <typename T>
    const TTypedElement* GetContainer() const
    {
        const Hash ContainerType = FGenericTypeHasher::value<T>();

        return GetContainer(ContainerType);
    }

    Allocator Signature;
    std::unordered_map<Hash, TTypedElement> ContainerMap;
};
