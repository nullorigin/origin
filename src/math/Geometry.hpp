#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#pragma once
#include "Basic.hpp"

#include <string>

namespace origin
{
    using AxisP = enum class Axis : i8 {
        O = 0,
        X = 1,
        Y = 2,
        XY = 3,
        Z = 4,
        XZ = 5,
        YZ = 6,
        XYZ = 7,
        W = 8,
        XW = 9,
        YW = 10,
        XYW = 11,
        ZW = 12,
        XZW = 13,
        YZW = 14,
        XYZW = 15
    };
    using AxisN = enum class AxisN : i8 {
        O = 0,
        X = -1,
        Y = -2,
        XY = -3,
        Z = -4,
        XZ = -5,
        YZ = -6,
        XYZ = -7,
        W = -8,
        XW = -9,
        YW = -10,
        XYW = -11,
        ZW = -12,
        XZW = -13,
        YZW = -14,
        XYZW = -15
    };
    using Face = enum class Face : i8 {
        None = 0,
        Right = 1,
        Up = 2,
        Front = 3,
        Left = -1,
        Back = -2,
        Down = -3
    };
    class Vec2
    {
    public:
        f64 X{ 0.0F }, Y{ 0.0F };
        Vec2(f64 x, f64 y) :
            X(x), Y(y)
        {
        }
        Vec2() = default;
        Vec2(Vec2 const& in) = default;
        Vec2(Vec2&& in) = default;
        Vec2(f64* in) :
            X(in[0]), Y(in[1]) {}
        ~Vec2() = default;

        Vec2& operator=(Vec2&& in) noexcept
        {
            X = in.X;
            Y = in.Y;
            return *this;
        }
        auto operator=(Vec2 const& in) -> Vec2& = default;
        operator f64*() { return new f64[2]{ X, Y }; }
        auto operator+(Vec2 const& v) const -> Vec2 { return { X + v.X, Y + v.Y }; }
        auto operator-(Vec2 const& v) const -> Vec2 { return { X - v.X, Y - v.Y }; }
        auto operator*(Vec2 const& v) const -> Vec2 { return { X * v.X, Y * v.Y }; }
        auto operator/(Vec2 const& v) const -> Vec2 { return { X / v.X, Y / v.Y }; }
        auto operator+(f64 in) const -> Vec2 { return { X + in, Y + in }; }
        auto operator-(f64 in) const -> Vec2 { return { X - in, Y - in }; }
        auto operator*(f64 in) const -> Vec2 { return { X * in, Y * in }; }
        auto operator/(f64 in) const -> Vec2 { return { X / in, Y / in }; }
        auto operator+=(Vec2 const& in) -> Vec2& { return *this = *this + in; }
        auto operator-=(Vec2 const& in) -> Vec2& { return *this = *this - in; }
        auto operator*=(Vec2 const& in) -> Vec2& { return *this = *this * in; }
        auto operator/=(Vec2 const& in) -> Vec2& { return *this = *this / in; }
        auto operator+=(f64 in) -> Vec2& { return *this = *this + in; }
        auto operator-=(f64 in) -> Vec2& { return *this = *this - in; }
        auto operator*=(f64 in) -> Vec2& { return *this = *this * in; }
        auto operator/=(f64 in) -> Vec2& { return *this = *this / in; }
        auto operator-() const -> Vec2 { return { -X, -Y }; }
        bool operator==(const Vec2& v) const { return X == v.X && Y == v.Y; }
        bool operator!=(const Vec2& v) const { return X != v.X || Y != v.Y; }
        bool operator<(const Vec2& v) const
        {
            return X < v.X || (X == v.X && Y < v.Y);
        }
        bool operator>(const Vec2& v) const
        {
            return X > v.X || (X == v.X && Y > v.Y);
        }
        bool operator<=(const Vec2& v) const
        {
            return X < v.X || (X == v.X && Y <= v.Y);
        }
        bool operator>=(const Vec2& v) const
        {
            return X > v.X || (X == v.X && Y >= v.Y);
        }
        auto abs() const -> Vec2
        {
            return { origin::abs(X), origin::abs(Y) };
        }
        auto angle(const Vec2& v) const -> f64
        {
            return origin::acos(this->dot(v) / (this->length() * v.length()));
        }
        auto ceil() const -> Vec2 { return { origin::ceil(X), origin::ceil(Y) }; }
        auto clamp(f64 min, f64 max) const -> Vec2
        {
            return { origin::fmin(origin::fmax(X, min), max), origin::fmin(origin::fmax(Y, min), max) };
        }
        auto clamp(const Vec2& min, const Vec2& max) const -> Vec2
        {
            return { origin::fmin(origin::fmax(X, min.X), max.X), origin::fmin(origin::fmax(Y, min.Y), max.Y) };
        }
        auto cross(const Vec2& v) -> Vec2
        {
            return Vec2(X * v.Y - Y * v.X, X * v.X + Y * v.Y);
        }
        auto distance(const Vec2& in) const -> f64 { return (*this - in).length(); }
        auto distanceSquared(const Vec2& v) const -> f64
        {
            return (*this - v).lengthSquared();
        }
        auto dot(const Vec2& v) const -> f64 { return X * v.X + Y * v.Y; }
        auto floor() const -> Vec2 { return { origin::floor(X), origin::floor(Y) }; }
        auto length() const -> f64 { return origin::abs(origin::sqrt(X * X + Y * Y)); }
        auto lengthSquared() const -> f64 { return origin::abs(X * X + Y * Y); }
        auto lerp(const Vec2& in, f64 t) const -> Vec2
        {
            return (*this * (1 - t) + in * t);
        }
        auto lerp(const Vec2& v1, const Vec2& v2, f64 t) const -> Vec2
        {
            return (*this * (1 - t) + v1 * t + v2 * (t - 1));
        }
        auto max() const -> f64 { return origin::fmax(X, Y); }
        auto max(const Vec2& v) const -> Vec2
        {
            return { origin::fmax(X, v.X), origin::fmax(Y, v.Y) };
        }
        auto min() const -> f64 { return origin::fmin(X, Y); }
        auto min(const Vec2& v) const -> Vec2
        {
            return { origin::fmin(X, v.X), origin::fmin(Y, v.Y) };
        }
        auto normalize() const -> Vec2 { return *this / length(); }
        auto reflect(const Vec2& normal) const -> Vec2
        {
            return normal * this->dot(normal) * (*this - 2);
        }
        auto round() const -> Vec2 { return { origin::round(X), origin::round(Y) }; }
        auto rotate(f64 angle) const -> Vec2
        {
            return { X * origin::cos(angle) - Y * origin::sin(angle), X * origin::sin(angle) + Y * origin::cos(angle) };
        }
        auto trunc() const -> Vec2 { return { origin::trunc(X), origin::trunc(Y) }; }
    };
    class Vec3
    {
    public:
        f64 X{ 0 }, Y{ 0 }, Z{ 0 };
        Vec3(f64 x, f64 y, f64 z) :
            X(x), Y(y), Z(z)
        {
        }
        Vec3() = default;
        Vec3(Vec3 const&) = default;
        Vec3(Vec3&&) = default;
        Vec3(f64* in) :
            X(in[0]), Y(in[1]), Z(in[2]) {}
        ~Vec3() = default;
        auto operator=(Vec3 const&) -> Vec3& = default;
        auto operator=(Vec3&& v) noexcept -> Vec3&
        {
            X = v.X;
            Y = v.Y;
            Z = v.Z;
            return *this;
        }
        operator f64*() { return new f64[3]{ X, Y, Z }; }
        auto operator*(Vec3 const& v) const -> Vec3 { return { X * v.X, Y * v.Y, Z * v.Z }; }
        auto operator/(Vec3 const& v) const -> Vec3 { return { X / v.X, Y / v.Y, Z / v.Z }; }
        auto operator+(Vec3 const& v) const -> Vec3 { return { X + v.X, Y + v.Y, Z + v.Z }; }
        auto operator-(Vec3 const& v) const -> Vec3 { return { X - v.X, Y - v.Y, Z - v.Z }; }
        auto operator*(f64 in) const -> Vec3 { return { X * in, Y * in, Z * in }; }
        auto operator/(f64 in) const -> Vec3 { return { X / in, Y / in, Z / in }; }
        auto operator+(f64 in) const -> Vec3 { return { X + in, Y + in, Z + in }; }
        auto operator-(f64 in) const -> Vec3 { return { X - in, Y - in, Z - in }; }
        auto operator+=(Vec3 const& in) -> Vec3& { return *this = *this + in; }
        auto operator-=(Vec3 const& in) -> Vec3& { return *this = *this - in; }
        auto operator*=(Vec3 const& in) -> Vec3& { return *this = *this * in; }
        auto operator/=(Vec3 const& in) -> Vec3& { return *this = *this / in; }
        auto operator+=(f64 in) -> Vec3& { return *this = *this + in; }
        auto operator-=(f64 in) -> Vec3& { return *this = *this - in; }
        auto operator*=(f64 in) -> Vec3& { return *this = *this * in; }
        auto operator/=(f64 in) -> Vec3& { return *this = *this / in; }
        auto operator-() const -> Vec3 { return { -X, -Y, -Z }; }
        bool operator==(const Vec3& v) const
        {
            return X == v.X && Y == v.Y && Z == v.Z;
        }
        bool operator!=(const Vec3& v) const
        {
            return X != v.X || Y != v.Y || Z != v.Z;
        }
        bool operator<(const Vec3& v) const
        {
            return X < v.X || (X == v.X && Y < v.Y) || (X == v.X && Y == v.Y && Z < v.Z);
        }
        bool operator>(const Vec3& v) const
        {
            return X > v.X || (X == v.X && Y > v.Y) || (X == v.X && Y == v.Y && Z > v.Z);
        }
        bool operator<=(const Vec3& v) const
        {
            return X < v.X || (X == v.X && Y <= v.Y) ||
                   (X == v.X && Y == v.Y && Z <= v.Z);
        }
        bool operator>=(const Vec3& v) const
        {
            return X > v.X || (X == v.X && Y >= v.Y) ||
                   (X == v.X && Y == v.Y && Z >= v.Z);
        }
        auto abs() const -> Vec3 { return { origin::abs(X), origin::abs(Y), origin::abs(Z) }; }
        auto angle(const Vec3& in) const -> f64
        {
            return origin::acos(this->dot(in) / (this->length() * in.length()));
        }
        auto ceil() const -> Vec3 { return { origin::ceil(X), origin::ceil(Y), origin::ceil(Z) }; }
        auto clamp(f64 min, f64 max) const -> Vec3
        {
            return { origin::fmin(origin::fmax(X, min), max), origin::fmin(origin::fmax(Y, min), max), origin::fmin(origin::fmax(Z, min), max) };
        }
        auto clamp(const Vec3& min, const Vec3& max) const -> Vec3
        {
            return { origin::fmin(origin::fmax(X, min.X), max.X), origin::fmin(origin::fmax(Y, min.Y), max.Y), origin::fmin(origin::fmax(Z, min.Z), max.Z) };
        }
        auto cross(const Vec3& v) const -> Vec3
        {
            return { Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X };
        }
        auto distance(const Vec3& in) const -> f64 { return (*this - in).length(); }
        auto distanceSquared(const Vec3& in) const -> f64
        {
            return (*this - in).lengthSquared();
        }
        auto dot(const Vec3& v) const -> f64 { return X * v.X + Y * v.Y + Z * v.Z; }
        auto floor() const -> Vec3 { return Vec3(origin::floor(X), origin::floor(Y), origin::floor(Z)); }
        auto length() const -> f64 { return origin::abs(origin::sqrt(X * X + Y * Y + Z * Z)); }
        auto lengthSquared() const -> f64 { return origin::abs(X * X + Y * Y + Z * Z); }
        auto lerp(const Vec3& in, f64 t) const -> Vec3
        {
            return (*this * (1 - t) + in * t);
        }
        auto lerp(const Vec3& v1, const Vec3& v2, f64 t) const -> Vec3
        {
            return (*this * (1 - t) + v1 * t + v2 * (t - 1));
        }
        auto max() const -> f64 { return origin::fmax(X, origin::fmax(Y, Z)); }
        auto max(const Vec3& v) const -> Vec3
        {
            return { origin::fmax(X, v.X), origin::fmax(Y, v.Y), origin::fmax(Z, v.Z) };
        }
        auto min() const -> f64 { return origin::fmin(X, origin::fmin(Y, Z)); }
        auto min(const Vec3& v) const -> Vec3
        {
            return { origin::fmin(X, v.X), origin::fmin(Y, v.Y), origin::fmin(Z, v.Z) };
        }
        auto normalize() const -> Vec3 { return *this / this->length(); }
        auto reflect(const Vec3& normal) const -> Vec3
        {
            return *this - normal * 2 * this->dot(normal);
        }
        auto round() const -> Vec3 { return { origin::round(X), origin::round(Y), origin::round(Z) }; }
        auto rotate(f64 angle) const -> Vec3
        {
            return { X * origin::cos(angle) - Y * origin::sin(angle), X * origin::sin(angle) + Y * origin::cos(angle), Z };
        }
        auto trunc() const -> Vec3 { return { origin::trunc(X), origin::trunc(Y), origin::trunc(Z) }; }
    };
    class Vec4
    {
    public:
        f64 X{ 0 }, Y{ 0 }, Z{ 0 }, W{ 0 };
        Vec4(f64 x, f64 y, f64 z, f64 w) :
            X(x), Y(y), Z(z), W(w)
        {
        }
        Vec4() = default;
        Vec4(Vec4&& in) noexcept :
            X(in.X), Y(in.Y), Z(in.Z), W(in.W) {}
        Vec4(Vec4 const& in) = default;
        Vec4(f64* in) :
            X(in[0]), Y(in[1]), Z(in[2]), W(in[3]) {}
        ~Vec4() = default;

