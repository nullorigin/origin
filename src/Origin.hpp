#pragma once
#include <cstddef>
#include <cstdlib>
#include <math.h>
namespace Origin {
typedef char I8;
typedef short I16;
typedef int I32;
typedef long long I64;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef unsigned long long U64;
typedef signed char S8;
typedef signed short S16;
typedef signed int S32;
typedef signed long long S64;
typedef float F32;
typedef double F64;
#if WORDSIZE == 64
typedef unsigned long SIZE_T;
#else
typedef unsigned long long SIZE_T;
#endif
static const U32 X = 1, Y = 2, XY = 3, Z = 4, XZ = 5, YZ = 6, XYZ = 7, W = 8,
                 XW = 9, YW = 10, XYW = 11, ZW = 12, XZW = 13, YZW = 14,
                 XYZW = 15;
static const U32 C8 = 0xff, C16 = 0xffff, C32 = 0xffffff, C64 = 0xffffffff;
constexpr F64 PI = 3.14159265358979323846535897932384;
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
#define U64_C2(h, l) ((static_cast<U64>(h) << 32) | static_cast<U64>(l))
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
#define FE32 F32_C(1.1920928955078125e-07f)
#define FE64 F64_C(2.220446049250313080847263336181640625e-16)
#ifndef NULL
#define NULL ((void *)0)
#endif

struct String {
private:
  U8 *data;
  U32 length;

public:
  String(U32 _length = 0);
  String(U8 *_data, U32 _length);
  ~String();
  U8 *CStr(U32 length = sizeof(*data)) const;
  U32 StrLen(U8 *str);
  void StrCpy(U8 *dest, U8 *src);
  U8 *StrCat(U8 *str1, U8 *str2);
  inline U8 operator[](U32 index) { return data[index]; }
  inline operator U8 *() { return data; }             // U8*
  inline operator const U8 *() const { return data; } // const U8*
  String operator=(const U8 *str);
  String operator=(const String str);
  String operator+(const U8 *str);
  String operator+(const String str);
  String operator+=(const U8 *str);
  String operator+=(const String str);
};
template <typename T> inline constexpr T Floor(const T _a) {
  return T(_a - T(I64(_a)));
}
template <typename T> inline constexpr T Square(const T _a) {
  return T(_a * _a);
}
template <typename T> inline constexpr T Madd(const T _a, T _b, const T _c) {
  return T(_a * _b + _c);
}
template <typename T> inline constexpr T Sqrt(const T _a) noexcept {
  return T(__builtin_sqrt((F64)_a));
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
template <typename T> inline constexpr T Pow(const T _a, const T _b) noexcept {
  return T(__builtin_pow(F64(_a), F64(_b)));
}
template <typename T> inline constexpr T Round(const T _a) {
  return T(__builtin_round((F64(_a))));
}
template <typename T> inline constexpr T Trunc(const T _a) noexcept {
  return T(__builtin_trunc(F64(_a)));
}
template <typename T> inline constexpr T Dot(const T _a, const T _b) {
  return T(_a * _b);
}
template <typename T> inline constexpr T Length(T _a, T _b) {
  return T(Sqrt((_a * _a) + (_b * _b)));
}
template <typename T, U64 N> inline constexpr T *Normalize(const T _a[N]) {
  U32 i = 0;
  ;
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
template <typename T> inline constexpr T Rand(T _min, T _max, U32 _seed = 0) {
  return T(srand(_seed) % (_max - _min) + _min);
}
template <typename T> inline constexpr T Sin(T _a) noexcept {
  return T(__builtin_sin(F64(_a)));
}
template <typename T> inline constexpr T Cos(T _a) noexcept {
  return T(__builtin_cos(F64(_a)));
}
template <typename T> inline constexpr T Tan(T _a) noexcept {
  return T(__builtin_tan(F64(_a)));
}
template <typename T> inline constexpr T Asin(T _a) noexcept {
  return T(__builtin_asin(F64(_a)));
}
template <typename T> inline constexpr T Acos(T _a) noexcept {
  return T(__builtin_acos(F64(_a)));
}
template <typename T> inline constexpr T Atan(T _a) noexcept {
  return T(__builtin_atan(F64(_a)));
}
template <typename T> inline constexpr T Atan2(T _a, T _b) noexcept {
  return T(__builtin_atan2(F64(_a), F64(_b)));
}
template <typename T> inline T log2(T _x) noexcept {
  return T(__builtin_log2(F64(_x)));
}
template <typename T, U32 N> class Vec {
  T *data[N];

public:
  const U32 Length = N;
  Vec<T, N>() {
    *data = new T[Length];
    for (U32 i = 0; i < Length; i++) {
      data[i] = new T(0);
    }
  }
  Vec<T, N>(T *_rhs) { *data = _rhs; }
  Vec<T, N>(const Vec<T, N> &_rhs) {
    *data = new T[Length];
    for (U32 i = 0; i < Length; i++) {
      data[i] = _rhs.data[i];
    }
  }
  Vec<T, N>(T *_rhs[N]) {
    data = new T[Length];
    for (U32 i = 0; i < Length; i++) {
      data[i] = _rhs[i];
    }
  }
  ~Vec<T, N>() {
    for (U32 i = 0; i < Length; i++) {
      delete data[i];
    }
    delete *data;
  }
  inline T &operator[](U32 index) { return *data[index]; }
  Vec<T, N> &operator=(T *_data) {
    if (_data == nullptr) {
      for (U32 i = 0; i < Length; i++) {
        _data[i] = 0;
      }
      return;
    }
    U32 a_size = (Length * 8) / (sizeof(data[0])) << 3;
    U32 b_size = ((sizeof(data[0]) * 8) / Length) << 3;
    U32 c_size = a_size > b_size ? a_size : b_size;
    for (U32 i = 0; i < Length; i++) {
      if (i < c_size) {
        data[i] = _data[i];
      } else {
        data[i] = 0;
      }
    }
  }
  Vec<T, N> Pow(const Vec<T, N> &_rhs) const {
    Vec ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Pow(ret[i], _rhs[i]);
    }
    return ret;
  }
  Vec<T, N> Lerp(const Vec<T, N> &_rhs, U32 _exp) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Lerp(ret[i], _rhs[i], _exp);
    }
    return ret;
  }
  Vec<T, N> Lerp(const Vec<T, N> &_rhs, const Vec<T, N> &_exp) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Lerp(ret[i], _rhs[i], _exp[i]);
    }
    return ret;
  }
  Vec<T, N> Clamp(const Vec<T, N> &_min, const Vec<T, N> &_max) const {
    Vec ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Clamp(ret[i], _min[i], _max[i]);
    }
    return ret;
  }
  Vec<T, N> Clamp(const T _min, const T _max) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = T(Origin::Clamp(ret[i], _min, _max));
    }
    return ret;
  }
  Vec<T, N> Abs() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Abs(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Sign() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Sign(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Sqrt() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Sqrt(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Sq() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Square(ret[i]);
    }
    return ret;
  }
  Vec<T, N> RSqrt() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = (T)__builtin_sqrt(F64(ret[i]));
    }
    return ret;
  }
  Vec<T, N> Rand(T _min, T _max) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = Origin::Rand(_min, _max);
    }
    return ret;
  }
  bool IsNan(bool set_zero = false) const {
    for (U32 i = 0; i < Length; i++) {
      if (__builtin_isnan(*data[i])) {
        if (set_zero) {
          *data[i] = 0;
        }
        return true;
      }
    }
    return false;
  }
  bool IsNum() const { return !IsNan(); }
  Vec<T, N> operator=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] = _rhs.data[i];
      } else {
        data[i] = new T(0);
      }
    }
    return *this;
  }
  T operator[](I32 i) {
    if (i < Length) {
      return *data[i];
    } else {
      return 0;
    }
  }
  operator Vec<T, N> *() { return *this; }
  Vec<T, N> operator+(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] += _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator-(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] -= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator*(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] *= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator/(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] /= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator%(const T &_rhs) {
    Vec ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] %= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator&(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] &= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator|(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] |= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator^(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] ^= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator<<(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] <<= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator>>(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] >>= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator+=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] += _rhs;
    }
    return *this;
  }
  Vec<T, N> operator-=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] -= _rhs;
    }
    return *this;
  }
  Vec<T, N> operator*=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] *= _rhs;
    }
    return *this;
  }
  Vec<T, N> operator/=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] /= _rhs;
    }
    return this;
  }
  Vec<T, N> operator%=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] %= _rhs;
    }
    return this;
  }
  Vec<T, N> operator&=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] &= _rhs;
    }
    return this;
  }
  Vec<T, N> operator|=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] |= _rhs;
    }
    return this;
  }
  Vec<T, N> operator^=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      data[i] ^= _rhs;
    }
    return this;
  }
  Vec<T, N> operator<<=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      this->data[i] <<= _rhs;
    }
    return this;
  }
  Vec<T, N> operator>>=(const T &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      this->data[i] >>= _rhs;
    }
    return this;
  }
  Vec<T, N> operator-() {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] = -ret[i];
    }
    return ret;
  }
  Vec<T, N> operator++() {
    for (U32 i = 0; i < Length; i++) {
      data[i]++;
    }
    return this;
  }
  Vec<T, N> operator--() {
    for (U32 i = 0; i < Length; i++) {
      data[i]--;
    }
    return this;
  }
  operator T *() { return data; }
  operator Vec<T, N>() { return data; } // Vec<T,N>
  Vec<T, N> operator+=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] += _rhs.data[i];
      }
    }
    return this;
  }
  Vec<T, N> operator-=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] -= _rhs.data[i];
      }
    }
    return this;
  }
  Vec<T, N> operator*=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] *= _rhs.data[i];
      }
    }
    return this;
  }
  Vec<T, N> operator/=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] /= _rhs.data[i];
      }
    }
    return this;
  }
  Vec<T, N> operator%=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] %= _rhs.data[i];
      }
    }
    return this;
  }
  Vec<T, N> operator&=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] &= _rhs.data[i];
      }
    }
    return this;
  }
  Vec<T, N> operator|=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] |= _rhs.data[i];
      }
    }
    return this;
  }
  Vec<T, N> operator^=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] ^= _rhs.data[i];
      }
    }
    return this;
  };
  Vec<T, N> operator<<=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] <<= _rhs.data[i];
      }
    }
    return this;
  };
  Vec<T, N> operator>>=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < Length; i++) {
      if (i < _rhs.Length) {
        data[i] >>= _rhs.data[i];
      }
    }
    return this;
  };
  Vec<T, N> operator+(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] += _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator-(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] -= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator*(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] *= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator/(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] /= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator%(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] %= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator&(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] &= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator|(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] |= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator^(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] ^= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator<<(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < Length; i++) {
      ret[i] <<= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> operator>>(const Vec<T, N> &_rhs) {
    return Vec<T, N>(*this) >>= _rhs;
  }
};
struct Vec2 : Vec<F64, 2> {
  Vec2(F64 _x, F64 _y) { *this = {_x, _y}; }
  Vec2() { *this = {0, 0}; }
};
struct Vec3 : Vec<F64, 3> {
  F64 x, y, z;
  Vec3(F64 _x, F64 _y, F64 _z) { *this = {_x, _y, _z}; }
  Vec3() { *this = {0, 0, 0}; }
};
struct Vec4 : Vec<F64, 4> {
  F64 x = 0, y = 0, z = 0, w = 0;
  Vec4(F64 _x, F64 _y, F64 _z, F64 _w) { *this = {_x, _y, _z, _w}; }
  Vec4() { *this = {0, 0, 0, 0}; }
  void Set(F64 _x, F64 _y, F64 _z, F64 _w, bool reset = false);
  Vec4 Get();
  Vec4 operator=(const Vec4 &_rhs) {
    x = _rhs.x;
    y = _rhs.y;
    z = _rhs.z;
    w = _rhs.w;
    return *this;
  }
  operator F64 *() const { return Vec4(x, y, z, w); }
  operator Vec4 *() const { return new Vec4(x, y, z, w); }
  F64 &operator[](U32 i);
};
typedef Vec<Vec<F64, 3>, 3> Matrix3x3;
typedef Vec<Vec<F64, 4>, 4> Matrix4x4;

