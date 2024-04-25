#ifndef CON_HPP
#define CON_HPP
#include "Basic.hpp"
#include <fcntl.h>
#include <string>
#include <termios.h>
#include <unistd.h>
namespace origin
{
    constexpr i32 FIONREAD = 0x541B;
    using std::string;
    struct Console
    {
        i32 Height;
        i32 Width;
        i32 BgColor;
        i32 FgColor;
        /* Console color identifiers*/
        const i32 BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4,
                  MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7, DARKGRAY = 8,
                  LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11,
                  LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15,
                  BLINK = 128;

        const char* ColorString[16] = {
            "black",
            "blue",
            "green",
            "cyan",
            "red",
            "magenta",
            "brown",
            "lightgray",
            "darkgray",
            "lightblue",
            "lightgreen",
            "lightcyan",
            "lightred",
            "lightmagenta",
            "yellow",
            "white",
        };
        const char* ColorCode[17] = { "\033[0;30m", "\033[0;34m", "\033[0;32m", "\033[0;36m", "\033[0;31m", "\033[0;35m", "\033[0;33m", "\033[0;37m", "\033[1;30m", "\033[1;34m", "\033[1;32m", "\033[1;36m", "\033[1;31m", "\033[1;35m", "\033[1;33m", "\033[1;37m", "\033[0m" };

        Console();
        Console(i32 h, i32 w, i32 bg, i32 fg) :
            Height(h), Width(w), BgColor(bg), FgColor(fg){};
        ~Console();
        static auto ClearEOL() -> void;
        static auto InsertLine() -> void;
        static auto GotoXY(i32 x, i32 y) -> void;

        auto ClearScreen() const -> void;

        auto SetBgColor(i32 color) -> void;
        auto SetFgColor(i32 color) -> void;
        auto PrintBgColor(i32 color) const -> void;

        auto PrintFgColor(i32 color) const -> void;

        auto PrintColor(i32 fg, i32 bg) const -> void;

        static auto UngetChar(i32 ch) -> i32;
        static auto GetChar(bool echo = false) -> i32;

        static auto GetXY(i32& x, i32& y) -> i32;

        static auto GetX() -> i32;

        static auto GetY() -> i32;

        static auto KeyHit() -> i32;
        static auto PrintChar(char c) -> char;
        static auto PrintStr(const string& str) -> i32;
        auto PrintStrColor(const string& str, i32 fg, i32 bg) -> i32;
        static auto ChangeColor(i32 fg, i32 bg) -> i32;
        static auto ChangeColor(i32 color) -> i32;
        static auto PrintCStr(const char* str) -> i32;
        static auto GetHome() -> string;
        static auto GetCwd() -> string;
        static auto GetUser() -> string;
        static auto GetHostname() -> string;
        static auto IsValidPass(const string& passwd) -> bool;
        static auto GetPass(const string& prompt) -> string;
        static auto GetEnv(const string& name) -> string;
        static auto ReadText(i32 l, i32 t, i32 r, i32 b, void* destination)
            -> size_t;
        static auto WriteText(i32 l, i32 t, i32 r, i32 b, void* source) -> size_t;
    } __attribute__((aligned(128)));
} // namespace origin
#endif
