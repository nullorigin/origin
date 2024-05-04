#include "Exec.hpp"
#include "Message.hpp"
#include <iostream>
namespace Origin
{
    auto Run::loop(f128 runtime) -> i32
    {
        if (runtime > 0)
        {
            Timers[0].set_limit(runtime);
        }
        while ((get_state() < EXITED) && (Timers[0].get_remaining() > 0))
        {
            process_cycles();
        }
        return 0;
    }
    auto Run::do_init() -> bool
    {
        if (RunState == UNINITIALIZED)
        {
            if (set_run_state(INITIALIZING))
            {
                return set_run_state(INITIALIZED);
            }
        }
        return false;
    }
    auto Run::do_start() -> bool
    {
        if (set_run_state(STARTING))
        {
            Timers[0].start();
            return set_run_state(STARTED);
        }
        return false;
    }
    auto Run::do_pause() -> bool
    {
        if (set_run_state(PAUSING))
        {
            Timers[0].pause();
            return set_run_state(PAUSED);
        }
        return false;
    }
    auto Run::do_resume() -> bool
    {
        if (set_run_state(RESUMING))
        {
            Timers[0].resume();
            return set_run_state(RESUMED);
        }
        return false;
    }
    auto Run::do_stop() -> bool
    {
        if (set_run_state(STOPPING))
        {
            Timers[0].stop();
            reset_cycles();
            return set_run_state(STOPPED);
        }

        return false;
    }
    auto Run::do_restart() -> bool
    {
        if (set_run_state(RESTARTING))
        {
            Timers[0].restart();
            reset_cycles();
            return set_run_state(RESTARTED);
        }
        return false;
    }
    auto Run::do_exit() -> bool
    {
        if (set_run_state(EXITING))
        {
            if (set_run_state(EXITED))
            {
                do_kill();
            }
        }
        return false;
    }
    auto Run::do_kill() -> bool
    {
        if (set_run_state(KILLING))
        {
            set_run_state(KILLED);
            ::exit(-1);
        }
        return false;
    }
    auto Run::get_arg(const string& command) -> string
    {
        for (i8 i = 0; i < 16; i++)
        {
            if (Cmd[i] == command)
            {
                return CmdArg[i];
            }
        }
        return "";
    }
    auto Run::get_cmd(const string& command) -> i32
    {
        for (i8 i = 0; i < 16; i++)
        {
            if (Cmd[i] == command)
            {
                return CmdMap[i];
            }
        }
        return -1;
    }
    auto Run::is_running() const -> bool
    {
        i8 const state = get_state();
        return ((state < PAUSED) && (state > UNINITIALIZED)) ||
               (state < EXITED && state >= RESUMING && state != STOPPED &&
                state != RESTARTED);
    }
    auto Run::increment_cycles() -> void
    {
        if (is_running())
        {
            Cycles++;
        }
        if (Cycles > MaxCycles)
        {
            do_exit();
        }
    }
    auto Run::set_max_cycles(u64 cycles) -> i8
    {
        if (cycles <= 0)
        {
            MaxCycles = 1;
            return -1;
        }
        MaxCycles = cycles;
        return 0;
    }

