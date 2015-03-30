#include "Timer.h"

namespace Hydra
{
	Timer::Timer()
	{
		timeSum = 0;
	}
    unsigned int Timer::getTime() const
    {
        return (SDL_GetTicks() - startTime) + timeSum;
    }
    void Timer::start()
    {
        startTime = SDL_GetTicks();
    }
    void Timer::stop()
    {
       	timeSum += SDL_GetTicks() - startTime;
    }
    void Timer::reset()
    {
    	timeSum = 0;
    }
    void Timer::setInterval(int ms)
    {
        timeInterval = ms;
    }
    bool Timer::hasIntervalPassed()
    {
        if (getTime() >= timeInterval)
            return true;
      	return false;
    }
}
