#ifndef TIMER_HPP
#define TIMER_HPP
#include "Basic.hpp"
#include <chrono>

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
        explicit Duration(TimeUnit tu) { set(0.0, tu); }
        Duration(const Duration&) = default;
        Duration(Duration&& /*unused*/) noexcept {}

        auto nanoseconds() const -> f128;
        auto microseconds() const -> f128;
        auto milliseconds() const -> f128;
        auto seconds() const -> f128;
        auto minutes() const -> f128;
        auto hours() const -> f128;
        auto days() const -> f128;
        auto weeks() const -> f128;
        auto operator=(const Duration& in) noexcept -> Duration&;
        ~Duration() = default;
        auto operator=(Duration&& /*unused*/) noexcept -> Duration&;
        explicit Duration(f128 nano, TimeUnit tu = TimeUnit::Nano);
        static auto zero() -> Duration;
        auto set(f128 nano) -> void;
        auto set(f128 _nano, TimeUnit tu) -> void;
        auto get(TimeUnit tu = TimeUnit::Nano) const -> Duration;
        auto getString(TimeUnit tu = TimeUnit::Nano) const -> string;
        explicit operator i128() const;
        explicit operator string() const;

        auto operator+(const Duration& in) const -> Duration;
        auto operator-(const Duration& in) const -> Duration;

        auto operator*(const Duration& in) const -> Duration;
        auto operator/(const Duration& in) const -> Duration;
        auto operator+=(const Duration& in) -> Duration&;
        auto operator-=(const Duration& in) -> Duration&;
        auto operator*=(const Duration& in) -> Duration&;
        auto operator/=(const Duration& in) -> Duration&;
        auto operator++() -> Duration&;
        auto operator--() -> Duration&;
        auto operator-() const noexcept -> Duration;
        auto operator==(const Duration& in) const -> bool;
        auto operator!=(const Duration& in) const -> bool;
        auto operator<(const Duration& in) const -> bool;
        auto operator>(const Duration& in) const -> bool;
        auto operator<=(const Duration& in) const -> bool;
        auto operator>=(const Duration& in) const -> bool;
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
        explicit Timer(const string& name);
        ~Timer();
        static auto nano() -> f128;
        static auto micro() -> f128;
        static auto milli() -> f128;
        static auto sec() -> f128;
        static auto min() -> f128;
        static auto hour() -> f128;
        static auto day() -> f128;
        static auto week() -> f128;
        auto setName(const string& name) -> void;
        auto setLimit(f128 in) -> void;
        static auto now() -> f128;

        static auto getId() -> ID;
        auto getName() const -> string;
        auto getStart() const -> f128;
        auto getResumed() const -> f128;
        auto getPaused() const -> f128;
        auto getRemaining() const -> f128;
        auto getElapsed() const -> f128;

        auto getEnd() const -> f128;
        auto getOffset() const -> f128;
        auto getLimit() const -> f128;
        explicit Timer(TimerState in);
        auto getString(TimeUnit tu) const -> string;
        auto set(TimerState in) -> void;
        auto is(TimerState in) const -> bool;
        auto pause() -> bool;
        auto resume() -> bool;
        auto stop() -> bool;

        auto start() -> bool;
        auto restart() -> bool;

        auto isRunning() const -> bool;
        [[nodiscard]] explicit operator Timer*()
        {
            this->Ptr = this;
            return this->Ptr;
        }

        auto operator=(const Timer* /*unused*/) noexcept -> Timer&;

        auto operator=(Timer** in) noexcept -> Timer&;
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
        static auto nano() -> f128
        {
            return std::chrono::high_resolution_clock::now().time_since_epoch().count();
        }
        static auto micro() -> f128 { return (nano() / 1000.0); }
        static auto milli() -> f128 { return (nano() / 1000000.0); }
        static auto sec() -> f128 { return (nano() / 1000000000.0); };
        static auto min() -> f128 { return (nano() / 60000000000.0); }
        static auto hour() -> f128 { return (nano() / 3600000000000.0); };
        static auto day() -> f128 { return (nano() / 86400000000000.0); }
        static auto week() -> f128 { return (nano() / 604800000000000.0); }
        static auto elapsed(ID id, TimeUnit tu = TimeUnit::Nano) -> f128
        {
            switch (tu)
            {
            case TimeUnit::Nano:
                time_point[id] = nano();
                break;
            case TimeUnit::Micro:
                time_point[id] = micro();
                break;
            case TimeUnit::Milli:
                time_point[id] = milli();
                break;
            case TimeUnit::Second:
                time_point[id] = sec();
                break;
            case TimeUnit::Minute:
                time_point[id] = min();
                break;
            case TimeUnit::Hour:
                time_point[id] = hour();
                break;
            case TimeUnit::Day:
                time_point[id] = day();
                break;
            case TimeUnit::Week:
                time_point[id] = week();
                break;
            default:
                break;
            }
            return time_point[id];
        }
        static auto reset(ID id) -> void { time_point[id] = nano(); }
        static auto toString(ID id) -> string
        {
            return std::to_string(time_point[id]) + "ns";
        }
    };
} // namespace origin
#endif // TIMER_HPP