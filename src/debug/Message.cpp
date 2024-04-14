#include <Message.hpp>
namespace origin {
auto SetStatus(int status = INFO) -> int {
  if (status >= NONE && status <= FATAL) {
    MsgStatus = status;
    return status;
  }
  return -1;
}

auto SetLevel(int level = INFO) -> int {
  if (level >= NONE && level <= FATAL) {
    MsgLevel = level;
    return level;
  }
  return -1;
}
auto SetOffset(int offset) -> int {
  MsgOffset = offset;
  return MsgOffset;
}
char *Info;

auto GetHeader() -> std::string {
  std::string header[5] = {"[--NONE--]", "[--INFO--]", "[-WARNING-]",
                           "[--ERROR--]", "[--FATAL--]"};
  MsgHeader = "##########################" + header[MsgStatus] +
              "#########################";
  return MsgHeader;
}

auto GetEnd(std::string begin, char padding, char ending) -> std::string {
  std::string end;
  for (int i = begin.length(); i < MsgHeader.length() - 1; i++) {
    end += padding;
  }
  end += ending;
  return end + "\n";
}
auto IsNone() -> bool { return (MsgStatus == NONE && MsgLevel <= NONE); }
auto IsInfo() -> bool { return (MsgStatus == INFO && MsgLevel <= INFO); }
auto IsWarning() -> bool {
  return (MsgStatus == WARNING && MsgLevel <= WARNING);
}
auto IsError() -> bool { return (MsgStatus == ERROR && MsgLevel <= ERROR); }
auto IsFatal() -> bool { return (MsgStatus == FATAL && MsgLevel <= FATAL); }
/* Levels for controlling message output. */

void Reset() {
  MsgStatus = NONE;
  MsgOffset = 0;
  MsgLevel = NONE;
}
} // namespace origin