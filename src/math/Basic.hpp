#pragma once
#include <Vector.hpp>

#include <algorithm>

#include <cstdlib>
#include <functional>
#include "Builtin.hpp"
#include <string>

#include <type_traits>
#include <utility>

#include <vector>

/*
namespace origin
{
    static size_t memory = 0;
    static size_t max_memory = 1024 * 1024 * 1024;
} // namespace origin
using namespace origin;
struct PlacementTag
{
};
template<typename T>
inline auto operator new(unsigned long size, void* ptr, PlacementTag) noexcept -> void*
{
    origin::memory += sizeof(T) * size;
    if (origin::memory > origin::max_memory)
    {
        std::printf("Memory leak detected.\n Memory used: %zu", origin::memory);
        return nullptr;
    }
    ptr = __builtin_operator_new(size);
    return ptr;
}
template<typename T>
inline void operator delete(void* ptr, unsigned long size, PlacementTag) noexcept
{
    if (ptr == nullptr)
    {
        return;
    }
    origin::memory -= sizeof(T) * size;
    if (origin::memory < 0)
    {
        std::printf("Memory leak detected.\n Memory used: %zu", origin::memory);
        return;
    }
    __builtin_operator_delete(ptr);
} */
namespace origin
{
    using std::string;
    using i8 = char;
    using i16 = short;
    using i32 = int;
    using i64 = long long;
    using i128 = __int128_t;
    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long long;
    using u128 = __uint128_t;
    using s8 = signed char;
    using s16 = signed short;
    using s32 = signed int;
    using s64 = signed long long;
    using s128 = __int128_t;
    using f32 = float;
    using f64 = double;
    using f128 = long double;
    using u8p = unsigned char*;
    using u16p = unsigned short*;
    using u32p = unsigned int*;
    using u64p = unsigned long long*;
    using u128p = __uint128_t*;
    using i8p = char*;
    using i16p = short*;
    using i32p = int*;
    using i64p = long long*;
    using i128p = __int128_t*;
    using f32p = f32*;
    using f64p = f64*;
    using f128p = f128*;
#define vattr16 __attribute__((__vector_size__(16), __aligned__(16)))
#define vattr32 __attribute__((__vector_size__(32), __aligned__(32)))
#define vattr64 __attribute__((__vector_size__(64), __aligned__(64)))
    using i8x16 = char vattr16;
    using u8x16 = unsigned char vattr16;
    using s8x16 = signed char vattr16;
    using i16x8 = short vattr16;
    using u16x8 = unsigned short vattr16;
    using s16x8 = short vattr16;
    using f32x4 = float vattr16;
    using i32x4 = int vattr16;
    using u32x4 = unsigned int vattr16;
    using s32x4 = int vattr16;
    using i64x2 = long long vattr16;
    using u64x2 = unsigned long long vattr16;
    using s64x2 = long long vattr16;
    using I8X32 = char vattr32;
    using u8x32 = unsigned char vattr32;
    using i16x16 = short vattr32;
    using u16x16 = unsigned short vattr32;
    using s16x16 = short vattr32;
    using i32x8 = int vattr32;
    using u32x8 = unsigned int vattr32;
    using s32x8 = int vattr32;
    using f32x8 = float vattr32;
    using i64x4 = long long vattr32;
    using u64x4 = unsigned long long vattr32;
    using s64x4 = signed long long vattr32;
    using f64x4 = double vattr32;
    using i128x2 = __int128_t vattr32;
    using u128x2 = __uint128_t vattr32;
    using f128x2 = long double vattr32;
    using f128x4 = long double vattr64;
#if WORDSIZE == 64
    using SIZE_T = unsigned long;
#else
    using SIZE_T = unsigned long long;
#endif
    static const u32 C4 = 0xf, C8 = 0xff, C16 = 0xffff, C32 = 0xffffff, C64 = 0xffffffff;
    template<typename T, typename U>
    auto cast(U c)
    {
        return static_cast<T>(c);
    }
    template<typename T>
    constexpr auto cast(T c, T d) -> T
    {
        return (c << (sizeof(T) * 4) | d);
    }
#define imax8 cast<i8>(127)
#define imax16 cast<i16>(32767)
#define imax32 cast<i32>(2147483647)
#define imax64 cast<i64>(9223372036854775807)
#define umax8 cast<u8>(255)
#define umax16 cast<u16>(65535)
#define umax32 cast<u32>(4294967295)
#define umax64 cast<u64>(18446744073709551615)
#define smax8 cast<s8>(127)
#define smax16 cast<s16>(32767)
#define smax32 cast<s32>(2147483647)
#define smax64 cast<s64>(9223372036854775807)
#define fmax32 cast<f32>(3.40282346638528859811704183484516925440e+38f)
#define fmax64 cast<f64>(1.797693134862315708145274237317043567981e+308)
#define fmax128 cast<f128>(1.18973149535723176508575932662800702e+4932)
#define imin8 cast<i8>(-128)
#define imin16 cast<i16>(-32768)
#define imin32 cast<i32>(-2147483648)
#define umin8 cast<u8>(0)
#define umin16 cast<u16>(0)
#define umin32 cast<u32>(0)
#define umin64 cast<u64>(0)
#define smin8 cast<s8>(-128)
#define smin16 cast<s16>(-32768)
#define smin16 cast<s16>(-32768)
#define smin32 cast<s32>(-2147483648)
#define smin64 cast<s64>(-9223372036854775808)
#define fmin32 cast<f32>(-3.40282346638528859811704183484516925440e+38f)
#define fmin64 cast<f64>(-1.797693134862315708145274237317043567981e+308)
#define fmin128 cast<f128>(-1.18973149535723176508575932662800702e+4932)
#define fe32 cast<f32>(1.1920928955078125e-07f)
#define fe64 cast<f64>(2.220446049250313080847263336181640625e-16)
#define fie64 cast<f64>(22204460492503130)
#define fe128 cast<f128>(1.9259299443872358530559779425849159658203125e-34)
#define fie128 cast<f128>(192509299444872355)
#ifndef NULL
#define NULL ((void*)0)
#endif
#define null ((void*)0)
    using V = __builtin_va_list;
    template<typename T>
    inline auto add(T a, T b)
    {
        T* c = *T(0);
        __builtin_add_overflow(a, b, c);
        return *c;
    }
    template<typename T>
    inline auto sub(T a, T b)
    {
        T* c = T(0);
        __builtin_sub_overflow(a, b, c);
        return *c;
    }
    template<typename T>
    inline auto mul(T a, T b)
    {
        T* c = T(0);
        __builtin_mul_overflow(a, b, c);
        return *c;
    }

