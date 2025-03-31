#pragma once

#include <cstddef>
#include <cstdint>

namespace Swarm
{
using ClassHashType = std::size_t;

using SignatureType = std::int64_t;
constexpr std::int64_t InvalidSignature = -1;
} // namespace Swarm
