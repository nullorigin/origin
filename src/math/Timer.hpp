#ifndef TIMER_HPP
#define TIMER_HPP
#include "Basic.hpp"
#include "Message.hpp"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>
#include <ratio>
#include <sstream>
#include <string>
#include <utility>

namespace origin
{
    static ID TimerID = 0;
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
        f128 nano{ 0.0 };

    public:
        Duration() = default;
        explicit Duration(TimeUnit _tu) { Set(0.0, _tu); }
        Duration(const Duration&) = default;
        Duration(Duration&& /*unused*/) noexcept {}

        auto Nano() const -> f128
        {
            return nano;
        }
        auto Micro() const -> f128 { return (Nano() / 1000.0); }
        auto Milli() const -> f128 { return (Nano() / 1000000.0); }
        auto Sec() const -> f128 { return (Nano() / 1000000000.0); };
        auto Min() const -> f128 { return (Nano() / 60000000000.0); }
        auto Hour() const -> f128 { return (Nano() / 3600000000000.0); };
        auto Day() const -> f128 { return (Nano() / 86400000000000.0); }
        auto Week() const -> f128 { return (Nano() / 604800000000000.0); }
        auto operator=(const Duration& _rhs) noexcept -> Duration&
        {
            this->nano = _rhs.nano;
            return *this;
        }
        ~Duration() = default;
        auto operator=(Duration&&) noexcept -> Duration& { return *this; }
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
            this->nano = nano;
        }
        auto Set(f128 _nano, TimeUnit tu) -> void
        {
            this->Tu = tu;
            this->nano = _nano;
        }
        auto Get(TimeUnit tu = TimeUnit::Nano) -> Duration
        {
            return Duration(this->nano, tu);
        }
        auto GetString(TimeUnit tu = TimeUnit::Nano) -> std::string
        {
            std::stringstream ss = std::stringstream();
            ss.precision(20);
            ss << std::fixed;
            ss << (this->Nano()) << "ns";
            return ss.str();
        }
        explicit operator i128() const { return this->nano; }
        explicit operator std::string() { return GetString(); }

        auto operator+(const Duration& _rhs) const -> Duration
        {
            return Duration(this->nano + _rhs.nano);
        }
        auto operator-(const Duration& _rhs) const -> Duration
        {
            return Duration(this->nano - _rhs.nano);
        }

        auto operator*(const Duration& _rhs) const -> Duration
        {
            return Duration(this->nano * _rhs.nano);
        }
        auto operator/(const Duration& _rhs) const -> Duration
        {
            return Duration(this->nano / _rhs.nano);
        }
        auto operator+=(const Duration& _rhs) -> Duration&
        {
            Set(this->nano + _rhs.nano);
            return *this;
        }
        auto operator-=(const Duration& _rhs) -> Duration&
        {
            Set(this->nano - _rhs.nano);
            return *this;
        }
        auto operator*=(const Duration& _rhs) -> Duration&
        {
            Set(this->nano * _rhs.nano);
            return *this;
        }
        auto operator/=(const Duration& _rhs) -> Duration&
        {
            Set(this->nano / _rhs.nano);
            return *this;
        }
        auto operator++() -> Duration&
        {
            Set(this->nano + 1);
            return *this;
        }
        auto operator--() -> Duration&
        {
            Set(this->nano - 1);
            return *this;
        }
        auto operator-() const noexcept -> Duration
        {
            return Duration(-this->nano);
        }
        auto operator==(const Duration& _rhs) const -> bool
        {
            return this->nano == _rhs.nano;
        }
        auto operator!=(const Duration& _rhs) const -> bool
        {
            return this->nano != _rhs.nano;
        }
        auto operator<(const Duration& _rhs) const -> bool
        {
            return this->nano < _rhs.nano;
        }
        auto operator>(const Duration& _rhs) const -> bool
        {
            return this->nano > _rhs.nano;
        }
        auto operator<=(const Duration& _rhs) const -> bool
        {
            return this->nano <= _rhs.nano;
        }
        auto operator>=(const Duration& _rhs) const -> bool
        {
            return this->nano >= _rhs.nano;
        }
    };
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
        f128 started;
        f128 resumed;
        f128 paused;
        f128 stopped;
        f128 restarted;
        f128 limit;
        f128 offset;
        std::string name;
        ID id = {};
        TimerState state = TimerState::None;
        Timer();
        explicit Timer(std::string _name);
        ~Timer();
        static auto Nano() -> f128
        {
            std::chrono::duration now = std::chrono::high_resolution_clock::now().time_since_epoch();
            return (f128)now.count();
        }
        static auto Micro() -> f128 { return (Nano() / 1000.0); }
        static auto Milli() -> f128 { return (Nano() / 1000000.0); }
        static auto Sec() -> f128 { return (Nano() / 1000000000.0); };
        static auto Min() -> f128 { return (Nano() / 60000000000.0); }
        static auto Hour() -> f128 { return (Nano() / 3600000000000.0); };
        static auto Day() -> f128 { return (Nano() / 86400000000000.0); }
        static auto Week() -> f128 { return (Nano() / 604800000000000.0); }
        auto SetName(const std::string& name) -> void { this->name = name; }
        auto SetLimit(const f128 _limit) -> void
        {
            this->limit = _limit;
        }
        static auto Now() -> f128
        {
            return Timer::Nano();
        }

        auto GetID() const -> ID { return TimerID; }
        auto GetName() const -> std::string { return this->name; }
        auto GetStart() const -> f128 { return this->started; }
        auto GetResumed() const -> f128 { return this->resumed; }
        auto GetPaused() const -> f128 { return this->paused; }
        auto GetRemaining() const -> f128 { return GetEnd() - Now(); }
        auto GetElapsed() const -> f128
        {
            f128 elapsed{ 0 };
            if (state == TimerState::Started || state == TimerState::Resumed || state == TimerState::Paused)
            {
                elapsed = Now() - started - offset;
            }
            return elapsed;
        }

        auto GetEnd() const -> f128 { return this->limit + (this->started - this->offset); }
        auto GetOffset() const -> f128 { return this->offset; }
        auto GetLimit() const -> f128 { return this->limit; }
        explicit Timer(TimerState _state)
        {
            this->state = _state;
        }
        auto Set(TimerState _state) -> void { this->state = _state; }
        auto Is(TimerState _state) -> bool;
        auto Pause() -> bool
        {
            if (IsRunning() && !Is(TimerState::Paused))
            {
                state = TimerState::Paused;
                paused = Now();
                return true;
            }
            return false;
        }
        auto Resume() -> bool
        {
            if (Is(TimerState::Paused))
            {
                auto now = Now();
                state = TimerState::Resumed;
                offset += now - paused;
                return true;
            }

            return false;
        }
        auto Stop() -> bool
        {
            if (IsRunning())
            {
                stopped = Now();
                state = TimerState::Stopped;
                started = 0;
                resumed = 0;
                paused = 0;
                offset = 0;
                limit = 0;
                restarted = 0;
                return true;
            }

            return false;
        }

        auto Start() -> bool
        {
            if (Is(TimerState::Paused))
                return Resume();

            if (!IsRunning())
            {
                state = TimerState::Started;
                started = Now();
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

            state = TimerState::Restarted;
            if (Stop() && Start())
            {
                restarted = Now();
                return true;
            }
            return false;
        }

        auto IsRunning() -> bool
        {
            return (state == TimerState::Started || state == TimerState::Resumed);
        }
        [[nodiscard]] explicit operator Timer*()
        {
            this->Ptr = this;
            return this->Ptr;
        }

        auto operator=(const Timer*) noexcept -> Timer&
        {
            *this->Ptr = *this;
            return *this;
        }

        auto operator=(Timer** rhs) noexcept -> Timer&
        {
            this->Ptr = *rhs;
            return *this->Ptr;
        }
    };
    struct Time
    {
    private:
        static const u8 MaxTimers = 32;
        static f128 TimePoint[MaxTimers];
        static struct Timer Timers[MaxTimers];
        static u8 TimerCount;
        Time()
        {
            if (TimerCount < MaxTimers)
            {
                TimerCount++;
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
                TimePoint[id] = Nano();
                break;
            case TimeUnit::Micro:
                TimePoint[id] = Micro();
                break;
            case TimeUnit::Milli:
                TimePoint[id] = Milli();
                break;
            case TimeUnit::Second:
                TimePoint[id] = Sec();
                break;
            case TimeUnit::Minute:
                TimePoint[id] = Min();
                break;
            case TimeUnit::Hour:
                TimePoint[id] = Hour();
                break;
            case TimeUnit::Day:
                TimePoint[id] = Day();
                break;
            case TimeUnit::Week:
                TimePoint[id] = Week();
                break;
            default:
                break;
            }
            return TimePoint[id];
        }
        static auto Reset(ID id) -> void { TimePoint[id] = Nano(); }
        static auto ToString(ID id) -> std::string
        {
            return std::to_string(TimePoint[id]) + "ns";
        }
    };
} // namespace origin
#endif // TIMER_HPP