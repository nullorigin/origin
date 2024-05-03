#ifndef HOME_MATT_ORIGIN_SRC_ORIGIN_HPP
#define HOME_MATT_ORIGIN_SRC_ORIGIN_HPP

#include <algorithm>
#include <functional>
#include <utility>
#pragma once
#include "Basic.hpp"
#include "math/Basic.hpp"
#include "math/Geometry.hpp"
#include <immintrin.h>

namespace Origin
{

    using ID = u64;
    struct ColorData
    {
    public:
        friend class Color;
        union
        {
            f64* data = new f64[4];
            struct
            {
                f64 R;
                f64 G;
                f64 B;
                f64 A;
            } __attribute__((aligned(32)));
        } __attribute__((aligned(16)));

        ColorData() { R = 0, G = 0, B = 0, A = 0; }
        ColorData(const f64 r, const f64 g, const f64 b, const f64 a) :
            R(r), G(g), B(b), A(a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
    };
    class Color : public ColorData
    {
    public:
        friend struct ColorData;
        Color(const f64 r, const f64 g, const f64 b, const f64 a) noexcept :
            ColorData(r, g, b, a) {}
        Color()
        {
            R = 0, G = 0, B = 0, A = 0;
        }
        Color(const Color& /*unused*/) = default;
        Color(Color&& /*unused*/) = default;

        [[nodiscard]] auto Scale() const -> f64 { return sqrt(R * R + G * G + B * B + A * A); }
        auto Normalize() -> Color&
        {
            f64 const inv_length = 1.0 / sqrt(R * R + G * G + B * B + A * A);
            R *= inv_length;
            G *= inv_length;
            B *= inv_length;
            A *= inv_length;
            return *this;
        }
        auto Clamp(const Color& mn, const Color& mx) -> Color
        {
            Color ret = *this;
            for (u64 i = 0; i < 4; i++)
            {
                ret.data[i] = mx.data[i] > ret.data[i] ? mx.data[i] : ret.data[i];
                ret.data[i] = mn.data[i] < ret.data[i] ? mn.data[i] : ret.data[i];
            }
            return ret;
        }
        ~Color() = default;
        auto operator=(Color&&) -> Color& = default;
        auto operator=(const Color&) -> Color& = default;
        auto operator=(ColorData other) noexcept -> Color&
        {
            this->R = other.R;
            this->G = other.G;
            this->B = other.B;
            this->A = other.A;
            return *this;
        }
        auto operator*(const f64& rhs) const -> Color
        {
            return { R * rhs, G * rhs, B * rhs, A * rhs };
        }
        auto operator[](u64 index) -> f64& { return data[index]; }
    };
    struct VertexData
    {
        friend class Vertex;

    private:
        Vec3 Position;
        Vec3 Normal;
        Color Col;
        u64 Index{ 0 };
        ID* Owners{ nullptr };

    public:
        VertexData() :
            Col(Color(0, 0, 0, 0))
        {
            Position = Vec3(0, 0, 0);
            Normal = Vec3(0, 0, 0);
        }
        VertexData(Vec3 pos, Vec3 norm, Color col, u64 idx, ID* own) :
            Position(std::move(pos)), Normal(std::move(norm)), Col(col), Index(idx), Owners(own) {

            };

    } __attribute__((aligned(128)));
    class Vertex : public VertexData
    {
    public:
        friend struct VertexData;
        Vertex() = default;
        ~Vertex()
        {
            Position = Vec3(0, 0, 0);
            Normal = Vec3(0, 0, 0);
            Col = Color(0, 0, 0, 0);
            Index = 0;
            Owners = nullptr;
        }
        Vertex(const Vec3& coords, const Vec3& norm, const Color& col, u32 idx = 0, ID* own = nullptr)
        {
            SetPosition(coords);
            SetNormal(norm);
            SetColor(col);
            Index = idx;
            Owners = own;
        }
        Vertex(const Vertex& rhs) noexcept
            :
            VertexData(rhs)
        {
            this->Position = rhs.Position;
            this->Normal = rhs.Normal;
            this->Col = rhs.Col;
            this->Index = rhs.Index;
            this->Owners = rhs.Owners;
        }
        explicit Vertex(const VertexData&& rhs) noexcept
        {
            this->Position = rhs.Position;
            this->Normal = rhs.Normal;
            this->Col = rhs.Col;
            this->Index = rhs.Index;
            this->Owners = rhs.Owners;
        }
        auto ClampPosition(Vec3& mn, Vec3& mx) noexcept -> Vertex
        {
            Vertex ret = *this;
            Vec3 const pos = this->GetPosition();
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = mx[i] > pos[i] ? mx[i] : pos[i];
                pos[i] = mn[i] < pos[i] ? mn[i] : pos[i];
            }
            ret.SetPosition(pos);
            return ret;
        }
        auto ClampColor(const Color& mn, const Color& mx) -> Vertex
        {
            Vertex ret = *this;
            ret.SetColor(this->GetColor().Clamp(mn, mx));
            return ret;
        }
        auto ClampNormal(Vec3& mn, Vec3& mx) const -> Vertex
        {
            Vertex ret = *this;
            Vec3 const norm = this->GetNormal();
            for (u64 i = 0; i < 3; i++)
            {
                norm[i] = mx[i] > norm[i] ? mx[i] : norm[i];
                norm[i] = mn[i] < norm[i] ? mn[i] : norm[i];
            }
            ret.SetNormal(norm);
            return ret;
        }
        auto ClampDistance(const f64 mn, const f64 mx) -> Vertex
        {
            Vertex ret = *this;
            Vec3 const pos = this->GetPosition();
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = mx > pos[i] ? mx : pos[i];
                pos[i] = mn < pos[i] ? mn : pos[i];
            }
            ret.SetPosition(pos);
            return ret;
        };

