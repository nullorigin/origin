#pragma once
#include <cstdarg>
#include <cstdio>
namespace origin
{
    constexpr double EPSILON_SQRT = 0.0000000000000000000000000000001;
    constexpr double EPSILON = 0.00000000000000000000000000000001;
    constexpr double PI = 3.1415926535897932384626433832795;
    constexpr double HALF_PI = 1.5707963267948966192313216916398;
    constexpr double TWO_PI = 6.283185307179586476925286766559;
    constexpr double E = 2.7182818284590452353602874713527;
#define M_PI PI // pi
#define M_E E // e
#undef restrict
#undef __restrict
#define restrict __restrict
    using va_list = __builtin_va_list;
    using size_t = unsigned long long;
    using ptrdiff_t = long long;
    using wchar = wchar_t;
    using int8_t = signed char;
    using int16_t = short;
    using int32_t = int;
    using int64_t = long long;
    using uint8_t = unsigned char;
    using uint16_t = unsigned short;
    using uint32_t = unsigned int;
    using uint64_t = unsigned long long;
    using uint128_t = __uint128_t;
    using int128_t = __int128_t;

    inline bool div_overflow(int x, int y)
    {
        if (x == -2147483647 - 1 && y == -1)
            return true;
        x /= y;
        return false;
    }

    inline int imul(int x, int y)
    {
        return x * y;
    }
    inline int iadd(int x, int y)
    {
        return x + y;
    }
    inline int isub(int x, int y)
    {
        return x - y;
    }
    inline int idiv(int x, int y)
    {
        return x / y;
    }
    inline double add(double x, double y)
    {
        return x + y;
    }
    inline double sub(double x, double y)
    {
        return x - y;
    }
    inline double mul(double x, double y)
    {
        return x * y;
    }
    inline double div(double x, double y)
    {
        return x / y;
    }
    inline int mod(int x, int y)
    {
        return x % y;
    }
    //================(MATH BUILTIN)===================//
    inline bool mul_overflow(int x, int y)
    {
        return __builtin_mul_overflow(x, y, &x);
    }
    inline bool add_overflow(int x, int y)
    {
        return __builtin_add_overflow(x, y, &x);
    }
    inline bool sub_overflow(int x, int y)
    {
        return __builtin_sub_overflow(x, y, &x);
    }
    inline int abs(int x)
    {
        return __builtin_abs(x);
    }
    inline double abs(double x)
    {
        return __builtin_fabs(x);
    }
    inline long long llabs(long long x)
    {
        return __builtin_llabs(x);
    }
    inline long labs(long x)
    {
        return __builtin_labs(x);
    }
    inline double fabs(double x)
    {
        return __builtin_fabs(x);
    }

    inline double acos(double x)
    {
        return __builtin_acos(x);
    }
    inline float acosf(float x)
    {
        return __builtin_acosf(x);
    }
    inline long double acosl(long double x)
    {
        return __builtin_acosl(x);
    }

    inline double asin(double x)
    {
        return __builtin_asin(x);
    }
    inline float asinf(float x)
    {
        return __builtin_asinf(x);
    }
    inline long double asinl(long double x)
    {
        return __builtin_asinl(x);
    }

    inline double atan(double x)
    {
        return __builtin_atan(x);
    }
    inline float atanf(float x)
    {
        return __builtin_atanf(x);
    }
    inline long double atanl(long double x)
    {
        return __builtin_atanl(x);
    }

    inline double atan2(double y, double x)
    {
        return __builtin_atan2(y, x);
    }
    inline float atan2f(float y, float x)
    {
        return __builtin_atan2f(y, x);
    }
    inline long double atan2l(long double y, long double x)
    {
        return __builtin_atan2l(y, x);
    }

    inline double ceil(double x)
    {
        return __builtin_ceil(x);
    }
    inline float ceilf(float x)
    {
        return __builtin_ceilf(x);
    }
    inline long double ceill(long double x)
    {
        return __builtin_ceill(x);
    }

