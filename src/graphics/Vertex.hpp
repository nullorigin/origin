#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "Geometry.hpp"
#include "Color.hpp"
namespace Origin
{
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
            Position(pos), Normal(norm), Col(col), Index(idx), Owners(own) {

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
            Position.X = mx.X > Position.X ? mx.X : Position.X;
            Position.X = mn.X < Position.X ? mn.X : Position.X;
            Position.Y = mx.Y > Position.Y ? mx.Y : Position.Y;
            Position.Y = mn.Y < Position.Y ? mn.Y : Position.Y;
            Position.Z = mx.Z > Position.Z ? mx.Z : Position.Z;
            Position.Z = mn.Z < Position.Z ? mn.Z : Position.Z;
            return *this;
        }
        auto clamp_color(const Color& mn, const Color& mx) -> Vertex
        {
            this->set_color(this->get_color().clamp(mn, mx));
            return *this;
        }
        auto clamp_normal(Vec3& mn, Vec3& mx) -> Vertex
        {
            Normal.X = mx.X > Normal.X ? mx.X : Normal.X;
            Normal.X = mn.X < Normal.X ? mn.X : Normal.X;
            Normal.Y = mx.Y > Normal.Y ? mx.Y : Normal.Y;
            Normal.Y = mn.Y < Normal.Y ? mn.Y : Normal.Y;
            Normal.Z = mx.Z > Normal.Z ? mx.Z : Normal.Z;
            Normal.Z = mn.Z < Normal.Z ? mn.Z : Normal.Z;
            return *this;
        }
        auto clamp_distance(const f64 mn, const f64 mx) -> Vertex
        {
            Position.X = mx > Position.X ? mx : Position.X;
            Position.X = mn < Position.X ? mn : Position.X;
            Position.Y = mx > Position.Y ? mx : Position.Y;
            Position.Y = mn < Position.Y ? mn : Position.Y;
            Position.Z = mx > Position.Z ? mx : Position.Z;
            Position.Z = mn < Position.Z ? mn : Position.Z;
            return *this;
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
        auto set(const Vec3& pos, const Vec3& norm, const Color& col) -> void
        {
            Position = pos;
            Normal = norm;
            Col = col;
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
            return Origin::sqrt(Position.X * Position.X + Position.Y * Position.Y + Position.Z * Position.Z);
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
            Position.X = Origin::sqrt(Position.X);
            Position.Y = Origin::sqrt(Position.Y);
            Position.Z = Origin::sqrt(Position.Z);
            Normal.X = Origin::sqrt(Normal.X);
            Normal.Y = Origin::sqrt(Normal.Y);
            Normal.Z = Origin::sqrt(Normal.Z);
            return *this;
        }

        auto normalize()
        {
            f64 const lengthsquared = Position.X * Position.X + Position.Y * Position.Y + Position.Z * Position.Z;
            if (lengthsquared > 0.0)
            {
                f64 const length = Origin::sqrt(lengthsquared);
                Position.X /= length;
                Position.Y /= length;
                Position.Z /= length;
                Normal.X /= length;
                Normal.Y /= length;
                Normal.Z /= length;
            }
            return *this;
        }
        Vertex& operator=(Vertex&& rhs) = default;
        Vertex& operator=(const Vertex& rhs) = default;
        auto operator*(const f64& rhs) const -> Vertex
        {
            Vertex ret = *this;
            Vec3 pos = this->Position;
            Vec3 norm = this->Normal;
            pos.X *= rhs;
            pos.Y *= rhs;
            pos.Z *= rhs;
            norm.X *= rhs;
            norm.Y *= rhs;
            norm.Z *= rhs;
            ret.Position = pos;
            ret.Normal = norm;
            return ret;
        }
        auto operator+(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.Position = (ret.Position + rhs.Position);
            ret.Normal = (ret.Normal + rhs.Normal);
            return ret;
        }
        auto operator-(const Vertex& rhs) const -> Vertex
        {
            Vertex ret = *this;
            ret.Position = (ret.Position - rhs.Position);
            ret.Normal = (ret.Normal - rhs.Normal);
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
} // namespace Origin
#endif