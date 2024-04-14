#include "Geometry.hpp"
namespace origin {

auto Cross(Vec3 const &_lhs, Vec3 const &_rhs) -> Vec3 {
  return Vec3(_lhs.y * _rhs.z - _lhs.z * _rhs.y,
              _lhs.z * _rhs.x - _lhs.x * _rhs.z,
              _lhs.x * _rhs.y - _lhs.y * _rhs.x);
}
auto Cross(Vec2 const &_lhs, Vec2 const &_rhs) -> Vec2 {
  return Vec2(_lhs.y * _rhs.x - _lhs.x * _rhs.y,
              _lhs.x * _rhs.y - _lhs.y * _rhs.x);
}
} // namespace origin