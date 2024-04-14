#include "Message.hpp"
#include "Origin.hpp"
#include <string>

namespace origin {
auto main() -> int {
  Mem mem = Mem(Mem::Unit::GBYTE);
  mem.size = 2048;
  mem.used = 256;
  mem.free = 256;
  mem.total = 1024;
  unsigned long long memsize = mem.size;
  mem.size = mem.Convert(Mem::Unit::MBYTE);
  DBG(std::to_string(mem.size) + "MB = " + std::to_string(memsize) + "GB",
      INFO);
  SetStatus(INFO);
  SetLevel(INFO);
  return 0;
}
} // namespace origin
auto main() -> int { return origin::main(); }