    template<typename T>
    inline auto div(T a, T b)
    {
        T* c = T(0);
        std::div(a, b, c);
        return *c;
    }

    inline auto rand8p(u8p p) -> u8p
    {
        if ((__builtin_ia32_rdrand16_step(reinterpret_cast<u16p>(p)) == 1))
        {
            return cast<u8p>(p);
        }
        return nullptr;
    }
    inline auto rand8() -> u8
    {
        u8p p = nullptr;
        return *rand8p(p);
    }
    inline auto rand16p(u16p p) -> u16p
    {
        if ((__builtin_ia32_rdrand16_step(p)) == 1)
        {
            return p;
        }
        return nullptr;
    }
    inline auto rand16() -> u16
    {
        u16p p = nullptr;
        return *rand16p(p);
    }
    inline auto rand32p(u32p p) -> u32p
    {
        if ((__builtin_ia32_rdrand32_step(p)) == 1)
        {
            return p;
        }
        return nullptr;
    }
    inline auto rand32() -> u32
    {
        u32p p = nullptr;
        return *rand32p(p);
    }
    inline auto rand64p(u64p p) -> u64p
    {
        if ((__builtin_ia32_rdrand64_step(p)) == 1)
        {
            return p;
        }
        return nullptr;
    }
    inline auto rand64() -> u64
    {
        u64p p = nullptr;
        return *rand64p(p);
    }
    template<typename T>
    inline auto random(T* p) -> T*
    {
        *p = cast<unsigned>(*p);
        (sizeof(T) == 8 ? rand64(p) : sizeof(T) == 4 ? rand32(p) :
                                  sizeof(T) == 2     ? rand16(p) :
                                                       rand8(p));
        if (p != nullptr)
        {
            return p;
        }
        return 0;
    }

    template<typename T>
    inline auto random()
    {
        T* p = nullptr;
        return cast<T>(origin::random(p));
    }

    template<typename T>
    constexpr auto isnan(T a)
    {
        return __builtin_isnan(f128(a));
    }
    template<typename T>
    constexpr auto isnan(T a, T b)
    {
        return cast<bool>(__builtin_isnan(a, b));
    }
    template<typename T>
    constexpr auto isnan(T a, T b, T c)
    {
        return cast<bool>(__builtin_isnan(a, b, c));
    }

    template<typename T>
    constexpr auto isnan(T a, T b, T c, T d) noexcept
    {
        return cast<bool>(__builtin_isnan(a, b, c, d));
    }
    template<typename T>
    constexpr auto isinf(T a)
    {
        return cast<bool>(__builtin_isinf(a));
    }

    template<typename T>
    constexpr auto isinf(T a, T b)
    {
        return cast<bool>(__builtin_isinf(a, b));
    }

