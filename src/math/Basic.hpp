#pragma once
#include <algorithm>

#include <cassert>

#include <cstddef>

#include <cstdlib>

#include <cstring>
#include <immintrin.h>
#include <string>
#include <utility>

/*
namespace Origin
{
    static size_t memory = 0;
    static size_t max_memory = 1024 * 1024 * 1024;
} // namespace Origin
using namespace Origin;
struct PlacementTag
{
};
template<typename T>
inline auto operator new(unsigned long size, void* ptr, PlacementTag) noexcept -> void*
{
    Origin::memory += sizeof(T) * size;
    if (Origin::memory > Origin::max_memory)
    {
        std::printf("Memory leak detected.\n Memory used: %zu", Origin::memory);
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
    Origin::memory -= sizeof(T) * size;
    if (Origin::memory < 0)
    {
        std::printf("Memory leak detected.\n Memory used: %zu", Origin::memory);
        return;
    }
    __builtin_operator_delete(ptr);
} */
namespace Origin
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
    static const u32 C8 = 0xff, C16 = 0xffff, C32 = 0xffffff, C64 = 0xffffffff;
    constexpr f64 PI = 3.14159265358979323846535897932384;
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
#ifndef NO_BUILTIN
    using V = __builtin_va_list;
    inline auto abs(f64 x) -> f64
    {
        return __builtin_fabs(x);
    }
    inline auto abs(f32 x) -> f32
    {
        return __builtin_fabsf(x);
    }
    inline auto abs(f128 x) -> f128
    {
        return __builtin_fabsl(x);
    }

    inline auto acos(f64 x) -> f64
    {
        return __builtin_acos(x);
    }
    inline auto acos(f32 x) -> f32
    {
        return __builtin_acosf(x);
    }
    inline auto acos(f128 x) -> f128
    {
        return __builtin_acosl(x);
    }

    inline auto acosh(f64 x) -> f64
    {
        return __builtin_acosh(x);
    }
    inline auto acosh(f32 x) -> f32
    {
        return __builtin_acoshf(x);
    }
    inline auto acosh(f128 x) -> f128
    {
        return __builtin_acoshl(x);
    }

    inline auto asin(f64 x) -> f64
    {
        return __builtin_asin(x);
    }
    inline auto asin(f32 x) -> f32
    {
        return __builtin_asinf(x);
    }
    inline auto asin(f128 x) -> f128
    {
        return __builtin_asinl(x);
    }

    inline auto asinh(f64 x) -> f64
    {
        return __builtin_asinh(x);
    }
    inline auto asinh(f32 x) -> f32
    {
        return __builtin_asinhf(x);
    }
    inline auto asinh(f128 x) -> f128
    {
        return __builtin_asinhl(x);
    }

    inline auto atan(f64 x) -> f64
    {
        return __builtin_atan(x);
    }
    inline auto atan(f32 x) -> f32
    {
        return __builtin_atanf(x);
    }
    inline auto atan(f128 x) -> f128
    {
        return __builtin_atanl(x);
    }

    inline auto atan2(f64 x, f64 y) -> f64
    {
        return __builtin_atan2(x, y);
    }
    inline auto atan2(f32 x, f32 y) -> f32
    {
        return __builtin_atan2f(x, y);
    }
    inline auto atan2(f128 x, f128 y) -> f128
    {
        return __builtin_atan2l(x, y);
    }

    inline auto cbrt(f64 x) -> f64
    {
        return __builtin_cbrt(x);
    }
    inline auto cbrt(f32 x) -> f32
    {
        return __builtin_cbrtf(x);
    }
    inline auto cbrt(f128 x) -> f128
    {
        return __builtin_cbrtl(x);
    }

    inline auto ceil(f64 x) -> f64
    {
        return __builtin_ceil(x);
    }
    inline auto ceil(f32 x) -> f32
    {
        return __builtin_ceilf(x);
    }
    inline auto ceil(f128 x) -> f128
    {
        return __builtin_ceill(x);
    }

    inline auto copysign(f64 x, f64 y) -> f64
    {
        return __builtin_copysign(x, y);
    }
    inline auto copysign(f32 x, f32 y) -> f32
    {
        return __builtin_copysignf(x, y);
    }
    inline auto copysign(f128 x, f128 y) -> f128
    {
        return __builtin_copysignl(x, y);
    }

    inline auto cos(f64 x) -> f64
    {
        return __builtin_cos(x);
    }
    inline auto cos(f32 x) -> f32
    {
        return __builtin_cosf(x);
    }
    inline auto cos(f128 x) -> f128
    {
        return __builtin_cosl(x);
    }

    inline auto cosh(f64 x) -> f64
    {
        return __builtin_cosh(x);
    }
    inline auto cosh(f32 x) -> f32
    {
        return __builtin_coshf(x);
    }
    inline auto cosh(f128 x) -> f128
    {
        return __builtin_coshl(x);
    }

    inline auto erf(f64 x) -> f64
    {
        return __builtin_erf(x);
    }
    inline auto erf(f32 x) -> f32
    {
        return __builtin_erff(x);
    }
    inline auto erf(f128 x) -> f128
    {
        return __builtin_erfl(x);
    }

    inline auto erfc(f64 x) -> f64
    {
        return __builtin_erfc(x);
    }
    inline auto erfc(f32 x) -> f32
    {
        return __builtin_erfcf(x);
    }
    inline auto erfc(f128 x) -> f128
    {
        return __builtin_erfcl(x);
    }

    inline auto exp(f64 x) -> f64
    {
        return __builtin_exp(x);
    }
    inline auto exp(f32 x) -> f32
    {
        return __builtin_expf(x);
    }
    inline auto exp(f128 x) -> f128
    {
        return __builtin_expl(x);
    }

    inline auto exp2(f64 x) -> f64
    {
        return __builtin_exp2(x);
    }
    inline auto exp2(f32 x) -> f32
    {
        return __builtin_exp2f(x);
    }
    inline auto exp2(f128 x) -> f128
    {
        return __builtin_exp2l(x);
    }

    inline auto fdim(f64 x, f64 y) -> f64
    {
        return __builtin_fdim(x, y);
    }
    inline auto fdim(f32 x, f32 y) -> f32
    {
        return __builtin_fdimf(x, y);
    }
    inline auto fdim(f128 x, f128 y) -> f128
    {
        return __builtin_fdiml(x, y);
    }

    inline auto floor(f64 x) -> f64
    {
        return __builtin_floor(x);
    }
    inline auto floor(f32 x) -> f32
    {
        return __builtin_floorf(x);
    }
    inline auto floor(f128 x) -> f128
    {
        return __builtin_floorl(x);
    }

    inline auto fma(f64 x, f64 y, f64 z) -> f64
    {
        return __builtin_fma(x, y, z);
    }
    inline auto fma(f32 x, f32 y, f32 z) -> f32
    {
        return __builtin_fmaf(x, y, z);
    }
    inline auto fma(f128 x, f128 y, f128 z) -> f128
    {
        return __builtin_fmal(x, y, z);
    }

    inline auto fmax(f64 x, f64 y) -> f64
    {
        return __builtin_fmax(x, y);
    }
    inline auto fmax(f32 x, f32 y) -> f32
    {
        return __builtin_fmaxf(x, y);
    }
    inline auto fmax(f128 x, f128 y) -> f128
    {
        return __builtin_fmaxl(x, y);
    }

    inline auto fmin(f64 x, f64 y) -> f64
    {
        return __builtin_fmin(x, y);
    }
    inline auto fmin(f32 x, f32 y) -> f32
    {
        return __builtin_fminf(x, y);
    }
    inline auto fmin(f128 x, f128 y) -> f128
    {
        return __builtin_fminl(x, y);
    }

    inline auto fmod(f64 x, f64 y) -> f64
    {
        return __builtin_fmod(x, y);
    }
    inline auto fmod(f32 x, f32 y) -> f32
    {
        return __builtin_fmodf(x, y);
    }
    inline auto fmod(f128 x, f128 y) -> f128
    {
        return __builtin_fmodl(x, y);
    }

    inline auto fpclassify(i32 a, i32 b, i32 c, i32 d, i32 e, f32 f) -> i32
    {
        return __builtin_fpclassify(a, b, c, d, e, f);
    }

    inline auto hypot(f64 x, f64 y) -> f64
    {
        return __builtin_hypot(x, y);
    }
    inline auto hypot(f32 x, f32 y) -> f32
    {
        return __builtin_hypotf(x, y);
    }
    inline auto hypot(f128 x, f128 y) -> f128
    {
        return __builtin_hypotl(x, y);
    }

    inline auto ilogb(f64 x) -> i32
    {
        return __builtin_ilogb(x);
    }
    inline auto ilogb(f32 x) -> i32
    {
        return __builtin_ilogbf(x);
    }
    inline auto ilogb(f128 x) -> i32
    {
        return __builtin_ilogbl(x);
    }

    inline auto isfinite(f64 x) -> bool
    {
        return __builtin_isfinite(x) != 0;
    }
    inline auto isfinite(f32 x) -> bool
    {
        return __builtin_isfinite(x) != 0;
    }
    inline auto isfinite(f128 x) -> bool
    {
        return __builtin_isfinite(x) != 0;
    }

    inline auto isgreater(f64 x, f64 y) -> bool
    {
        return __builtin_isgreater(x, y) != 0;
    }
    inline auto isgreater(f32 x, f32 y) -> bool
    {
        return __builtin_isgreater(x, y) != 0;
    }
    inline auto isgreater(f128 x, f128 y) -> bool
    {
        return __builtin_isgreater(x, y) != 0;
    }

    inline auto isgreaterequal(f64 x, f64 y) -> bool
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline auto isgreaterequal(f32 x, f32 y) -> bool
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline auto isgreaterequal(f128 x, f128 y) -> bool
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline auto lgammal(f128 x) -> f128
    {
        return __builtin_lgammal(x);
    }
    inline auto llrint(f64 x) -> i64
    {
        return __builtin_llrint(x);
    }
    inline auto llrintf(f32 x) -> i64
    {
        return __builtin_llrintf(x);
    }
    inline auto llrintl(f128 x) -> i64
    {
        return __builtin_llrintl(x);
    }
    inline auto llround(f64 x) -> i64
    {
        return __builtin_llround(x);
    }
    inline auto llroundf(f32 x) -> i64
    {
        return __builtin_llroundf(x);
    }
    inline auto llroundl(f128 x) -> i64
    {
        return __builtin_llroundl(x);
    }
    inline auto log(f64 x) -> f64
    {
        return __builtin_log(x);
    }
    inline auto logf(f32 x) -> f32
    {
        return __builtin_logf(x);
    }
    inline auto logl(f128 x) -> f128
    {
        return __builtin_logl(x);
    }
    inline auto log10(f64 x) -> f64
    {
        return __builtin_log10(x);
    }
    inline auto log10f(f32 x) -> f32
    {
        return __builtin_log10f(x);
    }
    inline auto log10l(f128 x) -> f128
    {
        return __builtin_log10l(x);
    }
    inline auto log1p(f64 x) -> f64
    {
        return __builtin_log1p(x);
    }
    inline auto log1pf(f32 x) -> f32
    {
        return __builtin_log1pf(x);
    }
    inline auto log1pl(f128 x) -> f128
    {
        return __builtin_log1pl(x);
    }
    inline auto log2(f64 x) -> f64
    {
        return __builtin_log2(x);
    }
    inline auto log2f(f32 x) -> f32
    {
        return __builtin_log2f(x);
    }
    inline auto log2l(f128 x) -> f128
    {
        return __builtin_log2l(x);
    }
    inline auto logb(f64 x) -> f64
    {
        return __builtin_logb(x);
    }
    inline auto logbf(f32 x) -> f32
    {
        return __builtin_logbf(x);
    }
    inline auto logbl(f128 x) -> f128
    {
        return __builtin_logbl(x);
    }
    inline auto lrint(f64 x) -> i32
    {
        return __builtin_lrint(x);
    }
    inline auto lrintf(f32 x) -> i32
    {
        return __builtin_lrintf(x);
    }
    inline auto lrintl(f128 x) -> f128
    {
        return __builtin_lrintl(x);
    }
    inline auto lround(f64 x) -> i32
    {
        return __builtin_lround(x);
    }
    inline auto lroundf(f32 x) -> i32
    {
        return __builtin_lroundf(x);
    }
    inline auto lroundl(f128 x) -> i32
    {
        return __builtin_lroundl(x);
    }
    inline auto modf(f64 x, f64* y) -> f64
    {
        return __builtin_modf(x, y);
    }
    inline auto modff(f32 x, f32* y) -> f32
    {
        return __builtin_modff(x, y);
    }
    inline auto modfl(f128 x, f128* y) -> f128
    {
        return __builtin_modfl(x, y);
    }
    inline auto nan(const i8* s) -> f64
    {
        return __builtin_nan(s);
    }
    inline auto nanf(const i8* s) -> f32
    {
        return __builtin_nanf(s);
    }
    inline auto nanl(const i8* s) -> f128
    {
        return __builtin_nanl(s);
    }
    inline auto nearbyint(f64 x) -> f64
    {
        return __builtin_nearbyint(x);
    }
    inline auto nearbyintf(f32 x) -> f32
    {
        return __builtin_nearbyintf(x);
    }
    inline auto nearbyintl(f128 x) -> f128
    {
        return __builtin_nearbyintl(x);
    }
    inline auto nextafter(f64 x, f64 y) -> f64
    {
        return __builtin_nextafter(x, y);
    }
    inline auto nextafterf(f32 x, f32 y) -> f32
    {
        return __builtin_nextafterf(x, y);
    }
    inline auto nextafterl(f128 x, f128 y) -> f128
    {
        return __builtin_nextafterl(x, y);
    }
    inline auto nexttoward(f64 x, f128 y) -> f64
    {
        return __builtin_nexttoward(x, y);
    }
    inline auto nexttowardf(f32 x, f128 y) -> f32
    {
        return __builtin_nexttowardf(x, y);
    }
    inline auto nexttowardl(f128 x, f128 y) -> f128
    {
        return __builtin_nexttowardl(x, y);
    }
    inline auto pow(f64 x, f64 y) -> f64
    {
        return __builtin_pow(x, y);
    }
    inline auto powf(f32 x, f32 y) -> f32
    {
        return __builtin_powf(x, y);
    }
    inline auto powi(f64 x, i32 y) -> f64
    {
        return __builtin_powi(x, y);
    }
    inline auto powl(f128 x, f128 y) -> f128
    {
        return __builtin_powl(x, y);
    }
    inline auto remainder(f64 x, f64 y) -> f64
    {
        return __builtin_remainder(x, y);
    }
    inline auto remainderf(f32 x, f32 y) -> f32
    {
        return __builtin_remainderf(x, y);
    }
    inline auto remainderl(f128 x, f128 y) -> f128
    {
        return __builtin_remainderl(x, y);
    }
    inline auto remquo(f64 x, f64 y, i32* q) -> f64
    {
        return __builtin_remquo(x, y, q);
    }
    inline auto remquof(f32 x, f32 y, i32* q) -> f32
    {
        return __builtin_remquof(x, y, q);
    }
    inline auto remquol(f128 x, f128 y, i32* q) -> f128
    {
        return __builtin_remquol(x, y, q);
    }
    inline auto rint(f64 x) -> f64
    {
        return __builtin_rint(x);
    }
    inline auto rintf(f32 x) -> f32
    {
        return __builtin_rintf(x);
    }
    inline auto rintl(f128 x) -> f128
    {
        return __builtin_rintl(x);
    }
    inline auto round(f64 x) -> f64
    {
        return __builtin_round(x);
    }
    inline auto roundf(f32 x) -> f32
    {
        return __builtin_roundf(x);
    }
    inline auto roundl(f128 x) -> f128
    {
        return __builtin_roundl(x);
    }
    inline auto scalbln(f64 x, i32 y) -> f64
    {
        return __builtin_scalbln(x, y);
    }
    inline auto scalblnf(f32 x, i32 y) -> f32
    {
        return __builtin_scalblnf(x, y);
    }
    inline auto scalblnl(f128 x, i32 y) -> f128
    {
        return __builtin_scalblnl(x, y);
    }
    inline auto scalbn(f64 x, i32 y) -> f64
    {
        return __builtin_scalbn(x, y);
    }
    inline auto scalbnf(f32 x, i32 y) -> f32
    {
        return __builtin_scalbnf(x, y);
    }
    inline auto scalbnf(f128 x, i32 y) -> f128
    {
        return __builtin_scalbnf(x, y);
    }
    inline auto signbit(f64 x) -> bool
    {
        return __builtin_signbit(x) != 0;
    }
    inline auto signbitf(f32 x) -> bool
    {
        return __builtin_signbitf(x) != 0;
    }
    inline auto signbitl(f128 x) -> bool
    {
        return __builtin_signbitl(x) != 0;
    }
    inline auto sin(f64 x) -> f64
    {
        return __builtin_sin(x);
    }
    inline auto sinf(f32 x) -> f32
    {
        return __builtin_sinf(x);
    }
    inline auto sinh(f64 x) -> f64
    {
        return __builtin_sinh(x);
    }
    inline auto sinhf(f32 x) -> f32
    {
        return __builtin_sinhf(x);
    }
    inline auto sinhl(f128 x) -> f128
    {
        return __builtin_sinhl(x);
    }
    inline auto sinl(f128 x) -> f128
    {
        return __builtin_sinl(x);
    }
    inline auto sqrt(f64 x) -> f64
    {
        return __builtin_sqrt(x);
    }
    inline auto sqrtf(f32 x) -> f32
    {
        return __builtin_sqrtf(x);
    }
    inline auto sqrtl(f128 x) -> f128
    {
        return __builtin_sqrtl(x);
    }
    inline auto tan(f64 x) -> f64
    {
        return __builtin_tan(x);
    }
    inline auto tanf(f32 x) -> f32
    {
        return __builtin_tanf(x);
    }
    inline auto tanh(f64 x) -> f64
    {
        return __builtin_tanh(x);
    }
    inline auto tanhf(f32 x) -> f32
    {
        return __builtin_tanhf(x);
    }
    inline auto tanhl(f128 x) -> f128
    {
        return __builtin_tanhl(x);
    }
    inline auto tanl(f128 x) -> f128
    {
        return __builtin_tanl(x);
    }
    inline auto tgamma(f64 x) -> f64
    {
        return __builtin_tgamma(x);
    }
    inline auto tgammaf(f32 x) -> f32
    {
        return __builtin_tgammaf(x);
    }
    inline auto tgammal(f128 x) -> f128
    {
        return __builtin_tgammal(x);
    }
    inline auto trunc(f64 x) -> f64
    {
        return __builtin_trunc(x);
    }
    inline auto truncf(f32 x) -> f32
    {
        return __builtin_truncf(x);
    }
    inline auto truncl(f128 x) -> f128
    {
        return __builtin_truncl(x);
    }
    template<typename T>
    constexpr auto isnan(const T a)
    {
        return cast<bool>(__builtin_isnan(f128(a)));
    }
    template<typename T>
    constexpr auto isinf(const T a)
    {
        return cast<bool>(__builtin_isinf(a));
    }
    template<typename T>
    constexpr auto isnum(const T a)
    {
        return !(cast<bool>(__builtin_isnan(a))) && !(cast<bool>(__builtin_isinf(a)));
    }
    template<typename T>
    constexpr auto abs(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_abs(a)) : 0;
    }
    template<typename T>
    constexpr auto ceil(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_ceil(a)) : 0;
    }
    template<typename T>
    constexpr auto floor(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_floor(a)) : 0;
    }
    template<typename T>
    constexpr auto round(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_round(a)) : 0;
    }
    template<typename T>
    constexpr auto trunc(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_trunc(a)) : 0;
    }
    template<typename T>
    constexpr auto rint(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_rint(a)) : 0;
    }
    template<typename T>
    constexpr auto nearbyint(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_nearbyint(a)) : 0;
    }
    template<typename T, typename U>
    constexpr auto copysign(T a, U b)
    {
        return isnum(a) && isnum(b) ? cast<T>(__builtin_elementwise_copysign(a, b)) : 0;
    }
    template<typename T>
    constexpr auto sin(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_sin(a)) : 0;
    }
    template<typename T>
    constexpr auto cos(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_cos(a)) : 0;
    }
    template<typename T>
    constexpr auto addsat(T a, T b)
    {
        return isnum(a) && isnum(b) ? cast<T>(__builtin_elementwise_add_sat(a, b)) : 0;
    }
    template<typename T>
    constexpr auto subsat(T a, T b)
    {
        return isnum(a) && isnum(b) ? cast<T>(__builtin_elementwise_sub_sat(a, b)) : 0;
    }
    template<typename T>
    constexpr auto max(T a, T b)
    {
        return isnum(a) && isnum(b) ? cast<T>(__builtin_elementwise_max(a, b)) : 0;
    }
    template<typename T>
    constexpr auto min(T a, T b)
    {
        return isnum(a) && isnum(b) ? cast<T>(__builtin_elementwise_min(a, b)) : 0;
    }
    template<typename T>
    constexpr auto sqrt(T a)
    {
        return !isnan(a) ? cast<T>(__builtin_sqrt(a)) : 0;
    }
    template<typename T>
    constexpr auto log(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_log(a)) : 0;
    }
    template<typename T>
    constexpr auto log2(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_log2(a)) : 0;
    }
    template<typename T>
    constexpr auto log10(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_log10(a)) : 0;
    }
    template<typename T>
    constexpr auto exp(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_exp(a)) : 0;
    }
    template<typename T>
    inline auto exp2(T a)
    {
        return isnum(a) ? cast<T>(__builtin_elementwise_exp2(a)) : 0;
    }
    template<typename T, typename U>
    constexpr auto pow(T a, U b)
    {
        return isnum(a) && isnum(b) ? cast<T>(__builtin_elementwise_pow(a, b)) : 0;
    }
