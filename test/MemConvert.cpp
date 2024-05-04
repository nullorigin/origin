#include "Basic.hpp"
#include "Message.hpp"
#include "String.hpp"
#include "Timer.hpp"
#include "Vector.hpp"

#include <iostream>

#include <string>

#include <unistd.h>

using Origin::i32;
namespace Origin
{
    using std::string;
    auto main() -> i32
    {
        set_status(Code::info);
        set_level(Code::info);
        Timer timer = Timer();
        timer.set_limit(1000000000000);
        timer.start();
        string str = string("Hello, World!");
        debug(str, Code::info);
        auto* vec = new Vector<i32>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
        std::cout << (vec->to_string()) << std::endl;
        vec->prepend(Vector<i32>({ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }));
        std::cout << (vec->to_string()) << std::endl;
        auto vec2 = new Vector<i32>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });
        vec->append(*vec2);
        vec->replace(10, 0);
        std::cout << (vec->to_string()) << std::endl;
        vec->randomize();
        std::cout << (vec->to_string()) << std::endl;
        Mem mem = Mem(Mem::Unit::GBYTE);
        mem.set(1024, 512, Mem::Unit::GBYTE);
        auto memsize = mem.size();
        mem = mem.convert(Mem::Unit::MBYTE);
        debug("Memory: " + std::to_string(memsize) + "GB = " + std::to_string(mem.size()) + "MB", Code::info);
        str = "Goodbye, World!";
        debug(str, Code::info);
        str = trim("Good", "Bye", str);
        debug(str, Code::info);
        str = "Hello, World!";
        str = replace("World", "Universe", str);
        debug(str, Code::info);
        str = "Hello, World! I'm Matthew Fay";
        str = replace("World", "Universe", str);
        debug(str, Code::info);
        debug("Elapsed: " + num_to_string(timer.get_elapsed(), 9), Code::info);
        return 0;
    }
} // namespace Origin
auto main() -> i32
{
    return Origin::main();
}