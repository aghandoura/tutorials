#include <cstdio>
#include <iostream>

constexpr bool is_prime_recursive(size_t number, size_t c)
{
  return (c*c > number) ? true : 
           (number % c == 0) ? false : 
              is_prime_recursive(number, c+1);
}

constexpr bool is_prime_func(size_t number)
{
  return (number <= 1) ? false : is_prime_recursive(number, 2);
}

int main(void)
{
    auto i = is_prime_func(5);
    if (i)
        std::cout <<"is prime " <<std::endl;
    else
        std::cout <<"is not prime " <<std::endl;
}