typedef U64 ID;
class Color : public Vec4 {
  F64 r, g, b, a;
  Color(const U32 _r, const U32 _g, const U32 _b, const U32 _a) {
    Set(_r, _g, _b, _a, true);
  }
  Color(const F64 _r, const F64 _g, const F64 _b, const F64 _a) {
    Set(_r, _g, _b, _a, true);
    *this = Color(1.0 / _r, 1.0 / _g, 1.0 / _b, 1.0 / _a);
    Normalize<F64, 4>(*this);
  }
  Color() { *this = {0.0, 0.0, 0.0, 0.0}; }
  Color operator=(const Color &_rhs) {
    Set(_rhs.r, _rhs.g, _rhs.b, _rhs.a, true);
    return *this;
  }
};
class Vertex {
  F64 *data[16];
  U32 index;
  U32 *owners;

public:
  Vertex(Vec3 coords, Vec3 normal, Vec4 color) {
    *data = new F64[16]{coords[0], coords[1], coords[2], normal[0],
                        normal[1], normal[2], color[0],  color[1],
                        color[2],  color[3],  0,         0,
                        0,         0,         0,         0};
    index = 0;
    owners = nullptr;
  }
  Vertex(Vec3 coords = {0.0, 0.0, 0.0}, Vec3 normal = {0.0, 0.0, 0.0},
         Vec4 color = {0.0, 0.0, 0.0, 0.0}, U32 index = 0,
         U32 *owners = nullptr) {
    *data = new F64[16]{coords[0], coords[1], coords[2], 1,   1,
                        1,         255,       255,       255, 255};
    index++;
    owners = nullptr;
  }
};
class Triangle {
  Vec3 *data = new Vec3[3]{Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0)};
  U32 index;

public:
  Triangle(const Vec3 &_a, const Vec3 &_b, const Vec3 &_c) {
    data[0] = _a;
    data[1] = _b;
    data[2] = _c;
  }
  Triangle() {
    data = new Vec3[3]{Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0)};
    for (U32 i = 0; i < 3; i++) {
      data[i] = Vec3(0, 0, 0);
    }
  }
  ~Triangle() { delete[] data; }
  Vec3 *Get() { return data; }
  const Vec3 *Get() const { return data; }
  Vec3 &operator[](U32 _i) { return data[_i]; }
  Vec3 operator[](U32 _i) const { return data[_i]; }
};
class Mesh {
  Triangle *data;

public:
  Mesh(Triangle *_data) { data = _data; }
  ~Mesh() { delete[] data; }
  Triangle *Get() { return data; }
  const Triangle *Get() const { return data; }
  void Index() const {
    for (U32 i = 0; i < 3; i++) {
    }
  }
};
} // namespace Origin