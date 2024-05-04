#include <Message.hpp>
#include <string>

namespace Origin
{
    auto get_header_txt() -> std::string
    {
        std::string header[5] = { "[--NONE--]", "[--INFO--]", "[-WARNING-]", "[--ERROR--]", "[--FATAL--]" };
        msg.header = "#############################" + header[i32(msg.status)] +
                     "#############################";
        return msg.header;
    }

    auto get_end_txt(std::string begin, i8 padding, std::string ending) -> std::string
    {
        std::string end{};
        for (u64 i = begin.length(); i < msg.header.length() - 1; i++)
        {
            end += padding;
        }
        end += ending;
        return end + "\n";
    }
    auto set_code(Code code) -> Code
    {
        if (msg.code < Code::any)
        {
            return Code::any;
        }
        msg.code = code;
        return code;
    }

    auto reset() -> void
    {
        msg.code = Code::none;
        msg.status = Code::info;
        msg.offset = Code::none;
        msg.level = Code::none;
    }
    auto set_status(Code status) -> Code
    {
        if (status < Code::any)
        {
            msg.status = Code::any;
            return msg.status;
        }
        msg.status = status;
        return status;
    }
    auto set_level(Code level) -> Code
    {
        if (msg.level < Code::any)
        {
            msg.level = Code::any;
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
    auto get_info_txt(std::string info) -> std::string
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
} // namespace Origin::dbg
