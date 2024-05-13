#include "Console.hpp"
#include "Basic.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
namespace origin
{
    const i8* Console::color_code[17] = { "\033[0;30m", "\033[0;34m", "\033[0;32m", "\033[0;36m", "\033[0;31m", "\033[0;35m", "\033[0;33m", "\033[0;37m", "\033[1;30m", "\033[1;34m", "\033[1;32m", "\033[1;36m", "\033[1;31m", "\033[1;35m", "\033[1;33m", "\033[1;37m", "\033[0m" };
    const i8* Console::color_string[16] = {
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
    auto Console::clearEol() -> void
    {
        printf("\033[2K");
    }
    auto Console::insertLine() -> void
    {
        printf("\033[%dA", 1);
    }
    auto Console::gotoXy(i32 x, i32 y) -> void
    {
        printf("\033[%d;%df", y, x);
    }
    /**
     * Clears the entire screen in the console.
     *
     * @return void
     */
    auto Console::clearScreen() -> void
    {
        printf("\033[%dm\033[2J\033[1;1f", Bg_color);
    }
    auto Console::setBgColor(i32 color) -> void
    {
        Bg_color = 40 + (color % 16);
    }
    auto Console::setFgColor(i32 color) -> void
    {
        Fg_color = 30 + (color % 16);
    }
    auto Console::printBgColor(i32 color) -> void
    {
        constexpr i32 offset = 30;
        constexpr i32 bright_offset = 60;

        printf("\033[%d;%dm", (color < 16) ? offset : bright_offset, Bg_color + color % 16);
    }
    auto Console::printFgColor(i32 color) -> void
    {
        constexpr i32 offset = 30;
        constexpr i32 bright_offset = 90;
        constexpr i32 fg_colors[] = {
            0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15
        };

        printf("\033[%d;%dm", (color < 16) ? offset : bright_offset, fg_colors[color % 16] + Fg_color);
    }
    auto Console::printColor(i32 fg, i32 bg) -> void
    {
        constexpr i32 offset = 30;
        constexpr i32 bright_offset = 60;
        constexpr i32 fg_colors[] = {
            0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15
        };

        printf("\033[%d;%d;%dm",
               (bg < 16) ? bright_offset : offset,
               fg_colors[fg % 16] + Console::Fg_color,
               Console::Bg_color + bg % 16);
    }
    auto Console::ungetChar(i32 ch) -> i32
    {
        return ungetc(ch, stdin);
    }
    auto Console::getChar(bool echo) -> i32
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
    auto Console::getXy(i32& x, i32& y) -> i32
    {
        constexpr i8 seq[] = "\033[6n";
        constexpr i8 end[] = "R";
        constexpr size_t seq_len = sizeof(seq) - 1;
        constexpr size_t end_len = sizeof(end) - 1;

        write(STDOUT_FILENO, seq, seq_len);

        i8 buf[256];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));

        if (len <= seq_len || std::memcmp(buf, seq, seq_len) != 0)
        {
            return 0;
        }

        i8p p = buf + seq_len;
        i8p end_p = memchr<i8p>(p, end[0], len - seq_len);
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
    auto Console::getX() -> i32
    {
        i32 x = 0;
        i32 y = 0;
        getXy(x, y);
        return x;
    }
    /**
     * Get the Y coordinate from the Console.
     *
     * @return the Y coordinate value
     */
    auto Console::getY() -> i32
    {
        i32 x = 0;
        i32 y = 0;
        getXy(x, y);
        return y;
    }

    /**
     * If there are bytes available, enable cannonical and echo modes
     * so that the next read call retrieves the keypress
     */
    auto Console::keyHit() -> i32
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
    auto Console::printChar(const i8 c) -> i8
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
    auto Console::printStr(const string& str) -> i32
    {
        printf("%s", str.c_str());
        return 0;
    }
    auto Console::printStrColor(const string& str, i32 fg, i32 bg) -> i32
    {
        setFgColor(fg);
        setBgColor(bg);
        printStr(str);
        setFgColor(WHITE);
        setBgColor(BLACK);
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
    auto Console::changeColor(i32 fg, i32 bg) -> i32
    {
        printf("\033[%d;%dm", fg + 30, bg + 40);
        return 0;
    }
    auto Console::changeColor(i32 color) -> i32
    {
        return changeColor(color % 16, color / 16);
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
    auto Console::printCStr(const i8* str) -> i32
    {
        printf("%s", str);
        return 0;
    }
    auto Console::getHome() -> string
    {
        return getenv("HOME");
    }
    auto Console::getCwd() -> string
    {
        i8 cwd[1024];
        return getcwd(cwd, sizeof(cwd));
    }
    auto Console::getUser() -> string
    {
        return cuserid(nullptr);
    }
    /**
     * Get the hostname of the system.
     *
     * @return The hostname as a string
     */
    auto Console::getHostname() -> string
    {
        i8 hostname[1024];
        gethostname(hostname, sizeof(hostname));
        return hostname;
    }
    auto Console::isValidPass(const string& passwd) -> bool
    {
        return (passwd.length() > 0 && passwd.length() <= 32 && passwd.find_first_not_of("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz./") == string::npos);
    }
    auto Console::getPass(const string& prompt) -> string
    {
        string passwd;
        passwd.resize(32);
        for (i32 i = 3; i >= 0; i--)
        {
            std::cout << prompt;
            std::cin >> passwd;
            if (isValidPass(passwd))
            {
                return passwd;
                break;
            };
        }
        return "";
    }
    auto Console::getEnv(const string& name) -> string
    {
        return getenv(name.c_str());
    }
    auto Console::readText(i32 l, i32 t, i32 r, i32 b, void* destination)
        -> size_t
    {
        printf("\033[%d;%d;%d;%dH", b, t, r, l);
        if (fflush(stdout) == EOF)
        {
            return 0;
        }
        return fread(destination, 1, static_cast<size_t>(l * t) * r, stdin);
    }
    auto Console::writeText(i32 l, i32 t, i32 r, i32 b, void* source) -> size_t
    {
        printf("\033[%d;%d;%d;%dH", b, t, r, l);
        if (fflush(stdout) == EOF)
        {
            return 0;
        };
        return fwrite(source, 1, static_cast<size_t>(l * t) * r, stdout);
    }
} // namespace origin