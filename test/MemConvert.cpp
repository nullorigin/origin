#include "Basic.hpp"
#include "Message.hpp"
#include "String.hpp"
#include "Timer.hpp"
#include <string>
#include <unistd.h>

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
        mem.Set(1024, 512, Mem::Unit::GBYTE);
        const f64 memsize = mem.Size();
        mem = mem.Convert(Mem::Unit::MBYTE);
        DBG("Memory: " + (std::to_string(memsize)) + "GB = " + std::to_string(mem.Size()) + "MB", INFO);
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
        DBG("Elapsed: " + ToString(timer.GetElapsed(), 9), INFO);
        return 0;
    }
} // namespace origin
auto main() -> int
{
    return origin::main();
}