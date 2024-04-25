
#include "Timer.hpp"
namespace origin
{
    Timer::Timer() :
        Limit{ 100000000000 }, Name("Timer_" + std::to_string(Id) + "]-(Timer" + std::to_string(Id) + ")"), Id(timer_id++)
    {
    }

    Timer::Timer(const string _name) :
        Limit(10000000000)
    {
        timer_id = { ++timer_id };
        this->Name = "Timer_" + _name + "]-(Timer" + std::to_string(timer_id) + ")";
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

    bool Timer::Is(TimerState _state)
    {
        return this->State == _state;
    }
}; // namespace origin