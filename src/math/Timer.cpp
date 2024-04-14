
#include "Timer.hpp"
namespace origin {
Timer::Timer() {
  TimeStarted = Duration(0);
  TimePaused = Duration(0);
  TimeResumed = Duration(0);
  TimeStopped = Duration(0);
  TimeRestarted = Duration(0);
  TimeOffset = Duration(0);
  TimeLimit = Duration(1000000000);
  TimerID = TimerID + 1;
  TimerName = "Timer_" + std::to_string(TimerID) + "]-(Timer" +
              std::to_string(TimerID) + ")";
}
Timer::Timer(std::string name) {
  TimeStarted = Duration(0);
  TimePaused = Duration(0);
  TimeResumed = Duration(0);
  TimeStopped = Duration(0);
  TimeRestarted = Duration(0);
  TimeOffset = Duration(0);
  TimeLimit = Duration(1000000000);
  TimerID = TimerID + 1;
  TimerName = "Timer [" + std::to_string(TimerID) + "]-(" + name + ")";
}
Timer::~Timer() {
  State = TimerState::None;
  TimeResumed = Duration(0);
  TimePaused = Duration(0);
  TimeStarted = Duration(0);
  TimeStopped = Duration(0);
  TimeRestarted = Duration(0);
  TimeOffset = Duration(0);
  TimeLimit = Duration(1000000000);
  TimerName = "";
  TimerID = TimerID - 1;
}
bool Timer::Is(TimerState state) {
  if (u8(state) >= 0 && u8(state) <= 5) {
    return State == state;
  }
  return false;
}
auto Timer::Pause() -> bool {
  if (Is(TimerState::Started) || Is(TimerState::Resumed)) {
    TimePaused = GetElapsed();
    State = TimerState::Paused;
    return true;
  }
  return false;
}
auto Timer::Resume() -> bool {
  if (Is(TimerState::Paused)) {
    TimeResumed = GetElapsed();
    TimeOffset.Set(TimeResumed.Get() - TimePaused.Get());
    State = TimerState::Resumed;
    return true;
  }
  return false;
}
auto Timer::Stop() -> bool {
  if (!Is(TimerState::Stopped) && !Is(TimerState::None)) {
    TimeStopped = Duration(Time::Nano());
    State = TimerState::Stopped;
    return true;
  }
  return false;
}
auto Timer::Start() -> bool {
  if (Is(TimerState::None) || Is(TimerState::Stopped) ||
      Is(TimerState::Restarted)) {
    TimeStarted = Duration(Time::Nano());
    State = TimerState::Started;
    return true;
  }
  return false;
}
auto Timer::Restart() -> bool {
  if (!Is(TimerState::None)) {
    TimeResumed = Duration(0);
    TimePaused = Duration(0);
    TimeStarted = Duration(0);
    TimeStopped = Duration(0);
    TimeOffset = Duration(0);
    TimeRestarted = Duration(Now());
    State = TimerState::Restarted;
    return true;
  }
  return false;
}
auto Timer::IsRunning() -> bool {
  return Is(TimerState::Started) || Is(TimerState::Resumed) ||
         Is(TimerState::Paused);
}
}; // namespace origin