#include <Message.hpp>
#include <string>

namespace Origin
{
    auto get_header_txt() -> std::string
    {
        const std::string header[6] = { "[--NONE--]", "[--INFO--]", "[-WARNING-]", "[--ERROR--]", "[--FATAL--]", "[--NONE--]" };
        msg.header = std::string(30, '#') + header[cast<i32>(msg.status)] +
                     std::string(30, '#');
        return msg.header;
    }

    auto get_end_txt(const std::string& begin, const i8& padding, const std::string& ending) -> std::string
    {
        std::string end = std::string(msg.header.length() - begin.length() - 1, padding);
        end += ending + "\n";
        return end;
    }
    auto set_code(Code code) -> Code
    {
        if (msg.code < Code::Any)
        {
            return Code::Any;
        }
        msg.code = code;
        return code;
    }

    auto reset() -> void
    {
        msg.code = Code::None;
        msg.status = Code::Info;
        msg.offset = Code::None;
        msg.level = Code::None;
    }
    auto set_status(Code status) -> Code
    {
        if (status < Code::Any)
        {
            msg.status = Code::Any;
            return msg.status;
        }
        msg.status = status;
        return status;
    }
    auto set_level(Code level) -> Code
    {
        if (msg.level < Code::Any)
        {
            msg.level = Code::Any;
            return msg.level;
        }
        msg.level = level;
        return level;
    }
    auto set_offset(Code offset) -> Code
    {
        msg.offset = offset;
        return offset;
    }
    auto get_footer_txt() -> std::string
    {
        msg.footer = std::string(msg.header.length() - 1, '#');
        return msg.footer;
    }
    auto get_info_txt(const std::string& info) -> std::string
    {
        std::string info_txt = "#-Info: [ " + info + " ]";
        return info_txt + get_end_txt(info_txt, ' ', "#");
    }
    auto get_code() -> Code
    {
        return msg.code;
    }
    auto is(Code status) -> bool
    {
        return msg.status == status;
    }
    auto get_level() -> Code
    {
        return msg.level;
    }
    auto get_status() -> Code
    {
        return msg.status;
    }
} // namespace Origin
