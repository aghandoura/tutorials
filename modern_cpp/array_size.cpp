#include <array>
#include <iostream>


//deduce array size at compile time
template <typename T, std::size_t N>
constexpr std::size_t array_size(T (&)[N]) noexcept
{
    return N;
}

int main(int argc, const char *argv[])
{
    int keyVals[] = {1,2,3,4,5,6,7,8};

    std::array<int, array_size(keyVals)> mappedVals;

    mappedVals.fill(5);
    for (auto& i : mappedVals) {
        std::cout << i;
    }
    return 0;
}

