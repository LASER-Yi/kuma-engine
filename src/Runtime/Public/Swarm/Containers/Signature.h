#pragma once

#include <queue>

template <typename T>
class TSignature
{
public:
    TSignature() : Next(), Fragment() {}

    T Allocate()
    {
        T Value;
        if (Fragment.empty() == false)
        {
            Value = Fragment.front();
            Fragment.pop();
        }
        else
        {
            Value = Next;
            Next = Next + 1;
        }

        return Value;
    }

    void Release(T InValue) { Fragment.push(InValue); }

private:
    T Next;
    std::queue<T> Fragment;
};
