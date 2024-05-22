#ifndef ORIGIN_HPP
#define ORIGIN_HPP

#include "debug/Message.hpp"
#include "process/Exec.hpp"
#pragma once

namespace origin
{
    static Run run;
    auto init(bool debug = false) -> Code;
    //auto update() -> void;
    //auto draw() -> void;
    auto exit() -> Code;
    int exitDbg(int sig, void* ptr);
} // namespace origin
#endif // ORIGIN_HPP
