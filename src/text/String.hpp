#pragma once
#ifndef STRING_HPP
#define STRING_HPP
#include "Basic.hpp"
#include <cctype>
#include <cstring>
#include <ios>
#include <sstream>
#include <string>
#include <valarray>
namespace origin
{
    class string;
    template<typename X, typename Y>
    class KeyVal
    {
    public:
        std::valarray<X> Key = std::valarray<X>();
        std::valarray<Y> Val = std::valarray<Y>();
        KeyVal<X, Y>& operator=(KeyVal<X, Y>&& other) noexcept
        {
            Key = std::move(other.Key);
            Val = std::move(other.Val);
            return *this;
        }
        KeyVal<X, Y>& operator=(const KeyVal<X, Y>& other) noexcept
        {
            Key = other.Key;
            Val = other.Val;
            return *this;
        }
        KeyVal<X, Y>(KeyVal<X, Y>&& other) noexcept :
            Key(std::move(other.Key)),
            Val(std::move(other.Val))
        {
            other.Key = std::valarray<X>(0);
            other.Val = std::valarray<Y>(0);
        }
        KeyVal<X, Y>(const KeyVal<X, Y>& other) noexcept :
            Key(other.Key),
            Val(other.Val) {}
        explicit KeyVal<X, Y>(const std::valarray<X>& key, const std::valarray<Y>& val) :
            Key(std::valarray<X>(key)), Val(std::valarray<X>(val))
        {
        }
        KeyVal<X, Y>() :
            Key(std::valarray<X>(0)), Val(std::valarray<Y>(0))
        {
        }
        ~KeyVal<X, Y>() = default;
    };
    static auto Replacei8p(const i8p from_str, const i8p to_str, const i8p str) -> i8p
    {
        i8p replaced = const_cast<i8p>(str);
        strcpy(replaced, str);
        for (i8p _p = replaced; (_p = strchr(_p, from_str[0])) != nullptr;)
        {
            *_p++ = to_str[0];
        }

        return replaced;
    }

    using callback = bool (*)(i8);

    static auto Replacei8p(const i8p from[2], const i8p str, callback func)
        -> i8p
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
        return str;
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
    static auto Lengthi8p(const i8p str) -> u64
    {
        return *str != 0 ? strlen(str) : 0;
    }
    static auto Formati8p(i8p str, u32 flags) -> i8p
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
        return out;
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
        strcpy(result, s1);
        memcpy(result + len1, s2, len2 + 1);
        return result;
    }
    class string : public std::basic_string<i8>, public std::basic_stringstream<i8>
    {
    public:
        string() :
            std::basic_stringstream<i8>(std::ios_base::in | std::ios_base::out)
        {
            std::basic_string<i8>::operator=("");
            this->sync();
        }
        string(i8p str) :
            std::basic_string<i8>(str), std::basic_stringstream<i8>(str)
        {
            this->sync();
        }
        string(const string& other) :
            std::basic_string<i8>(other), std::basic_stringstream<i8>(other.str())
        {
            this->sync();
        }
        string(const std::basic_string<i8>& str) :
            std::basic_string<i8>(str), basic_stringstream<i8>(ios_base::in | ios_base::out)
        {
            this->str(str);
            this->sync();
        }
        auto operator=(const std::basic_string<i8>& rhs) noexcept -> string&
        {
            std::basic_string<i8>::operator=(rhs);
            this->str(rhs);
            this->sync();
            return *this;
        }

        auto operator=(const string& rhs) noexcept -> string&
        {
            std::basic_string<i8>::operator=(rhs);
            this->str(rhs.str());
            this->sync();
            return *this;
        }

        auto operator=(const i8p& rhs) noexcept -> string&
        {
            std::basic_string<i8>::operator=(rhs);
            this->str(rhs);
            this->sync();
            return *this;
        }
        auto operator+(const string& rhs) const -> string
        {
            string ret = *this;
            ret = (ret.str() + rhs.str());
            return ret;
        }

        auto operator+(const i8p& rhs) const -> string
        {
            string ret = *this;
            ret = (ret.str() + rhs);
            ret.sync();
            return ret;
        }
        auto operator+(const std::basic_string<i8>& rhs) const -> string
        {
            string ret = *this;
            ret = (ret.str() + rhs);
            ret.sync();
            return ret;
        }

        auto operator+=(const string& rhs) -> string&
        {
            this->str(this->str() + rhs.str());
            this->sync();
            return *this;
        }

        auto operator+=(const i8p& rhs) -> string&
        {
            this->str(this->str() + rhs);
            this->sync();
            return *this;
        }

        auto operator+=(const std::basic_string<i8>& rhs) -> string&
        {
            this->str(this->str() + rhs);
            this->sync();
            return *this;
        }
        string operator<<=(const i8p& rhs)
        {
            this->str(rhs + this->str());
            this->sync();
            std::basic_string<i8>::operator=(this->str());
            return *this;
        }

        string operator>>=(const i8p& rhs)
        {
            this->str(this->str() + rhs);
            this->sync();
            std::basic_string<i8>::operator=(this->str());
            return *this;
        }
        i8(*data(string& str0))
        {
            i8p ret = { new i8[this->size() + 1] };
            memcpy(ret, str0.c_str(), this->size() + 1);
            this->str(ret);
            return ret;
        }
    };
    inline string operator"" _(const char* str9, unsigned long size)
    {
        size = strlen(str9);
        string ret = (string(str9));
        return ret;
    }
} // namespace origin
#endif