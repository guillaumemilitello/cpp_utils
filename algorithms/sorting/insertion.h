#include <vector>

template<typename T>
void insertionSort(std::vector<T>& arr_)
{
    for (size_t i = 1; i < arr_.size(); ++i)
    {
        auto tmp {arr_[i]};
        size_t j = i - 1;

        while (j >= 0 && arr_[j] > tmp)
        {
            arr_[j+1] = arr_[j]; // move one value over one place to the right
            j--;
        }
        arr_[j + 1] = tmp; // insert kth value in correct place relative to previous values
    }
}
