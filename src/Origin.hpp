#pragma once
#include "Basic.hpp"
#include "math/Geometry.hpp"
#include <algorithm>
#include <cstring>
#include <immintrin.h>

namespace origin
{

    using ID = u64;

    class Color : public Vec<f64, 4>
    {
    public:
        union
        {
            f64 data[4] = { 0, 0, 0, 0 };
            struct
            {
                f64 r;
                f64 g;
                f64 b;
                f64 a;
            };
        };
        Color(const f64 _r, const f64 _g, const f64 _b, const f64 _a)
        {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }
        Color() { r = 0, g = 0, b = 0, a = 0; }
        Color(Color&& /*unused*/) noexcept { r = 0, g = 0, b = 0, a = 0; };
        auto Scale() const -> f64 { return sqrt(r * r + g * g + b * b + a * a); }
        auto Normalize() -> Color&
        {
            f64 inv_length = 1.0 / sqrt(r * r + g * g + b * b + a * a);
            r *= inv_length;
            g *= inv_length;
            b *= inv_length;
            a *= inv_length;
            return *this;
        }
        ~Color() = default;
        auto operator=(Color&& other) noexcept -> Color&
        {
            data[0] = other.data[0];
            data[1] = other.data[1];
            data[2] = other.data[2];
            data[3] = other.data[3];
            return *this;
        }
        auto operator*(const f64& rhs) -> Color
        {
            return { r * rhs, g * rhs, b * rhs, a * rhs };
        }
        auto operator[](u64 index) -> f64& { return data[index]; }
    };
    class Vertex : public Vec<f64, 12>
    {
    private:
        union
        {
            f64 data[12]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            struct
            {
                f64 x;
                f64 y;
                f64 z;
                f64 w;
                f64 nx;
                f64 ny;
                f64 nz;
                f64 nw;
                f64 r;
                f64 g;
                f64 b;
                f64 a;
            };
        };
        u64 index{};
        ID* owners{};

    public:
        Vertex() = default;
        Vertex(Vertex&& /*unused*/) noexcept {};
        ~Vertex()
        {
            index = 0;
            owners = nullptr;
        }
        explicit Vertex(f64* data) { std::memcpy(data, data, 12 * sizeof(f64)); }
        Vertex(const Vec4& coords, const Vec4& normal, const Color& color) noexcept :
            x{ coords.x },
            y{ coords.y },
            z{ coords.z },
            w{ coords.w },
            nx{ normal.x },
            ny{ normal.y },
            nz{ normal.z },
            nw{ normal.w },
            r{ color.r },
            g{ color.g },
            b{ color.b },
            a{ color.a } {}
        Vertex(const f64 _x, const f64 _y, const f64 _z, const f64 _w, const f64 _nx, const f64 _ny, const f64 _nz, const f64 _nw, const f64 _r, const f64 _g, const f64 _b, const f64 _a, const u64 _index = 0, const ID* _owners = nullptr) noexcept :
            index(_index), owners(const_cast<ID*>(_owners))
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
            nx = _nx;
            ny = _ny;
            nz = _nz;
            nw = _nw;
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }
        Vertex(const Vec4& coords, const Vec4& normal, const Color& color, u32 _index = 0, ID* _owners = nullptr) noexcept :
            index(_index), owners(_owners)
        {
            *this = { coords.x, coords.y, coords.z, coords.w, normal.x, normal.y, normal.z, normal.w, color.r, color.g, color.b, color.a, _index, _owners };
        }
        Vertex(const Vertex& _rhs) noexcept
            :
            Vec(_rhs)
        {
            std::memcpy(this, &_rhs, sizeof(*this));
        }
        explicit Vertex(const Vertex* _rhs) noexcept
        {
            std::memcpy(this, _rhs, sizeof(*this));
        }
        auto ClampPosition(const Vec4& _min, const Vec4& _max) noexcept -> Vertex
        {
            Vertex ret = *this;
            ret.SetPosition(Vec4(this->GetPosition().Clamp(_min, _max)));
            return ret;
        }
        auto ClampColor(const Color& _min, const Color& _max) -> Vertex
        {
            Vertex ret = *this;
            Color color = this->GetColor();
            color.Clamp(_min, _max);
            ret.SetColor(color);
            return ret;
        }
        auto ClampNormal(const Vec4& _min, const Vec4& _max) noexcept -> Vertex
        {
            Vertex ret = *this;
            ret.SetNormal(Vec4(this->GetNormal().Clamp(_min, _max)));
            return ret;
        }
        auto ClampDistance(const f64 _min, const f64 _max) -> Vertex
        {
            f64 _distance = origin::Clamp(sqrt(x * x + y * y + z * z + w * w), _min, _max);
            Vec4 ret = Vec4(x / _distance, y / _distance, z / _distance, w / _distance);
            (Vertex(ret, Vec4(nx, ny, nz, nw), Color(r, g, b, a), index, owners));
        };