        auto operator=(Vec4&& in) noexcept -> Vec4&
        {
            X = in.X;
            Y = in.Y;
            Z = in.Z;
            W = in.W;
            return *this;
        }
        auto operator=(Vec4 const& v) -> Vec4& = default;
        operator f64*() { return new f64[4]{ X, Y, Z, W }; }
        auto operator+(Vec4 const& v) const -> Vec4 { return { X + v.X, Y + v.Y, Z + v.Z, W + v.W }; }
        auto operator-(Vec4 const& v) const -> Vec4 { return { X - v.X, Y - v.Y, Z - v.Z, W - v.W }; }
        auto operator*(Vec4 const& v) const -> Vec4 { return { X * v.X, Y * v.Y, Z * v.Z, W * v.W }; }
        auto operator/(Vec4 const& v) const -> Vec4 { return { X / v.X, Y / v.Y, Z / v.Z, W / v.W }; }
        auto operator+(f64 in) const -> Vec4 { return { X + in, Y + in, Z + in, W + in }; }
        auto operator-(f64 in) const -> Vec4 { return { X - in, Y - in, Z - in, W - in }; }
        auto operator*(f64 in) const -> Vec4 { return { X * in, Y * in, Z * in, W * in }; }
        auto operator/(f64 in) const -> Vec4 { return { X / in, Y / in, Z / in, W / in }; }
        auto operator+=(Vec4 const& in) -> Vec4& { return *this = *this + in; }
        auto operator-=(Vec4 const& in) -> Vec4& { return *this = *this - in; }
        auto operator*=(Vec4 const& in) -> Vec4& { return *this = *this * in; }
        auto operator/=(Vec4 const& in) -> Vec4& { return *this = *this / in; }
        auto operator+=(f64 in) -> Vec4& { return *this = *this + in; }
        auto operator-=(f64 in) -> Vec4& { return *this = *this - in; }
        auto operator*=(f64 in) -> Vec4& { return *this = *this * in; }
        auto operator/=(f64 in) -> Vec4& { return *this = *this / in; }
        auto operator-() const -> Vec4 { return { -X, -Y, -Z, -W }; }
        bool operator==(const Vec4& v) const
        {
            return X == v.X && Y == v.Y && Z == v.Z && W == v.W;
        }
        bool operator!=(const Vec4& v) const
        {
            return X != v.X || Y != v.Y || Z != v.Z || W != v.W;
        }
        bool operator<(const Vec4& v) const
        {
            return X < v.X || (X == v.X && Y < v.Y) ||
                   (X == v.X && Y == v.Y && Z < v.Z) ||
                   (X == v.X && Y == v.Y && Z == v.Z && W < v.W);
        }
        bool operator>(const Vec4& v) const
        {
            return X > v.X || (X == v.X && Y >= v.Y) ||
                   (X == v.X && Y == v.Y && Z >= v.Z) ||
                   (X == v.X && Y == v.Y && Z == v.Z && W >= v.W);
        }
        bool operator<=(const Vec4& v) const
        {
            return X < v.X || (X == v.X && Y <= v.Y) ||
                   (X == v.X && Y == v.Y && Z <= v.Z) ||
                   (X == v.X && Y == v.Y && Z == v.Z && W <= v.W);
        }
        bool operator>=(const Vec4& v) const
        {
            return X > v.X || (X == v.X && Y >= v.Y) ||
                   (X == v.X && Y == v.Y && Z >= v.Z) ||
                   (X == v.X && Y == v.Y && Z == v.Z && W >= v.W);
        }
        auto abs() const -> Vec4 { return { origin::abs(X), origin::abs(Y), origin::abs(Z), origin::abs(W) }; }
        auto angle(const Vec4& in) const -> f64
        {
            return origin::acos(this->dot(in) / (this->length() * in.length()));
        }
        auto ceil() const -> Vec4 { return { origin::ceil(X), origin::ceil(Y), origin::ceil(Z), origin::ceil(W) }; }
        auto clamp(f64 min, f64 max) const -> Vec4
        {
            return Vec4(origin::fmin(origin::fmax(X, min), max), origin::fmin(origin::fmax(Y, min), max), origin::fmin(origin::fmax(Z, min), max), origin::fmin(origin::fmax(W, min), max));
        }
        auto clamp(const Vec4& min, const Vec4& max) const -> Vec4
        {
            return Vec4(origin::fmin(origin::fmax(X, min.X), max.X), origin::fmin(origin::fmax(Y, min.Y), max.Y), origin::fmin(origin::fmax(Z, min.Z), max.Z), origin::fmin(origin::fmax(W, min.W), max.W));
        }
        auto cross(const Vec4& v) const -> Vec4
        {
            return { Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X, 0.0F };
        }
        auto distance(const Vec4& in) const -> f64 { return (*this - in).length(); }
        auto distanceSquared(const Vec4& in) const -> f64
        {
            return (*this - in).lengthSquared();
        }
        auto dot(const Vec4& v) const -> f64
        {
            return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
        }
        auto floor() const -> Vec4
        {
            return Vec4(origin::floor(X), origin::floor(Y), origin::floor(Z), origin::floor(W));
        }
        f64 length() const { return origin::abs(origin::sqrt(X * X + Y * Y + Z * Z + W * W)); }
        f64 lengthSquared() const { return origin::abs(X * X + Y * Y + Z * Z + W * W); }
        Vec4 lerp(const Vec4& in, f64 t) const
        {
            return (*this * (1 - t) + in * t);
        }
        Vec4 lerp(const Vec4& v1, const Vec4& v2, f64 t) const
        {
            return (*this * (1 - t) + v1 * t + v2 * (t - 1));
        }
        f64 max() const { return origin::fmax(X, origin::fmax(Y, origin::fmax(Z, W))); }
        Vec4 max(const Vec4& v) const
        {
            return Vec4(origin::fmax(X, v.X), origin::fmax(Y, v.Y), origin::fmax(Z, v.Z), origin::fmax(W, v.W));
        }
        f64 min() const { return origin::fmin(X, origin::fmin(Y, origin::fmin(Z, W))); }
        Vec4 min(const Vec4& v) const
        {
            return Vec4(origin::fmin(X, v.X), origin::fmin(Y, v.Y), origin::fmin(Z, v.Z), origin::fmin(W, v.W));
        }
        Vec4 normalize() const { return *this / this->length(); }
        Vec4 reflect(const Vec4& normal) const
        {
            return normal * this->dot(normal) * (*this - 2);
        }
        Vec4 round() const
        {
            return { origin::round(X), origin::round(Y), origin::round(Z), origin::round(W) };
        }
        Vec4 rotate(f64 angle) const
        {
            return { X * origin::cos(angle) - Y * origin::sin(angle), X * origin::sin(angle) + Y * origin::cos(angle), Z, W };
        }
        Vec4 trunc() const
        {
            return { origin::trunc(X), origin::trunc(Y), origin::trunc(Z), origin::trunc(W) };
        }
    };
    class Rect
    {
    public:
        Vec2 Min;
        Vec2 Max;
        Rect(Vec2 v1, Vec2 v2) :
            Min(v1), Max(v2)
        {
        }
        Rect(Vec4 v)
        {
            Min = Vec2(v.X, v.Y);
            Max = Vec2(v.Z, v.W);
        }
        Rect(f64 x, f64 y, f64 w, f64 h)
        {
            Min = Vec2(x, y);
            Max = Vec2(x + w, y + h);
        }
        Rect()
        {
            Min = Vec2(0.0F, 0.0F);
            Max = Vec2(0.0F, 0.0F);
        }
        Rect operator+(Rect& r) const { return Rect(Min + r.Min, Max + r.Max); }
        Rect operator-(Rect& r) const { return Rect(Min - r.Min, Max - r.Max); }
        Rect operator*(Rect& r) const { return Rect(Min * r.Min, Max * r.Max); }
        Rect operator/(Rect& r) const { return Rect(Min / r.Min, Max / r.Max); }
        auto operator=(Rect const& r) -> Rect& = default;
        auto operator=(Rect&& r) noexcept -> Rect&
        {
            this->Max = r.Max;
            this->Min = r.Min;
            return *this;
        }
        auto operator+=(Rect& r) -> Rect&
        {
            Min += r.Min;
            Max += r.Max;
            return *this;
        }
        auto operator-=(Rect& r) -> Rect&
        {
            Min -= r.Min;
            Max -= r.Max;
            return *this;
        }
        auto operator*=(Rect& r) -> Rect&
        {
            Min *= r.Min;
            Max *= r.Max;
            return *this;
        }
        auto operator/=(Rect& r) -> Rect&
        {
            Min /= r.Min;
            Max /= r.Max;
            return *this;
        }
        bool operator==(Rect& r) const { return Min == r.Min && Max == r.Max; }
        bool operator!=(Rect& r) const { return Min != r.Min || Max != r.Max; }
        bool operator<(Rect& r) const
        {
            return Min < r.Min || (Min == r.Min && Max < r.Max);
        }
        bool operator>(Rect& r) const
        {
            return Min > r.Min || (Min == r.Min && Max > r.Max);
        }
        bool operator<=(Rect& r) const
        {
            return Min < r.Min || (Min == r.Min && Max <= r.Max);
        }
        bool operator>=(Rect& r) const
        {
            return Min > r.Min || (Min == r.Min && Max >= r.Max);
        }
        auto abs() const -> Rect { return Rect(Min.abs(), Max.abs()); }
        auto area() const -> f64 { return origin::abs((Max.X - Min.X) * (Max.Y - Min.Y)); }
        auto bottomLeft() const -> Vec2 { return Vec2(Min.X, Max.Y); }
        auto bottomRight() const -> Vec2 { return Max; }
        auto ceil() const -> Rect { return Rect(Min.ceil(), Max.ceil()); }
        auto center() const -> Vec2 { return (Min + Max) * 0.5F; }
        auto clamp(f64 f1, f64 f2) const -> Rect
        {
            return Rect(Min.clamp(f1, f2), Max.clamp(f1, f2));
        }
        auto clamp(const Rect& r1, const Rect& r2) const -> Rect
        {
            return Rect(Min.clamp(r1.Min, r2.Min), Max.clamp(r1.Max, r2.Max));
        }
        bool contains(const Vec2& v) const
        {
            return v.X >= Min.X && v.X <= Max.X && v.Y >= Min.Y &&
                   v.Y <= Max.Y;
        }
        bool contains(const Rect& r) const
        {
            return r.Min.X >= Min.X && r.Min.Y >= Min.Y && r.Max.X <= Max.X &&
                   r.Max.Y <= Max.Y;
        }
        bool contains(const Vec2& v1, const Vec2& v2) const
        {
            return v1.X >= Min.X - v2.X && v1.X <= Max.X + v2.X &&
                   v1.Y >= Min.Y - v2.Y && v1.Y <= Max.Y + v2.Y;
        }
        bool contains(const Rect& r, const Vec2& v) const
        {
            return r.Min.X >= Min.X - v.X && r.Min.Y >= Min.Y - v.Y &&
                   r.Max.X <= Max.X + v.X && r.Max.Y <= Max.Y + v.Y;
        }
        auto floor() const { return Rect(Min.floor(), Max.floor()); }
        auto height() const { return origin::abs(Max.Y - Min.Y); }
        bool intersects(const Rect& r) const
        {
            return r.Min.X <= Max.X && r.Min.Y <= Max.Y && r.Max.X >= Min.X &&
                   r.Max.Y >= Min.Y;
        }
        bool intersects(const Vec2& v1, const Vec2& v2) const
        {
            return v1.X >= Min.X - v2.X && v1.X <= Max.X + v2.X &&
                   v1.Y >= Min.Y - v2.Y && v1.Y <= Max.Y + v2.Y;
        }
        bool intersects(const Rect& r, const Vec2& p) const
        {
            return r.Min.X <= Max.X + p.X && r.Min.Y <= Max.Y + p.Y &&
                   r.Max.X >= Min.X - p.X && r.Max.Y >= Min.Y - p.Y;
        }
        auto max(const Rect& r) const -> Rect
        {
            return Rect(Min.max(r.Min), Max.max(r.Max));
        }
        auto min(const Rect& r) const -> Rect
        {
            return Rect(Min.min(r.Min), Max.min(r.Max));
        }
        auto normalize() const { return Rect(Min.normalize(), Max.normalize()); }
        auto reflect(const Rect& r) const
        {
            return Rect(Min.reflect(r.Min), Max.reflect(r.Max));
        }
        Rect rotate(f64 a) const
        {
            return Rect(Min.rotate(a), Max.rotate(a));
        }
        auto round() const -> Rect { return Rect(Min.round(), Max.round()); }
        auto size() const -> Vec2 { return (Max - Min).abs(); }
        auto topLeft() const -> Vec2 { return Min; }
        auto topRight() const -> Vec2 { return Vec2(Max.X, Min.Y); }
        auto trunc() const -> Rect { return Rect(Min.trunc(), Max.trunc()); }
        auto width() const -> f64 { return origin::abs(Max.X - Min.X); }
    };
    class Matrix
    {
    public:
        f64 X0{}, X1{}, X2{}, X3{}, Y0{}, Y1{}, Y2{}, Y3{}, Z0{}, Z1{}, Z2{}, Z3{}, W0{}, W1{}, W2{}, W3{};
        Matrix()
        {
            X0 = X1 = X2 = X3 = Y0 = Y1 = Y2 = Y3 = Z0 = Z1 = Z2 = Z3 = W0 = W1 = W2 = W3 = 0.0;
        }

