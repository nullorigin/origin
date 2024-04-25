#ifndef TIMER_HPP
#define TIMER_HPP
#include "Basic.hpp"
#include <chrono>
#include <iostream>
#include <sstream>

namespace origin
{

    static ID timer_id = 0;
    enum class TimeUnit : u8
    {
        Nano = 1,
        Micro = 2,
        Milli = 3,
        Second = 4,
        Minute = 5,
        Hour = 6,
        Day = 7,
        Week = 8
    };
    struct Duration
    {
    private:
        Duration* Ptr{ this };
        TimeUnit Tu{ TimeUnit::Nano };
        f128 Nano{ 0.0 };

    public:
        Duration() = default;
        explicit Duration(TimeUnit _tu) { Set(0.0, _tu); }
        Duration(const Duration&) = default;
        Duration(Duration&& /*unused*/) noexcept {}

        auto Nanoseconds() const -> f128
        {
            return Nano;
        }
        auto Microseconds() const -> f128 { return (Nanoseconds() / 1000.0); }
        auto Milliseconds() const -> f128 { return (Nanoseconds() / 1000000.0); }
        auto Seconds() const -> f128 { return (Nanoseconds() / 1000000000.0); };
        auto Minutes() const -> f128 { return (Nanoseconds() / 60000000000.0); }
        auto Hours() const -> f128 { return (Nanoseconds() / 3600000000000.0); };
        auto Days() const -> f128 { return (Nanoseconds() / 86400000000000.0); }
        auto Weeks() const -> f128 { return (Nanoseconds() / 604800000000000.0); }
        auto operator=(const Duration& _rhs) noexcept -> Duration&
        {
            this->Nano = _rhs.Nano;
            return *this;
        }
        ~Duration() = default;
        auto operator=(Duration&& /*unused*/) noexcept -> Duration& { return *this; }
        explicit Duration(f128 nano, TimeUnit tu = TimeUnit::Nano)
        {
            Set(nano, tu);
        }
        static auto Zero() -> Duration
        {
            return Duration(0);
        }
        auto Set(f128 nano) -> void
        {
            this->Nano = nano;
        }
        auto Set(f128 _nano, TimeUnit tu) -> void
        {
            this->Tu = tu;
            this->Nano = _nano;
        }
        auto Get(TimeUnit tu = TimeUnit::Nano) const -> Duration
        {
            return Duration(this->Nano, tu);
        }
        auto GetString(TimeUnit tu = TimeUnit::Nano) const -> string
        {
            std::stringstream ss = std::stringstream();
            ss.precision(20);
            ss << std::fixed;
            ss << (this->Nanoseconds()) << "ns";
            return ss.str();
        }
        explicit operator i128() const { return this->Nano; }
        explicit operator string() const { return GetString(); }

        auto operator+(const Duration& _rhs) const -> Duration
        {
            return Duration(this->Nano + _rhs.Nano);
        }
        auto operator-(const Duration& _rhs) const -> Duration
        {
            return Duration(this->Nano - _rhs.Nano);
        }

        auto operator*(const Duration& _rhs) const -> Duration
        {
            return Duration(this->Nano * _rhs.Nano);
        }
        auto operator/(const Duration& _rhs) const -> Duration
        {
            return Duration(this->Nano / _rhs.Nano);
        }
        auto operator+=(const Duration& _rhs) -> Duration&
        {
            Set(this->Nano + _rhs.Nano);
            return *this;
        }
        auto operator-=(const Duration& _rhs) -> Duration&
        {
            Set(this->Nano - _rhs.Nano);
            return *this;
        }
        auto operator*=(const Duration& _rhs) -> Duration&
        {
            Set(this->Nano * _rhs.Nano);
            return *this;
        }
        auto operator/=(const Duration& _rhs) -> Duration&
        {
            Set(this->Nano / _rhs.Nano);
            return *this;
        }
        auto operator++() -> Duration&
        {
            Set(this->Nano + 1);
            return *this;
        }
        auto operator--() -> Duration&
        {
            Set(this->Nano - 1);
            return *this;
        }
        auto operator-() const noexcept -> Duration
        {
            return Duration(-this->Nano);
        }
        auto operator==(const Duration& _rhs) const -> bool
        {
            return this->Nano == _rhs.Nano;
        }
        auto operator!=(const Duration& _rhs) const -> bool
        {
            return this->Nano != _rhs.Nano;
        }
        auto operator<(const Duration& _rhs) const -> bool
        {
            return this->Nano < _rhs.Nano;
        }
        auto operator>(const Duration& _rhs) const -> bool
        {
            return this->Nano > _rhs.Nano;
        }
        auto operator<=(const Duration& _rhs) const -> bool
        {
            return this->Nano <= _rhs.Nano;
        }
        auto operator>=(const Duration& _rhs) const -> bool
        {
            return this->Nano >= _rhs.Nano;
        }
    } __attribute__((aligned(32)));
    enum class TimerState : u8
    {
        None = 0,
        Started = 1,
        Paused = 2,
        Resumed = 3,
        Stopped = 4,
        Restarted = 5
    };
    struct Timer
    {
    protected:
        Timer* Ptr = this;

