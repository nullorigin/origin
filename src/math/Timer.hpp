#ifndef TIMER_HPP
#define TIMER_HPP
#include "../origin.hpp"
#include <chrono>
#include <string>

namespace Origin {
static int TimerNumber;

struct Timer {
private:
  U64 TimeStarted = 0;
  U64 TimeResumed = 0;
  U64 TimePaused = 0;
  U64 TimeStopped = 0;
  U64 TimeRestarted = 0;
  U64 TimeLimit = 0;
  U64 TimeOffset = 0;
  std::string TimerName;

public:
  enum class TimerState : U8 {
    None = 0,
    Started = 1,
    Paused = 2,
    Resumed = 3,
    Stopped = 4,
    Restarted = 5
  };
  TimerState State = TimerState::None;
  Timer();
  Timer(std::string name);
  ~Timer();
  auto operator=(const Timer & /*unused*/) -> Timer & { return *this; }
  auto operator=(Timer && /*unused*/) noexcept -> Timer & { return *this; }
  Timer(Timer &&t) noexcept { *this = t; }
  Timer(const Timer &t) { *this = t; }
  auto GetName() -> std::string { return TimerName; }
  auto GetElapsed() -> U64;
  static auto GetNow() -> U64 { return NowNanoseconds(); }
  auto GetNowOffset() -> U64 { return (NowNanoseconds() - TimeOffset); }
  auto GetRemaining() -> U64 { return TimeLimit - GetElapsed(); }
  auto GetStart() -> U64 { return TimeStarted; }
  auto GetResumed() -> U64 { return TimeResumed; }
  auto GetPaused() -> U64 { return TimePaused; }
  auto GetEnd() -> U64 { return TimeStopped; }
  auto GetOffset() -> U64 { return TimeOffset; }
  auto GetLimit() -> U64 { return TimeLimit; }
  auto SetLimit(const U64 &limit) -> void { TimeLimit = limit; }
  auto SetName(const std::string &name) -> void { TimerName = name; }

  static auto GetMicroseconds(U64 nano) -> U64 { return nano / 1000; }
  static auto GetMiliseconds(U64 nano) -> U64 { return nano / 1000000; }
  static auto GetSeconds(U64 nano) -> U64 { return nano / 1000000000; }
  static auto NowNanoseconds() -> U64 {
    return std::chrono::steady_clock::now().time_since_epoch().count();
  }
  static auto NowMicroseconds() -> U64 { return NowNanoseconds() / 1000; }
  static auto NowMilliseconds() -> U64 { return NowNanoseconds() / 1000000; }
  static auto NowSeconds() -> U64 { return NowNanoseconds() / 1000000000; }
  static auto NowMinutes() -> U64 { return NowNanoseconds() / (60000000000LL); }
  static auto NowHours() -> U64 { return NowNanoseconds() / 3600000000000LL; }
  bool Is(TimerState state);
  auto Pause() -> bool;
  auto Resume() -> bool;
  auto Stop() -> bool;
  auto Start() -> bool;
  auto Restart() -> bool;
  auto IsRunning() -> bool;
};
} // namespace Origin
#endif // TIMER_HPP