    template<typename T>
    constexpr auto isinf(T a, T b, T c)
    {
        return cast<bool>(__builtin_isinf(a, b, c));
    }

    template<typename T>
    constexpr auto isinf(T a, T b, T c, T d) noexcept
    {
        return cast<bool>(__builtin_isinf(a, b, c, d));
    }
    template<typename T>
    inline auto isnum(T a)
    {
        try
        {
            f128 const b = a;
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    template<typename T>
    constexpr auto isnum(T a, T b)
    {
        return !(cast<bool>(__builtin_isnan(a, b)) || cast<bool>(__builtin_isinf(a, b)));
    }

    template<typename T>
    constexpr auto isnum(T a, T b, T c)
    {
        return !(cast<bool>(__builtin_isnan(a, b, c)) || cast<bool>(__builtin_isinf(a, b, c)));
    }

    template<typename T>
    constexpr auto isnum(T a, T b, T c, T d) noexcept
    {
        return !(cast<bool>(__builtin_isnan(a, b, c, d)) || cast<bool>(__builtin_isinf(a, b, c, d)));
    }
    template<typename T>
    constexpr auto abs(T& a, T& b, T& c)
    {
        return cast<bool>(isnan(a, b, c) ? false : (__builtin_elementwise_abs(a, b, c)));
    }

    template<typename T>
    constexpr auto abs(T& a, T& b, T& c, T& d) noexcept
    {
        return cast<bool>(isnan(a, b, c, d) ? false : (__builtin_elementwise_abs(a, b, c, d)));
    }

    template<typename T>
    constexpr auto sin(T a) noexcept
    {
        return cast<T>(isnan(a) ? 0.0 : (__builtin_sinl(cast<f128>(a))));
    }

    template<typename T>
    constexpr auto cos(T a) noexcept
    {
        return cast<T>(isnan(a) ? 0.0 : (__builtin_cosl(cast<f128>(a))));
    }
    template<typename T>
    constexpr auto atan2(T& a, T& b) noexcept
    {
        return cast<T>(isnan(a, b) ? 0.0 : (__builtin_atan2l(cast<f128>(a), cast<f128>(b))));
    }
    template<typename T>
    constexpr auto atan2(T& a, T& b, T& c) noexcept
    {
        return cast<T>(isnan(a, b, c) ? 0.0 : (__builtin_atan2l(__builtin_atan2l(cast<f128>(a), cast<f128>(b)), cast<f128>(c))));
    }

    template<typename T>
    constexpr auto asin(T a) noexcept
    {
        return cast<T>(isnan(a) ? 0.0 : (__builtin_asinl(cast<f128>(a))));
    }

    template<typename T>
    constexpr auto acos(T a) noexcept
    {
        return cast<T>(isnan(a) ? 0.0 : (__builtin_acosl(cast<f128>(a))));
    }

    template<typename T>
    constexpr auto atan(T a) noexcept
    {
        return cast<T>(isnan(a) ? 0.0 : (__builtin_atanl(cast<f128>(a))));
    }
    template<typename T>
    constexpr auto ceil(T& a, T& b, T* c)
    {
        (__builtin_elementwise_ceil(a, b, c));
        return *c;
    }
    template<typename T>
    constexpr auto floor(T& a, T& b, T* c)
    {
        (__builtin_elementwise_floor(a, b, c));
        return *c;
    }

    template<typename T>
    constexpr auto round(T& a, T* b) noexcept
    {
        (__builtin_elementwise_round(a, *b));
        return *b;
    }
    template<typename T>
    constexpr auto trunc(T& a, T& b, T* c) noexcept
    {
        (__builtin_elementwise_trunc(a, b, c));
        return *c;
    }

    template<typename T>
    constexpr auto rint(T& a, T& b, T* c)
    {
        (__builtin_elementwise_rint(a, b, c));
        return *c;
    }
    template<typename T>
    constexpr auto nearbyint(T& a, T& b, T* c)
    {
        (__builtin_elementwise_nearbyint(a, b, c));
        return *c;
    }

    template<typename T, typename U>
    constexpr auto copysign(T& a, U* b) noexcept
    {
        (__builtin_elementwise_copysign(a, *b));
    }

    template<typename T>
    constexpr auto sin(T& a, T* b) noexcept
    {
        (__builtin_elementwise_sin(a, b));
        return *b;
    }
    template<typename T>
    constexpr auto cos(T& a, T* b)
    {
        (__builtin_elementwise_cos(a, b));
        return *b;
    }
    template<typename T>
    constexpr auto addsat(T& a, T& b, T* c)
    {
        (__builtin_elementwise_add_sat(a, b, c));
        return *c;
    }

    template<typename T>
    constexpr auto addsat(T& a, T& b, T& c, T& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : (__builtin_elementwise_add_sat(a, b, c, d)));
    }
    template<typename T>
    constexpr auto subsat(T& a, T& b, T& c)
    {
        (isnan(a, b, c) ? T(0) : (__builtin_elementwise_sub_sat(a, b, c)));
    }

    template<typename T>
    constexpr auto subsat(T& a, T& b, T& c, T& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : (__builtin_elementwise_sub_sat(a, b, c, d)));
    }
    template<typename T>
    constexpr auto min(T a, T b) noexcept
    {
        return (isnan(a, b) ? T(0) : (a < b) ? a :
                                               b);
    }

