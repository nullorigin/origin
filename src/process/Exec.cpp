#include "Exec.hpp"
namespace Origin
{
    auto Run::Loop(f128 runtime) -> i32
    {
        if (runtime > 0)
        {
            Timers[0].SetLimit(runtime);
        }
        while ((GetState() < EXITED) && (Timers[0].GetRemaining() > 0))
        {
            ProcessCycles();
        }
        return 0;
    }
    auto Run::DoInit() -> bool
    {
        if (RunState == UNINITIALIZED)
        {
            if (SetState(INITIALIZING))
            {
                return SetState(INITIALIZED);
            }
        }
        return false;
    }
    auto Run::DoStart() -> bool
    {
        if (SetState(STARTING))
        {
            Timers[0].Start();
            return SetState(STARTED);
        }
        return false;
    }
    auto Run::DoPause() -> bool
    {
        if (SetState(PAUSING))
        {
            Timers[0].Pause();
            return SetState(PAUSED);
        }
        return false;
    }
    auto Run::DoResume() -> bool
    {
        if (SetState(RESUMING))
        {
            Timers[0].Resume();
            return SetState(RESUMED);
        }
        return false;
    }
    auto Run::DoStop() -> bool
    {
        if (SetState(STOPPING))
        {
            Timers[0].Stop();
            ResetCycles();
            return SetState(STOPPED);
        }

        return false;
    }
    auto Run::DoRestart() -> bool
    {
        if (SetState(RESTARTING))
        {
            Timers[0].Restart();
            ResetCycles();
            return SetState(RESTARTED);
        }
        return false;
    }
    auto Run::DoExit() -> bool
    {
        if (SetState(EXITING))
        {
            if (SetState(EXITED))
            {
                DoKill();
            }
        }
        return false;
    }
    auto Run::DoKill() -> bool
    {
        if (SetState(KILLING))
        {
            SetState(KILLED);
            ::exit(-1);
        }
        return false;
    }
    auto Run::GetArg(const string& command) -> string
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
    auto Run::GetCmd(const string& command) -> i32
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
    auto Run::IsRunning() const -> bool
    {
        i8 const state = GetState();
        return ((state < PAUSED) && (state > UNINITIALIZED)) ||
               (state < EXITED && state >= RESUMING && state != STOPPED &&
                state != RESTARTED);
    }
    auto Run::IncrementCycles() -> void
    {
        if (IsRunning())
        {
            Cycles++;
        }
        if (Cycles > MaxCycles)
        {
            DoExit();
        }
    }
    auto Run::SetMaxCycles(u64 cycles) -> i8
    {
        if (cycles <= 0)
        {
            MaxCycles = 1;
            return -1;
        }
        MaxCycles = cycles;
        return 0;
    }
    auto Run::SetStatus(bool status) -> bool
    {
        Status = status;
        return Status;
    }
    auto Run::SetState(i8 target) -> bool
    {
        bool status = false;
        i32 state = GetState();
        i8 i = 0;
        if (state == target)
        {
            return SetStatus(status);
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
        return SetStatus(status);
    }
    auto Run::ProcessCycles() -> i8
    {
        IncrementCycles();
        if (GetCycles() >= GetMaxCycles() && GetMaxCycles() != 0)
        {
            DoExit();
        }
        return 0;
    }
    auto Run::ProcessState(i8 state) -> i8
    {
        switch (state)
        {
        case INITIALIZING:
            if (SetStatus(DoInit()))
            {
                DBG("Initialized", INFO);
                return INITIALIZED;
            }
            break;
        case STARTING:
            if (SetStatus(DoStart()))
            {
                DBG("Started", INFO);
                return STARTED;
            }
            break;
        case PAUSING:
            if (SetStatus(DoPause()))
            {
                DBG("Paused", INFO);
                return PAUSED;
            }
            break;
        case RESUMING:
            if (SetStatus(DoResume()))
            {
                DBG("Resumed", INFO);
                return RESUMED;
            }
            break;
        case STOPPING:
            if (SetStatus(DoStop()))
            {
                DBG("Stopped", INFO);
                return STOPPED;
            }
            break;
        case RESTARTING:
            if (SetStatus(DoRestart()))
            {
                DBG("Restarted", INFO);
                return RESTARTED;
            }
            break;
        case EXITING:
            if (SetStatus(DoExit()))
            {
                DBG("Exited", INFO);
                return EXITED;
            }
            break;
        case KILLING:
            if (SetStatus(DoKill()))
            {
                DBG("Killed", INFO);
                return KILLED;
            }
            break;
        default:
            DBG("Unknown state", ERROR);
            break;
        }
        return -1;
    }
    auto Run::SetMinArgs(u8 min_args) -> void
    {
        if (min_args == 0)
        {
            DBG("Minimum number of arguments was set to 0.", INFO);
        }
        MinArgs = min_args;
    }
    auto Run::GetMinArgs() -> u8
    {
        if (MinArgs == 0)
        {
            DBG("Minimum number of arguments is set to 0.", INFO);
        }
        if (MinArgs < 0)
        {
            DBG("Minimum number of arguments is less than 0.", ERROR);
            MinArgs = 0;
        }
        return MinArgs;
    }
    auto Run::Call(const string& cmd) -> string
    {
        string output;
        std::unique_ptr<FILE, decltype(&pclose)> in{ popen(cmd.c_str(), "r"), pclose };
        if (!in)
        {
            DBG("Null pointer passed to popen().", ERROR);
            return "";
        }
        i8 buffer[128];
        while (fgets(buffer, sizeof(buffer), in.get()) != nullptr)
        {
            output += buffer;
        }
        if (ferror(in.get()) != 0)
        {
            DBG("Error while executing command.", ERROR);
            return "";
        }
        DBG("Command executed successfully.", INFO);
        return output;
    }
    auto Run::Call(const i8p cmd) -> string
    {
        i8 buffer[128];
        string result;
        FILE* pipe = popen(cmd, "r");
        if (pipe == nullptr)
        {
            DBG("Null pointer passed to popen().", ERROR);
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

            DBG("Error while executing command.", ERROR);
            return "";
        }
        pclose(pipe);
        DBG("Command executed successfully.", INFO);
        return result;
    }
    auto Run::Exec(const i8p command, const i8p argv[]) -> void
    {
        if (command == nullptr || argv == nullptr)
        {
            DBG("Null pointer passed to Exec().", ERROR);
            return;
        }
        string output = Call(string(command) + " " + string(argv[0]));
        if (output.length() <= string::npos && output.length() > 0)
        {
            DBG("Invalid command string passed.", ERROR);
            return;
        }
        Output = output.substr(0, output.length() - 1);
        DBG("Command Successfully Executed.", INFO);
    }
    auto Run::Parse(const string& cmd) -> string
    {
        if (cmd.length() <= string::npos && cmd.length() > 0)
        {
            DBG("Invalid command string passed.", ERROR);
            return "";
        }
        return cmd;
    }
} // namespace origin