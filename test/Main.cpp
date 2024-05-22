#include "Basic.hpp"
#include "Geometry.hpp"
#include "Message.hpp"
#include "Origin.hpp"
#include "String.hpp"
#include "Timer.hpp"
#include <iostream>

#include <string>

#include <unistd.h>

using origin::i32;
namespace origin {
using std::string;
auto testVec() -> void;
auto testStr() -> void;
auto testGeom() -> void;
auto testTimer() -> Timer;
auto testMem() -> void;
auto testMessage() -> void;
auto main() -> i32 {
  /////////////////////////////////////
  // Initialize debug message system //
  /////////////////////////////////////
  setStatus(Code::Info);
  setLevel(Code::Info);
  ///////////////////
  // Hello World...//
  ///////////////////
  string str = string("Hello, World!");
  debug(str, Code::Info);
  testGeom();
  testStr();
  testVec();
  testMessage();
  testMem();
  init(false);
  Timer timer = testTimer();
  debug("Elapsed: " + numToString(timer.getElapsed() / 1000000000.0L, 9),
        Code::Info);
  exit();
  return 0;
}
auto testVec() -> void {
  Vector<i32> vec = Vector<i32>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  std::cout << (vec.toString()) << std::endl;
  *vec = Vector<i32>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  std::cout << (vec.toString()) << std::endl;
  Vector<i32> vec2 = Vector<i32>(
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20});
  vec2.replace(10, 0);
  std::cout << (vec2.toString()) << std::endl;
  vec.randomize();
  std::cout << (vec.toString()) << std::endl;
  vec.append(*vec2);
  std::cout << (vec.toString()) << std::endl;
}
auto testStr() -> void {
  string str = string("Hello, World!");
  std::cout << (str) << std::endl;
}
auto testGeom() -> void {
  Vec4 v4 = Vec4(1, 2, 3, 4);
  Vec3 v3 = Vec3(1, 2, 3);
  Vec2 v2 = Vec2(1, 2);
  std::cout << Vector({v4.X, v4.Y, v4.Z, v4.W, v3.X, v3.Y, v3.Z, v2.X, v2.Y})
                   .toString()
            << std::endl;
  Quaternion q =
      Quaternion(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  q = Quaternion::translate(q, Vec3(0.5, 1, 1));
  std::cout << (q.toString()) << std::endl;
}
auto testTimer() -> Timer {
  Timer timer = Timer();
  timer.setLimit(1000000000000);
  timer.start();
  while (timer.getElapsed() < 100000000000) {
    std::cout << (timer.getElapsed() / 1000000000.0L) << std::endl;
  }
  std::cout << (timer.getElapsed() / 1000000000.0L) << std::endl;
  return timer;
} // namespace origin
auto testMessage() -> void {
  debug("Hello, World!", Code::Info);
  debug("Hello, Warning!", Code::Warning);
  debug("Hello, Error!", Code::Error);
  debug("Hello, Fatality!", Code::Fatal);
  debug("Hello, ???!", Code::Any);
}
auto testMem() -> void {
  Mem mem = Mem(Mem::Unit::GBYTE);
  mem.set(1024, 512, Mem::Unit::GBYTE);
  auto memsize = mem.size();
  mem = mem.convert(Mem::Unit::MBYTE);
  debug("Memory: " + std::to_string(memsize) +
            "GB = " + std::to_string(mem.size()) + "MB",
        Code::Info);
}
} // namespace origin
auto main() -> i32 { return origin::main(); }