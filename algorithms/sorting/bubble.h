#include <vector>

template <typename T>
void bubbleSort(std::vector<T>& arr_)
{
    for (size_t i = 0; i < arr_.size() - 1; ++i)
    {
        for (size_t j = 0; j < arr_.size() - i - 1; ++j)
        {
            if (arr_[j] > arr_[j+1])
            {
                std::swap(arr_[j], arr_[j+1]);
            }
        }
    }
}
