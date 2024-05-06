#include "Exec.hpp"
#include "Console.hpp"
#include "Message.hpp"
#include "Origin.hpp"
#include "Timer.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
namespace Origin
{
    const i32 Run::RUN_MAP[17][8] = {
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
    const string Run::RUN_STATES[17] = {
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
    const string Run::CMD[16] = { "init", "1", "start", "2", "pause", "3", "resume", "4", "stop", "5", "restart", "6", "exit", "7", "kill", "8" };
    const u32 Run::CMD_LEN[16] = { 4, 1, 5, 1, 5, 1, 6, 1, 4, 1, 7, 1, 4, 1, 4, 1 };
    const u32 Run::CMD_MAP[16] = { 1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15 };
    const string Run::CMD_ARG[16] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };

    auto Run::loop(f128 runtime) -> Code
    {
        RunStatus = set_max_cycles();
        if (runtime > 0)
        {
            Timers[0].set_limit(runtime);
        }
        else
        {
            Timers[0].set_limit(INFINITY);
        }
        do_init();
        while (true)
        {
            RunStatus = process_cycles();
            RunStatus = process_output();
            RunStatus = process_input();
            if (get_run_state() >= EXITING || Timers[0].get_remaining() <= 0)
            {
                return do_exit();
            }
        }
        return do_kill();
    }
    auto Run::do_init() -> Code
    {
        if (RunState == UNINITIALIZED)
        {
            if (set_run_state(INITIALIZING) == Code::Success)
            {
                Code code = set_run_state(INITIALIZED);
                return code;
            }
        }
        return Code::Error;
    }
    auto Run::do_start() -> Code
    {
        if (set_run_state(STARTING) == Code::Success)
        {
            Timers[0].start();
            return set_run_state(STARTED);
        }
        return Code::Error;
    }
    auto Run::do_pause() -> Code
    {
        if (set_run_state(PAUSING) == Code::Success)
        {
            Timers[0].pause();
            return set_run_state(PAUSED);
        }
        return Code::Failure;
    }
    auto Run::do_resume() -> Code
    {
        if (set_run_state(RESUMING) == Code::Success)
        {
            Timers[0].resume();
            return set_run_state(RESUMED);
        }
        return Code::Failure;
    }
    auto Run::do_stop() -> Code
    {
        if (set_run_state(STOPPING) == Code::Success)
        {
            Timers[0].stop();
            reset_cycles();
            return set_run_state(STOPPED);
        }

        return Code::Failure;
    }
    auto Run::do_restart() -> Code
    {
        if (set_run_state(RESTARTING) == Code::Success)
        {
            Timers[0].restart();
            reset_cycles();
            return set_run_state(RESTARTED);
        }
        return Code::Failure;
    }
    auto Run::do_exit() -> Code
    {
        if (set_run_state(EXITING) == Code::Success)
        {
            Timers[0].stop();
            reset_cycles();
            Cycles = 0;
            try
            {
                std::exit(0);
            }
            catch (...)
            {
                debug("Failed to exit process.", Code::Error);
                return set_run_status(Code::Failure);
            }
            set_run_status(Code::Success);
            return set_run_state(EXITED);
        }
        return Code::Failure;
    }
    auto Run::do_kill() -> Code
    {
        Timers[0].stop();
        reset_cycles();
        if (set_run_state(KILLING) == Code::Success)
        {
            try
            {
                std::exit(-1);
            }
            catch (...)
            {
                debug("Failed to kill process.", Code::Error);
                return set_run_status(Code::Failure);
            }
            return set_run_state(KILLED);
        }
        return Code::Failure;
    }
    auto Run::get_arg(const string& command) -> string
    {
        for (i8 i = 0; i < 16; i++)
        {
            if (CMD[i] == command)
            {
                return CMD_ARG[i];
            }
        }
        return "";
    }
    auto Run::get_cmd(const string& command) -> u32
    {
        for (i8 i = 0; i < 16; i++)
        {
            if (CMD[i] == command)
            {
                return CMD_MAP[i];
            }
        }
        return -1;
    }
    auto Run::is_running() const -> Code
    {
        i8 const state = get_run_state();
        if (((state < PAUSED) && (state > UNINITIALIZED)) ||
            (state < EXITED && state >= RESUMING && state != STOPPED &&
             state != RESTARTED))
        {
            return Code::True;
        }
        return Code::False;
    }
    auto Run::increment_cycles() -> Code
    {
        if (is_running() == Code::True && Timers[0].is_running())
        {
            Cycles++;
        }
        if (Cycles > MaxCycles)
        {
            return do_exit();
        }
        return Code::Failure;
    }
    auto Run::set_max_cycles(u64 cycles) -> Code
    {
        if (cycles <= 0)
        {
            MaxCycles = INFINITY;
            return Code::Warning;
        }
        MaxCycles = cycles;
        return Code::Success;
    }

    auto Run::set_run_state(i32 rtarget) -> Code
    {
        Code rstatus = Code::None;
        i32 rstate = get_run_state();
        i32 i = 0;
        if (rstate == rtarget)
        {
            return set_run_status(Code::Success);
        }
        if (rtarget >= 1 && rtarget < 17)
        {
            while ((RUN_MAP[rstate][i] != -1) && (i < 8) && (rstatus != Code::Success))
            {
                if (RUN_MAP[rstate][i] == rtarget)
                {
                    rstate = rtarget;
                    rstatus = Code::Success;
                }
                i++;
            }
        }
        RunState = rstate;
        if (rstatus != Code::Success)
        {
            return set_run_status(Code::Failure);
        }
        return set_run_status(Code::Success);
    }
    auto Run::process_cycles() -> Code
    {
        increment_cycles();
        if (get_cycles() >= get_max_cycles() && get_max_cycles() > 0)
        {
            return do_exit();
        }
        return Code::Success;
    }
    auto Run::process_state(i32 state) -> Code
    {
        switch (state)
        {
        case INITIALIZING:
            if (set_run_status(do_init()) == Code::Success)
            {
                debug("Initialized", Code::Info);
                return Code::Initialized;
            }
            break;
        case STARTING:
            if (set_run_status(do_start()) == Code::Success)
            {
                debug("Started", Code::Info);
                return Code::Started;
            }
            break;
        case PAUSING:
            if (set_run_status(do_pause()) == Code::Success)
            {
                debug("Paused", Code::Info);
                return Code::Paused;
            }
            break;
        case RESUMING:
            if (set_run_status(do_resume()) == Code::Success)
            {
                debug("Resumed", Code::Info);
                return Code::Resumed;
            }
            break;
        case STOPPING:
            if (set_run_status(do_stop()) == Code::Success)
            {
                debug("Stopped", Code::Info);
                return Code::Stopped;
            }
            break;
        case RESTARTING:
            if (set_run_status(do_restart()) == Code::Success)
            {
                debug("Restarted", Code::Info);
                return Code::Restarted;
            }
            break;
        case EXITING:
            if (set_run_status(do_exit()) == Code::Success)
            {
                debug("Exited", Code::Info);
                return Code::Exited;
            }
            break;
        case KILLING:
            if (set_run_status(do_kill()) == Code::Success)
            {
                debug("Killed", Code::Info);
                return Code::Killed;
            }
            break;
        default:
            debug("Unknown state", Code::Error);
            break;
        }
        return Code::Failure;
    }
    auto Run::set_min_args(u32 min_args) -> Code
    {
        if (min_args == 0)
        {
            debug("Minimum number of arguments was set to 0.", Code::Info);
            return Code::Info;
        }
        MinArgs = min_args;
        return Code::Success;
    }
    auto Run::get_min_args() -> u32
    {
        if (MinArgs == 0)
        {
            debug("Minimum number of arguments is set to 0.", Code::Info);
            return 0;
        }
        if (MinArgs < 0)
        {
            debug("Minimum number of arguments is less than 0.", Code::Error);
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
            debug("Null pointer passed to popen().", Code::Error);
            return "";
        }
        i8 buffer[128];
        while (fgets(buffer, sizeof(buffer), in.get()) != nullptr)
        {
            output += buffer;
        }
        if (ferror(in.get()) != 0)
        {
            debug("Error while executing command.", Code::Error);
            return "";
        }
        debug("Command executed successfully.", Code::Info);
        return output;
    }
    auto Run::call(const i8p cmd) -> string
    {
        i8 buffer[128];
        string result;
        FILE* pipe = popen(cmd, "r");
        if (pipe == nullptr)
        {
            debug("Null pointer passed to popen().", Code::Error);
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

            debug("Error while executing command.", Code::Error);
            return "";
        }
        pclose(pipe);
        debug("Command executed successfully.", Code::Info);
        return result;
    }
    auto Run::exec(const i8p command, const i8p argv[]) -> Code
    {
        if (command == nullptr || argv == nullptr)
        {
            debug("Null pointer passed to Exec().", Code::Error);
            return Code::Failure;
        }
        string output = call(string(command) + " " + string(argv[0]));
        if (output.length() <= string::npos && output.length() > 0)
        {
            debug("Invalid command string passed.", Code::Error);
            return Code::Failure;
        }
        Output = output.substr(0, output.length() - 1);
        debug("Command Successfully Executed.", Code::Info);
        return Code::Success;
    }
    auto Run::parse(const string& cmd) -> string
    {
        if (cmd.length() <= string::npos && cmd.length() > 0)
        {
            debug("Invalid command string passed.", Code::Error);
            return "";
        }
        return cmd;
    }
    auto Run::parse(const i8p cmd) -> string
    {
        return { cmd };
    }
    auto Run::get_text(i32 name, const std::string& dlim) -> std::string
    {
        std::string txt[] = {
            (">-(" + con.get_user() + "@" + con.get_hostname() + ")-$ [" +
             get_input() + "]" + dlim),
            (" (State)=[" + get_state_string(get_run_state()) + "]" + dlim),
            (" (Cycles)=[" + std::to_string(get_cycles()) + "]" + dlim),
            (" (Timer)=[" + (Timers[0].get_string(TimeUnit::Second) + "s]") + dlim),
            (dlim + ExecText + dlim)
        };
        if (this->is_running() == Code::True)
        {
            TimerText = txt[3];
        }
        else if (Timers[0].is(TimerState::Paused))
        {
            txt[3] = TimerText;
        }
        std::string txt_out;
        if (name >= 0 && name < 5)
        {
            txt_out = txt[name];
        }
        else if (name == AllTxt)
        {
            for (i32 i = 0; i < 5; i++)
            {
                txt_out += txt[i];
            }
        }
        return txt_out;
    }
    auto Run::set_input(const std::string& input, bool format) -> Code
    {
        Input.clear();
        if (format)
        {
            for (i8 i : input)
            {
                if (i != '\0' && i != '\r' && i != cast<i8>(8))
                {
                    Input += i;
                }
            }
        }
        else
        {
            Input = input;
        }
        return Code::Success;
    }
    auto Run::set_output(const std::string& output, bool format) -> Code
    {
        Output.clear();
        if (format)
        {
            for (i8 o : output)
            {
                if (o != '\0' && o != '\r')
                {
                    Output.push_back(o);
                }
            }
        }
        else
        {
            Output = output;
        }
        return Code::Success;
    }
    auto Run::process_input() -> Code
    {
        i32 cur_state = get_run_state();
        if ((cur_state >= UNINITIALIZED) && (cur_state <= EXITED))
        {
            std::string in = get_input();
            if (con.key_hit() != 0)
            {
                i32 const i = con.get_char();
                i8 ch = static_cast<i8>(i);
                if ((ch != '\n') && (ch != '\r') && (ch != '\0'))
                {
                    if (ch == 8 || ch == 127 || ch == 27)
                    {
                        in = in.substr(0, in.size() - 1);
                    }
                    else
                    {
                        in += ch;
                    }
                    in.shrink_to_fit();
                    return set_input(in, true);
                }

                cur_state = get_cmd(in);
                if (cur_state != -1)
                {
                    return process_state(cur_state);
                }
                if (!in.empty() || ch == '\n')
                {
                    ExecText = (call(in));
                }
                return set_input("", false);
            }
            return Code::Success;
        }
        return Code::Failure;
    }

    auto Run::process_output() -> Code
    {
        if (Timer::now() >= TimeMax)
        {
            TimeMax = (Timer::now() + 10000000);
            con.clear_screen();
            flush(std::cout);
            flush(std::cerr);
            std::string const out = get_text(AllTxt);
            set_output(out, false);
            std::cout << get_output() << std::flush;
            return Code::Success;
        }
        return Code::None;
    }
} // namespace Origin