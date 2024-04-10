#pragma once
#include "Basic.hpp"
namespace Origin {

template <typename T, U64 N> class Vec {
private:
  T *data[N];

public:
  constexpr U64 const Size(Mem::Unit _mu = Mem::Unit::BYTE) {
    return U64((N * sizeof(T)) << (U64(_mu) * 10));
  }
  constexpr U64 const Length() { return U64(N); }
  Vec<T, N>() {
    *data = new T[N];
    for (U32 i = 0; i < N; i++) {
      data[i] = new T(0);
    }
  }
  Vec<T, N>(T *_rhs) { *data = _rhs; }
  Vec<T, N>(const Vec<T, N> *_rhs) {
    data = new T[N]();
    for (U32 i = 0; i < N; i++) {
      data[i] = _rhs[i];
    }
  }
  Vec<T, N>(T *_rhs[N]) {
    data = new T[N];
    for (U32 i = 0; i < N; i++) {
      data[i] = _rhs[i];
    }
  }
  ~Vec<T, N>() {
    for (U32 i = 0; i < N; i++) {
      delete data[i];
    }
    delete *data;
  }
  Vec<T, N> Set(T _rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] = _rhs;
    }
    return *this;
  }
  Vec<T, N> Set(T *_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] = _rhs[i];
    }
    return *this;
  }
  Vec<T, N> Set(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] = _rhs[i];
    }
    return *this;
  }
  Vec<T, N> Set(T *_rhs[N]) {
    for (U32 i = 0; i < N; i++) {
      data[i] = _rhs[i];
    }
    return *this;
  }
  Vec<T, N> Get() { return data; }
  Vec<T, N> Get(U32 _index) { return data[_index]; }
  Vec<T, N> Add(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] += _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Sub(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] -= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Mul(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] *= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Div(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] /= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Mod(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] %= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> And(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] &= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Or(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] |= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Xor(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] ^= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Neg() {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = (-ret[i]);
    }
    return ret;
  }
  Vec<T, N> Pow(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] ^= _rhs[i];
    }
    return ret;
  }
  Vec<T, N> Swap(Vec<T, N> &_rhs) {
    for (U32 i = 0; i < N; i++) {
      T tmp = data[i];
      data[i] = _rhs[i];
      _rhs[i] = tmp;
    }
    return *this;
  }
  Vec<T, N> Cross(const Vec<T, N> &_rhs, const Vec<T, N> &_rhs2) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Cross(data[i], _rhs[i], _rhs2[i]);
    }
    return ret;
  }
  Vec<T, N> Abs() {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Abs(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Sqrt() {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Sqrt(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Lerp(const Vec<T, N> &_rhs, const Vec<T, N> &_exp) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Lerp(data[i], _rhs[i], _exp[i]);
    }
    return ret;
  }
  Vec<bool, N> Eq(const Vec<T, N> &_rhs) {
    Vec<bool, N> ret;
    for (U32 i = 0; i < N; i++) {
      ret[i] = (data[i] == _rhs[i]);
    }
    return ret;
  }
  Vec<bool, N> Neq(const Vec<T, N> &_rhs) {
    Vec<bool, N> ret;
    for (U32 i = 0; i < N; i++) {
      ret = data[i] != _rhs[i];
    }
    return ret;
  }
  Vec<bool, N> Gt(const Vec<T, N> &_rhs) {
    Vec<bool, N> ret;
    for (U32 i = 0; i < N; i++) {
      ret[i] = (data[i] > _rhs[i]);
    }
    return ret;
  }
  Vec<bool, N> Gte(const Vec<T, N> &_rhs) {
    Vec<bool, N> ret;
    for (U32 i = 0; i < N; i++) {
      ret[i] = (data[i] >= _rhs[i]);
    }
    return ret;
  }
  Vec<bool, N> Lt(const Vec<T, N> &_rhs) {
    Vec<bool, N> ret;
    for (U32 i = 0; i < N; i++) {
      ret[i] = (data[i] < _rhs[i]);
    }
    return ret;
  }
  Vec<bool, N> Lte(const Vec<T, N> &_rhs) {
    Vec<bool, N> ret;
    for (U32 i = 0; i < N; i++) {
      ret[i] = (data[i] <= _rhs[i]);
    }
    return ret;
  }

  Vec<T, N> Max(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Max(data[i], _rhs[i]);
    }
    return ret;
  }
  Vec<T, N> Min(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Min(data[i], _rhs[i]);
    }
    return ret;
  }
  Vec<T, N> Clamp(const Vec<T, N> &_min, const Vec<T, N> &_max) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Clamp(data[i], _min[i], _max[i]);
    }
    return ret;
  }
  Vec<T, N> Rand(T _min, T _max) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = Origin::Rand(_min, _max);
    }
    return ret;
  }
  inline T &operator[](U32 index) { return *data[index]; }
  Vec<T, N> &operator=(T *_data) {
    if (_data == nullptr) {
      for (U32 i = 0; i < N; i++) {
        _data[i] = 0;
      }
      return *this;
    }
    U32 a_size = (N * 8) / (sizeof(data[0])) / 8;
    U32 b_size = ((sizeof(data[0]) * 8) / N) / 8;
    U32 c_size = a_size > b_size ? a_size : b_size;
    for (U32 i = 0; i < c_size; i++) {
      if (i < c_size) {
        data[i] = _data[i];
      } else {
        data[i] = 0;
      }
    }
  }
  Vec<T, N> Pow(const Vec<T, N> &_rhs) const {
    Vec ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Pow(ret[i], _rhs[i]);
    }
    return ret;
  }
  Vec<T, N> Lerp(const Vec<T, N> &_rhs, U32 _exp) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Lerp(ret[i], _rhs[i], _exp);
    }
    return ret;
  }
  Vec<T, N> Lerp(const Vec<T, N> &_rhs, const Vec<T, N> &_exp) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Lerp(ret[i], _rhs[i], _exp[i]);
    }
    return ret;
  }
  Vec<T, N> Clamp(const Vec<T, N> &_min, const Vec<T, N> &_max) const {
    Vec ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Clamp(ret[i], _min[i], _max[i]);
    }
    return ret;
  }
  Vec<T, N> Clamp(const T _min, const T _max) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = T(Origin::Clamp(ret[i], _min, _max));
    }
    return ret;
  }
  Vec<T, N> Abs() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i].data = Origin::Abs(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Sign() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Sign(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Sqrt() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Sqrt(ret[i]);
    }
    return ret;
  }
  Vec<T, N> Sq() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Square(ret[i]);
    }
    return ret;
  }
  Vec<T, N> RSqrt() const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = (T)__builtin_sqrt(F64(ret[i]));
    }
    return ret;
  }
  Vec<T, N> Rand(T _min, T _max) const {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret.data[i] = Origin::Rand(_min, _max);
    }
    return ret;
  }
  bool IsNan(bool set_zero = false) const {
    for (U32 i = 0; i < N; i++) {
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
    for (U32 i = 0; i < N; i++) {
      data[i] = _rhs[i];
    }
    return *this;
  }
  T operator[](I32 i) {
    if (i < N) {
      return *data[i];
    } else {
      return 0;
    }
  }
  operator Vec<T, N> *() { return *this; }
  Vec<T, N> operator+(const T &_rhs) { return Add(_rhs); }
  Vec<T, N> operator-(const T &_rhs) { return Sub(_rhs); }
  Vec<T, N> operator*(const T &_rhs) { return Mul(_rhs); }
  Vec<T, N> operator/(const T &_rhs) { return Div(_rhs); }
  Vec<T, N> operator%(const T &_rhs) { return Mod(_rhs); }
  Vec<T, N> operator&(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] &= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator|(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] |= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator^(const T &_rhs) { return Pow(_rhs); }
  Vec<T, N> operator<<(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] <<= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator>>(const T &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] >>= _rhs;
    }
    return ret;
  }
  Vec<T, N> operator+=(const T &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] += _rhs;
    }
    return *this;
  }
  Vec<T, N> operator-=(const T &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] -= _rhs;
    }
    return *this;
  }
  Vec<T, N> operator*=(const T &_rhs) {
    *this = Mul(_rhs);
    return *this;
  }
  Vec<T, N> operator/=(const T &_rhs) {
    *this = Div(_rhs);
    return *this;
  }
  Vec<T, N> operator%=(const T &_rhs) {
    *this = Mod(_rhs);
    return *this;
  }
  Vec<T, N> operator&=(const T &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] &= _rhs;
    }
    return *this;
  }
  Vec<T, N> operator|=(const T &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] |= _rhs;
    }
    return *this;
  }
  Vec<T, N> operator^=(const T &_rhs) {
    *this = Pow(_rhs);
    return *this;
  }
  Vec<T, N> operator<<=(const T &_rhs) {
    for (U32 i = 0; i < N; i++) {
      this->data[i] <<= _rhs;
    }
    return *this;
  }
  Vec<T, N> operator>>=(const T &_rhs) {
    for (U32 i = 0; i < N; i++) {
      this->data[i] >>= _rhs;
    }
    return *this;
  }
  Vec<T, N> operator-() {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] = -ret[i];
    }
    return ret;
  }
  Vec<T, N> operator++() {
    for (U32 i = 0; i < N; i++) {
      data[i]++;
    }
    return *this;
  }
  Vec<T, N> operator--() {
    for (U32 i = 0; i < N; i++) {
      data[i]--;
    }
    return *this;
  }
  operator T *() { return data; }
  operator Vec<T, N>() { return data; } // Vec<T,N>

  Vec<T, N> operator+(const Vec<T, N> &_rhs) { return Add(_rhs); }
  Vec<T, N> operator-(const Vec<T, N> &_rhs) { return Sub(_rhs); }
  Vec<T, N> operator*(const Vec<T, N> &_rhs) { return Mul(_rhs); }
  Vec<T, N> operator/(const Vec<T, N> &_rhs) { return Div(_rhs); }
  Vec<T, N> operator%(const Vec<T, N> &_rhs) { return Mod(_rhs); }
  Vec<T, N> operator&(const Vec<T, N> &_rhs) { return And(_rhs); }
  Vec<T, N> operator|(const Vec<T, N> &_rhs) { return Or(_rhs); }
  Vec<T, N> operator^(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] ^= _rhs[i];
    }
    return *ret;
  }
  Vec<T, N> operator<<(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] <<= _rhs[i];
    }
    return *ret;
  }
  Vec<T, N> operator>>(const Vec<T, N> &_rhs) {
    Vec<T, N> ret = *this;
    for (U32 i = 0; i < N; i++) {
      ret[i] >>= _rhs[i];
    }
    return *ret;
  }
  Vec<T, N> operator+=(const Vec<T, N> &_rhs) {
    *this = Add(_rhs);
    return *this;
  }
  Vec<T, N> operator-=(const Vec<T, N> &_rhs) {
    *this = Sub(_rhs);
    return *this;
  }
  Vec<T, N> operator*=(const Vec<T, N> &_rhs) {
    *this = Mul(_rhs);
    return *this;
  }
  Vec<T, N> operator/=(const Vec<T, N> &_rhs) {
    *this = Div(_rhs);
    return *this;
  }
  Vec<T, N> operator%=(const Vec<T, N> &_rhs) {
    *this = Mod(_rhs);
    return *this;
  }
  Vec<T, N> operator&=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] &= _rhs[i];
    }
    return *this;
  }
  Vec<T, N> operator|=(const Vec<T, N> &_rhs) {
    *this = Or(_rhs);
    return *this;
  }
  Vec<T, N> operator^=(const Vec<T, N> &_rhs) {
    *this = Pow(_rhs);
    return *this;
  };
  Vec<T, N> operator<<=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] <<= _rhs.data[i];
    }
    return *this;
  };
  Vec<T, N> operator>>=(const Vec<T, N> &_rhs) {
    for (U32 i = 0; i < N; i++) {
      data[i] >>= _rhs[i];
    }
    return *this;
  };
};
class Vec2 : public Vec<F64, 2> {
public:
  F64 x, y;
  Vec2(F64 _x, F64 _y) { *this = {_x, _y}; }
  Vec2() { *this = {0, 0}; }
  Vec2 operator=(const Vec2 &_rhs) {
    x = _rhs.x;
    y = _rhs.y;
    *this = {_rhs.x, _rhs.y};
    return *this;
  }
  Vec2 operator+(const Vec2 &_rhs) {
    Vec2 ret = *this;
    ret += _rhs;
    return ret;
  }
  Vec2 operator-(const Vec2 &_rhs) {
    Vec2 ret = *this;
    ret -= _rhs;
    return ret;
  }
  Vec2 operator*(const Vec2 &_rhs) {
    Vec2 ret = *this;
    ret *= _rhs;
    return ret;
  }
  Vec2 operator/(const Vec2 &_rhs) {
    Vec2 ret = *this;
    ret /= _rhs;
    return ret;
  }
  Vec2 operator%(const Vec2 &_rhs) {
    *this %= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator&(const Vec2 &_rhs) {
    *this &= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator|(const Vec2 &_rhs) {
    *this |= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator^(const Vec2 &_rhs) {
    *this ^= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator<<(const Vec2 &_rhs) {
    *this <<= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator>>(const Vec2 &_rhs) {
    *this >>= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator+=(const Vec2 &_rhs) {
    x += _rhs.x;
    y += _rhs.y;
    *this = {x, y};
    return *this;
  }
  Vec2 operator-=(const Vec2 &_rhs) {
    x -= _rhs.x;
    y -= _rhs.y;
    *this = {x, y};
    return *this;
  }
  Vec2 operator*=(const Vec2 &_rhs) {
    x *= _rhs.x;
    y *= _rhs.y;
    *this = {x, y};
    return *this;
  }
  Vec2 operator/=(const Vec2 &_rhs) {
    x /= _rhs.x;
    y /= _rhs.y;
    *this = {x, y};
    return *this;
  }
  Vec2 operator%=(const Vec2 &_rhs) {
    *this %= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator&=(const Vec2 &_rhs) {
    *this &= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator|=(const Vec2 &_rhs) {
    *this |= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator^=(const Vec2 &_rhs) {
    *this ^= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator<<=(const Vec2 &_rhs) {
    *this <<= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  Vec2 operator>>=(const Vec2 &_rhs) {
    *this >>= _rhs;
    Vec2 tmp = *this;
    x = tmp.x;
    y = tmp.y;
    return *this;
  }
  operator F64 *() { return Vec2{x, y}; }
  operator const F64 *() { return Vec2{x, y}; }
  operator Vec2 *() { return new Vec2{x, y}; }
  operator const Vec2 *() { return new Vec2{x, y}; }
  Vec2 operator-() const { return Vec2(-x, -y); }
};
class Vec3 : Vec<F64, 3> {
public:
  F64 x, y, z;
  Vec3(F64 _x, F64 _y, F64 _z) {
    x = _x;
    y = _y;
    z = _z;
    *this = {_x, _y, _z};
  }
  Vec3() {
    x = 0;
    y = 0;
    z = 0;
    *this = {0, 0, 0};
  }
  Vec3 operator=(const Vec3 &_rhs) {
    x = _rhs.x;
    y = _rhs.y;
    z = _rhs.z;
    *this = {_rhs.x, _rhs.y, _rhs.z};
    return *this;
  }

  F64 &operator[](U32 i);
  Vec3 operator+(const Vec3 &_rhs) { return *this + _rhs; }
  Vec3 operator-(const Vec3 &_rhs) {
    return Vec3(x - _rhs.x, y - _rhs.y, z - _rhs.z);
  };
  Vec3 operator*(const Vec3 &_rhs) const {
    return Vec3(x * _rhs.x, y * _rhs.y, z * _rhs.z);
  }
  const Vec3 operator/(const Vec3 &_rhs) {
    return Vec3(x / _rhs.x, y / _rhs.y, z / _rhs.z);
  }
  Vec3 operator%(const Vec3 &_rhs) { return *this % _rhs; }
  Vec3 operator&(const Vec3 &_rhs) { return *this & _rhs; };
  Vec3 operator|(const Vec3 &_rhs) { return *this | _rhs; };
  Vec3 operator^(const Vec3 &_rhs) { return *this ^ _rhs; };
  Vec3 operator<<(const Vec3 &_rhs) { return *this << _rhs; };
  Vec3 operator>>(const Vec3 &_rhs) { return *this >> _rhs; };
  Vec3 operator-() const { return Vec3(-x, -y, -z); }
  Vec3 operator+=(const Vec3 &_rhs) {
    x += _rhs.x;
    y += _rhs.y;
    z += _rhs.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator-=(const Vec3 &_rhs) {
    x -= _rhs.x;
    y -= _rhs.y;
    z -= _rhs.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator*=(const Vec3 &_rhs) {
    x *= _rhs.x;
    y *= _rhs.y;
    z *= _rhs.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator/=(const Vec3 &_rhs) {
    x /= _rhs.x;
    y /= _rhs.y;
    z /= _rhs.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator%=(const Vec3 &_rhs) {
    const Vec3 ret = *this % _rhs;
    x = ret.x;
    y = ret.y;
    z = ret.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator&=(const Vec3 &_rhs) {
    const Vec3 ret = *this & _rhs;
    x = ret.x;
    y = ret.y;
    z = ret.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator|=(const Vec3 &_rhs) {
    const Vec3 ret = *this | _rhs;
    x = ret.x;
    y = ret.y;
    z = ret.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator^=(const Vec3 &_rhs) {
    const Vec3 ret = *this ^ _rhs;
    x = ret.x;
    y = ret.y;
    z = ret.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator<<=(const Vec3 &_rhs) {
    const Vec3 ret = *this << _rhs;
    x = ret.x;
    y = ret.y;
    z = ret.z;
    *this = {x, y, z};
    return *this;
  }
  Vec3 operator>>=(const Vec3 &_rhs) {
    const Vec3 ret = *this >> _rhs;
    x = ret.x;
    y = ret.y;
    z = ret.z;
    *this = {x, y, z};
    return *this;
  }

  bool operator==(const Vec3 &_rhs) {
    return x == _rhs.x && y == _rhs.y && z == _rhs.z;
  }
  bool operator!=(const Vec3 &_rhs) {
    return x != _rhs.x || y != _rhs.y || z != _rhs.z;
  }
  bool operator<(const Vec3 &_rhs) {
    return x < _rhs.x && y < _rhs.y && z < _rhs.z;
  }
  bool operator>(const Vec3 &_rhs) {
    return x > _rhs.x && y > _rhs.y && z > _rhs.z;
  }
  bool operator<=(const Vec3 &_rhs) {
    return x <= _rhs.x && y <= _rhs.y && z <= _rhs.z;
  }
  bool operator>=(const Vec3 &_rhs) {
    return x >= _rhs.x && y >= _rhs.y && z >= _rhs.z;
  }
  operator F64 *() const { return Vec3(x, y, z); }
  operator Vec3 *() const { return new Vec3(x, y, z); }
  operator const Vec3 *() const { return new Vec3(x, y, z); }
};
class Vec4 : Vec<F64, 4> {
public:
  F64 x = 0, y = 0, z = 0, w = 0;
  Vec4(F64 _x, F64 _y, F64 _z, F64 _w) { *this = {_x, _y, _z, _w}; }
  Vec4() { *this = {0, 0, 0, 0}; }
  void Set(F64 _x, F64 _y, F64 _z, F64 _w, bool reset = false) {
    if (__builtin_isnan(_x) || __builtin_isnan(_y) || __builtin_isnan(_z) ||
        __builtin_isnan(_w) || reset) {
      if (reset) {
        x = 0, y = 0, z = 0, w = 0;
        *this = {0, 0, 0, 0};
        return;
      }
      throw("Failed to set Vec4: Not a number");
      return;
    }
    x = _x;
    y = _y;
    z = _z;
    w = _w;
    *this = {x, y, z, w};
    return;
  }

  Vec4 Get() {
    *this = {x, y, z, w};
    return *this;
  }

  Vec4 operator=(const Vec4 &_rhs) {
    x = _rhs.x;
    y = _rhs.y;
    z = _rhs.z;
    w = _rhs.w;
    return *this;
  }
  operator F64 *() const { return Vec4(x, y, z, w); }
  operator Vec4 *() const { return new Vec4(x, y, z, w); }
  operator const Vec4 *() const { return new Vec4(x, y, z, w); }
  F64 &operator[](U32 i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw("Failed to get Vec4 value: Index out of range");
    }
  }

  Vec4 operator+(const Vec4 &_rhs);
  Vec4 operator-(const Vec4 &_rhs);
  Vec4 operator*(const Vec4 &_rhs);
  Vec4 operator/(const Vec4 &_rhs);
  Vec4 operator%(const Vec4 &_rhs);
  Vec4 operator&(const Vec4 &_rhs);
  Vec4 operator|(const Vec4 &_rhs);
  Vec4 operator^(const Vec4 &_rhs);
  Vec4 operator<<(const Vec4 &_rhs);
  Vec4 operator>>(const Vec4 &_rhs);
  Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }

  Vec4 operator+=(const Vec4 &_rhs);
  Vec4 operator-=(const Vec4 &_rhs);
  Vec4 operator*=(const Vec4 &_rhs);
  Vec4 operator/=(const Vec4 &_rhs);
  Vec4 operator%=(const Vec4 &_rhs);
  Vec4 operator&=(const Vec4 &_rhs);
  Vec4 operator|=(const Vec4 &_rhs);
  Vec4 operator^=(const Vec4 &_rhs);
  Vec4 operator<<=(const Vec4 &_rhs);
  Vec4 operator>>=(const Vec4 &_rhs);
};
typedef Vec<Vec<F64, 3>, 3> Matrix3x3;
typedef Vec<Vec<F64, 4>, 4> Matrix4x4;
} // namespace Origin