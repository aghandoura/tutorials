#pragma once

#include <chrono>


class Perf_timer
{

using clock_type = std::chrono::high_resolution_clock;
public:
    Perf_timer()
        :start_time {clock_type::now()}
         ,stop_time {}
    {
        start();
    }

    void start()
    {
        start_time = clock_type::now();
    }

    void stop()
    {
        stop_time = clock_type::now();
    }

    double get_seconds() const
    {
        return
            static_cast<double>(std::chrono::duration_cast<std::chrono::seconds>
                                (stop_time - start_time).count());
    }

    double get_mseconds() const
    {
        return
            static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>
                                (stop_time - start_time).count());
    }

    double get_useconds() const
    {
        return
            static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>
                                (stop_time - start_time).count());
    }

    double get_nseconds() const
    {
        return
            static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>
                                (stop_time - start_time).count());
    }
private:
    clock_type::time_point start_time;
    clock_type::time_point stop_time;

};
