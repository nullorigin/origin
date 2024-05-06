
#include "Timer.hpp"
#include <sstream>
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

    bool Timer::is(TimerState _state)
    {
        return this->State == _state;
    }
    auto Duration::nanoseconds() const -> f128
    {
        return Nano;
    }
    auto Duration::microseconds() const -> f128
    {
        return (nanoseconds() / 1000.0);
    }
    auto Duration::milliseconds() const -> f128
    {
        return (nanoseconds() / 1000000.0);
    }
    auto Duration::seconds() const -> f128
    {
        return (nanoseconds() / 1000000000.0);
    };
    auto Duration::minutes() const -> f128
    {
        return (nanoseconds() / 60000000000.0);
    }
    auto Duration::hours() const -> f128
    {
        return (nanoseconds() / 3600000000000.0);
    };
    auto Duration::days() const -> f128
    {
        return (nanoseconds() / 86400000000000.0);
    }
    auto Duration::weeks() const -> f128
    {
        return (nanoseconds() / 604800000000000.0);
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
        set(nano, tu);
    }
    auto Duration::zero() -> Duration
    {
        return Duration(0);
    }
    auto Duration::set(f128 nano) -> void
    {
        this->Nano = nano;
    }
    auto Duration::set(f128 _nano, TimeUnit tu) -> void
    {
        this->Tu = tu;
        this->Nano = _nano;
    }
    auto Duration::get(TimeUnit tu) const -> Duration
    {
        return Duration(this->Nano, tu);
    }
    auto Duration::get_string(TimeUnit tu) const -> string
    {
        std::stringstream ss = std::stringstream();
        ss.precision(9);
        ss << std::fixed;
        ss << (this->nanoseconds() / static_cast<f128>(tu));
        return ss.str();
    }
    Duration::operator i128() const
    {
        return this->Nano;
    }
    Duration::operator string() const
    {
        return get_string();
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
        set(this->Nano + rhs.Nano);
        return *this;
    }
    auto Duration::operator-=(const Duration& rhs) -> Duration&
    {
        set(this->Nano - rhs.Nano);
        return *this;
    }
    auto Duration::operator*=(const Duration& rhs) -> Duration&
    {
        set(this->Nano * rhs.Nano);
        return *this;
    }
    auto Duration::operator/=(const Duration& rhs) -> Duration&
    {
        set(this->Nano / rhs.Nano);
        return *this;
    }
    auto Duration::operator++() -> Duration&
    {
        set(this->Nano + 1);
        return *this;
    }
    auto Duration::operator--() -> Duration&
    {
        set(this->Nano - 1);
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
    auto Timer::nano() -> f128
    {
        std::chrono::duration now = std::chrono::high_resolution_clock::now().time_since_epoch();
        return static_cast<f128>(now.count());
    }
    auto Timer::micro() -> f128
    {
        return (nano() / 1000.0);
    }
    auto Timer::milli() -> f128
    {
        return (nano() / 1000000.0);
    }
    auto Timer::sec() -> f128
    {
        return (nano() / 1000000000.0);
    };
    auto Timer::min() -> f128
    {
        return (nano() / 60000000000.0);
    }
    auto Timer::hour() -> f128
    {
        return (nano() / 3600000000000.0);
    };
    auto Timer::day() -> f128
    {
        return (nano() / 86400000000000.0);
    }
    auto Timer::week() -> f128
    {
        return (nano() / 604800000000000.0);
    }
    auto Timer::set_name(const string& name) -> void
    {
        this->Name = name;
    }
    auto Timer::set_limit(const f128 _limit) -> void
    {
        this->Limit = _limit;
    }
    auto Timer::now() -> f128
    {
        return Timer::nano();
    }
    auto Timer::get_id() -> ID
    {
        return timer_id;
    }
    auto Timer::get_name() const -> string
    {
        return this->Name;
    }
    auto Timer::get_start() const -> f128
    {
        return this->Started;
    }
    auto Timer::get_resumed() const -> f128
    {
        return this->Resumed;
    }
    auto Timer::get_paused() const -> f128
    {
        return this->Paused;
    }
    auto Timer::get_remaining() const -> f128
    {
        return get_end() - Timer::now();
    }
    auto Timer::get_elapsed() const -> f128
    {
        f128 elapsed = 0.0;
        if (State == TimerState::Started || State == TimerState::Resumed || State == TimerState::Paused)
        {
            return elapsed = now() - Started - Offset;
        }
        return elapsed;
    }
    auto Timer::get_end() const -> f128
    {
        return this->Limit + (this->Started - this->Offset);
    }
    auto Timer::get_offset() const -> f128
    {
        return this->Offset;
    }
    auto Timer::get_limit() const -> f128
    {
        return this->Limit;
    }
    Timer::Timer(TimerState _state) :
        State(_state)
    {
    }
    auto Timer::get_string(TimeUnit tu) const -> string
    {
        std::stringstream ss = std::stringstream();
        ss.precision(9);
        ss << std::fixed;
        ss << (get_elapsed() / static_cast<f128>(tu));
        return ss.str();
    }
    auto Timer::set(TimerState _state) -> void
    {
        this->State = _state;
    }
    auto Timer::pause() -> bool
    {
        if (is_running() && !is(TimerState::Paused))
        {
            State = TimerState::Paused;
            Paused = Timer::now();
            return true;
        }
        return false;
    }
    auto Timer::resume() -> bool
    {
        if (is(TimerState::Paused))
        {
            auto now = Timer::now();
            State = TimerState::Resumed;
            Offset += now - Paused;
            return true;
        }

        return false;
    }
    auto Timer::stop() -> bool
    {
        if (is_running())
        {
            Stopped = Timer::now();
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
    auto Timer::start() -> bool
    {
        if (is(TimerState::Paused))
        {
            return resume();
        }

        if (!is_running())
        {
            State = TimerState::Started;
            Started = Timer::now();
            return true;
        }

        return false;
    }
    auto Timer::restart() -> bool
    {
        if (!is_running())
        {
            return false;
        }

        State = TimerState::Restarted;
        if (stop() && start())
        {
            Restarted = now();
            return true;
        }
        return false;
    }
    auto Timer::is_running() const -> bool
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