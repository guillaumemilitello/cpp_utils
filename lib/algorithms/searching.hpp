#pragma once

#include <vector>

namespace details
{
    template<typename T>
    bool binarySearch(const std::vector<T>& arr_, const T& v_, size_t low_, size_t high_)
    {
        if (low_ > high_)
        {
            return false;
        }
        const auto middle {(low_ + high_) / 2};
        if (arr_[middle] == v_)
        {
            return true;
        }
        else if (arr_[middle] > v_)
        {
            return binarySearch(arr_, v_, low_, middle - 1);
        }
        return binarySearch(arr_, v_, middle+1, high_);
    }
}

// precondition: arr is sorted (in ascending order)
template<typename T>
bool binarySearch(const std::vector<T>& arr_, const T& v_)
{
    return details::binarySearch(arr_, v_, 0, arr_.size() - 1);
}

template<typename T>
bool linearSearch(const std::vector<T>& arr_, const T& v_)
{
    for (unsigned i = 0; i < arr_.size(); i++)
    {
        if (arr_[i] == v_)
        {
            return true;
        }
        // for sequential search if the array is sorted, we can quit earlier
        if (arr_[i] > v_)
        {
            return false;
        }
    }
    return false;
}