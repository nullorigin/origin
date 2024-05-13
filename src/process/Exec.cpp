#include "Exec.hpp"
#include "Console.hpp"
#include "Message.hpp"
#include "Origin.hpp"
#include <functional>
#include <memory>
#include "Timer.hpp"
#include "Vector.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
namespace origin
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
    Run::Run()
    {
        setMaxCycles(0);
        setRunState(UNINITIALIZED);
    }
    Run::Run(i32 /*argc*/, i8** /*argv*/)
    {
        setMaxCycles(0);
        setRunState(UNINITIALIZED);
    }
    auto Run::loop(f128 runtime) -> Code
    {
        Run_status = setMaxCycles();
        if (runtime > 0)
        {
            Timers[0].setLimit(runtime);
        }
        else
        {
            Timers[0].setLimit(INFINITY);
        }
        doInit();
        while (true)
        {
            Run_status = processCycles();
            Run_status = processIO();

            if (getRunState() >= EXITING || Timers[0].getRemaining() <= 0)
            {
                return doExit();
            }
        }
        return doKill();
    }
    auto Run::doInit() -> Code
    {
        if (Run_state == UNINITIALIZED)
        {
            if (setRunState(INITIALIZING) == Code::Success)
            {
                Code code = setRunState(INITIALIZED);
                return code;
            }
        }
        return Code::Error;
    }
    auto Run::doStart() -> Code
    {
        if (setRunState(STARTING) == Code::Success)
        {
            Timers[0].start();
            return setRunState(STARTED);
        }
        return Code::Error;
    }
    auto Run::doPause() -> Code
    {
        if (setRunState(PAUSING) == Code::Success)
        {
            Timers[0].pause();
            return setRunState(PAUSED);
        }
        return Code::Failure;
    }
    auto Run::doResume() -> Code
    {
        if (setRunState(RESUMING) == Code::Success)
        {
            Timers[0].resume();
            return setRunState(RESUMED);
        }
        return Code::Failure;
    }
    auto Run::doStop() -> Code
    {
        if (setRunState(STOPPING) == Code::Success)
        {
            Timers[0].stop();
            resetCycles();
            return setRunState(STOPPED);
        }

        return Code::Failure;
    }
    auto Run::doRestart() -> Code
    {
        if (setRunState(RESTARTING) == Code::Success)
        {
            Timers[0].restart();
            resetCycles();
            return setRunState(RESTARTED);
        }
        return Code::Failure;
    }
    auto Run::doExit() -> Code
    {
        if (setRunState(EXITING) == Code::Success)
        {
            Timers[0].stop();
            resetCycles();
            Cycles = 0;
            try
            {
                std::exit(0);
            }
            catch (...)
            {
                debug("Failed to exit process.", Code::Error);
                return Code::Failure;
            }
            return setRunState(EXITED);
        }
        return Code::Failure;
    }
    auto Run::doKill() -> Code
    {
        Timers[0].stop();
        resetCycles();
        if (setRunState(KILLING) == Code::Success)
        {
            try
            {
                std::quick_exit(-1);
            }
            catch (...)
            {
                debug("Failed to kill process.", Code::Error);
                return setRunStatus(Code::Failure);
            }
            return setRunState(KILLED);
        }
        return Code::Failure;
    }
    auto Run::getArg(const string& command) -> string
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
    auto Run::getCmd(const string& command) -> u32
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
    auto Run::isRunning() const -> Code
    {
        i8 const state = getRunState();
        if (((state < PAUSED) && (state > UNINITIALIZED)) ||
            (state < EXITED && state >= RESUMING && state != STOPPED &&
             state != RESTARTED))
        {
            return Code::True;
        }
        return Code::False;
    }
    auto Run::incrementCycles() -> Code
    {
        if (isRunning() == Code::True && Timers[0].isRunning())
        {
            Cycles++;
        }
        if (Cycles > Max_cycles)
        {
            return doExit();
        }
        return Code::Failure;
    }
    auto Run::setMaxCycles(u64 cycles) -> Code
    {
        if (cycles <= 0)
        {
            Max_cycles = INFINITY;
            return Code::Warning;
        }
        Max_cycles = cycles;
        return Code::Success;
    }

    auto Run::setRunState(i32 rtarget) -> Code
    {
        Code rstatus = Code::None;
        i32 rstate = getRunState();
        i32 i = 0;
        if (rstate == rtarget)
        {
            return setRunStatus(Code::Success);
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
        Run_state = rstate;
        if (rstatus != Code::Success)
        {
            return setRunStatus(Code::Failure);
        }
        return setRunStatus(Code::Success);
    }
    auto Run::processCycles() -> Code
    {
        incrementCycles();
        if (getCycles() >= getMaxCycles() && getMaxCycles() > 0)
        {
            return doExit();
        }
        return Code::Success;
    }
    auto Run::processState(i32 state) -> Code
    {
        switch (state)
        {
        case INITIALIZING:
            if (setRunStatus(doInit()) == Code::Success)
            {
                debug("Initialized", Code::Info);
                return Code::Initialized;
            }
            break;
        case STARTING:
            if (setRunStatus(doStart()) == Code::Success)
            {
                debug("Started", Code::Info);
                return Code::Started;
            }
            break;
        case PAUSING:
            if (setRunStatus(doPause()) == Code::Success)
            {
                debug("Paused", Code::Info);
                return Code::Paused;
            }
            break;
        case RESUMING:
            if (setRunStatus(doResume()) == Code::Success)
            {
                debug("Resumed", Code::Info);
                return Code::Resumed;
            }
            break;
        case STOPPING:
            if (setRunStatus(doStop()) == Code::Success)
            {
                debug("Stopped", Code::Info);
                return Code::Stopped;
            }
            break;
        case RESTARTING:
            if (setRunStatus(doRestart()) == Code::Success)
            {
                debug("Restarted", Code::Info);
                return Code::Restarted;
            }
            break;
        case EXITING:
            if (setRunStatus(doExit()) == Code::Success)
            {
                debug("Exited", Code::Info);
                return Code::Exited;
            }
            break;
        case KILLING:
            if (setRunStatus(doKill()) == Code::Success)
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
    auto Run::setMinArgs(u32 min_args) -> Code
    {
        if (min_args == 0)
        {
            debug("Minimum number of arguments was set to 0.", Code::Info);
            return Code::Info;
        }
        Min_args = min_args;
        return Code::Success;
    }
    auto Run::getMinArgs() -> u32
    {
        if (Min_args == 0)
        {
            debug("Minimum number of arguments is set to 0.", Code::Info);
            return 0;
        }
        if (Min_args < 0)
        {
            debug("Minimum number of arguments is less than 0.", Code::Error);

            return Min_args = 0;
        }
        return Min_args;
    }
    auto Run::call(const string& cmd) -> string
    {
        string out;
        std::unique_ptr<FILE, decltype(&pclose)> in{ popen(cmd.c_str(), "r"), pclose };
        if (!in)
        {
            debug("Null pointer passed to popen().", Code::Error);
            setStatus(Code::Failure);
            return "";
        }
        i8 buffer[128];
        while (fgets(buffer, sizeof(buffer), in.get()) != nullptr)
        {
            out += buffer;
        }
        if (ferror(in.get()) != 0)
        {
            debug("Error while executing command.", Code::Error);
            setStatus(Code::Failure);
            return "";
        }
        debug("Command executed successfully.", Code::Info);
        return out;
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
        string out = call(string(command) + " " + string(argv[0]));
        if (out.length() <= string::npos && out.length() > 0)
        {
            debug("Invalid command string passed.", Code::Error);
            return Code::Failure;
        }
        Output = out.substr(0, out.length() - 1);
        debug("Command Successfully Executed.", Code::Info);
        return Code::Success;
    }
    auto Run::parse(const string& cmd) const -> string
    {
        if (cmd.length() <= string::npos && cmd.length() > 0)
        {
            debug("Invalid command string passed.", Code::Error);
            return "";
        }
        return cmd;
    }
    auto Run::getText(i32 name, const std::string& dlim) -> std::string
    {
        std::string txt[] = {
            (">-(" + con.getUser() + "@" + con.getHostname() + ")-$ [" +
             getInput() + "]" + dlim),
            (" (State)=[" + getStateString(getRunState()) + "]" + dlim),
            (" (Cycles)=[" + std::to_string(getCycles()) + "]" + dlim),
            (" (Timer)=[" + (Timers[0].getString(TimeUnit::Second) + "s]") + dlim),
            (dlim + Exec_text + dlim)
        };
        if (this->isRunning() == Code::True)
        {
            Timer_text = txt[3];
        }
        else if (Timers[0].is(TimerState::Paused))
        {
            txt[3] = Timer_text;
        }
        std::string txt_out;
        if (name >= 0 && name < 5)
        {
            txt_out = txt[name];
        }
        else if (name == ALL_TXT)
        {
            for (i32 i = 0; i < 5; i++)
            {
                txt_out += txt[i];
            }
        }
        return txt_out;
    }
    auto Run::setInput(const std::string& in, bool format) -> Code
    {
        Input.clear();
        if (format)
        {
            try
            {
                for (i8 i : in)
                {
                    if (i != '\0' && i != '\r' && i != cast<i8>(8))
                    {
                        Input += i;
                    }
                }
            }
            catch (...)
            {
                debug("Failed to format input.", Code::Error);
                return Code::Failure;
            }
        }
        else
        {
            Input = in;
        }
        return Code::Success;
    }
    auto Run::setOutput(const std::string& out, bool format) -> Code
    {
        Output.clear();
        if (format)
        {
            try
            {
                for (i8 o : out)
                {
                    if (o != '\0' && o != '\r')
                    {
                        Output.push_back(o);
                    }
                }
            }
            catch (...)
            {
                debug("Failed to format output.", Code::Error);
                return Code::Failure;
            }
        }
        else
        {
            Output = out;
        }
        return Code::Success;
    }
    auto Run::processOut() -> Code
    {
        if (Timer::now() >= Time_out_max)
        {
            Time_out_max = (Timer::now() + 10000000);
            try
            {
                con.clearScreen();
                flush(std::cout);
                flush(std::cerr);
                const std::string out = getText(ALL_TXT);
                if (setOutput(out, false) != Code::Success)
                {
                    return Code::Failure;
                }
                std::cout << getOutput() << std::flush;
            }
            catch (...)
            {
                return Code::Failure;
            }
        }
        return Code::Success;
    }
    auto Run::processIn() -> Code
    {
        i32 cur_state = getRunState();
        const Code rstatus = getRunStatus();
        if ((Timer::now() >= Time_in_max) && (rstatus != Code::Failure && rstatus != Code::Error))
        {
            Time_in_max = (Timer::now() + 10000);
            if ((cur_state > INITIALIZING) && (cur_state <= EXITED))
            {
                std::string in = getInput();
                if (con.keyHit() != 0)
                {
                    i32 const i = con.getChar();
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
                        return setInput(in, true);
                    }

                    cur_state = getCmd(in);
                    if (cur_state != -1)
                    {
                        return processState(cur_state);
                    }
                    if (!in.empty() || ch == '\n')
                    {
                        Exec_text = (call(in));
                    }
                    return setInput("", false);
                }
                return Code::Success;
            }
        }
        return rstatus;
    }
    auto Run::processIO() -> Code
    {
        Code rstatus = getRunStatus();
        const bool success = ((processIn() == Code::Success) && (processOut() == Code::Success) && (rstatus <= Code::Error) && (rstatus != Code::Failure));
        return (!success) ? Code::Failure : Code::Success;
    }

} // namespace origin