        Matrix(f64 x0, f64 x1, f64 x2, f64 x3, f64 y0, f64 y1, f64 y2, f64 y3, f64 z0, f64 z1, f64 z2, f64 z3, f64 w0, f64 w1, f64 w2, f64 w3) :
            X0(x0), X1(x1), X2(x2), X3(x3), Y0(y0), Y1(y1), Y2(y2), Y3(y3), Z0(z0), Z1(z1), Z2(z2), Z3(z3), W0(w0), W1(w1), W2(w2), W3(w3) {}

        Matrix(Matrix&& m) noexcept :
            X0(m.X0), X1(m.X1), X2(m.X2), X3(m.X3), Y0(m.Y0), Y1(m.Y1), Y2(m.Y2), Y3(m.Y3), Z0(m.Z0), Z1(m.Z1), Z2(m.Z2), Z3(m.Z3), W0(m.W0), W1(m.W1), W2(m.W2), W3(m.W3) {}
        Matrix(const Matrix& m) :
            Matrix(m.X0, m.X1, m.X2, m.X3, m.Y0, m.Y1, m.Y2, m.Y3, m.Z0, m.Z1, m.Z2, m.Z3, m.W0, m.W1, m.W2, m.W3) {}
        ~Matrix() = default;

        Matrix& operator=(const Matrix& m) noexcept = default;
        auto operator=(Matrix&& m) noexcept -> Matrix&
        {
            X0 = m.X0;
            X1 = m.X1;
            X2 = m.X2;
            X3 = m.X3;
            Y0 = m.Y0;
            Y1 = m.Y1;
            Y2 = m.Y2;
            Y3 = m.Y3;
            Z0 = m.Z0;
            Z1 = m.Z1;
            Z2 = m.Z2;
            Z3 = m.Z3;
            W0 = m.W0;
            W1 = m.W1;
            W2 = m.W2;
            W3 = m.W3;
            return *this;
        }
        auto operator+(const Matrix& m) const -> Matrix { return { X0 + m.X0, X1 + m.X1, X2 + m.X2, X3 + m.X3, Y0 + m.Y0, Y1 + m.Y1, Y2 + m.Y2, Y3 + m.Y3, Z0 + m.Z0, Z1 + m.Z1, Z2 + m.Z2, Z3 + m.Z3, W0 + m.W0, W1 + m.W1, W2 + m.W2, W3 + m.W3 }; }
        auto operator-(const Matrix& m) const -> Matrix { return { X0 - m.X0, X1 - m.X1, X2 - m.X2, X3 - m.X3, Y0 - m.Y0, Y1 - m.Y1, Y2 - m.Y2, Y3 - m.Y3, Z0 - m.Z0, Z1 - m.Z1, Z2 - m.Z2, Z3 - m.Z3, W0 - m.W0, W1 - m.W1, W2 - m.W2, W3 - m.W3 }; }
        auto operator*(const Matrix& m) const -> Matrix { return Matrix(*this) *= m; }
        auto operator/(const Matrix& m) const -> Matrix { return Matrix(*this) /= m; }
        auto operator+=(const Matrix& m) -> Matrix
        {
            X0 += m.X0;
            X1 += m.X1;
            X2 += m.X2;
            X3 += m.X3;
            Y0 += m.Y0;
            Y1 += m.Y1;
            Y2 += m.Y2;
            Y3 += m.Y3;
            Z0 += m.Z0;
            Z1 += m.Z1;
            Z2 += m.Z2;
            Z3 += m.Z3;
            W0 += m.W0;
            W1 += m.W1;
            W2 += m.W2;
            W3 += m.W3;
            return *this;
        }
        auto operator-=(const Matrix& m) -> Matrix
        {
            X0 -= m.X0;
            X1 -= m.X1;
            X2 -= m.X2;
            X3 -= m.X3;
            Y0 -= m.Y0;
            Y1 -= m.Y1;
            Y2 -= m.Y2;
            Y3 -= m.Y3;
            Z0 -= m.Z0;
            Z1 -= m.Z1;
            Z2 -= m.Z2;
            Z3 -= m.Z3;
            W0 -= m.W0;
            W1 -= m.W1;
            W2 -= m.W2;
            W3 -= m.W3;
            return *this;
        }
        auto operator*=(const Matrix& m) -> Matrix
        {
            X0 = m.X0 * X0 + m.X1 * Y0 + m.X2 * Z0 + m.X3 * W0;
            X1 = m.X0 * X1 + m.X1 * Y1 + m.X2 * Z1 + m.X3 * W1;
            X2 = m.X0 * X2 + m.X1 * Y2 + m.X2 * Z2 + m.X3 * W2;
            X3 = m.X0 * X3 + m.X1 * Y3 + m.X2 * Z3 + m.X3 * W3;
            Y0 = m.Y0 * X0 + m.Y1 * Y0 + m.Y2 * Z0 + m.Y3 * W0;
            Y1 = m.Y0 * X1 + m.Y1 * Y1 + m.Y2 * Z1 + m.Y3 * W1;
            Y2 = m.Y0 * X2 + m.Y1 * Y2 + m.Y2 * Z2 + m.Y3 * W2;
            Y3 = m.Y0 * X3 + m.Y1 * Y3 + m.Y2 * Z3 + m.Y3 * W3;
            Z0 = m.Z0 * X0 + m.Z1 * Y0 + m.Z2 * Z0 + m.Z3 * W0;
            Z1 = m.Z0 * X1 + m.Z1 * Y1 + m.Z2 * Z1 + m.Z3 * W1;
            Z2 = m.Z0 * X2 + m.Z1 * Y2 + m.Z2 * Z2 + m.Z3 * W2;
            Z3 = m.Z0 * X3 + m.Z1 * Y3 + m.Z2 * Z3 + m.Z3 * W3;
            W0 = m.W0 * X0 + m.W1 * Y0 + m.W2 * Z0 + m.W3 * W0;
            W1 = m.W0 * X1 + m.W1 * Y1 + m.W2 * Z1 + m.W3 * W1;
            W2 = m.W0 * X2 + m.W1 * Y2 + m.W2 * Z2 + m.W3 * W2;
            W3 = m.W0 * X3 + m.W1 * Y3 + m.W2 * Z3 + m.W3 * W3;
            return *this;
        }

