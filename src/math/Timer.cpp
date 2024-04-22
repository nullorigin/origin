
#include "Timer.hpp"
namespace origin
{
    Timer::Timer() :
        started{}, paused{}, resumed{}, stopped{}, restarted{}, limit{ 100000000000 }, offset(0.0), id(TimerID++)
    {
        name = "Timer_" + std::to_string(id) + "]-(Timer" + std::to_string(id) + ")";
    }

    Timer::Timer(const std::string _name) :
        started(0.0), resumed(0.0), paused(0.0), stopped(0.0), restarted(0.0), limit(10000000000), offset(0.0)
    {
        TimerID = { ++TimerID };
        this->name = "Timer_" + _name + "]-(Timer" + std::to_string(TimerID) + ")";
    }
    Timer::~Timer()
    {
        state = TimerState::None;
        resumed = 0.0;
        paused = 0.0;
        started = 0.0;
        stopped = 0.0;
        restarted = 0.0;
        offset = 0.0;
        limit = 1000000000;
        this->name.clear();
        TimerID--;
    }

    bool Timer::Is(TimerState _state)
    {
        return this->state == _state;
    }
}; // namespace origin