#pragma once
#ifndef STRING_HPP
#define STRING_HPP
#include <string>
#include "Basic.hpp"
namespace origin
{
    class KeyValue
    {
    public:
        i8p key;
        i8p val;
    };
    class string : public std::string
    {
    private:
        union
        {
            i8p data[2] = { i8p(nullptr), i8p(nullptr) };
            struct
            {
                i8p val;
                i8p key;
            };
        };

    public:
        explicit string(KeyValue* keyval)
        {
            key = keyval->key;
            val = keyval->val;
        }

        explicit string(i8p str)
        {
            val = str;
            key = nullptr;
        }

        auto Val(u64 index) const -> i8
        {
            return val[index];
        }
        auto Key(u64 index) const -> i8
        {
            return key[index];
        }
        auto Val() const -> i8p
        {
            return val;
        }
        auto Key() const -> i8p
        {
            return key;
        }

        string();
        string(const string& str) :
            std::string(str)
        {
        }
        string(string&&) noexcept :
            std::string(*this){};
        auto operator=(string&&) -> string& = default;
        auto operator=(const string& str) -> string&
        {
            return *this = string(str);
        }
        explicit operator i8p()
        {
            i8p ret = new i8[strlen(*data) + 1];
            strcpy(ret, *data);
            return ret;
        }
        ~string()
        {
            delete[] *data;
        }

        static auto Replacei8p(const i8p from_str, const i8p to_str, const i8p str) -> string
        {
            i8p replaced = new i8[strlen(str) + 1];
            strcpy(replaced, str);
            for (i8p _p = replaced; (_p = strchr(_p, from_str[0])) != nullptr;)
            {
                *_p++ = to_str[0];
            }

            return { replaced, strlen(replaced) };
        }

        using callback = bool (*)(i8);

        static auto Replacei8p(const i8p from[2], const i8p str, callback func)
            -> string
        {
            i8p target = const_cast<i8p>(str);
            const i8p end = target + strlen(str);
            while (target != end && ((target = static_cast<i8p>(memchr(target, from[0][0], end - target))) != nullptr))
            {
                if (func(*target) && *target == from[0][0])
                {
                    *target = from[0][1];
                }
                ++target;
            }
            return { const_cast<i8p>(str), static_cast<u32>(strlen(str)) };
        }

        static i8p Cleani8p(i8p str, u32 flags)
        {
            i8p dst = str;
            for (i8p src = str; *src != '\0'; ++src)
            {
                if ((*src >= '\0' && *src <= '\n') ||
                    (flags == 1 && (*src >= '0' && *src <= '9')))
                {
                    *dst++ = ' ';
                }
                else
                {
                    *dst++ = *src;
                }
            }
            *dst = '\0';
            return str;
        }
        explicit string(u64 length) :
            data{ new i8[length + 1] }
        {
            std::memset(data, 0, length + 1);
        }

        string(i8p _data, u64 _length);
        static auto Lengthi8p(const i8p str) -> u64
        {
            return *str != 0 ? strlen(str) : 0;
        }
        static auto Formati8p(i8p str, u32 flags) -> string
        {
            u64 len = strlen(str);
            i8p out = static_cast<i8p>(memccpy(nullptr, str, ' ', len));
            for (i8p p = out; *p != '\0'; ++p)
            {
                if ((flags == 1 && (isdigit(*p) == 0)) ||
                    (flags == 2 && (isdigit(*p) == 0)) ||
                    (flags == 3 && (islower(*p) == 0)) ||
                    (flags == 4 && (isupper(*p) == 0)) ||
                    (*p >= '\0' && *p <= '\n'))
                {
                    *p = ' ';
                }
            }
            return { out, static_cast<u32>(len) };
        }

        static void Copyi8p(i8p __restrict dest, const i8p __restrict src)
        {
            memcpy(dest, src, strlen(src) + 1);
        }

        static auto Concatenatei8p(const i8p s1, const i8p s2) -> i8p
        {
            const auto len1 = strlen(s1);
            const auto len2 = strlen(s2);
            auto* result = static_cast<i8p>(malloc(len1 + len2 + 1));
            if (result == nullptr)
            {
                throw std::bad_alloc{};
            }
            strcpy(result, s1);
            memcpy(result + len1, s2, len2 + 1);
            return result;
        }

        auto operator=(const i8p* str) -> string { return { string(*str) }; }
        auto operator+(const string& str1) -> string
        {
            string ret = *this;
            ret += str1;
            return { ret };
        }
    };

} // namespace origin
#endif