    auto Run::set_run_state(i8 target) -> bool
    {
        bool status = false;
        i32 state = get_state();
        i8 i = 0;
        if (state == target)
        {
            return set_run_status(status);
        }
        if (target >= 1 && target < 17)
        {
            while ((RunMap[state][i] != -1) && (i < 8) && (!status))
            {
                if (RunMap[state][i] == target)
                {
                    state = target;
                    status = true;
                }
                i++;
            }
        }
        RunState = state;
        return get_status();
    }
    auto Run::process_cycles() -> i8
    {
        increment_cycles();
        if (get_cycles() >= get_max_cycles() && get_max_cycles() != 0)
        {
            do_exit();
        }
        return 0;
    }
    auto Run::process_state(i8 state) -> i8
    {
        switch (state)
        {
        case INITIALIZING:
            if (set_run_status(do_init()))
            {
                debug("Initialized", Code::info);
                return INITIALIZED;
            }
            break;
        case STARTING:
            if (set_run_status(do_start()))
            {
                debug("Started", Code::info);
                return STARTED;
            }
            break;
        case PAUSING:
            if (set_run_status(do_pause()))
            {
                debug("Paused", Code::info);
                return PAUSED;
            }
            break;
        case RESUMING:
            if (set_run_status(do_resume()))
            {
                debug("Resumed", Code::info);
                return RESUMED;
            }
            break;
        case STOPPING:
            if (set_run_status(do_stop()))
            {
                debug("Stopped", Code::info);
                return STOPPED;
            }
            break;
        case RESTARTING:
            if (set_run_status(do_restart()))
            {
                debug("Restarted", Code::info);
                return RESTARTED;
            }
            break;
        case EXITING:
            if (set_run_status(do_exit()))
            {
                debug("Exited", Code::info);
                return EXITED;
            }
            break;
        case KILLING:
            if (set_run_status(do_kill()))
            {
                debug("Killed", Code::info);
                return KILLED;
            }
            break;
        default:
            debug("Unknown state", Code::error);
            break;
        }
        return -1;
    }
    auto Run::set_min_args(u8 min_args) -> void
    {
        if (min_args == 0)
        {
            debug("Minimum number of arguments was set to 0.", Code::info);
        }
        MinArgs = min_args;
    }
    auto Run::get_min_args() -> u8
    {
        if (MinArgs == 0)
        {
            debug("Minimum number of arguments is set to 0.", Code::info);
        }
        if (MinArgs < 0)
        {
            debug("Minimum number of arguments is less than 0.", Code::error);
            MinArgs = 0;
        }
        return MinArgs;
    }
    auto Run::call(const string& cmd) -> string
    {
        string output;
        std::unique_ptr<FILE, decltype(&pclose)> in{ popen(cmd.c_str(), "r"), pclose };
        if (!in)
        {
            debug("Null pointer passed to popen().", Code::error);
            return "";
        }
        i8 buffer[128];
        while (fgets(buffer, sizeof(buffer), in.get()) != nullptr)
        {
            output += buffer;
        }
        if (ferror(in.get()) != 0)
        {
            debug("Error while executing command.", Code::error);
            return "";
        }
        debug("Command executed successfully.", Code::info);
        return output;
    }
    auto Run::call(const i8p cmd) -> string
    {
        i8 buffer[128];
        string result;
        FILE* pipe = popen(cmd, "r");
        if (pipe == nullptr)
        {
            debug("Null pointer passed to popen().", Code::error);
        }
        try
        {
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
            {
                result += buffer;
            }
        }
        catch (...)
        {
            pclose(pipe);

            debug("Error while executing command.", Code::error);
            return "";
        }
        pclose(pipe);
        debug("Command executed successfully.", Code::info);
        return result;
    }
    auto Run::exec(const i8p command, const i8p argv[]) -> void
    {
        if (command == nullptr || argv == nullptr)
        {
            debug("Null pointer passed to Exec().", Code::error);
            return;
        }
        string output = call(string(command) + " " + string(argv[0]));
        if (output.length() <= string::npos && output.length() > 0)
        {
            debug("Invalid command string passed.", Code::error);
            return;
        }
        Output = output.substr(0, output.length() - 1);
        debug("Command Successfully Executed.", Code::info);
    }
    auto Run::parse(const string& cmd) -> string
    {
        if (cmd.length() <= string::npos && cmd.length() > 0)
        {
            debug("Invalid command string passed.", Code::error);
            return "";
        }
        return cmd;
    }
    auto Run::parse(const i8p cmd) -> string
    {
        return { cmd };
    }
    auto Run::process_input() -> i8
    {
        return 0;
    }
    auto Run::process_output() -> i8
    {
        return 0;
    }
} // namespace Origin