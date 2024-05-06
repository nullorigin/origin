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
    private:
        i32 Height{ 25 };
        i32 Width{ 80 };
        i32 BgColor{ 0 };
        i32 FgColor{ 15 };

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
            Height(h), Width(w), BgColor(bg), FgColor(fg) {}
        ~Console() = default;
        auto clear_eol() -> void;
        auto insert_line() -> void;
        auto goto_xy(i32 x, i32 y) -> void;

        auto clear_screen() -> void;

        auto set_bg_color(i32 color) -> void;
        auto set_fg_color(i32 color) -> void;
        auto print_bg_color(i32 color) -> void;

        auto print_fg_color(i32 color) -> void;

        auto print_color(i32 fg, i32 bg) -> void;

        auto unget_char(i32 ch) -> i32;
        auto get_char(bool echo = false) -> i32;

        auto get_xy(i32& x, i32& y) -> i32;

        auto get_x() -> i32;

        auto get_y() -> i32;

        auto key_hit() -> i32;
        auto print_char(i8 c) -> i8;
        auto print_str(const string& str) -> i32;
        auto print_str_color(const string& str, i32 fg, i32 bg) -> i32;
        auto change_color(i32 fg, i32 bg) -> i32;
        auto change_color(i32 color) -> i32;
        auto print_c_str(const i8* str) -> i32;
        auto get_home() -> string;
        auto get_cwd() -> string;
        auto get_user() -> string;
        auto get_hostname() -> string;
        auto is_valid_pass(const string& passwd) -> bool;
        auto get_pass(const string& prompt) -> string;
        auto get_env(const string& name) -> string;
        auto read_text(i32 l, i32 t, i32 r, i32 b, void* destination)
            -> size_t;
        auto write_text(i32 l, i32 t, i32 r, i32 b, void* source) -> size_t;
    } __attribute__((aligned(16)));
    static Console con = Console(25, 80, 0, 15);
} // namespace Origin
#endif
