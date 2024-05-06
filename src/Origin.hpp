#ifndef ORIGIN_HPP
#define ORIGIN_HPP

#include "Message.hpp"
#include "process/Exec.hpp"
#pragma once

namespace Origin
{
    static Run run;
    auto init(bool debug = false) -> Code;
    //auto update() -> void;
    //auto draw() -> void;
    auto exit() -> Code;
    int exit_dbg(int sig, void* ptr);
} // namespace Origin
#endif // ORIGIN_HPP
