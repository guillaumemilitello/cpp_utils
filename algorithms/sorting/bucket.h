#include <vector>
#include <algorithm>

template <typename T>
void bucketSort(std::vector<T>& arr_)
{
    std::vector<T> tmp[arr_.size()];
    const T max {*std::max_element(std::begin(arr_), std::end(arr_))};

    for (size_t i = 0; i < arr_.size(); ++i)
    {
        // We need max to fit bucketIdx in the tmp array
        const auto bucketIdx {std::min(arr_.size() * arr_[i] / max, arr_.size() - 1)};
        tmp[bucketIdx].emplace_back(arr_[i]);
    }

    // Sort individual buckets
    for (size_t i = 0; i < arr_.size(); i++)
    {
        std::stable_sort(tmp[i].begin(), tmp[i].end());
    }

    // Concatenate all buckets into arr_
    size_t index = 0;
    for (size_t i = 0; i < arr_.size(); i++)
    {
        for (size_t j = 0; j < tmp[i].size(); ++j)
        {
            arr_[index++] = tmp[i][j];
        }
    }
}