    template<typename T>
    constexpr auto min(T a, T b, T c) noexcept
    {
        return (isnan(a, b, c) ? T(0) : (a < b) ? (a < c ? a : c) :
                                                  (b < c ? b : c));
    }

    template<typename T>
    constexpr auto min(T a, T b, T c, T d) noexcept
    {
        return (isnan(a, b, c, d) ? T(0) : (a < b) ? (a < c ? (a < d ? a : d) : c) :
                                                     (b < c ? (b < d ? b : d) : (c < d ? c : d)));
    }
    template<typename T>
    constexpr auto max(T a, T b) noexcept
    {
        return (isnan(a, b) ? T(0) : (a < b) ? b :
                                               a);
    }
    template<typename T>
    constexpr auto max(T a, T b, T c) noexcept
    {
        return (isnan(a, b, c) ? T(0) : (a < b) ? (b < c ? c : b) :
                                                  (a < c ? c : a));
    }

    template<typename T>
    constexpr auto max(T a, T b, T c, T d) noexcept
    {
        return (isnan(a, b, c, d) ? T(0) : (a < b) ? (b < c ? (c < d ? d : c) : b) :
                                                     (a < c ? (c < d ? d : c) : (a < d ? d : a)));
    }

    template<typename T>
    constexpr auto sqrt(T a)
    {
        return (isnan(a) ? T(0) : cast<T>(__builtin_sqrtl(cast<f128>(a))));
    }
    template<typename T>
    constexpr auto log(T& a, T& b, T& c)
    {
        (isnan(a) ? T(0) : cast<T>(__builtin_elementwise_log(a, b, c)));
    }

    template<typename T>
    constexpr auto log(T& a, T& b, T& c, T& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : cast<T>(__builtin_elementwise_log(a, b, c, d)));
    }
    template<typename T>
    constexpr auto log2(T& a, T& b, T& c)
    {
        (isnan(a, b, c) ? T(0) : (__builtin_elementwise_log2(a, b, c)));
    }

    template<typename T>
    constexpr auto log2(T& a, T& b, T& c, T& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : (__builtin_elementwise_log2(a, b, c, d)));
    }
    template<typename T>
    constexpr auto log10(T& a, T& b, T& c)
    {
        (isnan(a, b, c) ? T(0) : (__builtin_elementwise_log10(a, b, c)));
    }

    template<typename T>
    constexpr auto log10(T& a, T& b, T& c, T& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : (__builtin_elementwise_log10(a, b, c, d)));
    }
    template<typename T>
    constexpr auto exp(T& a, T& b, T& c)
    {
        (isnan(a, b, c) ? T(0) : (__builtin_elementwise_exp(a, b, c)));
    }

    template<typename T>
    constexpr auto exp(T& a, T& b, T& c, T& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : (__builtin_elementwise_exp(a, b, c, d)));
    }
    template<typename T>
    inline auto exp2(T& a, T& b, T& c)
    {
        (isnan(a, b, c) ? T(0) : (__builtin_elementwise_exp2(a, b, c)));
    }

    template<typename T>
    inline auto exp2(T& a, T& b, T& c, T& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : (__builtin_elementwise_exp2(a, b, c, d)));
    }
    template<typename T, typename U>
    constexpr auto pow(T& a, U& b, U& c)
    {
        (isnan(a, b, c) ? T(0) : (__builtin_elementwise_pow(a, b, c)));
    }
    template<typename T, typename U>
    constexpr auto pow(T& a, U& b, U& c, U& d) noexcept
    {
        (isnan(a, b, c, d) ? T(0) : (__builtin_elementwise_pow(a, b, c, d)));
    }
    using ID = u64;

    template<typename T>
    constexpr auto isnormal(T a)
    {
        return bool(__builtin_isnormal(a));
    }

    template<typename T>
    constexpr auto isnormal(T a, T b)
    {
        return bool(__builtin_isnormal(a, b));
    }

    template<typename T>
    constexpr auto isnormal(T a, T b, T c)
    {
        return bool(__builtin_isnormal(a, b, c));
    }

    template<typename T>
    constexpr auto isnormal(T a, T b, T c, T d)
    {
        return bool(__builtin_isnormal(a, b, c, d));
    }
    template<typename T>
    constexpr auto isfinite(T a)
    {
        return bool(__builtin_isfinite(a));
    }
    template<typename T>
    constexpr auto isfinite(T a, T b)
    {
        return bool(__builtin_isfinite(a, b));
    }
    template<typename T>
    constexpr auto isfinite(T a, T b, T c)
    {
        return bool(__builtin_isfinite(a, b, c));
    }
    template<typename T>
    constexpr auto isfinite(T a, T b, T c, T d)
    {
        return bool(__builtin_isfinite(a, b, c, d));
    }
