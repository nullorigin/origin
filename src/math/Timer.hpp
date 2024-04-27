#ifndef TIMER_HPP
#define TIMER_HPP
#include "Basic.hpp"
#include "String.hpp"
#include <chrono>
#include <iostream>
#include <sstream>

namespace origin
{

    static ID timer_id = 0;
    enum class TimeUnit : u64
    {
        Nano = 1,
        Micro = 1000,
        Milli = 1000000,
        Second = 1000000000,
        Minute = 60000000000,
        Hour = 3600000000000,
        Day = 86400000000000,
        Week = 604800000000000
    };
    struct Duration
    {
    private:
        TimeUnit Tu{ TimeUnit::Nano };
        f128 Nano{ 0.0 };

    public:
        Duration() = default;
        explicit Duration(TimeUnit _tu) { Set(0.0, _tu); }
        Duration(const Duration&) = default;
        Duration(Duration&& /*unused*/) noexcept {}

        auto Nanoseconds() const -> f128;
        auto Microseconds() const -> f128;
        auto Milliseconds() const -> f128;
        auto Seconds() const -> f128;
        auto Minutes() const -> f128;
        auto Hours() const -> f128;
        auto Days() const -> f128;
        auto Weeks() const -> f128;
        auto operator=(const Duration& rhs) noexcept -> Duration&;
        ~Duration() = default;
        auto operator=(Duration&& /*unused*/) noexcept -> Duration&;
        explicit Duration(f128 nano, TimeUnit tu = TimeUnit::Nano);
        static auto Zero() -> Duration;
        auto Set(f128 nano) -> void;
        auto Set(f128 _nano, TimeUnit tu) -> void;
        auto Get(TimeUnit tu = TimeUnit::Nano) const -> Duration;
        auto GetString(TimeUnit tu = TimeUnit::Nano) const -> string;
        explicit operator i128() const;
        explicit operator string() const;

        auto operator+(const Duration& rhs) const -> Duration;
        auto operator-(const Duration& rhs) const -> Duration;

        auto operator*(const Duration& rhs) const -> Duration;
        auto operator/(const Duration& rhs) const -> Duration;
        auto operator+=(const Duration& rhs) -> Duration&;
        auto operator-=(const Duration& rhs) -> Duration&;
        auto operator*=(const Duration& rhs) -> Duration&;
        auto operator/=(const Duration& rhs) -> Duration&;
        auto operator++() -> Duration&;
        auto operator--() -> Duration&;
        auto operator-() const noexcept -> Duration;
        auto operator==(const Duration& rhs) const -> bool;
        auto operator!=(const Duration& rhs) const -> bool;
        auto operator<(const Duration& rhs) const -> bool;
        auto operator>(const Duration& rhs) const -> bool;
        auto operator<=(const Duration& rhs) const -> bool;
        auto operator>=(const Duration& rhs) const -> bool;
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
    private:
        Timer* Ptr = this;
        f128 Started{};
        f128 Resumed{};
        f128 Paused{};
        f128 Stopped{};
        f128 Restarted{};
        f128 Limit{};
        f128 Offset{};
        string Name{ "Timer" };
        ID Id{};
        TimerState State = TimerState::None;

    public:
        Timer();
        explicit Timer(const string& _name);
        ~Timer();
        static auto Nano() -> f128;
        static auto Micro() -> f128;
        static auto Milli() -> f128;
        static auto Sec() -> f128;
        static auto Min() -> f128;
        static auto Hour() -> f128;
        static auto Day() -> f128;
        static auto Week() -> f128;
        auto SetName(const string& name) -> void;
        auto SetLimit(const f128 _limit) -> void;
        static auto Now() -> f128;

        static auto GetID() -> ID;
        auto GetName() const -> string;
        auto GetStart() const -> f128;
        auto GetResumed() const -> f128;
        auto GetPaused() const -> f128;
        auto GetRemaining() const -> f128;
        auto GetElapsed() const -> f128;

        auto GetEnd() const -> f128;
        auto GetOffset() const -> f128;
        auto GetLimit() const -> f128;
        explicit Timer(TimerState _state);
        auto Set(TimerState _state) -> void;
        auto Is(TimerState _state) -> bool;
        auto Pause() -> bool;
        auto Resume() -> bool;
        auto Stop() -> bool;

        auto Start() -> bool;
        auto Restart() -> bool;

        auto IsRunning() const -> bool;
        [[nodiscard]] explicit operator Timer*()
        {
            this->Ptr = this;
            return this->Ptr;
        }

        auto operator=(const Timer* /*unused*/) noexcept -> Timer&;

        auto operator=(Timer** rhs) noexcept -> Timer&;
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