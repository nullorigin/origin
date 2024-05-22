#pragma once

#include <algorithm>

#include "Builtin.hpp"
#include "Vector.hpp"

#include <cfloat>
#include <cstdlib>
#include <functional>

#include <utility>

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
inline auto operator new(unsigned long size, void* ptr, PlacementTag) noexcept
-> void*
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
inline void operator delete(void* ptr, unsigned long size, PlacementTag)
noexcept
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
namespace origin {

/// Using directive for `char` type.
///
/// Type alias for an 8-bit signed integer.
using i8 = char;

/// Reference to an `i8`.
///
/// Type alias for a reference to an 8-bit signed integer.
using i8r = char &;

/// Pointer to an `i8`.
///
/// Type alias for a pointer to an 8-bit signed integer.
using i8p = char *;

/// Pointer-to-pointer to an `i8`.
///
/// Type alias for a pointer to a pointer to an 8-bit signed integer.
using i8pr = char *&;

/// Array of `i8`.
///
/// Type alias for an array of 8-bit signed integers.
using i8pp = char **;

/// Rvalue reference to an `i8`.
///
/// Type alias for an rvalue reference to an 8-bit signed integer.
using i8rr = char &&;

/// Using directive for `unsigned char` type.
///
/// Type alias for an 8-bit unsigned integer.
using u8 = unsigned char;

/// Reference to a `u8`.
///
/// Type alias for a reference to an 8-bit unsigned integer.
using u8r = unsigned char &;

/// Pointer to a `u8`.
///
/// Type alias for a pointer to an 8-bit unsigned integer.
using u8p = unsigned char *;

/// Pointer-to-pointer to a `u8`.
///
/// Type alias for a pointer to a pointer to an 8-bit unsigned integer.
using u8pr = unsigned char *&;

/// Array of `u8`.
///
/// Type alias for an array of 8-bit unsigned integers.
using u8pp = unsigned char **;

/// Rvalue reference to a `u8`.
///
/// Type alias for an rvalue reference to an 8-bit unsigned integer.
using u8rr = unsigned char &&;

/// Using directive for `signed char` type.
///
/// Type alias for an 8-bit signed integer.
using s8 = signed char;

/// Reference to an `s8`.
///
/// Type alias for a reference to an 8-bit signed integer.
using s8r = signed char &;

/// Pointer to an `s8`.
///
/// Type alias for a pointer to an 8-bit signed integer.
using s8p = signed char *;

/// Pointer-to-pointer to an `s8`.
///
/// Type alias for a pointer to a pointer to an 8-bit signed integer.
using s8pr = signed char *&;

/// Array of `s8`.
///
/// Type alias for an array of 8-bit signed integers.
using s8pp = signed char **;

/// Rvalue reference to an `s8`.
///
/// Type alias for an rvalue reference to an 8-bit signed integer.
using s8rr = signed char &&;

/// Rvalue reference to an `i16`.
///
/// Type alias for an rvalue reference to a 16-bit signed integer.
using i16rr = short &&;

/// Reference to an `i16`.
///
/// Type alias for a reference to a 16-bit signed integer.
using i16r = short &;

/// Pointer to an `i16`.
///
/// Type alias for a pointer to a 16-bit signed integer.
using i16p = short *;

/// Pointer-to-pointer to an `i16`.
///
/// Type alias for a pointer to a pointer to a 16-bit signed integer.
using i16pr = short *&;

/// Array of `i16`.
///
/// Type alias for an array of 16-bit signed integers.
using i16pp = short **;

/// Using directive for `unsigned short` type.
///
/// Type alias for an unsigned 16-bit integer.
using u16 = unsigned short;

/// Reference to an `u16`.
///
/// Type alias for a reference to an unsigned 16-bit integer.
using u16r = unsigned short &;

/// Pointer to an `u16`.
///
/// Type alias for a pointer to an unsigned 16-bit integer.
using u16p = unsigned short *;

/// Pointer-to-pointer to an `u16`.
///
/// Type alias for a pointer to a pointer to an unsigned 16-bit integer.
using u16pr = unsigned short *&;

/// Array of `u16`.
///
/// Type alias for an array of unsigned 16-bit integers.
using u16pp = unsigned short **;

/// Using directive for `signed short` type.
///
/// Type alias for a signed 16-bit integer.
using s16 = signed short;

/// Reference to an `s16`.
///
/// Type alias for a reference to a signed 16-bit integer.
using s16r = signed short &;

/// Pointer to an `s16`.
///
/// Type alias for a pointer to a signed 16-bit integer.
using s16p = signed short *;

/// Pointer-to-pointer to an `s16`.
///
/// Type alias for a pointer to a pointer to a signed 16-bit integer.
using s16pr = signed short *&;

/// Array of `s16`.
///
/// Type alias for an array of signed 16-bit integers.
using s16pp = signed short **;

/// Using directive for `int` type.
///
/// Type alias for a 32-bit signed integer.
using i32 = int;

/// Reference to an `i32`.
///
/// Type alias for a reference to a 32-bit signed integer.
using i32r = int &;

/// Pointer to an `i32`.
///
/// Type alias for a pointer to a 32-bit signed integer.
using i32p = int *;

/// Pointer-to-pointer to an `i32`.
///
/// Type alias for a pointer to a pointer to a 32-bit signed integer.
using i32pr = int *&;

/// Array of `i32`.
///
/// Type alias for an array of 32-bit signed integers.
using i32pp = int **;

/// Using directive for `unsigned int` type.
///
/// Type alias for an unsigned 32-bit integer.
using u32 = unsigned int;

/// Reference to an `u32`.
///
/// Type alias for a reference to an unsigned 32-bit integer.
using u32r = unsigned int &;

/// Pointer to an `u32`.
///
/// Type alias for a pointer to an unsigned 32-bit integer.
using u32p = unsigned int *;

/// Pointer-to-pointer to an `u32`.
///
/// Type alias for a pointer to a pointer to an unsigned 32-bit integer.
using u32pr = unsigned int *&;

/// Array of `u32`.
///
/// Type alias for an array of unsigned 32-bit integers.
using u32pp = unsigned int **;

/// Using directive for `signed int` type.
///
/// Type alias for a signed 32-bit integer.
using s32 = signed int;

/// Reference to an `s32`.
///
/// Type alias for a reference to a signed 32-bit integer.
using s32r = signed int &;

/// Pointer to an `s32`.
///
/// Type alias for a pointer to a signed 32-bit integer.
using s32p = signed int *;

/// Pointer-to-pointer to an `s32`.
///
/// Type alias for a pointer to a pointer to a signed 32-bit integer.
using s32pr = signed int *&;

/// Array of `s32`.
///
/// Type alias for an array of signed 32-bit integers.
using s32pp = signed int **;

/// Using directive for `long long` type.
///
/// Type alias for a 64-bit signed integer.
using i64 = long long;

/// Reference to an `i64`.
///
/// Type alias for a reference to a 64-bit signed integer.
using i64r = long long &;

/// Pointer to an `i64`.
///
/// Type alias for a pointer to a 64-bit signed integer.
using i64p = long long *;

/// Pointer-to-pointer to an `i64`.
///
/// Type alias for a pointer to a pointer to a 64-bit signed integer.
using i64pr = long long *&;

/// Array of `i64`.
///
/// Type alias for an array of 64-bit signed integers.
using i64pp = long long **;

/// Using directive for `unsigned long long` type.
///
/// Type alias for an unsigned 64-bit integer.
using u64 = unsigned long long;

/// Reference to an `u64`.
///
/// Type alias for a reference to an unsigned 64-bit integer.
using u64r = unsigned long long &;

/// Pointer to an `u64`.
///
/// Type alias for a pointer to an unsigned 64-bit integer.
using u64p = unsigned long long *;

/// Pointer-to-pointer to an `u64`.
///
/// Type alias for a pointer to a pointer to an unsigned 64-bit integer.
using u64pr = unsigned long long *&;

/// Array of `u64`.
///
/// Type alias for an array of unsigned 64-bit integers.
using u64pp = unsigned long long **;

/// Using directive for `signed long long` type.
///
/// Type alias for a signed 64-bit integer.
using s64 = signed long long;

/// Reference to an `s64`.
///
/// Type alias for a reference to a signed 64-bit integer.
using s64r = signed long long &;

/// Pointer to an `s64`.
///
/// Type alias for a pointer to a signed 64-bit integer.
using s64p = signed long long *;

/// Pointer-to-pointer to an `s64`.
///
/// Type alias for a pointer to a pointer to a signed 64-bit integer.
using s64pr = signed long long *&;

/// Array of `s64`.
///
/// Type alias for an array of signed 64-bit integers.
using s64pp = signed long long **;

/// Using directive for `__int128_t` type.
///
/// Type alias for a 128-bit signed integer.
using i128 = __int128_t;

/// Reference to an `i128`.
///
/// Type alias for a reference to a 128-bit signed integer.
using i128r = __int128_t &;

/// Pointer to an `i128`.
///
/// Type alias for a pointer to a 128-bit signed integer.
using i128p = __int128_t *;

/// Pointer-to-pointer to an `i128`.
///
/// Type alias for a pointer to a pointer to a 128-bit signed integer.
using i128pr = __int128_t *&;

/// Array of `i128`.
///
/// Type alias for an array of 128-bit signed integers.
using i128pp = __int128_t **;

/// Using directive for `__uint128_t` type.
///
/// Type alias for an unsigned 128-bit integer.
using u128 = __uint128_t;

/// Reference to an `u128`.
///
/// Type alias for a reference to an unsigned 128-bit integer.
using u128r = __uint128_t &;

/// Pointer to an `u128`.
///
/// Type alias for a pointer to an unsigned 128-bit integer.
using u128p = __uint128_t *;

/// Pointer-to-pointer to an `u128`.
///
/// Type alias for a pointer to a pointer to an unsigned 128-bit integer.
using u128pr = __uint128_t *&;

/// Array of `u128`.
///
/// Type alias for an array of unsigned 128-bit integers.
using u128pp = __uint128_t **;

/// Using directive for `float` type.
///
/// Type alias for a 32-bit floating-point number.
using f32 = float;

/// Reference to an `f32`.
///
/// Type alias for a reference to a 32-bit floating-point number.
using f32r = float &;

/// Pointer to an `f32`.
///
/// Type alias for a pointer to a 32-bit floating-point number.
using f32p = float *;

/// Pointer-to-pointer to an `f32`.
///
/// Type alias for a pointer to a pointer to a 32-bit floating-point number.
using f32pr = float *&;
/// Array of `f32`.
///
/// Type alias for an array of 32-bit floating-point numbers.
using f32pp = float **;

/// Using directive for `double` type.
///
/// Type alias for a 64-bit floating-point number.
using f64 = double;

/// Reference to an `f64`.
///
/// Type alias for a reference to a 64-bit floating-point number.
using f64r = double &;

/// Pointer to an `f64`.
///
/// Type alias for a pointer to a 64-bit floating-point number.
using f64p = double *;

/// Pointer-to-pointer to an `f64`.
///
/// Type alias for a pointer to a pointer to a 64-bit floating-point number.
using f64pr = double *&;

/// Array of `f64`.
///
/// Type alias for an array of 64-bit floating-point numbers.
using f64pp = double **;

/// Using directive for `long double` type.
///
/// Type alias for a 128-bit floating-point number.
using f128 = long double;

/// Reference to an `f128`.
///
/// Type alias for a reference to a 128-bit floating-point number.
using f128r = long double &;

/// Pointer to an `f128`.
///
/// Type alias for a pointer to a 128-bit floating-point number.
using f128p = long double *;

/// Pointer-to-pointer to an `f128`.
///
/// Type alias for a pointer to a pointer to a 128-bit floating-point number.
using f128pr = long double *&;

/// Array of `f128`.
///
/// Type alias for an array of 128-bit floating-point numbers.
using f128pp = long double **;

/// Using directive for vector types attributes.
///
/// attribute alias for a vector with a 16 bit alignment and size.
#define vattr16 __attribute__((__vector_size__(16), __aligned__(16)))
/// Using directive for vector type attributes.
///
/// attribute alias for a vector with a 32 bit alignment and size.
#define vattr32 __attribute__((__vector_size__(32), __aligned__(32)))
/// Using directive for vector type attributes.
///
/// attribute alias for a vector with a 64 bit alignment and size..
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
static const u32 C4 = 0xf, C8 = 0xff, C16 = 0xffff, C32 = 0xffffff,
                 C64 = 0xffffffff;
template <typename T, typename U> auto cast(U c) { return static_cast<T>(c); }
template <typename T> constexpr auto cast(T c, T d) -> T {
  return (c << (sizeof(T) * 4) | d);
}
#define imax8 cast<i8>(127)
#define imax16 cast<i16>(32767)
#define imax32 cast<i32>(2147483647)
#define imax64 cast<i64>(9223372036854775807L)
#define imax128 cast<i128>(170141183460469231731687303715884105727L)
#define umax8 cast<u8>(255U)
#define umax16 cast<u16>(65535U)
#define umax32 cast<u32>(4294967295U)
#define umax64 cast<u64>(18446744073709551615UL)
#define umax128 cast<u128>(340282366920938463463374607431768211455ULL)
#define smax8 cast<s8>(127)
#define smax16 cast<s16>(32767)
#define smax32 cast<s32>(2147483647)
#define smax64 cast<s64>(9223372036854775807L)
#define fmax32 cast<f32>(3.40282346638528859811704183484516925440e+38)
#define fmax64 cast<f64>(1.797693134862315708145274237317043567981e+308)
#define fmax128 cast<f128>(1.18973149535723176508575932662800702e+4932)
#define imin8 cast<i8>(-128)
#define imin16 cast<i16>(-32768)
#define imin32 cast<i32>(-2147483648)
#define imin64 cast<i64>(-9223372036854775808L)
#define imin128 cast<i128>(-170141183460469231731687303715884105728LL)
#define umin8 cast<u8>(0)
#define umin16 cast<u16>(0)
#define umin32 cast<u32>(0)
#define umin64 cast<u64>(0)
#define umin128 cast<u128>(0)
#define smin8 cast<s8>(-128)
#define smin16 cast<s16>(-32768)
#define smin16 cast<s16>(-32768)
#define smin32 cast<s32>(-2147483648)
#define smin64 cast<s64>(-9223372036854775808L)
#define smin128 cast<s128>(-170141183460469231731687303715884105728LL)
constexpr auto FNMIN32 = -3.40282346638528859811704183484516925440e-38F;
constexpr auto FNMIN64 = -1.797693134862315708145274237317043567981e-308;
constexpr auto FNMIN128 = -1.18973149535723176502E+4932L;
constexpr auto FNMAX32 = -3.40282346638528859811704183484516925440e+38F;
constexpr auto FNMAX64 = -1.797693134862315708145274237317043567981e+308;
constexpr auto FNMAX128 = -1.18973149535723176502E+4932L;
constexpr auto FPMAX32 = 3.40282346638528859811704183484516925440e+38F;
constexpr auto FPMAX64 = 1.797693134862315708145274237317043567981e+308;
constexpr auto FPMAX128 = 1.18973149535723176502E+4932L;
constexpr auto FPMIN32 = 3.40282346638528859811704183484516925440e-38F;
constexpr auto FPMIN64 = 1.797693134862315708145274237317043567981e-308;
constexpr auto FPMIN128 = 1.18973149535723176502E-4932L;
// interval epsilon of f128
#ifndef NULL
#define NULL ((void *)0)
#endif
#define null ((void *)0)
using V = __builtin_va_list;
template <typename T> inline auto add(T a, T b) {
  T *c = *T(0);
  __builtin_add_overflow(a, b, c);
  return *c;
}
template <typename T> inline auto sub(T a, T b) {
  T *c = T(0);
  __builtin_sub_overflow(a, b, c);
  return *c;
}
template <typename T> inline auto mul(T a, T b) {
  T *c = T(0);
  __builtin_mul_overflow(a, b, c);
  return *c;
}

template <typename T> inline auto div(T a, T b) {
  T *c = T(0);
  div(a, b, c);
  return *c;
}

inline auto rand8p(u8p p) -> u8p {
  if ((__builtin_ia32_rdrand16_step(reinterpret_cast<u16p>(p)) == 1)) {
    return cast<u8p>(p);
  }
  return nullptr;
}
inline auto rand8() -> u8 {
  u8p p = nullptr;
  return *rand8p(p);
}
inline auto rand16p(u16p p) -> u16p {
  if ((__builtin_ia32_rdrand16_step(p)) == 1) {
    return p;
  }
  return nullptr;
}
inline auto rand16() -> u16 {
  u16p p = nullptr;
  return *rand16p(p);
}
inline auto rand32p(u32p p) -> u32p {
  if ((__builtin_ia32_rdrand32_step(p)) == 1) {
    return p;
  }
  return nullptr;
}
inline auto rand32() -> u32 {
  u32p p = nullptr;
  return *rand32p(p);
}
inline auto rand64p(u64p p) -> u64p {
  if ((__builtin_ia32_rdrand64_step(p)) == 1) {
    return p;
  }
  return nullptr;
}
inline auto rand64() -> u64 {
  u64p p = nullptr;
  return *rand64p(p);
}
template <typename T> inline auto random(T *p) -> T * {
  *p = cast<unsigned>(*p);
  (sizeof(T) == 8   ? rand64(p)
   : sizeof(T) == 4 ? rand32(p)
   : sizeof(T) == 2 ? rand16(p)
                    : rand8(p));
  if (p != nullptr) {
    return p;
  }
  return 0;
}

template <typename T> inline auto random() {
  T *p = nullptr;
  return cast<T>(origin::random(p));
}

template <typename T> constexpr auto isnan(T a) {
  return cast<bool>(__builtin_isnan(f128(a)));
}
template <typename T> constexpr auto isnan(T a, T b) {
  return bool(__builtin_isnan(cast<f128>(a), cast<f128>(b)));
}
template <typename T> constexpr auto isnan(T a, T b, T c) {
  return cast<bool>(__builtin_isnan(a, b, c));
}

template <typename T> constexpr auto isnan(T a, T b, T c, T d) noexcept {
  return cast<bool>(__builtin_isnan(a, b, c, d));
}
template <typename T> constexpr auto isinf(T a) {
  return cast<bool>(__builtin_isinf(a));
}

template <typename T> constexpr auto isinf(T a, T b) {
  return cast<bool>(__builtin_isinf(a, b));
}

template <typename T> constexpr auto isinf(T a, T b, T c) {
  return cast<bool>(__builtin_isinf(a, b, c));
}

template <typename... Args> constexpr auto isinf(Args... args) noexcept {
  return cast<bool>(__builtin_isinf(args...));
}
template <typename T> constexpr auto isNumeric(T a) {
  f128 num{a};
  return !cast<bool>(isnan(num) || isinf(num));
}

template <typename T> constexpr auto isnum(T a, T b) {
  return !(cast<bool>(isnan(a, b)) || cast<bool>(isinf(a, b)));
}

template <typename T> constexpr auto isnum(T a, T b, T c) {
  return !(cast<bool>(isnan(a, b, c)) || cast<bool>(isinf(a, b, c)));
}

template <typename T> constexpr auto isnum(T a, T b, T c, T d) noexcept {
  return !(cast<bool>(isnan(a, b, c, d)) || cast<bool>(isinf(a, b, c, d)));
}

template <typename T> constexpr auto sin(T a) noexcept {
  return T(__builtin_sinl(cast<f128>(a)));
}

template <typename T> constexpr auto cos(T a) noexcept {
  return T(__builtin_cosl(cast<f128>(a)));
}
template <typename T> constexpr auto atan2(T &a, T &b) noexcept {
  return T(__builtin_atan2l(cast<f128>(a), cast<f128>(b)));
}
template <typename T> constexpr auto asin(T a) noexcept {
  return T(__builtin_asinl(cast<f128>(a)));
}

template <typename T> constexpr auto acos(T a) noexcept {
  return T(__builtin_acosl(cast<f128>(a)));
}

template <typename T> constexpr auto atan(T a) noexcept {
  return T(__builtin_atanl(cast<f128>(a)));
}
template <typename T> constexpr auto ceil(T &a, T &b) {
  T c;
  __builtin_elementwise_ceil(a, b, &c);
  return c;
}

template <typename T> constexpr auto floor(T &a, T &b) {
  T c;
  (__builtin_elementwise_floor(a, b, &c));
  return c;
}

template <typename T> constexpr auto round(T &a) noexcept {
  T b;
  (__builtin_elementwise_round(a, &b));
  return b;
}
template <typename T> constexpr auto trunc(T &a, T &b) noexcept {
  T c;
  (__builtin_elementwise_trunc(a, b, &c));
  return c;
}

template <typename T> constexpr auto rint(T &a, T &b) {
  T c;
  (__builtin_elementwise_rint(a, b, &c));
  return c;
}
template <typename T> constexpr auto nearbyint(T &a, T &b, T *c) {
  T d;
  (__builtin_elementwise_nearbyint(a, b, c, &d));
  return d;
}

template <typename T, typename U> constexpr auto copysign(T &a) noexcept {
  T b;
  (__builtin_elementwise_copysign(a, &b));
  return b;
}

template <typename T> constexpr auto sin(T &a) noexcept {
  T b;
  (__builtin_elementwise_sin(a, &b));
  return b;
}
template <typename T> constexpr auto cos(T &a) {
  T b;
  (__builtin_elementwise_cos(a, &b));
  return b;
}
template <typename T> constexpr auto addsat(T &a, T &b) {
  T *c = nullptr;
  (__builtin_elementwise_add_sat(a, b, c));
  return *c;
}
template <typename T> constexpr auto subsat(T &a, T &b) {
  T *c = nullptr;
  (__builtin_elementwise_sub_sat(a, b, c));
  return *c;
}
template <typename T> constexpr auto min(T a, T b) noexcept {
  return T((a < b) ? a : b);
}

template <typename T> constexpr auto min(T a, T b, T c) noexcept {
  return T((a < b) ? (a < c ? a : c) : (b < c ? b : c));
}

template <typename T> constexpr auto min(T a, T b, T c, T d) noexcept {
  return T((a < b) ? (a < c ? (a < d ? a : d) : c)
                   : (b < c ? (b < d ? b : d) : (c < d ? c : d)));
}
template <typename T> constexpr auto max(T a, T b) noexcept {
  return T((a < b) ? b : a);
}
template <typename T> constexpr auto max(T a, T b, T c) noexcept {
  return T((a < b) ? (b < c ? c : b) : (a < c ? c : a));
}

template <typename T> constexpr auto max(T a, T b, T c, T d) noexcept {
  return T((a < b) ? (b < c ? (c < d ? d : c) : b)
                   : (a < c ? (c < d ? d : c) : (a < d ? d : a)));
}

template <typename T> constexpr auto sqrt(T a) {
  return T(__builtin_sqrtl(cast<f128>(a)));
}
template <typename T> constexpr auto log(T &a) {
  T b;
  (__builtin_elementwise_log(a, &b));
  return b;
}
template <typename T> constexpr auto log2(T &a, T &b) {
  T c;
  (__builtin_elementwise_log2(a, b, &c));
  return c;
}
template <typename T> constexpr auto log10(T &a) {
  f128 b = cast<f128>(a);
  (__builtin_elementwise_log10(b));
  return T(b);
}
template <typename T> constexpr auto exp(T &a) {
  T b;
  (__builtin_elementwise_exp(a, &b));
  return b;
}
template <typename T> inline auto exp2(T &a, T &b) {
  T c;
  (__builtin_elementwise_exp2(a, b, &c));
  return c;
}
template <typename T, typename U> constexpr auto pow(T &a, U &b) {
  T *c = nullptr;
  (__builtin_elementwise_pow(a, b, c));
  return *c;
}
using ID = u64;

template <typename T> constexpr auto isnormal(T a) {
  return bool(__builtin_isnormal(a));
}

template <typename T> constexpr auto isnormal(T a, T b) {
  return bool(__builtin_isnormal(a, b));
}

template <typename T> constexpr auto isnormal(T a, T b, T c) {
  return bool(__builtin_isnormal(a, b, c));
}

template <typename T> constexpr auto isnormal(T a, T b, T c, T d) {
  return bool(__builtin_isnormal(a, b, c, d));
}
template <typename T> constexpr auto isfinite(T a) {
  return bool(__builtin_isfinite(a));
}
template <typename T> constexpr auto isfinite(T a, T b) {
  return bool(__builtin_isfinite(a, b));
}
template <typename T> constexpr auto isfinite(T a, T b, T c) {
  return bool(__builtin_isfinite(a, b, c));
}
template <typename T> constexpr auto isfinite(T a, T b, T c, T d) {
  return bool(__builtin_isfinite(a, b, c, d));
}
#undef alloca
template <typename T> auto alloca(unsigned long a) {
  return cast<T>(__builtin_alloca(a));
}
template <typename T> auto memchr(const void *a, int b, unsigned long c) {
  return cast<T>(__builtin_memchr(a, b, c));
}
template <typename T> auto memmove(void *a, const void *b, unsigned long c) {
  return cast<T>(__builtin_memmove(a, b, c));
}
template <typename T> auto memcpy(void *a, const void *b, unsigned long c) {
  return cast<T>(__builtin_memcpy(a, b, c));
}
template <typename T>
auto memcmp(const void *a, const void *b, unsigned long c) {
  return cast<T>(__builtin_memcmp(a, b, c));
}
template <typename T> auto memset(void *a, int b, unsigned long c) {
  return cast<T>(__builtin_memset(a, b, c));
}
template <typename T> constexpr auto cross(T a[3], T b[3], T c[3]) noexcept {
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
template <typename T> constexpr auto reverse(T a) {
  T result = 0;
  for (u32 i = 0; i < sizeof(T); i++) {
    result = (result << 1) | (a & 1);
    a >>= 1;
  }
  return result;
}
template <typename T> constexpr auto bitset(T a) {
  T b = 0;
  for (u32 i = 0; i < sizeof(T); i++) {
    b = (b << 1) | ((a >> i) & 1);
  }
  return b;
}

template <typename T> constexpr auto hypot(T a, T b) {
  return T(__builtin_hypotl(cast<f128>(a), cast<f128>(b)));
}
template <typename T> constexpr auto square(T a) { return T(a * a); }
template <typename T> constexpr auto madd(T a, T b, T c) {
  return T(a * b + c);
}
template <typename T> constexpr auto copysign(T a, T b) {
  return T(__builtin_copysignl(cast<f128>(a), cast<f128>(b)));
}
template <typename T> constexpr auto clamp(T a, T b, T c) {
  return origin::min<T>(origin::max<T>(a, b), c);
}
template <typename T> constexpr auto step(T a, T b) {
  return origin::clamp(b - a, 0.0, 1.0);
}
template <typename T> constexpr auto fract(T a) noexcept {
  return T(cast<f128>(a) - __builtin_floorl(cast<f128>(a)));
}
template <typename T> constexpr auto lerp(T a, T b, T c) noexcept {
  return T(a + c * (b - a));
}
template <typename T> constexpr auto smoothstep(T a, T b, T c) {
  auto c2 = clamp(c - a / b - a, 0.0, 1.0);
  return T(c2 * c2 * 3.0 - 2.0 * c2);
}
template <typename T> constexpr auto rsqrt(T a) {
  return T(1.0 / sqrtl(cast<f128>(a)));
}
template <typename T> constexpr auto dot(T a, T b) noexcept { return T(a * b); }
template <typename T> constexpr auto length(T a, T b) {
  return T(sqrt(cast<f128>(a * a + b * b)));
}
template <typename T, u64 N> constexpr auto normalize(T const (&arr)[N]) {
  T out[N];
  for (u64 i = 0; i < N; ++i) {
    out[i] = arr[i] /
             sqrt(arr[i] * arr[i] + (i + 1 < N ? arr[i + 1] * arr[i + 1] : 0));
  }
  return out;
}
template <typename T> auto neg(T a) { return T(mul(cast<f128>(a), (-1))); }

template <typename T> constexpr auto random(T a, T b) {
  return abs(rand64() % cast<u64>((b - a) + a));
}
template <typename T> constexpr auto tan(T a) {
  return T(__builtin_tanl(cast<f128>(a)));
}
template <typename T> constexpr auto atan2(T a, T b) noexcept {
  return T(__builtin_atan2l(cast<f128>(a), cast<f128>(b)));
}

template <typename T> constexpr auto sinsq(T a) noexcept {
  const T b = T(__builtin_sinl(cast<f128>(a)));
  return b * b;
}
template <typename T> constexpr auto cossq(T a) noexcept {
  const T b = T(__builtin_cosl(cast<f128>(a)));
  return b * b;
}

template <u64 N> struct Complex {
public:
  union {
    f128 Data[N * 2];
    struct {
      f128 Real[N];
      f128 Imag[N];
    };
  } C;
  explicit Complex(f64 real = 0, f64 imag = 0) {
    C.Real = real;
    C.Imag = imag;
  }
  static auto zero() -> Complex { return {0, 0}; }

  auto add(const Complex<N> b) const noexcept -> Complex<N> {
    return {C.Real + b.Real, C.Imag + b.Imag};
  }
  auto sub(const Complex<N> b) const noexcept -> Complex<N> {
    return {C.Real - b.Real, C.Imag - b.Imag};
  }
  auto mul(const Complex b) const noexcept -> Complex {
    return {C.Real * b.Real - C.Imag * b.Imag,
            C.Real * b.Imag + C.Imag * b.Real};
  }
  auto div(const Complex a) const noexcept -> Complex {
    return {(a.Real * C.Real + a.Imag * C.Imag) /
                (C.Real * C.Real + C.Imag * C.Imag),
            (a.Imag * C.Real - a.Real * C.Imag) /
                (C.Real * C.Real + C.Imag * C.Imag)};
  }
  static auto add(const Complex A, const Complex B) noexcept -> Complex {
    return {A.Real + B.Real, A.Imag + B.Imag};
  }

  static auto sub(const Complex A, const Complex B) noexcept -> Complex {
    return {A.Real - B.Real, A.Imag - B.Imag};
  }
  static auto mul(const Complex<N> a,
                  const Complex<N> b) noexcept -> Complex<N> {
    return {a.Real * b.Real - a.Imag * b.Imag,
            a.Real * b.Imag + a.Imag * b.Real};
  }
  static auto div(Complex a, Complex b) noexcept -> Complex {
    return {(a.Real * b.Real + a.Imag * b.Imag) /
                (b.Real * b.Real + b.Imag * b.Imag),
            (a.Imag * b.Real - a.Real * b.Imag) /
                (b.Real * b.Real + b.Imag * b.Imag)};
  }
  auto mul(f64 *out, const f64 *in) const noexcept {
    auto *ret = out;
    for (u64 i = 0; i < N; i++) {
      ret[i] = C.Real[i] * in[i] - C.Imag[i] * in[i + N];
      ret[i + N] = C.Real[i] * in[i + N] + C.Imag[i] * in[i];
    }
    return ret;
  }

  static auto fft(const Complex *input, u64 n) -> Complex * {
    auto output = new Complex[n];
    f64 wn = -2 * PI / n;

    // Divide input into even and odd parts
    for (u64 i = 0; i < n; i += 4) {
      const auto a = input[i].real;
      const auto b = input[i + 1].real;
      const auto c = input[i + 2].real;
      const auto d = input[i + 3].real;
      output[i].real = a + c;
      output[i + 1].real = a - c;
      output[i + 2].real = b + d;
      output[i + 3].real = b - d;
    }

    for (u64 size = 4, half_size = n >> 1U; size <= n;
         size <<= 2U, half_size >>= 1U) {
      const auto w = wn;
      for (u64 i = 0; i < n; i += size) {
        for (u64 j = i; j < i + half_size; j += 4) {
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
    for (u64 i = 1, j = 0; i < n; ++i) {
      u64 x = i;
      u64 k = n >> 1U;
      while (j >= k) {
        x = (x ^ (j & ~k)) & (n - 1);
        j &= k;
        k >>= 1U;
      }
      if (i < (j | k)) {
        std::swap(output[i], output[j | k]);
      }
    }

    // Normalize
    const auto norm = 1.0 / sqrt(n);
    for (u64 i = 0; i < n; i += 4) {
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

  static auto conjugate(Complex *C1) -> Complex * {
    auto *c = C1;
    for (u64 i = 0; i < N; i++) {
      c[i].Imag = -c[i].Imag;
    }
    return c;
  }

  static auto fft2(Complex *input) -> Complex * {
    auto *c = input;

    // Cooley–Tukey FFT (in-place)
    for (size_t size = 1, half_size = 1; size < N;
         size <<= 1U, half_size = size >> 1U) {
      const double phase = -2 * PI / size;
      for (size_t first_index = 0; first_index < N; first_index += size) {
        for (size_t index = 0; index < half_size; ++index) {
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
    for (size_t i = 1, j = 0; i < N; ++i) {
      size_t k = N >> 1U;
      while ((j ^= k) < k) {
        k >>= 1U;
      }
      if (i < j) {
        std::swap(c[i], c[j]);
      }
    }

    // Normalize
    const double norm = 1.0 / sqrt(N);
    for (size_t i = 0; i < N; i += 4) {
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

  static auto ifft(Complex *C1) -> Complex * {
    auto *c = C1;
    c = conjugate(c, N);
    fft2(c, N);
    c = conjugate(c, N);
    return c;
  }
  auto operator+(Complex<N> a) const noexcept -> Complex<N> {
    return this->add(a);
  }

  auto operator-(Complex<N> a) const noexcept -> Complex<N> {
    return this->sub(*this, a);
  }
  auto operator*(Complex<N> a) const noexcept -> Complex<N> {
    return this->mul(a);
  }

  auto operator/(Complex<N> a) const noexcept -> Complex<N> {
    return this->div(a);
  }
} __attribute__((aligned(32)));
struct Mem {
private:
  f64 Mem_size = 0.0;
  f64 Mem_used = 0.0;
  f64 Mem_max = 1.000000e+15;

public:
  enum class Unit : i8 {
    NONE = -1,
    BYTE = 0,
    KBYTE = 1,
    MBYTE = 2,
    GBYTE = 3,
    TBYTE = 4,
    PBYTE = 5
  } Mem_unit = Unit::BYTE;
  explicit Mem(enum Unit unit = Unit::BYTE) : Mem_unit(unit) {
    Mem_size = Mem_used = 0.0;
  }
  explicit Mem(f64 size, f64 used = 0.0, enum Unit unit = Unit::BYTE)
      : Mem_size(size), Mem_used(used < size ? used : size), Mem_unit(unit) {}
  Mem(const Mem &rhs) { *this = rhs; }
  Mem(Mem &&rhs) noexcept { *this = std::move(rhs); }
  ~Mem() {
    Mem_size = Mem_used = 0.0;
    Mem_unit = Unit::BYTE;
  }
  [[nodiscard]] auto convert(const enum Unit unit) const -> Mem {
    const u8 one = 1;
    const u8 unit0 = static_cast<u8>(Mem_unit) * 10;
    const u8 unit1 = static_cast<u8>(unit) * 10;
    f64 ratio = one << unit0;
    ratio /= one << unit1;
    return Mem(Mem_size * ratio, Mem_used * ratio, unit);
  }
  [[nodiscard]] auto convert(const Mem &mem) const -> Mem {
    const u8 one = 1;
    if (mem.Mem_unit == Unit::NONE) {
      return Mem{Mem_size, Mem_used, Mem_unit};
    };
    const u8 unit0 = static_cast<u8>(Mem_unit) * 10;
    const u8 unit1 = static_cast<u8>(mem.Mem_unit) * 10;
    f64 ratio = one << unit0;
    ratio /= one << unit1;
    return Mem{mem.Mem_size * ratio, mem.Mem_used * ratio, mem.Mem_unit};
  }
  auto operator[](enum Unit unit) const { return convert(unit); }
  auto operator=(const Mem &rhs) -> Mem & = default;
  auto operator=(Mem &&rhs) noexcept -> Mem & { return *this = rhs; }
  [[nodiscard]] constexpr auto size() const -> f64 { return Mem_size; }
  [[nodiscard]] constexpr auto total() const -> f64 { return size(); }
  [[nodiscard]] constexpr auto available() const -> f64 {
    return Mem_size - Mem_used;
  }
  [[nodiscard]] constexpr auto used() const -> f64 { return Mem_used; }
  [[nodiscard]] constexpr auto free() const -> f64 {
    return Mem_size - Mem_used;
  }
  [[nodiscard]] constexpr auto percentage() const -> f64 {
    return ((Mem_used) / (Mem_size)) * 100.0;
  }
  [[nodiscard]] constexpr auto percentageUsed() const -> f64 {
    return ((Mem_used) / (Mem_size)) * 100.0;
  }
  [[nodiscard]] constexpr auto percentageFree() const -> f64 {
    return ((Mem_size) / (Mem_used)) * 100.0;
  }
  constexpr auto set(const f64 size = -1, const f64 used = -1,
                     enum Unit unit = Unit::NONE) -> Mem & {
    if (unit != Unit::NONE) {
      if (size >= 0.0 && size < Mem_max) {
        Mem_size = size;
      }
      if (used >= 0.0 && used <= Mem_size) {
        Mem_used = used;
      }
      if (unit >= Unit::BYTE && unit <= Unit::PBYTE && unit != Mem_unit) {
        Mem_unit = unit;
      }
    }
    return *this;
  }
} __attribute__((aligned(32))) __attribute__((packed));
template <typename T, typename... U>
class Function : public std::function<T (*)(U...)> {
public:
  Function() = default;
  explicit Function(std::function<T (*)(U...)> f)
      : std::function<T (*)(U...)>(f) {}
  explicit Function(T (*f)(U...))
      : std::function<T (*)(U...)>((std::function<T (*)(U...)>(f))) {}
  Function(const Function &f) : std::function<T (*)(U...)>(f) {}
  Function(Function &&f) noexcept : std::function<T (*)(U...)>(std::move(f)) {}
  ~Function() = default;
  explicit operator Function() { return std::function<T (*)(U...)>(*this); }
  explicit operator std::function<T (*)(U...)>() {
    return std::function<T (*)(U...)>(*this);
  }
  Function &operator=(const Function &f) {
    *this = std::function<T (*)(U...)>(f);
    return *this;
  }
  Function &operator=(Function &&f) noexcept {
    *this = std::function<T (*)(U...)>(std::move(f));
    return *this;
  }
  Function &operator=(T (*f)(U...)) {
    *this = std::function<T (*)(U...)>(f);
    return *this;
  }
  Function &operator=(Function f) {
    *this = std::function<T (*)(U...)>(f);
    return *this;
  }
  auto operator()(U... args) { return T(args...); }
  auto operator()(U... args) const -> T & { return T(args...); }
  explicit Function(U... args) { return &(*this)(args...); }
};
template <typename T, typename... U> struct Op {
private:
  using function = Function<T, U...>;
  static constexpr auto FMAX = [](U... args) {
    return __builtin_fmax(args...);
  };
  static constexpr auto FMIN = [](U... args) {
    return __builtin_fmin(args...);
  };
  Vector<function> Fvec = Vector<function>();

public:
  auto emplaceMin(U... args) {
    return Fvec.emplace_back(Fvec.transform(Fvec, FMIN(args...)));
  }
  auto emplaceMax(U... args) {
    return Fvec.emplace_back(Fvec.transform(Fvec, FMAX(args...)));
  }

  auto pushBack(function f) {
    if constexpr (sizeof(V) > 0) {
      Fvec.push_back([=](V args...) { return f(args); });
      return *Fvec.rbegin();
    } else {
      Fvec.push_back(f);
      return *Fvec.rbegin();
    }
  }

  Op() = default;
  Op(Op &&) = default;
  Op &operator=(Op const &op) {
    if (this == &op) {
      return *this;
    }
    Fvec = op.Fvec;
    return *this;
  }
  auto clear() { Fvec.clear(); }
  auto size() { return Fvec.size(); }
  auto begin() { return Fvec.begin(); }
  auto end() { return Fvec.end(); }
  auto rbegin() { return Fvec.rbegin(); }
  auto rend() { return Fvec.rend(); }
  auto &get(u32 i) { return Fvec[i]; }
  auto &operator[](u32 i) { return Fvec[i]; }
  auto push(Op op) noexcept { Fvec.pushBack(std::move(op.Func)); }
  Op(Op const &op) {
    *this = op;
    return *this;
  }
  explicit Op(function f) {
    this->Fvec.pushBack(f);
    return *this;
  }
  ~Op() = default;
  auto operator()(function f) {
    this->Fvec.pushBack(f);
    return *this;
  }
  explicit operator function() const { return Fvec.begin(); }
  Op &operator=(Op &&op) noexcept { return *this = std::move(op); }
  Op &operator=(Op op) noexcept { return *this = std::move(op); }
  auto operator<<(function &&f) {
    Fvec.pushBack(f);
    return Fvec;
  }
  auto &operator<<(function const &f) {
    Fvec.pushBack(f);
    return Fvec;
  }
  auto &operator<<(Op const &op) {
    Fvec.pushBack(op.f);
    return Fvec;
  }
  auto operator()() const noexcept { return Fvec.cbegin(); }
  auto operator()() { return Fvec.begin(); }

  auto operator()(Op const &op) {
    *this() = op();
    return *this();
  }
  auto operator->() { return &Fvec.begin(); }

  auto operator->() const { return &Fvec.cbegin(); }

  auto operator()(V args) -> Vector<function> { return *Fvec(args); }

  auto operator*(V args) -> Vector<function> { return *Fvec(args); }

  auto reset(function f) { f = nullptr; }

  auto reset(Op const &op) { *this = op; }

  auto empty() const { return Fvec == nullptr; }

  auto swap(Op &op) noexcept { std::swap(Fvec, op.Fvec); }

  auto get() const { return Fvec; }
};
} // namespace origin
