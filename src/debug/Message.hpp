#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include "Basic.hpp"
#include <string>
namespace Origin
{
    using ExCode = enum ExLevel : i32 {
        ANY = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        FATAL = 4,
        NONE = 5,
    };
    static ExCode MsgCode = NONE;
    static ExCode MsgStatus = INFO;
    static ExLevel MsgOffset = NONE;
    static ExLevel MsgLevel = NONE;
    static std::string MsgHeader;
    static std::string MsgInfo = " ";
    auto ToString(const i8* str) -> std::string;
    auto GetStringEnd(const std::string& begin, i8 padding, i8 ending) -> std::string;
    auto GetHeader() -> std::string;
    inline auto GetCode() -> ExCode
    {
        return MsgCode;
    };
    auto SetCode(ExCode code) -> ExCode;
    inline auto IsAny() -> bool
    {
        return MsgLevel == ANY;
    };
    inline auto IsInfo() -> bool
    {
        return MsgStatus == INFO;
    };
    inline auto IsWarning() -> bool
    {
        return MsgStatus == WARNING;
    };
    inline auto IsError() -> bool
    {
        return MsgStatus == ERROR;
    };
    inline auto IsFatal() -> bool
    {
        return MsgStatus == FATAL;
    };
    inline auto IsNone() -> bool
    {
        return MsgStatus == NONE;
    };
    auto Restart() -> void;
    auto SetStatus(ExCode status) -> ExCode;
    auto SetLevel(ExLevel level) -> ExLevel;
    auto SetOffset(ExLevel offset) -> ExLevel;
    auto GetStringEnd(std::string begin, i32 padding = ' ', i32 ending = '#')
        -> std::string;
#define SET_LEVEL(level) SetLevel(level)
#define SET_STATUS(status) SetStatus(status)
#define SET_OFFSET(offset) SetOffset(offset)
#define HEADER_TXT GetHeader() + "\n"
#define FILE_TXT (ToString("#-File: [ ") + (__FILE__) + ToString(" ]"))
#define FUNCTION_TXT \
    ToString("#-Function: [ ") + (__PRETTY_FUNCTION__) + ToString(" ]")
#define LINE_TXT \
    ToString("#-Line: [ ") + (std::to_string(__LINE__)) + ToString(" ]")
    inline auto INFO_TXT(const std::string& info) -> std::string
    {
        return "#-Info: [ " + info + " ]";
    }
#define TIME_TXT ToString("#-Time: [ ") + ToString(__TIME__) + ToString(" ]")
    constexpr auto PAD_TXT = "##########################";
#define MSG(info)                                                                         \
    ((HEADER_TXT) + FILE_TXT + GetStringEnd(FILE_TXT, ' ', '#') + FUNCTION_TXT +          \
     GetStringEnd(FUNCTION_TXT, ' ', '#') + LINE_TXT + GetStringEnd(LINE_TXT, ' ', '#') + \
     TIME_TXT + GetStringEnd(TIME_TXT, ' ', '#') + INFO_TXT(info) +                       \
     GetStringEnd(INFO_TXT(info), ' ', '#') + PAD_TXT + GetStringEnd(PAD_TXT, '#', '#'))
#define DBG(info, status)                                                         \
    SetStatus(status);                                                            \
    switch (status)                                                               \
    {                                                                             \
    case ANY:                                                                     \
        if (IsAny())                                                              \
        {                                                                         \
            std::cout << MSG(info) << "\n";                                       \
            SetCode(status);                                                      \
        }                                                                         \
        break;                                                                    \
    case INFO:                                                                    \
        if (IsInfo())                                                             \
        {                                                                         \
            std::cout << MSG(info) << "\n";                                       \
            SetCode(INFO);                                                        \
        }                                                                         \
        break;                                                                    \
    case WARNING:                                                                 \
        if (IsWarning())                                                          \
        {                                                                         \
            std::cout << MSG(info) << "\n";                                       \
            SetCode(WARNING);                                                     \
        }                                                                         \
        break;                                                                    \
    case ERROR:                                                                   \
        if (IsError())                                                            \
        {                                                                         \
            std::cout << MSG(info) << "\n";                                       \
            SetCode(ERROR);                                                       \
        }                                                                         \
        break;                                                                    \
    case FATAL:                                                                   \
        if (IsFatal())                                                            \
        {                                                                         \
            std::cout << MSG(info) << "\n";                                       \
            SetCode(FATAL);                                                       \
        }                                                                         \
        break;                                                                    \
    case NONE:                                                                    \
        if (IsNone())                                                             \
        {                                                                         \
            SetCode(NONE);                                                        \
        }                                                                         \
        break;                                                                    \
    default:                                                                      \
        std::cout << MSG("ERROR: Invalid status code: " + std::to_string(status)) \
                  << "\n";                                                        \
        SetCode(ERROR);                                                           \
        break;                                                                    \
    }
} // namespace origin
#endif // MSG_HPP