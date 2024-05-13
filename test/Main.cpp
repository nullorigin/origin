#include "Basic.hpp"
#include "Geometry.hpp"
#include "Message.hpp"
#include "Origin.hpp"
#include "String.hpp"

#include "Vector.hpp"

#include "Timer.hpp"

#include <iostream>

#include <string>

#include <unistd.h>

using origin::i32;
namespace origin
{
    using std::string;
    auto main() -> i32
    {
        /////////////////////////////////////
        // Initialize debug message system //
        /////////////////////////////////////
        setStatus(Code::Info);
        setLevel(Code::Info);
        /////////////////////
        // Initialize timer//
        /////////////////////
        Timer timer = Timer();
        timer.setLimit(1000000000000);
        timer.start();
        ///////////////////
        // Hello World...//
        ///////////////////
        string str = string("Hello, World!");
        debug(str, Code::Info);
        /////////////////
        // Vector test //
        /////////////////
        auto* vec = new Vector<i32>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
        std::cout << (vec->toString()) << std::endl;
        vec->prepend(Vector<i32>({ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }));
        std::cout << (vec->toString()) << std::endl;
        auto* vec2 = new Vector<i32>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });
        vec->append(*vec2);
        vec->replace(10, 0);
        std::cout << (vec->toString()) << std::endl;
        vec->randomize();
        std::cout << (vec->toString()) << std::endl;
        /////////////////////
        // Quaternion test //
        /////////////////////
        Quaternion q = Quaternion(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        q = Quaternion::translate(q, Vec3(0.5, 1, 1));
        std::cout << (q.toString()) << std::endl;
        ////////////////////////////
        // Memory conversion test//
        //////////////////////////
        Mem mem = Mem(Mem::Unit::GBYTE);
        mem.set(1024, 512, Mem::Unit::GBYTE);
        auto memsize = mem.size();
        mem = mem.convert(Mem::Unit::MBYTE);
        debug("Memory: " + std::to_string(memsize) + "GB = " + std::to_string(mem.size()) + "MB", Code::Info);
        str = "Goodbye, World!";
        /////////////////
        // Message test//
        /////////////////
        debug(str, Code::Info);
        str = trim("Good", "Bye", str);
        debug(str, Code::Info);
        str = "Hello, World!";
        str = replace("World", "Universe", str);
        debug(str, Code::Info);
        str = "Hello, World! I'm Matthew Fay";
        str = replace("World", "Universe", str);
        //////////////////////////
        // Timer to string test //
        //////////////////////////
        debug(str, Code::Info);
        init(true);
        debug("Elapsed: " + numToString(timer.getElapsed(), 9), Code::Info);
        exit();
        return 0;
    }
} // namespace origin
auto main() -> i32
{
    return origin::main();
}