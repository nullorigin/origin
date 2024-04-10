#pragma once
#include "math/Basic.hpp"
#include "math/Geometry.hpp"

namespace Origin {

struct String {
private:
  U8 *data;
  U32 length;

public:
  String(U32 _length = 0) {
    data = new U8[_length + 1];
    if (data == nullptr) {
      for (U32 i = 0; i < _length; i++) {
        data[i] = 0;
      }
    }
    length = _length;
    data[_length] = '\0';
  }

  String(U8 *_data, U32 _length);
  ~String() { delete[] data; }

  U8 *CStr(U32 length = sizeof(*data)) const {
    U8 *ret = new U8[length];
    for (U32 i = 0; i < length; i++) {
      if (data[i] == '\0') {
        break;
      }
      ret[i] = data[i];
    }
    return ret;
  }

  U32 StrLen(U8 *str) {
    if (str == nullptr) {
      return 0;
    }
    U32 len = sizeof(str);
    return len;
  }

  void StrCpy(U8 *dest, U8 *src) {
    if (dest == nullptr || src == nullptr) {
      return;
    }
    for (U32 i = 0; i < length; i++) {
      dest[i] = src[i];
    }
  }

  U8 *StrCat(U8 *str1, U8 *str2) {
    if (str1 == nullptr || str2 == nullptr) {
      return NULL;
    }
    U32 str1_len = sizeof(*str1);
    U32 str2_len = sizeof(*str2);
    U32 str_len = str1_len + str2_len;
    U8 *ret = new U8[str_len];
    for (U32 i = 1; i < str_len; i++) {
      if (ret[i - 1] != '\0') {
        if (i < str1_len) {
          ret[i] = str1[i];
        } else {
          ret[i] = str2[i - str1_len];
        }
      } else {
        i++;
        str_len--;
      }
    }
    return ret;
  }

  inline U8 operator[](U32 index) { return data[index]; }
  inline operator U8 *() { return data; }             // U8*
  inline operator const U8 *() const { return data; } // const U8*
  String operator=(const U8 *str) {
    if (str != nullptr) {
      if (str != data)
        return *StrCat((U8 *)data, (U8 *)str);
    } else {
      for (U32 i = 0; i < length; i++) {
        data[i] = 0;
      }
    }
    return *this;
  }
  String operator=(const String str);
  String operator+(const U8 *str);
  String operator+(const String str);
  String operator+=(const U8 *str);
  String operator+=(const String str);
};

typedef U64 ID;

class Color : public Vec<U8, 4> {
public:
  const U8 r = 0;
  const U8 g = 1;
  const U8 b = 2;
  const U8 a = 3;
  Color(const U8 _r, const U8 _g, const U8 _b, const U8 _a) {
    *this = {_r, _g, _b, _a};
  }
  Color() { *this = {0, 0, 0, 0}; }
  Color operator=(const Color &_rhs) {
    *this = {_rhs.r, _rhs.g, _rhs.b, _rhs.a};
    return *this;
  }
  F64 &operator[](U32 index) { return (F64 &)(*this)[index]; }
};
class Vertex {
  F64 *data[10];
  U32 index;
  U32 *owners;

public:
  Vertex(Vec3 coords, Vec3 normal, Color color) {
    *data = new F64[10]{coords[0], coords[1], coords[2], normal[0], normal[1],
                        normal[2], color[0],  color[1],  color[2],  color[3]};
    index = 0;
    owners = nullptr;
  }
  Vertex(Vec3 coords = {0.0, 0.0, 0.0}, Vec3 normal = {0.0, 0.0, 0.0},
         Color color = {0, 0, 0, 0}, U32 _index = 0, U32 *owners = nullptr) {
    *data = new F64[10]{coords[0], coords[1], coords[2], normal[0], normal[1],
                        normal[2], color[0],  color[1],  color[2],  color[3]};
    index = _index;
    owners = nullptr;
  }
};
class Triangle {
  Vertex *data = Vec<Vertex, 3>();
  U32 index;

public:
  Triangle(const Vertex &_a, const Vertex &_b, const Vertex &_c) {
    data[0] = _a;
    data[1] = _b;
    data[2] = _c;
  }
  Triangle() {
    *data = (Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0));
    for (U32 i = 0; i < 3; i++) {
      data[i] = Vec3(0, 0, 0);
    }
  }
  ~Triangle() { delete[] data; }
  Vertex *Get() { return data; }
  const Vertex *Get() const { return data; }
  Vertex &operator[](U32 _i) { return data[_i]; }
  Vertex operator[](U32 _i) const { return data[_i]; }
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