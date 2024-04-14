#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

#ifndef MESSAGE_HPP
#define MESSAGE_HPP
namespace origin {
static const int NONE = 0;
static const int INFO = 1;
static const int WARNING = 2;
static const int ERROR = 3;
static const int FATAL = 4;
static int MsgStatus;
static int MsgOffset;
static int MsgLevel;
static std::string MsgHeader;
auto GetHeader() -> std::string;
auto IsNone() -> bool;
auto IsInfo() -> bool;
auto IsWarning() -> bool;
auto IsError() -> bool;
auto IsFatal() -> bool;
void Restart();
auto SetStatus(int status) -> int;
auto SetLevel(int level) -> int;
auto SetOffset(int offset) -> int;
auto GetEnd(std::string begin, char padding = ' ', char ending = '#')
    -> std::string;
#define SET_LEVEL(level) SetLevel((int)level)
#define SET_STATUS(status) SetStatus((int)status)
#define SET_OFFSET(offset) SetOffset((int)offset)
#define HEADER_TXT (GetHeader() + "\n")
#define FILE_TXT ("#-File: [ " + (std::string)(__FILE__) + " ]")
#define FUNCTION_TXT                                                           \
  ("#-Function: [ " + (std::string)(__PRETTY_FUNCTION__) + " ]")
#define LINE_TXT ("#-Line: [ " + (std::to_string(__LINE__)) + " ]")
#define INFO_TXT(info) ("#-Info: [ " + (std::string)(info) + " ]")
#define TIME_TXT ("#-Time: [ " + (std::string)(__TIME__) + " ]")
#define PAD_TXT "##########################"
#define MSG(info)                                                              \
  ((HEADER_TXT) + (FILE_TXT) + GetEnd(FILE_TXT) + (FUNCTION_TXT) +             \
   GetEnd(FUNCTION_TXT) + (LINE_TXT) + GetEnd(LINE_TXT) + (TIME_TXT) +         \
   GetEnd(TIME_TXT) + INFO_TXT((std::string)(info)) + GetEnd(INFO_TXT(info)) + \
   (PAD_TXT) + GetEnd(PAD_TXT, '#', '#'))
#define DBG(info, status)                                                      \
  SetStatus((int)(status));                                                    \
  switch ((int)(status)) {                                                     \
  case INFO:                                                                   \
    if (IsInfo()) {                                                            \
      std::cout << MSG(info) << "\n";                                          \
    }                                                                          \
    break;                                                                     \
  case WARNING:                                                                \
    if (IsWarning()) {                                                         \
      std::cout << MSG(info) << "\n";                                          \
    }                                                                          \
    break;                                                                     \
  case ERROR:                                                                  \
    if (IsError()) {                                                           \
      std::cout << MSG(info) << "\n";                                          \
    }                                                                          \
    break;                                                                     \
  case FATAL:                                                                  \
    if (IsFatal()) {                                                           \
      std::cout << MSG(info) << "\n";                                          \
    }                                                                          \
    break;                                                                     \
  case NONE:                                                                   \
    break;                                                                     \
  default:                                                                     \
    break;                                                                     \
  }

} // namespace origin
#endif // MSG_HPP