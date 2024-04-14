#pragma once
#include "Basic.hpp"
#include <cstring>
namespace origin {
using Axis = enum class Axis : u8 {
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
};
using Face = enum : u32 {
  Right = 1 << 0,
  Left = 1 << 1,
  Forward = 1 << 2,
  Backward = 1 << 3,
  Up = 1 << 4,
  Down = 1 << 5
};

template <typename T, u64 N> class Vec {
public:
  T Data[N];
  constexpr auto Size(Mem::Unit _mu = Mem::Unit::BYTE) -> u64 {
    return u64((N * sizeof(T)) << (u64(_mu) * 10));
  }
  constexpr auto Length() -> u64 { return u64(N); }
  Vec<T, N>() {
    *Data = *new T[N];
    for (u32 i = 0; i < N; i++) {
      Data[i] = *new T();
    }
  }
  auto operator=(const Vec & /*unused*/) -> Vec & { return *this; };
  auto operator=(Vec && /*unused*/) noexcept -> Vec & { return *this; };
  Vec(const Vec & /*unused*/) { memset(Data, 0, sizeof(T) * N); };
  Vec(Vec && /*unused*/) noexcept : Data{} { memset(Data, 0, sizeof(T)); };
  constexpr auto Find(T min, T max, u64 &index) -> T {
    for (u32 i = 0; i < N; i++) {
      if (Data[i] >= min && Data[i] <= max) {
        index = i;
        return Data[i];
      }
    }
    return T(0);
  }
  constexpr auto Find(T min, T max) -> Vec<T, N> {
    Vec<T, N> ret;
    for (u32 i = 0; i < N; i++) {
      if (Data[i] >= min && Data[i] <= max) {
        ret[i] = Data[i];
      }
    }
    return ret;
  }
  constexpr auto Find(T value, void (*callback)(T)) -> Vec<T, N> {
    Vec<T, N> ret;
    for (u32 i = 0; i < N; i++) {
      if (Data[i] == value) {
        ret[i] = Data[i];
        callback(Data[i]);
      }
    }
    return ret;
  }
  constexpr auto Replace(T min, T max, T value) -> Vec<T, N> {
    T ret = T(0);
    for (u32 i = 0; i < N; i++) {
      if (Data[i] >= min && Data[i] <= max) {
        ret[i] = value;
      } else {
        ret[i] = Data[i];
      }
    }
    return ret;
  }
  constexpr auto Index(Vec<T, N> value) -> Vec<u64, N> {
    Vec<u64, N> ret = Vec<u64, N>();
    for (u32 i = 0; i < N; i++) {
      if (Data[i] == value[i]) {
        ret[i] = i;
      }
    }
    return ret;
  }
  constexpr auto Index(Vec<T, N> /*value*/, T min, T max) -> Vec<u64, N> {
    Vec<u64, N> ret = Vec<u64, N>();
    for (u64 i = 0; i < N; i++) {
      if (Data[i] >= min && Data[i] <= max) {
        ret[i] = i;
      }
    }
    return ret;
  }
  auto Index(T value, T threshold) -> Vec<u64, N> {
    Vec<u64, N> ret = Vec<u64, N>();
    for (u32 i = 0; i < N; i++) {
      if (Data[i] >= value - threshold && Data[i] <= value + threshold) {
        ret[i] = i;
      }
    }
    return ret;
  }
  explicit Vec<T, N>(T *_rhs) {
    memset(Data, 0, sizeof(T) * N);
    *Data = *_rhs;
  }
  explicit Vec<T, N>(const Vec<T, N> *_rhs) : Data(new T[N]()) { *Data = _rhs; }
  explicit Vec<T, N>(const T *_rhs) : Data(new T[N]) { *Data = _rhs; }
  explicit Vec<T, N>(T *_rhs[N]) : Data(new T[N]) { *Data = _rhs; }
  ~Vec<T, N>() { delete[] &Data; }
  auto Set(T _rhs) -> Vec<T, N> {
    for (u32 i = 0; i < N; i++) {
      Data[i] = _rhs;
    }
    return *this;
  }
  auto Set(T *_rhs) -> Vec<T, N> {
    *Data = _rhs;
    return *this;
  }
  auto Set(const Vec<T, N> &_rhs) -> Vec<T, N> {
    for (u32 i = 0; i < N; i++) {
      Data[i] = _rhs[i];
    }
    return *this;
  }
  auto Set(T *_rhs[N]) -> Vec<T, N> {
    Data = _rhs;
    return *this;
  }
  auto Get() -> Vec<T, N> { return Data; }
  auto Get(u32 _index) -> Vec<T, N> { return Data[_index]; }
  auto Add(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] += _rhs[i];
    }
    return ret;
  }
  auto Sub(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] -= _rhs[i];
    }
    return ret;
  }
  auto Mul(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] *= _rhs[i];
    }
    return ret;
  }
  auto Div(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] /= _rhs[i];
    }
    return ret;
  }
  auto Mod(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] %= _rhs[i];
    }
    return ret;
  }
  auto And(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] &= _rhs[i];
    }
    return ret;
  }
  auto Or(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] |= _rhs[i];
    }
    return ret;
  }
  auto Xor(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] | &_rhs[i];
    }
    return ret;
  }
  auto Neg() -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = (-ret[i]);
    }
    return ret;
  }
  auto Pow(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] ^= _rhs[i];
    }
    return ret;
  }
  auto Swap(Vec<T, N> &_rhs) -> Vec<T, N> {
    for (u32 i = 0; i < N; i++) {
      T tmp = Data[i];
      Data[i] = _rhs[i];
      _rhs[i] = tmp;
    }
    return *this;
  }
  auto Cross(const Vec<T, N> &_rhs, const Vec<T, N> &_rhs2) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Cross(Data[i], _rhs[i], _rhs2[i]);
    }
    return ret;
  }
  auto Abs() -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Abs(ret[i]);
    }
    return ret;
  }
  auto Sqrt() -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Sqrt(ret[i]);
    }
    return ret;
  }
  auto Lerp(const Vec<T, N> &_rhs, const Vec<T, N> &_exp) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Lerp(Data[i], _rhs[i], _exp[i]);
    }
    return ret;
  }
  Vec<bool, N> Eq(const Vec<T, N> &_rhs) {
    Vec<bool, N> ret;
    for (u32 i = 0; i < N; i++) {
      ret[i] = (Data[i] == _rhs[i]);
    }
    return ret;
  }
  auto Neq(const Vec<T, N> &_rhs) -> Vec<bool, N> {
    Vec<bool, N> ret;
    for (u32 i = 0; i < N; i++) {
      ret = Data[i] != _rhs[i];
    }
    return ret;
  }
  auto Gt(const Vec<T, N> &_rhs) -> Vec<bool, N> {
    Vec<bool, N> ret;
    for (u32 i = 0; i < N; i++) {
      ret[i] = (Data[i] > _rhs[i]);
    }
    return ret;
  }
  auto Gte(const Vec<T, N> &_rhs) -> Vec<bool, N> {
    Vec<bool, N> ret;
    for (u32 i = 0; i < N; i++) {
      ret[i] = (Data[i] >= _rhs[i]);
    }
    return ret;
  }
  auto Lt(const Vec<T, N> &_rhs) -> Vec<bool, N> {
    Vec<bool, N> ret;
    for (u32 i = 0; i < N; i++) {
      ret[i] = (Data[i] < _rhs[i]);
    }
    return ret;
  }
  auto Lte(const Vec<T, N> &_rhs) -> Vec<bool, N> {
    Vec<bool, N> ret;
    for (u32 i = 0; i < N; i++) {
      ret[i] = (Data[i] <= _rhs[i]);
    }
    return ret;
  }

  auto Max(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Max(Data[i], _rhs[i]);
    }
    return ret;
  }
  auto Min(const Vec<T, N> &_rhs) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Min(Data[i], _rhs[i]);
    }
    return ret;
  }
  auto Clamp(const Vec<T, N> &_min, const Vec<T, N> &_max) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Clamp(Data[i], _min[i], _max[i]);
    }
    return ret;
  }
  auto Rand(T _min, T _max) -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u64 i = 0; i < N; i++) {
      ret[i] = origin::Rand(_min, _max);
    }
    return ret;
  }
  inline auto operator[](u64 index) const -> T & { return *Data[index]; }
  auto operator=(T *_data) -> Vec<T, N> & {
    if (_data == nullptr) {
      for (u32 i = 0; i < N; i++) {
        _data[i] = 0;
      }
      return *this;
    }
    u32 a_size = (N * 8) / (sizeof(Data[0])) / 8;
    u32 b_size = ((sizeof(Data[0]) * 8) / N) / 8;
    u32 c_size = a_size > b_size ? a_size : b_size;
    for (u32 i = 0; i < c_size; i++) {
      if (i < c_size) {
        Data[i] = _data[i];
      } else {
        Data[i] = 0;
      }
    }
  }
  auto ShiftL(const Vec<T, N> &_rhs) const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] <<= _rhs[i];
    }
    return ret;
  }
  auto ShiftR(const Vec<T, N> &_rhs) const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] >>= _rhs[i];
    }
    return ret;
  }
  auto Pow(const Vec<T, N> &_rhs) const -> Vec<T, N> {
    Vec ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Pow(ret[i], _rhs[i]);
    }
    return ret;
  }
  auto Lerp(const Vec<T, N> &_rhs, u32 _exp) const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Lerp(ret[i], _rhs[i], _exp);
    }
    return ret;
  }
  auto Lerp(const Vec<T, N> &_rhs, const Vec<T, N> &_exp) const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Lerp(ret[i], _rhs[i], _exp[i]);
    }
    return ret;
  }
  auto Clamp(const Vec<T, N> &_min, const Vec<T, N> &_max) const -> Vec<T, N> {
    Vec ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Clamp(ret[i], _min[i], _max[i]);
    }
    return ret;
  }
  auto Clamp(const T _min, const T _max) const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = T(origin::Clamp(ret[i], _min, _max));
    }
    return ret;
  }
  auto Abs() const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Abs(ret[i]);
    }
    return ret;
  }
  auto Sign() const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Sign(ret[i]);
    }
    return ret;
  }
  auto Sqrt() const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Sqrt(ret[i]);
    }
    return ret;
  }
  auto Sq() const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Square(ret[i]);
    }
    return ret;
  }
  auto RSqrt() const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = (T)__builtin_sqrt(f64(ret[i]));
    }
    return ret;
  }
  auto Rand(T _min, T _max) const -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = origin::Rand(_min, _max);
    }
    return ret;
  }
  auto IsNan(bool set_zero = false) const -> bool {
    for (u32 i = 0; i < N; i++) {
      if (__builtin_isnan(*Data[i])) {
        if (set_zero) {
          *Data[i] = 0;
        }
        return true;
      }
    }
    return false;
  }
  auto IsNum() const -> bool { return !IsNan(); }
  auto operator=(const Vec<T, N> *_rhs) -> Vec<T, N> {
    for (u32 i = 0; i < N; i++) {
      &Data[i] = _rhs[i];
    }
    return &this;
  }
  auto operator[](u32 i) const -> T {
    if (i < N) {
      return Data[i];
    }
    return 0;
  }
  explicit operator Vec<T, N> *() { return *this; }
  auto operator+(const T &_rhs) -> Vec<T, N> { return Add(_rhs); }
  auto operator-(const T &_rhs) -> Vec<T, N> { return Sub(_rhs); }
  auto operator*(const T &_rhs) -> Vec<T, N> { return Mul(_rhs); }
  auto operator/(const T &_rhs) -> Vec<T, N> { return Div(_rhs); }
  auto operator%(const T &_rhs) -> Vec<T, N> { return Mod(_rhs); }
  auto operator&(const T &_rhs) -> Vec<T, N> { return And(_rhs); }
  auto operator|(const T &_rhs) -> Vec<T, N> { return Or(_rhs); }
  auto operator^(const T &_rhs) -> Vec<T, N> { return Pow(_rhs); }
  auto operator<<(const T &_rhs) -> Vec<T, N> { return ShiftL(_rhs); }
  auto operator>>(const T &_rhs) -> Vec<T, N> { return ShiftR(_rhs); }
  auto operator==(const T &_rhs) -> Vec<bool, N> { return Eq(_rhs); }
  auto operator!=(const T &_rhs) -> Vec<bool, N> { return Neq(_rhs); }
  auto operator<(const T &_rhs) -> Vec<bool, N> { return Lt(_rhs); }
  auto operator<=(const T &_rhs) -> Vec<bool, N> { return Lte(_rhs); }
  auto operator>(const T &_rhs) -> Vec<bool, N> { return Gt(_rhs); }
  auto operator>=(const T &_rhs) -> Vec<bool, N> { return Gte(_rhs); }
  auto operator-() -> Vec<T, N> { return Neg(); }
  auto operator~() -> Vec<T, N> {
    Vec<T, N> ret = *this;
    for (u32 i = 0; i < N; i++) {
      ret[i] = ~ret[i];
    }
    return ret;
  }
  auto operator+=(const T &_rhs) -> Vec<T, N> {
    *this = Add(_rhs);
    return *this;
  }
  auto operator-=(const T &_rhs) -> Vec<T, N> {
    *this = Sub(_rhs);
    return *this;
  }
  auto operator*=(const T &_rhs) -> Vec<T, N> {
    *this = Mul(_rhs);
    return *this;
  }
  auto operator/=(const T &_rhs) -> Vec<T, N> {
    *this = Div(_rhs);
    return *this;
  }
  auto operator%=(const T &_rhs) -> Vec<T, N> {
    *this = Mod(_rhs);
    return *this;
  }
  auto operator&=(const T &_rhs) -> Vec<T, N> {
    *this = And(_rhs);
    return *this;
  }
  auto operator|=(const T &_rhs) -> Vec<T, N> {
    *this = Or(_rhs);
    return *this;
  }
  auto operator^=(const T &_rhs) -> Vec<T, N> {
    *this = Pow(_rhs);
    return *this;
  }
  auto operator<<=(const T &_rhs) -> Vec<T, N> {
    *this = ShiftL(_rhs);
    return *this;
  }
  auto operator>>=(const T &_rhs) -> Vec<T, N> {
    *this = ShiftR(_rhs);
    return *this;
  }
  auto operator++() -> Vec<T, N> {
    *this = Add(1);
    return *this;
  }
  auto operator--() -> Vec<T, N> {
    *this = Sub(1);
    return *this;
  }
  explicit operator T *() { return *Data; }
  explicit operator Vec<T, N>() { return *Data; } // Vec<T,N>

  auto operator+(const Vec<T, N> &_rhs) -> Vec<T, N> { return Add(_rhs); }
  auto operator-(const Vec<T, N> &_rhs) -> Vec<T, N> { return Sub(_rhs); }
  auto operator*(const Vec<T, N> &_rhs) -> Vec<T, N> { return Mul(_rhs); }
  auto operator/(const Vec<T, N> &_rhs) -> Vec<T, N> { return Div(_rhs); }
  auto operator%(const Vec<T, N> &_rhs) -> Vec<T, N> { return Mod(_rhs); }
  auto operator&(const Vec<T, N> &_rhs) -> Vec<T, N> { return And(_rhs); }
  auto operator|(const Vec<T, N> &_rhs) -> Vec<T, N> { return Or(_rhs); }
  auto operator^(const Vec<T, N> &_rhs) -> Vec<T, N> { return Pow(_rhs); }
  auto operator<<(const Vec<T, N> &_rhs) -> Vec<T, N> { return ShiftL(_rhs); }
  auto operator>>(const Vec<T, N> &_rhs) -> Vec<T, N> { return ShiftR(_rhs); }
  auto operator+=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = Add(_rhs);
    return *this;
  }
  auto operator-=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = Sub(_rhs);
    return *this;
  }
  auto operator*=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = Mul(_rhs);
    return *this;
  }
  auto operator/=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = Div(_rhs);
    return *this;
  }
  auto operator%=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = Mod(_rhs);
    return *this;
  }
  auto operator&=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = And(_rhs);
    return *this;
  }
  auto operator|=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = Or(_rhs);
    return *this;
  }
  auto operator^=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = Pow(_rhs);
    return *this;
  };
  auto operator<<=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = ShiftL(_rhs);
    return *this;
  };
  auto operator>>=(const Vec<T, N> &_rhs) -> Vec<T, N> {
    *this = ShiftR(_rhs);
    return *this;
  };
  auto operator[](u32 _i) -> T & { return Data[_i]; }
};
class Vec2 : public Vec<f64, 2> {
public:
  union {
    f64 *Data = new f64[2];
    struct {
      f64 x;
      f64 y;
    };
  };
  explicit Vec2(Vec<f64, 2> &_rhs) { Data = _rhs.Data; };
  explicit Vec2(Vec<f64, 2> const &_rhs) { *Data = *_rhs.Data; }
  explicit Vec2(f64 _x = 0, f64 _y = 0) {
    x = _x;
    y = _y;
  }
};
class Vec3 : public Vec<f64, 3> {
public:
  union {
    f64 *Data = new f64[3];
    struct {
      f64 x;
      f64 y;
      f64 z;
    };
  };
  explicit Vec3(Vec<f64, 3> &_rhs) { Data = _rhs.Data; }
  explicit Vec3(Vec<f64, 3> const &_rhs) { *Data = *_rhs.Data; }
  explicit Vec3(f64 _x = 0, f64 _y = 0, f64 _z = 0) {
    x = _x;
    y = _y;
    z = _z;
  }
};
class Vec4 : public Vec<f64, 4> {
public:
  union {
    f64 *Data = new f64[4];
    struct {
      f64 x;
      f64 y;
      f64 z;
      f64 w;
    };
  };
  explicit Vec4(Vec<f64, 4> &_rhs) { Data = _rhs.Data; }
  explicit Vec4(Vec<f64, 4> const &_rhs) { *Data = *_rhs.Data; }
  explicit Vec4(f64 _x = 0, f64 _y = 0, f64 _z = 0, f64 _w = 0) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
  }
};
class Vec16 : public Vec<f64, 16> {
public:
  union {
    f64 *Data = new f64[16];
    struct {
      f64 x[4];
      f64 y[4];
      f64 z[4];
      f64 w[4];
    };
  };
  Vec16() = default;
  explicit Vec16(Vec<f64, 16> &_rhs) : Vec<f64, 16>(x) { Data = _rhs.Data; }
  explicit Vec16(Vec<f64, 16> const &_rhs) { *Data = *_rhs.Data; }
  explicit Vec16(f64 _x[4], f64 _y[4], f64 _z[4], f64 _w[4]) {
    *x = *_x;
    *y = *_y;
    *z = *_z;
    *w = *_w;
  }
};
class Quaternion : public Vec16 {
public:
  explicit Quaternion(Vec<f64, 4> &_rhs)
      : Vec16(&_rhs[0], &_rhs[1], &_rhs[2], &_rhs[3]) {
    Data[0] = _rhs.Data[0];
    Data[1] = _rhs.Data[1];
    Data[2] = _rhs.Data[2];
    Data[3] = _rhs.Data[3];
  }
  explicit Quaternion(Vec<f64, 4> const &_rhs) { *Data = *_rhs.Data; };
  f64 q[4][4]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  explicit Quaternion(f64 x1 = 0, f64 y1 = 0, f64 z1 = 0, f64 w1 = 0,
                      f64 x2 = 0, f64 y2 = 0, f64 z2 = 0, f64 w2 = 0,
                      f64 x3 = 0, f64 y3 = 0, f64 z3 = 0, f64 w3 = 0,
                      f64 x4 = 0, f64 y4 = 0, f64 z4 = 0, f64 w4 = 0) {
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
  Quaternion(const Quaternion &) = default;
  Quaternion(Quaternion && /*unused*/) noexcept {
    *this = Quaternion(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  };
  auto operator=(Quaternion &&) noexcept -> Quaternion & { return *this; }
  explicit Quaternion(const Vec4 _q[4]) {
    *this = Quaternion(_q[0].x, _q[0].y, _q[0].z, _q[0].w, _q[1].x, _q[1].y,
                       _q[1].z, _q[1].w, _q[2].x, _q[2].y, _q[2].z, _q[2].w,
                       _q[3].x, _q[3].y, _q[3].z, _q[3].w);
  };
  auto Mul(Quaternion &_rhs) -> Quaternion {
    Quaternion ret = *this;
    for (u32 i = 0; i < 4; i++) {
      for (u32 j = 0; j < 4; j++) {
        ret.q[i][j] = 0;
        for (u32 k = 0; k < 4; k++) {
          ret.q[i][j] += q[i][k] * _rhs.q[k][j];
        }
      }
    }
    return Quaternion{ret};
  }

  auto MulV(const Vec3 &_rhs) -> Vec3 {
    Vec3 ret;
    ret.x = q[0][0] * _rhs.x + q[0][1] * _rhs.y + q[0][2] * _rhs.z + q[0][3];
    ret.y = q[1][0] * _rhs.x + q[1][1] * _rhs.y + q[1][2] * _rhs.z + q[1][3];
    ret.z = q[2][0] * _rhs.x + q[2][1] * _rhs.y + q[2][2] * _rhs.z + q[2][3];
    return ret;
  }

  auto MulVQ(const Quaternion &_rhs) -> Vec3 {
    Vec3 ret;
    ret.x = q[0][0] * _rhs.q[0][0] + q[0][1] * _rhs.q[1][0] +
            q[0][2] * _rhs.q[2][0] + q[0][3] * _rhs.q[3][0];
    ret.y = q[1][0] * _rhs.q[0][0] + q[1][1] * _rhs.q[1][0] +
            q[1][2] * _rhs.q[2][0] + q[1][3] * _rhs.q[3][0];
    ret.z = q[2][0] * _rhs.q[0][0] + q[2][1] * _rhs.q[1][0] +
            q[2][2] * _rhs.q[2][0] + q[2][3] * _rhs.q[3][0];
    return ret;
  }

  static auto Rotate(Quaternion _q, const Vec3 &_a, Face _f, f64 _d)
      -> Quaternion {
    Quaternion q;
    switch (_f) {
    case Face::Right:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Left:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Forward:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Backward:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Up:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Down:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    default:
      break;
    }
    q = _q.Mul(q);
    return Transform(q, _a, _d);
  }
  static auto Transform(Quaternion _q, const Vec3 &_v) -> Quaternion {
    Quaternion q =
        Quaternion{0, _v.x, _v.y, _v.z, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    return q.Mul(_q);
  }
  static auto Transform(Quaternion &_q, const Vec3 &_v, f64 _d) -> Quaternion {
    Quaternion q0 =
        Quaternion(0, _v.x, _v.y, _v.z, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
    f64 angle = _d * PI / 180.0; // Convert degrees to radians
    Quaternion q1 = Quaternion(
        Quaternion(__builtin_sin(angle / 2), _v.x * __builtin_sin(angle / 2),
                   _v.y * __builtin_sin(angle / 2),
                   _v.z * __builtin_sin(angle / 2), __builtin_cos(angle / 2)));
    return Quaternion(q0.Mul(q1).Mul(_q));
  }
  static auto Translate(Quaternion _q, const Vec3 &_v) -> Quaternion {
    Quaternion q =
        Quaternion{0, _v.x, _v.y, _v.z, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    return q.Mul(_q);
  }
  static auto Translate(Quaternion _q, const Vec3 &_v, Face _face)
      -> Quaternion {
    Quaternion q;
    switch (_face) {
    case Face::Right:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Left:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Forward:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Backward:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Up:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    case Face::Down:
      q = Quaternion{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    default:
      q = Quaternion{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
      break;
    }
    q = Translate(q, _v);
    return q.Mul(_q);
  }
  auto operator=(const Quaternion &_rhs) -> Quaternion {
    for (u32 i = 0; i < 4; i++) {
      for (u32 j = 0; j < 4; j++) {
        q[i][j] = _rhs.q[i][j];
      }
    }
    return *this;
  }
  auto operator*(Quaternion &_rhs) -> Quaternion { return Mul(_rhs); }

  explicit operator f64 *() {
    f64 ret[16] = {q[0][0], q[0][1], q[0][2], q[0][3], q[1][0], q[1][1],
                   q[1][2], q[1][3], q[2][0], q[2][1], q[2][2], q[2][3],
                   q[3][0], q[3][1], q[3][2], q[3][3]};
    return (f64 *)ret;
  }
};
} // namespace origin