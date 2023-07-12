#include <iostream>
#include <functional>
#include <stream.hpp>
#include <random.hpp>
#include <sorting.hpp>
#include <searching.hpp>

#include "benchmark/benchmark.h"

template <class T>
using SortFunc = std::function<void(std::vector<T>&)>;

template <class T>
void BM_Sort(benchmark::State& state, SortFunc<T> F)
{
    const auto N {state.range(0)};
    auto doubleVect {getRandVect<T>(N)};
    while (state.KeepRunning())
    {
        F(doubleVect);
    }
    state.SetItemsProcessed(N * state.iterations());
}

template <class T>
void BM_bubbleSort(benchmark::State& state)
{
    BM_Sort<T>(state, &(sorting::bubbleSort<T>));
}

template <class T>
void BM_bucketSort(benchmark::State& state)
{
    BM_Sort<T>(state, &(sorting::bucketSort<T>));
}

template <class T>
void BM_heapSort(benchmark::State& state)
{
    BM_Sort<T>(state, &(sorting::heapSort<T>));
}

template <class T>
void BM_insertionSort(benchmark::State& state)
{
    BM_Sort<T>(state, &(sorting::insertionSort<T>));
}

template <class T>
void BM_mergeSort(benchmark::State& state)
{
    BM_Sort<T>(state, &(sorting::mergeSort<T>));
}

template <class T>
void BM_quickSort(benchmark::State& state)
{
    BM_Sort<T>(state, &(sorting::quickSort<T>));
}

template <class T>
void BM_selectionSort(benchmark::State& state)
{
    BM_Sort<T>(state, &(sorting::selectionSort<T>));
}

// {
//     auto doubleVect {getRandVect<T>(MIN, MAX, SIZE)};
//     sorting::selectionSort(doubleVect); // precondition: arr is sorted (in ascending order)
//     const auto indVect {getRandVect<size_t>(0, SIZE, 100)};
//     std::for_each(indVect.begin(), indVect.end(), [&doubleVect](size_t i) { searching::binarySearch(doubleVect, doubleVect[i]); });
// }

// {
//     auto doubleVect {getRandVect<T>(MIN, MAX, SIZE)};
//     const auto indVect {getRandVect<size_t>(0, SIZE, 100)};
//     std::for_each(indVect.begin(), indVect.end(), [&doubleVect](size_t i) { searching::linearSearch(doubleVect, doubleVect[i]); });
// }

#define ARGS \
    ->MinTime(2) \
    ->Arg(1<<8)

BENCHMARK_TEMPLATE1(BM_bubbleSort, double) ARGS;
BENCHMARK_TEMPLATE1(BM_bucketSort, double) ARGS;
BENCHMARK_TEMPLATE1(BM_heapSort, double) ARGS;
BENCHMARK_TEMPLATE1(BM_insertionSort, double) ARGS;
BENCHMARK_TEMPLATE1(BM_mergeSort, double) ARGS;
BENCHMARK_TEMPLATE1(BM_quickSort, double) ARGS;
BENCHMARK_TEMPLATE1(BM_selectionSort, double) ARGS;

BENCHMARK_MAIN();
