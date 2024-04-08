#ifndef TIMER_HPP
#define TIMER_HPP
#include "../Origin.hpp"
#include <chrono>
#include <string>

namespace Origin {
static ID TimerID = 0;
enum class Precision : U8 {
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
  I64 nano = 0;
  F64 micro = 0;
  F64 milli = 0;
  F64 second = 0;
  F64 minute = 0;
  F64 hour = 0;
  F64 day = 0;
  F64 week = 0;
  Duration() = default;
  Duration(I64 _nano) : nano(_nano) { Set(_nano); }
  auto Set() -> I64 {
    Set(nano);
    return nano;
  }
  auto Set(I64 _nano) -> void {
    nano = _nano;
    micro = nano / 1000.0;
    milli = micro / 1000.0;
    second = milli / 1000, 0;
    minute = second / 60.0;
    hour = minute / 60.0;
    day = hour / 24.0;
    week = day / 7.0;
  }
  auto Get() -> I64 { return nano; }
  auto Get(Precision _p) -> F64 {
    Set();
    switch (_p) {
    case Precision::Nano:
      return nano;
    case Precision::Micro:
      return micro;
    case Precision::Milli:
      return milli;
    case Precision::Second:
      return second;
    case Precision::Minute:
      return minute;
    case Precision::Hour:
      return hour;
    case Precision::Day:
      return day;
    case Precision::Week:
      return week;
    }
  }
  auto Set(Precision _p) -> I64 {
    switch (_p) {
    case Precision::Nano:
      nano = I64(nano);
      break;
    case Precision::Micro:
      nano = I64(nano / (1000LL)) * I64(nano);
      break;
    case Precision::Milli:
      nano = I64(nano / (1000000LL)) * I64(nano);
      break;
    case Precision::Second:
      nano = I64(nano / (1000000000LL)) * I64(nano);
      break;
    case Precision::Minute:
      nano = I64(nano / (1000000000LL * 60)) * I64(nano);
      break;
    case Precision::Hour:
      nano = I64(nano / (1000000000LL * 60 * 60)) * I64(nano);
      break;
    case Precision::Day:
      nano = I64(nano / (1000000000LL * 60 * 60 * 24)) * I64(nano);
      break;
    case Precision::Week:
      nano = I64(nano / (1000000000LL * 60 * 60 * 24 * 7)) * I64(nano);
      break;
    }
    Set(nano);
    return nano;
  }
};
enum class TimerState : U8 {
  None = 0,
  Started = 1,
  Paused = 2,
  Resumed = 3,
  Stopped = 4,
  Restarted = 5
};
struct Timer {
  Duration TimeStarted = 0;
  Duration TimeResumed = 0;
  Duration TimePaused = 0;
  Duration TimeStopped = 0;
  Duration TimeRestarted = 0;
  Duration TimeLimit = 0;
  Duration TimeOffset = 0;
  std::string TimerName;
  ID TimerID;
  TimerState State = TimerState::None;
  Timer();
  Timer(std::string name);
  ~Timer();
  Timer(std::string name, std::function<void()> callback);
  auto operator=(const Timer & /*unused*/) -> Timer & { return *this; }
  auto operator=(Timer && /*unused*/) noexcept -> Timer & { return *this; }
  auto SetName(const std::string &name) -> void { TimerName = name; }
  auto SetLimit(const Duration &limit) -> void { TimeLimit = limit; }
  auto Now() -> F64 {
    return (std::chrono::steady_clock::now().time_since_epoch().count()) -
           TimeOffset.Get();
  }
  auto GetID() -> ID { return TimerID; }
  auto GetName() -> std::string { return TimerName; }
  auto GetStart() -> Duration { return TimeStarted; }
  auto GetResumed() -> Duration { return TimeResumed; }
  auto GetPaused() -> Duration { return TimePaused; }
  auto GetElapsed() -> Duration {
    if (IsRunning()) {
      return (Now() - TimeStarted.Get()) - TimeOffset.Get();
    }
    return 0;
  }
  auto GetEnd() -> Duration { return TimeStopped; }
  auto GetOffset() -> Duration { return TimeOffset; }
  auto GetLimit() -> Duration { return TimeLimit; }
  Timer(TimerState _state) { State = _state; }
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
  static const U8 MaxTimers = 32;
  static Duration TimePoint[MaxTimers];
  static struct Timer Timers[MaxTimers];
  static U8 TimerCount;
  Time() {
    if (TimerCount < MaxTimers) {
      TimerCount++;
    }
  }

public:
  static auto Nano() -> F64 {
    return (std::chrono::steady_clock::now().time_since_epoch().count());
  }
  static auto Micro() -> F64 { return (Nano() / 1000.0); }
  static auto Milli() -> F64 { return (Nano() / 1000000.0); }
  static auto Sec() -> F64 { return (Nano() / 1000000000.0); };
  static auto Min() -> F64 { return (Nano() / 60000000000.0); }
  static auto Hour() -> F64 { return (Nano() / 3600000000000.0); };
  static auto Day() -> F64 { return (Nano() / 86400000000000.0); }
  static auto Week() -> F64 { return (Nano() / 604800000000000.0); }
  static auto Elapsed(ID id, Precision _p = Precision::Nano) -> Duration {
    TimePoint[id].Set(_p);
    return Nano() - TimePoint[id].Get();
  }
  static auto Reset(ID id) -> void { TimePoint[id].nano = Nano(); }
  static auto ToString(ID id) -> std::string {
    return std::to_string(TimePoint[id].nano) + "ns";
  }
};
} // namespace Origin
#endif // TIMER_HPP