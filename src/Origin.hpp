#ifndef ORIGIN_HPP
#define ORIGIN_HPP

#pragma once
#include "Basic.hpp"
#include "math/Basic.hpp"
#include "math/Geometry.hpp"
#include <immintrin.h>
#include <cstddef>
#include <utility>

namespace Origin
{

    using ID = u64;
    struct Color
    {
    public:
        f64 R;
        f64 G;
        f64 B;
        f64 A;
        Color(const f64 r, const f64 g, const f64 b, const f64 a) noexcept :
            R(r), G(g), B(b), A(a) {}
        Color()
        {
            R = 0, G = 0, B = 0, A = 0;
        }
        Color(const Color& /*unused*/) = default;
        Color(Color&& /*unused*/) = default;
        ~Color() = default;
        [[nodiscard]] auto scale() const -> f64 { return sqrt(R * R + G * G + B * B + A * A); }
        auto normalize() -> Color&
        {
            f64 const inv_length = 1.0 / sqrt(R * R + G * G + B * B + A * A);
            R *= inv_length;
            G *= inv_length;
            B *= inv_length;
            A *= inv_length;
            return *this;
        }
        auto clamp(const Color& mn, const Color& mx) -> Color
        {
            Color ret = *this;
            ret.R = mx.R > ret.R ? mx.R : ret.R;
            ret.G = mx.G > ret.G ? mx.G : ret.G;
            ret.B = mx.B > ret.B ? mx.B : ret.B;
            ret.A = mx.A > ret.A ? mx.A : ret.A;
            ret.R = mn.R < ret.R ? mn.R : ret.R;
            ret.G = mn.G < ret.G ? mn.G : ret.G;
            ret.B = mn.B < ret.B ? mn.B : ret.B;
            ret.A = mn.A < ret.A ? mn.A : ret.A;
            return ret;
        }
        auto operator=(Color&& other) noexcept -> Color&
        {
            R = other.R;
            G = other.G;
            B = other.B;
            A = other.A;
            return *this;
        }
        auto operator=(const Color& other) noexcept -> Color&
        {
            R = other.R;
            G = other.G;
            B = other.B;
            A = other.A;
            return *this;
        }
        auto operator+(const Color& rhs) const -> Color
        {
            return { R + rhs.R, G + rhs.G, B + rhs.B, A + rhs.A };
        }
        auto operator-(const Color& rhs) const -> Color
        {
            return { R - rhs.R, G - rhs.G, B - rhs.B, A - rhs.A };
        }
        auto operator*(const Color& rhs) const -> Color
        {
            return { R * rhs.R, G * rhs.G, B * rhs.B, A * rhs.A };
        }
        auto operator/(const Color& rhs) const -> Color { return { R / rhs.R, G / rhs.G, B / rhs.B, A / rhs.A }; }
    } __attribute__((aligned(32)));
    struct VertexData
    {
        friend class Vertex;

    private:
    } __attribute__((aligned(128)));
    class Vertex
    {
    private:
        Vec3 Position;
        Vec3 Normal;
        Color Col;
        u64 Index{ 0 };
        ID* Owners{ nullptr };

