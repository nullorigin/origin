#ifndef CON_HPP
#define CON_HPP
#include "Basic.hpp"
#include <fcntl.h>
#include <string>
#include <termios.h>
#include <unistd.h>
namespace Origin
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

        const i8* ColorString[16] = {
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
        const i8* ColorCode[17] = { "\033[0;30m", "\033[0;34m", "\033[0;32m", "\033[0;36m", "\033[0;31m", "\033[0;35m", "\033[0;33m", "\033[0;37m", "\033[1;30m", "\033[1;34m", "\033[1;32m", "\033[1;36m", "\033[1;31m", "\033[1;35m", "\033[1;33m", "\033[1;37m", "\033[0m" };

        Console();
        Console(i32 h, i32 w, i32 bg, i32 fg) :
            Height(h), Width(w), BgColor(bg), FgColor(fg) {};
        ~Console();
        static auto clear_eol() -> void;
        static auto insert_line() -> void;
        static auto goto_xy(i32 x, i32 y) -> void;

        auto clear_screen() const -> void;

        auto set_bg_color(i32 color) -> void;
        auto set_fg_color(i32 color) -> void;
        auto print_bg_color(i32 color) const -> void;

        auto print_fg_color(i32 color) const -> void;

        auto print_color(i32 fg, i32 bg) const -> void;

        static auto unget_char(i32 ch) -> i32;
        static auto get_char(bool echo = false) -> i32;

        static auto get_xy(i32& x, i32& y) -> i32;

        static auto get_x() -> i32;

        static auto get_y() -> i32;

        static auto key_hit() -> i32;
        static auto print_char(i8 c) -> i8;
        static auto print_str(const string& str) -> i32;
        auto print_str_color(const string& str, i32 fg, i32 bg) -> i32;
        static auto change_color(i32 fg, i32 bg) -> i32;
        static auto change_color(i32 color) -> i32;
        static auto print_c_str(const i8* str) -> i32;
        static auto get_home() -> string;
        static auto get_cwd() -> string;
        static auto get_user() -> string;
        static auto get_hostname() -> string;
        static auto is_valid_pass(const string& passwd) -> bool;
        static auto get_pass(const string& prompt) -> string;
        static auto get_env(const string& name) -> string;
        static auto read_text(i32 l, i32 t, i32 r, i32 b, void* destination)
            -> size_t;
        static auto write_text(i32 l, i32 t, i32 r, i32 b, void* source) -> size_t;
    } __attribute__((aligned(128)));
} // namespace Origin
#endif
