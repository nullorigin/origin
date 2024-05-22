#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include "Basic.hpp"

#include <string>

#ifndef ASSERT_ENABLED
#define ASSERT_ENABLED true
#endif
namespace origin {
enum class Code : i8 {
  False = 0,
  True = 1,
  Failure = 0,
  Success = 1,
  Any = 0,
  Info = 1,
  Warning = 2,
  Error = 3,
  Fatal = 4,
  None = 5,
  Uninitialized = 0,
  Initializing = 1,
  Initialized = 2,
  Starting = 3,
  Started = 4,
  Pausing = 5,
  Paused = 6,
  Resuming = 7,
  Resumed = 8,
  Stopping = 9,
  Stopped = 10,
  Restarting = 11,
  Restarted = 12,
  Exiting = 13,
  Exited = 14,
  Killing = 15,
  Killed = 16
};
struct Message {
  Code code = Code::Any;
  Code status = Code::Info;
  Code offset = Code::None;
  Code level = Code::None;
  std::string header;
  std::string mesg;
  std::string footer;
} __attribute__((aligned(128)));
static Message msg;
auto getHeaderTxt() -> std::string;
auto getEndTxt(const std::string &begin, const i8 &padding, const i8 &ending,
               bool include_ending = true) -> std::string;
auto getInfoTxt(const std::string &info) -> std::string;
auto getFooterTxt() -> std::string;
auto getCode() -> Code;
auto setCode(Code code) -> Code;
auto is(Code status) -> bool;
auto reset() -> void;
auto setStatus(Code status) -> Code;
auto setLevel(Code level) -> Code;
auto getLevel() -> Code;
auto getStatus() -> Code;

auto setOffset(Code offset) -> Code;

#define get_file_txt() ("#-File: [ " + std::string(__FILE__) + " ]")
#define get_function_txt()                                                     \
  ("#-Function: [ " + std::string(__PRETTY_FUNCTION__) + " ]")
#define get_line_txt() ("#-Line: [ " + std::to_string(__LINE__) + " ]")
#define get_time_txt() ("#-Time: [ " + std::string(__TIME__) + " ]")

#define HEADER_TXT getHeaderTxt() + '\n'
#define FILE_TXT_BEGIN get_file_txt()
#define FILE_TXT (FILE_TXT_BEGIN + getEndTxt(get_file_txt(), ' ', '#'))
#define LINE_TXT_BEGIN get_line_txt()
#define LINE_TXT (LINE_TXT_BEGIN + getEndTxt(LINE_TXT_BEGIN, ' ', '#'))
#define FUNCTION_TXT_BEGIN get_function_txt()
#define FUNCTION_TXT                                                           \
  (FUNCTION_TXT_BEGIN + getEndTxt(FUNCTION_TXT_BEGIN, ' ', '#'))
#define TIME_TXT_BEGIN get_time_txt()
#define TIME_TXT (TIME_TXT_BEGIN + getEndTxt(TIME_TXT_BEGIN, ' ', '#'))
#define INFO_TXT(mesg) getInfoTxt(mesg)
#define FOOTER_TXT_BEGIN getFooterTxt()
#define FOOTER_TXT (FOOTER_TXT_BEGIN + getEndTxt(FOOTER_TXT_BEGIN, '#', '#'))
#define MSG(mesg)                                                              \
  (HEADER_TXT + FILE_TXT + FUNCTION_TXT + LINE_TXT + TIME_TXT +                \
   INFO_TXT(mesg) + FOOTER_TXT)
#define DBG(mesg, status)                                                      \
  setStatus(status);                                                           \
  switch (status) {                                                            \
  case Code::Any:                                                              \
    if (is(Code::Any)) {                                                       \
      std::cout << MSG(mesg) << "\n";                                          \
      setCode(status);                                                         \
    }                                                                          \
    break;                                                                     \
  case Code::Info:                                                             \
    if (is(Code::Info)) {                                                      \
      std::cout << MSG(mesg) << "\n";                                          \
      setCode(Code::Info);                                                     \
    }                                                                          \
    break;                                                                     \
  case Code::Warning:                                                          \
    if (is(Code::Warning)) {                                                   \
      std::cout << MSG(mesg) << "\n";                                          \
      setCode(Code::Warning);                                                  \
    }                                                                          \
    break;                                                                     \
  case Code::Error:                                                            \
    if (is(Code::Error)) {                                                     \
      std::cout << MSG(mesg) << "\n";                                          \
      setCode(Code::Error);                                                    \
    }                                                                          \
    break;                                                                     \
  case Code::Fatal:                                                            \
    if (is(Code::Fatal)) {                                                     \
      std::cout << MSG(mesg) << "\n";                                          \
      setCode(Code::Fatal);                                                    \
    }                                                                          \
    break;                                                                     \
  case Code::None:                                                             \
    if (is(Code::None)) {                                                      \
      setCode(Code::None);                                                     \
    }                                                                          \
    break;                                                                     \
  default:                                                                     \
    std::cout << MSG("ERROR: Invalid status Code: " +                          \
                     std::to_string((i32)(status)))                            \
              << "\n";                                                         \
    setCode(Code::Error);                                                      \
    break;                                                                     \
  }
#define debug(mesg, status) DBG(mesg, status)
#undef assert
#define assert(condition, mesg)                                                \
  if (!(condition) && (ASSERT_ENABLED)) {                                      \
    DBG(mesg, Code::Error);                                                    \
  }
} // namespace origin

#endif // MSG_HPP