#endif // NO_BUILTIN
    using ID = u64;

    template<typename T>
    constexpr auto isnormal(const T a)
    {
        return cast<bool>(__builtin_isnormal(a));
    }
    template<typename T>
    constexpr auto isfinite(const T a)
    {
        return cast<bool>(__builtin_isfinite(a));
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
    constexpr auto cross(const T a[3], const T b[3], const T c[3]) noexcept
    {
        T vec[3][3];
        T dot;
        T result[3];
        vec[0][0] = a[1] * b[2] - a[2] * b[1];
        vec[0][1] = a[2] * b[0] - a[0] * b[2];
        vec[0][2] = a[0] * b[1] - a[1] * b[0];
        vec[1][0] = a[2] * c[1] - a[1] * c[2];
        vec[1][1] = a[0] * c[2] - a[2] * c[0];
        vec[1][2] = a[1] * c[0] - a[0] * c[1];
        vec[2][0] = a[1] * b[2] - a[2] * b[1];
        vec[2][1] = a[2] * b[0] - a[0] * b[2];
        vec[2][2] = a[0] * b[1] - a[1];
    }
    template<typename T>
    constexpr auto reverse(T _a)
    {
        T result = 0;
        for (u32 i = 0; i < sizeof(T); i++)
        {
            result = (result << 1) | (_a & 1);
            _a >>= 1;
        }
        return result;
    }
    template<typename T>
    constexpr auto bitset(T _a)
    {
        T result = 0;
        for (u32 i = 0; i < sizeof(T); i++)
        {
            result = (result << 1) | ((_a >> i) & 1);
        }
        return result;
    }

    template<typename T>
    constexpr auto hypot(T _a, T _b)
    {
        return cast<T>(__builtin_hypot(_a, _b));
    }
    template<typename T>
    constexpr auto square(const T _a)
    {
        return cast<T>(_a * _a);
    }
    template<typename T>
    constexpr auto madd(const T _a, T _b, const T _c)
    {
        return cast<T>(__builtin_elementwise_add_sat((_a * _b), _c));
    }
    template<typename T>
    constexpr auto sign(const T _a)
    {
        return cast<T>(__builtin_copysign(_a));
    }
    template<typename T>
    constexpr auto clamp(const T _a, const T _b, const T _c)
    {
        return min(max(_a, _b), _c);
    }
    template<typename T>
    constexpr auto step(const T _a, const T _b)
    {
        return clamp(_b - _a, 0.0, 1.0);
    }
    template<typename T>
    constexpr auto fract(const T _a)
    {
        return _a - __builtin_floor(_a);
    }
    template<typename T>
    constexpr auto lerp(const T _a, const T _b, const T _t)
    {
        return _a + (_b - _a) * _t;
    }
    template<typename T>
    constexpr auto smoothstep(const T _a, const T _b, const T _t)
    {
        auto t = clamp(_t - _a / _b - _a, 0.0, 1.0);
        return t * t * 3.0 - 2.0 * t;
    }
    template<typename T>
    constexpr auto rsqrt(const T _a)
    {
        if (isnan(_a))
        {
            return 0;
        }
        return 1.0 / sqrt(_a);
    }
    template<typename T>
    constexpr auto dot(const T _a, const T _b)
    {
        return _a * _b;
    }
    template<typename T>
    constexpr auto length(T _a, T _b)
    {
        return sqrt(_a * _a + _b * _b);
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
    auto mul(const T _a, const T _b)
    {
        try
        {
            return (_a * _b);
        }
        catch (...)
        {
            return cast<T>(0);
        };
    }
    template<typename T>
    auto neg(const T _a)
    {
        try
        {
            mul(_a, -1);
        }
        catch (...)
        {
            return 0;
        };
    }

    template<typename T>
    constexpr auto random(T _min, T _max)
    {
        return rand() % u64(_max - _min) + _min;
    }
    template<typename T>
    constexpr auto tan(T _a)
    {
        return __builtin_tan(_a);
    }
    template<typename T>
    constexpr auto asin(T _a)
    {
        return __builtin_asin(_a);
    }
    template<typename T>
    constexpr auto acos(T _a)
    {
        return __builtin_acos(_a);
    }
    template<typename T>
    constexpr auto atan(T _a)
    {
        return __builtin_atan(_a);
    }
    template<typename T>
    constexpr auto atan2(T _a, T _b)
    {
        return __builtin_atan2(_a, _b);
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
        f64 MemSize = 0.0;
        f64 MemUsed = 0.0;
        f64 MemMax = 1.000000e+15;

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
        } MemUnit = Unit::BYTE;
        explicit Mem(enum Unit unit = Unit::BYTE) :
            MemUnit(unit)
        {
            MemSize = MemUsed = 0.0;
        }
        explicit Mem(f64 size, f64 used = 0.0, enum Unit unit = Unit::BYTE) :
            MemSize(size), MemUsed(used < size ? used : size), MemUnit(unit)
        {
        }
        Mem(const Mem& rhs) { *this = rhs; }
        Mem(Mem&& rhs) noexcept { *this = std::move(rhs); }
        ~Mem()
        {
            MemSize = MemUsed = 0.0;
            MemUnit = Unit::BYTE;
        }
        [[nodiscard]] auto convert(const enum Unit unit) const -> Mem
        {
            const u8 one = 1;
            const u8 unit0 = static_cast<u8>(MemUnit) * 10;
            const u8 unit1 = static_cast<u8>(unit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return Mem(MemSize * ratio, MemUsed * ratio, unit);
        }
        [[nodiscard]] auto convert(const Mem& mem) const -> Mem
        {
            const u8 one = 1;
            if (mem.MemUnit == Unit::NONE)
            {
                return Mem{ MemSize, MemUsed, MemUnit };
            };
            const u8 unit0 = static_cast<u8>(MemUnit) * 10;
            const u8 unit1 = static_cast<u8>(mem.MemUnit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return Mem{ mem.MemSize * ratio, mem.MemUsed * ratio, mem.MemUnit };
        }
        auto operator[](enum Unit unit) const { return convert(unit); }
        auto operator=(const Mem& rhs) -> Mem& = default;
        auto operator=(Mem&& rhs) noexcept -> Mem& { return *this = rhs; }
        [[nodiscard]] constexpr auto size() const -> f64 { return MemSize; }
        [[nodiscard]] constexpr auto total() const -> f64 { return size(); }
        [[nodiscard]] constexpr auto available() const -> f64 { return MemSize - MemUsed; }
        [[nodiscard]] constexpr auto used() const -> f64 { return MemUsed; }
        [[nodiscard]] constexpr auto free() const -> f64 { return MemSize - MemUsed; }
        [[nodiscard]] constexpr auto percentage() const -> f64 { return ((MemUsed) / (MemSize)) * 100.0; }
        [[nodiscard]] constexpr auto percentage_used() const -> f64 { return ((MemUsed) / (MemSize)) * 100.0; }
        [[nodiscard]] constexpr auto percentage_free() const -> f64 { return ((MemSize) / (MemUsed)) * 100.0; }
        constexpr auto set(const f64 size = -1, const f64 used = -1, enum Unit unit = Unit::NONE) -> Mem&
        {
            if (unit != Unit::NONE)
            {
                if (size >= 0.0 && size < MemMax)
                {
                    MemSize = size;
                }
                if (used >= 0.0 && used <= MemSize)
                {
                    MemUsed = used;
                }
                if (unit >= Unit::BYTE && unit <= Unit::PBYTE && unit != MemUnit)
                {
                    MemUnit = unit;
                }
            }
            return *this;
        }
    } __attribute__((aligned(32))) __attribute__((packed));

} // namespace Origin
