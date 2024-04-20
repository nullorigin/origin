#pragma once

#ifndef EXEC_HPP
#define EXEC_HPP
#include "Basic.hpp"
#include "Message.hpp"
#include "Timer.hpp"
#include <string>

namespace origin
{
    class Run
    {
        u8 MinArgs = 0;
        std::string Output{};
        std::string Input{};
        Timer Timers[2] = { Timer(), Timer() };
        int RunState{};
        long Cycles{};
        long MaxCycles{};
        bool Status{};
        static const i8 Uninitialized = 0, Initializing = 1, Initialized = 2,
                        Starting = 3, Started = 4, Pausing = 5, Paused = 6,
                        Resuming = 7, Resumed = 8, Stopping = 9, Stopped = 10,
                        Restarting = 11, Restarted = 12, Exiting = 13, Exited = 14,
                        Killing = 15, Killed = 16;
        const std::string RunStates[17] = {
            "Uninitialized",
            "Initializing",
            "Initialized",
            "Starting",
            "Started",
            "Pausing",
            "Paused",
            "Resuming",
            "Resumed",
            "Stopping",
            "Stopped",
            "Restarting",
            "Restarted",
            "Exiting",
            "Exited",
            "Killing",
            "Killed"
        };
        const i8 RunMap[17][8] = {
            { Uninitialized, Initializing, -1, -1, -1, -1, -1, -1 },
            { Initializing, Initialized, Exiting, Killing, -1, -1, -1, -1 },
            { Initialized, Starting, Exiting, Killing, -1, -1, -1, -1 },
            { Starting, Started, Restarting, Exiting, Killing, -1, -1, -1 },
            { Started, Pausing, Stopping, Restarting, Exiting, Killing, -1, -1 },
            { Pausing, Paused, Resuming, Restarting, Exiting, Killing, -1, -1 },
            { Paused, Resuming, Stopping, Restarting, Exiting, Killing, -1, -1 },
            { Resuming, Resumed, Stopping, Restarting, Exiting, Killing - 1, -1, -1 },
            { Resumed, Pausing, Stopping, Restarting, Exiting, Killing, -1, -1 },
            { Stopping, Stopped, Restarting, Exiting, Killing, -1, -1, -1 },
            { Stopped, Starting, Restarting, Exiting, Killing, -1, -1, -1 },
            { Restarting, Restarted, Exiting, Killing, -1, -1, -1, -1 },
            { Restarted, Restarting, Starting, Exiting, Killing, -1, -1, -1 },
            { Exiting, Exited, Killing, -1, -1, -1, -1, -1 },
            { Exited, Killing, -1, -1, -1, -1, -1, -1 },
            { Killing, Killed, -1, -1, -1, -1, -1, -1 },
            { Killed, Uninitialized, -1, -1, -1, -1, -1, -1 }
        };

        const std::string Cmd[16] = { "init", "1", "start", "2", "pause", "3", "resume", "4", "stop", "5", "restart", "6", "exit", "7", "kill", "8" };

        const u8 CmdMap[16] = { 1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15 };
        const std::string CmdArg[16] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
        const int AllTxt = -1, PromptTxt = 0, StateTxt = 1, CycleTxt = 2,
                  TimerTxt = 3, ExecTxt = 4;
        explicit Run(const i8* cmd) { Parse(cmd); }
        explicit Run(const std::string& cmd) { Parse(cmd.c_str()); }
        Run(const i8* cmd, i8 const* argv[]) { Exec(cmd, argv); }
        /* A dependency map of applicable run states to enter into after a state
switch. Uses the constants above as specifiers for the equivalent index. */

    public:
        Run() = default;
        static auto GetCode() -> ExCode { return origin::GetCode(); }
        static auto SetCode(ExCode code) -> void { origin::SetCode(code); }
        Run(i32 argc, i8** argv) :
            MaxCycles(1000000000) { SetState(Uninitialized); }
        ~Run() = default;

