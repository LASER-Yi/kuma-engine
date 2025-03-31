#pragma once

#include "Swarm/Containers/Signature.h"
#include "Swarm/Definition.h"
#include "Swarm/Utilities/Hasher.h"
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * @brief Group elements based on type, and allocate them into continuous memory
 * Similar to std::vector but support different types
 */
template <
    typename Base, typename S = Swarm::SignatureType,
    typename Allocator = TSignature<S>>
class TTypedArray
{
public:
    template <typename T, typename... Args>
    S Add(Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        auto Container = GetOrCreateContainer<T>();

        T NewElement(std::forward<Args>(Arguments)...);

        NewElement.Signature = Signature.Allocate();

        Container->push_back(std::move(NewElement));
    }

    template <typename T>
    void Remove(S InSignature)
    {
        auto Container = GetOrCreateContainer<T>();

        std::remove_if(
            Container->begin(), Container->end(),
            [InSignature](const T& Element)
            { return Element.GetSignature() == InSignature; }
        );

        Signature.Release(InSignature);
    }

    template <typename T>
    T* Find(S InSignature)
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        auto Container = GetOrCreateContainer<T>();

        auto Result = std::find_if(
            Container->begin(), Container->end(),
            [InSignature](const T& Element)
            { return Element.GetSignature() == InSignature; }
        );

        if (Result != Container->end())
        {
            return &(*Result);
        }

        return nullptr;
    }

    template <typename T>
    std::size_t Count() const
    {
        static_assert(
            std::is_base_of<Base, T>::value, "T must be derived from Base"
        );

        if (auto Container = GetContainer<T>())
        {
            return Container->size();
        }

        return 0;
    }

private:
    template <typename T>
    std::shared_ptr<std::vector<T>> GetOrCreateContainer()
    {
        const std::size_t ContainerType = typeid(T).hash_code();

        std::shared_ptr<std::vector<T>> Container =
            std::reinterpret_pointer_cast<std::vector<T>>(
                Containers[ContainerType]
            );

        if (!Container)
        {
            Container = std::make_shared<std::vector<T>>();
        }

        return Container;
    }

    std::shared_ptr<std::vector<Base>> GetContainer() const;

    template <typename T>
    const std::shared_ptr<const std::vector<T>> GetContainer() const
    {
        const std::size_t ContainerType = typeid(T).hash_code();

        std::shared_ptr<const std::vector<T>> Container =
            std::reinterpret_pointer_cast<const std::vector<T>>(
                Containers.at(ContainerType)
            );

        return Container;
    }

    Allocator Signature;
    std::unordered_map<std::size_t, std::shared_ptr<std::vector<Base>>>
        Containers;
};
