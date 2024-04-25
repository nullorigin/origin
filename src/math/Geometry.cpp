#include "Geometry.hpp"
namespace origin
{

    auto Cross(Vec3f const& _lhs, Vec3f const& _rhs) -> Vec3f
    {
        return Vec3f(_lhs.y * _rhs.z - _lhs.z * _rhs.y,
                     _lhs.z * _rhs.x - _lhs.x * _rhs.z,
                     _lhs.x * _rhs.y - _lhs.y * _rhs.x);
    }
    auto Cross(Vec2f const& _lhs, Vec2f const& _rhs) -> Vec2f
    {
        return Vec2f(_lhs.y * _rhs.x - _lhs.x * _rhs.y,
                     _lhs.x * _rhs.y - _lhs.y * _rhs.x);
    }
} // namespace origin