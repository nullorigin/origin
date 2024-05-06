#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#pragma once
#include "Basic.hpp"

#include "Vector.hpp"

#include <string>

namespace Origin
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

    template<u64 N>
    class Vec : public Vector<f64>
    {
        f64* Data{};
        friend Vector<f64>;

    public:
        Vec()
        {
            this->Data = new f64[N];
        }
        Vec(Vec const& rhs) = default;
        explicit Vec(f64 const* ap)
        {
            this->Data = new f64[N];
            for (auto i = 0; i < N; ++i)
            {
                this->Data[i] = ap[i];
            }
        }
        Vec(Vec&& rhs) noexcept :
            Data(rhs.Data) { rhs.Data = nullptr; }
        ~Vec() { delete[] this; }

        [[nodiscard]] auto get_data() const -> f64* { return this->Data; }

        auto operator=(Vec const& rhs) -> Vec& = default;
        auto operator=(f64 const* ap) -> Vec&
        {
            memcpy(this->Data, ap, N * sizeof(f64));
            return *this;
        }
        auto operator=(Vec&& rhs) -> Vec& = default;
        auto operator[](u64 i) -> f64& { return this->Get(i); }
        auto operator[](u64 i) const -> f64 { return this->Get(i); }
        auto operator+(f64 const& rhs) -> Vec { return this->Add(rhs); }
        auto operator-(f64 const& rhs) -> Vec { return this->Sub(-rhs); }
        auto operator*(f64 const& rhs) -> Vec { return this->Mul(rhs); }
        auto operator/(f64 const& rhs) -> Vec { return this->Div(rhs); }
        auto operator+(Vec const& rhs) -> Vec { return this->Add(rhs); }
        auto operator-(Vec const& rhs) -> Vec { return this->Sub(rhs); }
        auto operator*(Vec const& rhs) -> Vec { return this->Mul(rhs); }
        auto operator/(Vec const& rhs) -> Vec { return this->Div(rhs); }
    };
    class Vec2
    {
    public:
        union
        {
            f64* Data = new f64[2];
            struct
            {
                f64 X;
                f64 Y;
            } __attribute__((aligned(16)));
        };
        Vec2() = default;
        Vec2(Vec2 const& rhs)
        {
            X = rhs.X;
            Y = rhs.Y;
        }
        Vec2(Vec2&& rhs) noexcept
        {
            X = rhs.X;
            Y = rhs.Y;
            rhs.Data = nullptr;
        }
        Vec2(f64 x, f64 y)
        {
            X = x;
            Y = y;
        }
        ~Vec2() { delete[] this->Data; }
    };

    class Vec3
    {
    public:
        f64 X, Y, Z;
        Vec3() = default;
        Vec3(Vec3 const&) = default;
        Vec3(Vec3&&) = default;
        ~Vec3() = default;
        Vec3(f64 x, f64 y, f64 z)
        {
            X = x;
            Y = y;
            Z = z;
        }
        auto operator=(Vec3 const&) -> Vec3& = default;
        auto operator=(Vec3&&) -> Vec3& = default;
        auto operator+(f64 rhs) const -> Vec3 { return { X + rhs, Y + rhs, Z + rhs }; }
        auto operator-(f64 rhs) const -> Vec3 { return { X - rhs, Y - rhs, Z - rhs }; }
        auto operator*(Vec3 const& rhs) const -> Vec3 { return { X * rhs.X, Y * rhs.Y, Z * rhs.Z }; }
        auto operator/(Vec3 const& rhs) const -> Vec3 { return { X / rhs.X, Y / rhs.Y, Z / rhs.Z }; }
        auto operator+(Vec3 const& rhs) const -> Vec3 { return { X + rhs.X, Y + rhs.Y, Z + rhs.Z }; }
        auto operator-(Vec3 const& rhs) const -> Vec3 { return { X - rhs.X, Y - rhs.Y, Z - rhs.Z }; }
        auto operator*(f64 rhs) const -> Vec3 { return { X * rhs, Y * rhs, Z * rhs }; }
        auto operator/(f64 rhs) const -> Vec3 { return { X / rhs, Y / rhs, Z / rhs }; }
    };

    class Vec4
    {
    public:
        f64 X, Y, Z, W;
        Vec4() = default;
        Vec4(Vec4 const&) = default;
        Vec4(Vec4&&) = default;
        Vec4(f64 x, f64 y, f64 z, f64 w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        ~Vec4() = default;
        auto operator=(Vec4&& rhs) noexcept -> Vec4& { return *this = rhs; }
        auto operator=(Vec4 const& rhs) -> Vec4& = default;
        auto operator+(Vec4 const& rhs) const -> Vec4 { return { X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W }; }

        auto operator-(Vec4 const& rhs) const -> Vec4 { return { X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W }; }

        auto operator*(f64 rhs) const -> Vec4 { return { X * rhs, Y * rhs, Z * rhs, W * rhs }; }

        auto operator/(f64 rhs) const -> Vec4 { return { X / rhs, Y / rhs, Z / rhs, W / rhs }; }
    };
    class Quaternion
    {
    private:
        union
        {
            f64* Data = new f64[16];
            struct
            {
                f64 X0;
                f64 X1;
                f64 X2;
                f64 X3;
                f64 Y0;
                f64 Y1;
                f64 Y2;
                f64 Y3;
                f64 Z0;
                f64 Z1;
                f64 Z2;
                f64 Z3;
                f64 W0;
                f64 W1;
                f64 W2;
                f64 W3;
            } __attribute__((aligned(128)));
        };

    public:
        Quaternion()
        {
            X0 = X1 = X2 = X3 = Y0 = Y1 = Y2 = Y3 = Z0 = Z1 = Z2 = Z3 = W0 = W1 = W2 = W3 = 0.0;
        };
        Quaternion(Quaternion&&) noexcept = default;
        Quaternion(f64 x0, f64 x1, f64 x2, f64 x3, f64 y0, f64 y1, f64 y2, f64 y3, f64 z0, f64 z1, f64 z2, f64 z3, f64 w0, f64 w1, f64 w2, f64 w3)
        {
            X0 = x0;
            X1 = x1;
            X2 = x2;
            X3 = x3;
            Y0 = y0;
            Y1 = y1;
            Y2 = y2;
            Y3 = y3;
            Z0 = z0;
            Z1 = z1;
            Z2 = z2;
            Z3 = z3;
            W0 = w0;
            W1 = w1;
            W2 = w2;
            W3 = w3;
        }
        Quaternion(Quaternion const&) = default;

        explicit Quaternion(const f64* src) noexcept :
            X0{ src[0] }, X1{ src[1] }, X2{ src[2] }, X3{ src[3] }, Y0{ src[4] }, Y1{ src[5] }, Y2{ src[6] }, Y3{ src[7] }, Z0{ src[8] }, Z1{ src[9] }, Z2{ src[10] }, Z3{ src[11] }, W0{ src[12] }, W1{ src[13] }, W2{ src[14] }, W3{ src[15] }
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

        auto operator/(const Vec3& rhs) const noexcept -> Vec3
        {
            return { X0 / rhs.X, X1 / rhs.Y, X2 / rhs.Z };
        }
        static auto inverse(Quaternion& q) -> Quaternion
        {
            Quaternion ret = q;
            ret.W0 = -ret.W0;
            ret.W1 = -ret.W1;
            ret.W2 = -ret.W2;
            ret.W3 = ret.W3;
            ret.X0 = -ret.X0;
            ret.X1 = -ret.X1;
            ret.X2 = -ret.X2;
            ret.X3 = -ret.X3;
            ret.Y0 = -ret.Y0;
            ret.Y1 = -ret.Y1;
            ret.Y2 = -ret.Y2;
            ret.Y3 = -ret.Y3;
            ret.Z0 = -ret.Z0;
            ret.Z1 = -ret.Z1;
            ret.Z2 = -ret.Z2;
            ret.Z3 = -ret.Z3;
            ret.W3 = ret.W3;
            return ret;
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

        static auto set_position(const Quaternion& q, const Vec3& v) -> Quaternion
        {
            Quaternion ret = q;
            ret.W0 = v.X;
            ret.W1 = v.Y;
            ret.W2 = v.Z;
            return ret;
        }
        static auto set_rotation(const Quaternion& q, const Vec3& v) -> Quaternion
        {
            Quaternion ret = q;
            ret.X0 = v.X;
            ret.X1 = v.Y;
            ret.X2 = v.Z;
            return ret;
        }
        static auto set_scale(const Quaternion& q, const Vec3& v) -> Quaternion
        {
            Quaternion ret = q;
            ret.X0 = v.X;
            ret.Y1 = v.Y;
            ret.Z2 = v.Z;
            return ret;
        }
        static auto get_position(const Quaternion& q)
        {
            return new f64[3]{ q.W0, q.W1, q.W2 };
        }
        static auto get_rotation(const Quaternion& q)
        {
            return new f64[3]{ q.X0, q.X1, q.X2 };
        }
        static auto get_scale(const Quaternion& q)
        {
            return new f64[3]{ q.X0, q.Y1, q.Z2 };
        }
        static auto rotate(const Quaternion& q, const Vec3& vec, f64 angle)
        {
            Quaternion ret = q;
            ret.X0 = sin(angle / 2.0F) * vec.X;
            ret.X1 = sin(angle / 2.0F) * vec.Y;
            ret.X2 = sin(angle / 2.0F) * vec.Z;
            ret.X3 = cos(angle / 2.0F);
            return ret;
        }

        static auto rotate(const Quaternion& q, Vec3& axis, Face face)
        {
            f64 const a = acos(q.X0) + PI * 2 * ((axis.X * axis.X + axis.Y * axis.Y + axis.Z * axis.Z) * 2.0 - 1.0);
            Vec3 dv;
            if (face == Face::Right)
            {
                dv.X = sin(a);
            }
            if (face == Face::Front)
            {
                dv.Y = sin(a);
            }
            if (face == Face::Up)
            {
                dv.Z = sin(a);
            }
            if (face == Face::Left)
            {
                dv.X = -sin(a);
            }
            if (face == Face::Back)
            {
                dv.Y = -sin(a);
            }
            if (face == Face::Down)
            {
                dv.Z = -sin(a);
            }
            auto ret = Quaternion(&axis.X, &axis.Y, &axis.Z);
            ret = ret * Quaternion(&dv.X, &dv.Y, &dv.Z);
            return transform(ret, axis);
        }
        [[nodiscard]] auto dot(const Quaternion& rhs, const Vec3& t) const
        {
            return X0 * rhs.X0 + Y0 * rhs.Y0 + Z0 * rhs.Z0 + W0 * rhs.W0 + t.X * rhs.X0 + t.Y * rhs.Y0 + t.Z * rhs.Z0 + t.X * rhs.X0 + t.Y * rhs.Y0 + t.Z * rhs.Z0;
        }
        [[nodiscard]] auto length_squared() const -> f64 { return dot(*this, Vec3(X0, Y0, Z0)); }

        [[nodiscard]] auto length() const -> f64 { return sqrt(length_squared()); }
        static auto translate(const Quaternion& q, const Vec3& t)
        {
            Quaternion ret = q;
            ret.W0 += t.X;
            ret.W1 += t.Y;
            ret.W2 += t.Z;
            return ret;
        }
        auto operator=(Quaternion&& rhs) noexcept -> Quaternion&
        {
            *this->Data = *rhs.Data;
            return *this;
        }
        auto operator=(Quaternion const&) -> Quaternion& = default;
        auto operator=(const f64* src) -> auto&
        {
            *this = Quaternion(src);
            return *this;
        }
        explicit operator Quaternion*() { return this; }
        explicit operator f64*() const { return Data; }

        auto operator+(const Quaternion& other) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 + other.X0;
            ret.X1 = X1 + other.X1;
            ret.X2 = X2 + other.X2;
            ret.X3 = X3 + other.X3;
            ret.Y0 = Y0 + other.Y0;
            ret.Y1 = Y1 + other.Y1;
            ret.Y2 = Y2 + other.Y2;
            ret.Y3 = Y3 + other.Y3;
            ret.Z0 = Z0 + other.Z0;
            ret.Z1 = Z1 + other.Z1;
            ret.Z2 = Z2 + other.Z2;
            ret.Z3 = Z3 + other.Z3;
            ret.W0 = W0 + other.W0;
            ret.W1 = W1 + other.W1;
            ret.W2 = W2 + other.W2;
            ret.W3 = W3 + other.W3;
            return ret;
        }

        auto operator-(const Quaternion& other) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 - other.X0;
            ret.X1 = X1 - other.X1;
            ret.X2 = X2 - other.X2;
            ret.X3 = X3 - other.X3;
            ret.Y0 = Y0 - other.Y0;
            ret.Y1 = Y1 - other.Y1;
            ret.Y2 = Y2 - other.Y2;
            ret.Y3 = Y3 - other.Y3;
            ret.Z0 = Z0 - other.Z0;
            ret.Z1 = Z1 - other.Z1;
            ret.Z2 = Z2 - other.Z2;
            ret.Z3 = Z3 - other.Z3;
            ret.W0 = W0 - other.W0;
            ret.W1 = W1 - other.W1;
            ret.W2 = W2 - other.W2;
            ret.W3 = W3 - other.W3;
            return ret;
        }
        auto operator*(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 * rhs.X0 - Y0 * rhs.Y0 - Z0 * rhs.Z0 - W0 * rhs.W0;
            ret.Y0 = X0 * rhs.Y0 + Y0 * rhs.X0 + Z0 * rhs.W0 - W0 * rhs.Z0;
            ret.Z0 = X0 * rhs.Z0 + Y0 * rhs.W0 - Z0 * rhs.X0 + W0 * rhs.Y0;
            ret.W0 = X0 * rhs.W0 + Y0 * rhs.Z0 + Z0 * rhs.Y0 + W0 * rhs.X0;
            ret.X1 = X1 * rhs.X1 - Y1 * rhs.Y1 - Z1 * rhs.Z1 - W1 * rhs.W1;
            ret.Y1 = X1 * rhs.Y1 + Y1 * rhs.X1 + Z1 * rhs.W1 - W1 * rhs.Z1;
            ret.Z1 = X1 * rhs.Z1 + Y1 * rhs.W1 - Z1 * rhs.X1 + W1 * rhs.Y1;
            ret.W1 = X1 * rhs.W1 + Y1 * rhs.Z1 + Z1 * rhs.Y1 + W1 * rhs.X1;
            ret.X2 = X2 * rhs.X2 - Y2 * rhs.Y2 - Z2 * rhs.Z2 - W2 * rhs.W2;
            ret.Y2 = X2 * rhs.Y2 + Y2 * rhs.X2 + Z2 * rhs.W2 - W2 * rhs.Z2;
            ret.Z2 = X2 * rhs.Z2 + Y2 * rhs.W2 - Z2 * rhs.X2 + W2 * rhs.Y2;
            ret.W2 = X2 * rhs.W2 + Y2 * rhs.Z2 + Z2 * rhs.Y2 + W2 * rhs.X2;
            ret.X3 = X3 * rhs.X3 - Y3 * rhs.Y3 - Z3 * rhs.Z3 - W3 * rhs.W3;
            ret.Y3 = X3 * rhs.Y3 + Y3 * rhs.X3 + Z3 * rhs.W3 - W3 * rhs.Z3;
            ret.Z3 = X3 * rhs.Z3 + Y3 * rhs.W3 - Z3 * rhs.X3 + W3 * rhs.Y3;
            ret.W3 = X3 * rhs.W3 + Y3 * rhs.Z3 + Z3 * rhs.Y3 + W3 * rhs.X3;
            return ret;
        }

        auto operator/(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 / rhs.X0 - Y0 / rhs.Y0 - Z0 / rhs.Z0 - W0 / rhs.W0;
            ret.Y0 = X0 / rhs.Y0 + Y0 / rhs.X0 + Z0 / rhs.W0 - W0 / rhs.Z0;
            ret.Z0 = X0 / rhs.Z0 + Y0 / rhs.W0 - Z0 / rhs.X0 + W0 / rhs.Y0;
            ret.W0 = X0 / rhs.W0 + Y0 / rhs.Z0 + Z0 / rhs.Y0 + W0 / rhs.X0;
            ret.X1 = X1 / rhs.X1 - Y1 / rhs.Y1 - Z1 / rhs.Z1 - W1 / rhs.W1;
            ret.Y1 = X1 / rhs.Y1 + Y1 / rhs.X1 + Z1 / rhs.W1 - W1 / rhs.Z1;
            ret.Z1 = X1 / rhs.Z1 + Y1 / rhs.W1 - Z1 / rhs.X1 + W1 / rhs.Y1;
            ret.W1 = X1 / rhs.W1 + Y1 / rhs.Z1 + Z1 / rhs.Y1 + W1 / rhs.X1;
            ret.X2 = X2 / rhs.X2 - Y2 / rhs.Y2 - Z2 / rhs.Z2 - W2 / rhs.W2;
            ret.Y2 = X2 / rhs.Y2 + Y2 / rhs.X2 + Z2 / rhs.W2 - W2 / rhs.Z2;
            ret.Z2 = X2 / rhs.Z2 + Y2 / rhs.W2 - Z2 / rhs.X2 + W2 / rhs.Y2;
            ret.W2 = X2 / rhs.W2 + Y2 / rhs.Z2 + Z2 / rhs.Y2 + W2 / rhs.X2;
            ret.X3 = X3 / rhs.X3 - Y3 / rhs.Y3 - Z3 / rhs.Z3 - W3 / rhs.W3;
            ret.Y3 = X3 / rhs.Y3 + Y3 / rhs.X3 + Z3 / rhs.W3 - W3 / rhs.Z3;
            ret.Z3 = X3 / rhs.Z3 + Y3 / rhs.W3 - Z3 / rhs.X3 + W3 / rhs.Y3;
            ret.W3 = X3 / rhs.W3 + Y3 / rhs.Z3 + Z3 / rhs.Y3 + W3 / rhs.X3;
            return ret;
        }

        auto operator+=(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 += rhs.X0;
            ret.Y0 += rhs.Y0;
            ret.Z0 += rhs.Z0;
            ret.W0 += rhs.W0;
            ret.X1 += rhs.X1;
            ret.Y1 += rhs.Y1;
            ret.Z1 += rhs.Z1;
            ret.W1 += rhs.W1;
            ret.X2 += rhs.X2;
            ret.Y2 += rhs.Y2;
            ret.Z2 += rhs.Z2;
            ret.W2 += rhs.W2;
            ret.X3 += rhs.X3;
            ret.Y3 += rhs.Y3;
            ret.Z3 += rhs.Z3;
            ret.W3 += rhs.W3;
            return ret;
        }

        auto operator-=(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion ret = *this;

            ret.X0 -= rhs.X0;
            ret.Y0 -= rhs.Y0;
            ret.Z0 -= rhs.Z0;
            ret.W0 -= rhs.W0;
            ret.X1 -= rhs.X1;
            ret.Y1 -= rhs.Y1;
            ret.Z1 -= rhs.Z1;
            ret.W1 -= rhs.W1;
            ret.X2 -= rhs.X2;
            ret.Y2 -= rhs.Y2;
            ret.Z2 -= rhs.Z2;
            ret.W2 -= rhs.W2;
            ret.X3 -= rhs.X3;
            ret.Y3 -= rhs.Y3;
            ret.Z3 -= rhs.Z3;
            ret.W3 -= rhs.W3;
            return ret;
        }

        auto operator*=(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 * rhs.X0 - Y0 * rhs.Y0 - Z0 * rhs.Z0 - W0 * rhs.W0;
            ret.Y0 = X0 * rhs.Y0 + Y0 * rhs.X0 - Z0 * rhs.W0 + W0 * rhs.Z0;
            ret.Z0 = X0 * rhs.Z0 + Y0 * rhs.W0 + Z0 * rhs.X0 - W0 * rhs.Y0;
            ret.W0 = X0 * rhs.W0 - Y0 * rhs.Z0 + Z0 * rhs.Y0 + W0 * rhs.X0;
            ret.X1 = X1 * rhs.X1 - Y1 * rhs.Y1 - Z1 * rhs.Z1 - W1 * rhs.W1;
            ret.Y1 = X1 * rhs.Y1 + Y1 * rhs.X1 - Z1 * rhs.W1 + W1 * rhs.Z1;
            ret.Z1 = X1 * rhs.Z1 + Y1 * rhs.W1 + Z1 * rhs.X1 - W1 * rhs.Y1;
            ret.W1 = X1 * rhs.W1 - Y1 * rhs.Z1 + Z1 * rhs.Y1 + W1 * rhs.X1;
            ret.X2 = X2 * rhs.X2 - Y2 * rhs.Y2 - Z2 * rhs.Z2 - W2 * rhs.W2;
            ret.Y2 = X2 * rhs.Y2 + Y2 * rhs.X2 - Z2 * rhs.W2 + W2 * rhs.Z2;
            ret.Z2 = X2 * rhs.Z2 + Y2 * rhs.W2 + Z2 * rhs.X2 - W2 * rhs.Y2;
            ret.W2 = X2 * rhs.W2 - Y2 * rhs.Z2 + Z2 * rhs.Y2 + W2 * rhs.X2;
            ret.X3 = X3 * rhs.X3 - Y3 * rhs.Y3 - Z3 * rhs.Z3 - W3 * rhs.W3;
            ret.Y3 = X3 * rhs.Y3 + Y3 * rhs.X3 - Z3 * rhs.W3 + W3 * rhs.Z3;
            ret.Z3 = X3 * rhs.Z3 + Y3 * rhs.W3 + Z3 * rhs.X3 - W3 * rhs.Y3;
            ret.W3 = X3 * rhs.W3 - Y3 * rhs.Z3 + Z3 * rhs.Y3 + W3 * rhs.X3;
            return ret;
        }
        auto operator/=(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 / rhs.X0 - Y0 / rhs.Y0 - Z0 / rhs.Z0 - W0 / rhs.W0;
            ret.Y0 = X0 / rhs.Y0 + Y0 / rhs.X0 - Z0 / rhs.W0 + W0 / rhs.Z0;
            ret.Z0 = X0 / rhs.Z0 + Y0 / rhs.W0 + Z0 / rhs.X0 - W0 / rhs.Y0;
            ret.W0 = X0 / rhs.W0 - Y0 / rhs.Z0 + Z0 / rhs.Y0 + W0 / rhs.X0;
            ret.X1 = X1 / rhs.X1 - Y1 / rhs.Y1 - Z1 / rhs.Z1 - W1 / rhs.W1;
            ret.Y1 = X1 / rhs.Y1 + Y1 / rhs.X1 - Z1 / rhs.W1 + W1 / rhs.Z1;
            ret.Z1 = X1 / rhs.Z1 + Y1 / rhs.W1 + Z1 / rhs.X1 - W1 / rhs.Y1;
            ret.W1 = X1 / rhs.W1 - Y1 / rhs.Z1 + Z1 / rhs.Y1 + W1 / rhs.X1;
            ret.X2 = X2 / rhs.X2 - Y2 / rhs.Y2 - Z2 / rhs.Z2 - W2 / rhs.W2;
            ret.Y2 = X2 / rhs.Y2 + Y2 / rhs.X2 - Z2 / rhs.W2 + W2 / rhs.Z2;
            ret.Z2 = X2 / rhs.Z2 + Y2 / rhs.W2 + Z2 / rhs.X2 - W2 / rhs.Y2;
            ret.W2 = X2 / rhs.W2 - Y2 / rhs.Z2 + Z2 / rhs.Y2 + W2 / rhs.X2;
            ret.X3 = X3 / rhs.X3 - Y3 / rhs.Y3 - Z3 / rhs.Z3 - W3 / rhs.W3;
            ret.Y3 = X3 / rhs.Y3 + Y3 / rhs.X3 - Z3 / rhs.W3 + W3 / rhs.Z3;
            ret.Z3 = X3 / rhs.Z3 + Y3 / rhs.W3 + Z3 / rhs.X3 - W3 / rhs.Y3;
            ret.W3 = X3 / rhs.W3 - Y3 / rhs.Z3 + Z3 / rhs.Y3 + W3 / rhs.X3;
            return ret;
        }
        auto operator+(f64 rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 += rhs;
            ret.Y0 += rhs;
            ret.Z0 += rhs;
            ret.W0 += rhs;
            ret.X1 += rhs;
            ret.Y1 += rhs;
            ret.Z1 += rhs;
            ret.W1 += rhs;
            ret.X2 += rhs;
            ret.Y2 += rhs;
            ret.Z2 += rhs;
            ret.W2 += rhs;
            ret.X3 += rhs;
            ret.Y3 += rhs;
            ret.Z3 += rhs;
            ret.W3 += rhs;
            return ret;
        }
        auto operator-(f64 rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 -= rhs;
            ret.Y0 -= rhs;
            ret.Z0 -= rhs;
            ret.W0 -= rhs;
            ret.X1 -= rhs;
            ret.Y1 -= rhs;
            ret.Z1 -= rhs;
            ret.W1 -= rhs;
            ret.X2 -= rhs;
            ret.Y2 -= rhs;
            ret.Z2 -= rhs;
            ret.W2 -= rhs;
            ret.X3 -= rhs;
            ret.Y3 -= rhs;
            ret.Z3 -= rhs;
            ret.W3 -= rhs;
            return ret;
        }
        auto operator*(f64 rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 * rhs;
            ret.Y0 = Y0 * rhs;
            ret.Z0 = Z0 * rhs;
            ret.W0 = W0 * rhs;
            ret.X1 = X1 * rhs;
            ret.Y1 = Y1 * rhs;
            ret.Z1 = Z1 * rhs;
            ret.W1 = W1 * rhs;
            ret.X2 = X2 * rhs;
            ret.Y2 = Y2 * rhs;
            ret.Z2 = Z2 * rhs;
            ret.W2 = W2 * rhs;
            ret.X3 = X3 * rhs;
            ret.Y3 = Y3 * rhs;
            ret.Z3 = Z3 * rhs;
            ret.W3 = W3 * rhs;
            return ret;
        }
        auto operator/(f64 rhs) const -> Quaternion
        {
            Quaternion ret = *this;
            ret.X0 = X0 / rhs;
            ret.Y0 = Y0 / rhs;
            ret.Z0 = Z0 / rhs;
            ret.W0 = W0 / rhs;
            ret.X1 = X1 / rhs;
            ret.Y1 = Y1 / rhs;
            ret.Z1 = Z1 / rhs;
            ret.W1 = W1 / rhs;
            ret.X2 = X2 / rhs;
            ret.Y2 = Y2 / rhs;
            ret.Z2 = Z2 / rhs;
            ret.W2 = W2 / rhs;
            ret.X3 = X3 / rhs;
            ret.Y3 = Y3 / rhs;
            ret.Z3 = Z3 / rhs;
            ret.W3 = W3 / rhs;
            return ret;
        }

        auto operator-() const noexcept -> Quaternion
        {
            Quaternion ret;
            ret.X0 = -X0;
            ret.Y0 = -Y0;
            ret.Z0 = -Z0;
            ret.W0 = -W0;
            return ret;
        }
        explicit operator f64*()
        {
            f64 ret[16] = { X0, Y0, Z0, W0, X1, Y1, Z1, W1, X2, Y2, Z2, W2, X3, Y3, Z3, W3 };
            f64* ptr = ret;
            return ptr;
        }

        explicit operator const f64*() const noexcept { return this->Data; }
        explicit operator string() const
        {
            string ret = "[";
            for (u32 i = 0; i < 16; i++)
            {
                ret += std::to_string(this->Data[i]);
                if (i < 15)
                {
                    ret += ", ";
                }
            }
            ret += "]";
            return ret;
        }

        auto operator==(const Quaternion& rhs) const -> bool
        {
            return std::equal(Data, Data + 16, rhs.Data);
        }

        auto operator!=(const Quaternion& rhs) const -> bool
        {
            return !(*this == rhs);
        }
    };
} // namespace Origin
#endif // GEOMETRY_HPP