        // The main loop of the application. Splits the output into a separate thread
        // and continues updating the input status until the application is exited or
        // a time limit is reached.
        auto Loop(Duration runtime) -> int;
        // Sets the run state of the application to 'Initializing' and Upon success,
        // sets the run state to 'Initialized'.
        auto DoInit() -> bool;
        // Sets the run state of the application to 'Starting' and executes specified
        // commands. Upon success,the run state is set to 'Started'.
        auto DoStart() -> bool;
        // Sets the run state of the application to 'Pausing' and executes specified
        // commands. Upon success, the run state is set to 'Paused'. In addition, the
        // output is frozen and saved until the 'resume' command is executed, at which
        // point it continues from where it left off.
        auto DoPause() -> bool;
        // Sets the run state of the application to 'Resuming' and executes specified
        // commands. Upon success, the run state is set to 'Resumed'. This command is
        // only valid if the application is in the 'Paused' state. In addition, the
        // output is frozen until this command is called at which point it
        // continues from where it left off.
        auto DoResume() -> bool;
        // Sets the run state of the application to 'Stopping' and executes specified
        // commands. Upon success, the run state is set to 'Stopped'. In this state
        // The only applicable commands are 'start', 'restart' and 'exit'.
        auto DoStop() -> bool;
        // Sets the run state of the application to 'Restarting' and executes
        // specified commands. Upon success, the run state is set to 'Restarted'. All
        // Variables are reset to their initial values.
        auto DoRestart() -> bool;
        // Sets the run state of the application to 'Exiting' and executes specified
        // commands. Upon failure, the kill command is executed and forces the
        // application to close. Upon success, the run state is set to 'Exited' and
        // exits normally.
        auto DoExit() -> bool;
        // Sets the run state of the application to 'Killing' and then 'Killed'. The
        // application is forced to close when this command is executed.
        auto DoKill() -> bool;
        // Returns the entire map of valid run states to enter into during a state
        // switch.
        inline auto GetRunMap() -> const i8 (*)[8] { return RunMap; }
        // Returns an array of applicable run states in which to switch to
        // from a given previous state.
        inline auto GetStateNext(i32 state) -> const i8 (*)[8]
        {
            return &RunMap[state];
        }
        // Returns the string representation of a given run state.
        inline auto GetStateString(i32 state) -> std::string
        {
            return RunStates[state];
        }
        auto GetArg(const std::string& command) -> std::string;
        auto GetCmd(const std::string& command) -> int;
        // Returns the string representation of a given command from its index.
        inline auto GetCmd(i8 index) -> int { return CmdMap[index]; }
        // Determines if the application is in a state in which it is actually
        // running.
        auto IsRunning() const -> bool;
        // Returns true if the application is in the specified state.
        inline auto Is(i8 state) const -> bool { return (RunState == state); }
        inline auto GetState() const -> i8 { return RunState; }
        inline auto GetOutput() -> std::string { return Output; }
        inline auto GetInput() -> std::string { return Input; }
        inline auto GetCycles() const -> long { return Cycles; }
        inline auto SetCycles(long cycles) -> void { Cycles = cycles; }
        auto IncrementCycles() -> void;
        inline auto GetMaxCycles() const -> long { return MaxCycles; }
        auto SetMaxCycles(long cycles) -> i8;
        auto ResetCycles() -> void { Cycles = 0; }
        auto SetStatus(bool status) -> bool;
        auto GetStatus() const -> bool { return Status; }
        auto SetState(i8 target) -> bool;
        auto ProcessCycles() -> i8;
        auto ProcessState(i8 state) -> i8;
        auto SetMinArgs(u8 min_args) -> void;
        auto GetMinArgs() -> u8;

        auto Call(const std::string& cmd) -> std::string;

        auto Call(const char* cmd) -> std::string;
        auto Exec(const char* command, char const* const argv[]) -> void;
        static auto Parse(const char* cmd) -> std::string { return { cmd }; }
        auto Parse(const std::string& cmd) -> std::string;
    };
} // namespace origin
#endif