        auto operator/=(const Matrix& m) -> Matrix
        {
            X0 = m.X0 / X0 + m.X1 / Y0 + m.X2 / Z0 + m.X3 / W0;
            X1 = m.X0 / X1 + m.X1 / Y1 + m.X2 / Z1 + m.X3 / W1;
            X2 = m.X0 / X2 + m.X1 / Y2 + m.X2 / Z2 + m.X3 / W2;
            X3 = m.X0 / X3 + m.X1 / Y3 + m.X2 / Z3 + m.X3 / W3;
            Y0 = m.Y0 / X0 + m.Y1 / Y0 + m.Y2 / Z0 + m.Y3 / W0;
            Y1 = m.Y0 / X1 + m.Y1 / Y1 + m.Y2 / Z1 + m.Y3 / W1;
            Y2 = m.Y0 / X2 + m.Y1 / Y2 + m.Y2 / Z2 + m.Y3 / W2;
            Y3 = m.Y0 / X3 + m.Y1 / Y3 + m.Y2 / Z3 + m.Y3 / W3;
            Z0 = m.Z0 / X0 + m.Z1 / Y0 + m.Z2 / Z0 + m.Z3 / W0;
            Z1 = m.Z0 / X1 + m.Z1 / Y1 + m.Z2 / Z1 + m.Z3 / W1;
            Z2 = m.Z0 / X2 + m.Z1 / Y2 + m.Z2 / Z2 + m.Z3 / W2;
            Z3 = m.Z0 / X3 + m.Z1 / Y3 + m.Z2 / Z3 + m.Z3 / W3;
            W0 = m.W0 / X0 + m.W1 / Y0 + m.W2 / Z0 + m.W3 / W0;
            W1 = m.W0 / X1 + m.W1 / Y1 + m.W2 / Z1 + m.W3 / W1;
            W2 = m.W0 / X2 + m.W1 / Y2 + m.W2 / Z2 + m.W3 / W2;
            W3 = m.W0 / X3 + m.W1 / Y3 + m.W2 / Z3 + m.W3 / W3;
            return *this;
        }
        auto operator-() const -> Matrix
        {
            return { -X0, -X1, -X2, -X3, -Y0, -Y1, -Y2, -Y3, -Z0, -Z1, -Z2, -Z3, -W0, -W1, -W2, -W3 };
        }
        auto rotate(Vec3& v) const -> Vec3
        {
            return { X0 * v.X + Y0 * v.Y + Z0 * v.Z, X1 * v.X + Y1 * v.Y + Z1 * v.Z, X2 * v.X + Y2 * v.Y + Z2 * v.Z };
        }
        auto translate(Vec3& v) const -> Vec3
        {
            return { X3 * v.X + Y3 * v.Y + Z3 * v.Z, X3 * v.X + Y3 * v.Y + Z3 * v.Z, X3 * v.X + Y3 * v.Y + Z3 * v.Z };
        }
    };
    class Quaternion
    {
    public:
        f64 X0, X1, X2, X3, Y0, Y1, Y2, Y3, Z0, Z1, Z2, Z3, W0, W1, W2, W3;
        Quaternion()
        {
            X0 = X1 = X2 = X3 = Y0 = Y1 = Y2 = Y3 = Z0 = Z1 = Z2 = Z3 = W0 = W1 = W2 = W3 = 0.0;
        };
        Quaternion(Quaternion&&) noexcept = default;
        Quaternion(f64 x0, f64 x1, f64 x2, f64 x3, f64 y0, f64 y1, f64 y2, f64 y3, f64 z0, f64 z1, f64 z2, f64 z3, f64 w0, f64 w1, f64 w2, f64 w3) :
            X0(x0), X1(x1), X2(x2), X3(x3), Y0(y0), Y1(y1), Y2(y2), Y3(y3), Z0(z0), Z1(z1), Z2(z2), Z3(z3), W0(w0), W1(w1), W2(w2), W3(w3)
        {
        }
        Quaternion(Quaternion const&) = default;

