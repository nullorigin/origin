#pragma once

#include "Timer.hpp"

namespace Origin {
Timer::Timer() {
  TimeStarted = 0;
  TimePaused = 0;
  TimeResumed = 0;
  TimeStopped = 0;
  TimeRestarted = 0;
  TimeOffset = 0;
  TimeLimit = 1000000000;
  TimerID = TimerID + 1;
  TimerName = "Timer_" + std::to_string(TimerID) + "]-(Timer" +
              std::to_string(TimerID) + ")";
}
Timer::Timer(std::string name) {
  TimeStarted = 0;
  TimePaused = 0;
  TimeResumed = 0;
  TimeStopped = 0;
  TimeRestarted = 0;
  TimeOffset = 0;
  TimeLimit = 1000000000;
  TimerID = TimerID + 1;
  TimerName = "Timer [" + std::to_string(TimerID) + "]-(" + name + ")";
}
Timer::~Timer() {
  State = TimerState::None;
  TimeResumed = 0;
  TimePaused = 0;
  TimeStarted = 0;
  TimeStopped = 0;
  TimeRestarted = 0;
  TimeOffset = 0;
  TimeLimit = 0;
  TimerName = "";
  TimerID = TimerID - 1;
}
bool Timer::Is(TimerState state) {
  if (U8(state) >= 0 && U8(state) <= 5) {
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
    TimeStopped = Time::Nano();
    State = TimerState::Stopped;
    return true;
  }
  return false;
}
auto Timer::Start() -> bool {
  if (Is(TimerState::None) || Is(TimerState::Stopped) ||
      Is(TimerState::Restarted)) {
    TimeStarted = Time::Nano();
    State = TimerState::Started;
    return true;
  }
  return false;
}
auto Timer::Restart() -> bool {
  if (!Is(TimerState::None)) {
    TimeResumed = 0;
    TimePaused = 0;
    TimeStarted = 0;
    TimeStopped = 0;
    TimeOffset = 0;
    TimeRestarted = Now();
    State = TimerState::Restarted;
    return true;
  }
  return false;
}
auto Timer::IsRunning() -> bool {
  return Is(TimerState::Started) || Is(TimerState::Resumed) ||
         Is(TimerState::Paused);
}
}; // namespace Origin