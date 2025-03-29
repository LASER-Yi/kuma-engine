#pragma once

#include "Core/CoreMinimal.h"
#include <cstdint>

namespace Swarm
{
using ComponentType = std::uint8_t;
using ComponentIndexType = std::int32_t;

constexpr ComponentType MaxComponents = 32;
constexpr ComponentType InvalidIndex = -1;
} // namespace Swarm