    inline double cos(double x)
    {
        return __builtin_cos(x);
    }
    inline float cosf(float x)
    {
        return __builtin_cosf(x);
    }
    inline long double cosl(long double x)
    {
        return __builtin_cosl(x);
    }

    inline double cosh(double x)
    {
        return __builtin_cosh(x);
    }
    inline float coshf(float x)
    {
        return __builtin_coshf(x);
    }
    inline long double coshl(long double x)
    {
        return __builtin_coshl(x);
    }

    inline double exp(double x)
    {
        return __builtin_exp(x);
    }
    inline float expf(float x)
    {
        return __builtin_expf(x);
    }
    inline long double expl(long double x)
    {
        return __builtin_expl(x);
    }

    inline float fabsf(float x)
    {
        return __builtin_fabsf(x);
    }
    inline long double fabsl(long double x)
    {
        return __builtin_fabsl(x);
    }

    inline double floor(double x)
    {
        return __builtin_floor(x);
    }
    inline float floorf(float x)
    {
        return __builtin_floorf(x);
    }
    inline long double floorl(long double x)
    {
        return __builtin_floorl(x);
    }

    inline double fmod(double x, double y)
    {
        return __builtin_fmod(x, y);
    }
    inline float fmodf(float x, float y)
    {
        return __builtin_fmodf(x, y);
    }
    inline long double fmodl(long double x, long double y)
    {
        return __builtin_fmodl(x, y);
    }

    inline double frexp(double value, int* exp)
    {
        return __builtin_frexp(value, exp);
    }
    inline float frexpf(float value, int* exp)
    {
        return __builtin_frexpf(value, exp);
    }
    inline long double frexpl(long double value, int* exp)
    {
        return __builtin_frexpl(value, exp);
    }