        [[nodiscard]] auto GetDistance(const Vertex& rhs) const -> f64
        {
            Vertex const ret = *this;
            Vec3 const dist = ret.GetPosition() - rhs.GetPosition();
            return sqrt(dist.X * dist.X + dist.Y * dist.Y + dist.Z * dist.Z);
        }
        [[nodiscard]] auto GetDistanceSquared(const Vertex& rhs) const -> f64
        {
            Vertex const ret = *this;
            Vec3 const dist = ret.GetPosition() - rhs.GetPosition();
            return dist.X * dist.X + dist.Y * dist.Y + dist.Z * dist.Z;
        }
        static auto GetDistance(Vertex* rhs) -> f64
        {
            f64 dist = 0.0;
            u64 const size = sizeof(*rhs) / sizeof(rhs[0]); // size
            for (u64 i = 0; i < size - 1; i++)
            {
                dist += rhs[i].GetDistance(rhs[i + 1]);
            }
            return dist;
        }
        static auto Sort(Vertex* rhs) -> Vertex*
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
        auto Set(const Vec3& rhs, const Vec3& norm, const Color& col) -> void
        {
            SetPosition(rhs);
            SetNormal(norm);
            SetColor(col);
        }
        auto SetPosition(const Vec3& rhs) -> void
        {
            this->Position = rhs;
        }
        auto SetNormal(const Vec3& rhs) -> void
        {
            this->Normal = rhs;
        }
        auto SetColor(const Color& rhs) -> void
        {
            this->Col = rhs;
        }
        auto SetIndex(u32 idx) -> void { Index = idx; }
        auto SetOwners(ID* own) -> void { Owners = own; }
        [[nodiscard]] auto GetLength() const -> f64
        {
            Vec3 const ret = GetPosition();
            return sqrt(ret.X * ret.X + ret.Y * ret.Y + ret.Z * ret.Z);
        }
        [[nodiscard]] auto GetPosition() const -> Vec3 { return this->Position; }
        [[nodiscard]] auto GetNormal() const -> Vec3
        {
            return this->Normal;
        }
        [[nodiscard]] auto GetColor() const -> Color
        {
            return this->Col;
        }
        [[nodiscard]] auto GetIndex() const -> u64 { return Index; }
        [[nodiscard]] auto GetOwners() const -> ID* { return Owners; }
        auto Sqrt()
        {
            Vertex ret = *this;
            Vec3 const pos = this->Position;
            Vec3 const norm = this->Normal;
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = sqrt(pos[i]);
                norm[i] = sqrt(norm[i]);
            }
            ret.SetPosition(pos);
            ret.SetNormal(norm);
            return ret;
        }

        auto Normalize()
        {
            Vertex* ret = this;
            Vec3 const pos = this->Position;
            Vec3 const norm = this->Normal;
            f64 const lengthsquared = pos.X * pos.X + pos.Y * pos.Y + pos.Z * pos.Z;
            if (lengthsquared > 0.0)
            {
                f64 const length = sqrt(lengthsquared);
                for (u64 i = 0; i < 3; i++)
                {
                    pos[i] /= length;
                    norm[i] /= length;
                }
            }
            ret->SetPosition(pos);
            ret->SetNormal(norm);
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
            ret.SetPosition(pos);
            ret.SetNormal(norm);
            return ret;
        }
        auto operator+(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.SetPosition(ret.Position + rhs.Position);
            ret.SetNormal(ret.Normal + rhs.Normal);
            return ret;
        }
        auto operator-(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.SetPosition(ret.Position - rhs.Position);
            ret.SetNormal(ret.Normal - rhs.Normal);
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
            Vertex* data = new Vertex[3]();
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
        auto Get() const -> Vertex* { return this->data; }
        auto Get(u32 idx) const -> Vertex& { return data[idx]; }
    };
} // namespace Origin
#endif
