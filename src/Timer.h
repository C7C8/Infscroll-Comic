#include <SDL.h>

namespace Hydra
{
    class Timer
    {
    public:
        Timer();
        unsigned int getTime() const;        //!< Gets the time since the timer was started
        void start();               //!< Starts the timer
        void stop();                //!< Stops and resets the timer
        void reset();
        void setInterval(int ms);   //!< Sets the time period/interval
        bool hasIntervalPassed();   //!< Checks if the time period/interval has passed yet.
    private:
       unsigned int startTime;
       unsigned int timeInterval;
       unsigned int timeSum;
    };
}
