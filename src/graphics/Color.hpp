#ifndef COLOR_HPP
#define COLOR_HPP
#include "Basic.hpp"
namespace origin
{
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
        auto operator=(Color&& in) noexcept -> Color&
        {
            R = in.R;
            G = in.G;
            B = in.B;
            A = in.A;
            return *this;
        }
        auto operator=(const Color& in) noexcept -> Color&
        {
            R = in.R;
            G = in.G;
            B = in.B;
            A = in.A;
            return *this;
        }
        auto operator+(const Color& in) const -> Color
        {
            return { R + in.R, G + in.G, B + in.B, A + in.A };
        }
        auto operator-(const Color& in) const -> Color
        {
            return { R - in.R, G - in.G, B - in.B, A - in.A };
        }
        auto operator*(const Color& in) const -> Color
        {
            return { R * in.R, G * in.G, B * in.B, A * in.A };
        }
        auto operator/(const Color& in) const -> Color { return { R / in.R, G / in.G, B / in.B, A / in.A }; }
    } __attribute__((aligned(32)));
} // namespace origin
#endif