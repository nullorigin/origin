#pragma once
#include "Origin.hpp"
namespace Origin {
String::String(U8 *_data, U32 _length) {
  if (_data == nullptr) {
    data = new U8[_length + 1];
    for (U32 i = 0; i < _length; i++) {
      data[i] = 0;
    }
    length = _length;
    return;
  }
  data = new U8[_length + 1];
  data = _data;
  length = _length;
}
String::String(U32 length) : data(nullptr) {
  data = new U8[length + 1];
  for (U32 i = 0; i < length; i++) {
    data[i] = 0;
  }
}

String::~String() { delete[] data; }
U8 *String::CStr(U32 length) const {
  U8 *ret = new U8[length];
  for (U32 i = 0; i < length; i++) {
    if (data[i] == '\0') {
      break;
    }
    ret[i] = data[i];
  }
  return ret;
}
U32 String::StrLen(U8 *str) {
  if (str == nullptr) {
    return 0;
  }
  U32 len = sizeof(str);
  return len;
}
void String::StrCpy(U8 *dest, U8 *src) {
  if (dest == nullptr || src == nullptr) {
    return;
  }
  for (U32 i = 0; i < length; i++) {
    dest[i] = src[i];
  }
}

U8 *String::StrCat(U8 *str1, U8 *str2) {
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

inline String operator""_(const char *str, size_t len) {
  return *(new String((U8 *)str, len));
}

inline String operator+(const String &str1, const String &str2) {
  return str1 + str2;
}
String String::operator=(const U8 *str) {
  if (str != nullptr) {
    for (U32 i = 0; i < length; i++) {
      data[i] = str[i];
    }
  }
  return *this;
}
String String::operator=(const String str) {
  if (str != nullptr) {
    data = str.CStr();
  }
  return *this;
}
String String::operator+(const U8 *str) {
  return *StrCat((U8 *)data, (U8 *)str);
}
String String::operator+(const String str) {
  return *StrCat((U8 *)data, (U8 *)str.CStr());
}
String String::operator+=(const U8 *str) {
  *this = *StrCat((U8 *)data, (U8 *)str);
  return *this;
}
String String::operator+=(const String str) {
  *this = *StrCat((U8 *)data, (U8 *)str.CStr());
  return *this;
}
void Vec4::Set(F64 _x, F64 _y, F64 _z, F64 _w, bool reset) {
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
Vec4 Vec4::Get() {
  *this = {x, y, z, w};
  return *this;
}
F64 &Vec4::operator[](U32 i) {
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
} // namespace Origin