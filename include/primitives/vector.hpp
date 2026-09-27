#pragma once

#include <cstdint>
namespace Primitives {

template <typename precision> struct Vector2D {
  precision x, y;
};

typedef Vector2D<int32_t> Vector2Di;
typedef Vector2D<int64_t> Vector2Dl;
typedef Vector2D<uint32_t> Vector2Dui;
typedef Vector2D<uint64_t> Vector2Dul;
} // namespace Primitives
