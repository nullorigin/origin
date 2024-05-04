#include "Console.hpp"
#include "Basic.hpp"
#include <cstdio>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
namespace Origin
{
    Console::Console() :
        Height(25), Width(80)
    {
        BgColor = BLACK;
        FgColor = WHITE;
    }
    auto Console::clear_eol() -> void
    {
        printf("\033[2K");
    }
    auto Console::insert_line() -> void
    {
        printf("\033[%dA", 1);
    }
    auto Console::goto_xy(i32 x, i32 y) -> void
    {
        printf("\033[%d;%df", y, x);
    }
    /**
     * Clears the entire screen in the console.
     *
     * @return void
     */
    auto Console::clear_screen() const -> void
    {
        printf("\033[%dm\033[2J\033[1;1f", BgColor);
    }
    auto Console::set_bg_color(i32 color) -> void
    {
        BgColor = 40 + (color % 16);
    }
    auto Console::set_fg_color(i32 color) -> void
    {
        FgColor = 30 + (color % 16);
    }
    auto Console::print_bg_color(i32 color) const -> void
    {
        constexpr i32 offset = 30;
        constexpr i32 bright_offset = 60;

        printf("\033[%d;%dm", (color < 16) ? offset : bright_offset, BgColor + color % 16);
    }
    auto Console::print_fg_color(i32 color) const -> void
    {
        constexpr i32 offset = 30;
        constexpr i32 bright_offset = 90;
        constexpr i32 fg_colors[] = {
            0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15
        };

        printf("\033[%d;%dm", (color < 16) ? offset : bright_offset, fg_colors[color % 16] + FgColor);
    }
    auto Console::print_color(i32 fg, i32 bg) const -> void
    {
        constexpr i32 offset = 30;
        constexpr i32 bright_offset = 60;
        constexpr i32 fg_colors[] = {
            0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15
        };

        printf("\033[%d;%d;%dm",
               (bg < 16) ? bright_offset : offset,
               fg_colors[fg % 16] + FgColor,
               BgColor + bg % 16);
    }
    auto Console::unget_char(i32 ch) -> i32
    {
        return ungetc(ch, stdin);
    }
    auto Console::get_char(bool echo) -> i32
    {
        struct termios oldt
        {
        };
        tcgetattr(STDIN_FILENO, &oldt);
        if (echo)
        {
            tcflag_t flags = oldt.c_lflag;
            flags &= ~ICANON & ~ECHO;
            oldt.c_lflag = flags;
        }
        else
        {
            tcflag_t flags = oldt.c_lflag;
            flags &= ~ICANON | ECHO;
            oldt.c_lflag = flags;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        i32 ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

    /**
     * Get the X and Y coordinates of the console cursor position using ANSI escape sequences.
     *
     * @param x reference to store the X coordinate
     * @param y reference to store the Y coordinate
     *
     * @return the product of X and Y coordinates
     */
    auto Console::get_xy(i32& x, i32& y) -> i32
    {
        static constexpr i8 seq[] = "\033[6n";
        static constexpr i8 end[] = "R";
        static constexpr size_t seq_len = sizeof(seq) - 1;
        static constexpr size_t end_len = sizeof(end) - 1;

        write(STDOUT_FILENO, seq, seq_len);

        i8 buf[256];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));

        if (len <= seq_len || std::memcmp(buf, seq, seq_len) != 0)
        {
            return 0;
        }

        i8p p = buf + seq_len;
        i8p end_p = static_cast<i8p>(memchr(p, end[0], len - seq_len));
        if (end_p == nullptr || end_p - p < end_len)
        {
            return 0;
        }

        i32 ly = 0;
        for (i8* q = p; q < end_p; ++q)
        {
            if (*q == ';')
            {
                p = q + 1;
                break;
            }
            ly = ly * 10 + *q - '0';
        }

        i32 lx = 0;
        for (i8p q = p; q < end_p; ++q)
        {
            lx = lx * 10 + *q - '0';
        }

        x = lx;
        y = ly;
        return x * y;
    }
    /**
     * Get the x-coordinate.
     *
     * @return the x-coordinate value
     */
    auto Console::get_x() -> i32
    {
        i32 x = 0;
        i32 y = 0;
        get_xy(x, y);
        return x;
    }
    /**
     * Get the Y coordinate from the Console.
     *
     * @return the Y coordinate value
     */
    auto Console::get_y() -> i32
    {
        i32 x = 0;
        i32 y = 0;
        get_xy(x, y);
        return y;
    }

