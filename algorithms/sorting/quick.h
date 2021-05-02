#include <vector>

// Takes the last element as pivot, put the pivot element at its correct position
// and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot
template <typename T>
int partition(std::vector<T>& arr_, int low_, int high_)
{
    T pivot {arr_[high_]};
    auto smallerElemIdx {low_ - 1};
    for (int j = low_; j <= high_ - 1; j++)
    {
        if (arr_[j] < pivot)
        {
            ++smallerElemIdx;
            std::swap(arr_[smallerElemIdx], arr_[j]);
        }
    }
    std::swap(arr_[smallerElemIdx + 1], arr_[high_]);
    return smallerElemIdx + 1;
}

template <typename T>
void quickSort(std::vector<T>& arr_, int low_, int high_)
{
    if (low_ < high_)
    {
        auto partitionIdx {partition(arr_, low_, high_)};
        quickSort(arr_, low_, partitionIdx - 1);
        quickSort(arr_, partitionIdx + 1, high_);
    }
}

template <typename T>
void quickSort(std::vector<T>& arr_)
{
    quickSort(arr_, 0, arr_.size() - 1);
}