        explicit Quaternion(const f64* in) noexcept :
            X0{ in[0] }, X1{ in[1] }, X2{ in[2] }, X3{ in[3] }, Y0{ in[4] }, Y1{ in[5] }, Y2{ in[6] }, Y3{ in[7] }, Z0{ in[8] }, Z1{ in[9] }, Z2{ in[10] }, Z3{ in[11] }, W0{ in[12] }, W1{ in[13] }, W2{ in[14] }, W3{ in[15] }
        {
        }
        Quaternion(const f64 x[4], const f64 y[4], const f64 z[4], const f64 w[4] = nullptr) noexcept :
            X0{ x[0] }, X1{ x[1] }, X2{ x[2] }, X3{ x[3] }, Y0{ y[0] }, Y1{ y[1] }, Y2{ y[2] }, Y3{ y[3] }, Z0{ z[0] }, Z1{ z[1] }, Z2{ z[2] }, Z3{ z[3] }, W0{ (w != nullptr) ? w[0] : 0.0 }, W1{ (w != nullptr) ? w[1] : 0.0 }, W2{ (w != nullptr) ? w[2] : 0.0 }, W3{ (w != nullptr) ? w[3] : 1.0 }
        {
        }

        ~Quaternion() = default;

        static auto rotate(const Quaternion& q, const Vec3& v) noexcept -> Vec3
        {
            const f64 xx{ q.X0 * v.X };
            const f64 yy{ q.Y0 * v.Y };
            const f64 zz{ q.Z0 * v.Z };
            const f64 xy{ q.X1 * v.Y };
            const f64 xz{ q.X2 * v.Z };
            const f64 yz{ q.Y2 * v.Z };
            const f64 wx{ q.W0 * v.X };
            const f64 wy{ q.W1 * v.Y };
            const f64 wz{ q.W2 * v.Z };
            return { v.X * (1.0 - 2.0 * (yy + zz)) + 2.0 * (xy - wz),
                     v.Y * (1.0 - 2.0 * (xx + zz)) + 2.0 * (xz + wy),
                     v.Z * (1.0 - 2.0 * (xx + yy)) + 2.0 * (yz - wx) };
        }

