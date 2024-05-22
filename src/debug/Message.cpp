#include "Message.hpp"
#include <string>

namespace origin {
auto getHeaderTxt() -> std::string {
  const std::string header[6] = {"[--NONE--]",  "[--INFO--]",  "[-WARNING-]",
                                 "[--ERROR--]", "[--FATAL--]", "[--NONE--]"};
  msg.header = std::string(50, '#') + header[cast<i32>(msg.status)] +
               std::string(50, '#');
  return msg.header;
}

auto getEndTxt(const std::string &begin, const i8 &padding, const i8 &ending,
               bool include_ending) -> std::string {

  std::string end;
  if (msg.header.size() > begin.size()) {
    end = std::string(msg.header.size() - begin.size() - 1, ' ');
  } else {
    end = "";
  }
  if (include_ending) {
    end += std::string(1, ending);
  }
  return end + '\n';
}
auto setCode(Code code) -> Code {
  if (msg.code < Code::Any) {
    return Code::Any;
  }
  msg.code = code;
  return code;
}

auto reset() -> void {
  msg.code = Code::None;
  msg.status = Code::Info;
  msg.offset = Code::None;
  msg.level = Code::None;
}
auto setStatus(Code status) -> Code {
  if (status < Code::Any) {
    msg.status = Code::Any;
    return msg.status;
  }
  msg.status = status;
  return status;
}
auto setLevel(Code level) -> Code {
  if (msg.level < Code::Any) {
    msg.level = Code::Any;
    return msg.level;
  }
  msg.level = level;
  return level;
}
auto setOffset(Code offset) -> Code {
  msg.offset = offset;
  return offset;
}
auto getFooterTxt() -> std::string {
  msg.footer = std::string(msg.header.length() - 1, '#');
  return msg.footer;
}
auto getInfoTxt(const std::string &info) -> std::string {
  std::string info_txt = "#-Info: [ " + info + " ] ";
  std::string end = getEndTxt(info_txt, ' ', '#');
  return info_txt + end;
}
auto getCode() -> Code { return msg.code; }
auto is(Code status) -> bool { return msg.status == status; }
auto getLevel() -> Code { return msg.level; }
auto getStatus() -> Code { return msg.status; }
} // namespace origin
