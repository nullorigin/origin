#include "Origin.hpp"
#include "debug/Message.hpp"
#include "process/Exec.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
namespace origin {

int exitDbg(int sig, void * /*ptr*/) {
  setLevel(Code::Info);
  Code status = origin::run.getRunStatus();
  if (status == Code::Success) {
    debug("Process Exited Normally.", status);
  } else {
    debug("Process Exited With Errors.", status);
  }
  return sig;
}

auto exit() -> Code { return run.doExit(); }
auto init(bool debug) -> Code {
  if (debug) {
    int *arg = nullptr;
    ::on_exit(reinterpret_cast<void (*)(int, void *)>(origin::exitDbg),
              arg); // ::on_exit(exit_dbg, cast<void*>(debug));
    setLevel(Code::Info);
  } else {
    setLevel(Code::None);
  }
  origin::run = Run();
  origin::run.setMaxCycles(1000000000);
  origin::run.loop();
  return origin::run.getRunStatus();
}

} // namespace origin