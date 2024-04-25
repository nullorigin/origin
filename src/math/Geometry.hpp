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
        constexpr auto SizeConvert(enum Mem::Unit _mu = Mem::Unit::BYTE) const -> u64
        {
            return N * sizeof(T) << static_cast<u8>(_mu);
        }
        constexpr auto Size() -> u64 { return N; }
        constexpr auto Find(T minValue, T maxValue, u64& index) -> T
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

        constexpr auto Find(T minValue, T maxValue) -> Vec<T, N>
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

        constexpr auto Find(T value, void (*callback)(T)) -> Vec<T, N>
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

        constexpr auto Replace(T from, T to, T replacement) -> Vec<T, N>
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

        constexpr auto Index(Vec<T, N> values) -> Vec<u64, N>
        {
            Vec<u64, N> indices{};
            u64* indicesData = indices.data;

            for (const T* it = this->data; it != this->data + N; ++it, ++indicesData)
            {
                *indicesData = static_cast<u64>(std::distance(values.data, std::find(values.data, values.data + N, *it)));
            }

            return indices;
        }

        constexpr auto IndexOf(Vec<T, N> values, T lower, T upper) -> Vec<u64, N>
        {
            Vec<u64, N> indices{};
            u64* indicesData = indices.data;

            for (const T* it = this->data; it != this->data + N; ++it, ++indicesData)
            {
                if (*it >= lower && *it <= upper)
                {
                    *indicesData = std::distance(values.data, std::find(values.data, values.data + N, *it));
                }
            }

            return indices;
        }

        auto indexThreshold(T value, T threshold) const -> Vec<u64, N>
        {
            Vec<u64, N> result{};
            T lowerBound = value - threshold;
            T upperBound = value + threshold;
            u64* resultData = result.data;
            for (auto it = this->data; it != this->data + N; ++it, ++resultData)
            {
                auto current = *it;
                if (current >= lowerBound && current <= upperBound)
                {
                    *resultData = std::distance(this->data, it);
                }
            }
            return result;
        }
        ~Vec<T, N>() { delete[] &this->data; }
        auto Set(T _rhs) -> Vec<T, N>
        {
            for (u32 i = 0; i < N; i++)
            {
                this->data[i] = _rhs;
            }
            return *this;
        }
        auto Set(T* _rhs) -> Vec<T, N>
        {
            std::copy(_rhs, _rhs + N, this->data);
            return *this;
        }
        auto Set(const Vec<T, N>& _rhs) -> Vec<T, N>
        {
            std::copy(_rhs.data, _rhs.data + N, this->data);
            return *this;
        }

        auto Set(T* _rhs[N]) -> Vec<T, N>
        {
            std::copy(_rhs, _rhs + N, this->data);
            return *this;
        }
        auto Get() -> Vec<T, N> { return this->data; }
        auto Get(u32 _index) -> Vec<T, N> { return this->data[_index]; }
        auto Add(Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return Add(_rhs.data, ret.data);
        }

        auto Sub(Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, _rhs.data, ret.data, std::minus<T>());
        }
        auto Mul(const Vec<T, N>& rhs) const -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::multiplies<T>());
        }

        auto Div(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, _rhs.data, ret.data, std::divides<T>());
        }

        auto Mod(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, _rhs.data, ret.data, std::modulus<T>());
        }

        auto And(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret;
            return std::transform(this->data, this->data + N, _rhs.data, ret.data, std::bit_and<T>());
        }

        auto Or(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, _rhs.data, ret.data, std::bit_or<T>());
        }
        auto Xor(const Vec<T, N>& rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, rhs.data, ret.data, std::bit_xor<T>());
        }

        auto Neg() -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, ret.data, std::negate<T>());
        }
        auto Inv() -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, ret.data, std::bit_not<T>());
        }
        auto Pow(const Vec<T, N> exp) -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return std::transform(this->data, this->data + N, exp.data, ret.data, std::multiplies<T>());
        }
        auto Swap(Vec<T, N> _rhs) -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                std::swap<T>(ret[i], _rhs[i]);
            }
            return ret;
        }
        auto Length() const -> T
        {
            T ret = 0;
            for (u32 i = 0; i < N; i++)
            {
                ret += this->data[i] * ret.data[i];
            }
            return std::sqrt(ret);
        }

        auto Dot(const Vec<T, N> _rhs) const -> T
        {
            T ret = 0;
            for (u32 i = 0; i < N; i++)
            {
                ret += ret * _rhs[i];
            }
            return ret;
        }
        auto LengthSquared() const -> T { return Dot(*this); }
        auto Cross(const Vec<T, N> a, const Vec<T, N> b) -> Vec<T, N>
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
        auto Abs() -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = origin::Abs<T>(ret[i]);
            }
            return ret;
        }

        auto Sqrt() -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = origin::Sqrt<T>(ret[i]);
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

        auto Equal(const Vec<T, N> _rhs) noexcept -> Vec<bool, N>
        {
            Vec<bool, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = ret.data[i] == _rhs.data[i];
            }
            return ret;
        }
        auto NotEqual(const Vec<T, N>& rhs) noexcept -> Vec<bool, N>
        {
            Vec<bool, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = ret[i] != rhs[i];
            }
            return ret;
        }

        auto Greater(const Vec<T, N>& rhs) const -> Vec<bool, N>
        {
            Vec<bool, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Max<T, T>(ret[i], rhs[i]);
            }
            return ret;
        }

        auto GreaterEqual(const Vec<T, N>& rhs) const noexcept -> Vec<bool, N>
        {
            Vec<bool, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Min<T, T>(ret[i], rhs[i]);
            }
            return ret;
        }

        auto Lesser(const Vec<T, N>& rhs) const noexcept -> Vec<bool, N>
        {
            Vec<bool, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Min<T, T>(ret[i], rhs[i]);
            }
            return ret;
        }
        auto LessEqual(const Vec<T, N>& rhs) const noexcept -> Vec<bool, N>
        {
            Vec<bool, N> ret = *this;

            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Max<T, T>(ret[i], rhs[i]);
            }
        }

        auto Max(const Vec<T, N>& rhs) const -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Max<T, T>(ret[i], rhs[i]);
            }
            return ret;
        }
        auto Min(const Vec<T, N> rhs) const -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Min<T, T>(ret[i], rhs[i]);
            }
            return ret;
        }
        auto Clamp(T minValue, T maxValue) -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Clamp(ret[i], minValue, maxValue);
            }
            return ret;
        }
        auto Clamp(Vec<T, N> min, Vec<T, N> max) -> Vec<T, N>
        {
            Vec<T, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = origin::Clamp(ret[i], min[i], max[i]);
            }
            return ret;
        }

        auto Random(T min, T max) -> Vec<T, N>
        {
            T range = max - min;
            T scale = range / static_cast<T>(RAND_MAX);
            Vec<T, N> result;
            for (u64 i = 0; i < N; i++)
            {
                result[i] = min + static_cast<T>(std::rand()) * scale;
            }
            return result;
        }
        auto ShiftLeft(const Vec<T, N>& rhs) const -> Vec<T, N>
        {
            Vec<T, N> ret;
            for (u32 i = 0; i < N; ++i)
            {
                ret[i] = ret[i] << rhs[i];
            }
            return ret;
        }

        auto ShiftRight(const Vec<T, N>& rhs) const noexcept -> Vec<T, N>
        {
            Vec<T, N> result = *this;
            for (u32 i = 0; i < N; ++i)
            {
                result[i] = result[i] >> rhs[i];
            }
            return result;
        }
        auto Pow(const Vec<T, N>& rhs) const -> Vec<T, N>
        {
            Vec<T, N> result = *this;
            for (u32 i = 0; i < N; ++i)
            {
                result[i] = T(origin::Pow(f64(result[i]), f64(rhs[i])));
            }
            return result;
        }
        auto Lerp(const Vec<T, N>& rhs, T exponent) const -> Vec<T, N>
        {
            Vec<T, N> result = *this;
            for (u32 i = 0; i < N; i++)
            {
                result[i] = origin::Add(result[i] * exponent, rhs[i] * (T(1) - exponent));
            }
            return Vec<T, N>(result);
        }
        auto Lerp(const Vec<T, N>& rhs, const Vec<T, N>& exp) const -> Vec<T, N>
        {
            Vec<T, N> result = *this;
            for (u32 i = 0; i < N; i++)
            {
                result[i] = origin::Add(result[i] * exp[i], rhs[i] * (T(1) - exp[i]));
            }
            return result;
        }
        auto Clamp(Vec<T, N> min, Vec<T, N> max) const -> Vec<T, N>
        {
            Vec<T, N> result = *this;
            for (u32 i = 0; i < N; i++)
            {
                result[i] = origin::Clamp(result[i], min[i], max[i]);
            }
            return result;
        }

        auto Clamp(T min, T max) const -> Vec<T, N>
        {
            Vec<T, N> result;
            for (u32 i = 0; i < N; ++i)
            {
                result[i] = origin::Clamp(data[i], min, max);
            }
            return result;
        }

        auto Abs() const noexcept -> Vec<T, N>
        {
            Vec<T, N> result;
            T* resultData = result.data;
            const T* thisData = this->data;

            for (u32 i = 0; i < N; i++)
            {
                resultData[i] = Abs(thisData[i]);
            }

            return result;
        }
        auto Sign() const noexcept -> Vec<T, N>
        {
            Vec<T, N> result;
            const T* src = this->data;
            T* dst = result.data;
            for (u32 i = 0; i < N; ++i)
            {
                dst[i] = origin::Sign(src[i]);
            }
            return result;
        }
        auto Sqrt() const -> Vec<T, N>
        {
            Vec<T, N> result{ *this };
            for (u32 i = 0; i < N; ++i)
            {
                result[i] = T(origin::Sqrt(f64(result[i])));
            }
            return result;
        }
        auto Square() const noexcept -> Vec<T, N>
        {
            Vec<T, N> result;
            T* resultData = result.data;
            const T* thisData = this->data;

            for (u32 i = 0; i < N; i++)
            {
                resultData[i] = thisData[i] * thisData[i];
            }

            return result;
        }
        auto RSqrt() const -> Vec<T, N>
        {
            Vec<T, N> result{ *this };
            for (u32 i = 0; i < N; ++i)
            {
                result[i] = T(1.0 / origin::Sqrt(f64(result[i])));
            }
            return result;
        }

        auto Rand(T min, T max) -> Vec<T, N>
        {
            const T scale = T(RAND_MAX) / (max - min);
            for (u32 i = 0; i < N; ++i)
            {
                data[i] = min + T((std::rand()) * scale);
            }
            return *this;
        }
        auto IsNan() const noexcept -> bool
        {
            bool result = false;
            for (u32 i = 0; i < N; i++)
            {
                result |= origin::IsNan(this[i]);
            }
            return result;
        }
        auto IsNum() const -> bool { return !IsNan(); }
        inline auto operator[](u32 index) -> T& { return this->data[index]; }
        auto operator=(T* src) -> Vec<T, N>&
        {
            std::memcpy(data, src, N * sizeof(T));
            return *this;
        }
        constexpr auto operator[](u32 index) const noexcept -> T
        {
            return index < N ? this->data[index] : T{};
        }
        explicit operator Vec<T, N>*() { return this; }
        auto operator+(const T _rhs) -> Vec<T, N> { return this->Add(_rhs); }
        auto operator-(const T _rhs) -> Vec<T, N> { return this->Sub(_rhs); }
        auto operator*(const T _rhs) -> Vec<T, N> { return this->Mul(_rhs); }
        auto operator/(const T _rhs) -> Vec<T, N> { return this->Div(_rhs); }
        auto operator%(const T _rhs) -> Vec<T, N> { return this->Mod(_rhs); }
        auto operator&(const T _rhs) -> Vec<T, N> { return this->And(_rhs); }
        auto operator|(const T _rhs) -> Vec<T, N> { return this->Or(_rhs); }
        auto operator^(const T _rhs) -> Vec<T, N> { return this->Pow(_rhs); }
        auto operator<<(const T _rhs) -> Vec<T, N> { return this->ShiftLeft(_rhs); }
        auto operator>>(const T _rhs) -> Vec<T, N> { return this->ShiftRight(_rhs); }
        auto operator==(const T _rhs) -> Vec<bool, N> { return this->Equal(_rhs); }
        auto operator!=(const T _rhs) -> Vec<bool, N> { return this->NotEqual(_rhs); }
        auto operator<(const T _rhs) -> Vec<bool, N> { return this->Lt(_rhs); }
        auto operator<=(const T _rhs) -> Vec<bool, N> { return this->LessEqual(_rhs); }
        auto operator>(const T _rhs) -> Vec<bool, N> { return this->Greater(_rhs); }
        auto operator>=(const T _rhs) -> Vec<bool, N> { return this->GreaterEqual(_rhs); }
        auto operator-() -> Vec<T, N> { return Neg(); }
        auto operator~() const -> Vec<T, N> { return Vec<T, N>(~*this); }
        auto operator+=(const T _rhs) -> Vec<T, N>
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] += _rhs;
            }
            return *this;
        }
        auto operator-=(const T _rhs) -> Vec<T, N>
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] -= _rhs;
            }
            return *this;
        }
        auto operator*=(const T _rhs) -> Vec<T, N>
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] *= _rhs;
            }
        }
        auto operator/=(const T _rhs) -> Vec<T, N>
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] /= _rhs;
            }
            return *this;
        }
        auto operator%=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            for (u32 i = 0; i < N; i++)
            {
                this[i] %= _rhs[i];
            }
            return *this;
        }
        auto operator&=(const Vec<T, N>& _rhs) -> Vec<T, N>
        {
            *this = this->And(_rhs);
            return *this;
        }
        auto operator|=(const Vec<T, N>& _rhs) -> Vec<T, N>
        {
            *this = this->Or(_rhs);
            return *this;
        }
        auto operator^=(const Vec<T, N>& _rhs) -> Vec<T, N>
        {
            *this = this->Pow(_rhs);
            return *this;
        }
        auto operator<<=(const Vec<T, N>& _rhs) -> Vec<T, N>
        {
            *this = this->ShiftL(_rhs);
            return *this;
        }
        auto operator>>=(const Vec<T, N>& _rhs) -> Vec<T, N>
        {
            *this = this->ShiftR(_rhs);
            return *this;
        }
        auto operator++() -> Vec<T, N>
        {
            *this = this->Add(1);
            return *this;
        }
        auto operator--() -> Vec<T, N>
        {
            *this = this->Sub(1);
            return *this;
        }
        explicit operator T*() { return this; }
        explicit operator Vec<T, N>() { return this; } // Vec<T,N>
        auto operator+(const Vec<T, N> _rhs) -> Vec<T, N> { return this->Add(_rhs); }
        auto operator-(const Vec<T, N> _rhs) -> Vec<T, N> { return this->Sub(_rhs); }
        auto operator*(const Vec<T, N> _rhs) -> Vec<T, N> { return this->Mul(_rhs); }
        auto operator/(const Vec<T, N> _rhs) -> Vec<T, N> { return this->Div(_rhs); }
        auto operator%(const Vec<T, N> _rhs) -> Vec<T, N> { return this->Mod(_rhs); }
        auto operator&(const Vec<T, N> _rhs) -> Vec<T, N> { return this->And(_rhs); }
        auto operator|(const Vec<T, N> _rhs) -> Vec<T, N> { return this->Or(_rhs); }
        auto operator^(const Vec<T, N> _rhs) -> Vec<T, N> { return this->Pow(_rhs); }
        auto operator<<(const Vec<T, N> _rhs) -> Vec<T, N> { return this->ShiftL(_rhs); }
        auto operator>>(const Vec<T, N> _rhs) -> Vec<T, N> { return this->ShiftR(_rhs); }
        auto operator+=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = this->Add(_rhs);
            return *this;
        }
        auto operator-=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = Sub(_rhs);
            return *this;
        }
        auto operator*=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = Mul(_rhs);
            return *this;
        }
        auto operator/=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = Div(_rhs);
            return *this;
        }
        auto operator&=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = And(_rhs);
            return *this;
        }
        auto operator|=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = Or(_rhs);
            return *this;
        }
        auto operator^=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = Pow(_rhs);
            return *this;
        };
        auto operator<<=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = ShiftLeft(_rhs);
            return *this;
        };
        auto operator>>=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = ShiftRight(_rhs);
            return *this;
        };
    };

    template<u64 N>
    class Vecf : private Vec<f64, N>
    {
    public:
        Vecf() = default;
        explicit Vecf(Vecf const& _rhs) :
            Vec<f64, 2>(_rhs) {}
        Vecf(f64 const* ap, u64 count = N)
        {
            this->data = new f64[N];
            for (auto i = 0; i < N; ++i)
            {
                this->data[i] = ap[i];
            }
        }

        ~Vecf() { delete[] this->data; }

        auto GetData() const -> f64* { return this->data; }

        auto operator=(Vecf const& _rhs) -> Vecf&
        {
            std::memcpy(this->data, _rhs.GetData(), N * sizeof(f64));
            return *this;
        }
        auto operator=(f64 const* ap) -> Vecf&
        {
            std::memcpy(this->data, ap, N * sizeof(f64));
            return *this;
        }

        auto operator[](u64 i) -> f64& { return this->data[i]; }
        auto operator[](u64 i) const -> f64 { return this->data[i]; }

        auto operator+(f64 const& _rhs) -> Vecf
        {
            Vecf<N> v = new Vecf<N>(*this);
            for (auto i = 0; i < N; ++i)
            {
                v[i] = v[i] + _rhs;
            }
            return *v;
        }
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
        explicit Vec2f(Vec2f const& _rhs)
        {
            std::memcpy(this->data, _rhs.data, 2 * sizeof(f64));
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
        Vec3f(Vec3f const& _rhs)
        {
            std::memcpy(this->data, _rhs.data, 3 * sizeof(f64));
        }
        Vec3f(f64 _x, f64 _y, f64 _z)
        {
            this->data[0] = _x;
            this->data[1] = _y;
            this->data[2] = _z;
        }
    };

    class Vec4f
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
        Vec4f(Vec4f const& _rhs)
        {
            std::memcpy(this->data, _rhs.data, 4 * sizeof(f64));
        }
        Vec4f(f64 _x, f64 _y, f64 _z, f64 _w)
        {
            this->data[0] = _x;
            this->data[1] = _y;
            this->data[2] = _z;
            this->data[3] = _w;
        }

        ~Vec4f() { delete[] this->data; }

        auto operator[](u64 i) -> f64& { return this->data[i]; }
        auto operator[](u64 i) const -> f64 { return this->data[i]; }
        auto operator=(Vec4f const& _rhs) -> Vec4f&
        {
            std::memcpy(this->data, _rhs.data, 4 * sizeof(f64));
            return *this;
        }
        auto operator+(Vec4f const& _rhs) -> Vec4f { return { this->data[0] + _rhs.data[0], this->data[1] + _rhs.data[1], this->data[2] + _rhs.data[2], this->data[3] + _rhs.data[3] }; }

        auto operator-(Vec4f const& _rhs) -> Vec4f { return { this->data[0] - _rhs.data[0], this->data[1] - _rhs.data[1], this->data[2] - _rhs.data[2], this->data[3] - _rhs.data[3] }; }

        auto operator*(f64 _rhs) -> Vec4f { return { this->data[0] * _rhs, this->data[1] * _rhs, this->data[2] * _rhs, this->data[3] * _rhs }; }

        auto operator/(f64 _rhs) -> Vec4f { return { this->data[0] / _rhs, this->data[1] / _rhs, this->data[2] / _rhs, this->data[3] / _rhs }; }
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
        Vec16(Vec<f64, 16>& _rhs) :
            Vec16() { this->data = _rhs.GetData(); }
        Vec16(Vec<f64, 16> const& _rhs) { *data = *_rhs.GetData(); }
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
        int* ptr{};
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
            *ptr = 0;
            std::fill(data, data + 16, 0.0);
        };
        Quaternion(const Quaternion& rhs) :
            ptr(rhs.ptr),
            Vec16(rhs)
        {
            std::copy(rhs.GetData(), rhs.GetData() + 16, data);
        }
        explicit Quaternion(const f64 (&src)[16]) :
            Vec16(src[0], src[1], src[2], src[3], src[4], src[5], src[6], src[7], src[8], src[9], src[10], src[11], src[12], src[13], src[14], src[15])
        {
            *ptr = 0;
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

        auto Add(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion result;
            for (u32 i = 0; i < 4; ++i)
            {
                result[i] = data[i] + rhs[i];
            }
            return result;
        }

        auto Sub(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion result;
            for (u32 i = 0; i < 4; ++i)
            {
                result[i] = data[i] - rhs[i];
            }
            return result;
        }
        auto Mul(const Vec4f& rhs) const -> Vec4f
        {
            Vec4f result;
            for (u32 i = 0; i < 4; ++i)
            {
                result[i] = data[i * 4] * rhs[0] + data[i * 4 + 1] * rhs[1] + data[i * 4 + 2] * rhs[2] + data[i * 4 + 3] * rhs[3];
            }
            return result;
        }
        auto Mul(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion result{};
            for (u32 i = 0; i < 4; ++i)
            {
                for (u32 j = 0; j < 4; ++j)
                {
                    result.data[i * 4 + j] = data[i * 4] * rhs.data[j] + data[i * 4 + 1] * rhs.data[j + 4] + data[i * 4 + 2] * rhs.data[j + 8] + data[i * 4 + 3] * rhs.data[j + 12];
                }
            }

            return result;
        }
        auto Div(const Quaternion& rhs) const -> Quaternion
        {
            return Mul(rhs.Inverse());
        }
        auto Div(const Vec4f& rhs) const -> Vec4f
        {
            Quaternion inv = Inverse();
            return inv.Mul(rhs);
        }
        auto Inverse() const -> Quaternion
        {
            Quaternion result;
            result.data[0] = data[0];
            result.data[1] = -data[1];
            result.data[2] = -data[2];
            result.data[3] = -data[3];
            result.data[4] = data[4];
            result.data[5] = -data[5];
            result.data[6] = -data[6];
            result.data[7] = -data[7];
            result.data[8] = data[8];
            result.data[9] = -data[9];
            result.data[10] = -data[10];
            result.data[11] = -data[11];
            result.data[12] = data[12];
            result.data[13] = -data[13];
            result.data[14] = -data[14];
            result.data[15] = -data[15];
            return result;
        }

        static auto Rotate(const Quaternion q, Vec4f& axis, Face face)
            -> Quaternion
        {
            f64 a = Acos(axis.w) / ((axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2] + axis[3] * axis[3]) * 2.0);
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

            Quaternion result = Quaternion(&axis.x, &axis.y, &axis.z, &axis.w);
            result *= Quaternion(&dv.x, &dv.y, &dv.z, &dv.w);
            return Transform(result, axis);
        }

        static auto Transform(const Quaternion& q, const Vec4f& v) -> Quaternion
        {
            return Quaternion{ { { q.data[0] * v.x + q.data[1] * v.y + q.data[2] * v.z },
                                 { q.data[1] * v.x - q.data[0] * v.y - q.data[3] * v.z }, //
                                 { q.data[2] * v.x - q.data[3] * v.y + q.data[0] * v.z }, //
                                 { q.data[3] * v.x + q.data[2] * v.y - q.data[1] * v.z } } };
        }

        static auto Rotate(const Quaternion& q, const Vec4f& v, f64 angle) -> Quaternion
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
        auto Dot(const Quaternion& rhs, const Vec4f& t) const -> f64
        {
            return data[0] * rhs.data[0] + data[1] * rhs.data[1] + data[2] * rhs.data[2] + data[3] * rhs.data[3] + t.x * rhs.data[0] + t.y * rhs.data[1] + t.z * rhs.data[2] + t.w * rhs.data[3] + t.x * rhs.data[0] + t.y * rhs.data[1] + t.z * rhs.data[2] + t.w * rhs.data[3];
        }
        auto LengthSquared() const -> f64 { return Dot(*this, Vec4f(data[0], data[1], data[2], data[3])); }

        auto Length() const -> f64 { return origin::Sqrt(LengthSquared()); }
        auto Translate(const Quaternion& q, const Vec4f& t) -> Quaternion
        {
            Quaternion result;
            for (u32 i = 0; i < 4; ++i)
            {
                result.data[i] = q.data[i] + result.Dot(q, t);
            }
            return result;
        }

        explicit operator Quaternion*()
        {
            return this;
        }

        auto operator=(f64 const* _rhs) -> Quaternion&
        {
            ;
            std::memcpy(this->data, _rhs, 16 * sizeof(f64));
            return *this;
        }
        auto operator=(Quaternion&& _rhs) noexcept -> Quaternion&
        {
            *this->data = *_rhs.data;
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
        auto operator*=(const Quaternion& _rhs) noexcept -> Quaternion { return *this = this->Mul(_rhs); }
        auto operator/=(const Quaternion& _rhs) noexcept -> Quaternion { return *this = this->Div(_rhs); }
        auto operator+=(const Quaternion& _rhs) noexcept -> Quaternion { return *this = this->Add(_rhs); }
        auto operator-=(const Quaternion& _rhs) noexcept -> Quaternion { return *this = this->Sub(_rhs); }
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

        auto operator!=(const Quaternion& _rhs) const -> bool
        {
            return !(*this == _rhs);
        }
    }; // namespace origin
} // namespace origin