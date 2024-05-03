
#include "Timer.hpp"
namespace Origin
{
    Timer::Timer() :
        Limit(100000000000), Id(timer_id++)
    {
        Name = ("Timer_" + std::to_string(Id) + "]-(Timer" + std::to_string(Id) + ")");
    }
    Timer::Timer(const std::string& name) :
        Limit(100000000000), Id(timer_id++)
    {
        this->Name = "Timer_" + name + "]-(Timer" + std::to_string(timer_id) + ")";
    }
    Timer::~Timer()
    {
        State = TimerState::None;
        Resumed = 0.0;
        Paused = 0.0;
        Started = 0.0;
        Stopped = 0.0;
        Restarted = 0.0;
        Offset = 0.0;
        Limit = 1000000000;
        timer_id--;
    }

    bool Timer::Is(TimerState _state)
    {
        return this->State == _state;
    }
    auto Duration::Nanoseconds() const -> f128
    {
        return Nano;
    }
    auto Duration::Microseconds() const -> f128
    {
        return (Nanoseconds() / 1000.0);
    }
    auto Duration::Milliseconds() const -> f128
    {
        return (Nanoseconds() / 1000000.0);
    }
    auto Duration::Seconds() const -> f128
    {
        return (Nanoseconds() / 1000000000.0);
    };
    auto Duration::Minutes() const -> f128
    {
        return (Nanoseconds() / 60000000000.0);
    }
    auto Duration::Hours() const -> f128
    {
        return (Nanoseconds() / 3600000000000.0);
    };
    auto Duration::Days() const -> f128
    {
        return (Nanoseconds() / 86400000000000.0);
    }
    auto Duration::Weeks() const -> f128
    {
        return (Nanoseconds() / 604800000000000.0);
    }
    auto Duration::operator=(const Duration& rhs) noexcept -> Duration&
    {
        this->Nano = rhs.Nano;
        return *this;
    }
    auto Duration::operator=(Duration&& /*unused*/) noexcept -> Duration&
    {
        return *this;
    }
    Duration::Duration(f128 nano, TimeUnit tu)
    {
        Set(nano, tu);
    }
    auto Duration::Zero() -> Duration
    {
        return Duration(0);
    }
    auto Duration::Set(f128 nano) -> void
    {
        this->Nano = nano;
    }
    auto Duration::Set(f128 _nano, TimeUnit tu) -> void
    {
        this->Tu = tu;
        this->Nano = _nano;
    }
    auto Duration::Get(TimeUnit tu) const -> Duration
    {
        return Duration(this->Nano, tu);
    }
    auto Duration::GetString(TimeUnit tu) const -> string
    {
        std::stringstream ss = std::stringstream();
        ss.precision(9);
        ss << std::fixed;
        ss << (this->Nanoseconds() / (1000000000.0 / static_cast<f128>(tu)));
        return ss.str();
    }
    Duration::operator i128() const
    {
        return this->Nano;
    }
    Duration::operator string() const
    {
        return GetString();
    }
    auto Duration::operator+(const Duration& rhs) const -> Duration
    {
        return Duration(this->Nano + rhs.Nano);
    }
    auto Duration::operator-(const Duration& rhs) const -> Duration
    {
        return Duration(this->Nano - rhs.Nano);
    }
    auto Duration::operator*(const Duration& rhs) const -> Duration
    {
        return Duration(this->Nano * rhs.Nano);
    }
    auto Duration::operator/(const Duration& rhs) const -> Duration
    {
        return Duration(this->Nano / rhs.Nano);
    }
    auto Duration::operator+=(const Duration& rhs) -> Duration&
    {
        Set(this->Nano + rhs.Nano);
        return *this;
    }
    auto Duration::operator-=(const Duration& rhs) -> Duration&
    {
        Set(this->Nano - rhs.Nano);
        return *this;
    }
    auto Duration::operator*=(const Duration& rhs) -> Duration&
    {
        Set(this->Nano * rhs.Nano);
        return *this;
    }
    auto Duration::operator/=(const Duration& rhs) -> Duration&
    {
        Set(this->Nano / rhs.Nano);
        return *this;
    }
    auto Duration::operator++() -> Duration&
    {
        Set(this->Nano + 1);
        return *this;
    }
    auto Duration::operator--() -> Duration&
    {
        Set(this->Nano - 1);
        return *this;
    }
    auto Duration::operator-() const noexcept -> Duration
    {
        return Duration(-this->Nano);
    }
    auto Duration::operator==(const Duration& rhs) const -> bool
    {
        return this->Nano == rhs.Nano;
    }
    auto Duration::operator!=(const Duration& rhs) const -> bool
    {
        return this->Nano != rhs.Nano;
    }
    auto Duration::operator<(const Duration& rhs) const -> bool
    {
        return this->Nano < rhs.Nano;
    }
    auto Duration::operator>(const Duration& rhs) const -> bool
    {
        return this->Nano > rhs.Nano;
    }
    auto Duration::operator<=(const Duration& rhs) const -> bool
    {
        return this->Nano <= rhs.Nano;
    }
    auto Duration::operator>=(const Duration& rhs) const -> bool
    {
        return this->Nano >= rhs.Nano;
    }
    auto Timer::Nano() -> f128
    {
        std::chrono::duration now = std::chrono::high_resolution_clock::now().time_since_epoch();
        return static_cast<f128>(now.count());
    }
    auto Timer::Micro() -> f128
    {
        return (Nano() / 1000.0);
    }
    auto Timer::Milli() -> f128
    {
        return (Nano() / 1000000.0);
    }
    auto Timer::Sec() -> f128
    {
        return (Nano() / 1000000000.0);
    };
    auto Timer::Min() -> f128
    {
        return (Nano() / 60000000000.0);
    }
    auto Timer::Hour() -> f128
    {
        return (Nano() / 3600000000000.0);
    };
    auto Timer::Day() -> f128
    {
        return (Nano() / 86400000000000.0);
    }
    auto Timer::Week() -> f128
    {
        return (Nano() / 604800000000000.0);
    }
    auto Timer::SetName(const string& name) -> void
    {
        this->Name = name;
    }
    auto Timer::SetLimit(const f128 _limit) -> void
    {
        this->Limit = _limit;
    }
    auto Timer::Now() -> f128
    {
        return Timer::Nano();
    }
    auto Timer::GetID() -> ID
    {
        return timer_id;
    }
    auto Timer::GetName() const -> string
    {
        return this->Name;
    }
    auto Timer::GetStart() const -> f128
    {
        return this->Started;
    }
    auto Timer::GetResumed() const -> f128
    {
        return this->Resumed;
    }
    auto Timer::GetPaused() const -> f128
    {
        return this->Paused;
    }
    auto Timer::GetRemaining() const -> f128
    {
        return GetEnd() - Now();
    }
    auto Timer::GetElapsed() const -> f128
    {
        f128 elapsed{ 0 };
        if (State == TimerState::Started || State == TimerState::Resumed || State == TimerState::Paused)
        {
            elapsed = Now() - Started - Offset;
        }
        return elapsed;
    }
    auto Timer::GetEnd() const -> f128
    {
        return this->Limit + (this->Started - this->Offset);
    }
    auto Timer::GetOffset() const -> f128
    {
        return this->Offset;
    }
    auto Timer::GetLimit() const -> f128
    {
        return this->Limit;
    }
    Timer::Timer(TimerState _state) :
        State(_state)
    {
    }
    auto Timer::Set(TimerState _state) -> void
    {
        this->State = _state;
    }
    auto Timer::Pause() -> bool
    {
        if (IsRunning() && !Is(TimerState::Paused))
        {
            State = TimerState::Paused;
            Paused = Now();
            return true;
        }
        return false;
    }
    auto Timer::Resume() -> bool
    {
        if (Is(TimerState::Paused))
        {
            auto now = Now();
            State = TimerState::Resumed;
            Offset += now - Paused;
            return true;
        }

        return false;
    }
    auto Timer::Stop() -> bool
    {
        if (IsRunning())
        {
            Stopped = Now();
            State = TimerState::Stopped;
            Started = 0;
            Resumed = 0;
            Paused = 0;
            Offset = 0;
            Limit = 0;
            Restarted = 0;
            return true;
        }

        return false;
    }
    auto Timer::Start() -> bool
    {
        if (Is(TimerState::Paused))
        {
            return Resume();
        }

        if (!IsRunning())
        {
            State = TimerState::Started;
            Started = Now();
            return true;
        }

        return false;
    }
    auto Timer::Restart() -> bool
    {
        if (!IsRunning())
        {
            return false;
        }

        State = TimerState::Restarted;
        if (Stop() && Start())
        {
            Restarted = Now();
            return true;
        }
        return false;
    }
    auto Timer::IsRunning() const -> bool
    {
        return (State == TimerState::Started || State == TimerState::Resumed);
    }
    auto Timer::operator=(const Timer* /*unused*/) noexcept -> Timer&
    {
        *this->Ptr = *this;
        return *this;
    }
    auto Timer::operator=(Timer** rhs) noexcept -> Timer&
    {
        this->Ptr = *rhs;
        return *this;
    }
} // namespace Origin