        auto Distance(const Vertex& rhs) const -> f64
        {
            return sqrt((x - rhs.x) * (x - rhs.x) +
                        (y - rhs.y) * (y - rhs.y) +
                        (z - rhs.z) * (z - rhs.z) +
                        (w - rhs.w) * (w - rhs.w));
        }
        auto DistanceSquared(const Vertex& rhs) const -> f64
        {
            return (x - rhs.x) * (x - rhs.x) +
                   (y - rhs.y) * (y - rhs.y) +
                   (z - rhs.z) * (z - rhs.z) +
                   (w - rhs.w) * (w - rhs.w);
        }
        static auto Distance(Vertex* _vertices) -> f64
        {
            f64 _dist = 0.0;
            Vertex* _verts = Sort(_vertices);
            u64 _size = sizeof(*_verts) / sizeof(_verts[0]); // size
            for (u64 i = 0; i < _size - 1; i++)
            {
                _dist += _verts[i].DistanceSquared(_verts[i + 1]);
            }
            return sqrt(_dist);
        }
        static auto Sort(Vertex* _vertices) -> Vertex*
        {
            u64 size = sizeof(*_vertices) / sizeof(_vertices[0]);
            Vertex ret = *_vertices;
            std::sort(_vertices, _vertices + size, [](const Vertex& lhs, const Vertex& rhs) -> bool {
                return lhs.index < rhs.index;
            });
            return _vertices;
        }
        auto SetData(f64* rhs) -> void { std::memcpy(data, rhs, 12 * sizeof(f64)); }
        auto SetPosition(const Vec4& rhs) -> void
        {
            std::memcpy(&data[0], &rhs, 4 * sizeof(f64));
        }
        auto SetNormal(const Vec4& rhs) -> void
        {
            std::memcpy(&data[4], &rhs, 4 * sizeof(f64));
        }
        auto SetColor(const Color& rhs) -> void
        {
            std::memcpy(&data[8], &rhs, 4 * sizeof(f64));
        }
        auto SetIndex(u32 _index) -> void { index = _index; }
        auto SetOwners(ID* _owners) -> void { owners = _owners; }
        auto GetData() -> f64* { return data; }
        auto GetLength() const -> f64
        {
            Vec4 ret = GetPosition();
            return sqrt(ret.x * ret.x + ret.y * ret.y + ret.z * ret.z + ret.w * ret.w);
        }
        auto GetPosition() const -> Vec4 { return Vec4(x, y, z, w); }
        auto GetNormal() const -> Vec4
        {
            return Vec4(nx, ny, nz, nw);
        }
        auto GetColor() const -> Color
        {
            return { r, g, b, a };
        }
        auto GetIndex() const -> u64 { return index; }
        auto GetOwners() const -> ID* { return owners; }
        auto GetPacked() const -> f64x4*
        {
            auto* ret = (new f64x4[3]);
            ret[0] = _mm256_loadu_pd(data);
            ret[1] = _mm256_loadu_pd(data + 4);
            ret[2] = _mm256_loadu_pd(data + 8);
            return ret;
        }
        auto GetPacked(u64 index) const -> f64x4
        {
            return _mm256_loadu_pd(data + index * 4);
        }
        auto SetPacked(f64x4* _packed) -> void
        {
            _mm256_storeu_pd(data, _packed[0]);
            _mm256_storeu_pd(data + 4, _packed[1]);
            _mm256_storeu_pd(data + 8, _packed[2]);
        }
        auto SetPacked(f64x4 _packed, u64 index) -> void
        {
            _mm256_storeu_pd(data + index * 4, _packed);
        }
        auto Sqrt() -> Vertex
        {
            Vertex ret = *this;
            f64x4 xmm0 = GetPacked(0);
            xmm0 = _mm256_sqrt_pd(xmm0);
            _mm256_storeu_pd(ret.data, xmm0);
            return ret;
        }
        auto Length() const -> f64
        {
            f64x4 xmm0 = GetPacked(0);
            xmm0 = _mm256_sqrt_pd(xmm0);
            return _mm256_cvtsd_f64(xmm0);
        }

