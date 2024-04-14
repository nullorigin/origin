#include "Origin.hpp"
namespace origin {

inline auto operator+(const String &str1, const String &str2) -> String {
  String ret = str1;
  ret += str2;
  return {ret};
}

} // namespace origin