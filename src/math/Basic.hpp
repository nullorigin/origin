#pragma once
#include "Basic.hpp"
#include <complex.h>
#include <cstdlib>
#include <emmintrin.h>
#include <xmmintrin.h>

namespace origin {
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef __int128_t i128;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef __uint128_t u128;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef __int128_t s128;
typedef float f32;
typedef double f64;
typedef long double f128;
typedef unsigned char *up8p;
typedef unsigned short *u16p;
typedef unsigned int *u32p;
typedef unsigned long long *u64p;
typedef __uint128_t *u128p;
typedef char *i8p;
typedef short *i16p;
typedef int *i32p;
typedef long long *i64p;
typedef __int128_t *i128p;
typedef float *f32p;
typedef double *f64p;
typedef long double *f128p;

typedef char m128i8 __attribute__((__vector_size__(16), __aligned__(16)));
typedef unsigned char m128u8
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef signed char m128s8
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef short m128i16 __attribute__((__vector_size__(16), __aligned__(16)));
typedef unsigned short m128u16
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef signed short m128s16
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef float m128f32 __attribute__((__vector_size__(16), __aligned__(16)));
typedef int m128i32 __attribute__((__vector_size__(16), __aligned__(16)));
typedef unsigned int m128u32
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef signed int m128s32
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef double m128f64 __attribute__((__vector_size__(16), __aligned__(16)));
typedef long long m128i64 __attribute__((__vector_size__(16), __aligned__(16)));
typedef unsigned long long m128u64
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef signed long long m128s64
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef char m256i8 __attribute__((__vector_size__(32), __aligned__(32)));
typedef unsigned char m256u8
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef char m256i8 __attribute__((__vector_size__(32), __aligned__(32)));
typedef unsigned char m256u8
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef signed char m256s8
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef short m256i16 __attribute__((__vector_size__(32), __aligned__(32)));
typedef unsigned short m256u16
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef signed short m256s16
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef float m256f32 __attribute__((__vector_size__(32), __aligned__(32)));
typedef int m256i32 __attribute__((__vector_size__(32), __aligned__(32)));
typedef unsigned int m256u32
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef signed int m256s32
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef double m256f64 __attribute__((__vector_size__(32), __aligned__(32)));
typedef long long m256i64 __attribute__((__vector_size__(32), __aligned__(32)));
typedef unsigned long long m256u64
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef signed long long m256s64
    __attribute__((__vector_size__(32), __aligned__(32)));
typedef double m256f64 __attribute__((__vector_size__(32), __aligned__(32)));
typedef long double m256f128
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef __int128_t m256i128
    __attribute__((__vector_size__(16), __aligned__(16)));
typedef __uint128_t m256u128
    __attribute__((__vector_size__(16), __aligned__(16)));
#if WORDSIZE == 64
typedef unsigned long SIZE_T;
#else
typedef unsigned long long SIZE_T;
#endif
static const u32 C8 = 0xff, C16 = 0xffff, C32 = 0xffffff, C64 = 0xffffffff;
constexpr f64 PI = 3.14159265358979323846535897932384;
#define I8_C(c) c
#define U8_C(c) c
#define S8_C(c) c
#define I16_C(c) c
#define U16_C(c) c
#define S16_C(c) c
#define I32_C(c) c
#define U32_C(c) c##U
#define S32_C(c) c
#if WORDSIZE == 64
#define I64_C(c) c##L
#define S64_C(c) c##L
#define U64_C(c) c##UL
#else
#define I64_C(c) c##LL
#define U64_C(c) c##ULL
#define S64_C(c) c##LL
#endif
#define F32_C(c) c##f
#define F64_C(c) c
#define F128_C(c) c##d
#define U64_C2(h, l) ((static_cast<u64>(h) << 32) | static_cast<u64>(l))
#define IMAX8 I8_C(127)
#define IMAX16 I16_C(32767)
#define IMAX32 I32_C(2147483647)
#define IMAX64 I64_C(9223372036854775807)
#define UMAX8 U8_C(255)
#define UMAX16 U16_C(65535)
#define UMAX32 U32_C(4294967295)
#define UMAX64 U64_C(18446744073709551615)
#define SMAX8 S8_C(127)
#define SMAX16 S16_C(32767)
#define SMAX32 S32_C(2147483647)
#define SMAX64 S64_C(9223372036854775807)
#define FMAX32 F32_C(3.40282346638528859811704183484516925440e+38f)
#define FMAX64 F64_C(1.797693134862315708145274237317043567981e+308)
#define FMAX128 F128_C(1.18973149535723176508575932662800702e+4932)
#define IMIN8 I8_C(-128)
#define IMIN16 I16_C(-32768)
#define IMIN32 I32_C(-2147483648)
#define UMIN8 U8_C(0)
#define UMIN16 U16_C(0)
#define UMIN32 U32_C(0)
#define UMIN64 U64_C(0)
#define SMIN8 S8_C(-128)
#define SMIN16 S16_C(-32768)
#define SMIN16 S16_C(-32768)
#define SMIN32 S32_C(-2147483648)
#define SMIN64 S64_C(-9223372036854775808)
#define FMIN32 F32_C(-3.40282346638528859811704183484516925440e+38f)
#define FMIN64 F64_C(-1.797693134862315708145274237317043567981e+308)
#define FMIN128 F128_C(-1.18973149535723176508575932662800702e+4932)
#define FE32 F32_C(1.1920928955078125e-07f)
#define FE64 F64_C(2.220446049250313080847263336181640625e-16)
#define FE128 F128_C(1.9259299443872358530559779425849159658203125e-34)
#ifndef NULL
#define NULL ((void *)0)
#endif
#ifndef NO_BUILTIN
#define abs __builtin_abs
#define acos __builtin_acos
#define acosf __builtin_acosf
#define acosh __builtin_acosh
#define acoshf __builtin_acoshf
#define acoshl __builtin_acoshl
#define acosl __builtin_acosl
#define asin __builtin_asin
#define asinf __builtin_asinf
#define asinh __builtin_asinh
#define asinhf __builtin_asinhf
#define asinhl __builtin_asinhl
#define asinl __builtin_asinl
#define atan __builtin_atan
#define atan2 __builtin_atan2
#define atan2f __builtin_atan2f
#define atan2l __builtin_atan2l
#define atanf __builtin_atanf
#define atanh __builtin_atanh
#define atanhf __builtin_atanhf
#define atanhl __builtin_atanhl
#define atanl __builtin_atanl
#define cbrt __builtin_cbrt
#define cbrtf __builtin_cbrtf
#define cbrtl __builtin_cbrtl
#define ceil __builtin_ceil
#define ceilf __builtin_ceilf
#define ceill __builtin_ceill
#define copysign __builtin_copysign
#define copysignf __builtin_copysignf
#define copysignl __builtin_copysignl
#define cos __builtin_cos
#define cosf __builtin_cosf
#define cosh __builtin_cosh
#define coshf __builtin_coshf
#define coshl __builtin_coshl
#define cosl __builtin_cosl
#define double_t __builtin_double_t
#define erf __builtin_erf
#define erfc __builtin_erfc
#define erfcf __builtin_erfcf
#define erfcl __builtin_erfcl
#define erff __builtin_erff
#define erfl __builtin_erfl
#define exp __builtin_exp
#define exp2 __builtin_exp2
#define exp2f __builtin_exp2f
#define exp2l __builtin_exp2l
#define expf __builtin_expf
#define expl __builtin_expl
#define expm1 __builtin_expm1
#define expm1f __builtin_expm1f
#define expm1l __builtin_expmll
#define fabs __builtin_fabs
#define fabsf __builtin_fabsf
#define fabsl __builtin_fabsl
#define fdim __builtin_fdim
#define fdimf __builtin_fdimf
#define fdiml __builtin_fdiml
#define float_t __builtin_float_t
#define floor __builtin_floor
#define floorf __builtin_floorf
#define floorl __builtin_floorl
#define fma __builtin_fma
#define fmaf __builtin_fmaf
#define fmal __builtin_fmal
#define fmax __builtin_fmax
#define fmaxf __builtin_fmaxf
#define fmaxl __builtin_fmaxl
#define fmin __builtin_fmin
#define fminf __builtin_fminf
#define fminl __builtin_fminl
#define fmod __builtin_fmod
#define fmodf __builtin_fmodf
#define fmodl __builtin_fmodl
#define fpclassify __builtin_fpclassify
#define frexp __builtin_frexp
#define frexpf __builtin_frexp
#define frexpl __builtin_frexpl
#define hypot __builtin_hypot
#define hypotf __builtin_hypotf
#define hypotl __builtin_hypotl
#define ilogb __builtin_ilogb
#define ilogbf __builtin_ilogbf
#define ilogbl __builtin_ilogbl
#define isfinite __builtin_isfinite
#define isgreater __builtin_isgreater
#define isgreaterequal __builtin_isgreaterequal
#define isinf __builtin_isinf
#define isless __builtin_isless
#define islessequal __builtin_islessequal
#define islessgreater __builtin_lessgreater
#define isnan __builtin_isnan
#define isnormal __builtin_normal
#define isunordered __builtin_isunordered
#define ldexp __builtin_ldexp
#define ldexpf __builtin_ldexpf
#define ldexpl __builtin_ldexpl
#define lgamma __builtin_lgamma
#define lgammaf __builtin_lgammaf
#define lgammal __builtin_lgammal
#define llrint __builtin_llrint
#define llrintf __builtin_llrintf
#define llrintl __builtin_llrintl
#define llround __builtin_llround
#define llroundf __builtin_llround
#define llroundl __builtin_llroundl
#define log __builtin_log
#define log10 __builtin_log10
#define log10f __builtin_log10f
#define log10l __builtin_log10l
#define log1p __builtin_log1p
#define log1pf __builtin_log1pf
#define log1pl __builtin_log1pl
#define log2 __builtin_log2
#define log2f __builtin_log2f
#define log2l __builtin_log2l
#define logb __builtin_logb
#define logbf __builtin_logbf
#define logbl __builtin_logbl
#define logf __builtin_logf
#define logl __builtin_logl
#define lrint __builtin_lrint
#define lrintf __builtin_lrintf
#define lrintl __builtin_lrintl
#define lround __builtin_lround
#define lroundf __builtin_lroundf
#define lroundl __builtin_lroundl
#define modf __builtin_modf
#define modff __builtin_modff
#define modfl __builtin_modfl
#define nan __builtin_nan
#define nanf __builtin_nanf
#define nanl __builtin_nanl
#define nearbyint __builtin_nearbyint
#define nearbyintf __builtin_nearbyintf
#define nearbyintl __builtin_nearbyintl
#define nextafter __builtin_nextafter
#define nextafterf __builtin_nextafterf
#define nextafterl __builtin_nextafterl
#define nexttoward __builtin_nexttoward
#define nexttowardf __builtin_nexttowardf
#define nexttowardl __builtin_nexttowardl
#define pow __builtin_pow
#define powf __builtin_powf
#define powi __builtin_powi
#define powl __builtin_powl
#define remainder __builtin_remainder
#define remainderf __builtin_remainderf
#define remainderl __builtin_remainderl
#define remquo __builtin_remquo
#define remquof __builtin_remquof
#define remquol __builtin_remquol
#define rint __builtin_rint
#define rintf __builtin_rintf
#define rintl __builtin_fintl
#define round __builtin_round
#define roundf __builtin_roundf
#define roundl __builtin_roundl
#define scalbln __builtin_scalbin
#define scalblnf __builtin_scalbinf
#define scalblnl __builtin_scalblnl
#define scalbn __builtin_scalbn
#define scalbnf __builtin_scalbnf
#define scalbnl __builtin_scalbnl
#define signbit __builtin_signbit
#define sin __builtin_sin
#define sinf __builtin_sinf
#define sinh __builtin_sinh
#define sinhf __builtin_sinhf
#define sinhl __builtin_sinhl
#define sinl __builtin_sinl
#define sqrt __builtin_sqrt
#define sqrtf __builtin_sqrtf
#define sqrtl __builtin_sqrtl
#define tan __builtin_tan
#define tanf __builtin_tanf
#define tanh __builtin_tanh
#define tanhf __builtin_tanhf
#define tanhl __builtin_tanhl
#define tanl __builtin_tanl
#define tgamma __builtin_tgamma
#define tgammaf __builtin_tgammaf
#define tgammal __builtin_tgammal
#define trunc __builtin_trunc
#define truncf __builtin_truncf
#define truncl __builtin_truncl
#endif // NO_BUILTIN
template <typename T> inline constexpr bool IsNum(const T _a) {
  return !(bool(isnan(_a))) && !(bool(isinf(_a)));
}
template <typename T> inline constexpr bool IsNan(const T _a) {
  return bool(isnan(_a));
}
template <typename T> inline constexpr bool IsInf(const T _a) {
  return bool(isinf(_a));
}
template <typename T, u64 N>
inline constexpr T *Cross(const T _a[N], const T _b[N], const T _c[N]) {
  T vec[3][N], dot;
  T ret[N];
  u32 i = 0;
  for (i = 0; i < N; i += 3) {
    vec[i][0] = _a[i];
    vec[i + 1][0] = _a[i + 1];
    vec[i + 2][0] = _a[i + 2];
    vec[i][1] = _b[i];
    vec[i + 1][1] = _b[i + 1];
    vec[i + 2][1] = _b[i + 2];
    vec[i][2] = _c[i];
    vec[i + 1][2] = _c[i + 1];
    vec[i + 2][2] = _c[i + 2];
    vec[i][0] =
        (vec[i + 1][1] * vec[i + 2][2]) - (vec[i + 2][1] * vec[i + 1][2]);
    vec[i][1] = -1 * ((vec[i + 1][0] * vec[i + 2][2]) -
                      (vec[i + 2][0] * vec[i + 1][2]));
    vec[i][2] =
        (vec[i + 1][0] * vec[i + 2][1]) - (vec[i + 2][0] * vec[i + 1][1]);
    dot = (vec[i + 1][0] * vec[2][0]) + (vec[i + 1][1] * vec[i + 2][1]) +
          (vec[i + 1][2] * vec[i + 2][2]);
    ret[i] = vec[i][0] * dot;
    ret[i + 1] = vec[i][1] * dot;
    ret[i + 2] = vec[i][2] * dot;
  }
  return ret;
}
template <typename T> inline constexpr T Floor(const T _a) {
  return T(floor(f64(_a)));
}
template <typename T> inline constexpr T Ceil(const T _a) {
  return T(ceil(f64(_a)));
}
template <typename T> inline constexpr T Hypot(T _a, T _b) {
  return T(hypot(f64(_a), f64(_b)));
}
template <typename T> inline constexpr T Square(const T _a) {
  return T(_a * _a);
}
template <typename T> inline constexpr T Madd(const T _a, T _b, const T _c) {
  return T(_a * _b + _c);
}
template <typename T> inline constexpr T Sqrt(const T _a) noexcept {
  return T(sqrt((f64)_a));
}
template <typename T> inline constexpr T Min(const T _a, const T _b) {
  return T(_a < _b ? _a : _b);
}
template <typename T> inline constexpr T Max(const T _a, const T _b) {
  return T(_a > _b ? _a : _b);
}
template <typename T> inline constexpr T Abs(const T _a) {
  return T(_a < 0 ? -_a : _a);
}
template <typename T> inline constexpr T Sign(const T _a) {
  return T(_a < 0 ? -1 : 1);
}
template <typename T> inline constexpr T Step(const T _a, const T _b) {
  return T(_a < _b ? 0 : 1);
}
template <typename T> inline constexpr T Fract(const T _a) {
  return T(_a - Floor(_a));
}
template <typename T>
inline constexpr T Lerp(const T _a, const T _b, const T _t) {
  return T(_a + (_b - _a) * _t);
}
template <typename T>
inline constexpr T SmoothStep(const T _a, const T _b, const T _t) {
  T t = T(Clamp((_t - _a) / (_b - _a), T(0.0), T(1.0)));
  return T(t * t * (T(3.0) - T(2.0) * t));
}
template <typename T> inline constexpr T RSqrt(const T _a) {
  if (IsNan(_a)) {
    throw("INV_SQRT failed: Not a number");
    return 0;
  }
  return T(1.0 / Sqrt(_a));
}
template <typename T> inline constexpr T Pow(const T _a, const i32 _b) {
  return T(__builtin_powi(f64(_a), i32(_b)));
}
template <typename T> inline constexpr T Pow(const T _a, const T _b) noexcept {
  return T(__builtin_pow(f64(_a), f64(_b)));
}
template <typename T> inline constexpr T Round(const T _a) {
  return T(__builtin_round((f64(_a))));
}
template <typename T> inline constexpr T Trunc(const T _a) noexcept {
  return T(__builtin_trunc(f64(_a)));
}
template <typename T> inline constexpr T Dot(const T _a, const T _b) {
  return T(_a * _b);
}
template <typename T> inline constexpr T Length(T _a, T _b) {
  return T(Sqrt((_a * _a) + (_b * _b)));
}
template <typename T, u64 N> inline constexpr T *Normalize(const T _a[N]) {
  u32 i = 0;
  T *ret[N];
  for (i = 0; i < N; i++) {
    *ret[i] = _a[i] / Length(_a[i], _a[i + 1]);
  }
  return *ret;
}
template <typename T> inline constexpr T Neg(const T _a) { return -_a; }
template <typename T> inline constexpr T Sub(const T _a, const T _b) {
  return T(_a - _b);
}
template <typename T> inline constexpr T Add(const T _a, const T _b) {
  return T(_a + _b);
}
template <typename T> inline constexpr T Mul(const T _a, const T _b) {
  return T(_a * _b);
}
template <typename T>
inline constexpr T Clamp(const T _a, const T _b, const T _c) {
  return T(Max(Min(_a, _b), _c));
}
template <typename T> inline constexpr T Rand(T _min, T _max, u32 _seed = 0) {
  return T(srand(_seed) % (_max - _min) + _min);
}
template <typename T> inline constexpr T Sin(T _a) noexcept {
  return T(__builtin_sin(f64(_a)));
}
template <typename T> inline constexpr T Cos(T _a) noexcept {
  return T(__builtin_cos(f64(_a)));
}
template <typename T> inline constexpr T Tan(T _a) noexcept {
  return T(__builtin_tan(f64(_a)));
}
template <typename T> inline constexpr T Asin(T _a) noexcept {
  return T(__builtin_asin(f64(_a)));
}
template <typename T> inline constexpr T Acos(T _a) noexcept {
  return T(__builtin_acos(f64(_a)));
}
template <typename T> inline constexpr T Atan(T _a) noexcept {
  return T(__builtin_atan(f64(_a)));
}
template <typename T> inline constexpr T Atan2(T _a, T _b) noexcept {
  return T(__builtin_atan2(f64(_a), f64(_b)));
}
template <typename T> inline T Log(T _a) noexcept {

  return T(__builtin_log(f64(_a)));
}
template <typename T> inline T log2(T _x) noexcept {
  return T(__builtin_log2(f64(_x)));
}
template <typename T> inline T Log10(T _a) noexcept {
  return T(__builtin_log10(f64(_a)));
}

struct Complex {
  f64 real = 0;
  f64 imag = 0;
  Complex() = default;
  Complex(f64 _real, f64 _imag) {
    real = _real;
    imag = _imag;
  }
  static Complex Zero() { return Complex(0, 0); }

