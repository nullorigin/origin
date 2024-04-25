#pragma once
#include "Basic.hpp"
#include "math/Geometry.hpp"
#include <algorithm>
#include <cstring>
#include <immintrin.h>

namespace origin
{

    using ID = u64;
    struct ColorData
    {
        ColorData() { R = 0, G = 0, B = 0, A = 0; }
        ColorData(const f64 _r, const f64 _g, const f64 _b, const f64 _a) :
            R(_r), G(_g), B(_b), A(_a)
        {
            data[0] = _r;
            data[1] = _g;
            data[2] = _b;
            data[3] = _a;
        }
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
    };
    class Color : public ColorData
    {
    public:
        Color(const f64 _r, const f64 _g, const f64 _b, const f64 _a) noexcept :
            ColorData(_r, _g, _b, _a) {}
        Color()
        {
            R = 0, G = 0, B = 0, A = 0;
        }
        Color(const Color& /*unused*/) = default;
        auto Scale() const -> f64 { return sqrt(R * R + G * G + B * B + A * A); }
        auto Normalize() -> Color&
        {
            f64 inv_length = 1.0 / sqrt(R * R + G * G + B * B + A * A);
            R *= inv_length;
            G *= inv_length;
            B *= inv_length;
            A *= inv_length;
            return *this;
        }
        auto Clamp(const Color& _min, const Color& _max) -> Color
        {
            Color ret = *this;
            for (u64 i = 0; i < 4; i++)
            {
                ret.data[i] = _max.data[i] > ret.data[i] ? _max.data[i] : ret.data[i];
                ret.data[i] = _min.data[i] < ret.data[i] ? _min.data[i] : ret.data[i];
            }
            return ret;
        }
        ~Color() = default;
        auto operator=(Color other) noexcept -> Color&
        {
            this->R = other.R;
            this->G = other.G;
            this->B = other.B;
            this->A = other.A;
        }
        auto operator*(const f64& rhs) const -> Color
        {
            return { R * rhs, G * rhs, B * rhs, A * rhs };
        }
        auto operator[](u64 index) -> f64& { return data[index]; }
    };
    struct VertexData
    {
    public:
        Vec4f position;
        Vec4f normal;
        Color color;
        u64 index;
        ID* owners;
        VertexData()
        {
            position = Vec4f(0, 0, 0, 0);
            normal = Vec4f(0, 0, 0, 0);
            color = Color(0, 0, 0, 0);
            index = 0;
            owners = nullptr;
        }
        VertexData(Vec4f _position, Vec4f _normal, Color _color, u64 _index, ID* _owners)
        {
            position = _position;
            normal = _normal;
            color = _color;
            index = _index;
            owners = _owners;
        };

    } __attribute__((aligned(128)));
    class Vertex : public VertexData
    {
    public:
        Vertex()

