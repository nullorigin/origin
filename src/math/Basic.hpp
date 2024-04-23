#pragma once
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <emmintrin.h>
#include <cmath>
#include <utility>
#include <immintrin.h>
#include <xmmintrin.h>
#include <string>
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
    using f32p = float*;
    using f64p = double*;
    using f128p = long double*;
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
    typedef unsigned long SIZE_T;
#else
    using size_t = unsigned long long;
#endif
    static const u32 C8 = 0xff, C16 = 0xffff, C32 = 0xffffff, C64 = 0xffffffff;
    constexpr f64 PI = 3.14159265358979323846535897932384;
#define i8_C(c) c
#define u8_C(c) c
#define s8_C(c) c
#define i16_C(c) c
#define u16_C(c) c
#define s16_C(c) c
#define i32_C(c) c
#define u32_C(c) c##U
#define s32_C(c) c
#if WORDSIZE == 64
#define i64_C(c) c##L
#define s64_C(c) c##L
#define u64_C(c) c##UL
#else
#define i64_C(c) c##LL
#define u64_C(c) c##ULL
#define s64_C(c) c##LL
#endif
#define f32_C(c) c##f
#define f64_C(c) c
#define f128_C(c) c##d
#define u64_C2(h, l) ((static_cast<u64>(h) << 32) | static_cast<u64>(l))
#define imax8 I8_C(127)
#define imax16 I16_C(32767)
#define imax32 I32_C(2147483647)
#define imax64 I64_C(9223372036854775807)
#define umax8 U8_C(255)
#define umax16 U16_C(65535)
#define umax32 U32_C(4294967295)
#define umax64 U64_C(18446744073709551615)
#define smax8 S8_C(127)
#define smax16 S16_C(32767)
#define smax32 S32_C(2147483647)
#define smax64 S64_C(9223372036854775807)
#define fmax32 F32_C(3.40282346638528859811704183484516925440e+38f)
#define fmax64 F64_C(1.797693134862315708145274237317043567981e+308)
#define fmax128 F128_C(1.18973149535723176508575932662800702e+4932)
#define imin8 I8_C(-128)
#define imin16 I16_C(-32768)
#define imin32 I32_C(-2147483648)
#define umin8 U8_C(0)
#define umin16 U16_C(0)
#define umin32 U32_C(0)
#define umin64 U64_C(0)
#define smin8 S8_C(-128)
#define smin16 S16_C(-32768)
#define smin16 S16_C(-32768)
#define smin32 S32_C(-2147483648)
#define smin64 S64_C(-9223372036854775808)
#define fmin32 F32_C(-3.40282346638528859811704183484516925440e+38f)
#define fmin64 F64_C(-1.797693134862315708145274237317043567981e+308)
#define fmin128 F128_C(-1.18973149535723176508575932662800702e+4932)
#define fe32 F32_C(1.1920928955078125e-07f)
#define fe64 F64_C(2.220446049250313080847263336181640625e-16)
#define fe128 F128_C(1.9259299443872358530559779425849159658203125e-34)
#ifndef NULL
#define NULL ((void*)0)
#endif
#define null ((void*)0)
#ifndef NO_BUILTIN
    inline double abs(double x)
    {
        return __builtin_fabs(x);
    }
    inline float abs(float x)
    {
        return __builtin_fabsf(x);
    }
    inline long double abs(long double x)
    {
        return __builtin_fabsl(x);
    }

    inline double acos(double x)
    {
        return __builtin_acos(x);
    }
    inline float acos(float x)
    {
        return __builtin_acosf(x);
    }
    inline long double acos(long double x)
    {
        return __builtin_acosl(x);
    }

    inline double acosh(double x)
    {
        return __builtin_acosh(x);
    }
    inline float acosh(float x)
    {
        return __builtin_acoshf(x);
    }
    inline long double acosh(long double x)
    {
        return __builtin_acoshl(x);
    }

    inline double asin(double x)
    {
        return __builtin_asin(x);
    }
    inline float asin(float x)
    {
        return __builtin_asinf(x);
    }
    inline long double asin(long double x)
    {
        return __builtin_asinl(x);
    }

    inline double asinh(double x)
    {
        return __builtin_asinh(x);
    }
    inline float asinh(float x)
    {
        return __builtin_asinhf(x);
    }
    inline long double asinh(long double x)
    {
        return __builtin_asinhl(x);
    }

    inline double atan(double x)
    {
        return __builtin_atan(x);
    }
    inline float atan(float x)
    {
        return __builtin_atanf(x);
    }
    inline long double atan(long double x)
    {
        return __builtin_atanl(x);
    }

    inline double atan2(double x, double y)
    {
        return __builtin_atan2(x, y);
    }
    inline float atan2(float x, float y)
    {
        return __builtin_atan2f(x, y);
    }
    inline long double atan2(long double x, long double y)
    {
        return __builtin_atan2l(x, y);
    }

    inline double cbrt(double x)
    {
        return __builtin_cbrt(x);
    }
    inline float cbrt(float x)
    {
        return __builtin_cbrtf(x);
    }
    inline long double cbrt(long double x)
    {
        return __builtin_cbrtl(x);
    }

    inline double ceil(double x)
    {
        return __builtin_ceil(x);
    }
    inline float ceil(float x)
    {
        return __builtin_ceilf(x);
    }
    inline long double ceil(long double x)
    {
        return __builtin_ceill(x);
    }

    inline double copysign(double x, double y)
    {
        return __builtin_copysign(x, y);
    }
    inline float copysign(float x, float y)
    {
        return __builtin_copysignf(x, y);
    }
    inline long double copysign(long double x, long double y)
    {
        return __builtin_copysignl(x, y);
    }

    inline double cos(double x)
    {
        return __builtin_cos(x);
    }
    inline float cos(float x)
    {
        return __builtin_cosf(x);
    }
    inline long double cos(long double x)
    {
        return __builtin_cosl(x);
    }

    inline double cosh(double x)
    {
        return __builtin_cosh(x);
    }
    inline float cosh(float x)
    {
        return __builtin_coshf(x);
    }
    inline long double cosh(long double x)
    {
        return __builtin_coshl(x);
    }

    inline double erf(double x)
    {
        return __builtin_erf(x);
    }
    inline float erf(float x)
    {
        return __builtin_erff(x);
    }
    inline long double erf(long double x)
    {
        return __builtin_erfl(x);
    }

    inline double erfc(double x)
    {
        return __builtin_erfc(x);
    }
    inline float erfc(float x)
    {
        return __builtin_erfcf(x);
    }
    inline long double erfc(long double x)
    {
        return __builtin_erfcl(x);
    }

    inline double exp(double x)
    {
        return __builtin_exp(x);
    }
    inline float exp(float x)
    {
        return __builtin_expf(x);
    }
    inline long double exp(long double x)
    {
        return __builtin_expl(x);
    }

    inline double exp2(double x)
    {
        return __builtin_exp2(x);
    }
    inline float exp2(float x)
    {
        return __builtin_exp2f(x);
    }
    inline long double exp2(long double x)
    {
        return __builtin_exp2l(x);
    }

    inline double fdim(double x, double y)
    {
        return __builtin_fdim(x, y);
    }
    inline float fdim(float x, float y)
    {
        return __builtin_fdimf(x, y);
    }
    inline long double fdim(long double x, long double y)
    {
        return __builtin_fdiml(x, y);
    }

    inline double floor(double x)
    {
        return __builtin_floor(x);
    }
    inline float floor(float x)
    {
        return __builtin_floorf(x);
    }
    inline long double floor(long double x)
    {
        return __builtin_floorl(x);
    }

    inline double fma(double x, double y, double z)
    {
        return __builtin_fma(x, y, z);
    }
    inline float fma(float x, float y, float z)
    {
        return __builtin_fmaf(x, y, z);
    }
    inline long double fma(long double x, long double y, long double z)
    {
        return __builtin_fmal(x, y, z);
    }

    inline double fmax(double x, double y)
    {
        return __builtin_fmax(x, y);
    }
    inline float fmax(float x, float y)
    {
        return __builtin_fmaxf(x, y);
    }
    inline long double fmax(long double x, long double y)
    {
        return __builtin_fmaxl(x, y);
    }

    inline double fmin(double x, double y)
    {
        return __builtin_fmin(x, y);
    }
    inline float fmin(float x, float y)
    {
        return __builtin_fminf(x, y);
    }
    inline long double fmin(long double x, long double y)
    {
        return __builtin_fminl(x, y);
    }

    inline double fmod(double x, double y)
    {
        return __builtin_fmod(x, y);
    }
    inline float fmod(float x, float y)
    {
        return __builtin_fmodf(x, y);
    }
    inline long double fmod(long double x, long double y)
    {
        return __builtin_fmodl(x, y);
    }

    inline int fpclassify(int a, int b, int c, int d, int e, float f)
    {
        return __builtin_fpclassify(a, b, c, d, e, f);
    }

    inline double hypot(double x, double y)
    {
        return __builtin_hypot(x, y);
    }
    inline float hypot(float x, float y)
    {
        return __builtin_hypotf(x, y);
    }
    inline long double hypot(long double x, long double y)
    {
        return __builtin_hypotl(x, y);
    }

    inline int ilogb(double x)
    {
        return __builtin_ilogb(x);
    }
    inline int ilogb(float x)
    {
        return __builtin_ilogbf(x);
    }
    inline int ilogb(long double x)
    {
        return __builtin_ilogbl(x);
    }

    inline bool isfinite(double x)
    {
        return __builtin_isfinite(x) != 0;
    }
    inline bool isfinite(float x)
    {
        return __builtin_isfinite(x) != 0;
    }
    inline bool isfinite(long double x)
    {
        return __builtin_isfinite(x) != 0;
    }

    inline bool isgreater(double x, double y)
    {
        return __builtin_isgreater(x, y) != 0;
    }
    inline bool isgreater(float x, float y)
    {
        return __builtin_isgreater(x, y) != 0;
    }
    inline bool isgreater(long double x, long double y)
    {
        return __builtin_isgreater(x, y) != 0;
    }

    inline bool isgreaterequal(double x, double y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline bool isgreaterequal(float x, float y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline bool isgreaterequal(long double x, long double y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline long double lgammal(long double x)
    {
        return __builtin_lgammal(x);
    }
    inline long long llrint(double x)
    {
        return __builtin_llrint(x);
    }
    inline long long llrintf(float x)
    {
        return __builtin_llrintf(x);
    }
    inline long long llrintl(long double x)
    {
        return __builtin_llrintl(x);
    }
    inline long long llround(double x)
    {
        return __builtin_llround(x);
    }
    inline long long llroundf(float x)
    {
        return __builtin_llroundf(x);
    }
    inline long long llroundl(long double x)
    {
        return __builtin_llroundl(x);
    }
    inline double log(double x)
    {
        return __builtin_log(x);
    }
    inline float logf(float x)
    {
        return __builtin_logf(x);
    }
    inline long double logl(long double x)
    {
        return __builtin_logl(x);
    }
    inline double log10(double x)
    {
        return __builtin_log10(x);
    }
    inline float log10f(float x)
    {
        return __builtin_log10f(x);
    }
    inline long double log10l(long double x)
    {
        return __builtin_log10l(x);
    }
    inline double log1p(double x)
    {
        return __builtin_log1p(x);
    }
    inline float log1pf(float x)
    {
        return __builtin_log1pf(x);
    }
    inline long double log1pl(long double x)
    {
        return __builtin_log1pl(x);
    }
    inline double log2(double x)
    {
        return __builtin_log2(x);
    }
    inline float log2f(float x)
    {
        return __builtin_log2f(x);
    }
    inline long double log2l(long double x)
    {
        return __builtin_log2l(x);
    }
    inline double logb(double x)
    {
        return __builtin_logb(x);
    }
    inline float logbf(float x)
    {
        return __builtin_logbf(x);
    }
    inline long double logbl(long double x)
    {
        return __builtin_logbl(x);
    }
    inline long lrint(double x)
    {
        return __builtin_lrint(x);
    }
    inline long int lrintf(float x)
    {
        return __builtin_lrintf(x);
    }
    inline long double lrintl(long double x)
    {
        return __builtin_lrintl(x);
    }
    inline long lround(double x)
    {
        return __builtin_lround(x);
    }
    inline long lroundf(float x)
    {
        return __builtin_lroundf(x);
    }
    inline long lroundl(long double x)
    {
        return __builtin_lroundl(x);
    }
    inline double modf(double x, double* y)
    {
        return __builtin_modf(x, y);
    }
    inline float modff(float x, float* y)
    {
        return __builtin_modff(x, y);
    }
    inline long double modfl(long double x, long double* y)
    {
        return __builtin_modfl(x, y);
    }
    inline double nan(const char* s)
    {
        return __builtin_nan(s);
    }
    inline float nanf(const char* s)
    {
        return __builtin_nanf(s);
    }
    inline long double nanl(const char* s)
    {
        return __builtin_nanl(s);
    }
    inline double nearbyint(double x)
    {
        return __builtin_nearbyint(x);
    }
    inline float nearbyintf(float x)
    {
        return __builtin_nearbyintf(x);
    }
    inline long double nearbyintl(long double x)
    {
        return __builtin_nearbyintl(x);
    }
    inline double nextafter(double x, double y)
    {
        return __builtin_nextafter(x, y);
    }
    inline float nextafterf(float x, float y)
    {
        return __builtin_nextafterf(x, y);
    }
    inline long double nextafterl(long double x, long double y)
    {
        return __builtin_nextafterl(x, y);
    }
    inline double nexttoward(double x, long double y)
    {
        return __builtin_nexttoward(x, y);
    }
    inline float nexttowardf(float x, long double y)
    {
        return __builtin_nexttowardf(x, y);
    }
    inline long double nexttowardl(long double x, long double y)
    {
        return __builtin_nexttowardl(x, y);
    }
    inline double pow(double x, double y)
    {
        return __builtin_pow(x, y);
    }
    inline float powf(float x, float y)
    {
        return __builtin_powf(x, y);
    }
    inline double powi(double x, int y)
    {
        return __builtin_powi(x, y);
    }
    inline long double powl(long double x, long double y)
    {
        return __builtin_powl(x, y);
    }
    inline double remainder(double x, double y)
    {
        return __builtin_remainder(x, y);
    }
    inline float remainderf(float x, float y)
    {
        return __builtin_remainderf(x, y);
    }
    inline long double remainderl(long double x, long double y)
    {
        return __builtin_remainderl(x, y);
    }
    inline double remquo(double x, double y, int* q)
    {
        return __builtin_remquo(x, y, q);
    }
    inline float remquof(float x, float y, int* q)
    {
        return __builtin_remquof(x, y, q);
    }
    inline long double remquol(long double x, long double y, int* q)
    {
        return __builtin_remquol(x, y, q);
    }
    inline double rint(double x)
    {
        return __builtin_rint(x);
    }
    inline float rintf(float x)
    {
        return __builtin_rintf(x);
    }
    inline long double rintl(long double x)
    {
        return __builtin_rintl(x);
    }
    inline double round(double x)
    {
        return __builtin_round(x);
    }
    inline float roundf(float x)
    {
        return __builtin_roundf(x);
    }
    inline long double roundl(long double x)
    {
        return __builtin_roundl(x);
    }
    inline double scalbln(double x, int y)
    {
        return __builtin_scalbln(x, y);
    }
    inline float scalblnf(float x, int y)
    {
        return __builtin_scalblnf(x, y);
    }
    inline long double scalblnl(long double x, int y)
    {
        return __builtin_scalblnl(x, y);
    }
    inline double scalbn(double x, int y)
    {
        return __builtin_scalbn(x, y);
    }
    inline float scalbnf(float x, int y)
    {
        return __builtin_scalbnf(x, y);
    }
    inline long double scalbnf(long double x, int y)
    {
        return __builtin_scalbnf(x, y);
    }
    inline bool signbit(double x)
    {
        return __builtin_signbit(x) != 0;
    }
    inline bool signbitf(float x)
    {
        return __builtin_signbitf(x) != 0;
    }
    inline bool signbitl(long double x)
    {
        return __builtin_signbitl(x) != 0;
    }
    inline double sin(double x)
    {
        return __builtin_sin(x);
    }
    inline float sinf(float x)
    {
        return __builtin_sinf(x);
    }
    inline double sinh(double x)
    {
        return __builtin_sinh(x);
    }
    inline float sinhf(float x)
    {
        return __builtin_sinhf(x);
    }
    inline long double sinhl(long double x)
    {
        return __builtin_sinhl(x);
    }
    inline long double sinl(long double x)
    {
        return __builtin_sinl(x);
    }
    inline double sqrt(double x)
    {
        return __builtin_sqrt(x);
    }
    inline float sqrtf(float x)
    {
        return __builtin_sqrtf(x);
    }
    inline long double sqrtl(long double x)
    {
        return __builtin_sqrtl(x);
    }
    inline double tan(double x)
    {
        return __builtin_tan(x);
    }
    inline float tanf(float x)
    {
        return __builtin_tanf(x);
    }
    inline double tanh(double x)
    {
        return __builtin_tanh(x);
    }
    inline float tanhf(float x)
    {
        return __builtin_tanhf(x);
    }
    inline long double tanhl(long double x)
    {
        return __builtin_tanhl(x);
    }
    inline long double tanl(long double x)
    {
        return __builtin_tanl(x);
    }
    inline double tgamma(double x)
    {
        return __builtin_tgamma(x);
    }
    inline float tgammaf(float x)
    {
        return __builtin_tgammaf(x);
    }
    inline long double tgammal(long double x)
    {
        return __builtin_tgammal(x);
    }
    inline double trunc(double x)
    {
        return __builtin_trunc(x);
    }
    inline float truncf(float x)
    {
        return __builtin_truncf(x);
    }
    inline long double truncl(long double x)
    {
        return __builtin_truncl(x);
    }
    template<typename T>
    inline auto abs(T a)
    {
        return __builtin_elementwise_abs(a);
    }
    template<typename T>
    inline auto ceil(T a)
    {
        return __builtin_elementwise_ceil(a);
    }
    template<typename T>
    inline auto floor(T a)
    {
        return __builtin_elementwise_floor(a);
    }
    template<typename T>
    inline auto Round(T a)
    {
        return __builtin_elementwise_round(a);
    }
    template<typename T>
    inline auto trunc(T a)
    {
        return __builtin_elementwise_trunc(a);
    }
    template<typename T>
    inline auto rint(T a)
    {
        return __builtin_elementwise_rint(a);
    }
    template<typename T>
    inline auto nearbyint(T a)
    {
        return __builtin_elementwise_nearbyint(a);
    }
    template<typename T, typename U>
    inline auto copysign(T a, U b)
    {
        return __builtin_elementwise_copysign(a, b);
    }
    template<typename T>
    inline auto sin(T a)
    {
        return __builtin_elementwise_sin(a);
    }
    template<typename T>
    inline auto cos(T a)
    {
        return __builtin_elementwise_cos(a);
    }
    template<typename T>
    inline auto add_sat(T a, T b)
    {
        return __builtin_elementwise_add_sat(a, b);
    }
    template<typename T>
    inline auto sub_sat(T a, T b)
    {
        return __builtin_elementwise_sub_sat(a, b);
    }
    template<typename T, typename U>
    inline auto max(T a, U b)
    {
        return __builtin_elementwise_max(a, b);
    }
    template<typename T, typename U>
    inline auto min(T a, U b)
    {
        return __builtin_elementwise_min(a, b);
    }
    template<typename T>
    inline auto sqrt(T a)
    {
        return __builtin_elementwise_sqrt(a);
    }
    template<typename T>
    inline auto log(T a)
    {
        return __builtin_elementwise_log(a);
    }
    template<typename T>
    inline auto log2(T a)
    {
        return __builtin_elementwise_log2(a);
    }
    template<typename T>
    inline auto log10(T a)
    {
        return __builtin_elementwise_log10(a);
    }
    template<typename T>
    inline auto exp(T a)
    {
        return __builtin_elementwise_exp(a);
    }
    template<typename T>
    inline auto exp2(T a)
    {
        return __builtin_elementwise_exp2(a);
    }
    template<typename T, typename U>
    inline auto pow(T a, U b)
    {
        return __builtin_elementwise_pow(a, b);
    }
#endif // NO_BUILTIN
    using ID = u64;
    template<typename T>
    inline auto isnum(const T _a) -> bool
    {
        return !(bool(isnan(_a))) && !(bool(isinf(_a)));
    }
    template<typename T>
    inline constexpr auto IsNan(const T _a) -> bool
    {
        return bool(isnan(_a));
    }
    template<typename T>
    inline constexpr auto IsInf(const T _a) -> bool
    {
        return bool(isinf(_a));
    }
    template<typename T, u64 N>
    inline constexpr auto Cross(const T a[N], const T b[N], const T c[N]) noexcept
        -> T*
    {
        T vec[3][N];
        T dot;
        T result[N];
        for (u32 i = 0; i < N; i += 3)
        {
            vec[0][i] = a[i];
            vec[1][i] = b[i];
            vec[2][i] = c[i];
            vec[0][i + 1] = a[i + 1];
            vec[1][i + 1] = b[i + 1];
            vec[2][i + 1] = c[i + 1];
            vec[0][i + 2] = a[i + 2];
            vec[1][i + 2] = b[i + 2];
            vec[2][i + 2] = c[i + 2];
            vec[1][i] =
                (vec[2][i + 1] * vec[0][i + 2]) - (vec[0][i + 1] * vec[2][i + 2]);
            vec[2][i] =
                -(vec[1][i + 1] * vec[0][i + 2]) + (vec[0][i + 1] * vec[1][i + 2]);
            vec[0][i] =
                (vec[1][i + 1] * vec[2][i + 2]) - (vec[2][i + 1] * vec[1][i + 2]);
            dot = vec[1][0] * vec[2][1] + vec[1][1] * vec[2][2] + vec[1][2] * vec[2][0];
            result[i] = vec[0][0] * dot;
            result[i + 1] = vec[0][1] * dot;
            result[i + 2] = vec[0][2] * dot;
        }
        return result;
    }
    template<typename T>
    inline constexpr auto Floor(const T _a) -> T
    {
        return __builtin_elementwise_floor(_a);
    }
    template<typename T>
    inline constexpr auto Ceil(const T _a) -> T
    {
        return __builtin_elementwise_ceil(_a);
    }
    template<typename T>
    inline constexpr auto Hypot(T _a, T _b) -> T
    {
        return T(hypot(f64(_a), f64(_b)));
    }
    template<typename T>
    inline constexpr auto Square(const T _a) -> T
    {
        return T(_a * _a);
    }
    template<typename T>
    inline constexpr auto Madd(const T _a, T _b, const T _c) -> T
    {
        return T(_a * _b + _c);
    }
    template<typename T>
    inline constexpr auto Sqrt(const T _a) noexcept -> T
    {
        return __builtin_sqrt(_a);
    }
    template<typename T>
    inline constexpr auto Min(const T _a, const T _b) -> T
    {
        return __builtin_elementwise_min(_a, _b);
    }
    template<typename T>
    inline constexpr auto Max(const T _a, const T _b) -> T
    {
        return __builtin_elementwise_max(_a, _b);
    }
    template<typename T>
    inline constexpr auto Abs(const T _a) -> T
    {
        return ABS(_a);
    }
    template<typename T>
    inline constexpr auto Sign(const T _a) -> T
    {
        return T(_a < 0 ? -1 : 1);
    }
    template<typename T>
    inline constexpr auto Step(const T _a, const T _b) -> T
    {
        return T(_a < _b ? 0 : 1);
    }
    template<typename T>
    inline constexpr auto Fract(const T _a) -> T
    {
        return T(_a - Floor(_a));
    }
    template<typename T>
    inline constexpr auto Lerp(const T _a, const T _b, const T _t) -> T
    {
        return T(_a + (_b - _a) * _t);
    }
    template<typename T>
    inline constexpr auto SmoothStep(const T _a, const T _b, const T _t) -> T
    {
        T t = T(Clamp((_t - _a) / (_b - _a), T(0.0), T(1.0)));
        return T(t * t * (T(3.0) - T(2.0) * t));
    }
    template<typename T>
    inline constexpr auto RSqrt(const T _a) -> T
    {
        if (IsNan(_a))
        {
            return 0;
        }
        return T(1.0 / Sqrt(_a));
    }
    template<typename T>
    inline constexpr auto Round(const T _a) -> T
    {
        return __builtin_elementwise_round(_a);
    }
    template<typename T>
    inline constexpr auto Trunc(const T _a) noexcept -> T
    {
        return __builtin_elementwise_trunc(_a);
    }
    template<typename T>
    inline constexpr auto Dot(const T _a, const T _b) -> T
    {
        return T(_a * _b);
    }
    template<typename T>
    inline constexpr auto Length(T _a, T _b) -> T
    {
        return T(Sqrt((_a * _a) + (_b * _b)));
    }
    template<typename T, u64 N>
    inline constexpr auto Normalize(const T _a[N]) -> T*
    {
        u32 i = 0;
        T* ret[N];
        for (i = 0; i < N; i++)
        {
            *ret[i] = _a[i] / Length(_a[i], _a[i + 1]);
        }
        return *ret;
    }
    template<typename T>
    inline constexpr auto Neg(const T _a) -> T
    {
        return -_a;
    }
    template<typename T>
    inline constexpr auto Sub(const T _a, const T _b) -> T
    {
        return __builtin_elementwise_sub_sat(_a, _b);
    }
    template<typename T>
    inline constexpr auto Add(const T _a, const T _b) -> T
    {
        return __builtin_elementwise_add_sat(_a, _b);
    }
    template<typename T>
    inline constexpr auto Mul(const T _a, const T _b) -> T
    {
        return T(_a * _b);
    }
    template<typename T>
    inline constexpr T Clamp(const T _a, const T _b, const T _c)
    {
        return T(Max(Min(_a, _b), _c));
    }
    template<typename T>
    inline constexpr auto Rand(T _min, T _max, u32 _seed = 0) -> T
    {
        return T(srand(_seed) % (_max - _min) + _min);
    }
    template<typename T>
    inline constexpr auto Sin(T _a) noexcept -> T
    {
        return __builtin_elementwise_sin(_a);
    }
    template<typename T>
    inline constexpr auto Cos(T _a) noexcept -> T
    {
        return __builtin_elementwise_cos(_a);
    }
    template<typename T>
    inline constexpr auto Tan(T _a) noexcept -> T
    {
        return T(tan(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Asin(T _a) noexcept -> T
    {
        return T(asin(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Acos(T _a) noexcept -> T
    {
        return T(acos(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Atan(T _a) noexcept -> T
    {
        return T(atan(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Atan2(T _a, T _b) noexcept -> T
    {
        return T(Atan2(f64(_a), f64(_b)));
    }
    template<typename T>
    inline auto Log(T _a) noexcept -> T
    {
        return __builtin_elementwise_log(_a);
    }
    template<typename T>
    inline auto Log2(T _x) noexcept -> T
    {
        return __builtin_elementwise_log2(_x);
    }
    template<typename T>
    inline auto Log10(T _a) noexcept -> T
    {
        return __builtin_elementwise_log10(_a);
    }

    struct Complex
    {
        union
        {
            __m128d v;
            struct
            {
                f64 real = 0;
                f64 imag = 0;
            };
        };
        Complex() = default;
        Complex(f64 _real, f64 _imag) :
            real(_real), imag(_imag) {}
        static auto Zero() -> Complex { return Complex(0, 0); }

        static auto Add(const Complex A, const Complex B) noexcept -> Complex
        {
            return { A.real + B.real, A.imag + B.imag };
        }
        static auto Sub(const Complex A, const Complex B) noexcept -> Complex
        {
            return { A.real - B.real, A.imag - B.imag };
        }

        auto Mul(const Complex b) const -> Complex
        {
            return { real * b.real - imag * b.imag, real * b.imag + imag * b.real };
        }
        auto Mul(f64* aPtr) const noexcept -> f64*
        {
            __m256d a = _mm256_loadu_pd(aPtr);
            __m256d b = _mm256_setr_pd(real, imag, aPtr[2], aPtr[3]);
            _mm256_storeu_pd(aPtr, _mm256_mul_pd(a, b));
            return aPtr;
        }

        static auto Div(Complex a, Complex b) noexcept -> Complex
        {
            __m128d num = _mm_setr_pd(a.real, a.imag);
            __m128d den = _mm_setr_pd(b.real, b.imag);
            return { _mm_cvtsd_f64(_mm_div_pd(num, den)), _mm_cvtsd_f64(_mm_div_pd(den, num)) };
        }
        static auto FFT(const Complex* input, u64 size) -> Complex*
        {
            Complex* out = new Complex[size];
            u64 half_size = size >> 1;
            const __m256d wn = _mm256_setr_pd(-2 * M_PI / size, M_PI / size, -2 * M_PI / size, M_PI / size);

            // Divide input into even and odd parts
            for (u64 i = 0; i < size; i += 4)
            {
                __m256d a = _mm256_loadu_pd(&input[i].real);
                __m256d b = _mm256_loadu_pd(&input[i + half_size].real);
                _mm256_storeu_pd(&out[i].real, _mm256_add_pd(a, b));
                _mm256_storeu_pd(&out[i + half_size].real, _mm256_sub_pd(a, b));
            }

            for (u64 n = 4, m = 2; n <= size; n <<= 2, m = n >> 1)
            {
                const __m256d w = _mm256_mul_pd(wn, _mm256_set1_pd(static_cast<double>(m)));
                for (u64 i = 0; i < size; i += n)
                {
                    for (u64 j = i; j < i + m; j += 4)
                    {
                        __m256d a = _mm256_loadu_pd(&out[j].real);
                        __m256d b = _mm256_loadu_pd(&out[j + m].real);
                        __m256d t = _mm256_add_pd(_mm256_sub_pd(a, b), _mm256_mul_pd(_mm256_sub_pd(_mm256_mul_pd(a, w), _mm256_mul_pd(b, w)), _mm256_setr_pd(j, j + 1, j + 2, j + 3)));
                        _mm256_storeu_pd(&out[j].real, _mm256_add_pd(a, b));
                        _mm256_storeu_pd(&out[j + m].real, t);
                    }
                }
            }

            // Bit reverse
            for (u64 i = 1, j = 0; i < size; ++i)
            {
                u64 x = i;
                u64 k = size >> 1;
                while (j >= k)
                {
                    x = (x ^ (j & ~k)) & (size - 1);
                    j &= k;
                    k >>= 1;
                }
                if (i < (j |= k))
                {
                    std::swap(out[i], out[j]);
                }
            }

            // Normalize
            const __m256d norm = _mm256_set1_pd(1.0 / size);
            for (u64 i = 0; i < size; i += 4)
            {
                __m256d v = _mm256_loadu_pd(&out[i].real);
                _mm256_storeu_pd(&out[i].real, _mm256_mul_pd(v, norm));
            }
            return out;
        }
        static Complex* FFT2(Complex* _C1, const u64 N)
        {
            auto* C = reinterpret_cast<Complex*>(_C1);

            // Cooley–Tukey FFT (in-place)
            for (u64 s = 1, s_half = 1; s < N; s <<= 2, s_half = s >> 1)
            {
                __m256d wn = _mm256_setr_pd(-2 * M_PI / s, M_PI / s, -2 * M_PI / s, M_PI / s);

                for (u64 p = 0; p < N; p += s)
                {
                    const __m256d w = _mm256_mul_pd(wn, _mm256_set1_pd(static_cast<double>(s_half)));
                    for (u64 i = 0; i < s_half; i++)
                    {
                        const u64 j = p + i;
                        const u64 k = j + s_half;
                        const __m256d t = _mm256_add_pd(_mm256_sub_pd(_mm256_loadu_pd(&C[j].real), _mm256_loadu_pd(&C[k].real)), _mm256_mul_pd(_mm256_sub_pd(_mm256_mul_pd(_mm256_loadu_pd(&C[j].real), w), _mm256_mul_pd(_mm256_loadu_pd(&C[k].real), w)), _mm256_setr_pd(j, j + 1, j + 2, j + 3)));
                        _mm256_storeu_pd(&C[j].real, _mm256_add_pd(_mm256_loadu_pd(&C[j].real), _mm256_loadu_pd(&C[k].real)));
                        _mm256_storeu_pd(&C[k].real, t);
                    }
                }
            }

            // Bit reverse
            for (u64 i = 1, j = 0; i < N; i++)
            {
                for (u64 k = N >> 1; (j ^= k) < k; k >>= 1)
                {
                }
                if (i < j)
                {
                    const __m256d temp = _mm256_loadu_pd(&C[i].real);
                    _mm256_storeu_pd(&C[i].real, _mm256_loadu_pd(&C[j].real));
                    _mm256_storeu_pd(&C[j].real, temp);
                }
            }

            // Normalize
            const __m256d norm = _mm256_set1_pd(1.0 / N);
            for (u64 i = 0; i < N; i += 4)
            {
                __m256d v = _mm256_loadu_pd(&C[i].real);
                _mm256_storeu_pd(&C[i].real, _mm256_mul_pd(v, norm));
            }
            return C;
        }
    };
    struct Mem
    {
    public:
        enum class Unit : u8
        {
            BYTE = 0,
            KBYTE = 1,
            MBYTE = 2,
            GBYTE = 3,
            TBYTE = 4,
            PBYTE = 5
        };

    private:
        Unit unit = Unit::BYTE;

    public:
        f64 size = 0.0;
        f64 used = 0.0;
        f64 free = 0.0;
        f64 total = 0.0;
        explicit Mem(enum Unit _unit) :
            unit(_unit)
        {
            size = used = free = total = 0.0;
        }
        explicit Mem(f64 _size = 0.0, f64 _used = 0.0, f64 _free = 0.0, f64 _total = 0.0, Unit _unit = Unit::BYTE) :
            size(_size), used(_used), free(_free), total(_total), unit(_unit) {}

        constexpr auto Convert(const Unit _unit) const -> f64
        {
            const u8 one = 1;
            const u8 unit0 = static_cast<u8>(unit) * 10;
            const u8 unit1 = static_cast<u8>(_unit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return size * ratio;
        }
        auto Convert(const Mem _mem) const -> Mem
        {
            const u8 one = 1;
            const u8 unit0 = static_cast<u8>(unit) * 10;
            const u8 unit1 = static_cast<u8>(_mem.unit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return Mem{ size * ratio, used * ratio, free * ratio, total * ratio, _mem.unit };
        }
        auto operator[](Unit _unit) const -> f64 { return Convert(_unit); }
        auto operator=(const Mem& _rhs) -> Mem& = default;

        auto Total() const -> f64 { return used + free; }
        auto Available() const -> f64 { return free; }
        auto Used() const -> f64 { return used; }
        auto Percentage() const -> f64 { return ((used) / static_cast<f64>(Total())) * 100.0; }
        auto PercentageUsed() const -> f64 { return ((used) / (size)) * 100.0; }
        auto PercentageFree() const -> f64 { return ((free) / (size)) * 100.0; }
    };

} // namespace origin