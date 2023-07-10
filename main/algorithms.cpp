#include <iostream>
#include <stream.hpp>
#include <searching.hpp>

int main(int argc, char *argv[])
{
    const std::vector<double> doubleVect {0.01, 0.23, -0.04, 1.23, -15};
    std::cout << "input: " << doubleVect << std::endl;
    for (double i : std::vector<double>{0.01, 0.23, 1.23})
    {
        std::cout << "binarySearch " << i << "\t: " << binarySearch(doubleVect, i) << std::endl; // need to be sorted
        std::cout << "linearSearch " << i << "\t: " << linearSearch(doubleVect, i) << std::endl;
    }
    return 0;
}