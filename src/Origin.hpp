#pragma once
#include "Basic.hpp"
#include "math/Geometry.hpp"

namespace origin {
class KeyValue {
public:
  u8 key;
  u8 val;
};
class String {
private:
  u8 *Data;
  u64 length{0};

public:
  String() : Data(new u8[1]) {}

  String(const String &) = default;
  String(String &&) = default;
  auto operator=(String &&) -> String & = delete;
  ~String() {
    delete[] Data;
    length = -1;
  }

  static auto ReplaceU8(u8 *keyval[2], const u8 *str) -> String {
    u64 keyval_len = sizeof(*keyval) / 2;
    u64 str_len = sizeof(*str);
    u8 *tmp = new u8[str_len];
    for (u32 i = 0; i < str_len; i++) {
      tmp[i] = str[i];
      for (u64 j = 0; j < keyval_len; j++) {
        if (str[i] == keyval[j][0]) {
          tmp[i] = keyval[j][1];
        }
      }
    }
    return {tmp, static_cast<u32>(str_len)};
  }
  using callback = bool (*)(u8);

  static auto ReplaceU8(const u8 *keyval[2], const u8 *str, callback func)
      -> String {
    u64 keyval_len = sizeof(*keyval) / 2;
    u64 str_len = sizeof(*str);
    u8 *tmp = new u8;
    for (u32 i = 0; i < str_len; i++) {
      for (u32 j = 0; j < keyval_len; j++) {
        if ((str[i] == keyval[j][0]) && (func(str[i]))) {
          tmp[i] = (keyval[j][1]);
        } else {
          tmp[i] = str[i];
        }
      }
    }
    return (String)*tmp;
  }

  static auto FormatU8(const u8 *str, u32 flags) -> u8 * {
    u8 *ret = new u8[sizeof(*str)];
    for (u32 i = 0; i < sizeof(*str); i++) {
      if ((str[i] >= (u8)('\0') && str[i] <= (u8)('\n')) || (flags == 1) ||
          (str[i] >= (u8)('0') && str[i] <= (u8)('9'))) {
        ret[i] = ' ';
      } else {
        ret[i] = str[i];
      }
    }
    return ret;
  }
  explicit String(u32 _length = 0) : Data(new u8[_length + 1]) {

    if (Data == nullptr) {
      for (u32 i = 0; i < _length; i++) {
        Data[i] = 0;
      }
    }
    length = _length;
    Data[_length] = '\0';
  }

  String(u8 *_data, u32 _length);
  auto CStr(u32 length = sizeof(*Data)) const -> u8 * {
    u8 *ret = new u8[length];
    for (u32 i = 0; i < length; i++) {
      if (Data[i] == '\0') {
        break;
      }
      ret[i] = Data[i];
    }
    return ret;
  }
  static auto StrLen(const u8 *str) -> u32 {
    if (str == nullptr) {
      return 0;
    }
    u32 len = sizeof(str);
    return len;
  }
  static auto Format(u8 *str, u32 flags) -> String {
    u8 *tmp = {str};
    tmp[sizeof(*str)] = '\0';
    switch (flags) {
    case 0:
      return {str, sizeof(*str)};
    case 1:
      for (u32 i = 0; i < sizeof(*str); i++) {
        if (str[i] >= '\0' && str[i] <= '\n') {
          tmp[i] = ' ';
        }
      }
      return {tmp, sizeof(*str)};
    case 2:
      for (u32 i = 0; i < sizeof(*str); i++) {
        if (str[i] < '0' || str[i] > '9') {
          tmp[i] = str[i];
        } else {
          tmp[i] = ' ';
        }
      }
    case 3:
      for (u32 i = 0; i < sizeof(*str); i++) {
        if (str[i] < 'a' || str[i] > 'z') {
          tmp[i] = str[i];
        } else {
          tmp[i] = ' ';
        }
      }
    case 4:
      for (u32 i = 0; i < sizeof(*str); i++) {
        if (str[i] < 'A' || str[i] > 'Z') {
          tmp[i] = str[i];
        } else {
          tmp[i] = ' ';
        }
      }
    default:
      for (u32 i = 0; i < sizeof(*str); i++) {
        tmp[i] = str[i];
      }
    }
    return {str, sizeof(*str)};
  }
  void StrCpy(u8 *dest, const u8 *src) const {
    if (dest == nullptr || src == nullptr) {
      return;
    }
    for (u32 i = 0; i < length; i++) {
      dest[i] = src[i];
    }
  }