    public:
        f128 Started{};
        f128 Resumed{};
        f128 Paused{};
        f128 Stopped{};
        f128 Restarted{};
        f128 Limit{};
        f128 Offset{};
        string Name;
        ID Id = {};
        TimerState State = TimerState::None;
        Timer();
        explicit Timer(string _name);
        ~Timer();
        static auto Nano() -> f128
        {
            std::chrono::duration now = std::chrono::high_resolution_clock::now().time_since_epoch();
            return static_cast<f128>(now.count());
        }
        static auto Micro() -> f128 { return (Nano() / 1000.0); }
        static auto Milli() -> f128 { return (Nano() / 1000000.0); }
        static auto Sec() -> f128 { return (Nano() / 1000000000.0); };
        static auto Min() -> f128 { return (Nano() / 60000000000.0); }
        static auto Hour() -> f128 { return (Nano() / 3600000000000.0); };
        static auto Day() -> f128 { return (Nano() / 86400000000000.0); }
        static auto Week() -> f128 { return (Nano() / 604800000000000.0); }
        auto SetName(const string& name) -> void { this->Name = name; }
        auto SetLimit(const f128 _limit) -> void
        {
            this->Limit = _limit;
        }
        static auto Now() -> f128
        {
            return Timer::Nano();
        }

        static auto GetID() -> ID { return timer_id; }
        auto GetName() const -> string { return this->Name; }
        auto GetStart() const -> f128 { return this->Started; }
        auto GetResumed() const -> f128 { return this->Resumed; }
        auto GetPaused() const -> f128 { return this->Paused; }
        auto GetRemaining() const -> f128 { return GetEnd() - Now(); }
        auto GetElapsed() const -> f128
        {
            f128 elapsed{ 0 };
            if (State == TimerState::Started || State == TimerState::Resumed || State == TimerState::Paused)
            {
                elapsed = Now() - Started - Offset;
            }
            return elapsed;
        }

        auto GetEnd() const -> f128 { return this->Limit + (this->Started - this->Offset); }
        auto GetOffset() const -> f128 { return this->Offset; }
        auto GetLimit() const -> f128 { return this->Limit; }
        explicit Timer(TimerState _state) :
            State(_state)
        {
        }
        auto Set(TimerState _state) -> void { this->State = _state; }
        auto Is(TimerState _state) -> bool;
        auto Pause() -> bool
        {
            if (IsRunning() && !Is(TimerState::Paused))
            {
                State = TimerState::Paused;
                Paused = Now();
                return true;
            }
            return false;
        }
        auto Resume() -> bool
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
        auto Stop() -> bool
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

        auto Start() -> bool
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
        auto Restart() -> bool
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

        auto IsRunning() const -> bool
        {
            return (State == TimerState::Started || State == TimerState::Resumed);
        }
        [[nodiscard]] explicit operator Timer*()
        {
            this->Ptr = this;
            return this->Ptr;
        }

        auto operator=(const Timer* /*unused*/) noexcept -> Timer&
        {
            *this->Ptr = *this;
            return *this;
        }

        auto operator=(Timer** rhs) noexcept -> Timer&
        {
            this->Ptr = *rhs;
            return *this->Ptr;
        }
    } __attribute__((aligned(128))) __attribute__((packed));
    struct Time
    {
    private:
        static const u8 MAX_TIMERS = 32;
        static f128 time_point[MAX_TIMERS];
        static struct Timer timers[MAX_TIMERS];
        static u8 timer_count;
        Time()
        {
            if (timer_count < MAX_TIMERS)
            {
                timer_count++;
            }
        }

    public:
        static auto Nano() -> f128
        {
            return std::chrono::high_resolution_clock::now().time_since_epoch().count();
        }
        static auto Micro() -> f128 { return (Nano() / 1000.0); }
        static auto Milli() -> f128 { return (Nano() / 1000000.0); }
        static auto Sec() -> f128 { return (Nano() / 1000000000.0); };
        static auto Min() -> f128 { return (Nano() / 60000000000.0); }
        static auto Hour() -> f128 { return (Nano() / 3600000000000.0); };
        static auto Day() -> f128 { return (Nano() / 86400000000000.0); }
        static auto Week() -> f128 { return (Nano() / 604800000000000.0); }
        static auto Elapsed(ID id, TimeUnit _p = TimeUnit::Nano) -> f128
        {
            switch (_p)
            {
            case TimeUnit::Nano:
                time_point[id] = Nano();
                break;
            case TimeUnit::Micro:
                time_point[id] = Micro();
                break;
            case TimeUnit::Milli:
                time_point[id] = Milli();
                break;
            case TimeUnit::Second:
                time_point[id] = Sec();
                break;
            case TimeUnit::Minute:
                time_point[id] = Min();
                break;
            case TimeUnit::Hour:
                time_point[id] = Hour();
                break;
            case TimeUnit::Day:
                time_point[id] = Day();
                break;
            case TimeUnit::Week:
                time_point[id] = Week();
                break;
            default:
                break;
            }
            return time_point[id];
        }
        static auto Reset(ID id) -> void { time_point[id] = Nano(); }
        static auto ToString(ID id) -> string
        {
            return std::to_string(time_point[id]) + "ns";
        }
    };
} // namespace origin
#endif // TIMER_HPP