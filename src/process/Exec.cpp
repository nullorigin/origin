#include "Exec.hpp"
namespace origin
{
    auto Run::Loop(f128 runtime) -> int
    {
        if (runtime > 0)
        {
            Timers[0].SetLimit(runtime);
        }
        while ((GetState() < Exited) && (Timers[0].GetRemaining() > 0))
        {
            ProcessCycles();
        }
        return 0;
    }
    auto Run::DoInit() -> bool
    {
        if (RunState == Uninitialized)
        {
            if (SetState(Initializing))
            {
                return SetState(Initialized);
            }
        }
        return false;
    }
    auto Run::DoStart() -> bool
    {
        if (SetState(Starting))
        {
            Timers[0].Start();
            return SetState(Started);
        }
        return false;
    }
    auto Run::DoPause() -> bool
    {
        if (SetState(Pausing))
        {
            Timers[0].Pause();
            return SetState(Paused);
        }
        return false;
    }
    auto Run::DoResume() -> bool
    {
        if (SetState(Resuming))
        {
            Timers[0].Resume();
            return SetState(Resumed);
        }
        return false;
    }
    auto Run::DoStop() -> bool
    {
        if (SetState(Stopping))
        {
            Timers[0].Stop();
            ResetCycles();
            return SetState(Stopped);
        }

        return false;
    }
    auto Run::DoRestart() -> bool
    {
        if (SetState(Restarting))
        {
            Timers[0].Restart();
            Output.clear();
            Input.clear();
            ResetCycles();
            return SetState(Restarted);
        }
        return false;
    }
    auto Run::DoExit() -> bool
    {
        if (SetState(Exiting))
        {
            if (SetState(Exited))
            {
                DoKill();
            }
        }
        return false;
    }
    auto Run::DoKill() -> bool
    {
        if (SetState(Killing))
        {
            SetState(Killed);
            ::exit(-1);
        }
        return false;
    }
    auto Run::GetArg(const std::string& command) -> std::string
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
    auto Run::GetCmd(const std::string& command) -> int
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
        return ((state < Paused) && (state > Uninitialized)) ||
               (state < Exited && state >= Resuming && state != Stopped &&
                state != Restarted);
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
    auto Run::SetMaxCycles(long cycles) -> i8
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
        int state = GetState();
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
        case Initializing:
            if (SetStatus(DoInit()))
            {
                DBG("Initialized", INFO);
                return Initialized;
            }
            break;
        case Starting:
            if (SetStatus(DoStart()))
            {
                DBG("Started", INFO);
                return Started;
            }
            break;
        case Pausing:
            if (SetStatus(DoPause()))
            {
                DBG("Paused", INFO);
                return Paused;
            }
            break;
        case Resuming:
            if (SetStatus(DoResume()))
            {
                DBG("Resumed", INFO);
                return Resumed;
            }
            break;
        case Stopping:
            if (SetStatus(DoStop()))
            {
                DBG("Stopped", INFO);
                return Stopped;
            }
            break;
        case Restarting:
            if (SetStatus(DoRestart()))
            {
                DBG("Restarted", INFO);
                return Restarted;
            }
            break;
        case Exiting:
            if (SetStatus(DoExit()))
            {
                DBG("Exited", INFO);
                return Exited;
            }
            break;
        case Killing:
            if (SetStatus(DoKill()))
            {
                DBG("Killed", INFO);
                return Killed;
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
    auto Run::Call(const std::string& cmd) -> std::string
    {
        std::string output;
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
    auto Run::Call(const char* cmd) -> std::string
    {
        i8 buffer[128];
        std::string result;
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
    auto Run::Exec(const char* command, char const* const argv[]) -> void
    {
        if (command == nullptr || argv == nullptr)
        {
            DBG("Null pointer passed to Exec().", ERROR);
            return;
        }
        std::string output = Call(std::string(command) + " " + std::string(argv[0]));
        if (output.length() <= std::string::npos && output.length() > 0)
        {
            DBG("Invalid command string passed.", ERROR);
            return;
        }
        Output = output.substr(0, output.length() - 1);
        DBG("Command Successfully Executed.", INFO);
    }
    auto Run::Parse(const std::string& cmd) -> std::string
    {
        if (cmd.length() <= std::string::npos && cmd.length() > 0)
        {
            DBG("Invalid command string passed.", ERROR);
            return "";
        }
        return cmd;
    }
} // namespace origin