        static auto inverse(Quaternion& q) -> Quaternion
        {
            Quaternion o = q;

            o.X0 = -o.X0;
            o.Y0 = -o.Y0;
            o.Z0 = -o.Z0;
            o.W0 = -o.W0;

            o.X1 = -o.X1;
            o.Y1 = -o.Y1;
            o.Z1 = -o.Z1;
            o.W1 = -o.W1;

            o.X2 = -o.X2;
            o.Y2 = -o.Y2;
            o.Z2 = -o.Z2;
            o.W2 = -o.W2;

            o.X3 = -o.X3;
            o.Y3 = -o.Y3;
            o.Z3 = -o.Z3;
            o.W3 = -o.W3;

            const f64 len = o.length();
            o.X0 /= len;
            o.Y0 /= len;
            o.Z0 /= len;
            o.W0 /= len;
            o.X1 /= len;
            o.Y1 /= len;
            o.Z1 /= len;
            o.W1 /= len;
            o.X2 /= len;
            o.Y2 /= len;
            o.Z2 /= len;
            o.W2 /= len;
            o.X3 /= len;
            o.Y3 /= len;
            o.Z3 /= len;
            o.W3 /= len;
            return o;
        }

        static auto transform(const Quaternion& q, const Vec3& v)
        {
            const f64 x0 = q.X0 * v.X + q.Y0 * v.Z - q.Z0 * v.Y;
            const f64 y0 = q.Y0 * v.X + q.Z0 * v.Y + q.X0 * v.Z;
            const f64 z0 = q.Z0 * v.X - q.X0 * v.Y + q.Y0 * v.Z;
            const f64 x1 = q.X1 * v.X + q.Y1 * v.Z - q.Z1 * v.Y;
            const f64 y1 = q.Y1 * v.X + q.Z1 * v.Y + q.X1 * v.Z;
            const f64 z1 = q.Z1 * v.X - q.X1 * v.Y + q.Y1 * v.Z;
            const f64 x2 = q.X2 * v.X + q.Y2 * v.Z - q.Z2 * v.Y;
            const f64 y2 = q.Y2 * v.X + q.Z2 * v.Y + q.X2 * v.Z;
            const f64 z2 = q.Z2 * v.X - q.X2 * v.Y + q.Y2 * v.Z;
            const f64 x3 = q.X3 * v.X + q.Y3 * v.Z - q.Z3 * v.Y;
            const f64 y3 = q.Y3 * v.X + q.Z3 * v.Y + q.X3 * v.Z;
            const f64 z3 = q.Z3 * v.X - q.X3 * v.Y + q.Y3 * v.Z;

            return Quaternion(
                x0, x1, x2, x3, y0, y1, y2, y3, z0, z1, z2, z3, 0.0, 0.0, 0.0, 1.0);
        }

        static auto setPosition(const Quaternion& q, const Vec3& v) -> Quaternion
        {
            Quaternion out = q;
            out.W0 = v.X;
            out.W1 = v.Y;
            out.W2 = v.Z;
            return out;
        }
        static auto setRotation(const Quaternion& q, const Vec3& v) -> Quaternion
        {
            Quaternion out = q;
            out.X0 = v.X;
            out.X1 = v.Y;
            out.X2 = v.Z;
            return out;
        }
        static auto setScale(const Quaternion& q, const Vec3& v) -> Quaternion
        {
            Quaternion out = q;
            out.X0 = v.X;
            out.Y1 = v.Y;
            out.Z2 = v.Z;
            return out;
        }
        static auto getPosition(const Quaternion& q) -> Vec3
        {
            return { q.W0, q.W1, q.W2 };
        }
        static auto getRotation(const Quaternion& q) -> Vec3
        {
            return { q.X0, q.X1, q.X2 };
        }
        static auto getScale(const Quaternion& q) -> Vec3
        {
            return { q.X0, q.Y1, q.Z2 };
        }
        static auto rotate(const Quaternion& q, const Vec3& v, f64 a) -> Quaternion
        {
            Quaternion out = q;
            out.X0 = sin(a / 2.0F) * v.X;
            out.X1 = sin(a / 2.0F) * v.Y;
            out.X2 = sin(a / 2.0F) * v.Z;
            out.X3 = origin::cos(a / 2.0F);
            return out;
        }

        static auto rotate(const Quaternion& q, Vec3& axis, Face f) -> Quaternion
        {
            f64 const a = acos(q.X0) + PI * 2 * ((axis.X * axis.X + axis.Y * axis.Y + axis.Z * axis.Z) * 2.0 - 1.0);
            Vec3 dv{};
            if (f == Face::Right)
            {
                dv.X = origin::sin(a);
            }
            if (f == Face::Front)
            {
                dv.Y = origin::sin(a);
            }
            if (f == Face::Up)
            {
                dv.Z = origin::sin(a);
            }
            if (f == Face::Left)
            {
                dv.X = -origin::sin(a);
            }
            if (f == Face::Back)
            {
                dv.Y = -origin::sin(a);
            }
            if (f == Face::Down)
            {
                dv.Z = -origin::sin(a);
            }
            auto out = Quaternion(&axis.X, &axis.Y, &axis.Z);
            out *= Quaternion(&dv.X, &dv.Y, &dv.Z);
            return transform(out, axis);
        }
        [[nodiscard]] auto dot(const Quaternion& in, const Vec3& t) const -> f64
        {
            return X0 * in.X0 + Y0 * in.Y0 + Z0 * in.Z0 + W0 * in.W0 + t.X * in.X0 + t.Y * in.Y0 + t.Z * in.Z0 + t.X * in.X0 + t.Y * in.Y0 + t.Z * in.Z0;
        }
        [[nodiscard]] auto lengthSquared() const -> f64 { return dot(*this, Vec3(X0, Y0, Z0)); }

        [[nodiscard]] auto length() const -> f64 { return sqrt(lengthSquared()); }
        static auto translate(const Quaternion& in, const Vec3& t)
        {
            Quaternion out = in;
            out.W0 += t.X;
            out.W1 += t.Y;
            out.W2 += t.Z;
            return out;
        }
        auto normalize() noexcept -> Quaternion& { return *this = *this / length(); }
        auto toString() const noexcept -> string
        {
            string out = "\n";
            auto out0 = "Quaternion(" + std::to_string(X0) + ", " + std::to_string(Y0) + ", " + std::to_string(Z0) + ", " + std::to_string(W0) + ",\n";
            auto out1 = std::to_string(X1) + ", " + std::to_string(Y1) + ", " + std::to_string(Z1) + ", " + std::to_string(W1) + ",\n";
            auto out2 = std::to_string(X2) + ", " + std::to_string(Y2) + ", " + std::to_string(Z2) + ", " + std::to_string(W2) + ",\n";
            auto out3 = std::to_string(X3) + ", " + std::to_string(Y3) + ", " + std::to_string(Z3) + ", " + std::to_string(W3) + ");\n";
            out += out0 + std::string(11, ' ') + out1 + std::string(11, ' ') + out2 + std::string(11, ' ') + out3;
            return out;
        }
        auto operator=(Quaternion&& q) noexcept -> Quaternion&
        {
            X0 = q.X0;
            X1 = q.X1;
            X2 = q.X2;
            X3 = q.X3;
            Y0 = q.Y0;
            Y1 = q.Y1;
            Y2 = q.Y2;
            Y3 = q.Y3;
            Z0 = q.Z0;
            Z1 = q.Z1;
            Z2 = q.Z2;
            Z3 = q.Z3;
            W0 = q.W0;
            W1 = q.W1;
            W2 = q.W2;
            W3 = q.W3;
            return *this;
        }
        auto operator=(Quaternion const&) -> Quaternion& = default;
        auto operator=(const f64* f) -> auto&
        {
            *this = Quaternion(f);
            return *this;
        }
        explicit operator Quaternion*() { return cast<Quaternion*>(this); }
        explicit operator f64*() const { return cast<f64*>(*this); }

