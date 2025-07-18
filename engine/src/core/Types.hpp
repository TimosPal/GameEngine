#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

namespace Engine {

using ID = uint32_t;
constexpr ID INVALID_ID = -1;

struct Component; // Used for ID groupping only.

} // Engine

#endif // !TYPES_HPP