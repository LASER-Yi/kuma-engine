#pragma once

#include <typeinfo>

struct FGenericTypeHasher
{
    template <typename T>
    constexpr static auto value()
    {
        return typeid(T).hash_code();
    };
};
