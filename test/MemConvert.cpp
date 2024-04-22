#include "Basic.hpp"
#include "Message.hpp"
#include "String.hpp"
#include "Timer.hpp"
#include <string>
#include <unistd.h>

namespace origin
{
    auto main() -> int
    {
        SetStatus(INFO);
        SetLevel(INFO);
        Timer timer = Timer();
        timer.SetLimit(1000000000000);
        timer.Start();
        string str = string("Hello, World!");
        DBG(str, INFO);
        Mem mem = Mem(Mem::Unit::GBYTE);
        mem.size = 2048;
        mem.used = 256;
        mem.free = 256;
        mem.total = 1024;
        const f64 memsize = mem.size;
        mem.size = mem.Convert(Mem::Unit::MBYTE);
        DBG(std::to_string(memsize) + "GB = " + std::to_string(mem.size) + "MB", INFO);
        DBG("Elapsed: " + std::to_string(timer.GetElapsed()), INFO);
        str = "Goodbye, World!";
        DBG(str, INFO);
        return 0;
    }
} // namespace origin
auto main() -> int
{
    return origin::main();
}