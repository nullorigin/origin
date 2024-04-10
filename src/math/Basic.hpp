#pragma once
#include <cstddef>
#include <cstdlib>
#include <xmmintrin.h>
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
typedef long double F128;
typedef I8 V16I128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef U8 V16U128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef S8 V16S128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef I16 V8I128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef U16 V8U128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef S16 V8S128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef F32 V4F128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef I32 V4I128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef U32 V4U128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef S32 V4S128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef F64 V2F128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef I64 V2I128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef U64 V2U128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef S64 V2S128 __attribute__((__vector_size__(16), __aligned__(16)));

typedef I8 V32I256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef U8 V32U256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef S8 V32S256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef I16 V16I256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef U16 V16U256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef S16 V16S256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef F32 V8F256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef I32 V8I256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef U32 V8U256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef S32 V8S256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef F64 V4F256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef I64 V4I256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef U64 V4U256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef S64 V4S256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef F128 V2F256 __attribute__((__vector_size__(32), __aligned__(32)));

#if WORDSIZE == 64
typedef unsigned long SIZE_T;
#else
typedef U64 SIZE_T;
#endif
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
#define F128_C(c) c##d
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

struct Dir {
  typedef enum : U32 {
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
  } Axis;
  typedef enum : U32 {
    Right = 1 << 0,
    Left = 1 << 1,
    Front = 1 << 2,
    Back = 1 << 3,
    Top = 1 << 4,
    Bottom = 1 << 5
  } Face;

  typedef struct {
    F64 x, y, z, w;
  } Quat;

  typedef struct {
    F64 x, y, z;
  } Vec3;
  typedef struct Vec4x4 {
  public:
    F64 q[4][4];
    Vec4x4(F64 x1 = 0, F64 y1 = 0, F64 z1 = 0, F64 w1 = 0, F64 x2 = 0,
           F64 y2 = 0, F64 z2 = 0, F64 w2 = 0, F64 x3 = 0, F64 y3 = 0,
           F64 z3 = 0, F64 w3 = 0, F64 x4 = 0, F64 y4 = 0, F64 z4 = 0,
           F64 w4 = 0) {
      q[0][0] = x1;
      q[1][0] = y1;
      q[2][0] = z1;
      q[3][0] = w1;
      q[0][1] = x2;
      q[1][1] = y2;
      q[2][1] = z2;
      q[3][1] = w2;
      q[0][2] = x3;
      q[1][2] = y3;
      q[2][2] = z3;
      q[3][2] = w3;
      q[0][3] = x4;
      q[1][3] = y4;
      q[2][3] = z4;
      q[3][3] = w4;
    }
    Vec4x4 Mul(Vec4x4 _rhs) {
      Vec4x4 ret = *this;
      for (U32 i = 0; i < 4; i++) {
        for (U32 j = 0; j < 4; j++) {
          ret.q[i][j] = 0;
          for (U32 k = 0; k < 4; k++) {
            ret.q[i][j] += q[i][k] * _rhs.q[k][j];
          }
        }
      }
      return ret;
    }

    Vec3 MulV(Vec3 _rhs) {
      Vec3 ret;
      ret.x = q[0][0] * _rhs.x + q[0][1] * _rhs.y + q[0][2] * _rhs.z + q[0][3];
      ret.y = q[1][0] * _rhs.x + q[1][1] * _rhs.y + q[1][2] * _rhs.z + q[1][3];
      ret.z = q[2][0] * _rhs.x + q[2][1] * _rhs.y + q[2][2] * _rhs.z + q[2][3];
      return ret;
    }

    Vec3 MulVQ(Vec4x4 _rhs) {
      Vec3 ret;
      ret.x = q[0][0] * _rhs.q[0][0] + q[0][1] * _rhs.q[1][0] +
              q[0][2] * _rhs.q[2][0] + q[0][3] * _rhs.q[3][0];
      ret.y = q[1][0] * _rhs.q[0][0] + q[1][1] * _rhs.q[1][0] +
              q[1][2] * _rhs.q[2][0] + q[1][3] * _rhs.q[3][0];
      ret.z = q[2][0] * _rhs.q[0][0] + q[2][1] * _rhs.q[1][0] +
              q[2][2] * _rhs.q[2][0] + q[2][3] * _rhs.q[3][0];
      return ret;
    }
  } Quaternion;

