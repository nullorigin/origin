#ifndef CON_HPP
#define CON_HPP
#include <cstdio>
#include <fcntl.h>
#include <sstream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
namespace origin
{
#define FIONREAD 0x541B
    struct Console
    {
        int Height;
        int Width;
        int BgColor;
        int FgColor;
        /* Console color identifiers*/
        static const int BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4,
                         MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7, DARKGRAY = 8,
                         LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11,
                         LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15,
                         BLINK = 128;

        const char* color_string[16] = {
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
        const char* color_code[17] = { "\033[0;30m", "\033[0;34m", "\033[0;32m", "\033[0;36m", "\033[0;31m", "\033[0;35m", "\033[0;33m", "\033[0;37m", "\033[1;30m", "\033[1;34m", "\033[1;32m", "\033[1;36m", "\033[1;31m", "\033[1;35m", "\033[1;33m", "\033[1;37m", "\033[0m" };

        Console();
        auto ClearEOL() -> void;
        auto InsertLine() -> void;
        auto GotoXY(int x, int y) -> void;

        auto ClearScreen() -> void;

        auto SetBgColor(int color) -> void;
        auto SetFgColor(int color) -> void;
        auto PrintBgColor(int color) -> void;

        auto PrintFgColor(int color) -> void;

        auto PrintColor(int fg, int bg) -> void;

        auto UngetChar(char ch) -> int;
        auto GetChar(bool echo = false) -> int;

        auto GetXY(int& x, int& y) -> int;

        auto GetX() -> int;

        auto GetY() -> int;

        auto KeyHit() -> int;

        auto PrintChar(const char c) -> char;
        auto PrintStr(std::string str) -> int;
        auto PrintStrColor(const std::string& str, int fg, int bg) -> int;
        auto ChangeColor(int fg, int bg) -> int;
        auto ChangeColor(int color) -> int;
        auto PrintCStr(const char* str) -> int;
        auto GetHome() -> std::string;
        auto GetCwd() -> std::string;
        auto GetUser() -> std::string;
        static auto GetHostname() -> std::string;
        auto GetPass(const char* prompt) -> char*;
        auto GetEnv(const std::string& name) -> std::string;
        auto ReadText(int l, int t, int r, int b, void* destination)
            -> size_t;
        auto WriteText(int l, int t, int r, int b, void* source) -> size_t;
    };
}
#endif
