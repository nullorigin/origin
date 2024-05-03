#pragma once

#ifndef EXEC_HPP
#define EXEC_HPP
#include "Basic.hpp"
#include "Message.hpp"
#include "Timer.hpp"

namespace Origin
{
    class Run
    {
        u8 MinArgs = 0;
        string Output{};
        string Input{};
        Timer Timers[2] = { Timer(), Timer() };
        i32 RunState{};
        long Cycles{};
        long MaxCycles{};
        bool Status{};
        static const i8 UNINITIALIZED = 0, INITIALIZING = 1, INITIALIZED = 2,
                        STARTING = 3, STARTED = 4, PAUSING = 5, PAUSED = 6,
                        RESUMING = 7, RESUMED = 8, STOPPING = 9, STOPPED = 10,
                        RESTARTING = 11, RESTARTED = 12, EXITING = 13, EXITED = 14,
                        KILLING = 15, KILLED = 16;
        const string RunStates[17] = {
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
            { UNINITIALIZED, INITIALIZING, -1, -1, -1, -1, -1, -1 },
            { INITIALIZING, INITIALIZED, EXITING, KILLING, -1, -1, -1, -1 },
            { INITIALIZED, STARTING, EXITING, KILLING, -1, -1, -1, -1 },
            { STARTING, STARTED, RESTARTING, EXITING, KILLING, -1, -1, -1 },
            { STARTED, PAUSING, STOPPING, RESTARTING, EXITING, KILLING, -1, -1 },
            { PAUSING, PAUSED, RESUMING, RESTARTING, EXITING, KILLING, -1, -1 },
            { PAUSED, RESUMING, STOPPING, RESTARTING, EXITING, KILLING, -1, -1 },
            { RESUMING, RESUMED, STOPPING, RESTARTING, EXITING, KILLING - 1, -1, -1 },
            { RESUMED, PAUSING, STOPPING, RESTARTING, EXITING, KILLING, -1, -1 },
            { STOPPING, STOPPED, RESTARTING, EXITING, KILLING, -1, -1, -1 },
            { STOPPED, STARTING, RESTARTING, EXITING, KILLING, -1, -1, -1 },
            { RESTARTING, RESTARTED, EXITING, KILLING, -1, -1, -1, -1 },
            { RESTARTED, RESTARTING, STARTING, EXITING, KILLING, -1, -1, -1 },
            { EXITING, EXITED, KILLING, -1, -1, -1, -1, -1 },
            { EXITED, KILLING, -1, -1, -1, -1, -1, -1 },
            { KILLING, KILLED, -1, -1, -1, -1, -1, -1 },
            { KILLED, UNINITIALIZED, -1, -1, -1, -1, -1, -1 }
        };

        const string Cmd[16] = { "init", "1", "start", "2", "pause", "3", "resume", "4", "stop", "5", "restart", "6", "exit", "7", "kill", "8" };
        const u8 CmdLen[16] = { 4, 1, 5, 1, 5, 1, 6, 1, 4, 1, 7, 1, 4, 1, 4, 1 };
        const u8 CmdMap[16] = { 1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15 };
        const string CmdArg[16] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
        const i32 AllTxt = -1, PromptTxt = 0, StateTxt = 1, CycleTxt = 2,
                  TimerTxt = 3, ExecTxt = 4;
        explicit Run(const i8* cmd) { Parse(cmd); }
        explicit Run(const string& cmd) { Parse(cmd); }
        Run(i8p cmd, i8p argv[]) { Exec(cmd, argv); }
        /* A dependency map of applicable run states to enter into after a state
switch. Uses the constants above as specifiers for the equivalent index. */

    public:
        Run() = default;
        static auto GetCode() -> ExCode { return Origin::GetCode(); }
        static auto SetCode(ExCode code) -> void { Origin::SetCode(code); }
        Run(i32 argc, i8** argv) :
            MaxCycles(1000000000) { SetState(UNINITIALIZED); }
        ~Run() = default;

        // The main loop of the application. Splits the output into a separate thread
        // and continues updating the input status until the application is exited or
        // a time limit is reached.
        auto Loop(f128 runtime) -> i32;
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
        inline auto GetStateString(i32 state) -> string
        {
            return RunStates[state];
        }
        auto GetArg(const string& command) -> string;
        auto GetCmd(const string& command) -> i32;
        // Returns the string representation of a given command from its index.
        inline auto GetCmd(i8 index) -> i32 { return CmdMap[index]; }
        // Determines if the application is in a state in which it is actually
        // running.
        auto IsRunning() const -> bool;
        // Returns true if the application is in the specified state.
        inline auto Is(i8 state) const -> bool { return (RunState == state); }
        inline auto GetState() const -> i8 { return RunState; }
        inline auto GetOutput() -> string { return Output; }
        inline auto GetInput() -> string { return Input; }
        inline auto GetCycles() const -> u64 { return Cycles; }
        inline auto SetCycles(u64 cycles) -> void { Cycles = cycles; }
        auto IncrementCycles() -> void;
        inline auto GetMaxCycles() const -> u64 { return MaxCycles; }
        auto SetMaxCycles(u64 cycles) -> i8;
        auto ResetCycles() -> void { Cycles = 0; }
        auto SetStatus(bool status) -> bool;
        auto GetStatus() const -> bool { return Status; }
        auto SetState(i8 target) -> bool;
        auto ProcessCycles() -> i8;
        auto ProcessState(i8 state) -> i8;
        auto SetMinArgs(u8 min_args) -> void;
        auto GetMinArgs() -> u8;

        auto Call(const string& cmd) -> string;

        auto Call(i8p cmd) -> string;
        auto Exec(i8p command, const i8p argv[]) -> void;
        static auto Parse(const i8p cmd) -> string { return { cmd }; }
        auto Parse(const string& cmd) -> string;
    };
} // namespace Origin
#endif