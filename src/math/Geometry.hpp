#pragma once
#include "Basic.hpp"
#include "Message.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

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

    template<typename T, u64 N>
    class Vec
    {
        T* data = new T[N];

    public:
        Vec<T, N>() { memset(this->data, 0, sizeof(T) * N); }
        Vec(const Vec&) { *this = *this; }
        Vec(Vec&&) noexcept { *this = std::move(*this); }
        Vec& operator=(const Vec&) { return *this; }
        Vec& operator=(Vec&&) noexcept { return *this; }
        Vec<T, N>(T* value) { *this->data = *value; }
        constexpr auto GetData(u64 index) const -> T { return this->data[index]; }
        constexpr T* GetData() { return this->data; }
        constexpr const T* GetData() const { return this->data; }
        constexpr auto SetData(u64 index, T value) -> void { this->data[index] = value; }
        constexpr auto SetData(T* value) -> void { *this->data = *value; }
        constexpr auto SizeConvert(enum Mem::Unit _mu = Mem::Unit::BYTE) const
        {
            return N * sizeof(T) << static_cast<u8>(_mu);
        }
        constexpr auto Size() -> u64 { return N; }
        constexpr auto Find(T minValue, T maxValue, u64& index)
        {
            u64* end = this->data + (N & ~(sizeof(u64) - 1));
            u64 mask = (static_cast<u64>(minValue) ^ static_cast<u64>(maxValue)) >> 63;
            for (auto data = this->data; data != end; data += sizeof(u64))
            {
                u64 value = *reinterpret_cast<const u64*>(data) & mask;
                if (value != 0)
                {
                    index = __builtin_ctzll(value);
                    return this->data[index];
                }
            }
            for (index = 0; this->data != end && index < N; index++)
            {
                T value = this->data[index];
                if (value >= minValue && value <= maxValue)
                {
                    return value;
                }
            }
            return T(0);
        }

        constexpr auto Find(T minValue, T maxValue)
        {
            Vec<T, N> result{};
            u32 count = 0;
            const T* end = this->data + (N & ~(sizeof(u64) - 1));
            for (; this->data != end; this->data += sizeof(u64))
            {
                u64 value = *reinterpret_cast<const u64*>(this->data);
                u64 mask = (static_cast<u64>(minValue) ^ static_cast<u64>(maxValue)) >> 63;
                u64 found = ((value & mask) + ((value ^ mask) & value)) >> 1;
                result[count++] = *reinterpret_cast<T*>(&found);
            }
            for (; count < N; ++count)
            {
                if (this->data[count] >= minValue && this->data[count] <= maxValue)
                {
                    result[count] = this->data[count];
                }
            }
            return result;
        }

        constexpr auto Find(T value, void (*callback)(T))
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<T, N> ret{};
            const T* dataEnd = this->data + (N & ~(sizeof(u64) - 1));
            for (; this->data != dataEnd; this->data += sizeof(u64))
            {
                u64 v = *reinterpret_cast<const u64*>(this->data);
                u64 val = *reinterpret_cast<const u64*>(&value);
                u64 mask = (v ^ val) | ~(v | val);
                u64 r = (mask & *reinterpret_cast<const u64*>(this->data)) ^ val;
                u64 indices = (r & (mask - 1)) + 1;
                while (indices != 0U)
                {
                    u64 index = __builtin_ctzll(indices);
                    indices &= ~(1 << index);
                    callback(this->data[index]);
                    ret[ret.Length()] = this->data[index];
                }
            }
            for (; this->data != (this->data + N); ++data)
            {
                if (*data == value)
                {
                    callback(*data);
                    ret[ret.Size()] = *data;
                }
            }
            return ret;
        }

        constexpr auto Replace(T from, T to, T replacement)
        {
            T* current = this->data;
            const T* const end = this->data + N;
            for (; current != end; ++current)
            {
                if (*current == from || *current == to)
                {
                    *current = replacement;
                }
            }
            return *this;
        }

        constexpr auto Index(Vec<T, N> values)
        {
            Vec<u64, N> indices{};
            u64* indices_data = indices.data;

            for (const T* it = this->data; it != this->data + N; ++it, ++indices_data)
            {
                *indices_data = static_cast<u64>(std::distance(values.data, std::find(values.data, values.data + N, *it)));
            }

            return indices;
        }

        constexpr auto IndexOf(Vec<T, N> values, T lower, T upper)
        {
            Vec<u64, N> indices{};
            u64* indices_data = indices.data;

            for (const T* it = this->data; it != this->data + N; ++it, ++indices_data)
            {
                if (*it >= lower && *it <= upper)
                {
                    *indices_data = std::distance(values.data, std::find(values.data, values.data + N, *it));
                }
            }

            return indices;
        }

        auto IndexThreshold(T value, T threshold)
        {
            Vec<u64, N> result{};
            T lower_bound = value - threshold;
            T upper_bound = value + threshold;
            u64* result_data = result.data;
            for (auto it = this->data; it != this->data + N; ++it, ++result_data)
            {
                auto current = *it;
                if (current >= lower_bound && current <= upper_bound)
                {
                    *result_data = std::distance(this->data, it);
                }
            }
            return result;
        }
        ~Vec<T, N>() { delete[] &this->data; }
        auto Set(T rhs) -> Vec<T, N>
        {
            for (u32 i = 0; i < N; i++)
            {
                this->data[i] = rhs;
            }
            return *this;
        }
        auto Set(T* rhs) -> Vec<T, N>
        {
            std::copy(rhs, rhs + N, this->data);
            return *this;
        }
        auto Set(const Vec<T, N>& rhs)
        {
            std::copy(rhs.data, rhs.data + N, this->data);
            return *this;
        }

        auto Set(T* rhs[N])
        {
            std::copy(rhs, rhs + N, this->data);
            return *this;
        }
        auto Get() -> Vec<T, N> { return this->data; }
        auto Get(u32 _index) -> Vec<T, N> { return this->data[_index]; }
        auto Add(Vec<T, N> rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return Add(rhs.data, ret.data);
        }

        auto Sub(Vec<T, N> rhs)
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::minus<T>());
        }
        auto Mul(const Vec<T, N>& rhs) const
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::multiplies<T>());
        }

        auto Div(const Vec<T, N> rhs)
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::divides<T>());
        }

        auto Mod(const Vec<T, N> rhs)
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::modulus<T>());
        }

        auto And(const Vec<T, N> rhs)
        {
            Vec<T, N> ret;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::bit_and<T>());
        }

        auto Or(const Vec<T, N> rhs)
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::bit_or<T>());
        }
        auto Xor(const Vec<T, N>& rhs)
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::bit_xor<T>());
        }

        auto Neg()
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, ret.data, std::negate<T>());
        }
        auto Inv()
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, ret.data, std::bit_not<T>());
        }
        auto Pow(const Vec<T, N> exp)
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, exp.data, ret.data, std::multiplies<T>());
        }
        auto Swap(Vec<T, N> rhs)
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                std::swap<T>(ret[i], rhs[i]);
            }
            return ret;
        }
        auto Length() const
        {
            T ret = 0;
            for (u32 i = 0; i < N; i++)
            {
                ret += this->data[i] * ret.data[i];
            }
            return std::sqrt(ret);
        }

        auto Dot(const Vec<T, N> rhs) const
        {
            T ret = 0;
            for (u32 i = 0; i < N; i++)
            {
                ret += ret * rhs[i];
            }
            return ret;
        }
        auto LengthSquared() const -> T { return Dot(*this); }
        auto Cross(const Vec<T, N> a, const Vec<T, N> b)
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i += 3)
            {
                ret[i] = a.data[i + 1] * b.data[i + 2] - a.data[i + 2] * b.data[i + 1];
                ret[i + 1] = a.data[i + 2] * b.data[i] - a.data[i] * b.data[i + 2];
                ret[i + 2] = a.data[i] * b.data[i + 1] - a.data[i + 1] * b.data[i];
            }
            return *this;
        }
        auto Abs()
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = abs(ret[i]);
            }
            return ret;
        }

        auto Sqrt()
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = sqrt(ret[i]);
            }
            return ret;
        }
        auto Lerp(const Vec<T, N> endValue, const Vec<T, N> alpha) -> Vec<T, N>
        {
            T* dst = data;
            const T* start = data;
            const T* end = endValue.data;
            const T* weight = alpha.data;

            for (u32 i = 0; i < N; i++, dst++, start++, end++, weight++)
            {
                *dst = *start + (*weight * (*end - *start));
            }

            return { dst };
        }

        auto Equal(const Vec<T, N> rhs) const
        {
            Vec<bool, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = this[i] == rhs[i];
            }
            return ret;
        }
        auto NotEqual(const Vec<T, N>& rhs) const
        {
            Vec<bool, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = this[i] != rhs[i];
            }
            return ret;
        }

        auto Greater(const Vec<T, N>& rhs) const noexcept
        {
            Vec<bool, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = max(this[i], rhs[i]);
            }
            return ret;
        }

        auto GreaterEqual(const Vec<T, N>& rhs) const noexcept
        {
            Vec<bool, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = min(this[i], rhs[i]);
            }
            return ret;
        }

        auto Less(const Vec<T, N>& rhs) const noexcept
        {
            Vec<bool, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = min(this[i], rhs[i]) == rhs[i];
            }
            return ret;
        }
        auto LessEqual(const Vec<T, N>& rhs) const noexcept
        {
            Vec<bool, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = max(this[i], rhs[i]) == rhs[i];
            }
            return ret;
        }

        auto Max(const Vec<T, N>& rhs) const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = max(ret[i], rhs[i]);
            }
            return ret;
        }
        auto Min(const Vec<T, N>& rhs) const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = min(ret[i], rhs[i]);
            }
            return ret;
        }
        auto Clamp(T minValue, T maxValue)
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = clamp(ret[i], minValue, maxValue);
            }
            return ret;
        }
        auto Clamp(Vec<T, N> min, Vec<T, N> max)
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = clamp(ret[i], min[i], max[i]);
            }
            return ret;
        }

        auto Random(T min, T max)
        {
            T range = max - min;
            T scale = range / static_cast<T>(RAND_MAX);
            auto ret = *this;
            for (u64 i = 0; i < N; i++)
            {
                ret[i] = min + static_cast<T>(std::rand()) * scale;
            }
            return ret;
        }
        auto ShiftLeft(const Vec<T, N>& rhs) const noexcept
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = ret[i] << rhs[i];
            }
            return ret;
        }

        auto ShiftRight(const Vec<T, N>& rhs) const noexcept
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = ret[i] >> rhs[i];
            }
            return ret;
        }
        auto Pow(const Vec<T, N>& rhs) const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = pow(ret[i], rhs[i]);
            }
            return ret;
        }
        auto Lerp(const Vec<T, N>& rhs, T exponent) const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = add(ret[i] * exponent, rhs[i] * (T(1) - exponent));
            }
            return ret;
        }
        auto Lerp(const Vec<T, N>& rhs, const Vec<T, N>& exp) const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = add(ret[i] * exp[i], rhs[i] * (T(1) - exp[i]));
            }
            return ret;
        }
        auto Clamp(Vec<T, N> min, Vec<T, N> max) const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = clamp(ret[i], min[i], max[i]);
            }
            return ret;
        }

        auto Clamp(T min, T max) const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = clamp(data[i], min, max);
            }
            return ret;
        }

        auto Abs() const noexcept
        {
            auto ret = *this;

            for (u32 i = 0; i < N; i++)
            {
                ret[i] = abs(this[i]);
            }

            return ret;
        }
        auto Sign() const noexcept
        {
            auto ret = *this;
            const T* src = this->data;
            T* dst = ret.data;
            for (u32 i = 0; i < N; ++i)
            {
                dst[i] = sign(src[i]);
            }
            return ret;
        }
        auto Sqrt() const
        {
            auto ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = T(sqrt(f64(ret[i])));
            }
            return ret;
        }
        auto Square() const noexcept
        {
            auto ret = *this;
            T* resultData = ret.data;
            const T* thisData = this->data;

            for (u32 i = 0; i < N; i++)
            {
                resultData[i] = thisData[i] * thisData[i];
            }

            return ret;
        }
        auto RSqrt() const
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = T(1.0 / sqrt(f64(ret[i])));
            }
            return ret;
        }

        auto Rand(T min, T max)
        {
            const T scale = T(RAND_MAX) / (max - min);
            for (u32 i = 0; i < N; ++i)
            {
                data[i] = min + (std::rand()) * scale;
            }
            return *this;
        }
        auto IsNan() const noexcept -> bool
        {
            bool result = false;
            for (u32 i = 0; i < N; i++)
            {
                result |= isnan(this[i]);
            }
            return result;
        }
        auto IsNum() const -> bool { return this->IsNan(); }
        inline auto operator[](u32 index) -> T& { return this->data[index]; }
        auto operator=(T* src)
        {
            std::memcpy(data, src, N * sizeof(T));
            return *this;
        }
        constexpr auto operator[](u32 index) const noexcept -> T
        {
            return index < N ? this->data[index] : T{};
        }
        explicit operator Vec<T, N>*() { return this; }
        auto operator+(const T rhs) -> Vec<T, N> { return this->Add(rhs); }
        auto operator-(const T rhs) -> Vec<T, N> { return this->Sub(rhs); }
        auto operator*(const T rhs) -> Vec<T, N> { return this->Mul(rhs); }
        auto operator/(const T rhs) -> Vec<T, N> { return this->Div(rhs); }
        auto operator%(const T rhs) -> Vec<T, N> { return this->Mod(rhs); }
        auto operator&(const T rhs) -> Vec<T, N> { return this->And(rhs); }
        auto operator|(const T rhs) -> Vec<T, N> { return this->Or(rhs); }
        auto operator^(const T rhs) -> Vec<T, N> { return this->Pow(rhs); }
        auto operator<<(const T rhs) -> Vec<T, N> { return this->ShiftLeft(rhs); }
        auto operator>>(const T rhs) -> Vec<T, N> { return this->ShiftRight(rhs); }
        auto operator==(const T rhs) -> Vec<bool, N> { return this->Equal(rhs); }
        auto operator!=(const T rhs) -> Vec<bool, N> { return this->NotEqual(rhs); }
        auto operator<(const T rhs) -> Vec<bool, N> { return this->Lt(rhs); }
        auto operator<=(const T rhs) -> Vec<bool, N> { return this->LessEqual(rhs); }
        auto operator>(const T rhs) -> Vec<bool, N> { return this->Greater(rhs); }
        auto operator>=(const T rhs) -> Vec<bool, N> { return this->GreaterEqual(rhs); }
        auto operator-() -> Vec<T, N> { return Neg(); }
        auto operator~() const -> Vec<T, N> { return Vec<T, N>(~*this); }
        auto operator+=(const T rhs)
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] += rhs;
            }
            return *this;
        }
        auto operator-=(const T rhs)
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] -= rhs;
            }
            return *this;
        }
        auto operator*=(const T rhs)
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] *= rhs;
            }
        }
        auto operator/=(const T rhs)
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] /= rhs;
            }
            return *this;
        }
        auto operator%=(const Vec<T, N> rhs)
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] %= rhs[i];
            }
            return *this;
        }
        auto operator&=(const Vec<T, N>& rhs)
        {
            return *this = this->And(rhs);
        }
        auto operator|=(const Vec<T, N>& rhs)
        {
            return *this = this->Or(rhs);
        }
        auto operator^=(const Vec<T, N>& rhs)
        {
            return *this = this->Pow(rhs);
        }
        auto operator<<=(const Vec<T, N>& rhs)
        {
            return *this = this->ShiftLeft(rhs);
        }
        auto operator>>=(const Vec<T, N>& rhs) -> Vec<T, N>
        {
            return *this = this->ShiftRight(rhs);
        }
        auto operator++()
        {
            return *this = this->Add(1);
        }
        auto operator--()
        {
            return *this = this->Sub(1);
        }
        explicit operator T*() { return this; }
        explicit operator Vec<T, N>() { return this; } // Vec<T,N>
        auto operator+(const Vec<T, N> rhs) -> Vec<T, N> { return this->Add(rhs); }
        auto operator-(const Vec<T, N> rhs) -> Vec<T, N> { return this->Sub(rhs); }
        auto operator*(const Vec<T, N> rhs) -> Vec<T, N> { return this->Mul(rhs); }
        auto operator/(const Vec<T, N> rhs) -> Vec<T, N> { return this->Div(rhs); }
        auto operator%(const Vec<T, N> rhs) -> Vec<T, N> { return this->Mod(rhs); }
        auto operator&(const Vec<T, N> rhs) -> Vec<T, N> { return this->And(rhs); }
        auto operator|(const Vec<T, N> rhs) -> Vec<T, N> { return this->Or(rhs); }
        auto operator^(const Vec<T, N> rhs) -> Vec<T, N> { return this->Pow(rhs); }
        auto operator<<(const Vec<T, N> rhs) -> Vec<T, N> { return this->ShiftL(rhs); }
        auto operator>>(const Vec<T, N> rhs) -> Vec<T, N> { return this->ShiftR(rhs); }
        auto operator+=(const Vec<T, N> rhs)
        {
            return *this = this->Add(rhs);
        }
        auto operator-=(const Vec<T, N> rhs)
        {
            return *this = this->Sub(rhs);
        }
        auto operator*=(const Vec<T, N> rhs)
        {
            return *this = Mul(rhs);
        }
        auto operator/=(const Vec<T, N> rhs)
        {
            return *this = Div(rhs);
        }
        auto operator&=(const Vec<T, N> rhs)
        {
            return *this = And(rhs);
        }
        auto operator|=(const Vec<T, N> rhs)
        {
            return *this = Or(rhs);
        }
        auto operator^=(const Vec<T, N> rhs)
        {
            return *this = Pow(rhs);
        };
        auto operator<<=(const Vec<T, N> rhs)
        {
            return *this = ShiftLeft(rhs);
        };
        auto operator>>=(const Vec<T, N> rhs)
        {
            return *this = ShiftRight(rhs);
        };
    };

    template<u64 N>
    class Vecf : private Vec<f64, N>
    {
    public:
        Vecf() = default;
        explicit Vecf(Vecf const& rhs) :
            Vec<f64, N>(rhs) {}
        Vecf(f64 const* ap)
        {
            this->data = new f64[N];
            for (auto i = 0; i < N; ++i)
            {
                this->data[i] = ap[i];
            }
        }
        Vecf(Vecf&& rhs) noexcept :
            Vec<f64, N>(rhs) {}
        ~Vecf() { delete[] this; }

        auto GetData() const -> f64* { return this->data; }

        auto operator=(Vecf const& rhs) -> Vecf&
        {
            std::memcpy(this->data, rhs.GetData(), N * sizeof(f64));
            return *this;
        }
        auto operator=(f64 const* ap) -> Vecf&
        {
            std::memcpy(this->data, ap, N * sizeof(f64));
            return *this;
        }
        auto operator=(Vecf&& rhs) noexcept -> Vecf& { return *this = rhs; }
        auto operator[](u64 i) -> f64& { return this->data[i]; }
        auto operator[](u64 i) const -> f64 { return this->data[i]; }
        auto operator+(f64 const& rhs) -> Vecf { return this->Add(rhs); }
        auto operator-(f64 const& rhs) -> Vecf { return this->Sub(-rhs); }
        auto operator*(f64 const& rhs) -> Vecf { return this->Mul(rhs); }
        auto operator/(f64 const& rhs) -> Vecf { return this->Div(rhs); }
        auto operator+(Vecf const& rhs) -> Vecf { return this->Add(rhs); }
        auto operator-(Vecf const& rhs) -> Vecf { return this->Sub(rhs); }
        auto operator*(Vecf const& rhs) -> Vecf { return this->Mul(rhs); }
        auto operator/(Vecf const& rhs) -> Vecf { return this->Div(rhs); }
    };
    using Vec2i = Vec<i64, 2>;
    using Vec3i = Vec<i64, 3>;
    using Vec4i = Vec<i64, 4>;
    using Vec16f = Vec<f64, 16>;
    using Vec16i = Vec<i64, 16>;
    class Vec2f
    {
    public:
        union
        {
            f64* data = new f64[2];
            struct
            {
                f64 x;
                f64 y;
            } __attribute__((aligned(16)));
        };
        Vec2f() = default;
        explicit Vec2f(Vec2f const& rhs)
        {
            std::memcpy(this->data, rhs.data, 2 * sizeof(f64));
        }
        Vec2f(f64 _x, f64 _y)
        {
            this->data[0] = _x;
            this->data[1] = _y;
        }
        ~Vec2f() { delete[] this->data; }
    };

    class Vec3f
    {
    public:
        union
        {
            f64* data = new f64[3];
            struct
            {
                f64 x;
                f64 y;
                f64 z;
            } __attribute__((aligned(32)));
        };
        Vec3f() = default;
        Vec3f(Vec3f const& rhs)
        {
            std::memcpy(this->data, rhs.data, 3 * sizeof(f64));
        }
        Vec3f(f64 _x, f64 _y, f64 _z)
        {
            this->data[0] = _x;
            this->data[1] = _y;
            this->data[2] = _z;
        }
    };

    class Vec4f : private Vecf<4>
    {
    public:
        union
        {
            f64* data = new f64[4];
            struct
            {
                f64 x;
                f64 y;
                f64 z;
                f64 w;
            } __attribute__((aligned(32)));
        };
        Vec4f() = default;
        Vec4f(Vecf<4> const& rhs) :
            Vecf(rhs)
        {
        }
        Vec4f(Vec4f&& rhs) noexcept :
            Vecf(rhs)
        {
        }
        Vec4f(Vec4f const& rhs) :
            Vecf(rhs)
        {
            std::memcpy(this->data, rhs.data, 4 * sizeof(f64));
        }
        Vec4f(f64 _x, f64 _y, f64 _z, f64 _w)
        {
            this->data[0] = _x;
            this->data[1] = _y;
            this->data[2] = _z;
            this->data[3] = _w;
        }

        ~Vec4f() { delete[] this->data; }
        auto operator=(Vec4f&& rhs) noexcept -> Vec4f& { return *this = rhs; }
        auto operator[](u64 i) const -> f64& { return this->data[i]; }
        auto operator=(Vec4f const& rhs) -> Vec4f&
        {
            std::memcpy(this->data, rhs.data, 4 * sizeof(f64));
            return *this;
        }
        auto operator+(Vec4f const& rhs) const -> Vec4f { return { this->data[0] + rhs.data[0], this->data[1] + rhs.data[1], this->data[2] + rhs.data[2], this->data[3] + rhs.data[3] }; }

        auto operator-(Vec4f const& rhs) const -> Vec4f { return { this->data[0] - rhs.data[0], this->data[1] - rhs.data[1], this->data[2] - rhs.data[2], this->data[3] - rhs.data[3] }; }

        auto operator*(f64 rhs) const -> Vec4f { return { this->data[0] * rhs, this->data[1] * rhs, this->data[2] * rhs, this->data[3] * rhs }; }

        auto operator/(f64 rhs) const -> Vec4f { return { this->data[0] / rhs, this->data[1] / rhs, this->data[2] / rhs, this->data[3] / rhs }; }
    };
    class Vec16 : public Vec16f
    {
    public:
        union
        {
            f64* data = new f64[16];
            struct
            {
                f64 x0;
                f64 x1;
                f64 x2;
                f64 x3;
                f64 y0;
                f64 y1;
                f64 y2;
                f64 y3;
                f64 z0;
                f64 z1;
                f64 z2;
                f64 z3;
                f64 w0;
                f64 w1;
                f64 w2;
                f64 w3;
            } __attribute__((aligned(128)));
        };
        Vec16() = default;
        Vec16(Vec<f64, 16>& rhs) :
            Vec16() { this->data = rhs.GetData(); }
        Vec16(Vec<f64, 16> const& rhs) { *data = *rhs.GetData(); }
        Vec16(f64 x0, f64 x1, f64 x2, f64 x3, f64 y0, f64 y1, f64 y2, f64 y3, f64 z0, f64 z1, f64 z2, f64 z3, f64 w0, f64 w1, f64 w2, f64 w3)
        {
            this->data[0] = x0;
            this->data[1] = x1;
            this->data[2] = x2;
            this->data[3] = x3;
            this->data[4] = y0;
            this->data[5] = y1;
            this->data[6] = y2;
            this->data[7] = y3;
            this->data[8] = z0;
            this->data[9] = z1;
            this->data[10] = z2;
            this->data[11] = z3;
            this->data[12] = w0;
            this->data[13] = w1;
            this->data[14] = w2;
            this->data[15] = w3;
        }
        Vec16(f64 x[4], f64 y[4], f64 z[4], f64 w[4]) :
            Vec16(x[0], x[1], x[2], x[3], y[0], y[1], y[2], y[3], z[0], z[1], z[2], z[3], w[0], w[1], w[2], w[3])
        {
        }
    };
    class Quaternion : Vec16
    {
    private:
        union
        {
            f64* data = new f64[16];
            struct
            {
                f64 x0;
                f64 x1;
                f64 x2;
                f64 x3;
                f64 y0;
                f64 y1;
                f64 y2;
                f64 y3;
                f64 z0;
                f64 z1;
                f64 z2;
                f64 z3;
                f64 w0;
                f64 w1;
                f64 w2;
                f64 w3;
            } __attribute__((aligned(128)));
        };

    public:
        Quaternion()
        {
            std::fill(data, data + 16, 0.0);
        };
        Quaternion(const Quaternion& rhs) :
            Vec16(rhs)
        {
            std::copy(rhs.GetData(), rhs.GetData() + 16, data);
        }
        explicit Quaternion(const f64 (&src)[16]) :
            Vec16(src[0], src[1], src[2], src[3], src[4], src[5], src[6], src[7], src[8], src[9], src[10], src[11], src[12], src[13], src[14], src[15])
        {
            std::copy(src, src + 16, data);
        }
        Quaternion(const f64 x[4], const f64 y[4], const f64 z[4], const f64 w[4]) :
            Vec16({ x[0], x[1], x[2], x[3], y[0], y[1], y[2], y[3], z[0], z[1], z[2], z[3], w[0], w[1], w[2], w[3] })
        {
            std::copy(x, x + 4, data);
            std::copy(y, y + 4, data + 4);
            std::copy(z, z + 4, data + 8);
            std::copy(w, w + 4, data + 12);
        }

        auto Add(const Quaternion& rhs) const
        {
            auto ret = *this;
            ;
            for (u32 i = 0; i < 4; ++i)
            {
                ret[i] = data[i] + rhs[i];
            }
            return ret;
        }

        auto Sub(const Quaternion& rhs) const
        {
            auto ret = *this;
            ;
            for (u32 i = 0; i < 4; ++i)
            {
                ret[i] = data[i] - rhs[i];
            }
            return ret;
        }
        auto Mul(const Vec4f& rhs) const
        {
            auto ret = *this;
            ;
            for (u32 i = 0; i < 4; ++i)
            {
                ret[i] = data[i * 4] * rhs[0] + data[i * 4 + 1] * rhs[1] + data[i * 4 + 2] * rhs[2] + data[i * 4 + 3] * rhs[3];
            }
            return ret;
        }
        auto Mul(const Quaternion& rhs) const
        {
            auto ret = *this;
            for (u32 i = 0; i < 4; ++i)
            {
                for (u32 j = 0; j < 4; ++j)
                {
                    ret.data[i * 4 + j] = data[i * 4] * rhs.data[j] + data[i * 4 + 1] * rhs.data[j + 4] + data[i * 4 + 2] * rhs.data[j + 8] + data[i * 4 + 3] * rhs.data[j + 12];
                }
            }
            return ret;
        }
        auto Div(const Quaternion& rhs) const
        {
            return Mul(-rhs);
        }
        auto Div(const Vec4f& rhs) const
        {
            auto ret = *this;
            return ret.Mul({ -rhs[0], -rhs[1], -rhs[2], -rhs[3] });
        }
        auto Inverse() const
        {
            auto ret = *this;
            for (u32 i = 0; i < 4; ++i)
            {
                ret.data[i * 4 + i] = 1.0f - ret.data[i * 4 + i];
            }
            return ret;
        }

        static auto Transform(const Quaternion& q, const Vec4f& v)
        {
            return Quaternion{ { q.data[0] * v.x + q.data[1] * v.y + q.data[2] * v.z,
                                 q.data[1] * v.x - q.data[0] * v.y - q.data[3] * v.z, //
                                 q.data[2] * v.x - q.data[3] * v.y + q.data[0] * v.z, //
                                 q.data[3] * v.x + q.data[2] * v.y - q.data[1] * v.z } };
        }

        static auto Rotate(const Quaternion& q, const Vec4f& v, f64 angle)
        {
            f64 s{ 0 };
            f64 c{ 0 };
            sincos(angle, &s, &c);
            f64 qx = q.data[1] * v.x + q.data[2] * v.y + q.data[3] * v.z * c - q.data[0] * v.x * s;
            f64 qy = q.data[2] * v.x - q.data[1] * v.y - q.data[3] * v.z * c - q.data[0] * v.y * s;
            f64 qz = q.data[3] * v.x - q.data[2] * v.y + q.data[1] * v.z * c - q.data[0] * v.z * s;
            f64 qw = q.data[0] * v.x + q.data[3] * v.y - q.data[2] * v.z * c + q.data[1] * v.w * s;

            Quaternion ret{ { qx, qy, qz, qw } };
            return ret;
        }

        static auto Rotate(const Quaternion q, Vec4f& axis, Face face)
        {
            f64 a = acos(axis.w) / ((axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2] + axis[3] * axis[3]) * 2.0);
            Vec4f dv;
            switch (face)
            {
            case Face::Right:
                dv.x = sin(a);
                break;
            case Face::Front:
                dv.y = sin(a);
                break;
            case Face::Up:
                dv.z = sin(a);
                break;
            case Face::Left:
                dv.x = -sin(a);
                break;
            case Face::Back:
                dv.y = -sin(a);
                break;
            case Face::Down:
                dv.z = -sin(a);
                break;
            case Face::None:
                break;
            }

            auto ret = Quaternion(&axis.x, &axis.y, &axis.z, &axis.w);
            ret *= Quaternion(&dv.x, &dv.y, &dv.z, &dv.w);
            return Transform(ret, axis);
        }
        auto Dot(const Quaternion& rhs, const Vec4f& t) const
        {
            return data[0] * rhs.data[0] + data[1] * rhs.data[1] + data[2] * rhs.data[2] + data[3] * rhs.data[3] + t.x * rhs.data[0] + t.y * rhs.data[1] + t.z * rhs.data[2] + t.w * rhs.data[3] + t.x * rhs.data[0] + t.y * rhs.data[1] + t.z * rhs.data[2] + t.w * rhs.data[3];
        }
        auto LengthSquared() const -> f64 { return Dot(*this, Vec4f(data[0], data[1], data[2], data[3])); }

        auto Length() const -> f64 { return sqrt(LengthSquared()); }
        auto Translate(const Quaternion& q, const Vec4f& t)
        {
            auto ret = *this;
            for (u32 i = 0; i < 4; ++i)
            {
                ret.data[i] = q.data[i] + ret.Dot(q, t);
            }
            return ret;
        }

        explicit operator Quaternion*()
        {
            return this;
        }

        auto operator=(f64 const* rhs) -> Quaternion&
        {
            std::memcpy(this->data, rhs, 16 * sizeof(f64));
            return *this;
        }
        auto operator=(Quaternion&& rhs) noexcept -> Quaternion&
        {
            *this->data = *rhs.data;
            return *this;
        }
        auto operator*(Quaternion const& rhs) const -> Quaternion
        {
            return Mul(rhs);
        }
        auto operator*(Quaternion& rhs) const -> Quaternion { return Mul(rhs); }
        auto operator*(const f64 scalar[16]) const -> Quaternion
        {
            Quaternion result;
            for (u64 i = 0; i < 4; i++)
            {
                for (u64 j = 0; j < 4; j++)
                {
                    result.data[i * 4 + j] = data[i * 4] * scalar[j] + data[i * 4 + 1] * scalar[j + 4] + data[i * 4 + 2] * scalar[j + 8] + data[i * 4 + 3] * scalar[j + 12];
                }
            }
            return result;
        }
        auto operator/(const Quaternion& rhs) const -> Quaternion
        {
            return Div(rhs);
        }

        auto operator+(const Quaternion& rhs) const noexcept -> Quaternion
        {
            return Add(rhs);
        }

        auto operator-(const Quaternion& rhs) const noexcept -> Quaternion
        {
            return Sub(rhs);
        }
        auto operator-() const noexcept -> Quaternion { return Inverse(); }
        auto operator*=(const Quaternion& rhs) noexcept -> Quaternion { return *this = this->Mul(rhs); }
        auto operator/=(const Quaternion& rhs) noexcept -> Quaternion { return *this = this->Div(rhs); }
        auto operator+=(const Quaternion& rhs) noexcept -> Quaternion { return *this = this->Add(rhs); }
        auto operator-=(const Quaternion& rhs) noexcept -> Quaternion { return *this = this->Sub(rhs); }
        explicit operator f64*() const
        {
            return new f64[16]{ this->data[0], this->data[1], this->data[2], this->data[3], this->data[4], this->data[5], this->data[6], this->data[7], this->data[8], this->data[9], this->data[10], this->data[11], this->data[12], this->data[13], this->data[14], this->data[15] };
        }

        explicit operator string() const
        {
            string ret = "[";
            for (u32 i = 0; i < 16; i++)
            {
                ret += std::to_string(this->data[i]);
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
            return std::equal(data, data + 16, rhs.data);
        }

        auto operator!=(const Quaternion& rhs) const -> bool
        {
            return !(*this == rhs);
        }
    }; // namespace origin
} // namespace origin