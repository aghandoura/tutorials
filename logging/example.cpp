#define LOGGING_LEVEL_1

#include <assert.h>
#include <iostream>

#include "logger.hpp"

const int  MAX= 1000;
const char N=48;


template <long N>
struct print_as_warning
{
    //use overflow warning to pass the message
     char operator()() {return N + 256;}

};

constexpr long long cfib(long nmb) noexcept
{
    return ((nmb<=1) ? nmb : (cfib(nmb - 1) + cfib(nmb - 2)));
}

long long f[MAX] = {0};

long long fib(long n)
{
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return (f[n] = 1);

    if (f[n])
        return f[n];

    long long k = (n & 1) ? (n+1)/2 : n/2;

    f[n] = (n & 1) ? (fib(k)*fib(k) + fib(k-1) * fib(k-1))
                     : (2*fib(k-1) + fib(k)) * fib(k);
    return f[n];
}

int main(int argc, const char *argv[])
{
    int n = N;
    LOG("starting...");
    //static_assert(12586269025==fib(50), "correct answer");
    print_as_warning<cfib(N)>()();
    LOG_WARN("start computing");
    LOG(" val at runtime(optimized): ", fib(n) );
    LOG(" val at runtime(non optimized): ", cfib(n) );
//    LOG(" val at runtime(non optimized * 2): ", cfib(n * 2) );
    LOG_WARN("done computing");

    LOG_ERR("done");
    return 0;
}
