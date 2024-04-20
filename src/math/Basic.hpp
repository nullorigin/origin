#pragma once
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <emmintrin.h>
#include <cmath>
#include <utility>
#include <immintrin.h>
#include <xmmintrin.h>
namespace origin
{
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
#define ABS __builtin_abs;
#define ACOS __builtin_acos
#define ACOSF __builtin_acosf
#define ACOSH __builtin_acosh
#define ACOSHF __builtin_acoshf
#define ACOSHL __builtin_acoshl
#define ACOSL __builtin_acosl
#define ASIN __builtin_asin
#define ASINF __builtin_asinf
#define ASINH __builtin_asinh
#define ASINHF __builtin_asinhf
#define ASINHL __builtin_asinhl
#define ASINL __builtin_asinl
#define ATAN __builtin_atan
#define ATAN2 __builtin_atan2
#define ATAN2F __builtin_atan2f
#define ATAN2L __builtin_atan2l
#define ATANF __builtin_atanf
#define ATANH __builtin_atanh
#define ATANHF __builtin_atanhf
#define ATANHL __builtin_atanhl
#define ATANL __builtin_atanl
#define CBRT __builtin_cbrt
#define CBRTF __builtin_cbrtf
#define CBRTL __builtin_cbrtl
#define CEIL __builtin_ceil
#define CEILF __builtin_ceilf
#define CEILL __builtin_ceill
#define COPYSIGN __builtin_copysign
#define COPYSIGNF __builtin_copysignf
#define COPYSIGNL __builtin_copysignl
#define COS __builtin_cos
#define COSF __builtin_cosf
#define COSH __builtin_cosh
#define COSHF __builtin_coshf
#define COSHL __builtin_coshl
#define COSL __builtin_cosl
#define DOUBLE_T __builtin_double_t
#define ERF __builtin_erf
#define ERFC __builtin_erfc
#define ERFCF __builtin_erfcf
#define ERFCL __builtin_erfcl
#define ERFF __builtin_erff
#define ERFL __builtin_erfl
#define EXP __builtin_exp
#define EXP2 __builtin_exp2
#define EXP2F __builtin_exp2f
#define EXP2L __builtin_exp2l
#define EXPF __builtin_expf
#define EXPL __builtin_expl
#define EXPM1 __builtin_expm1
#define EXPM1F __builtin_expm1f
#define EXPM1L __builtin_expmll
#define FABS __builtin_fabs
#define FABSF __builtin_fabsf
#define FABSL __builtin_fabsl
#define FDIM __builtin_fdim
#define FDIMF __builtin_fdimf
#define FDIML __builtin_fdiml
#define FLOAT_T __builtin_float_t
#define FLOOR __builtin_floor
#define FLOORF __builtin_floorf
#define FLOORL __builtin_floorl
#define FMA __builtin_fma
#define FMAF __builtin_fmaf
#define FMAL __builtin_fmal
#define FMAX __builtin_fmax
#define FMAXF __builtin_fmaxf
#define FMAXL __builtin_fmaxl
#define FMIN __builtin_fmin
#define FMINF __builtin_fminf
#define FMINL __builtin_fminl
#define FMOD __builtin_fmod
#define FMODF __builtin_fmodf
#define FMODL __builtin_fmodl
#define FPCLASSIFY __builtin_fpclassify
#define FREXP __builtin_frexp
#define FREXPF __builtin_frexp
#define FREXPL __builtin_frexpl
#define HYPOT __builtin_hypot
#define HYPOTF __builtin_hypotf
#define HYPOTL __builtin_hypotl
#define ILOGB __builtin_ilogb
#define ILOGBF __builtin_ilogbf
#define ILOGBL __builtin_ilogbl
#define ISFINITE __builtin_isfinite
#define ISGREATER __builtin_isgreater
#define ISGREATEREQUAL __builtin_isgreaterequal
#define ISINF __builtin_isinf
#define ISLESS __builtin_isless
#define ISLESSEQUAL __builtin_islessequal
#define ISLESSGREATER __builtin_lessgreater
#define ISNAN __builtin_isnan
#define ISNORMAL __builtin_normal
#define ISUNORDERED __builtin_isunordered
#define LDEXP __builtin_ldexp
#define LDEXPF __builtin_ldexpf
#define LDEXPL __builtin_ldexpl
#define LGAMMA __builtin_lgamma
#define LGAMMAF __builtin_lgammaf
#define LGAMMAL __builtin_lgammal
#define LLRINT __builtin_llrint
#define LLRINTF __builtin_llrintf
#define LLRINTL __builtin_llrintl
#define LLROUND __builtin_llround
#define LLROUND __builtin_llround
#define LLROUNDL __builtin_llroundl
#define LOG __builtin_log
#define LOG10 __builtin_log10
#define LOG10F __builtin_log10f
#define LOG10L __builtin_log10l
#define LOG1P __builtin_log1p
#define LOG1PF __builtin_log1pf
#define LOG1PL __builtin_log1pl
#define LOG2 __builtin_log2
#define LOG2F __builtin_log2f
#define LOG2L __builtin_log2l
#define LOGB __builtin_logb
#define LOGBF __builtin_logbf
#define LOGBL __builtin_logbl
#define LOGF __builtin_logf
#define LOGL __builtin_logl
#define LRINT __builtin_lrint
#define LRINTF __builtin_lrintf
#define LRINTL __builtin_lrintl
#define LROUND __builtin_lround
#define LROUNDF __builtin_lroundf
#define LROUNDL __builtin_lroundl
#define MODF __builtin_modf
#define MODFF __builtin_modff
#define MODFL __builtin_modfl
#define NAND __builtin_nan
#define NANF __builtin_nanf
#define NANL __builtin_nanl
#define NEARBYINT __builtin_nearbyint
#define NEARBYINTF __builtin_nearbyintf
#define NEARBYINTL __builtin_nearbyintl
#define NEXTAFTER __builtin_nextafter
#define NEXTAFTERF __builtin_nextafterf
#define NEXTAFTERL __builtin_nextafterl
#define NEXTTOWARD __builtin_nexttoward
#define NEXTTOWARDF __builtin_nexttowardf
#define NEXTTOWARDL __builtin_nexttowardl
#define POW __builtin_pow
#define POWF __builtin_powf
#define POWI __builtin_powi
#define POWL __builtin_powl
#define REMAINDER __builtin_remainder
#define REMAINDERF __builtin_remainderf
#define REMAINDERL __builtin_remainderl
#define REMQUO __builtin_remquo
#define REMQUOF __builtin_remquof
#define REMQUOL __builtin_remquol
#define RINT __builtin_rint
#define RINTF __builtin_rintf
#define RINTL __builtin_fintl
#define ROUND __builtin_round
#define ROUNDF __builtin_roundf
#define ROUNDL __builtin_roundl
#define SCALBIN __builtin_scalbin
#define SCALBINF __builtin_scalbinf
#define SCALBINL __builtin_scalbinl
#define SCALBN __builtin_scalbn
#define SCALBNF __builtin_scalbnf
#define SCALBNL __builtin_scalbnl
#define SIGNBIT __builtin_signbit
#define SIN __builtin_sin
#define SINF __builtin_sinf
#define SINH __builtin_sinh
#define SINHF __builtin_sinhf
#define SINHL __builtin_sinhl
#define SINL __builtin_sinl
#define SQRT __builtin_sqrt
#define SQRTF __builtin_sqrtf
#define SQRTL __builtin_sqrtl
#define TAN __builtin_tan
#define TANF __builtin_tanf
#define TANH __builtin_tanh
#define TANHF __builtin_tanhf
#define TANHL __builtin_tanhl
#define TANL __builtin_tanl
#define TGAMMA __builtin_tgamma
#define TGAMMAF __builtin_tgammaf
#define TGAMMAL __builtin_tgammal
#define TRUNC __builtin_trunc
#define TRUNCF __builtin_truncf
#define TRUNCL __builtin_truncl
#endif // NO_BUILTIN
    using ID = u64;
    template<typename T>
    inline constexpr auto IsNum(const T _a) -> bool
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
        return __builtin_elementwise_abs(_a);
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
    inline constexpr auto Pow(const T _a, const T _b) -> T
    {
        return __builtin_elementwise_pow(_a, _b);
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
        return T(SQRT((_a * _a) + (_b * _b)));
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
        return T(TAN(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Asin(T _a) noexcept -> T
    {
        return T(ASIN(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Acos(T _a) noexcept -> T
    {
        return T(ACOS(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Atan(T _a) noexcept -> T
    {
        return T(ATAN(f64(_a)));
    }
    template<typename T>
    inline constexpr auto Atan2(T _a, T _b) noexcept -> T
    {
        return T(ATAN2(f64(_a), f64(_b)));
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