  static auto StrCat(const u8 *str1, const u8 *str2) -> u8 * {
    if (str1 == nullptr || str2 == nullptr) {
      return nullptr;
    }
    u32 str1_len = sizeof(*str1);
    u32 str2_len = sizeof(*str2);
    u32 str_len = str1_len + str2_len;
    u8 *ret = new u8[str_len];
    for (u32 i = 1; i < str_len; i++) {
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

  inline u8 operator[](u32 index) { return Data[index]; }
  inline explicit operator u8 *() { return Data; }             // u8*
  inline explicit operator const u8 *() const { return Data; } // const u8*
  auto operator=(const u8 *str) -> String {
    if (str != nullptr) {
      if (str != Data) {
        return {StrCat(Data, str), sizeof(*str)};
      }
    } else {
      for (u32 i = 0; i < length; i++) {
        Data[i] = 0;
      }
    }
    return {Data, static_cast<u32>(length)};
  }
  auto operator=(String str) -> String;
  auto operator+(const u8 *str) -> String;
  auto operator+(String str) -> String;
  auto operator+=(const u8 *str) -> String;
  auto operator+=(String str) -> String;
};

using ID = u64;

class Color : public Vec<u8, 4> {
public:
  f64 Data[4] = {0, 0, 0, 0};
  union {
    struct {
      f64 r{};
      f64 g{};
      f64 b{};
      f64 a{};
    };
  };
  Color(const f64 _r, const f64 _g, const f64 _b, const f64 _a) {
    Data[0] = _r;
    Data[1] = _g;
    Data[2] = _b;
    Data[3] = _a;
  }
  Color() { Data[0] = 0, Data[1] = 0, Data[2] = 0, Data[3] = 0; }
  Color(const Color &) = default;
  Color(Color && /*unused*/) noexcept {
    Data[0] = 0, Data[1] = 0, Data[2] = 0, Data[3] = 0;
  };
  ~Color() = default;
  auto operator=(Color &&) noexcept -> Color & {
    Data[0] = 0, Data[1] = 0, Data[2] = 0, Data[3] = 0;
    return *this;
  }
  auto operator=(const Color &_rhs) -> Color {
    Data[0] = _rhs.r, Data[1] = _rhs.g, Data[2] = _rhs.b, Data[3] = _rhs.a;
    return *this;
  }
  auto operator[](u32 index) -> f64 & { return Data[index]; }
};
class Vertex : public Vec<f64, 10> {
public:
  u32 index;
  u32 owners{};
  Vertex(Vec3 coords, Vec3 normal, Color color) {
    *Data = *new f64[10]{coords[0], coords[1], coords[2], normal[0], normal[1],
                         normal[2], color[0],  color[1],  color[2],  color[3]};
    index = 0;
  }
  explicit Vertex(const Vec3 &coords = Vec3(0.0, 0.0, 0.0),
                  const Vec3 &normal = Vec3(0.0, 0.0, 0.0),
                  const Color &color = Color(0, 0, 0, 0), u32 _index = 0,
                  const u32 *owners = nullptr)
      : index(_index), owners(*owners) {
    *Data = *new f64[10]{coords.Data[0], coords.Data[1], coords.Data[2],
                         normal.Data[0], normal.Data[1], normal.Data[2],
                         color.Data[0],  color.Data[1],  color.Data[2],
                         color.Data[3]};
  }
};
class Triangle : public Vec<Vertex, 3> {
  u32 index{};

public:
  Triangle(const Vertex &_a, const Vertex &_b, const Vertex &_c) {
    for (u32 i = 0; i < 3; i++) {
      Data[0][i % 3] = _a[i];
      Data[1][i % 3] = _b[i];
      Data[2][i % 3] = _c[i];
    }
  }
  ~Triangle() = default;
  auto Get() -> Vertex * { return Data; }
};
template <u32 N> class Mesh : public Vec<Triangle, N> {
  Triangle Data[N];

public:
  ~Mesh() { delete[] *Data; }
  Triangle *Get() { return *Data; }
  const Triangle *Get() const { return *Data; }
  void Index() const {
    for (u32 i = 0; i < 3; i++) {
      Data[i] = Triangle(Vertex(), Vertex(), Vertex());
    }
  }
};
} // namespace origin