        auto operator+(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;
            out.X0 = X0 + q.X0;
            out.X1 = X1 + q.X1;
            out.X2 = X2 + q.X2;
            out.X3 = X3 + q.X3;
            out.Y0 = Y0 + q.Y0;
            out.Y1 = Y1 + q.Y1;
            out.Y2 = Y2 + q.Y2;
            out.Y3 = Y3 + q.Y3;
            out.Z0 = Z0 + q.Z0;
            out.Z1 = Z1 + q.Z1;
            out.Z2 = Z2 + q.Z2;
            out.Z3 = Z3 + q.Z3;
            out.W0 = W0 + q.W0;
            out.W1 = W1 + q.W1;
            out.W2 = W2 + q.W2;
            out.W3 = W3 + q.W3;
            return out;
        }

        auto operator-(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;
            out.X0 = X0 - q.X0;
            out.X1 = X1 - q.X1;
            out.X2 = X2 - q.X2;
            out.X3 = X3 - q.X3;
            out.Y0 = Y0 - q.Y0;
            out.Y1 = Y1 - q.Y1;
            out.Y2 = Y2 - q.Y2;
            out.Y3 = Y3 - q.Y3;
            out.Z0 = Z0 - q.Z0;
            out.Z1 = Z1 - q.Z1;
            out.Z2 = Z2 - q.Z2;
            out.Z3 = Z3 - q.Z3;
            out.W0 = W0 - q.W0;
            out.W1 = W1 - q.W1;
            out.W2 = W2 - q.W2;
            out.W3 = W3 - q.W3;
            return out;
        }
        auto operator*(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;
            out.X0 = X0 * q.X0 - Y0 * q.Y0 - Z0 * q.Z0 - W0 * q.W0;
            out.Y0 = X0 * q.Y0 + Y0 * q.X0 + Z0 * q.W0 - W0 * q.Z0;
            out.Z0 = X0 * q.Z0 + Y0 * q.W0 - Z0 * q.X0 + W0 * q.Y0;
            out.W0 = X0 * q.W0 + Y0 * q.Z0 + Z0 * q.Y0 + W0 * q.X0;
            out.X1 = X1 * q.X1 - Y1 * q.Y1 - Z1 * q.Z1 - W1 * q.W1;
            out.Y1 = X1 * q.Y1 + Y1 * q.X1 + Z1 * q.W1 - W1 * q.Z1;
            out.Z1 = X1 * q.Z1 + Y1 * q.W1 - Z1 * q.X1 + W1 * q.Y1;
            out.W1 = X1 * q.W1 + Y1 * q.Z1 + Z1 * q.Y1 + W1 * q.X1;
            out.X2 = X2 * q.X2 - Y2 * q.Y2 - Z2 * q.Z2 - W2 * q.W2;
            out.Y2 = X2 * q.Y2 + Y2 * q.X2 + Z2 * q.W2 - W2 * q.Z2;
            out.Z2 = X2 * q.Z2 + Y2 * q.W2 - Z2 * q.X2 + W2 * q.Y2;
            out.W2 = X2 * q.W2 + Y2 * q.Z2 + Z2 * q.Y2 + W2 * q.X2;
            out.X3 = X3 * q.X3 - Y3 * q.Y3 - Z3 * q.Z3 - W3 * q.W3;
            out.Y3 = X3 * q.Y3 + Y3 * q.X3 + Z3 * q.W3 - W3 * q.Z3;
            out.Z3 = X3 * q.Z3 + Y3 * q.W3 - Z3 * q.X3 + W3 * q.Y3;
            out.W3 = X3 * q.W3 + Y3 * q.Z3 + Z3 * q.Y3 + W3 * q.X3;
            return out;
        }

        auto operator/(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;
            out.X0 = X0 / q.X0 - Y0 / q.Y0 - Z0 / q.Z0 - W0 / q.W0;
            out.Y0 = X0 / q.Y0 + Y0 / q.X0 + Z0 / q.W0 - W0 / q.Z0;
            out.Z0 = X0 / q.Z0 + Y0 / q.W0 - Z0 / q.X0 + W0 / q.Y0;
            out.W0 = X0 / q.W0 + Y0 / q.Z0 + Z0 / q.Y0 + W0 / q.X0;
            out.X1 = X1 / q.X1 - Y1 / q.Y1 - Z1 / q.Z1 - W1 / q.W1;
            out.Y1 = X1 / q.Y1 + Y1 / q.X1 + Z1 / q.W1 - W1 / q.Z1;
            out.Z1 = X1 / q.Z1 + Y1 / q.W1 - Z1 / q.X1 + W1 / q.Y1;
            out.W1 = X1 / q.W1 + Y1 / q.Z1 + Z1 / q.Y1 + W1 / q.X1;
            out.X2 = X2 / q.X2 - Y2 / q.Y2 - Z2 / q.Z2 - W2 / q.W2;
            out.Y2 = X2 / q.Y2 + Y2 / q.X2 + Z2 / q.W2 - W2 / q.Z2;
            out.Z2 = X2 / q.Z2 + Y2 / q.W2 - Z2 / q.X2 + W2 / q.Y2;
            out.W2 = X2 / q.W2 + Y2 / q.Z2 + Z2 / q.Y2 + W2 / q.X2;
            out.X3 = X3 / q.X3 - Y3 / q.Y3 - Z3 / q.Z3 - W3 / q.W3;
            out.Y3 = X3 / q.Y3 + Y3 / q.X3 + Z3 / q.W3 - W3 / q.Z3;
            out.Z3 = X3 / q.Z3 + Y3 / q.W3 - Z3 / q.X3 + W3 / q.Y3;
            out.W3 = X3 / q.W3 + Y3 / q.Z3 + Z3 / q.Y3 + W3 / q.X3;
            return out;
        }

        auto operator+=(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;
            out.X0 += q.X0;
            out.Y0 += q.Y0;
            out.Z0 += q.Z0;
            out.W0 += q.W0;
            out.X1 += q.X1;
            out.Y1 += q.Y1;
            out.Z1 += q.Z1;
            out.W1 += q.W1;
            out.X2 += q.X2;
            out.Y2 += q.Y2;
            out.Z2 += q.Z2;
            out.W2 += q.W2;
            out.X3 += q.X3;
            out.Y3 += q.Y3;
            out.Z3 += q.Z3;
            out.W3 += q.W3;
            return out;
        }

        auto operator-=(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;

            out.X0 -= q.X0;
            out.Y0 -= q.Y0;
            out.Z0 -= q.Z0;
            out.W0 -= q.W0;
            out.X1 -= q.X1;
            out.Y1 -= q.Y1;
            out.Z1 -= q.Z1;
            out.W1 -= q.W1;
            out.X2 -= q.X2;
            out.Y2 -= q.Y2;
            out.Z2 -= q.Z2;
            out.W2 -= q.W2;
            out.X3 -= q.X3;
            out.Y3 -= q.Y3;
            out.Z3 -= q.Z3;
            out.W3 -= q.W3;
            return out;
        }