    inline double ldexp(double value, int exp)
    {
        return __builtin_ldexp(value, exp);
    }
    inline float ldexpf(float value, int exp)
    {
        return __builtin_ldexpf(value, exp);
    }
    inline long double ldexpl(long double value, int exp)
    {
        return __builtin_ldexpl(value, exp);
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

    inline double modf(double value, double* iptr)
    {
        return __builtin_modf(value, iptr);
    }
    inline float modff(float value, float* iptr)
    {
        return __builtin_modff(value, iptr);
    }
    inline long double modfl(long double value, long double* iptr)
    {
        return __builtin_modfl(value, iptr);
    }

    inline double pow(double x, double y)
    {
        return __builtin_pow(x, y);
    }
    inline float powf(float x, float y)
    {
        return __builtin_powf(x, y);
    }
    inline long double powl(long double x, long double y)
    {
        return __builtin_powl(x, y);
    }
    inline double powi(double x, int y)
    {
        return __builtin_powi(x, y);
    }
    inline double sin(double x)
    {
        return __builtin_sin(x);
    }
    inline float sinf(float x)
    {
        return __builtin_sinf(x);
    }
    inline long double sinl(long double x)
    {
        return __builtin_sinl(x);
    }

    inline double sinh(double x)
    {
        return __builtin_sin(x);
    }
    inline float sinhf(float x)
    {
        return __builtin_sinhf(x);
    }
    inline long double sinhl(long double x)
    {
        return __builtin_sinhl(x);
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
    inline long double tanl(long double x)
    {
        return __builtin_tanl(x);
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

    //  C99

    inline bool signbit(double x)
    {
        return __builtin_signbit(x) != 0;
    }

    inline double copysign(double x, double y)
    {
        return __builtin_copysign(x, y);
    }
    inline float copysignf(float x, float y)
    {
        return __builtin_copysignf(x, y);
    }
    inline long double copysignl(long double x, long double y)
    {
        return __builtin_copysignl(x, y);
    }

    inline double nan(const char* str)
    {
        return __builtin_nan(str);
    }

    inline float nanf(const char* str)
    {
        return __builtin_nanf(str);
    }

    inline long double nanl(const char* str)
    {
        return __builtin_nanl(str);
    }

    inline double huge_val()
    {
        return __builtin_huge_val();
    }
    inline float huge_valf()
    {
        return __builtin_huge_valf();
    }
    inline long double huge_vall()
    {
        return __builtin_huge_vall();
    }
    inline double infinity()
    {
        return __builtin_huge_val();
    }
    inline float infinityf()
    {
        return __builtin_huge_valf();
    }
    inline long double infinityl()
    {
        return __builtin_huge_vall();
    }

    inline int fpclassify(double x)
    {
        return __builtin_fpclassify(x, __builtin_huge_val(), __builtin_nan(""), 0.0, 0.0, 1.0);
    }

    inline bool isfinite(double x)
    {
        return __builtin_isfinite(x) != 0;
    }
    inline bool isinf(double x)
    {
        return __builtin_isinf(x) != 0;
    }
    inline bool isnan(double x)
    {
        return __builtin_isnan(x) != 0;
    }
    inline bool isnormal(double x)
    {
        return __builtin_isnormal(x) != 0;
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

    inline bool isgreaterequal(float x, float y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline bool isgreaterequal(long double x, long double y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline bool isgreaterequal(double x, double y)
    {
        return __builtin_isgreaterequal(x, y) != 0;
    }
    inline bool isless(double x, double y)
    {
        return __builtin_isless(x, y) != 0;
    }
    inline bool islessequal(double x, double y)
    {
        return __builtin_islessequal(x, y) != 0;
    }
    inline bool islessgreater(double x, double y)
    {
        return __builtin_islessgreater(x, y) != 0;
    }
    inline bool isunordered(double x, double y)
    {
        return __builtin_isunordered(x, y) != 0;
    }

    inline double acosh(double x)
    {
        return __builtin_acosh(x);
    }
    inline float acoshf(float x)
    {
        return __builtin_acoshf(x);
    }
    inline long double acoshl(long double x)
    {
        return __builtin_acoshl(x);
    }

    inline double asinh(double x)
    {
        return __builtin_asinh(x);
    }
    inline float asinhf(float x)
    {
        return __builtin_asinhf(x);
    }
    inline long double asinhl(long double x)
    {
        return __builtin_asinhl(x);
    }

    inline double atanh(double x)
    {
        return __builtin_atanh(x);
    }
    inline float atanhf(float x)
    {
        return __builtin_atanhf(x);
    }
    inline long double atanhl(long double x)
    {
        return __builtin_atanhl(x);
    }

    inline double cbrt(double x)
    {
        return __builtin_cbrt(x);
    }
    inline float cbrtf(float x)
    {
        return __builtin_cbrtf(x);
    }
    inline long double cbrtl(long double x)
    {
        return __builtin_cbrtl(x);
    }

    inline double erf(double x)
    {
        return __builtin_erf(x);
    }
    inline float erff(float x)
    {
        return __builtin_erff(x);
    }
    inline long double erfl(long double x)
    {
        return __builtin_erfl(x);
    }

    inline double erfc(double x)
    {
        return __builtin_erfc(x);
    }
    inline float erfcf(float x)
    {
        return __builtin_erfcf(x);
    }
    inline long double erfcl(long double x)
    {
        return __builtin_erfcl(x);
    }

    inline double exp2(double x)
    {
        return __builtin_exp2(x);
    }
    inline float exp2f(float x)
    {
        return __builtin_exp2f(x);
    }
    inline long double exp2l(long double x)
    {
        return __builtin_exp2l(x);
    }

    inline double expm1(double x)
    {
        return __builtin_expm1(x);
    }
    inline float expm1f(float x)
    {
        return __builtin_expm1f(x);
    }
    inline long double expm1l(long double x)
    {
        return __builtin_expm1l(x);
    }

    inline double fdim(double x, double y)
    {
        return __builtin_fdim(x, y);
    }
    inline float fdimf(float x, float y)
    {
        return __builtin_fdimf(x, y);
    }
    inline long double fdiml(long double x, long double y)
    {
        return __builtin_fdiml(x, y);
    }

    inline double fma(double x, double y, double z)
    {
        return __builtin_fma(x, y, z);
    }
    inline float fmaf(float x, float y, float z)
    {
        return __builtin_fmaf(x, y, z);
    }
    inline long double fmal(long double x, long double y, long double z)
    {
        return __builtin_fmal(x, y, z);
    }

    inline double fmax(double x, double y)
    {
        return __builtin_fmax(x, y);
    }
    inline float fmaxf(float x, float y)
    {
        return __builtin_fmaxf(x, y);
    }
    inline long double fmaxl(long double x, long double y)
    {
        return __builtin_fmaxl(x, y);
    }

    inline double fmin(double x, double y)
    {
        return __builtin_fmin(x, y);
    }
    inline float fminf(float x, float y)
    {
        return __builtin_fminf(x, y);
    }
    inline long double fminl(long double x, long double y)
    {
        return __builtin_fminl(x, y);
    }

    inline double hypot(double x, double y)
    {
        return __builtin_hypot(x, y);
    }
    inline float hypotf(float x, float y)
    {
        return __builtin_hypotf(x, y);
    }
    inline long double hypotl(long double x, long double y)
    {
        return __builtin_hypotl(x, y);
    }
    inline float hypot(float x, float y, float z)
    {
        return __builtin_sqrt(x * x + y * y + z * z);
    }
    inline double hypot(double x, double y, double z)
    {
        return __builtin_sqrt(x * x + y * y + z * z);
    }
    inline long double hypot(long double x, long double y, long double z)
    {
        return __builtin_sqrt(x * x + y * y + z * z);
    }

    inline int ilogb(double x)
    {
        return __builtin_ilogb(x);
    }
    inline int ilogbf(float x)
    {
        return __builtin_ilogbf(x);
    }
    inline int ilogbl(long double x)
    {
        return __builtin_ilogbl(x);
    }

    inline double lgamma(double x)
    {
        return __builtin_lgamma(x);
    }
    inline float lgammaf(float x)
    {
        return __builtin_lgammaf(x);
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
    inline long lrintf(float x)
    {
        return __builtin_lrintf(x);
    }
    inline long lrintl(long double x)
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

    inline double nextafter(double x, double y);
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

    inline double remquo(double x, double y, int* pquo)
    {
        return __builtin_remquo(x, y, pquo);
    }
    inline float remquof(float x, float y, int* pquo)
    {
        return __builtin_remquof(x, y, pquo);
    }
    inline long double remquol(long double x, long double y, int* pquo)
    {
        return __builtin_remquol(x, y, pquo);
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
    inline double scalbln(double x, int ex)
    {
        return __builtin_scalbln(x, ex);
    }
    inline float scalblnf(float x, int ex)
    {
        return __builtin_scalblnf(x, ex);
    }
    inline long double scalblnl(long double x, int ex)
    {
        return __builtin_scalblnl(x, ex);
    }
    inline double scalbn(double x, int ex)
    {
        return __builtin_scalbn(x, ex);
    }
    inline float scalbnf(long double x, int ex)
    {
        return __builtin_scalbnf(x, ex);
    }
    inline double scalbln(double x, long ex)
    {
        return __builtin_scalbln(x, ex);
    }
    inline float scalblnf(float x, long ex)
    {
        return __builtin_scalblnf(x, ex);
    }
    inline long double scalblnl(long double x, long ex)
    {
        return __builtin_scalblnl(x, ex);
    }

    inline float scalbnf(float x, int ex)
    {
        return __builtin_scalbnf(x, ex);
    }
    inline long double scalbnl(long double x, int ex)
    {
        return __builtin_scalbnl(x, ex);
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
    };
    inline long double truncl(long double x)
    {
        return __builtin_truncl(x);
    }
    inline constexpr float lerp(float a, float b, float t) noexcept
    {
        return a + (b - a) * t;
    } // C++20
    inline constexpr double lerp(double a, double b, double t) noexcept
    {
        return a + (b - a) * t;
    } // C++20
    inline constexpr long double lerp(long double a, long double b, long double t) noexcept
    {
        return a + (b - a) * t;
    }

    inline int fpclassify(int a, int b, int c, int d, int e, float f)
    {
        return __builtin_fpclassify(a, b, c, d, e, f);
    }

    inline bool isfinite(float x)
    {
        return __builtin_isfinite(x) != 0;
    }
    inline bool isfinite(long double x)
    {
        return __builtin_isfinite(x) != 0;
    }

    inline double nextafter(double x, double y)
    {
        return __builtin_nextafter(x, y);
    }
    inline int signbitf(float x)
    {
        return __builtin_signbitf(x);
    }
    inline int signbitl(long double x)
    {
        return __builtin_signbitl(x);
    }
    //===================STRING======================//

    inline unsigned long strlen(const char* str)
    {
        return __builtin_strlen(str);
    }

    inline int strcmp(const char* lhs, const char* rhs)
    {
        return __builtin_strcmp(lhs, rhs);
    }

    inline int strncmp(const char* lhs, const char* rhs, unsigned long count)
    {
        return __builtin_strncmp(lhs, rhs, count);
    }
    inline char* strcpy(char* dest, const char* src)
    {
        return __builtin_strcpy(dest, src);
    }

    inline char* strncpy(char* dest, const char* src, unsigned long count)
    {
        return __builtin_strncpy(dest, src, count);
    }

    inline char* strcat(char* dest, const char* src)
    {
        return __builtin_strcat(dest, src);
    }

    inline char* strncat(char* dest, const char* src, unsigned long count)
    {
        return __builtin_strncat(dest, src, count);
    }
    inline char* strstr(const char* haystack, const char* needle)
    {
        return __builtin_strstr(haystack, needle);
    }

    inline int vscanf(const char* restrict format, va_list ap...)
    {
        return __builtin_vscanf(format, ap);
    }
    inline int printf(const char* restrict format, ...)
    {
        return __builtin_printf(format);
    }
    inline int scanf(const char* restrict format, ...)
    {
        return __builtin_scanf(format);
    }
    inline int snprintf(char* restrict s, unsigned long n, const char* restrict format, ...)
    {
        return __builtin_snprintf(s, n, format);
    }
    inline int sprintf(char* restrict s, const char* restrict format, ...)
    {
        return __builtin_sprintf(s, format);
    }
    inline int sscanf(const char* restrict s, const char* restrict format, ...)
    {
        return __builtin_sscanf(s, format);
    }

    inline int vsprintf(char* restrict s, const char* restrict format, va_list ap...)
    {
        return __builtin_vsprintf(s, format, ap);
    }
    inline int vsscanf(const char* restrict s, const char* restrict format, va_list ap...)
    {
        return __builtin_vsscanf(s, format, ap);
    }

    inline int vsnprintf(char* restrict s, unsigned long n, const char* restrict format, va_list ap...)
    {
        return __builtin_vsnprintf(s, n, format, ap);
    }
    inline int wmemcmp(const wchar_t* lhs, const wchar_t* rhs, unsigned long count)
    {
        return __builtin_wmemcmp(lhs, rhs, count);
    }
    inline wchar_t* wmemcpy(wchar_t* dest, const wchar_t* src, unsigned long count)
    {
        return __builtin_wmemcpy(dest, src, count);
    }
    inline wchar_t* wmemmove(wchar_t* dest, const wchar_t* src, unsigned long count)
    {
        return __builtin_wmemmove(dest, src, count);
    }

    //===================MEMORY======================//
    inline char* char_memchr(const char* str, int value, unsigned long count)
    {
        return __builtin_char_memchr(str, value, count);
    }
    inline void* memchar(const void* str, int value_buffer, unsigned long count)
    {
        return __builtin_memchr(str, value_buffer, count);
    }
    inline void* memcpy(void* dest, const void* src, unsigned long count)
    {
        return __builtin_memcpy(dest, src, count);
    }

    inline void* memmove(void* dest, const void* src, unsigned long count)
    {
        return __builtin_memmove(dest, src, count);
    }
    inline int memcmp(const void* lhs, const void* rhs, unsigned long count)
    {
        return __builtin_memcmp(lhs, rhs, count);
    }
#ifdef va_copy
#undef va_copy
#endif
    inline void va_copy(va_list dst, va_list src)
    {
        return __builtin_va_copy(dst, src);
    }
} // namespace origin