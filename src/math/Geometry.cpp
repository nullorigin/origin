#include "Geometry.hpp"
namespace origin
{

    auto cross(Vec3 const& v0, Vec3 const& v1) -> Vec3
    {
        return { v0.Y * v1.Z - v0.Z * v1.Y,
                 v0.Z * v1.X - v0.X * v1.Z,
                 v0.X * v1.Y - v0.Y * v1.X };
    }
    auto cross(Vec2 const& v0, Vec2 const& v1) -> Vec2
    {
        return { v0.Y * v1.X - v0.X * v1.Y,
                 v0.X * v1.Y - v0.Y * v1.X };
    }
} // namespace origin