        auto Normalize() -> Vertex&
        {
            f64x4 xmm0 = GetPacked(0);
            f64x4 xmm1 = _mm256_sqrt_pd(xmm0);
            xmm0 = _mm256_div_pd(xmm0, xmm1);
            SetPacked(xmm0, 0);
            return *this;
        }
        auto operator==(const Vertex& rhs) const -> bool
        {
            return (std::memcmp(data, rhs.data, 12 * sizeof(f64)) == 0) && (index == rhs.index) && (owners == rhs.owners);
        }
        auto operator!=(const Vertex& rhs) const -> bool
        {
            return !(*this == rhs);
        }

        explicit operator f64*()
        {
            return GetData();
        }
        auto operator=(const Vertex&& rhs) noexcept -> Vertex&
        {
            std::memcpy(this, &rhs, sizeof(Vertex));
            return *this;
        }
        auto operator*(const f64& rhs) const -> Vertex
        {
            Vertex ret = *this;
            const f64x4 result = _mm256_mul_pd(_mm256_loadu_pd(data), _mm256_set1_pd(rhs));
            _mm256_storeu_pd(ret.GetData(), result);
            return ret;
        }
        auto operator+(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.SetPacked(_mm256_add_pd(GetPacked(0), rhs.GetPacked(0)), 0);
            return ret;
        }
        auto operator-(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.SetPacked(_mm256_sub_pd(GetPacked(0), rhs.GetPacked(0)), 0);
            return ret;
        }
        auto operator+=(const Vertex& rhs) -> Vertex&
        {
            *this = *this + rhs;
            return *this;
        }
        auto operator-=(const Vertex& rhs) -> Vertex&
        {
            *this = *this - rhs;
            return *this;
        }
        auto operator[](u64 _index) -> f64& { return data[_index]; }
        auto operator[](u64 _index) const -> f64 { return data[_index]; }
    };
    class Triangle : public Vec<Vertex, 3>
    {
        u32 index{};
        union
        {
            Vertex data[3] = { Vertex(), Vertex(), Vertex() };
            struct
            {
                Vertex* a;
                Vertex* b;
                Vertex* c;
            };
        };

    public:
        Triangle() = default;
        Triangle(Vertex* _a, Vertex* _b, Vertex* _c)
        {
            a = _a;
            b = _b;
            c = _c;
        }
        ~Triangle() = default;
        auto Get() -> Vertex* { return data; }
        auto Get(u32 _index) -> Vertex& { return data[_index]; }
    };
    template<u64 N>
    class Mesh : public Vec<Triangle, N>
    {
        u32 index{};
        union
        {
            Triangle data[N] = new Triangle*[N];
            struct
            {
                Vertex* a;
                Vertex* b;
                Vertex* c;
            };
        };

    public:
        Triangle* Get() { return this->data; }
        auto Get() const -> const Triangle* { return this->data; }
        Mesh<N>() :
            Vec<Triangle, N>()
        {
            for (u64 i = 0; i < N; i++)
            {
                this->data[i] = (Vertex(), Vertex(), Vertex());
            }
        }
        ~Mesh<N>() { delete[] this->data; }

        auto operator*() { return this->data; }
        auto operator[](const u64 _index[2]) -> Vertex
        {
            Vertex _vertex = this->data[_index[0]][_index[1]];
            return _vertex;
        }
        auto operator[](u64 _index) -> Triangle& { return this->data[_index]; }
        auto operator[](u64 _index) const -> const Triangle& { return this->data[_index]; }
    };
} // namespace origin