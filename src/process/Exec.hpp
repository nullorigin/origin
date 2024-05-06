#pragma once

#ifndef EXEC_HPP
#define EXEC_HPP
#include "Basic.hpp"
#include "Message.hpp"
#include "Timer.hpp"
#include <string>
namespace Origin
{
    class Run
    {
    private:
        f128 TimeMax = 0;
        u32 MinArgs = 0;
        string Output;
        string Input;
        Timer Timers[2] = { Timer(), Timer() };
        i32 RunState{};
        Code RunStatus{};
        u64 Cycles{};
        u64 MaxCycles{};
        std::string TimerText = " ";
        std::string ExecText = " ";

    public:
        static const i32 UNINITIALIZED = 0, INITIALIZING = 1, INITIALIZED = 2,
                         STARTING = 3, STARTED = 4, PAUSING = 5, PAUSED = 6,
                         RESUMING = 7, RESUMED = 8, STOPPING = 9, STOPPED = 10,
                         RESTARTING = 11, RESTARTED = 12, EXITING = 13, EXITED = 14,
                         KILLING = 15, KILLED = 16;
        static const string RUN_STATES[17];
        static const i32 RUN_MAP[17][8];

        static const string CMD[16];
        static const u32 CMD_LEN[16];
        static const u32 CMD_MAP[16];
        static const string CMD_ARG[16];
        static const i32 AllTxt = -1, PromptTxt = 0, StateTxt = 1, CycleTxt = 2,
                         TimerTxt = 3, ExecTxt = 4;
        explicit Run(const i8* cmd) { parse(cmd); }
        explicit Run(const string& cmd) { parse(cmd); }
        Run(i8p cmd, i8p argv[]) { exec(cmd, argv); }
        /* A dependency map of applicable run states to enter into after a state
switch. Uses the constants above as specifiers for the equivalent index. */

        Run()
        {
            set_max_cycles(0);
            set_run_state(UNINITIALIZED);
        }
        Run(i32 /*argc*/, i8** /*argv*/)
        {
            set_max_cycles(0);
            set_run_state(UNINITIALIZED);
        }
        ~Run() = default;

        // The main loop of the application. Splits the output into a separate thread
        // and continues updating the input status until the application is exited or
        // a time limit is reached.
        auto loop(f128 runtime = 0) -> Code;
        // Sets the run state of the application to 'Initializing' and Upon success,
        // sets the run state to 'Initialized'.
        auto do_init() -> Code;
        // Sets the run state of the application to 'Starting' and executes specified
        // commands. Upon success,the run state is set to 'Started'.
        auto do_start() -> Code;
        // Sets the run state of the application to 'Pausing' and executes specified
        // commands. Upon success, the run state is set to 'Paused'. In addition, the
        // output is frozen and saved until the 'resume' command is executed, at which
        // point it continues from where it left off.
        auto do_pause() -> Code;
        // Sets the run state of the application to 'Resuming' and executes specified
        // commands. Upon success, the run state is set to 'Resumed'. This command is
        // only valid if the application is in the 'Paused' state. In addition, the
        // output is frozen until this command is called at which point it
        // continues from where it left off.
        auto do_resume() -> Code;
        // Sets the run state of the application to 'Stopping' and executes specified
        // commands. Upon success, the run state is set to 'Stopped'. In this state
        // The only applicable commands are 'start', 'restart' and 'exit'.
        auto do_stop() -> Code;
        // Sets the run state of the application to 'Restarting' and executes
        // specified commands. Upon success, the run state is set to 'Restarted'. All
        // Variables are reset to their initial values.
        auto do_restart() -> Code;
        // Sets the run state of the application to 'Exiting' and executes specified
        // commands. Upon failure, the kill command is executed and forces the
        // application to close. Upon success, the run state is set to 'Exited' and
        // exits normally.
        auto do_exit() -> Code;
        // Sets the run state of the application to 'Killing' and then 'Killed'. The
        // application is forced to close when this command is executed.
        auto do_kill() -> Code;

        // Returns the entire map of valid run states to enter into during a state
        // switch.
        static inline auto get_run_map() -> const i32 (*)[8] { return RUN_MAP; }
        // Returns an array of applicable run states in which to switch to
        // from a given previous state.
        static inline auto get_state_next(i32 rstate) -> const i32 (*)[8]
        {
            return &RUN_MAP[rstate];
        }
        // Returns the string representation of a given run state.
        static inline auto get_state_string(i32 rstate) -> string
        {
            return RUN_STATES[rstate];
        }
        auto get_arg(const string& command) -> string;
        auto get_cmd(const string& command) -> u32;
        // Returns the string representation of a given command from its index.
        static inline auto get_cmd(u32 index) -> i32 { return CMD_MAP[index]; }
        // Determines if the application is in a state in which it is actually
        // running.
        auto is_running() const -> Code;
        // Returns true if the application is in the specified state.
        inline auto is_state(i32 rstate) const -> Code
        {
            return RunState == rstate ? Code::True : Code::False;
        }
        inline auto get_run_state() const -> i32 { return RunState; }
        auto set_output(const std::string& output, bool format = false) -> Code;
        inline auto get_output() -> string { return Output; }
        auto set_input(const std::string& input, bool format = false) -> Code;
        inline auto get_input() -> string { return Input; }
        inline auto get_cycles() const -> u64 { return Cycles; }
        inline auto set_cycles(u64 cycles) -> void { Cycles = cycles; }
        auto increment_cycles() -> Code;
        inline auto get_max_cycles() const -> u64 { return MaxCycles; }
        auto set_max_cycles(u64 cycles = 0) -> Code;
        inline auto reset_cycles() -> void { Cycles = 0; }
        auto set_run_status(Code rstatus) -> Code
        {
            return RunStatus = rstatus;
        }
        inline auto get_run_status() const -> Code { return RunStatus; }
        auto set_run_state(i32 target) -> Code;
        auto process_cycles() -> Code;
        auto process_state(i32 rstate) -> Code;
        // Reads input from various sources and acts accordingly.
        auto process_input() -> Code;
        // Writes output to various destinations and acts accordingly.
        auto process_output() -> Code;
        auto set_min_args(u32 min_args) -> Code;
        auto get_min_args() -> u32;

        static auto call(const string& cmd) -> string;

        static auto call(i8p cmd) -> string;
        auto exec(i8p command, const i8p argv[]) -> Code;
        auto parse(i8p cmd) -> string;
        auto parse(const string& cmd) -> string;
        auto get_text(i32 name, const string& dlim = "\n") -> string;
    };
} // namespace Origin
#endif