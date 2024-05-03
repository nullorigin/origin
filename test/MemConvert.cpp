#include "Basic.hpp"
#include "Message.hpp"
#include "String.hpp"
#include "Timer.hpp"
#include <initializer_list>
#include <string>
#include <unistd.h>

using Origin::i32;

namespace Origin
{
    using std::string;
    auto main() -> i32
    {
        SetStatus(INFO);
        SetLevel(INFO);
        Timer timer = Timer();
        timer.SetLimit(1000000000000);
        timer.Start();
        string str = string("Hello, World!");
        DBG(str, INFO);
        auto vec = new Vector<i32>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
        std::cout << (vec->ToString()) << std::endl;
        vec->prepend(Vector<i32>({ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }));
        std::cout << (vec->ToString()) << std::endl;
        auto vec2 = new Vector<i32>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });
        vec->append(*vec2);
        std::cout << (vec->ToString()) << std::endl;
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
} // namespace Origin
auto main() -> i32
{
    return Origin::main();
}