  Quaternion Rotate(Quaternion _q, Vec3 _a, Face _f, F64 _d) {
    Quaternion q;
    switch (_f) {
    case Face::Right:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Left:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Front:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Back:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Top:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Bottom:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    default:
      break;
    }
    q = _q.Mul(q);
    return Transform(q, _a, _d);
  }
  Quaternion Transform(Quaternion _q, Vec3 _v) {
    Quaternion q =
        Quaternion{0, _v.x, _v.y, _v.z, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    return q.Mul(_q);
  }
  Quaternion Transform(Quaternion _q, Vec3 _v, F64 _d) {
    Quaternion q =
        Quaternion{0, _v.x, _v.y, _v.z, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    F64 angle = _d * PI / 180.0; // Convert degrees to radians
    q.Mul(Quaternion{__builtin_sin(angle / 2), _v.x * __builtin_sin(angle / 2),
                     _v.y * __builtin_sin(angle / 2),
                     _v.z * __builtin_sin(angle / 2),
                     __builtin_cos(angle / 2)});
    return q.Mul(_q);
  }
  Quaternion Translate(Quaternion _q, Vec3 _v) {
    Quaternion q =
        Quaternion{0, _v.x, _v.y, _v.z, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    return q.Mul(_q);
  }
  Quaternion Translate(Quaternion _q, Vec3 _v, Face _face) {
    Quaternion q;
    switch (_face) {
    case Face::Right:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Left:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Front:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Back:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Top:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Bottom:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    default:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    }
    q = Translate(q, _v);
    return q.Mul(_q);
  }
};
template <typename T> inline constexpr bool IsNum(const T _a) {
  return !(bool(__builtin_isnan(_a))) && !(bool(__builtin_isinf(_a)));
}
template <typename T> inline constexpr bool IsNan(const T _a) {
  return bool(__builtin_isnan(_a));
}
template <typename T> inline constexpr bool IsInf(const T _a) {
  return bool(__builtin_isinf(_a));
}
template <typename T, U64 N>
inline constexpr T *Cross(const T _a[N], const T _b[N], const T _c[N]) {
  T vec[3][N], dot;
  T ret[N];
  U32 i = 0;
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
  return T(__builtin_floor(F64(_a)));
}
template <typename T> inline constexpr T Ceil(const T _a) {
  return T(__builtin_ceil(F64(_a)));
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
template <typename T> inline T Log(T _a) noexcept {

  return T(__builtin_log(F64(_a)));
}
template <typename T> inline T log2(T _x) noexcept {
  return T(__builtin_log2(F64(_x)));
}
template <typename T> inline T Log10(T _a) noexcept {
  return T(__builtin_log10(F64(_a)));
}

struct Complex {
  F64 real = 0;
  F64 imag = 0;
  Complex() = default;
  Complex(F64 _real, F64 _imag) {
    real = _real;
    imag = _imag;
  }
  static Complex Zero() { return Complex(0, 0); }

  static Complex Add(Complex A, Complex B) {
    Complex out = {A.real + B.real, A.imag + B.imag};
    return out;
  }
  static Complex Mul(Complex A, Complex B) {
    Complex out = {A.real * B.real - A.imag * B.imag,
                   A.real * B.imag + A.imag * B.real};
    return out;
  }
  F64 *Mul(F64 *A, F64 *B) {
    //-------------Basied SIMD testing--------------//
    //  Using SIMD to compute the complex multiplication

    // if A=a+b*j,B=c+d*j; then A * B = (ac -bd) + (bc+ad)*j
    // load a b
    V2F128 n1 = _mm_load_pd(A);
    // load b a
    V2F128 n2 = _mm_loadr_pd(A);
    // load c c
    V2F128 n3 = _mm_load1_pd(B);
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
    F64 *C = new F64[2];
    _mm_store_pd(C, n1);
    return C;
  }
};
void FFT2(Complex *X, int N) {
  // Notes	: the length of fft must be a power of 2,and it is  a in-place
  // algorithm ref		:
  // https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
  if (N < 2) {
    // bottom of recursion.
    // Do nothing here, because already X[0] = x[0]
  } else {
    Complex *Y = new Complex[N / 2]; // get temp heap storage
    for (U32 i = 0; i < N / 2; i++)  // copy all odd elements to heap storage
      Y[i] = X[i * 2 + 1];
    for (U32 i = 0; i < N / 2;
         i++) // copy all even elements to lower-half of a[]
      X[i] = X[i * 2];
    for (U32 i = 0; i < N / 2;
         i++) // copy all odd (from heap) to upper-half of a[]
      X[i + N / 2] = Y[i];
    delete[] Y;             // delete heap storage
    FFT2(X, N / 2);         // recurse even items
    FFT2(X + N / 2, N / 2); // recurse odd  items
    //                             // combine results of two half recursions
    for (U32 k = 0; k < N / 2; k++) {
      V2F128 o = _mm_load_pd((double *)&X[k + N / 2]); // odd
      F64 cc = Cos(-2. * PI * k / N);
      F64 ss = Sin(-2. * PI * k / N);
      V2F128 wr = _mm_load1_pd(
          &cc); //__m128d wr =  _mm_set_pd( cc,cc );		// cc
      V2F128 wi =
          _mm_set_pd(ss, -ss); // -d | d	, note that it is reverse order
      // compute the w*o
      wr = _mm_mul_pd(o, wr);                               // ac|bc
      V2F128 n1 = _mm_shuffle_pd(o, o, _MM_SHUFFLE2(0, 1)); // invert
      wi = _mm_mul_pd(n1, wi);                              // -bd|ad
      n1 = _mm_add_pd(wr, wi);
      o = _mm_load_pd((F64 *)&X[k]); // load even part
      wr = _mm_add_pd(o, n1);        // compute even part, X_e + w * X_o;
      wi = _mm_sub_pd(o, n1);        // compute odd part,  X_e - w * X_o;
      _mm_store_pd((F64 *)&X[k], wr);
      _mm_store_pd((F64 *)&X[k + N / 2], wi);
    }
  }
}
struct Mem {
public:
  U64 size = 0, used = 0, free = 0, total = 0;
  Mem() = default;
  enum class Unit : U8 {
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
  Mem(U64 _size, U64 _used, U64 _free, U64 _total, Unit _unit = Unit::BYTE) {
    size = _size;
    used = _used;
    free = _free;
    total = _total;
    unit = _unit;
  }
  constexpr U64 Convert(Unit _unit) {
    F64 ratio = (1 >> (U64(_unit) * 10)) / (1 >> (U64(unit) * 10));
    return U64(size * ratio);
  }
  Mem Convert(Mem _mem) {
    F64 ratio = (1 >> (U64(_mem.unit) * 10)) / (1 >> (U64(unit) * 10));
    return Mem(U64(size * ratio), U64(used * ratio), U64(free * ratio),
               U64(total * ratio), _mem.unit);
  }
  U64 operator[](Unit _unit) { return Convert(_unit); }
  Mem &operator=(const Mem &_rhs) {
    size = _rhs.size;
    used = _rhs.used;
    free = _rhs.free;
    total = _rhs.total;
    unit = _rhs.unit;
    return *this;
  }
};
} // namespace Origin