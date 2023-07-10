#include <iostream>
#include <stream.hpp>
#include <random.hpp>
#include <sorting.hpp>
#include <searching.hpp>

int main(int argc, char *argv[])
{
    constexpr double MIN  {0};
    constexpr double MAX  {30};
    constexpr double SIZE {25000};

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::bubbleSort(doubleVect);
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::bucketSort(doubleVect);
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::heapSort(doubleVect);
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::insertionSort(doubleVect);
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::mergeSort(doubleVect);
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::quickSort(doubleVect);
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::selectionSort(doubleVect);
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        sorting::selectionSort(doubleVect); // precondition: arr is sorted (in ascending order)
        const auto indVect {getRandVect<size_t>(0, SIZE, 100)};
        std::for_each(indVect.begin(), indVect.end(), [&doubleVect](size_t i) { searching::binarySearch(doubleVect, doubleVect[i]); });
    }

    {
        auto doubleVect {getRandVect<double>(MIN, MAX, SIZE)};
        const auto indVect {getRandVect<size_t>(0, SIZE, 100)};
        std::for_each(indVect.begin(), indVect.end(), [&doubleVect](size_t i) { searching::linearSearch(doubleVect, doubleVect[i]); });
    }

    return 0;
}