#include "Geometry.hpp"
namespace origin
{

    auto Cross(Vec3f const& _lhs, Vec3f const& rhs) -> Vec3f
    {
        return { _lhs.y * rhs.z - _lhs.z * rhs.y,
                 _lhs.z * rhs.x - _lhs.x * rhs.z,
                 _lhs.x * rhs.y - _lhs.y * rhs.x };
    }
    auto Cross(Vec2f const& _lhs, Vec2f const& rhs) -> Vec2f
    {
        return { _lhs.y * rhs.x - _lhs.x * rhs.y,
                 _lhs.x * rhs.y - _lhs.y * rhs.x };
    }
} // namespace origin