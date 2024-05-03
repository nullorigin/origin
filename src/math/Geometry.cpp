#include "Geometry.hpp"
namespace Origin
{

    auto Cross(Vec3 const& _lhs, Vec3 const& rhs) -> Vec3
    {
        return { _lhs.Y * rhs.Z - _lhs.Z * rhs.Y,
                 _lhs.Z * rhs.X - _lhs.X * rhs.Z,
                 _lhs.X * rhs.Y - _lhs.Y * rhs.X };
    }
    auto Cross(Vec2 const& _lhs, Vec2 const& rhs) -> Vec2
    {
        return { _lhs.Y * rhs.X - _lhs.X * rhs.Y,
                 _lhs.X * rhs.Y - _lhs.Y * rhs.X };
    }
} // namespace Origin