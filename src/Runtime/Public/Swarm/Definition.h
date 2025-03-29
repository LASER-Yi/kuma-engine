#pragma once

#include "CoreMinimal.h"
#include <cstddef>
#include <cstdint>
#include <limits>

namespace Swarm
{
using ComponentType = std::int64_t;

using EntityIndex = std::size_t;
using ComponentIndex = std::size_t;

static_assert(
    sizeof(ComponentType) >= sizeof(std::size_t),
    "ComponentType must be at least as large as std::size_t"
);

constexpr std::int64_t InvalidType = -1;
constexpr std::size_t InvalidIndex = std::numeric_limits<std::size_t>::max();
} // namespace Swarm
