#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include "Basic.hpp"
#include <sstream>

#include <string>

#ifndef ASSERT_ENABLED
#define ASSERT_ENABLED true
#endif
namespace Origin
{
    enum class Code : i8
    {
        any = 0,
        info = 1,
        warning = 2,
        error = 3,
        fatal = 4,
        none = 5
    };
    struct Message
    {
        Code code = Code::any;
        Code status = Code::info;
        Code offset = Code::none;
        Code level = Code::none;
        std::string header;
        std::string mesg;
        std::string footer;
    } __attribute__((aligned(128)));
    static Message msg;
    auto get_header_txt() -> std::string;
    auto get_end_txt(std::string begin, i8 padding, std::string ending) -> std::string;
    auto get_info_txt(std::string info) -> std::string;
    auto get_footer_txt() -> std::string;
    auto get_code() -> Code;
    auto set_code(Code code) -> Code;
    auto is(Code status) -> bool;
    auto reset() -> void;
    auto set_status(Code status) -> Code;
    auto set_level(Code level) -> Code;
    auto get_level() -> Code;
    auto get_status() -> Code;

    auto set_offset(Code offset) -> Code;

#define get_file_txt() ("#-File: [ " + std::string(__FILE__) + " ]")
#define get_function_txt() ("#-Function: [ " + std::string(__PRETTY_FUNCTION__) + " ]")
#define get_line_txt() ("#-Line: [ " + std::to_string(__LINE__) + " ]")
#define get_time_txt() ("#-Time: [ " + std::string(__TIME__) + " ]")

#define HEADER_TXT get_header_txt() + '\n'
#define FILE_TXT_BEGIN get_file_txt()
#define FILE_TXT (FILE_TXT_BEGIN + get_end_txt(get_file_txt(), ' ', "#"))
#define LINE_TXT_BEGIN get_line_txt()
#define LINE_TXT (LINE_TXT_BEGIN + get_end_txt(LINE_TXT_BEGIN, ' ', "#"))
#define FUNCTION_TXT_BEGIN get_function_txt()
#define FUNCTION_TXT (FUNCTION_TXT_BEGIN + get_end_txt(FUNCTION_TXT_BEGIN, ' ', "#"))
#define TIME_TXT_BEGIN get_time_txt()
#define TIME_TXT (TIME_TXT_BEGIN + get_end_txt(TIME_TXT_BEGIN, ' ', "#"))
#define INFO_TXT(mesg) get_info_txt(mesg)
#define FOOTER_TXT_BEGIN get_footer_txt()
#define FOOTER_TXT (FOOTER_TXT_BEGIN + get_end_txt(FOOTER_TXT_BEGIN, '#', "#"))
#define MSG(mesg) (HEADER_TXT + FILE_TXT + FUNCTION_TXT + LINE_TXT + TIME_TXT + INFO_TXT(mesg) + FOOTER_TXT)
#define DBG(mesg, status)                                                                \
    set_status(status);                                                                  \
    switch (status)                                                                      \
    {                                                                                    \
    case Code::any:                                                                      \
        if (is(Code::any))                                                               \
        {                                                                                \
            std::cout << MSG(mesg) << "\n";                                              \
            set_code(status);                                                            \
        }                                                                                \
        break;                                                                           \
    case Code::info:                                                                     \
        if (is(Code::info))                                                              \
        {                                                                                \
            std::cout << MSG(mesg) << "\n";                                              \
            set_code(Code::info);                                                        \
        }                                                                                \
        break;                                                                           \
    case Code::warning:                                                                  \
        if (is(Code::warning))                                                           \
        {                                                                                \
            std::cout << MSG(mesg) << "\n";                                              \
            set_code(Code::warning);                                                     \
        }                                                                                \
        break;                                                                           \
    case Code::error:                                                                    \
        if (is(Code::error))                                                             \
        {                                                                                \
            std::cout << MSG(mesg) << "\n";                                              \
            set_code(Code::error);                                                       \
        }                                                                                \
        break;                                                                           \
    case Code::fatal:                                                                    \
        if (is(Code::fatal))                                                             \
        {                                                                                \
            std::cout << MSG(mesg) << "\n";                                              \
            set_code(Code::fatal);                                                       \
        }                                                                                \
        break;                                                                           \
    case Code::none:                                                                     \
        if (is(Code::none))                                                              \
        {                                                                                \
            set_code(Code::none);                                                        \
        }                                                                                \
        break;                                                                           \
    default:                                                                             \
        std::cout << MSG("ERROR: Invalid status Code: " + std::to_string((i32)(status))) \
                  << "\n";                                                               \
        set_code(Code::error);                                                           \
        break;                                                                           \
    }
#define debug(mesg, status) DBG(mesg, status)
#undef assert
#define assert(condition, mesg)           \
    if (!(condition) && (ASSERT_ENABLED)) \
    {                                     \
        DBG(mesg, Code::error);           \
    }
} // namespace Origin

#endif // MSG_HPP