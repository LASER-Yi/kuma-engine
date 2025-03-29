#pragma once

template <typename T>
class TSingleton
{
public:
    static T* Get()
    {
        static T Instance;
        return &Instance;
    }

    TSingleton() = default;
    ~TSingleton() = default;
    TSingleton(const TSingleton&) = delete;
    TSingleton& operator=(const TSingleton&) = delete;
    TSingleton(T&&) = delete;
    TSingleton& operator=(T&&) = delete;
};
