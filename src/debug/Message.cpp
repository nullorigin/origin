#include <Message.hpp>
#include <sstream>
namespace origin
{

    auto GetHeader() -> std::string
    {
        std::string header[5] = { "[--NONE--]", "[--INFO--]", "[-WARNING-]", "[--ERROR--]", "[--FATAL--]" };
        MsgHeader = "##########################" + header[MsgStatus] +
                    "#########################";
        return MsgHeader;
    }

    auto GetStringEnd(const std::string& begin, i8 padding, i8 ending) -> std::string
    {
        std::string end;
        for (u64 i = begin.length(); i < MsgHeader.length() - 1; i++)
        {
            end += padding;
        }
        end += ending;
        return end + "\n";
    }
    void Reset()
    {
        MsgStatus = NONE;
        MsgOffset = NONE;
        MsgLevel = NONE;
    }
    auto SetCode(ExCode code) -> ExCode
    {
        if (MsgCode < ANY)
        {
            return ANY;
        }
        MsgCode = code;
        return code;
    }
    auto ToString(const char* str) -> std::string
    {
        std::stringstream ss = std::stringstream(str);
        return ss.str();
    };
    auto Restart() -> void
    {
        MsgCode = NONE;
        MsgStatus = INFO;
        MsgOffset = NONE;
        MsgLevel = NONE;
    }
    auto SetStatus(ExCode status) -> ExCode
    {
        if (status < ANY)
        {
            MsgStatus = INFO;
            return MsgStatus;
        }
        MsgStatus = status;
        return status;
    }
    auto SetLevel(ExLevel level) -> ExLevel
    {
        if (MsgLevel < ANY)
        {
            MsgLevel = ANY;
            return MsgLevel;
        }
        MsgLevel = level;
        return level;
    }
    auto SetOffset(ExLevel offset) -> ExLevel
    {
        MsgOffset = offset;
        return offset;
    }
} // namespace origin