#undef alloca
    template<typename T>
    auto alloca(unsigned long a)
    {
        return cast<T>(__builtin_alloca(a));
    }
    template<typename T>
    auto memchr(const void* a, int b, unsigned long c)
    {
        return cast<T>(__builtin_memchr(a, b, c));
    }
    template<typename T>
    auto memmove(void* a, const void* b, unsigned long c)
    {
        return cast<T>(__builtin_memmove(a, b, c));
    }
    template<typename T>
    auto memcpy(void* a, const void* b, unsigned long c)
    {
        return cast<T>(__builtin_memcpy(a, b, c));
    }
    template<typename T>
    auto memcmp(const void* a, const void* b, unsigned long c)
    {
        return cast<T>(__builtin_memcmp(a, b, c));
    }
    template<typename T>
    auto memset(void* a, int b, unsigned long c)
    {
        return cast<T>(__builtin_memset(a, b, c));
    }
    template<typename T>
    constexpr auto cross(T a[3], T b[3], T c[3]) noexcept
    {
        T vec[3][3];
        T dot;
        T result[3];
        vec[0][0] = a * b[2] - a[2] * b[1];
        vec[0][1] = a[2] * b[0] - a[0] * b[2];
        vec[0][2] = a[0] * b[1] - a * b[0];
        vec[1][0] = a[2] * c[1] - a * c[2];
        vec[1][1] = a[0] * c[2] - a[2] * c[0];
        vec[1][2] = a * c[0] - a[0] * c[1];
        vec[2][0] = a * b[2] - a[2] * b[1];
        vec[2][1] = a[2] * b[0] - a[0] * b[2];
        vec[2][2] = a[0] * b[1] - a;
    }
    template<typename T>
    constexpr auto reverse(T a)
    {
        T result = 0;
        for (u32 i = 0; i < sizeof(T); i++)
        {
            result = (result << 1) | (a & 1);
            a >>= 1;
        }
        return result;
    }
    template<typename T>
    constexpr auto bitset(T a)
    {
        T result = 0;
        for (u32 i = 0; i < sizeof(T); i++)
        {
            result = (result << 1) | ((a >> i) & 1);
        }
        return result;
    }

    template<typename T>
    constexpr auto hypot(T a, T b)
    {
        return !isnan(a, b) ? T(__builtin_hypotl(cast<f128>(a), cast<f128>(b))) : T(0);
    }
    template<typename T>
    constexpr auto square(T a)
    {
        return !isnan(a) ? T(a * a) : T(0);
    }
    template<typename T>
    constexpr auto madd(T a, T b, T c)
    {
        return !isnan(a, b, c) ? T(a * b + c) : T(0);
    }
    template<typename T>
    constexpr auto copysign(T a, T b)
    {
        return !isnan(a, b) ? T(__builtin_copysignl(cast<f128>(a), cast<f128>(b))) : T(0);
    }
    template<typename T>
    constexpr auto clamp(T a, T b, T c)
    {
        return origin::min<T>(origin::max<T>(a, b), c);
    }
    template<typename T>
    constexpr auto step(T a, T b)
    {
        return origin::clamp(b - a, 0.0, 1.0);
    }
    template<typename T>
    constexpr auto fract(T a) noexcept
    {
        if (isnan(a))
            return T(0);
        return a - cast<T>(__builtin_floorl(cast<f128>(a)));
    }
    template<typename T>
    constexpr auto lerp(T a, T b, T c) noexcept
    {
        if (isnan(a))
            return T(0);
        return (a + c * (b - a));
    }
    template<typename T>
    constexpr auto smoothstep(T a, T b, T c)
    {
        if (isnan(a, b, c))
            return T(0);
        auto c2 = clamp(c - a / b - a, 0.0, 1.0);
        return c2 * c2 * 3.0 - 2.0 * c2;
    }
    template<typename T>
    constexpr auto rsqrt(T a)
    {
        if (isnan(a))
            return T(0);
        return cast<T>(1.0 / sqrtl(cast<f128>(a)));
    }
    template<typename T>
    constexpr auto dot(T a, T b) noexcept
    {
        if (isnan(a, b))
            return T(0);
        return a * b;
    }
    template<typename T>
    constexpr auto length(T a, T b)
    {
        if (isnan(a, b))
            return T(0);
        return sqrt(a * a + b * b);
    }
    template<typename T, u64 N>
    constexpr auto normalize(T const (&arr)[N])
    {
        T out[N];
        for (u64 i = 0; i < N; ++i)
        {
            out[i] = arr[i] / sqrt(arr[i] * arr[i] + (i + 1 < N ? arr[i + 1] * arr[i + 1] : 0));
        }
        return out;
    }
    template<typename T>
    auto neg(T a)
    {
        if (isnan(a))
            return T(0);
        try
        {
            mul(a, -1);
        }
        catch (...)
        {
            return 0;
        };
    }

    template<typename T>
    constexpr auto random(T a, T b)
    {
        if (isnan(a, b))
            return T(0);
        return abs<T>((rand64() % cast<u64>(b - a)) + a);
    }
    template<typename T>
    constexpr auto tan(T a)
    {
        if (isnan(a))
            return T(0);
        return cast<T>(__builtin_tanl(cast<f128>(a)));
    }
    template<typename T>
    constexpr auto atan2(T a, T b) noexcept
    {
        if (isnan(a, b))
            return T(0);
        return cast<T>(__builtin_atan2l(cast<f128>(a), cast<f128>(b)));
    }

    template<typename T>
    constexpr auto sinsq(T a) noexcept
    {
        const T b = (isnan(a) ? T(0) : cast<T>(__builtin_sinl(cast<f128>(a))));
        return b * b;
    }
    template<typename T>
    constexpr auto cossq(T a) noexcept
    {
        const T b = (isnan(a) ? T(0) : cast<T>(__builtin_cosl(cast<f128>(a))));
        return b * b;
    }

    template<u64 N>
    struct Complex
    {
    public:
        union
        {
            f128 Data[N * 2];
            struct
            {
                f128 Real[N];
                f128 Imag[N];
            };
        } C;
        explicit Complex(f64 real = 0, f64 imag = 0)
        {
            C.Real = real;
            C.Imag = imag;
        }
        static auto zero() -> Complex { return { 0, 0 }; }
        static auto add(const Complex A, const Complex B) noexcept -> Complex
        {
            auto C = op(A.Data, B.Data, N * 2);
            return { A.Real + B.Real, A.Imag + B.Imag };
        }
        static auto sub(const Complex A, const Complex B) noexcept -> Complex
        {
            return { A.Real - B.Real, A.Imag - B.Imag };
        }

        auto mul(const Complex b) const noexcept -> Complex
        {
            return { C.Real * b.Real - C.Imag * b.Imag, C.Real * b.Imag + C.Imag * b.Real };
        }
        auto mul(f64* out, const f64* in) const noexcept
        {
            auto* ret = out;
            for (u64 i = 0; i < N; i++)
            {
                ret[i] = C.Real[i] * in[i] - C.Imag[i] * in[i + N];
                ret[i + N] = C.Real[i] * in[i + N] + C.Imag[i] * in[i];
            }
            return ret;
        }

        static auto div(Complex a, Complex b) noexcept -> Complex
        {
            return { (a.Real * b.Real + a.Imag * b.Imag) / (b.Real * b.Real + b.Imag * b.Imag),
                     (a.Imag * b.Real - a.Real * b.Imag) / (b.Real * b.Real + b.Imag * b.Imag) };
        }
        static auto fft(const Complex* input, u64 n) -> Complex*
        {
            auto output = new Complex[n];
            f64 wn = -2 * PI / n;

            // Divide input into even and odd parts
            for (u64 i = 0; i < n; i += 4)
            {
                const auto a = input[i].real;
                const auto b = input[i + 1].real;
                const auto c = input[i + 2].real;
                const auto d = input[i + 3].real;
                output[i].real = a + c;
                output[i + 1].real = a - c;
                output[i + 2].real = b + d;
                output[i + 3].real = b - d;
            }

            for (u64 size = 4, half_size = n >> 1U; size <= n; size <<= 2U, half_size >>= 1U)
            {
                const auto w = wn;
                for (u64 i = 0; i < n; i += size)
                {
                    for (u64 j = i; j < i + half_size; j += 4)
                    {
                        const auto a = output[j].real;
                        const auto b = output[j].imag;
                        const auto c = output[j + 2].real;
                        const auto d = output[j + 2].imag;
                        const auto e = output[j + 1].real;
                        const auto f = output[j + 1].imag;
                        const auto g = output[j + 3].real;
                        const auto h = output[j + 3].imag;
                        output[j].real = a + c;
                        output[j].imag = b + d;
                        output[j + 1].real = e + g;
                        output[j + 1].imag = f + h;
                        output[j + 2].real = a - c;
                        output[j + 2].imag = b - d;
                        output[j + 3].real = e - g;
                        output[j + 3].imag = f - h;
                        wn = w * wn;
                    }
                }
            }

            // Bit reverse
            for (u64 i = 1, j = 0; i < n; ++i)
            {
                u64 x = i;
                u64 k = n >> 1U;
                while (j >= k)
                {
                    x = (x ^ (j & ~k)) & (n - 1);
                    j &= k;
                    k >>= 1U;
                }
                if (i < (j | k))
                {
                    std::swap(output[i], output[j | k]);
                }
            }

            // Normalize
            const auto norm = 1.0 / sqrt(n);
            for (u64 i = 0; i < n; i += 4)
            {
                output[i].real *= norm;
                output[i + 1].real *= norm;
                output[i + 2].real *= norm;
                output[i + 3].real *= norm;
                output[i].imag *= norm;
                output[i + 1].imag *= norm;
                output[i + 2].imag *= norm;
                output[i + 3].imag *= norm;
            }
            return output;
        }

        static auto conjugate(Complex* C1) -> Complex*
        {
            auto* c = C1;
            for (u64 i = 0; i < N; i++)
            {
                c[i].Imag = -c[i].Imag;
            }
            return c;
        }

        static auto fft2(Complex* input) -> Complex*
        {
            auto* c = input;

            // Cooley–Tukey FFT (in-place)
            for (size_t size = 1, half_size = 1; size < N; size <<= 1U, half_size = size >> 1U)
            {
                const double phase = -2 * PI / size;
                for (size_t first_index = 0; first_index < N; first_index += size)
                {
                    for (size_t index = 0; index < half_size; ++index)
                    {
                        const size_t i = first_index + index;
                        const size_t j = i + half_size;
                        const auto a = c[i];
                        const auto b = c[j];
                        c[i] = a + b;
                        c[j] = a - b;
                        c[j].Imag += phase * c[i].Imag;
                        c[i].Imag -= phase * c[j].Imag;
                    }
                }
            }

            // Bit reverse
            for (size_t i = 1, j = 0; i < N; ++i)
            {
                size_t k = N >> 1U;
                while ((j ^= k) < k)
                {
                    k >>= 1U;
                }
                if (i < j)
                {
                    std::swap(c[i], c[j]);
                }
            }

            // Normalize
            const double norm = 1.0 / sqrt(N);
            for (size_t i = 0; i < N; i += 4)
            {
                c[i].Real *= norm;
                c[i + 1].Real *= norm;
                c[i + 2].Real *= norm;
                c[i + 3].Real *= norm;
                c[i].Imag *= norm;
                c[i + 1].Imag *= norm;
                c[i + 2].Imag *= norm;
                c[i + 3].Imag *= norm;
            }
            return c;
        }

        static auto ifft(Complex C1[]) -> Complex*
        {
            auto* c = C1;
            c = conjugate(c, N);
            fft2(c, N);
            c = conjugate(c, N);
            return c;
        }
    } __attribute__((aligned(32)));
    struct Mem
    {
    private:
        f64 Mem_size = 0.0;
        f64 Mem_used = 0.0;
        f64 Mem_max = 1.000000e+15;

    public:
        enum class Unit : i8
        {
            NONE = -1,
            BYTE = 0,
            KBYTE = 1,
            MBYTE = 2,
            GBYTE = 3,
            TBYTE = 4,
            PBYTE = 5
        } Mem_unit = Unit::BYTE;
        explicit Mem(enum Unit unit = Unit::BYTE) :
            Mem_unit(unit)
        {
            Mem_size = Mem_used = 0.0;
        }
        explicit Mem(f64 size, f64 used = 0.0, enum Unit unit = Unit::BYTE) :
            Mem_size(size), Mem_used(used < size ? used : size), Mem_unit(unit)
        {
        }
        Mem(const Mem& rhs) { *this = rhs; }
        Mem(Mem&& rhs) noexcept { *this = std::move(rhs); }
        ~Mem()
        {
            Mem_size = Mem_used = 0.0;
            Mem_unit = Unit::BYTE;
        }
        [[nodiscard]] auto convert(const enum Unit unit) const -> Mem
        {
            const u8 one = 1;
            const u8 unit0 = static_cast<u8>(Mem_unit) * 10;
            const u8 unit1 = static_cast<u8>(unit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return Mem(Mem_size * ratio, Mem_used * ratio, unit);
        }
        [[nodiscard]] auto convert(const Mem& mem) const -> Mem
        {
            const u8 one = 1;
            if (mem.Mem_unit == Unit::NONE)
            {
                return Mem{ Mem_size, Mem_used, Mem_unit };
            };
            const u8 unit0 = static_cast<u8>(Mem_unit) * 10;
            const u8 unit1 = static_cast<u8>(mem.Mem_unit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return Mem{ mem.Mem_size * ratio, mem.Mem_used * ratio, mem.Mem_unit };
        }
        auto operator[](enum Unit unit) const { return convert(unit); }
        auto operator=(const Mem& rhs) -> Mem& = default;
        auto operator=(Mem&& rhs) noexcept -> Mem& { return *this = rhs; }
        [[nodiscard]] constexpr auto size() const -> f64 { return Mem_size; }
        [[nodiscard]] constexpr auto total() const -> f64 { return size(); }
        [[nodiscard]] constexpr auto available() const -> f64 { return Mem_size - Mem_used; }
        [[nodiscard]] constexpr auto used() const -> f64 { return Mem_used; }
        [[nodiscard]] constexpr auto free() const -> f64 { return Mem_size - Mem_used; }
        [[nodiscard]] constexpr auto percentage() const -> f64 { return ((Mem_used) / (Mem_size)) * 100.0; }
        [[nodiscard]] constexpr auto percentageUsed() const -> f64 { return ((Mem_used) / (Mem_size)) * 100.0; }
        [[nodiscard]] constexpr auto percentageFree() const -> f64 { return ((Mem_size) / (Mem_used)) * 100.0; }
        constexpr auto set(const f64 size = -1, const f64 used = -1, enum Unit unit = Unit::NONE) -> Mem&
        {
            if (unit != Unit::NONE)
            {
                if (size >= 0.0 && size < Mem_max)
                {
                    Mem_size = size;
                }
                if (used >= 0.0 && used <= Mem_size)
                {
                    Mem_used = used;
                }
                if (unit >= Unit::BYTE && unit <= Unit::PBYTE && unit != Mem_unit)
                {
                    Mem_unit = unit;
                }
            }
            return *this;
        }
    } __attribute__((aligned(32))) __attribute__((packed));

    template<typename T, typename... U>
    struct Op
    {
    private:
        using function = T (*)(T (*)(U...));
        template<typename... V>
        static constexpr auto fmax_ = [](U... args) { return __builtin_fmax(args...); };
        template<typename... V>
        static constexpr auto fmin_ = [](U... args) { return __builtin_fmin(args...); };
        static Vector<function> fvec = Vector<function>();
        function func = nullptr;

    public:
        static auto emplace_min(U... args) { return fvec.emplace_back(fmin_<U...>(args...)); }
        static auto emplace_max(U... args) { return fvec.emplace_back(fmax_<U...>(args...)); }

        template<typename... V>
        static auto pushBack(function f)
        {
            if constexpr (sizeof...(V) > 0)
            {
                fvec.push_back([=](V... args) { return f(args...); });
                return *fvec.rbegin();
            }
            else
            {
                fvec.push_back(f);
                return *fvec.rbegin();
            }
        }

        Op() = default;
        Op& operator=(Op const& op)
        {
            if (this == &op)
            {
                return *this;
            }
            func = op.func;
            return *this;
        }
        auto push(Op op) noexcept
        {
            fvec.pushBack(std::move(op.func));
        }
        Op(Op const& op)
        {
            *this = op;
            return *this;
        }
        Op(function f)
        {
            this->func = f;
            return *this;
        }
        ~Op() = default;
        auto operator()(function f)
        {
            this->func = f;
            return *this;
        }
        operator function() const { return fvec.begin(); }
        Op& operator=(Op&& op) noexcept
        {
            return *this = std::move(op);
        }
        Op& operator=(Op op) noexcept
        {
            return *this = std::move(op);
        }
        auto operator[](u32 i) { return fvec[i]; }
        auto operator<<(function&& f)
        {
            fvec.pushBack(f);
            return fvec;
        }
        auto& operator<<(function const& f)
        {
            fvec.pushBack(f);
            return fvec;
        }
        auto& operator<<(Op const& op)
        {
            fvec.pushBack(op.f);
            return fvec;
        }

    private:
        static auto pushBack(function f)
        {
            fvec.push_back(f);
            return *fvec.rbegin();
        }

    public:
        auto operator()() const noexcept { return func(); }
        auto operator()() { return func(); }

        auto operator()(Op const& op)
        {
            this->f = op.f(op);
            return *this;
        }
        auto operator->() { return &func; }

        auto operator->() const { return &func; }

        auto operator*() { return func; }

        auto operator*() const { return func; }

        auto reset(function f) { this->func = f; }

        auto reset(Op const& op) { *this = op; }

        auto clear() { func = nullptr; }

        auto empty() const { return func == nullptr; }

        auto swap(Op& op) noexcept { std::swap(func, op.func); }

        auto target() const
        {
            return func;
        }
    };
} // namespace origin
