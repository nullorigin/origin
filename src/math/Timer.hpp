#ifndef TIMER_HPP
#define TIMER_HPP
#include "Basic.hpp"
#include <ctime>
#include <string>

namespace origin {
using ID = u8;
static ID TimerID = 0;
enum class TimeUnit : u8 {
  Nano = 0,
  Micro = 1,
  Milli = 2,
  Second = 3,
  Minute = 4,
  Hour = 5,
  Day = 6,
  Week = 7
};
struct Duration {
  i64 nano = 0;
  f64 micro = 0;
  f64 milli = 0;
  f64 second = 0;
  f64 minute = 0;
  f64 hour = 0;
  f64 day = 0;
  f64 week = 0;
  Duration() = default;
  Duration(const Duration &) = default;
  Duration(Duration &&) noexcept { *this = Duration(0); }
  ~Duration() = default;
  auto operator=(Duration &&) -> Duration & = default;
  explicit Duration(i64 _nano) : nano(_nano) { Set(_nano); }
  auto Set() -> i64 {
    Set(nano);
    return nano;
  }
  auto Set(i64 _nano) -> void {
    nano = _nano;
    micro = (f64)nano / 1000.0;
    milli = micro / 1000.0;
    second = milli / 1000.0;
    minute = second / 60.0;
    hour = minute / 60.0;
    day = hour / 24.0;
    week = day / 7.0;
  }
  auto Get() const -> i64 { return nano; }
  auto Get(TimeUnit _tu) -> f64 {
    Set();
    switch (_tu) {
    case TimeUnit::Nano:
      return nano;
    case TimeUnit::Micro:
      return micro;
    case TimeUnit::Milli:
      return milli;
    case TimeUnit::Second:
      return second;
    case TimeUnit::Minute:
      return minute;
    case TimeUnit::Hour:
      return hour;
    case TimeUnit::Day:
      return day;
    case TimeUnit::Week:
      return week;
    }
  }
  auto Set(TimeUnit _tu) -> i64 {
    Set();
    switch (_tu) {
    case TimeUnit::Nano:
      nano = i64(nano);
      Set(nano);
      break;
    case TimeUnit::Micro:
      micro = i64(nano / (1000LL));
      Set(micro * 1000LL);
      break;
    case TimeUnit::Milli:
      milli = i64(nano / (1000000LL));
      Set(milli * 1000000LL);
      break;
    case TimeUnit::Second:
      second = i64(nano / (1000000000LL));
      Set(second * 1000000000LL);
      break;
    case TimeUnit::Minute:
      minute = i64(nano / (1000000000LL * 60));
      Set(minute * 1000000000LL * 60);
      break;
    case TimeUnit::Hour:
      hour = i64(nano / (1000000000LL * 60 * 60));
      Set(hour * 1000000000LL * 60 * 60);
      break;
    case TimeUnit::Day:
      day = i64(nano / (1000000000LL * 60 * 60 * 24));
      Set(day * 1000000000LL * 60 * 60 * 24);
      break;
    case TimeUnit::Week:
      week = i64(nano / (1000000000LL * 60 * 60 * 24 * 7));
      Set(week * 1000000000LL * 60 * 60 * 24 * 7);
      break;
    }
    return nano;
  }
  explicit operator f64() const { return f64(nano); }
  explicit operator i64() const { return nano; }
  explicit operator u64() const { return u64(nano); }
  explicit operator std::string() const { return std::to_string(nano); }
  auto operator=(const Duration &_rhs) -> Duration & = default;
  auto operator+(const Duration &_rhs) -> Duration {
    Duration ret = *this;
    ret.nano += _rhs.nano;
    ret.micro += _rhs.micro;
    ret.milli += _rhs.milli;
    ret.second += _rhs.second;
    ret.minute += _rhs.minute;
    ret.hour += _rhs.hour;
    ret.day += _rhs.day;
    ret.week += _rhs.week;
    return ret;
  }
  auto operator-(const Duration &_rhs) -> Duration {
    Duration ret = *this;
    ret.nano -= _rhs.nano;
    ret.micro -= _rhs.micro;
    ret.milli -= _rhs.milli;
    ret.second -= _rhs.second;
    ret.minute -= _rhs.minute;
    ret.hour -= _rhs.hour;
    ret.day -= _rhs.day;
    ret.week -= _rhs.week;
    return ret;
  }
  auto operator+=(const Duration &_rhs) -> Duration & {
    *this = *this + _rhs;
    return *this;
  }
  auto operator-=(const Duration &_rhs) -> Duration & {
    *this = *this - _rhs;
    return *this;
  }
  auto operator-() -> Duration {
    Duration ret = *this;
    ret.nano = -ret.nano;
    ret.micro = -ret.micro;
    ret.milli = -ret.milli;
    ret.second = -ret.second;
    ret.minute = -ret.minute;
    ret.hour = -ret.hour;
    ret.day = -ret.day;
    ret.week = -ret.week;
    return ret;
  }
  auto operator==(const Duration &_rhs) const -> bool {
    return nano == _rhs.nano && micro == _rhs.micro && milli == _rhs.milli &&
           second == _rhs.second && minute == _rhs.minute &&
           hour == _rhs.hour && day == _rhs.day && week == _rhs.week;
  }
  auto operator!=(const Duration &_rhs) const -> bool {
    return !(*this == _rhs);
  }
  auto operator<(const Duration &_rhs) const -> bool {
    if (nano != _rhs.nano) {
      return nano < _rhs.nano;
    }
    if (micro != _rhs.micro) {
      return micro < _rhs.micro;
    }
    if (milli != _rhs.milli) {
      return milli < _rhs.milli;
    }
    if (second != _rhs.second) {
      return second < _rhs.second;
    }
    if (minute != _rhs.minute) {
      return minute < _rhs.minute;
    }
    if (hour != _rhs.hour) {
      return hour < _rhs.hour;
    }
    if (day != _rhs.day) {
      return day < _rhs.day;
    }
    if (week != _rhs.week) {
      return week < _rhs.week;
    }
    return false;
  }
  auto operator>(const Duration &_rhs) const -> bool {
    return !(*this < _rhs) && !(*this == _rhs);
  }
  auto operator<=(const Duration &_rhs) const -> bool {
    return !(*this > _rhs) || (*this == _rhs);
  }
  auto operator>=(const Duration &_rhs) const -> bool {
    return !(*this < _rhs) || (*this == _rhs);
  }
};
enum class TimerState : u8 {
  None = 0,
  Started = 1,
  Paused = 2,
  Resumed = 3,
  Stopped = 4,
  Restarted = 5
};
struct Timer {
  Duration TimeStarted;
  Duration TimeResumed;
  Duration TimePaused;
  Duration TimeStopped;
  Duration TimeRestarted;
  Duration TimeLimit;
  Duration TimeOffset;
  std::string TimerName;
  ID TimerID{};
  TimerState State = TimerState::None;
  Timer();
  Timer(const Timer &) = delete;
  Timer(Timer &&) = delete;
  explicit Timer(std::string name);
  ~Timer();
  auto operator=(const Timer & /*unused*/) -> Timer & { return *this; }
  auto operator=(Timer && /*unused*/) noexcept -> Timer & { return *this; }
  auto SetName(const std::string &name) -> void { TimerName = name; }
  auto SetLimit(const Duration &limit) -> void { TimeLimit = limit; }
  auto Now() const -> f64 {
    timespec ts{};
    clock_gettime(CLOCK_REALTIME, &ts);
    return (ts.tv_sec + ts.tv_nsec / 1000000000.0) - TimeOffset.Get();
  }
  auto GetID() const -> ID { return TimerID; }
  auto GetName() const -> std::string { return TimerName; }
  auto GetStart() const -> Duration { return TimeStarted; }
  auto GetResumed() const -> Duration { return TimeResumed; }
  auto GetPaused() const -> Duration { return TimePaused; }
  auto GetElapsed() -> Duration {
    if (IsRunning()) {
      return Duration(Now() - TimeStarted.Get() - TimeOffset.Get());
    }
    return Duration(0);
  }
  auto GetEnd() const -> Duration { return TimeStopped; }
  auto GetOffset() const -> Duration { return TimeOffset; }
  auto GetLimit() const -> Duration { return TimeLimit; }
  explicit Timer(TimerState _state) : State(_state) {}
  auto Set(TimerState _state) -> void { State = _state; }
  auto Is(TimerState state) -> bool;
  auto Pause() -> bool;
  auto Resume() -> bool;
  auto Stop() -> bool;
  auto Start() -> bool;
  auto Restart() -> bool;
  auto IsRunning() -> bool;
};
struct Time {
private:
  static const u8 MaxTimers = 32;
  static Duration TimePoint[MaxTimers];
  static struct Timer Timers[MaxTimers];
  static u8 TimerCount;
  Time() {
    if (TimerCount < MaxTimers) {
      TimerCount++;
    }
  }

public:
  static auto Nano() -> f64 {
    timespec ts{};
    ::clock_gettime(CLOCK_REALTIME, &ts);
    return (ts.tv_sec + ts.tv_nsec / 1000000000.0);
  }
  static auto Micro() -> f64 { return (Nano() / 1000.0); }
  static auto Milli() -> f64 { return (Nano() / 1000000.0); }
  static auto Sec() -> f64 { return (Nano() / 1000000000.0); };
  static auto Min() -> f64 { return (Nano() / 60000000000.0); }
  static auto Hour() -> f64 { return (Nano() / 3600000000000.0); };
  static auto Day() -> f64 { return (Nano() / 86400000000000.0); }
  static auto Week() -> f64 { return (Nano() / 604800000000000.0); }
  static auto Elapsed(ID id, TimeUnit _p = TimeUnit::Nano) -> Duration {
    TimePoint[id].Set(_p);
    return Duration(Nano() - TimePoint[id].Get());
  }
  static auto Reset(ID id) -> void { TimePoint[id].nano = Nano(); }
  static auto ToString(ID id) -> std::string {
    return std::to_string(TimePoint[id].nano) + "ns";
  }
};
} // namespace origin
#endif // TIMER_HPP