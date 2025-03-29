#pragma once

#include "CoreMinimal.h"
#include <cstdint>

namespace Swarm
{
using ComponentType = std::uint8_t;

using EntityIndex = std::int32_t;
using ComponentIndex = std::int32_t;

constexpr std::int32_t Invalid = -1;
} // namespace Swarm
