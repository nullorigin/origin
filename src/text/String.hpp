#pragma once
#include "Basic.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <valarray>
namespace origin
{
    template<typename X, typename Y>
    class KeyVal
    {
    private:
        std::valarray<X> Key = std::valarray<X>();
        std::valarray<Y> Val = std::valarray<Y>();

    public:
        KeyVal<X, Y>& operator=(KeyVal<X, Y>&& other) noexcept
        {
            Key = std::move(other.Key);
            Val = std::move(other.Val);
            return *this;
        }
        auto& operator=(const KeyVal<X, Y>& other)
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
    static auto ToLower(const string& str) -> string
    {
        string ret = str;
        std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
        return ret;
    }

    static auto ToUpper(const string& str) -> string
    {
        string ret = str;
        std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
        return ret;
    }
    static auto Trim(const string& str) -> string
    {
        return str.substr(0, str.length() - 1);
    }
    static auto Trim(const string& begin, const string& end, const string& str) -> string
    {
        size_t start = str.find_first_not_of(begin);
        size_t end_it = str.find(end) - 1;

        if (start == string::npos || end_it == string::npos)
        {
            return "";
        }

        return str.substr(start, end_it - start + 1);
    }

    static auto Trim(const size_t n, const string& str) -> string
    {
        return Trim(str.substr(n, str.length() - n - 1));
    }
    static auto Trim(const size_t start, const string& end, const string& str) -> string
    {
        if (start == string::npos || end.length() > str.length())
        {
            return "";
        }

        size_t end_it = str.find_last_not_of(end) - end.length() - 1;
        if (end_it == string::npos)
        {
            end_it = 0;
        }
        else
        {
            ++end_it;
        }

        return Trim(str.substr(start, end_it - start));
    }
    static auto Trim(const string& start, const size_t end, const string& str) -> string
    {
        if (end == string::npos || start.length() > str.length())
        {
            return "";
        }

        size_t start_it = str.find_first_of(start) + start.length() + 1;
        if (start_it == string::npos)
        {
            start_it = 0;
        }
        else
        {
            --start_it;
        }
        return Trim(str.substr(start_it, end - start_it));
    }
    static auto Replace(const string& from_str, const string& to_str, const string& str) -> string
    {
        string result;
        result.reserve(str.length());
        size_t pos = 0;
        size_t prev_pos = 0;
        while ((pos = str.find(from_str, pos)) != string::npos)
        {
            result.append(str, prev_pos, pos - prev_pos);
            result += to_str;
            pos += from_str.length();
            prev_pos = pos;
        }
        result += str.substr(prev_pos);
        return result;
    }
    static auto Replace(const string& search, const string& repl, const string& file_name, u32 retries) -> string
    {
        string result;
        bool success = false;
        u32 retries_count = retries;
        std::fstream file(file_name, std::fstream::in | std::fstream::out | std::fstream::trunc);
        while (!success && retries_count > 0)
        {
            file.open(file_name, std::fstream::in | std::fstream::out | std::fstream::trunc);
            if (file.is_open())
            {
                try
                {
                    (file.seekp(0, std::ios::end));
                    result.resize(file.tellp());
                    file << Replace(search, repl, result);
                    file.seekp(0, std::ios::beg);
                    file << result;
                    success = true;
                }
                catch (std::exception& e)
                {
                    if (file.is_open())
                    {
                        file.close();
                    }
                    retries_count--;
                    continue;
                }
            }
            else
            {
                retries_count--;
            }
        }
        return result;
    }
    static auto Clean(string str, u32 flags)
    {
        auto dst = str.begin();
        for (char& src : str)
        {
            if ((src >= '\0' && src <= '\n') ||
                (flags == 1 && (src >= '0' && src <= '9')))
            {
                *dst++ = ' ';
            }
            else
            {
                *dst++ = src;
            }
        }
        str.erase(dst, str.end());
        return str;
    }

    static auto Length(const string& str) -> u64
    {
        return str.size();
    }
    static auto Format(const string& str, u32 flags) -> string
    {
        u64 len = str.size();
        string out;
        out.resize(len);
        auto p = out.begin();
        auto s = str.cbegin();
        for (; s != str.cend(); ++s, ++p)
        {
            if ((flags == 1 && (isdigit(*s) == 0)) ||
                (flags == 2 && (isdigit(*s) == 0)) ||
                (flags == 3 && (islower(*s) == 0)) ||
                (flags == 4 && (isupper(*s) == 0)) ||
                (*s >= '\0' && *s <= '\n'))
            {
                *p = ' ';
            }
            else
            {
                *p = *s;
            }
        }
        return out;
    }

    static void Copy(i8p dest, const i8* src)
    {
        memcpy(dest, src, strlen(src) + 1);
    }

    static auto Concatenate(const string& first, const string& second) -> string
    {
        const auto first_len = first.size();
        const auto second_len = second.size();
        string result;
        result.reserve(first_len + second_len);
        result.append(first);
        result.append(second);
        return result;
    }

    static auto Concatenate(const string& first, const string& second, const string& third) -> string
    {
        const auto first_len = first.size();
        const auto second_len = second.size();
        const auto third_len = third.size();
        string result;
        result.reserve(first_len + second_len + third_len);
        result.append(first);
        result.append(second);
        result.append(third);
        return result;
    }
    static auto Erase(string& str, const string& toErase) -> string&
    {
        return str.erase(0, str.find(toErase) + toErase.length());
    }
    static auto EraseAll(string& str, const string& toErase) -> string&
    {
        auto last_pos = str.find_first_not_of(toErase);
        auto pos = str.find_first_of(toErase, last_pos);
        while (string::npos != pos || string::npos != last_pos)
        {
            str.erase(pos, toErase.length());
            last_pos = pos + 1;
            pos = str.find_first_of(toErase, last_pos);
        }
        return str;
    }
    inline auto NumDigits(f128 num, string& buf) -> f128
    {
        f128 ret = floor(log10(num) + 1);
        buf = std::to_string(static_cast<u64>(ret));
        return ret;
    }

    inline auto ToString(f128 num, u32 precision = 0) -> string
    {
        string buffer(38, '\0');
        string digits(38, '\0');
        if (precision == 0 || precision > 38)
        {
            precision = static_cast<u32>(NumDigits(num, digits));
        }
        std::stringstream ss;
        ss.precision(precision);
        ss.flags(std::ios_base::dec | std::ios_base::fixed);
        ss << (num / 1000000000.0);
        ss >> buffer;
        return buffer;
    }
} // namespace origin