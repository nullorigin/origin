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
        string Output;
        string Input;
        Timer Timers[2] = { Timer(), Timer() };
        i32 RunState{};
        long Cycles{};
        long MaxCycles{};
        bool RunStatus{};
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
        explicit Run(const i8* cmd) { parse(cmd); }
        explicit Run(const string& cmd) { parse(cmd); }
        Run(i8p cmd, i8p argv[]) { exec(cmd, argv); }
        /* A dependency map of applicable run states to enter into after a state
switch. Uses the constants above as specifiers for the equivalent index. */

    public:
        Run() = default;
        Run(i32 /*argc*/, i8** /*argv*/) :
            MaxCycles(1000000000) { set_run_state(UNINITIALIZED); }
        ~Run() = default;

        // The main loop of the application. Splits the output into a separate thread
        // and continues updating the input status until the application is exited or
        // a time limit is reached.
        auto loop(f128 runtime) -> i32;
        // Sets the run state of the application to 'Initializing' and Upon success,
        // sets the run state to 'Initialized'.
        auto do_init() -> bool;
        // Sets the run state of the application to 'Starting' and executes specified
        // commands. Upon success,the run state is set to 'Started'.
        auto do_start() -> bool;
        // Sets the run state of the application to 'Pausing' and executes specified
        // commands. Upon success, the run state is set to 'Paused'. In addition, the
        // output is frozen and saved until the 'resume' command is executed, at which
        // point it continues from where it left off.
        auto do_pause() -> bool;
        // Sets the run state of the application to 'Resuming' and executes specified
        // commands. Upon success, the run state is set to 'Resumed'. This command is
        // only valid if the application is in the 'Paused' state. In addition, the
        // output is frozen until this command is called at which point it
        // continues from where it left off.
        auto do_resume() -> bool;
        // Sets the run state of the application to 'Stopping' and executes specified
        // commands. Upon success, the run state is set to 'Stopped'. In this state
        // The only applicable commands are 'start', 'restart' and 'exit'.
        auto do_stop() -> bool;
        // Sets the run state of the application to 'Restarting' and executes
        // specified commands. Upon success, the run state is set to 'Restarted'. All
        // Variables are reset to their initial values.
        auto do_restart() -> bool;
        // Sets the run state of the application to 'Exiting' and executes specified
        // commands. Upon failure, the kill command is executed and forces the
        // application to close. Upon success, the run state is set to 'Exited' and
        // exits normally.
        auto do_exit() -> bool;
        // Sets the run state of the application to 'Killing' and then 'Killed'. The
        // application is forced to close when this command is executed.
        auto do_kill() -> bool;

        // Returns the entire map of valid run states to enter into during a state
        // switch.
        inline auto get_run_map() -> const i8 (*)[8] { return RunMap; }
        // Returns an array of applicable run states in which to switch to
        // from a given previous state.
        inline auto get_state_next(i32 state) -> const i8 (*)[8]
        {
            return &RunMap[state];
        }
        // Returns the string representation of a given run state.
        inline auto get_state_string(i32 state) -> string
        {
            return RunStates[state];
        }
        auto get_arg(const string& command) -> string;
        auto get_cmd(const string& command) -> i32;
        // Returns the string representation of a given command from its index.
        inline auto get_cmd(i8 index) -> i32 { return CmdMap[index]; }
        // Determines if the application is in a state in which it is actually
        // running.
        auto is_running() const -> bool;
        // Returns true if the application is in the specified state.
        inline auto is_state(i8 rstate) const -> bool { return (RunState == rstate); }
        inline auto get_state() const -> i8 { return RunState; }
        inline auto get_output() -> string { return Output; }
        inline auto get_input() -> string { return Input; }
        inline auto get_cycles() const -> u64 { return Cycles; }
        inline auto set_cycles(u64 cycles) -> void { Cycles = cycles; }
        auto increment_cycles() -> void;
        inline auto get_max_cycles() const -> u64 { return MaxCycles; }
        auto set_max_cycles(u64 cycles) -> i8;
        inline auto reset_cycles() -> void { Cycles = 0; }
        auto set_run_status(bool status) -> bool
        {
            return RunStatus = status;
        }
        inline auto get_status() const -> bool { return RunStatus; }
        auto set_run_state(i8 target) -> bool;
        auto process_cycles() -> i8;
        auto process_state(i8 state) -> i8;
        // Reads input from various sources and acts accordingly.
        auto process_input() -> i8;
        // Writes output to various destinations and acts accordingly.
        auto process_output() -> i8;
        auto set_min_args(u8 min_args) -> void;
        auto get_min_args() -> u8;

        auto call(const string& cmd) -> string;

        auto call(i8p cmd) -> string;
        auto exec(i8p command, const i8p argv[]) -> void;
        auto parse(const i8p cmd) -> string;
        auto parse(const string& cmd) -> string;
    };
} // namespace Origin
#endif