    public:
        Vertex() :
            Col(Color(0, 0, 0, 0))
        {
            Position = Vec3(0, 0, 0);
            Normal = Vec3(0, 0, 0);
        }
        Vertex(Vec3 pos, Vec3 norm, Color col, u64 idx, ID* own) :
            Position(std::move(pos)), Normal(std::move(norm)), Col(col), Index(idx), Owners(own) {

            };
        ~Vertex()
        {
            Position = Vec3(0, 0, 0);
            Normal = Vec3(0, 0, 0);
            Col = Color(0, 0, 0, 0);
            Index = 0;
            Owners = nullptr;
        }
        Vertex(const Vec3& coords, const Vec3& norm, const Color& col, u32 idx = 0, ID* own = nullptr) :
            Index(idx), Owners(own)
        {
            set_position(coords);
            set_normal(norm);
            set_color(col);
        }
        Vertex(const Vertex& rhs) noexcept = default;
        Vertex(Vertex&& rhs) noexcept = default;
        auto clamp_position(Vec3& mn, Vec3& mx) noexcept -> Vertex
        {
            Vertex ret = *this;
            Vec3 const pos = this->get_position();
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = mx[i] > pos[i] ? mx[i] : pos[i];
                pos[i] = mn[i] < pos[i] ? mn[i] : pos[i];
            }
            ret.set_position(pos);
            return ret;
        }
        auto clamp_color(const Color& mn, const Color& mx) -> Vertex
        {
            Vertex ret = *this;
            ret.set_color(this->get_color().clamp(mn, mx));
            return ret;
        }
        auto clamp_normal(Vec3& mn, Vec3& mx) const -> Vertex
        {
            Vertex ret = *this;
            Vec3 const norm = this->get_normal();
            for (u64 i = 0; i < 3; i++)
            {
                norm[i] = mx[i] > norm[i] ? mx[i] : norm[i];
                norm[i] = mn[i] < norm[i] ? mn[i] : norm[i];
            }
            ret.set_normal(norm);
            return ret;
        }
        auto clamp_distance(const f64 mn, const f64 mx) -> Vertex
        {
            Vertex ret = *this;
            Vec3 const pos = this->get_position();
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = mx > pos[i] ? mx : pos[i];
                pos[i] = mn < pos[i] ? mn : pos[i];
            }
            ret.set_position(pos);
            return ret;
        };

        [[nodiscard]] auto get_distance(const Vertex& rhs) const -> f64
        {
            Vertex const ret = *this;
            Vec3 const dist = ret.get_position() - rhs.get_position();
            return Origin::sqrt(dist.X * dist.X + dist.Y * dist.Y + dist.Z * dist.Z);
        }
        [[nodiscard]] auto get_distance_squared(const Vertex& rhs) const -> f64
        {
            Vertex const ret = *this;
            Vec3 const dist = ret.get_position() - rhs.get_position();
            return dist.X * dist.X + dist.Y * dist.Y + dist.Z * dist.Z;
        }
        static auto get_distance(Vertex* rhs) -> f64
        {
            f64 dist = 0.0;
            u64 const size = sizeof(*rhs) / sizeof(rhs[0]); // size
            for (u64 i = 0; i < size - 1; i++)
            {
                dist += rhs[i].get_distance(rhs[i + 1]);
            }
            return dist;
        }
        static auto sort(Vertex* rhs) -> Vertex*
        {
            u64 const size = sizeof(*rhs) / sizeof(rhs[0]);
            u64* idx = (new u64[size]);
            for (u64 i = 0; i < size; i++)
            {
                if (rhs[i].Index > idx[i])
                {
                    idx[i] = rhs[i].Index;
                }
            }
            auto* ret = (new Vertex[size]);
            for (u64 i = 0; i < size; i++)
            {
                ret[i] = Vertex(rhs[idx[i]]);
            }
            delete[] idx;
            idx = nullptr;
            return ret;
        }
        auto set(const Vec3& rhs, const Vec3& norm, const Color& col) -> void
        {
            set_position(rhs);
            set_normal(norm);
            set_color(col);
        }
        auto set_position(const Vec3& rhs) -> void
        {
            this->Position = rhs;
        }
        auto set_normal(const Vec3& rhs) -> void
        {
            this->Normal = rhs;
        }
        auto set_color(const Color& rhs) -> void
        {
            this->Col = rhs;
        }
        auto set_index(u32 idx) -> void { Index = idx; }
        auto set_owners(ID* own) -> void { Owners = own; }
        [[nodiscard]] auto get_length() const -> f64
        {
            Vec3 const ret = get_position();
            return Origin::sqrt(ret.X * ret.X + ret.Y * ret.Y + ret.Z * ret.Z);
        }
        [[nodiscard]] auto get_position() const -> Vec3 { return this->Position; }
        [[nodiscard]] auto get_normal() const -> Vec3
        {
            return this->Normal;
        }
        [[nodiscard]] auto get_color() const -> Color
        {
            return this->Col;
        }
        [[nodiscard]] auto get_index() const -> u64 { return Index; }
        [[nodiscard]] auto get_owners() const -> ID* { return Owners; }
        auto sqrt()
        {
            Vertex ret = *this;
            Vec3 const pos = this->Position;
            Vec3 const norm = this->Normal;
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = Origin::sqrt(pos[i]);
                norm[i] = Origin::sqrt(norm[i]);
            }
            ret.set_position(pos);
            ret.set_normal(norm);
            return ret;
        }

        auto normalize()
        {
            Vertex* ret = this;
            Vec3 const pos = this->Position;
            Vec3 const norm = this->Normal;
            f64 const lengthsquared = pos.X * pos.X + pos.Y * pos.Y + pos.Z * pos.Z;
            if (lengthsquared > 0.0)
            {
                f64 const length = Origin::sqrt(lengthsquared);
                for (u64 i = 0; i < 3; i++)
                {
                    pos[i] /= length;
                    norm[i] /= length;
                }
            }
            ret->set_position(pos);
            ret->set_normal(norm);
            return *ret;
        }
        Vertex& operator=(Vertex&& rhs) = default;
        Vertex& operator=(const Vertex& rhs) = default;
        auto operator*(const f64& rhs) const -> Vertex
        {
            Vertex ret = *this;
            Vec3 const pos = this->Position;
            Vec3 const norm = this->Normal;
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] *= rhs;
                norm[i] *= rhs;
            }
            ret.set_position(pos);
            ret.set_normal(norm);
            return ret;
        }
        auto operator+(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.set_position(ret.Position + rhs.Position);
            ret.set_normal(ret.Normal + rhs.Normal);
            return ret;
        }
        auto operator-(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.set_position(ret.Position - rhs.Position);
            ret.set_normal(ret.Normal - rhs.Normal);
            return ret;
        }
        auto operator+=(const Vertex& rhs) -> Vertex&
        {
            return *this = *this + rhs;
        }
        auto operator-=(const Vertex& rhs) -> Vertex&
        {
            return *this = *this - rhs;
        }
    };
    class Triangle
    {
    public:
        union
        {
            Vertex* Data = new Vertex[3]();
            struct
            {
                Vertex A;
                Vertex B;
                Vertex C;
            } __attribute__((aligned(32)));
        };
        Triangle() = default;
        Triangle(const Vertex& a, const Vertex& b, const Vertex& c)
        {
            A = a;
            B = b;
            C = c;
        }
        ~Triangle() = delete;
        auto get() const -> Vertex* { return this->Data; }
        auto get(u32 idx) const -> Vertex& { return Data[idx]; }
    };
} // namespace Origin
#endif // ORIGIN_HPP
