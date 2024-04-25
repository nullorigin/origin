#pragma once
#include <cmath>

#include <cstddef>

#include <cstdlib>

#include <cstring>
#include <cstdarg>
#include <emmintrin.h>

#include <immintrin.h>

#include <string>

#include <utility>

#include <xmmintrin.h>

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
    using V = __builtin_va_list;
    inline double Abs(double x)
    {
        return __builtin_fabs(x);
    }
    inline float Abs(float x)
    {
        return __builtin_fabsf(x);
    }
    inline long double Abs(long double x)
    {
        return __builtin_fabsl(x);
    }

    inline double Acos(double x)
    {
        return __builtin_acos(x);
    }
    inline float Acos(float x)
    {
        return __builtin_acosf(x);
    }
    inline long double Acos(long double x)
    {
        return __builtin_acosl(x);
    }

    inline double Acosh(double x)
    {
        return __builtin_acosh(x);
    }
    inline float Acosh(float x)
    {
        return __builtin_acoshf(x);
    }
    inline long double Acosh(long double x)
    {
        return __builtin_acoshl(x);
    }

    inline double Asin(double x)
    {
        return __builtin_asin(x);
    }
    inline float Asin(float x)
    {
        return __builtin_asinf(x);
    }
    inline long double Asin(long double x)
    {
        return __builtin_asinl(x);
    }

    inline double Asinh(double x)
    {
        return __builtin_asinh(x);
    }
    inline float Asinh(float x)
    {
        return __builtin_asinhf(x);
    }
    inline long double Asinh(long double x)
    {
        return __builtin_asinhl(x);
    }

    inline double Atan(double x)
    {
        return __builtin_atan(x);
    }
    inline float Atan(float x)
    {
        return __builtin_atanf(x);
    }
    inline long double Atan(long double x)
    {
        return __builtin_atanl(x);
    }

    inline double Atan2(double x, double y)
    {
        return __builtin_atan2(x, y);
    }
    inline float Atan2(float x, float y)
    {
        return __builtin_atan2f(x, y);
    }
    inline long double Atan2(long double x, long double y)
    {
        return __builtin_atan2l(x, y);
    }

    inline double Cbrt(double x)
    {
        return __builtin_cbrt(x);
    }
    inline float Cbrt(float x)
    {
        return __builtin_cbrtf(x);
    }
    inline long double Cbrt(long double x)
    {
        return __builtin_cbrtl(x);
    }

    inline double Ceil(double x)
    {
        return __builtin_ceil(x);
    }
    inline float Ceil(float x)
    {
        return __builtin_ceilf(x);
    }
    inline long double Ceil(long double x)
    {
        return __builtin_ceill(x);
    }

    inline double Copysign(double x, double y)
    {
        return __builtin_copysign(x, y);
    }
    inline float Copysign(float x, float y)
    {
        return __builtin_copysignf(x, y);
    }
    inline long double Copysign(long double x, long double y)
    {
        return __builtin_copysignl(x, y);
    }

    inline double Cos(double x)
    {
        return __builtin_cos(x);
    }
    inline float Cos(float x)
    {
        return __builtin_cosf(x);
    }
    inline long double Cos(long double x)
    {
        return __builtin_cosl(x);
    }

    inline double Cosh(double x)
    {
        return __builtin_cosh(x);
    }
    inline float Cosh(float x)
    {
        return __builtin_coshf(x);
    }
    inline long double Cosh(long double x)
    {
        return __builtin_coshl(x);
    }

    inline double Erf(double x)
    {
        return __builtin_erf(x);
    }
    inline float Erf(float x)
    {
        return __builtin_erff(x);
    }
    inline long double Erf(long double x)
    {
        return __builtin_erfl(x);
    }

    inline double Erfc(double x)
    {
        return __builtin_erfc(x);
    }
    inline float Erfc(float x)
    {
        return __builtin_erfcf(x);
    }
    inline long double Erfc(long double x)
    {
        return __builtin_erfcl(x);
    }

    inline double Exp(double x)
    {
        return __builtin_exp(x);
    }
    inline float Exp(float x)
    {
        return __builtin_expf(x);
    }
    inline long double Exp(long double x)
    {
        return __builtin_expl(x);
    }

    inline double Exp2(double x)
    {
        return __builtin_exp2(x);
    }
    inline float Exp2(float x)
    {
        return __builtin_exp2f(x);
    }
    inline long double Exp2(long double x)
    {
        return __builtin_exp2l(x);
    }

    inline double Fdim(double x, double y)
    {
        return __builtin_fdim(x, y);
    }
    inline float Fdim(float x, float y)
    {
        return __builtin_fdimf(x, y);
    }
    inline long double Fdim(long double x, long double y)
    {
        return __builtin_fdiml(x, y);
    }

    inline double Floor(double x)
    {
        return __builtin_floor(x);
    }
    inline float Floor(float x)
    {
        return __builtin_floorf(x);
    }
    inline long double Floor(long double x)
    {
        return __builtin_floorl(x);
    }

    inline double Fma(double x, double y, double z)
    {
        return __builtin_fma(x, y, z);
    }
    inline float Fma(float x, float y, float z)
    {
        return __builtin_fmaf(x, y, z);
    }
    inline long double Fma(long double x, long double y, long double z)
    {
        return __builtin_fmal(x, y, z);
    }

    inline double Fmax(double x, double y)
    {
        return __builtin_fmax(x, y);
    }
    inline float Fmax(float x, float y)
    {
        return __builtin_fmaxf(x, y);
    }
    inline long double Fmax(long double x, long double y)
    {
        return __builtin_fmaxl(x, y);
    }

    inline double Fmin(double x, double y)
    {
        return __builtin_fmin(x, y);
    }
    inline float Fmin(float x, float y)
    {
        return __builtin_fminf(x, y);
    }
    inline long double Fmin(long double x, long double y)
    {
        return __builtin_fminl(x, y);
    }

    inline double Fmod(double x, double y)
    {
        return __builtin_fmod(x, y);
    }
    inline float Fmod(float x, float y)
    {
        return __builtin_fmodf(x, y);
    }
    inline long double Fmod(long double x, long double y)
    {
        return __builtin_fmodl(x, y);
    }

    inline int Fpclassify(int a, int b, int c, int d, int e, float f)
    {
        return __builtin_fpclassify(a, b, c, d, e, f);
    }

    inline double Hypot(double x, double y)
    {
        return __builtin_hypot(x, y);
    }
    inline float Hypot(float x, float y)
    {
        return __builtin_hypotf(x, y);
    }
    inline long double Hypot(long double x, long double y)
    {
        return __builtin_hypotl(x, y);
    }

    inline int Ilogb(double x)
    {
        return __builtin_ilogb(x);
    }
    inline int Ilogb(float x)
    {
        return __builtin_ilogbf(x);
    }
    inline int Ilogb(long double x)
    {
        return __builtin_ilogbl(x);
    }

    inline bool Isfinite(double x)
    {
        return __builtin_isfinite(x) != 0;
    }
    inline bool Isfinite(float x)
    {
        return __builtin_isfinite(x) != 0;
    }
    inline bool Isfinite(long double x)
    {
        return __builtin_isfinite(x) != 0;
    }

    inline bool Isgreater(double x, double y)
    {
        return __builtin_isgreater(x, y) != 0;
    }
    inline bool Isgreater(float x, float y)
    {
        return __builtin_isgreater(x, y) != 0;
    }
    inline bool Isgreater(long double x, long double y)
    {
        return __builtin_isgreater(x, y) != 0;
    }

    inline bool Isgreaterequal(double x, double y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline bool Isgreaterequal(float x, float y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline bool Isgreaterequal(long double x, long double y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline long double Lgammal(long double x)
    {
        return __builtin_lgammal(x);
    }
    inline long long Llrint(double x)
    {
        return __builtin_llrint(x);
    }
    inline long long Llrintf(float x)
    {
        return __builtin_llrintf(x);
    }
    inline long long Llrintl(long double x)
    {
        return __builtin_llrintl(x);
    }
    inline long long Llround(double x)
    {
        return __builtin_llround(x);
    }
    inline long long Llroundf(float x)
    {
        return __builtin_llroundf(x);
    }
    inline long long Llroundl(long double x)
    {
        return __builtin_llroundl(x);
    }
    inline double Log(double x)
    {
        return __builtin_log(x);
    }
    inline float Logf(float x)
    {
        return __builtin_logf(x);
    }
    inline long double Logl(long double x)
    {
        return __builtin_logl(x);
    }
    inline double Log10(double x)
    {
        return __builtin_log10(x);
    }
    inline float Log10f(float x)
    {
        return __builtin_log10f(x);
    }
    inline long double Log10l(long double x)
    {
        return __builtin_log10l(x);
    }
    inline double Log1p(double x)
    {
        return __builtin_log1p(x);
    }
    inline float Log1pf(float x)
    {
        return __builtin_log1pf(x);
    }
    inline long double Log1pl(long double x)
    {
        return __builtin_log1pl(x);
    }
    inline double Log2(double x)
    {
        return __builtin_log2(x);
    }
    inline float Log2f(float x)
    {
        return __builtin_log2f(x);
    }
    inline long double Log2l(long double x)
    {
        return __builtin_log2l(x);
    }
    inline double Logb(double x)
    {
        return __builtin_logb(x);
    }
    inline float Logbf(float x)
    {
        return __builtin_logbf(x);
    }
    inline long double Logbl(long double x)
    {
        return __builtin_logbl(x);
    }
    inline long Lrint(double x)
    {
        return __builtin_lrint(x);
    }
    inline long int Lrintf(float x)
    {
        return __builtin_lrintf(x);
    }
    inline long double Lrintl(long double x)
    {
        return __builtin_lrintl(x);
    }
    inline long Lround(double x)
    {
        return __builtin_lround(x);
    }
    inline long Lroundf(float x)
    {
        return __builtin_lroundf(x);
    }
    inline long Lroundl(long double x)
    {
        return __builtin_lroundl(x);
    }
    inline double Modf(double x, double* y)
    {
        return __builtin_modf(x, y);
    }
    inline float Modff(float x, float* y)
    {
        return __builtin_modff(x, y);
    }
    inline long double Modfl(long double x, long double* y)
    {
        return __builtin_modfl(x, y);
    }
    inline double Nan(const char* s)
    {
        return __builtin_nan(s);
    }
    inline float Nanf(const char* s)
    {
        return __builtin_nanf(s);
    }
    inline long double Nanl(const char* s)
    {
        return __builtin_nanl(s);
    }
    inline double Nearbyint(double x)
    {
        return __builtin_nearbyint(x);
    }
    inline float Nearbyintf(float x)
    {
        return __builtin_nearbyintf(x);
    }
    inline long double Nearbyintl(long double x)
    {
        return __builtin_nearbyintl(x);
    }
    inline double Nextafter(double x, double y)
    {
        return __builtin_nextafter(x, y);
    }
    inline float Nextafterf(float x, float y)
    {
        return __builtin_nextafterf(x, y);
    }
    inline long double Nextafterl(long double x, long double y)
    {
        return __builtin_nextafterl(x, y);
    }
    inline double Nexttoward(double x, long double y)
    {
        return __builtin_nexttoward(x, y);
    }
    inline float Nexttowardf(float x, long double y)
    {
        return __builtin_nexttowardf(x, y);
    }
    inline long double Nexttowardl(long double x, long double y)
    {
        return __builtin_nexttowardl(x, y);
    }
    inline double Pow(double x, double y)
    {
        return __builtin_pow(x, y);
    }
    inline float Powf(float x, float y)
    {
        return __builtin_powf(x, y);
    }
    inline double Powi(double x, int y)
    {
        return __builtin_powi(x, y);
    }
    inline long double Powl(long double x, long double y)
    {
        return __builtin_powl(x, y);
    }
    inline double Remainder(double x, double y)
    {
        return __builtin_remainder(x, y);
    }
    inline float Remainderf(float x, float y)
    {
        return __builtin_remainderf(x, y);
    }
    inline long double Remainderl(long double x, long double y)
    {
        return __builtin_remainderl(x, y);
    }
    inline double Remquo(double x, double y, int* q)
    {
        return __builtin_remquo(x, y, q);
    }
    inline float Remquof(float x, float y, int* q)
    {
        return __builtin_remquof(x, y, q);
    }
    inline long double Remquol(long double x, long double y, int* q)
    {
        return __builtin_remquol(x, y, q);
    }
    inline double Rint(double x)
    {
        return __builtin_rint(x);
    }
    inline float Rintf(float x)
    {
        return __builtin_rintf(x);
    }
    inline long double Rintl(long double x)
    {
        return __builtin_rintl(x);
    }
    inline double Round(double x)
    {
        return __builtin_round(x);
    }
    inline float Roundf(float x)
    {
        return __builtin_roundf(x);
    }
    inline long double Roundl(long double x)
    {
        return __builtin_roundl(x);
    }
    inline double Scalbln(double x, int y)
    {
        return __builtin_scalbln(x, y);
    }
    inline float Scalblnf(float x, int y)
    {
        return __builtin_scalblnf(x, y);
    }
    inline long double Scalblnl(long double x, int y)
    {
        return __builtin_scalblnl(x, y);
    }
    inline double Scalbn(double x, int y)
    {
        return __builtin_scalbn(x, y);
    }
    inline float Scalbnf(float x, int y)
    {
        return __builtin_scalbnf(x, y);
    }
    inline long double Scalbnf(long double x, int y)
    {
        return __builtin_scalbnf(x, y);
    }
    inline bool Signbit(double x)
    {
        return __builtin_signbit(x) != 0;
    }
    inline bool Signbitf(float x)
    {
        return __builtin_signbitf(x) != 0;
    }
    inline bool Signbitl(long double x)
    {
        return __builtin_signbitl(x) != 0;
    }
    inline double Sin(double x)
    {
        return __builtin_sin(x);
    }
    inline float Sinf(float x)
    {
        return __builtin_sinf(x);
    }
    inline double Sinh(double x)
    {
        return __builtin_sinh(x);
    }
    inline float Sinhf(float x)
    {
        return __builtin_sinhf(x);
    }
    inline long double Sinhl(long double x)
    {
        return __builtin_sinhl(x);
    }
    inline long double Sinl(long double x)
    {
        return __builtin_sinl(x);
    }
    inline double Sqrt(double x)
    {
        return __builtin_sqrt(x);
    }
    inline float Sqrtf(float x)
    {
        return __builtin_sqrtf(x);
    }
    inline long double Sqrtl(long double x)
    {
        return __builtin_sqrtl(x);
    }
    inline double Tan(double x)
    {
        return __builtin_tan(x);
    }
    inline float Tanf(float x)
    {
        return __builtin_tanf(x);
    }
    inline double Tanh(double x)
    {
        return __builtin_tanh(x);
    }
    inline float Tanhf(float x)
    {
        return __builtin_tanhf(x);
    }
    inline long double Tanhl(long double x)
    {
        return __builtin_tanhl(x);
    }
    inline long double Tanl(long double x)
    {
        return __builtin_tanl(x);
    }
    inline double Tgamma(double x)
    {
        return __builtin_tgamma(x);
    }
    inline float Tgammaf(float x)
    {
        return __builtin_tgammaf(x);
    }
    inline long double Tgammal(long double x)
    {
        return __builtin_tgammal(x);
    }
    inline double Trunc(double x)
    {
        return __builtin_trunc(x);
    }
    inline float Truncf(float x)
    {
        return __builtin_truncf(x);
    }
    inline long double Truncl(long double x)
    {
        return __builtin_truncl(x);
    }
    template<typename T>
    inline auto Abs(T a)
    {
        return T(__builtin_elementwise_abs(a));
    }
    template<typename T>
    inline auto Ceil(T a)
    {
        return T(__builtin_elementwise_ceil(a));
    }
    template<typename T>
    inline auto Floor(T a)
    {
        return T(__builtin_elementwise_floor(a));
    }
    template<typename T>
    inline auto Round(T a)
    {
        return T(__builtin_elementwise_round(a));
    }
    template<typename T>
    inline auto Trunc(T a)
    {
        return T(__builtin_elementwise_trunc(a));
    }
    template<typename T>
    inline auto Rint(T a)
    {
        return T(__builtin_elementwise_rint(a));
    }
    template<typename T>
    inline auto Nearbyint(T a)
    {
        return T(__builtin_elementwise_nearbyint(a));
    }
    template<typename T, typename U>
    inline auto Copysign(T a, U b)
    {
        return T(__builtin_elementwise_copysign(a, b));
    }
    template<typename T>
    inline auto Sin(T a)
    {
        return T(__builtin_elementwise_sin(a));
    }
    template<typename T>
    inline auto Cos(T a)
    {
        return T(__builtin_elementwise_cos(a));
    }
    template<typename T>
    inline auto AddSat(T a, T b)
    {
        return T(__builtin_elementwise_add_sat(a, b));
    }
    template<typename T>
    inline auto SubSat(T a, T b)
    {
        return T(__builtin_elementwise_sub_sat(a, b));
    }
    template<typename T, typename U>
    inline auto Max(T a, U b)
    {
        return T(__builtin_elementwise_max(a, b));
    }
    template<typename T, typename U>
    inline auto Min(T a, U b)
    {
        return T(__builtin_elementwise_min(a, b));
    }
    template<typename T>
    inline auto Sqrt(T a)
    {
        return T(__builtin_sqrt(f64(a)));
    }
    template<typename T>
    inline auto Log(T a)
    {
        return T(__builtin_elementwise_log(a));
    }
    template<typename T>
    inline auto Log2(T a)
    {
        return T(__builtin_elementwise_log2(a));
    }
    template<typename T>
    inline auto Log10(T a)
    {
        return T(__builtin_elementwise_log10(a));
    }
    template<typename T>
    inline auto Exp(T a)
    {
        return T(__builtin_elementwise_exp(a));
    }
    template<typename T>
    inline auto Exp2(T a)
    {
        return T(__builtin_elementwise_exp2(a));
    }
    template<typename T, typename U>
    inline auto Pow(T a, U b)
    {
        return T(__builtin_elementwise_pow(a, b));
    }
#endif // NO_BUILTIN
    using ID = u64;
    template<typename T>
    inline auto Isnum(const T _a) -> bool
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
        return T(__builtin_elementwise_floor(_a));
    }
    template<typename T>
    inline constexpr auto Ceil(const T _a) -> T
    {
        return __builtin_elementwise_ceil(_a);
    }
    template<typename T>
    inline constexpr auto Hypot(T _a, T _b) -> T
    {
        return T(Hypot(f64(_a), f64(_b)));
    }
    template<typename T>
    inline constexpr auto Square(const T _a) -> T
    {
        return T(_a * _a);
    }
    template<typename T>
    inline constexpr auto Madd(const T _a, T _b, const T _c) -> T
    {
        return T(__builtin_elementwise_add_sat((_a * _b), _c));
    }
    template<typename T>
    inline constexpr auto Sqrt(const T _a) noexcept -> T
    {
        return T(__builtin_sqrt(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Min(const T _a, const T _b) -> T
    {
        return T(__builtin_elementwise_min(_a, _b));
    }
    template<typename T>
    inline constexpr auto Max(const T _a, const T _b) -> T
    {
        return T(__builtin_elementwise_max(_a, _b));
    }
    template<typename T>
    inline constexpr auto Abs(const T _a) -> T
    {
        return T(__builtin_elementwise_abs(_a));
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
        return T(Sub(_a, Floor(_a)));
    }
    template<typename T>
    inline constexpr auto Lerp(const T _a, const T _b, const T _t) -> T
    {
        return T(Add(_a, Sub(_b - _a)) * _t);
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
        return T(__builtin_elementwise_round(_a));
    }
    template<typename T>
    inline constexpr auto Trunc(const T _a) noexcept -> T
    {
        return T(__builtin_elementwise_trunc(_a));
    }
    template<typename T>
    inline constexpr auto Dot(const T _a, const T _b) -> T
    {
        return T(_a * _b);
    }
    template<typename T>
    inline constexpr auto Length(T _a, T _b) -> T
    {
        return T(Sqrt(AddSat((_a * _a), (_b * _b))));
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
        return SubSat(0, _a);
    }
    template<typename T>
    inline constexpr auto Sub(const T _a, const T _b) -> T
    {
        return T(__builtin_elementwise_sub_sat(_a, _b));
    }
    template<typename T>
    inline constexpr auto Add(const T _a, const T _b) -> T
    {
        return T(__builtin_elementwise_add_sat(_a, _b));
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
        return T(__builtin_elementwise_sin(_a));
    }
    template<typename T>
    inline constexpr auto Cos(T _a) noexcept -> T
    {
        return T(__builtin_elementwise_cos(_a));
    }
    template<typename T>
    inline constexpr auto Tan(T _a) noexcept -> T
    {
        return T(Tan(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Asin(T _a) noexcept -> T
    {
        return T(Asin(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Acos(T _a) noexcept -> T
    {
        return T(Acos(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Atan(T _a) noexcept -> T
    {
        return T(Atan(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Atan2(T _a, T _b) noexcept -> T
    {
        return T(Atan2(f64(_a), f64(_b)));
    }
    template<typename T>
    inline auto Log(T _a) noexcept -> T
    {
        return T(__builtin_elementwise_log(_a));
    }
    template<typename T>
    inline auto Log2(T _x) noexcept -> T
    {
        return T(__builtin_elementwise_log2(_x));
    }
    template<typename T>
    inline auto Log10(T _a) noexcept -> T
    {
        return T(__builtin_elementwise_log10(_a));
    }

    struct Complex
    {
        union
        {
            __m128d V{};
            struct
            {
                f64 Real;
                f64 Imag;
            } __attribute__((aligned(16)));
        };
        Complex() = default;
        Complex(f64 _real, f64 _imag) :
            Real(_real), Imag(_imag) {}
        static auto Zero() -> Complex { return Complex(0, 0); }

        static auto Add(const Complex A, const Complex B) noexcept -> Complex
        {
            return { A.Real + B.Real, A.Imag + B.Imag };
        }
        static auto Sub(const Complex A, const Complex B) noexcept -> Complex
        {
            return { A.Real - B.Real, A.Imag - B.Imag };
        }

        auto Mul(const Complex b) const -> Complex
        {
            return { Real * b.Real - Imag * b.Imag, Real * b.Imag + Imag * b.Real };
        }
        auto Mul(f64* aPtr) const noexcept -> f64*
        {
            __m256d a = _mm256_loadu_pd(aPtr);
            __m256d b = _mm256_setr_pd(Real, Imag, aPtr[2], aPtr[3]);
            _mm256_storeu_pd(aPtr, _mm256_mul_pd(a, b));
            return aPtr;
        }

        static auto Div(Complex a, Complex b) noexcept -> Complex
        {
            __m128d num = _mm_setr_pd(a.Real, a.Imag);
            __m128d den = _mm_setr_pd(b.Real, b.Imag);
            return { _mm_cvtsd_f64(_mm_div_pd(num, den)), _mm_cvtsd_f64(_mm_div_pd(den, num)) };
        }
        static auto FFT(const Complex* input, u64 size) -> Complex*
        {
            auto* out = new Complex[size];
            u64 half_size = size >> 1;
            const __m256d wn = _mm256_setr_pd(-2 * M_PI / size, M_PI / size, -2 * M_PI / size, M_PI / size);

            // Divide input into even and odd parts
            for (u64 i = 0; i < size; i += 4)
            {
                __m256d a = _mm256_loadu_pd(&input[i].Real);
                __m256d b = _mm256_loadu_pd(&input[i + half_size].Real);
                _mm256_storeu_pd(&out[i].Real, _mm256_add_pd(a, b));
                _mm256_storeu_pd(&out[i + half_size].Real, _mm256_sub_pd(a, b));
            }

            for (u64 n = 4, m = 2; n <= size; n <<= 2, m = n >> 1)
            {
                const __m256d w = _mm256_mul_pd(wn, _mm256_set1_pd(static_cast<double>(m)));
                for (u64 i = 0; i < size; i += n)
                {
                    for (u64 j = i; j < i + m; j += 4)
                    {
                        __m256d a = _mm256_loadu_pd(&out[j].Real);
                        __m256d b = _mm256_loadu_pd(&out[j + m].Real);
                        __m256d t = _mm256_add_pd(_mm256_sub_pd(a, b), _mm256_mul_pd(_mm256_sub_pd(_mm256_mul_pd(a, w), _mm256_mul_pd(b, w)), _mm256_setr_pd(j, j + 1, j + 2, j + 3)));
                        _mm256_storeu_pd(&out[j].Real, _mm256_add_pd(a, b));
                        _mm256_storeu_pd(&out[j + m].Real, t);
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
                __m256d v = _mm256_loadu_pd(&out[i].Real);
                _mm256_storeu_pd(&out[i].Real, _mm256_mul_pd(v, norm));
            }
            return out;
        }
        static Complex* Conjugate(Complex* C1, const u64 N)
        {
            auto* c = C1;
            for (u64 i = 0; i < N; i++)
            {
                c[i].Imag = -c[i].Imag;
            }
            return c;
        }

        static Complex* FFT2(Complex* C1, const u64 N)
        {
            auto* c = reinterpret_cast<Complex*>(C1);

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
                        const __m256d t = _mm256_add_pd(_mm256_sub_pd(_mm256_loadu_pd(&c[j].Real), _mm256_loadu_pd(&c[k].Real)), _mm256_mul_pd(_mm256_sub_pd(_mm256_mul_pd(_mm256_loadu_pd(&c[j].Real), w), _mm256_mul_pd(_mm256_loadu_pd(&c[k].Real), w)), _mm256_setr_pd(j, j + 1, j + 2, j + 3)));
                        _mm256_storeu_pd(&c[j].Real, _mm256_add_pd(_mm256_loadu_pd(&c[j].Real), _mm256_loadu_pd(&c[k].Real)));
                        _mm256_storeu_pd(&c[k].Real, t);
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
                    const __m256d temp = _mm256_loadu_pd(&c[i].Real);
                    _mm256_storeu_pd(&c[i].Real, _mm256_loadu_pd(&c[j].Real));
                    _mm256_storeu_pd(&c[j].Real, temp);
                }
            }

            // Normalize
            const __m256d norm = _mm256_set1_pd(1.0 / N);
            for (u64 i = 0; i < N; i += 4)
            {
                __m256d v = _mm256_loadu_pd(&c[i].Real);
                _mm256_storeu_pd(&c[i].Real, _mm256_mul_pd(v, norm));
            }
            return c;
        }

        static Complex* IFFT(Complex C1[], const u64 N)
        {
            auto* c = C1;
            c = Conjugate(c, N);
            FFT2(c, N);
            c = Conjugate(c, N);
            return c;
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
        Unit Unit = Unit::BYTE;

    public:
        f64 MemSize = 0.0;
        f64 MemUsed = 0.0;
        f64 MemFree = 0.0;
        f64 MemTotal = 0.0;
        explicit Mem(enum Unit _unit) :
            Unit(_unit)
        {
            MemSize = MemUsed = MemFree = MemTotal = 0.0;
        }
        explicit Mem(f64 _size = 0.0, f64 _used = 0.0, f64 _free = 0.0, f64 _total = 0.0, enum Unit _unit = Unit::BYTE) :
            MemSize(_size), MemUsed(_used), MemFree(_free), MemTotal(_total), Unit(_unit) {}

        constexpr auto Convert(const enum Unit _unit) const -> f64
        {
            const u8 one = 1;
            const u8 unit0 = static_cast<u8>(Unit) * 10;
            const u8 unit1 = static_cast<u8>(_unit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return MemSize * ratio;
        }
        auto Convert(const Mem _mem) const -> Mem
        {
            const u8 one = 1;
            const u8 unit0 = static_cast<u8>(Unit) * 10;
            const u8 unit1 = static_cast<u8>(_mem.Unit) * 10;
            f64 ratio = one << unit0;
            ratio /= one << unit1;
            return Mem{ MemSize * ratio, MemUsed * ratio, MemFree * ratio, MemTotal * ratio, _mem.Unit };
        }
        auto operator[](enum Unit _unit) const -> f64 { return Convert(_unit); }
        auto operator=(const Mem& _rhs) -> Mem& = default;

        auto Total() const -> f64 { return MemUsed + MemFree; }
        auto Available() const -> f64 { return MemFree; }
        auto Used() const -> f64 { return MemUsed; }
        auto Percentage() const -> f64 { return ((MemUsed) / static_cast<f64>(Total())) * 100.0; }
        auto PercentageUsed() const -> f64 { return ((MemUsed) / (MemSize)) * 100.0; }
        auto PercentageFree() const -> f64 { return ((MemFree) / (MemSize)) * 100.0; }
    } __attribute__((aligned(64))) __attribute__((packed));

} // namespace origin