    /**
     * If there are bytes available, enable cannonical and echo modes
     * so that the next read call retrieves the keypress
     */
    auto Console::key_hit() -> i32
    {
        constexpr i32 icanon_echo = (ICANON | ECHO);
        i32 available = 0;

        if (ioctl(0, FIONREAD, &available) == -1)
        {
            perror("ioctl error");
            return 0;
        }

        // If there are bytes available, enable cannonical and echo modes
        // so that the next read call retrieves the keypress
        if (available > 0)
        {
            termios old_t{};
            termios new_t{};

            if (tcgetattr(0, &old_t) == -1)
            {
                perror("tcgetattr error");
                return 0;
            }

            new_t = old_t;
            new_t.c_lflag |= icanon_echo;

            if (tcsetattr(0, TCSANOW, &new_t) == -1)
            {
                perror("tcsetattr error");
                return 0;
            }
        }

        return static_cast<i32>(available > 0);
    }

    /**
     * Print a character to the console.
     *
     * @param c the character to be printed
     *
     * @return the character that was printed
     *
     * @throws None
     */
    auto Console::print_char(const i8 c) -> i8
    {
        printf("%c", c);
        return c;
    }
    /**
     * Print a string to the console.
     *
     * @param str the string to be printed
     *
     * @return 0
     *
     * @throws None
     */
    auto Console::print_str(const string& str) -> i32
    {
        printf("%s", str.c_str());
        return 0;
    }
    auto Console::print_str_color(const string& str, i32 fg, i32 bg) -> i32
    {
        set_fg_color(fg);
        set_bg_color(bg);
        print_str(str);
        set_fg_color(WHITE);
        set_bg_color(BLACK);
        return 0;
    }
    /**
     * Change color of the console text.
     *
     * @param fg the foreground color
     * @param bg the background color
     *
     * @return 0
     *
     * @throws None
     */
    auto Console::change_color(i32 fg, i32 bg) -> i32
    {
        printf("\033[%d;%dm", fg + 30, bg + 40);
        return 0;
    }
    auto Console::change_color(i32 color) -> i32
    {
        return change_color(color % 16, color / 16);
    }
    /**
     * Print a C-style string to the console.
     *
     * @param str the C-style string to be printed
     *
     * @return 0 indicating success
     *
     * @throws None
     */
    auto Console::print_c_str(const i8* str) -> i32
    {
        printf("%s", str);
        return 0;
    }
    auto Console::get_home() -> string
    {
        return get_env("HOME");
    }
    auto Console::get_cwd() -> string
    {
        i8 cwd[1024];
        return getcwd(cwd, sizeof(cwd));
    }
    auto Console::get_user() -> string
    {
        return cuserid(nullptr);
    }
    /**
     * Get the hostname of the system.
     *
     * @return The hostname as a string
     */
    auto Console::get_hostname() -> string
    {
        i8 hostname[1024];
        gethostname(hostname, sizeof(hostname));
        return hostname;
    }
    auto Console::is_valid_pass(const string& passwd) -> bool
    {
        return (passwd.length() > 0 && passwd.length() <= 32 && passwd.find_first_not_of("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz./") == string::npos);
    }
    auto Console::get_pass(const string& prompt) -> string
    {
        string passwd;
        passwd.resize(32);
        for (i32 i = 3; i >= 0; i--)
        {
            std::cout << prompt;
            std::cin >> passwd;
            if (is_valid_pass(passwd))
            {
                return passwd;
                break;
            };
        }
        return "";
    }
    auto Console::get_env(const string& name) -> string
    {
        return getenv(name.c_str());
    }
    auto Console::read_text(i32 l, i32 t, i32 r, i32 b, void* destination)
        -> size_t
    {
        printf("\033[%d;%d;%d;%dH", b, t, r, l);
        if (fflush(stdout) == EOF)
        {
            return 0;
        }
        return fread(destination, 1, static_cast<size_t>(l * t) * r, stdin);
    }
    auto Console::write_text(i32 l, i32 t, i32 r, i32 b, void* source) -> size_t
    {
        printf("\033[%d;%d;%d;%dH", b, t, r, l);
        if (fflush(stdout) == EOF)
        {
            return 0;
        };
        return fwrite(source, 1, static_cast<size_t>(l * t) * r, stdout);
    }
} // namespace Origin