        auto operator*=(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;
            out.X0 = X0 * q.X0 - Y0 * q.Y0 - Z0 * q.Z0 - W0 * q.W0;
            out.Y0 = X0 * q.Y0 + Y0 * q.X0 - Z0 * q.W0 + W0 * q.Z0;
            out.Z0 = X0 * q.Z0 + Y0 * q.W0 + Z0 * q.X0 - W0 * q.Y0;
            out.W0 = X0 * q.W0 - Y0 * q.Z0 + Z0 * q.Y0 + W0 * q.X0;
            out.X1 = X1 * q.X1 - Y1 * q.Y1 - Z1 * q.Z1 - W1 * q.W1;
            out.Y1 = X1 * q.Y1 + Y1 * q.X1 - Z1 * q.W1 + W1 * q.Z1;
            out.Z1 = X1 * q.Z1 + Y1 * q.W1 + Z1 * q.X1 - W1 * q.Y1;
            out.W1 = X1 * q.W1 - Y1 * q.Z1 + Z1 * q.Y1 + W1 * q.X1;
            out.X2 = X2 * q.X2 - Y2 * q.Y2 - Z2 * q.Z2 - W2 * q.W2;
            out.Y2 = X2 * q.Y2 + Y2 * q.X2 - Z2 * q.W2 + W2 * q.Z2;
            out.Z2 = X2 * q.Z2 + Y2 * q.W2 + Z2 * q.X2 - W2 * q.Y2;
            out.W2 = X2 * q.W2 - Y2 * q.Z2 + Z2 * q.Y2 + W2 * q.X2;
            out.X3 = X3 * q.X3 - Y3 * q.Y3 - Z3 * q.Z3 - W3 * q.W3;
            out.Y3 = X3 * q.Y3 + Y3 * q.X3 - Z3 * q.W3 + W3 * q.Z3;
            out.Z3 = X3 * q.Z3 + Y3 * q.W3 + Z3 * q.X3 - W3 * q.Y3;
            out.W3 = X3 * q.W3 - Y3 * q.Z3 + Z3 * q.Y3 + W3 * q.X3;
            return out;
        }
        auto operator/=(const Quaternion& q) const -> Quaternion
        {
            Quaternion out = *this;
            out.X0 = X0 / q.X0 - Y0 / q.Y0 - Z0 / q.Z0 - W0 / q.W0;
            out.Y0 = X0 / q.Y0 + Y0 / q.X0 - Z0 / q.W0 + W0 / q.Z0;
            out.Z0 = X0 / q.Z0 + Y0 / q.W0 + Z0 / q.X0 - W0 / q.Y0;
            out.W0 = X0 / q.W0 - Y0 / q.Z0 + Z0 / q.Y0 + W0 / q.X0;
            out.X1 = X1 / q.X1 - Y1 / q.Y1 - Z1 / q.Z1 - W1 / q.W1;
            out.Y1 = X1 / q.Y1 + Y1 / q.X1 - Z1 / q.W1 + W1 / q.Z1;
            out.Z1 = X1 / q.Z1 + Y1 / q.W1 + Z1 / q.X1 - W1 / q.Y1;
            out.W1 = X1 / q.W1 - Y1 / q.Z1 + Z1 / q.Y1 + W1 / q.X1;
            out.X2 = X2 / q.X2 - Y2 / q.Y2 - Z2 / q.Z2 - W2 / q.W2;
            out.Y2 = X2 / q.Y2 + Y2 / q.X2 - Z2 / q.W2 + W2 / q.Z2;
            out.Z2 = X2 / q.Z2 + Y2 / q.W2 + Z2 / q.X2 - W2 / q.Y2;
            out.W2 = X2 / q.W2 - Y2 / q.Z2 + Z2 / q.Y2 + W2 / q.X2;
            out.X3 = X3 / q.X3 - Y3 / q.Y3 - Z3 / q.Z3 - W3 / q.W3;
            out.Y3 = X3 / q.Y3 + Y3 / q.X3 - Z3 / q.W3 + W3 / q.Z3;
            out.Z3 = X3 / q.Z3 + Y3 / q.W3 + Z3 / q.X3 - W3 / q.Y3;
            out.W3 = X3 / q.W3 - Y3 / q.Z3 + Z3 / q.Y3 + W3 / q.X3;
            return out;
        }
        auto operator+(const f64 f) const -> Quaternion
        {
            Quaternion o = *this;
            o.X0 += f;
            o.Y0 += f;
            o.Z0 += f;
            o.W0 += f;
            o.X1 += f;
            o.Y1 += f;
            o.Z1 += f;
            o.W1 += f;
            o.X2 += f;
            o.Y2 += f;
            o.Z2 += f;
            o.W2 += f;
            o.X3 += f;
            o.Y3 += f;
            o.Z3 += f;
            o.W3 += f;
            return o;
        }
        auto operator-(const f64 q) const -> Quaternion
        {
            Quaternion o = *this;
            o.X0 -= q;
            o.Y0 -= q;
            o.Z0 -= q;
            o.W0 -= q;
            o.X1 -= q;
            o.Y1 -= q;
            o.Z1 -= q;
            o.W1 -= q;
            o.X2 -= q;
            o.Y2 -= q;
            o.Z2 -= q;
            o.W2 -= q;
            o.X3 -= q;
            o.Y3 -= q;
            o.Z3 -= q;
            o.W3 -= q;
            return o;
        }
        auto operator*(const f64 f) const -> Quaternion
        {
            Quaternion o = *this;
            o.X0 = X0 * f;
            o.Y0 = Y0 * f;
            o.Z0 = Z0 * f;
            o.W0 = W0 * f;
            o.X1 = X1 * f;
            o.Y1 = Y1 * f;
            o.Z1 = Z1 * f;
            o.W1 = W1 * f;
            o.X2 = X2 * f;
            o.Y2 = Y2 * f;
            o.Z2 = Z2 * f;
            o.W2 = W2 * f;
            o.X3 = X3 * f;
            o.Y3 = Y3 * f;
            o.Z3 = Z3 * f;
            o.W3 = W3 * f;
            return o;
        }
        auto operator/(const f64 f) const -> Quaternion
        {
            Quaternion o = *this;
            o.X0 = X0 / f;
            o.Y0 = Y0 / f;
            o.Z0 = Z0 / f;
            o.W0 = W0 / f;
            o.X1 = X1 / f;
            o.Y1 = Y1 / f;
            o.Z1 = Z1 / f;
            o.W1 = W1 / f;
            o.X2 = X2 / f;
            o.Y2 = Y2 / f;
            o.Z2 = Z2 / f;
            o.W2 = W2 / f;
            o.X3 = X3 / f;
            o.Y3 = Y3 / f;
            o.Z3 = Z3 / f;
            o.W3 = W3 / f;
            return o;
        }
        auto operator-() const noexcept -> Quaternion
        {
            Quaternion o;
            o.X0 = -X0;
            o.Y0 = -Y0;
            o.Z0 = -Z0;
            o.W0 = -W0;
            o.X1 = -X1;
            o.Y1 = -Y1;
            o.Z1 = -Z1;
            o.W1 = -W1;
            o.X2 = -X2;
            o.Y2 = -Y2;
            o.Z2 = -Z2;
            o.W2 = -W2;
            o.X3 = -X3;
            o.Y3 = -Y3;
            o.Z3 = -Z3;
            o.W3 = -W3;
            return o;
        }
        operator f64*()
        {
            return cast<f64*>(*this);
        }
        operator const f64*() const { return cast<const f64*>(*this); }

        operator std::string() const { return toString(); }
        auto operator==(const Quaternion& q) const -> bool
        {
            return (X0 == q.X0) && (Y0 == q.Y0) && (Z0 == q.Z0) && (W0 == q.W0) &&
                   (X1 == q.X1) && (Y1 == q.Y1) && (Z1 == q.Z1) && (W1 == q.W1) &&
                   (X2 == q.X2) && (Y2 == q.Y2) && (Z2 == q.Z2) && (W2 == q.W2) &&
                   (X3 == q.X3) && (Y3 == q.Y3) && (Z3 == q.Z3) && (W3 == q.W3);
        }

        auto operator!=(const Quaternion& q) const -> bool
        {
            return !(*this == q);
        }
    };
} // namespace origin
#endif // GEOMETRY_HPP
