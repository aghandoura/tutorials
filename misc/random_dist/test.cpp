#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

int main()
{
    // Seed with a real random value, if available
    std::random_device rd;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(1, 66);
    int mean = uniform_dist(e1);
    std::cout << "Randomly-chosen mean: " << mean << '\n';

    // Generate a normal distribution around that mean
    std::mt19937 e2(rd());
    std::uniform_int_distribution<int> dist(0 , mean);

    std::map<int, int> hist;
    for (int n = 0; n < 10000; ++n) {
        ++hist[dist(e2)];
    }
    std::cout << "uniform distribution around " << mean << ":\n";
    for (auto p : hist) {
        std::cout << p.first << ' ' << p.second<< '\n';
        }

    for (auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/20, '-') << '\n';
    }
}
