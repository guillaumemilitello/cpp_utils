#include <vector>

template<typename T>
void selectionSort(std::vector<T>& arr_)
{
    for (size_t i = 0; i < arr_.size(); ++i)
    {
        auto min {arr_[i]};
        auto minIndex {i};
        for (size_t j = i + 1; j < arr_.size(); ++j)
        {
            if (arr_[j] < min)
            {
                min = arr_[j];
                minIndex = j;
            }
        }
        arr_[minIndex] = arr_[i];
        arr_[i] = min;
    }
}
