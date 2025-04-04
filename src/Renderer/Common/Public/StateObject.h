#pragma once

#include <memory>
struct FStateObject
{
    virtual ~FStateObject(){};
};

using FStateObjectRef = std::shared_ptr<FStateObject>;
