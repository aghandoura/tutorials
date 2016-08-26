#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <inttypes.h>
#include <chrono>

class my_timer
{
public:

    typedef std::chrono::high_resolution_clock clock_type;

    my_timer()
        : _start(clock_type::now())
        , _finish()
    {
        start();
    }

    void start()
    {
        _start = clock_type::now();
    }

    void finish()
    {
        _finish = clock_type::now();
    }

    double get_seconds() const
    {
        return
            static_cast<double>(std::chrono::duration_cast<std::chrono::seconds>
                               (_finish - _start).count());
    }

    double get_mseconds() const
    {
        return
            static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>
                               (_finish - _start).count());
    }
private:
    clock_type::time_point _start;
    clock_type::time_point _finish;
};

#endif
