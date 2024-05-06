#include "Origin.hpp"
#include "Basic.hpp"
#include "Message.hpp"
#include "process/Console.hpp"
#include "process/Exec.hpp"
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <unistd.h>
namespace Origin
{

    int exit_dbg(int sig, void* /*ptr*/)
    {
        set_level(Code::Info);
        Code status = Origin::run.get_run_status();
        if (status == Code::Success)
        {
            debug("Process Exited Normally.", status);
        }
        else
        {
            debug("Process Exited With Errors.", status);
        }
        return sig;
    }

    auto exit() -> Code
    {
        return run.do_exit();
    }
    auto init(bool debug) -> Code
    {
        if (debug)
        {
            int* arg = nullptr;
            ::on_exit(reinterpret_cast<void (*)(int, void*)>(Origin::exit_dbg), arg); // ::on_exit(exit_dbg, cast<void*>(debug));
            set_level(Code::Info);
        }
        else
        {
            set_level(Code::None);
        }
        Origin::run = Run();
        Origin::run.set_max_cycles(1000000000);
        Origin::run.loop();
        return Origin::run.get_run_status();
    }

} // namespace Origin