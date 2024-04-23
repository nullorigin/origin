#pragma once
#include "Basic.hpp"
#include "Message.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
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
        T data[N];

    public:
        Vec<T, N>() { memset(this->data, 0, sizeof(T) * N); }
        explicit Vec<T, N>(T* data) :
            data{} { std::copy(this->data, this->data + N, data); }
        auto operator=(const Vec& /*unused*/) -> Vec& { return *this; };
        auto operator=(Vec&& /*unused*/) noexcept -> Vec& { return *this; };
        Vec(const Vec& /*unused*/) { memset(this->data, 0, sizeof(T) * N); };
        Vec(Vec&& /*unused*/) noexcept :
            data{} { memset(this->data, 0, sizeof(T)); };
        constexpr auto GetData(u64 index) const -> T { return this->data[index]; }
        constexpr T* GetData() { return this->data; }
        constexpr const T* GetData() const { return this->data; }
        constexpr auto SetData(u64 index, T value) -> void { this->data[index] = value; }
        constexpr auto SetData(T* value) -> void { *this->data = *value; }
        constexpr auto SizeConvert(Mem::Unit _mu = Mem::Unit::BYTE) const -> u64
        {
            return N * sizeof(T) << static_cast<u8>(_mu);
        }
        constexpr auto Size() -> u64 { return N; }
        constexpr auto Find(T min, T max, u64& index) -> T
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            const T* dataEnd = this->data + (N & ~(sizeof(u64) - 1));
            u64 mask = ((min - T{}) ^ (max - T{})) >> 63;
            for (; this->data != dataEnd; this->data += sizeof(u64))
            {
                u64 v = *reinterpret_cast<const u64*>(this->data) & mask;
                u64 index = __builtin_ctzll(v);
                if (index < sizeof(u64) * 8)
                {
                    return this->data[index];
                }
            }
            index = N;
            for (; this->data != (this->data + N); ++data, ++index)
            {
                if (*data >= min && *data <= max)
                {
                    return *data;
                }
            }
            return T(0);
        }
        constexpr auto Find(T min, T max) -> Vec<T, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<T, N> ret{};
            u32 index = 0;
            const T* dataEnd = this->data + (N & ~(sizeof(u64) - 1));
            for (; this->data != dataEnd; this->data += sizeof(u64))
            {
                u64 v = *reinterpret_cast<const u64*>(this->data);
                u64 mask = ((min - v) ^ (v - max)) >> 63;
                u64 r = (v & mask) + (((v ^ mask) & v) >> 1);
                ret[index++] = *reinterpret_cast<T*>(&r);
            }
            for (; index < N; ++index)
            {
                if (this->data[index] >= min && this->data[index] <= max)
                {
                    ret[index] = this->data[index];
                }
            }
            return ret;
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

        constexpr auto Replace(T min, T max, T value) -> Vec<T, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            const T* const end = this->data + N;
            const T* lhs = this->data;
            T* rhs = this->data;
            for (; lhs != end; ++lhs, ++rhs)
            {
                *rhs = (*lhs < min || *lhs > max) ? *lhs : value;
            }
            return *this;
        }

        constexpr auto Index(Vec<T, N> value) -> Vec<u64, N>
        {
            Vec<u64, N> ret{};

            const T* valData = value.data;
            const T* dataEnd = this->data + N;
            u64* retData = ret.data;

            if constexpr (std::is_same_v<T, u64>)
            {
                const u64* data = reinterpret_cast<const u64*>(this->data);
                const u64* valDataEnd = reinterpret_cast<const u64*>(valData + N);
                for (; valData != valDataEnd; ++valData, ++retData)
                {
                    *retData = static_cast<u64>(std::distance(this->data, std::find(this->data, dataEnd, *valData)));
                }
            }
            else
            {
                for (const T* it = this->data; it != dataEnd; ++it, ++retData)
                {
                    *retData = static_cast<u64>(std::distance(valData, std::find(valData, valData + N, *it)));
                }
            }
            return ret;
        }

        constexpr auto Index(Vec<T, N> value, T min, T max) -> Vec<u64, N>
        {
            Vec<u64, N> ret{};
            if (!this->data)
            {
                DBG("Null pointer reference", ERROR);
                return ret;
            }
            u64* retData = ret.data;
            const T* valData = value.data;
            const T* dataEnd = this->data + N;

            for (; this->data != dataEnd; ++this->data, ++valData, ++retData)
            {
                if (*this->data >= min && *this->data <= max && *this->data == *valData)
                {
                    *retData = this->data - this->data;
                }
            }
            return ret;
        }

        auto Index(T value, T threshold) -> Vec<u64, N>
        {
            Vec<u64, N> ret{};
            if (!this->data)
            {
                DBG("Null pointer reference", ERROR);
                return ret;
            }
            T lt = value - threshold;
            T gt = value + threshold;
            u64* retData = ret.data;
            const T* dataEnd = this->data + N;
            for (const T* it = this->data; it != dataEnd; ++it, ++retData)
            {
                T cur = *it;
                if ((cur >= lt) && (cur <= gt))
                {
                    *retData = it - this->data;
                }
            }
            return ret;
        }

        explicit Vec<T, N>(const Vec<T, N>* _rhs) :
            data(new T[N]()) { *this->data = _rhs; }
        explicit Vec<T, N>(const T* _rhs) :
            data(new T[N]) { *this->data = _rhs; }
        explicit Vec<T, N>(T* _rhs[N]) :
            data(new T[N]) { *this->data = _rhs; }
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
            std::memcpy(this->data, _rhs, sizeof(T) * N);
            return *this;
        }
        auto Set(const Vec<T, N>& _rhs) -> Vec<T, N>
        {
            std::memcpy(this->data, _rhs.data, sizeof(T) * N);
            return *this;
        }

        auto Set(T* _rhs[N]) -> Vec<T, N>
        {
            std::copy(_rhs, _rhs + N, this->data);
            return *this;
        }
        auto Get() -> Vec<T, N> { return this->data; }
        auto Get(u32 _index) -> Vec<T, N> { return this->data[_index]; }
        auto Add(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            return __builtin_elementwise_add_sat(ret.data, _rhs.data);
        }

        auto Sub(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                __builtin_elementwise_sub_sat(ret.data[i], _rhs.data[i]);
            }
            return ret;
        }
        auto Mul(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            Vec<T, N> ret{ this->data }; // avoid copying elements
            for (u32 i = 0; i < N; i += sizeof(T))
            {
                *reinterpret_cast<T*>(ret.data + i) *=
                    *reinterpret_cast<const T*>(_rhs.data + i);
            }
            return ret;
        }

        auto Div(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret{};
            std::transform(this->data, this->data + N, _rhs.data, ret.data, [](T lhs, T rhs) { return lhs / rhs; });
            return ret;
        }

        auto Mod(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret;
            std::transform(this->data, this->data + N, _rhs.data, ret.data, std::modulus<T>());
            return ret;
        }

        auto And(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret;
            std::transform(this->data, this->data + N, _rhs.data, ret.data, std::bit_and<T>());
            return ret;
        }

        auto Or(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            Vec<T, N> ret;
            std::transform(this->data, this->data + N, _rhs.data, ret.data, std::bit_or<T>());
            return ret;
        }
        auto Xor(const Vec<T, N> _rhs) noexcept -> Vec<T, N>
        {
            Vec<T, N> ret;
            if (this->data && _rhs.data)
            {
                const T* lhs = this->data;
                const T* rhs = _rhs.data;
                T* retData = ret.data;
                for (u32 i = 0; i < N; i++)
                {
                    *retData++ = *lhs++ ^ *rhs++;
                }
            }
            return ret;
        }

        auto Neg() noexcept -> Vec<T, N>
        {
            Vec<T, N> ret{ this->data };
            for (T* it = ret.data; it != ret.data + N; ++it)
            {
                *it = -*it;
            }
            return ret;
        }
        auto Pow(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            Vec<T, N> ret;
            const T* src = this->data;
            T* dst = ret.data;
            for (u32 i = 0; i < N; i++, src++, dst++)
            {
                *dst = std::pow(*src, _rhs[i]);
            }
            return ret;
        }
        auto Swap(Vec<T, N> _rhs) -> Vec<T, N>
        {
            std::swap(this->data, _rhs.data);
            return *this;
        }
        auto Length() const -> T
        {
            T ret = 0;
            for (u32 i = 0; i < N; i++)
            {
                ret += this->data[i] * this->data[i];
            }
            return Sqrt(ret);
        }

        auto Dot(const Vec<T, N> _rhs) const -> T
        {
            T ret = 0;
            for (u32 i = 0; i < N; i++)
            {
                ret += this->data[i] * _rhs[i];
            }
            return ret;
        }
        auto LengthSq() const -> T { return Dot(*this); }
        auto Cross(const Vec<T, N> _rhs, const Vec<T, N> _rhs2) -> Vec<T, N>
        {
            const Vec<T, N>* src[3] = { this, &_rhs, &_rhs2 };
            T* dst = this->data;

            for (u32 i = 0; i < N; i += 3)
            {
                const auto s1 = src[i / 3]->data[i];
                const auto s2 = src[i / 3]->data[i + 1];
                const auto s3 = src[i / 3]->data[i + 2];
                const auto d1 = src[(i + 1) / 3]->data[i + 1];
                const auto d2 = src[(i + 2) / 3]->data[i];
                const auto d3 = src[(i + 2) / 3]->data[i + 2];

                dst[i] = s2 * d3 - s3 * d2;
                dst[i + 1] = s3 * d1 - s1 * d3;
                dst[i + 2] = s1 * d2 - s2 * d1;
            }
            return *this;
        }
        auto Abs() -> Vec<T, N>
        {
            Vec<T, N> ret{ this->data };
            T* dst = ret.data;
            for (u32 i = 0; i < N; i++, dst++)
            {
                *dst = origin::Abs(*dst);
            }
            return ret;
        }

        auto Sqrt() -> Vec<T, N>
        {
            Vec<T, N> ret{ this->data }; // Copy the this->data pointer
            std::transform(reinterpret_cast<const T*>(this->data),
                           reinterpret_cast<const T*>(this->data) + N,
                           reinterpret_cast<T*>(ret.data),
                           [](T x) { return origin::Sqrt(x); });
            return ret;
        }
        auto Lerp(const Vec<T, N> _rhs, const Vec<T, N> _exp) -> Vec<T, N>
        {
            T* retData = const_cast<T*>(this->data);
            if constexpr (std::is_same_v<T, f32>)
            {
                const f32* lhs = reinterpret_cast<const f32*>(this->data);
                const f32* rhs = reinterpret_cast<const f32*>(_rhs.data);
                const f32* exp = reinterpret_cast<const f32*>(_exp.data);
                for (u32 i = 0; i < N; i++, lhs++, rhs++, exp++, retData++)
                {
                    *retData = *lhs + (*exp * (*rhs - *lhs));
                }
            }
            else
            {
                const T* lhs = this->data;
                const T* rhs = _rhs.data;
                const T* exp = _exp.data;
                for (u32 i = 0; i < N; i++, lhs++, rhs++, exp++, retData++)
                {
                    *retData = fma(*exp, *rhs - *lhs, *lhs);
                }
            }
            return { retData };
        }

        auto Eq(const Vec<T, N> _rhs) noexcept -> Vec<bool, N>
        {
            return Vec<bool, N>{ this->data } == _rhs;
        }
        auto Neq(const Vec<T, N> _rhs) noexcept -> Vec<bool, N>
        {
            return Vec<bool, N>{ this->data } != _rhs;
        }

        auto Gt(const Vec<T, N> _rhs) -> Vec<bool, N>
        {
            Vec<bool, N> ret;
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            const T* lhs = this->data;
            const T* rhs = _rhs.data;
            std::transform(lhs, lhs + N, rhs, ret.data, std::greater<T>());
            return ret;
        }

        auto Gte(const Vec<T, N> _rhs) -> Vec<bool, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<bool, N> ret{ data, _rhs.data, std::greater_equal<T>() };
            return ret;
        }

        auto Lt(const Vec<T, N> _rhs) -> Vec<bool, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<bool, N> ret{ data, _rhs.data, std::less<T>() };
            return ret;
        }
        auto Lte(const Vec<T, N> _rhs) -> Vec<bool, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<bool, N> ret{ data, _rhs.data, std::less_equal<T>() };
            return ret;
        }

        auto Max(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            Vec<T, N> ret;
            const T* const end = ret.data + N;
            const T* data = this->data;
            const T* rhsData = _rhs.data;
            if (this->data && rhsData)
            {
                std::transform(this->data, this->data + N, rhsData, ret.data, std::max<T>());
                return ret;
            }
            DBG("Null pointer reference", ERROR);
        }
        auto Min(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            Vec<T, N> ret;
            const T* const end = ret.data + N;
            const T* lhs = this->data;
            const T* rhs = _rhs.data;
            T* retData = ret.data;
            if (lhs && rhs)
            {
                std::transform(lhs, lhs + N, rhs, retData, std::min<T>());
            }
            else
            {
                DBG("Null pointer reference", ERROR);
            }
            return ret;
        }
        auto Clamp(const T _min, const T _max) -> Vec<T, N>
        {
            T* retData = this->data ? this->data : (T*)alloca(N * sizeof(T));
            const T* const end = retData + N;
            const T* const minData = &_min;
            const T* const maxData = &_max;
            for (; retData != end; ++retData)
            {
                *retData = std::min(*std::max(minData, std::min(maxData, retData)), maxData[-1]);
            }
            return { retData, N };
        }
        auto Clamp(const Vec<T, N> _min, const Vec<T, N> _max) -> Vec<T, N>
        {
            Vec<T, N> ret;
            const T* minData = _min.data;
            const T* maxData = _max.data;
            T* retData = ret.data;
            if (this->data && minData && maxData)
            {
                for (u32 i = 0; i < N; ++i)
                {
                    retData[i] = origin::Clamp(this->data[i], minData[i], maxData[i]);
                }
            }
            else
            {
                DBG("Null pointer reference", ERROR);
            }
            return ret;
        }

        auto Rand(T _min, T _max) -> Vec<T, N>
        {
            if (_min > _max)
            {
                DBG("Min > Max", ERROR);
            }
            T diff = _max - _min;
            T scale = static_cast<T>(RAND_MAX) / diff;
            Vec<T, N> ret = *this;
            for (u64 i = 0; i < N; i++)
            {
                ret[i] = _min + (static_cast<T>(std::rand()) * scale);
            }
            return ret;
        }
        auto ShiftL(const Vec<T, N> _rhs) const -> Vec<T, N>
        {
            if (this->data == nullptr || _rhs.data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<T, N> ret;
            std::transform(this->data, this->data + N, _rhs.data, ret.data, [](T a, T b) { return a << b; });
            return ret;
        }

        auto ShiftR(const Vec<T, N> _rhs) const -> Vec<T, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<T, N> ret;
            std::transform(this->data, this->data + N, _rhs.data, ret.data, [](T a, T b) { return a >> b; });
            return ret;
        }
        auto Pow(const Vec<T, N> _rhs) const -> Vec<T, N>
        {
            if (this->data == nullptr || _rhs.data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<T, N> ret;
            try
            {
                for (u32 i = 0; i < N; i++)
                {
                    ret[i] = std::pow(this->data[i], _rhs[i]);
                }
            }
            catch (std::exception& e)
            {
                DBG(e.what(), ERROR);
            }
            return ret;
        }
        auto Lerp(const Vec<T, N> _rhs, u32 _exp) const -> Vec<T, N>
        {
            if (this->data == nullptr || _rhs.data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            const T* data = this->data;
            const T* rhsData = _rhs.data;
            T* retData = (T*)alloca(N * sizeof(T));

            for (u32 i = 0; i < N; i++)
            {
                retData[i] = this->data[i] + (rhsData[i] - this->data[i]) * _exp;
            }

            return Vec<T, N>(retData);
        }
        auto Lerp(const Vec<T, N> _rhs, const Vec<T, N> _exp) const -> Vec<T, N>
        {
            const T* data = this->data;
            const T* rhsData = _rhs.data;
            const T* expData = _exp.data;
            T* retData = (T*)alloca(N * sizeof(T));

            for (u32 i = 0; i < N; i++)
            {
                retData[i] = this->data[i] + (rhsData[i] - this->data[i]) * expData[i];
            }

            return Vec<T, N>(retData);
        }
        auto Clamp(const Vec<T, N> _min, const Vec<T, N> _max) const -> Vec<T, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }

            Vec<T, N> ret;
            const T* minData = _min.data;
            const T* maxData = _max.data;
            T* retData = ret.data;

            for (u32 i = 0; i < N; i++)
            {
                retData[i] = origin::Clamp(this->data[i], minData[i], maxData[i]);
            }

            return ret;
        }

        auto Clamp(const T _min, const T _max) const -> Vec<T, N>
        {
            Vec<T, N> ret;
            const T* d = this->data;
            T* r = ret.data;
            if (d == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            for (u32 i = 0; i < N; i++)
            {
                r[i] = origin::Clamp(d[i], _min, _max);
            }
            return ret;
        }

        auto Abs() const noexcept -> Vec<T, N>
        {
            Vec<T, N> ret;
            T* r = ret.data;
            const T* d = this->data;
            if (d == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            for (u32 i = 0; i < N; i++)
            {
                r[i] = d[i] < T(0) ? -d[i] : d[i];
            }
            return ret;
        }
        auto Sign() const noexcept -> Vec<T, N>
        {
            Vec<T, N> ret;
            const T* d = this->data;
            T* r = ret.data;
            if (d == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            for (u32 i = 0; i < N; i++)
            {
                r[i] = origin::Sign(d[i]);
            }
            return ret;
        }
        auto Sqrt() const -> Vec<T, N>
        {
            Vec<T, N> ret;
            const T* d = this->data;
            T* r = ret.data;
            if (d == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            for (u32 i = 0; i < N; i++)
            {
                r[i] = origin::Sqrt(d[i]);
            }
            return ret;
        }
        auto Sq() const -> Vec<T, N>
        {
            Vec<T, N> ret;
            T* r = ret.data;
            const T* d = this->data;
            if (d == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            for (u32 i = 0; i < N; i++)
            {
                r[i] = d[i] * d[i];
            }
            return ret;
        }
        auto RSqrt() const -> Vec<T, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            Vec<T, N> ret = *this;
            for (u32 i = 0; i < N; i++)
            {
                ret[i] = (T)(1.0 / sqrt(double(ret[i])));
            }
            return ret;
        }

        auto Rand(T _min, T _max) const -> Vec<T, N>
        {
            if (this->data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            const T range = _max - _min;
            const T scale = (T)(RAND_MAX / range);
            for (u32 i = 0; i < N; i++)
            {
                this->data[i] = _min + (T)(std::rand() * scale);
            }
            return *this;
        }
        auto IsNan(bool set_zero = false) const noexcept -> bool
        {
            if (this->data == nullptr)
            {
                return false;
            }
            bool result = false;
            for (u32 i = 0; i < N; i++)
            {
                if (isnan(this->data[i][0]))
                {
                    result = true;
                    if (set_zero)
                    {
                        this->data[i][0] = 0;
                    }
                    break;
                }
            }
            return result;
        }
        auto IsNum() const -> bool { return !IsNan(); }
        inline auto operator[](u32 index) -> T& { return this->data[index]; }
        auto operator=(T* _data) -> Vec<T, N>&
        {
            if (_data == nullptr)
            {
                DBG("Null pointer reference", ERROR);
            }
            std::memcpy(this->data, _data, N * sizeof(T));
            return *this;
        }
        auto operator=(const Vec<T, N>* _rhs) -> Vec<T, N>
        {
            if (_rhs == nullptr)
            {
                throw std::runtime_error("Null pointer reference");
            }
            for (u32 i = 0; i < N; i++)
            {
                this->data[i] = _rhs[i];
            }
            return this;
        }
        auto operator[](u32 i) const -> T
        {
            if (i < N)
            {
                return this->data[i];
            }
            return 0;
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
        auto operator<<(const T _rhs) -> Vec<T, N> { return this->ShiftL(_rhs); }
        auto operator>>(const T _rhs) -> Vec<T, N> { return this->ShiftR(_rhs); }
        auto operator==(const T _rhs) -> Vec<bool, N> { return this->Eq(_rhs); }
        auto operator!=(const T _rhs) -> Vec<bool, N> { return this->Neq(_rhs); }
        auto operator<(const T _rhs) -> Vec<bool, N> { return this->Lt(_rhs); }
        auto operator<=(const T _rhs) -> Vec<bool, N> { return this->Lte(_rhs); }
        auto operator>(const T _rhs) -> Vec<bool, N> { return this->Gt(_rhs); }
        auto operator>=(const T _rhs) -> Vec<bool, N> { return this->Gte(_rhs); }
        auto operator-() -> Vec<T, N> { return Neg(); }
        auto operator~() const -> Vec<T, N> { return Vec<T, N>(~*this); }
        auto operator+=(const T _rhs) -> Vec<T, N>
        {
            *this = this->Add(_rhs);
            return *this;
        }
        auto operator-=(const T _rhs) -> Vec<T, N>
        {
            *this = this->Sub(_rhs);
            return *this;
        }
        auto operator*=(const T _rhs) -> Vec<T, N>
        {
            *this = this->Mul(_rhs);
            return *this;
        }
        auto operator/=(const T _rhs) -> Vec<T, N>
        {
            *this = this->Div(_rhs);
            return *this;
        }
        auto operator%=(const T _rhs) -> Vec<T, N>
        {
            *this = this->Mod(_rhs);
            return *this;
        }
        auto operator&=(const T& _rhs) -> Vec<T, N>
        {
            *this = this->And(_rhs);
            return *this;
        }
        auto operator|=(const T& _rhs) -> Vec<T, N>
        {
            *this = this->Or(_rhs);
            return *this;
        }
        auto operator^=(const T& _rhs) -> Vec<T, N>
        {
            *this = this->Pow(_rhs);
            return *this;
        }
        auto operator<<=(const T& _rhs) -> Vec<T, N>
        {
            *this = this->ShiftL(_rhs);
            return *this;
        }
        auto operator>>=(const T& _rhs) -> Vec<T, N>
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
        auto operator%=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = Mod(_rhs);
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
            *this = ShiftL(_rhs);
            return *this;
        };
        auto operator>>=(const Vec<T, N> _rhs) -> Vec<T, N>
        {
            *this = ShiftR(_rhs);
            return *this;
        };
    };
    class Vec2 : public Vec<f64, 2>
    {
    public:
        union
        {
            f64* data = new f64[2];
            struct
            {
                f64 x;
                f64 y;
            };
        };
        explicit Vec2(Vec<f64, 2>& _rhs) { this->data = _rhs.GetData(); };
        explicit Vec2(const Vec<f64, 2>& _rhs)
        {
            std::memcpy(this->data, _rhs.GetData(), sizeof(f64) * 2);
        }
        explicit Vec2(f64 _x = 0, f64 _y = 0)
        {
            x = _x;
            y = _y;
        }
    };
    class Vec3 : public Vec<f64, 3>
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
            };
        };
        Vec3() = default;
        explicit Vec3(Vec<f64, 3>& _rhs) { this->data = _rhs.GetData(); }
        explicit Vec3(Vec<f64, 3> const& _rhs) { *data = *_rhs.GetData(); }
        explicit Vec3(f64 _x, f64 _y, f64 _z) :
            x(_x), y(_y), z(_z) {}
    };
    class Vec4 : public Vec<f64, 4>
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
            };
        };
        explicit Vec4(Vec<f64, 4>& _rhs) { this->data = _rhs.GetData(); }
        explicit Vec4(const Vec<f64, 4>& _rhs) { *data = *_rhs.GetData(); }
        explicit Vec4(f64 _x = 0, f64 _y = 0, f64 _z = 0, f64 _w = 0)
        {
            if (this->data == nullptr)
            {
                DBG("Vec4 ctor: data is nullptr", ERROR);
            }
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }
    };
    class Vec16 : public Vec<f64, 16>
    {
        union
        {
            f64* data = new f64[16];
            struct
            {
                f64 x[4];
                f64 y[4];
                f64 z[4];
                f64 w[4];
            };
        };

    public:
        Vec16() = default;
        explicit Vec16(Vec<f64, 16>& _rhs) :
            Vec16() { this->data = _rhs.GetData(); }
        explicit Vec16(Vec<f64, 16> const& _rhs) { *data = *_rhs.GetData(); }
        explicit Vec16(const f64 _x[4], const f64 _y[4], const f64 _z[4], const f64 _w[4])
        {
            *x = *_x;
            *y = *_y;
            *z = *_z;
            *w = *_w;
        }
    };
    class Quaternion : public Vec16
    {
        union
        {
            f64* data = new f64[16];
            struct
            {
                f64 x1;
                f64 y1;
                f64 z1;
                f64 w1;
                f64 x2;
                f64 y2;
                f64 z2;
                f64 w2;
                f64 x3;
                f64 y3;
                f64 z3;
                f64 w3;
                f64 x4;
                f64 y4;
                f64 z4;
                f64 w4;
            };
        };

    public:
        explicit Quaternion(Vec<f64, 4>& _rhs)
        {
            if (_rhs.GetData() == nullptr)
            {
                DBG("Null pointer reference in Quaternion constructor.", ERROR);
            }
            std::copy(_rhs.GetData(), _rhs.GetData() + 4, data);
        }
        explicit Quaternion(f64 x[4], f64 y[4], f64 z[4], f64 w[4]) :
            Vec16(x, y, z, w) {}
        explicit Quaternion(f64 q1x = 0, f64 q1y = 0, f64 q1z = 0, f64 q1w = 0, f64 q2x = 0, f64 q2y = 0, f64 q2z = 0, f64 q2w = 0, f64 q3x = 0, f64 q3y = 0, f64 q3z = 0, f64 q3w = 0, f64 q4x = 0, f64 q4y = 0, f64 q4z = 0, f64 q4w = 0)
        {
            __m128d c0 = _mm_set_pd(q1z, q1x);
            __m128d c1 = _mm_set_pd(q1w, q2x);
            __m128d c2 = _mm_set_pd(q2z, q2y);
            __m128d c3 = _mm_set_pd(q2w, q3x);
            __m128d c4 = _mm_set_pd(q3z, q3y);
            __m128d c5 = _mm_set_pd(q3w, q4x);
            __m128d c6 = _mm_set_pd(q4z, q4y);
            __m128d c7 = _mm_set_pd(q4w, 0);

            _mm_storeu_pd(&this->data[0], c0);
            _mm_storeu_pd(&this->data[2], c1);
            _mm_storeu_pd(&this->data[4], c2);
            _mm_storeu_pd(&this->data[6], c3);
            _mm_storeu_pd(&this->data[8], c4);
            _mm_storeu_pd(&this->data[10], c5);
            _mm_storeu_pd(&this->data[12], c6);
            _mm_storeu_pd(&this->data[14], c7);
        }
        explicit Quaternion(const Vec4 _q[4]) :
            Quaternion(_q[0].x, _q[0].y, _q[0].z, _q[0].w, _q[1].x, _q[1].y, _q[1].z, _q[1].w, _q[2].x, _q[2].y, _q[2].z, _q[2].w, _q[3].x, _q[3].y, _q[3].z, _q[3].w)
        {
            __m128d c0 = _mm_loadu_pd(&_q[0].x);
            __m128d c1 = _mm_loadu_pd(&_q[1].x);
            __m128d c2 = _mm_loadu_pd(&_q[2].x);
            __m128d c3 = _mm_loadu_pd(&_q[3].x);
            _mm_store_pd(&this->data[0], c0);
            _mm_store_pd(&this->data[2], c1);
            _mm_store_pd(&this->data[4], c2);
            _mm_store_pd(&this->data[6], c3);
        }

        auto operator*(Quaternion& rhs) const -> Quaternion
        {
            __m128d c0 = _mm_load_pd(&this->data[0]);
            __m128d c1 = _mm_load_pd(&this->data[2]);
            __m128d c2 = _mm_load_pd(&rhs.data[0]);
            __m128d c3 = _mm_load_pd(&rhs.data[2]);
            __m128d c4 = _mm_mul_pd(c0, c2);
            __m128d c5 = _mm_mul_pd(c1, c3);
            __m128d c6 = _mm_mul_pd(c0, c3);
            __m128d c7 = _mm_mul_pd(c1, c2);
            c4 = _mm_add_pd(c4, c5);
            c6 = _mm_xor_pd(c6, _mm_set_pd(-0.0, 0.0));
            c7 = _mm_xor_pd(c7, _mm_set_pd(-0.0, 0.0));
            c6 = _mm_add_pd(c6, c7);
            _mm_store_pd(&this->data[0], c4);
            _mm_store_pd(&this->data[2], c6);
            return *this;
        }

        auto operator*(f64 scale) const -> Quaternion
        {
            __m128d c0 = _mm_load_pd(&this->data[0]);
            __m128d c1 = _mm_load_pd(&this->data[2]);
            __m128d c2 = _mm_mul_pd(c0, _mm_set1_pd(scale));
            __m128d c3 = _mm_mul_pd(c1, _mm_set1_pd(scale));
            _mm_store_pd(&this->data[0], c2);
            _mm_store_pd(&this->data[2], c3);
            return *this;
        }

        auto operator==(const Quaternion& _rhs) const -> bool
        {
            __m128d c0 = _mm_load_pd(&this->data[0]);
            __m128d c1 = _mm_load_pd(&_rhs.data[0]);
            __m128d c2 = _mm_cmpeq_pd(c0, c1);
            return _mm_movemask_pd(c2) == 3;
        }

        auto operator!=(const Quaternion& _rhs) const -> bool
        {
            return !(*this == _rhs);
        }

        auto Mul(const Vec4& rhs) const -> Vec4
        {
            __m128d c0 = _mm_load_pd(&this->data[0]);
            __m128d c1 = _mm_load_pd(&this->data[2]);
            __m128d c2 = _mm_load_pd(&this->data[4]);
            __m128d c3 = _mm_load_pd(&this->data[6]);

            __m128d a0 = _mm_mul_pd(c0, _mm_set1_pd(rhs.x));
            __m128d a1 = _mm_mul_pd(c1, _mm_set1_pd(rhs.y));
            __m128d a2 = _mm_mul_pd(c2, _mm_set1_pd(rhs.z));
            __m128d a3 = _mm_mul_pd(c3, _mm_set1_pd(rhs.w));

            __m128d r0 = _mm_add_pd(a0, a1);
            __m128d r1 = _mm_add_pd(a2, a3);
            __m128d r2 = _mm_add_pd(r0, r1);

            Vec4 result{};
            _mm_storeu_pd(&result.x, r2);
            return result;
        }

        auto Mul(const Quaternion& rhs) const -> Vec3
        {
            __m128d c0 = _mm_set_pd(this->data[3], this->data[0]);
            __m128d c1 = _mm_set_pd(this->data[7], this->data[4]);
            __m128d c2 = _mm_set_pd(this->data[11], this->data[8]);
            __m128d c3 = _mm_set_pd(rhs.data[3], rhs.data[0]);

            __m128d a0 = _mm_mul_pd(c0, c3);
            __m128d a1 = _mm_mul_pd(c1, c3);
            __m128d a2 = _mm_mul_pd(c2, c3);

            __m128d b0 = _mm_unpackhi_pd(a0, a1);
            __m128d b1 = _mm_unpacklo_pd(a0, a1);
            __m128d b2 = _mm_unpackhi_pd(a2, _mm_setzero_pd());

            __m128d r0 = _mm_add_pd(b0, b1);
            __m128d r1 = _mm_add_pd(b2, _mm_setzero_pd());

            Vec3 result{};
            _mm_storeu_pd(&result.x, r0);
            _mm_storeu_pd(&result.z, r1);
            return result;
        }

        auto Mul(const Vec16& rhs) const -> Quaternion
        {
            Quaternion result;
            __m128d c0 = _mm_setzero_pd();
            __m128d c1 = _mm_setzero_pd();
            __m128d c2 = _mm_setzero_pd();
            __m128d c3 = _mm_setzero_pd();

            for (u64 i = 0; i < 4; i++)
            {
                c0 = _mm_add_pd(
                    c0, _mm_mul_pd(_mm_load_pd(&this->data[i]), _mm_set1_pd(rhs[i])));
                c1 = _mm_add_pd(c1, _mm_mul_pd(_mm_load_pd(&this->data[i * 4 + 2]), _mm_set1_pd(rhs[i + 4])));
                c2 = _mm_add_pd(c2, _mm_mul_pd(_mm_load_pd(&this->data[i * 4 + 4]), _mm_set1_pd(rhs[i + 8])));
                c3 = _mm_add_pd(c3, _mm_mul_pd(_mm_load_pd(&this->data[i * 4 + 6]), _mm_set1_pd(rhs[i + 12])));
            }

            _mm_store_pd(&result[0], c0);
            _mm_store_pd(&result[2], c1);
            _mm_store_pd(&result[4], c2);
            _mm_store_pd(&result[6], c3);

            return result;
        }

        auto Divide(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion result;
            for (u32 i = 0; i < 4; i++)
            {
                result.data[i] = this->data[i] / rhs.data[0] - this->data[i + 4] / rhs.data[1] -
                                 this->data[i + 8] / rhs.data[2] - this->data[i + 12] / rhs.data[3];
            }
            return result;
        }
        auto Add(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion result;
            for (u32 i = 0; i < 4; i++)
            {
                result.data[i] = this->data[i] + rhs.data[i];
            }
            return result;
        }

        auto Sub(const Quaternion& rhs) const -> Quaternion
        {
            Quaternion result;
            for (u32 i = 0; i < 4; i++)
            {
                result.data[i] = this->data[i] - rhs.data[i];
            }
            return result;
        }
        static auto Rotate(Quaternion q, const Vec4& axis, Face face)
            -> Quaternion
        {
            f64 a = acos(axis.w) / (axis.LengthSq() * 2.0);
            Vec4 dv;
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
            }
            q = Quaternion(0, axis.x, axis.y, axis.z);
            q *= Quaternion(0, dv.x, dv.y, dv.z);
            return Transform(q, axis);
        }

        static auto Transform(Quaternion& q, const Vec4& v) -> Quaternion
        {
            return Quaternion{ q.data[3] * v.x + q.data[1] * v.y + q.data[2] * v.z -
                                   q.data[0] * v.x - q.data[4] * v.y - q.data[5] * v.z,
                               q.data[0] * v.x + q.data[4] * v.y + q.data[5] * v.z -
                                   q.data[3] * v.x - q.data[7] * v.y - q.data[8] * v.z,
                               q.data[6] * v.x + q.data[7] * v.y + q.data[8] * v.z -
                                   q.data[0] * v.x - q.data[1] * v.y - q.data[2] * v.z,
                               0 };
        }

        static auto Rotate(Quaternion& q, const Vec4& v, f64 angle) -> Quaternion
        {
            f64 s{ 0 };
            f64 c{ 0 };
            sincos(angle * PI / 180.0, &s, &c);
            f64 qx = q.data[3] * v.x + q.data[1] * v.y - q.data[2] * v.z;
            f64 qy = q.data[3] * v.y + q.data[2] * v.x - q.data[0] * v.z;
            f64 qz = q.data[3] * v.z + q.data[0] * v.y - q.data[1] * v.x;
            Quaternion ret = Quaternion{
                qx * s + q.data[0] * v.x - q.data[1] * v.y - q.data[2] * v.z, //
                qy * s + q.data[1] * v.x + q.data[2] * v.y - q.data[0] * v.z, //
                qz * s + q.data[2] * v.x + q.data[0] * v.y - q.data[1] * v.z,
                q.data[0] * v.x + q.data[1] * v.y + q.data[2] * v.z
            };
            return Quaternion{ 0, 0, 0, c } * q * ret;
        }
        static auto Translate(const Quaternion& q, const Vec3& v) -> Quaternion
        {
            Quaternion ret;
            ret.data[0] =
                q.data[0] + v.x * q.data[3] + v.y * q.data[2] - v.z * q.data[1];
            ret.data[1] =
                q.data[1] + v.x * q.data[2] + v.y * q.data[3] - v.z * q.data[0];
            ret.data[2] =
                q.data[2] + v.x * q.data[0] + v.y * q.data[1] - v.z * q.data[2];
            ret.data[3] =
                q.data[3] + v.x * q.data[1] + v.y * q.data[0] - v.z * q.data[3];
            return ret;
        }

        static auto Translate(const Quaternion& q, const Vec3& v, Face face)
            -> Quaternion
        {
            if (q.data == nullptr || v.data == nullptr)
            {
                throw std::runtime_error{
                    "Null pointer reference in Quaternion translation"
                };
            }
            u32 idx = static_cast<int>(face) * 4;
            f64 x =
                q.data[3 + idx] * v.x + q.data[7 + idx] * v.y + q.data[11 + idx] * v.z;
            q.data[3] +=
                q.data[idx] * v.x + q.data[1 + idx] * v.y + q.data[2 + idx] * v.z;
            q.data[7] +=
                q.data[1 + idx] * v.x - q.data[idx] * v.y - q.data[2 + idx] * v.z;
            q.data[11] +=
                q.data[2 + idx] * v.x - q.data[1 + idx] * v.y + q.data[idx] * v.z;
            q.data[15] -=
                q.data[0 + idx] * v.x - q.data[1 + idx] * v.y - q.data[2 + idx] * v.z;
            return q;
        }

        auto operator=(const Quaternion& _rhs) noexcept -> Quaternion
        {
            std::memcpy(this->data, _rhs.data, 16 * sizeof(f64));
            return *this;
        }
        auto operator*(Quaternion& rhs) -> Quaternion
        {
            Quaternion result{};
            f64* lhsData = this->data;
            f64* rhsData = rhs.data;
            f64* resData = result.data;
            for (u64 i = 0; i < 4; i++)
            {
                f64 r0 = rhsData[i];
                f64 r1 = rhsData[i + 4];
                f64 r2 = rhsData[i + 8];
                f64 r3 = rhsData[i + 12];
                resData[i * 4] =
                    lhsData[0] * r0 + lhsData[1] * r1 + lhsData[2] * r2 + lhsData[3] * r3;
                resData[i * 4 + 1] =
                    lhsData[1] * r0 + lhsData[4] * r1 + lhsData[5] * r2 + lhsData[7] * r3;
                resData[i * 4 + 2] = lhsData[2] * r0 + lhsData[5] * r1 + lhsData[8] * r2 +
                                     lhsData[11] * r3;
                resData[i * 4 + 3] = lhsData[3] * r0 + lhsData[7] * r1 +
                                     lhsData[11] * r2 + lhsData[15] * r3;
            }
            return result;
        }

        explicit operator f64*() const
        {
            f64* ret = new f64[16]{ this->data[0], this->data[1], this->data[2], this->data[3], this->data[4], this->data[5], this->data[6], this->data[7], this->data[8], this->data[9], this->data[10], this->data[11], this->data[12], this->data[13], this->data[14], this->data[15] };
            return ret;
        }
        explicit operator f64*()
        {
            f64* ret = new f64[16]{ this->data[0], this->data[1], this->data[2], this->data[3], this->data[4], this->data[5], this->data[6], this->data[7], this->data[8], this->data[9], this->data[10], this->data[11], this->data[12], this->data[13], this->data[14], this->data[15] };
            return ret;
        }

        auto operator=(const f64* _rhs) -> Quaternion
        {
            std::memcpy(this->data, _rhs, 16 * sizeof(f64));
            return *this;
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

        auto operator+=(const Quaternion& _rhs) noexcept -> Quaternion
        {
            std::transform(this->data, this->data + 16, _rhs.data, data, std::plus<f64>());
            return *this;
        }
    }; // namespace origin
} // namespace origin