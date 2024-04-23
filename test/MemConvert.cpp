#include "Basic.hpp"
#include "Message.hpp"
#include "Timer.hpp"
#include <string>
#include <unistd.h>
#include "String.hpp"

namespace origin
{
    using std::string;
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
        DBG("Memory: " + (std::to_string(memsize)) + "GB = " + std::to_string(mem.size) + "MB", INFO);
        str = "Goodbye, World!";
        DBG(str, INFO);
        str = Trim("Good", "Bye", str);
        DBG(str, INFO);
        str = "Hello, World!";
        str = Replace("World", "Universe", str);
        DBG(str, INFO);
        str = "Hello, World! I'm Matthew Fay";
        str = Replace("World", "Universe", str);
        DBG(str, INFO);
        DBG("Elapsed: " + ToString(timer.GetElapsed()), INFO);
        return 0;
    }
} // namespace origin
auto main() -> int
{
    return origin::main();
}