  static Complex Add(Complex A, Complex B) {
    Complex out = {A.real + B.real, A.imag + B.imag};
    return out;
  }
  static Complex Sub(Complex A, Complex B) {
    Complex out = {A.real - B.real, A.imag - B.imag};
    return out;
  }
  static Complex Mul(Complex A, Complex B) {
    Complex out = {A.real * B.real - A.imag * B.imag,
                   A.real * B.imag + A.imag * B.real};
    return out;
  }
  static f64 *Mul(f64 *A, f64 *B) {
    //-------------Basied SIMD testing--------------//
    //  Using SIMD to compute the complex multiplication

    // if A=a+b*j,B=c+d*j; then A * B = (ac -bd) + (bc+ad)*j
    // load a b
    m128f64 n1 = _mm_load_pd(A);
    // load b a
    m128f64 n2 = _mm_loadr_pd(A);
    // load c c
    m128f64 n3 = _mm_load1_pd(B);
    // mul, ac bc
    n1 = _mm_mul_pd(n1, n3); //  a b * c c = ac|bc
    // load d d
    n3 = _mm_load1_pd(B + 1);
    // mul,bd ad
    n3 = _mm_mul_pd(n2, n3);
    // sub n1 n3->ac-bd,bc-ad
    n2 = _mm_sub_pd(n1, n3);
    // add n1 n3->ac+bd,bc+ad
    n3 = _mm_add_pd(n1, n3);
    // select n2.at[0] n3.at[1] || ac-bd bc+ad
    n1 = _mm_shuffle_pd(n2, n3, _MM_SHUFFLE2(1, 0));
    // dst[63:0] : = (imm8[0] == 0) ? a[63:0] : a[127:64]
    // dst[127:64] : = (imm8[1] == 0) ? b[63:0] : b[127:64]
    //  store and output
    f64 *C = new f64[2];
    _mm_store_pd(C, n1);
    return C;
  }
};
static void FFT2(Complex *X, int N) {
  // Notes	: the length of fft must be a power of 2,and it is  a in-place
  // algorithm ref		:
  // https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
  if (N < 2) {
    // bottom of recursion.
    // Do nothing here, because already X[0] = x[0]
  } else {
    Complex *Y = new Complex[N / 2]; // get temp heap storage
    for (u32 i = 0; i < N / 2; i++)  // copy all odd elements to heap storage
      Y[i] = X[i * 2 + 1];
    for (u32 i = 0; i < N / 2;
         i++) // copy all even elements to lower-half of a[]
      X[i] = X[i * 2];
    for (u32 i = 0; i < N / 2;
         i++) // copy all odd (from heap) to upper-half of a[]
      X[i + N / 2] = Y[i];
    delete[] Y;             // delete heap storage
    FFT2(X, N / 2);         // recurse even items
    FFT2(X + N / 2, N / 2); // recurse odd  items
    //                             // combine results of two half recursions
    for (u32 k = 0; k < N / 2; k++) {
      m128f64 o = _mm_load_pd((double *)&X[k + N / 2]); // odd
      f64 cc = Cos(-2. * PI * k / N);
      f64 ss = Sin(-2. * PI * k / N);
      m128f64 wr = _mm_load1_pd(
          &cc); //__m128d wr =  _mm_set_pd( cc,cc );		// cc
      m128f64 wi =
          _mm_set_pd(ss, -ss); // -d | d	, note that it is reverse order
      // compute the w*o
      wr = _mm_mul_pd(o, wr);                                // ac|bc
      m128f64 n1 = _mm_shuffle_pd(o, o, _MM_SHUFFLE2(0, 1)); // invert
      wi = _mm_mul_pd(n1, wi);                               // -bd|ad
      n1 = _mm_add_pd(wr, wi);
      o = _mm_load_pd((f64 *)&X[k]); // load even part
      wr = _mm_add_pd(o, n1);        // compute even part, X_e + w * X_o;
      wi = _mm_sub_pd(o, n1);        // compute odd part,  X_e - w * X_o;
      _mm_store_pd((f64 *)&X[k], wr);
      _mm_store_pd((f64 *)&X[k + N / 2], wi);
    }
  }
}
struct Mem {
public:
  u64 size = 0, used = 0, free = 0, total = 0;
  Mem() = default;
  enum class Unit : u8 {
    BYTE = 0,
    KBYTE = 1,
    MBYTE = 2,
    GBYTE = 3,
    TBYTE = 4,
    PBYTE = 5
  };
  Unit unit = Unit::BYTE;
  Mem(Unit _unit = Unit::BYTE) {
    size = 0;
    used = 0;
    free = 0;
    total = 0;
    unit = _unit;
  };
  Mem(u64 _size, u64 _used, u64 _free, u64 _total, Unit _unit = Unit::BYTE) {
    size = _size;
    used = _used;
    free = _free;
    total = _total;
    unit = _unit;
  }
  constexpr u64 Convert(Unit _unit) {
    f64 ratio = f64(1 << (u64(unit) * 10));
    ratio = ratio / (1 << (u64(_unit) * 10));
    return u64(size * ratio);
  }
  Mem Convert(Mem _mem) {
    f64 ratio = f64(1 << (u64(_mem.unit) * 10));
    ratio = ratio / (1 << (u64(unit) * 10));
    return Mem(u64(size * ratio), u64(used * ratio), u64(free * ratio),
               u64(total * ratio), _mem.unit);
  }
  u64 operator[](Unit _unit) { return Convert(_unit); }
  Mem &operator=(const Mem &_rhs) {
    size = _rhs.size;
    used = _rhs.used;
    free = _rhs.free;
    total = _rhs.total;
    unit = _rhs.unit;
    return *this;
  }
};
} // namespace origin