        {
            position = Vec4f(0, 0, 0, 0);
            normal = Vec4f(0, 0, 0, 0);
            color = Color(0, 0, 0, 0);
            index = 0;
            owners = nullptr;
        }
        ~Vertex()
        {
            position = Vec4f(0, 0, 0, 0);
            normal = Vec4f(0, 0, 0, 0);
            color = Color(0, 0, 0, 0);
            index = 0;
            owners = nullptr;
        }
        Vertex(const Vec4f& coords, const Vec4f& normal, const Color& color, u32 _index = 0, ID* _owners = nullptr)
        {
            SetPosition(coords);
            SetNormal(normal);
            SetColor(color);
            index = _index;
            owners = _owners;
        }
        Vertex(const Vertex& _rhs) noexcept
        {
            this->position = _rhs.position;
            this->normal = _rhs.normal;
            this->color = _rhs.color;
            this->index = _rhs.index;
            this->owners = _rhs.owners;
        }
        explicit Vertex(const Vertex* _rhs) noexcept
        {
            this->position = _rhs->position;
            this->normal = _rhs->normal;
            this->color = _rhs->color;
            this->index = _rhs->index;
            this->owners = _rhs->owners;
        }
        auto ClampPosition(const Vec4f& _min, const Vec4f& _max) noexcept -> Vertex
        {
            Vertex ret = *this;
            Vec4f pos = this->GetPosition();
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = _max[i] > pos[i] ? _max[i] : pos[i];
                pos[i] = _min[i] < pos[i] ? _min[i] : pos[i];
            }
            ret.SetPosition(pos);
            return ret;
        }
        auto ClampColor(const Color& _min, const Color& _max) -> Vertex
        {
            Vertex ret = *this;
            ret.SetColor(this->GetColor().Clamp(_min, _max));
            return ret;
        }
        auto ClampNormal(const Vec4f& _min, const Vec4f& _max) noexcept -> Vertex
        {
            Vertex ret = *this;
            Vec4f norm = this->GetNormal();
            for (u64 i = 0; i < 3; i++)
            {
                norm[i] = _max[i] > norm[i] ? _max[i] : norm[i];
                norm[i] = _min[i] < norm[i] ? _min[i] : norm[i];
            }
            ret.SetNormal(norm);
            return ret;
        }
        auto ClampDistance(const f64 _min, const f64 _max) -> Vertex
        {
            Vertex ret = *this;
            Vec4f pos = this->GetPosition();
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = _max > pos[i] ? _max : pos[i];
                pos[i] = _min < pos[i] ? _min : pos[i];
            }
            ret.SetPosition(pos);
            return ret;
        };

        auto GetDistance(const Vertex& rhs) const -> f64
        {
            Vertex ret = *this;
            Vec4f dist = ret.GetPosition() - rhs.GetPosition();
            return sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z + dist.w * dist.w);
        }
        auto GetDistanceSquared(const Vertex& rhs) const -> f64
        {
            Vertex ret = *this;
            Vec4f dist = ret.GetPosition() - rhs.GetPosition();
            return dist.x * dist.x + dist.y * dist.y + dist.z * dist.z + dist.w * dist.w;
        }
        static auto GetDistance(Vertex* rhs) -> f64
        {
            f64 dist = 0.0;
            u64 size = sizeof(*rhs) / sizeof(rhs[0]); // size
            for (u64 i = 0; i < size - 1; i++)
            {
                dist += rhs[i].GetDistance(rhs[i + 1]);
            }
            return dist;
        }
        auto Sort(Vertex* rhs) -> Vertex*
        {
            u64 size = sizeof(*rhs) / sizeof(rhs[0]);
            u64* idx = (new u64[size]);
            for (u64 i = 0; i < size; i++)
            {
                if (rhs[i].index > idx[i])
                {
                    idx[i] = rhs[i].index;
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
        auto Set(const Vec4f& _rhs, const Vec4f& _normal, const Color& _color) -> void
        {
            SetPosition(_rhs);
            SetNormal(_normal);
            SetColor(_color);
        }
        auto SetPosition(const Vec4f& rhs) -> void
        {
            this->position = rhs;
        }
        auto SetNormal(const Vec4f& rhs) -> void
        {
            this->normal = rhs;
        }
        auto SetColor(const Color& rhs) -> void
        {
            this->color = rhs;
        }
        auto SetIndex(u32 _index) -> void { index = _index; }
        auto SetOwners(ID* _owners) -> void { owners = _owners; }
        auto GetLength() const -> f64
        {
            Vec4f ret = GetPosition();
            return sqrt(ret.x * ret.x + ret.y * ret.y + ret.z * ret.z + ret.w * ret.w);
        }
        auto GetPosition() const -> Vec4f { return this->position; }
        auto GetNormal() const -> Vec4f
        {
            return this->normal;
        }
        auto GetColor() const -> Color
        {
            return this->color;
        }
        auto GetIndex() const -> u64 { return index; }
        auto GetOwners() const -> ID* { return owners; }
        auto Sqrt() -> Vertex
        {
            Vertex ret = *this;
            Vec4f pos = this->position;
            Vec4f norm = this->normal;
            for (u64 i = 0; i < 3; i++)
            {
                pos[i] = sqrt(pos[i]);
                norm[i] = sqrt(norm[i]);
            }
            ret.SetPosition(pos);
            ret.SetNormal(norm);
            return ret;
        }

        auto Normalize() -> Vertex&
        {
            Vertex ret = *this;
            Vec4f pos = this->position;
            Vec4f norm = this->normal;
            f64 lengthsquared = pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + pos.w * pos.w;
            if (lengthsquared > 0.0)
            {
                f64 length = sqrt(lengthsquared);
                for (u64 i = 0; i < 3; i++)
                {
                    pos[i] /= length;
                    norm[i] /= length;
                }
            }
            ret.SetPosition(pos);
            ret.SetNormal(norm);
            return ret;
        }
        auto operator==(const Vertex& rhs) const -> bool
        {
            return (std::memcmp(this, &rhs, sizeof(Vertex)) == 0);
        }
        auto operator!=(const Vertex& rhs) const -> bool
        {
            return !(*this == rhs);
        }
        auto operator=(const Vertex&& rhs) noexcept -> Vertex&
        {
            std::memcpy(this, &rhs, sizeof(Vertex));
            return *this;
        }
        auto operator*(const f64& rhs) const -> Vertex
        {
            Vertex ret = *this;
            Vec4f pos = this->position;
            Vec4f norm = this->normal;
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
            ret.SetPosition(ret.position + rhs.position);
            ret.SetNormal(ret.normal + rhs.normal);
            return ret;
        }
        auto operator-(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.SetPosition(ret.position - rhs.position);
            ret.SetNormal(ret.normal - rhs.normal);
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
    class Triangle : public Vec<Vertex, 3>
    {
        u32 Index{};
        union
        {
            Vertex Data[3] = { Vertex(), Vertex(), Vertex() };
            struct
            {
                Vertex* A;
                Vertex* B;
                Vertex* C;
            } __attribute__((aligned(32)));
        };

    public:
        Triangle() = default;
        Triangle(Vertex* _a, Vertex* _b, Vertex* _c)
        {
            A = _a;
            B = _b;
            C = _c;
        }
        ~Triangle() = delete;
        auto Get() -> Vertex* { return Data; }
        auto Get(u32 _index) -> Vertex& { return Data[_index]; }
    };
    template<u64 N>
    class Mesh : public Vec<Triangle, N>
    {
        u32 Index{};
        union
        {
            Triangle Data[N] = new Triangle*[N];
            struct
            {
                Vertex* A;
                Vertex* B;
                Vertex* C;
            };
        };

    public:
        Triangle* Get() { return this->Data; }
        auto Get() const -> const Triangle* { return this->Data; }
        Mesh<N>() :
            Vec<Triangle, N>()
        {
            for (u64 i = 0; i < N; i++)
            {
                this->Data[i] = (Vertex(), Vertex(), Vertex());
            }
        }
        ~Mesh<N>() { delete[] this->Data; }

        auto operator*() { return this->Data; }
        auto operator[](const u64 _index[2]) -> Vertex
        {
            Vertex vertex = this->Data[_index[0]][_index[1]];
            return vertex;
        }
        auto operator[](u64 _index) -> Triangle& { return this->Data[_index]; }
        auto operator[](u64 _index) const -> const Triangle& { return this->Data[_index]; }
    };
} // namespace origin