#pragma once
#include <cctype>
#ifndef STRING_HPP
#define STRING_HPP
#include "Basic.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <valarray>
namespace origin {
template <typename X, typename Y> class KeyVal {
private:
  std::valarray<X> Key = std::valarray<X>();
  std::valarray<Y> Val = std::valarray<Y>();

public:
  KeyVal<X, Y> &operator=(KeyVal<X, Y> &&in) noexcept {
    Key = std::move(in.Key);
    Val = std::move(in.Val);
    return *this;
  }
  auto operator=(KeyVal<X, Y> in) noexcept -> KeyVal<X, Y> & {
    Key = in.Key;
    Val = in.Val;
    *this = std::move(*this);
    return *this;
  }
  KeyVal<X, Y>(KeyVal<X, Y> &&in) noexcept
      : Key(std::move(in.Key)), Val(std::move(in.Val)) {
    in.Key = std::valarray<X>(0);
    in.Val = std::valarray<Y>(0);
  }
  KeyVal<X, Y>(const KeyVal<X, Y> &in) noexcept : Key(in.Key), Val(in.Val) {}
  explicit KeyVal<X, Y>(const std::valarray<X> &key,
                        const std::valarray<Y> &val)
      : Key(std::valarray<X>(key)), Val(std::valarray<X>(val)) {}
  KeyVal<X, Y>() : Key(std::valarray<X>(0)), Val(std::valarray<Y>(0)) {}
  ~KeyVal<X, Y>() = default;
};
static auto toLower(const std::string &str) -> std::string {
  std::string ret = str;
  std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
  return ret;
}

static auto toUpper(const std::string &str) -> std::string {
  std::string ret = str;
  std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
  return ret;
}
static auto trim(const std::string &str) -> std::string {
  return str.substr(0, str.length() - 1);
}
static auto trim(const std::string &begin, const std::string &end,
                 const std::string &str) -> std::string {
  size_t start = str.find_first_not_of(begin);
  size_t end_it = str.find(end) - 1;

  if (start == std::string::npos || end_it == std::string::npos) {
    return "";
  }

  return str.substr(start, end_it - start + 1);
}

static auto trim(const size_t n, const std::string &str) -> std::string {
  return trim(str.substr(n, str.length() - n - 1));
}
static auto trim(const size_t start, const std::string &end,
                 const std::string &str) -> std::string {
  if (start == std::string::npos || end.length() > str.length()) {
    return "";
  }

  size_t end_it = str.find_last_not_of(end) - end.length() - 1;
  if (end_it == std::string::npos) {
    end_it = 0;
  } else {
    ++end_it;
  }

  return trim(str.substr(start, end_it - start));
}
static auto trim(const std::string &start, const size_t end,
                 const std::string &str) -> std::string {
  if (end == std::string::npos || start.length() > str.length()) {
    return "";
  }

  size_t start_it = str.find_first_of(start) + start.length() + 1;
  if (start_it == std::string::npos) {
    start_it = 0;
  } else {
    --start_it;
  }
  return trim(str.substr(start_it, end - start_it));
}
static auto replace(const std::string &from_str, const std::string &to_str,
                    const std::string &str) -> std::string {
  std::string result;
  result.reserve(str.length());
  size_t pos = 0;
  size_t prev_pos = 0;
  while ((pos = str.find(from_str, pos)) != std::string::npos) {
    result.append(str, prev_pos, pos - prev_pos);
    result += to_str;
    pos += from_str.length();
    prev_pos = pos;
  }
  result += str.substr(prev_pos);
  return result;
}
static auto replace(const std::string &search, const std::string &repl,
                    const std::string &file_name, u32 retries) -> std::string {
  std::string result;
  bool success = false;
  u32 retries_count = retries;
  std::fstream file(file_name,
                    std::fstream::in | std::fstream::out | std::fstream::trunc);
  while (!success && retries_count > 0) {
    file.open(file_name,
              std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (file.is_open()) {
      try {
        (file.seekp(0, std::ios::end));
        result.resize(file.tellp());
        file << replace(search, repl, result);
        file.seekp(0, std::ios::beg);
        file << result;
        success = true;
      } catch (std::exception &e) {
        if (file.is_open()) {
          file.close();
        }
        retries_count--;
        continue;
      }
    } else {
      retries_count--;
    }
  }
  return result;
}
static auto clean(std::string str, u32 flags) {
  auto dst = str.begin();
  for (i8 &src : str) {
    if ((src >= '\0' && src <= '\n') ||
        (flags == 1 && (src >= '0' && src <= '9'))) {
      *dst++ = ' ';
    } else {
      *dst++ = src;
    }
  }
  str.erase(dst, str.end());
  return str;
}

static auto length(const std::string &str) -> u64 { return str.size(); }
static auto format(const std::string &str, u32 flags) -> std::string {
  u64 len = str.size();
  std::string out;
  out.resize(len);
  auto p = out.begin();
  auto s = str.cbegin();
  for (; s != str.cend(); ++s, ++p) {
    if ((flags == 1 && (isdigit(*s) == 0)) ||
        (flags == 2 && (isdigit(*s) == 0)) ||
        (flags == 3 && (islower(*s) == 0)) ||
        (flags == 4 && (isupper(*s) == 0)) || (*s >= '\0' && *s <= '\n')) {
      *p = ' ';
    } else {
      *p = *s;
    }
  }
  return out;
}

static void copy(i8p dest, const i8 *src) {
  std::memcpy(dest, src, strlen(src) + 1);
}

static auto concatenate(const std::string &first,
                        const std::string &second) -> std::string {
  const auto first_len = first.size();
  const auto second_len = second.size();
  std::string result;
  result.reserve(first_len + second_len);
  result.append(first);
  result.append(second);
  return result;
}

static auto concatenate(const std::string &first, const std::string &second,
                        const std::string &third) -> std::string {
  const auto first_len = first.size();
  const auto second_len = second.size();
  const auto third_len = third.size();
  std::string result;
  result.reserve(first_len + second_len + third_len);
  result.append(first);
  result.append(second);
  result.append(third);
  return result;
}
static auto erase(std::string &str,
                  const std::string &toErase) -> std::string & {
  return str.erase(0, str.find(toErase) + toErase.length());
}
static auto eraseAll(std::string &str,
                     const std::string &toErase) -> std::string & {
  auto last_pos = str.find_first_not_of(toErase);
  auto pos = str.find_first_of(toErase, last_pos);
  while (std::string::npos != pos || std::string::npos != last_pos) {
    str.erase(pos, toErase.length());
    last_pos = pos + 1;
    pos = str.find_first_of(toErase, last_pos);
  }
  return str;
}
inline auto numDigits(f128 num, std::string &buf) -> f128 {
  buf = std::to_string(fabsl(num));
  f128 ret = buf.size() - 1;
  while (buf[ret] == '0') {
    ret--;
  }
  if (buf[ret] == '.') {
    ret--;
  }
  return ret;
}

inline auto numToString(f128 num, u32 precision = 9,
                        i32 offset = 0) -> std::string {
  std::string buffer(10000, '\0');
  std::string digits(10000, '\0');
  std::stringstream ss;
  ss.precision(precision);
  ss.flags(std::stringstream::dec);
  f128 factor = 1.0;
  factor = offset > 0   ? powli(10.0, offset)
           : offset < 0 ? powli(10.0, -offset)
                        : 1.0;
  ss << (num * factor);
  ss >> digits;
  digits.erase(digits.find_last_not_of('0') + 1, std::string::npos);
  digits.shrink_to_fit();
  ss.clear();
  if (offset > 0) {
    buffer = digits.substr(0, digits.length() - offset);
  } else {
    buffer = digits.substr(0, digits.length() + offset);
  }
  return buffer;
}
inline auto switchType(const char x) -> std::string {
  switch (x) {
  case 'b':
    return "bool";
  case 'c':
    return "char";
  case 'd':
    return "double";
  case 'f':
    return "float";
  case 'i':
    return "int";
  case 's':
    return "short";
  case 'v':
    return "void";
  case 'w':
    return "wchar_t";
  case 'C':
    return "const";
  case 'D':
    return "volatile";
  case 'J':
    return "jmp_buf";
  case 'L':
    return "long";
  case 'N':
    return "int";
  case 'O':
    return "long long";
  case 'P':
    return "FILE";
  case 'R':
    return "restrict";
  case 'S':
    return "signed";
  case 'U':
    return "unsigned";
  case 'W':
    return "int64_t";
  case 'Y':
    return "ptrdiff_t";
  case 'Z':
    return "int32_t";
  case '&':
    return "&";
  case '*':
    return "*";
  default:
    return "";
  }

  return "";
}
inline auto nand(const char x, const char y, const char z) -> bool {
  return (x == y || x == z) && (y != z);
}
struct FunctionData {
  FunctionData() = default;
  Vector<std::string> types =
      Vector<std::string>({"bool", "void", "char", "short", "int", "long",
                           "long long", "float", "double", "long double",
                           "long int", "long long int", "wchar", "complex"});
  Vector<std::string> prefix = Vector<std::string>(
      {"signed", "unsigned", "const", "const signed", "const unsigned",
       "volatile", "const volatile", "const volatile signed",
       "const volatile unsigned", "const restrict", "const volatile restrict",
       "const volatile restrict signed", "const volatile restrict unsigned"});
  Vector<std::string> suffix =
      Vector<std::string>("", "*", "&", "**", "*&", "&&");
  Vector<std::string> generate() {
    Vector<std::string> out = Vector<std::string>();
    for (const std::string &j : prefix) {
      for (const std::string &t : types) {
        for (const std::string &k : suffix) {
          out.append({j + " " + t + k});
        }
      }
    }
    return out;
  }
};
inline std::string stringToFunction(const char *x, const char *fname) {
  std::string s1 = std::string(x);
  std::string s2 = std::string(switchType(s1[0]) + " " + fname + "(");
  int i = 1;
  int j = 0;
  bool type_done = false;
  const std::string in_param[] = {"b", "c", "d", "f", "i", "v", "w", "C",
                                  "D", "J", "L", "N", "O", "P", "R", "S",
                                  "U", "W", "Y", "Z", "&", "*"};
  const std::string out_param[] = {
      "bool",      "char",    "double",   "float",   "int",      "void",
      "wchar_t",   "const",   "volatile", "jmp_buf", "long",     "long",
      "long long", "FILE",    "restrict", "signed",  "unsigned", "int64_t",
      "ptrdiff_t", "int32_t", "&",        "*"};
  const std::string argname[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i",
                                 "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                 "s", "t", "u", "v", "w", "x", "y", "z"};

  std::string tmp;
  while (s1[i] != '\0') {
    if (type_done) {
      if (j < 25) {
        s2 += tmp.append(" " + argname[j]);
        s1[i + 1] != '\0' ? s2.append(", ") : s2.append(")");
        j++;
      }
      tmp = " ";
      type_done = false;
    }
    i++;
    tmp += switchType(s1[i]);
    if (tmp != "") {
      tmp += " ";
      if (s1[i] == 'v' || s1[i] == 's' || s1[i] == 'c' || s1[i] == 'b' ||
          s1[i] == 'i' || s1[i] == 'f' || s1[i] == 'd' ||
          (s1[i] == '&' && s1[i + 1] != '&' && s1[i + 1] != '*') ||
          (s1[i] == '*' && s1[i + 1] != '*') || s1[i] == 'w' ||
          s1[i + 1] == 'R' || s1[i] == 'N' || s1[i] == 'J' || s1[i] == 'P' ||
          s1[i] == 'O' || s1[i] == 'W' || s1[i] == 'Y' || s1[i] == 'Z') {
        type_done = true;
      }
    }
  }
  return s2;
}
} // namespace origin

#endif // STRING_HPP