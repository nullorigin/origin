#pragma once
#include "Geometry.hpp"
namespace Origin {

Vec3 Cross(Vec3 const &_lhs, Vec3 const &_rhs) {
  return {_lhs.y * _rhs.z - _lhs.z * _rhs.y, _lhs.z * _rhs.x - _lhs.x * _rhs.z,
          _lhs.x * _rhs.y - _lhs.y * _rhs.x};
}
Vec2 Cross(Vec2 const &_lhs, Vec2 const &_rhs) {
  return Vec2(_lhs.y * _rhs.x - _lhs.x * _rhs.y,
              _lhs.x * _rhs.y - _lhs.y * _rhs.x);
}
} // namespace Origin