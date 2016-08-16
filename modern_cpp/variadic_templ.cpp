#include <iostream>

template<typename T>
auto adder(T v)-> decltype(v)
{
    return v;
}

template <typename T, typename... Args>
auto adder(T first, Args... args) -> T
{
    return first + adder(args...);
}

int main(int argc, const char *argv[])
{
    auto sum = adder(1,1,1,1,1);
    std::cout << sum <<std::endl;
    auto sum_str = adder(std::string("hello "),std::string(" world "));
    std::cout <<sum_str <<std::endl;
    auto sum_mixed = adder(1.0,1.1,1,1,1);
    std::cout <<sum_mixed <<std::endl;
    return 0;
}
