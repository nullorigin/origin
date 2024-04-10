#pragma once
#include "Origin.hpp"
namespace Origin {

inline String operator""_(const char *str, size_t len) {
  return *(new String((U8 *)str, len));
}

inline String operator+(const String &str1, const String &str2) {
  return str1 + str2;
}

} // namespace Origin