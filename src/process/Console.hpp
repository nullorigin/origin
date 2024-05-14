#ifndef CON_HPP
#define CON_HPP
#include "Basic.hpp"
#include <fcntl.h>
#include <string>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
namespace origin
{
    using std::string;
    struct Console
    {
    private:
        i32 Height{ 25 };
        i32 Width{ 80 };
        i32 Bg_color{ 0 };
        i32 Fg_color{ 15 };

    public:
        /* Console color identifiers*/
        static const u8 BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4,
                        MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7, DARKGRAY = 8,
                        LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11,
                        LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15,
                        BLINK = 128;
        static const i8* color_code[17];

        static const i8* color_string[16];

        Console() :
            Console(25, 80, 0, 15) {}
        Console(i32 h, i32 w, i32 bg, i32 fg) :
            Height(h), Width(w), Bg_color(bg), Fg_color(fg) {}
        ~Console() = default;
        auto clearEol() -> void;
        auto insertLine() -> void;
        auto gotoXy(i32 x, i32 y) -> void;

        auto clearScreen() -> void;

        auto setBgColor(i32 color) -> void;
        auto setFgColor(i32 color) -> void;
        auto printBgColor(i32 color) -> void;

        auto printFgColor(i32 color) -> void;

        auto printColor(i32 fg, i32 bg) -> void;

        auto ungetChar(i32 ch) -> i32;
        auto getChar(bool echo = false) -> i32;

        auto getXy(i32& x, i32& y) -> i32;

        auto getX() -> i32;

        auto getY() -> i32;

        auto keyHit() -> i32;
        auto printChar(i8 c) -> i8;
        auto printStr(const string& str) -> i32;
        auto printStrColor(const string& str, i32 fg, i32 bg) -> i32;
        auto changeColor(i32 fg, i32 bg) -> i32;
        auto changeColor(i32 color) -> i32;
        auto printCStr(const i8* str) -> i32;
        auto getHome() -> string;
        auto getCwd() -> string;
        auto getUser() -> string;
        auto getHostname() -> string;
        auto isValidPass(const string& passwd) -> bool;
        auto getPass(const string& prompt) -> string;
        auto getEnv(const string& name) -> string;
        auto readText(i32 l, i32 t, i32 r, i32 b, void* destination)
            -> size_t;
        auto writeText(i32 l, i32 t, i32 r, i32 b, void* source) -> size_t;
    } __attribute__((aligned(16)));
    static Console con = Console(25, 80, 0, 15);
} // namespace origin
#endif
