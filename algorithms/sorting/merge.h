#include <vector>

template <typename T>
void mergeSort(std::vector<T> &arr_, size_t left_, size_t middle_, size_t right_)
{
    auto tmpLeftSize {middle_ - left_ + 1};
    auto tmpRightSize {right_ - middle_};
    T tmpLeft[tmpLeftSize], tmpRight[tmpRightSize];

    // Copy data to temp arrays tmpLeft[] and tmpRight[]
    for (size_t tmpLeftIdx = 0; tmpLeftIdx < tmpLeftSize; tmpLeftIdx++)
    {
        tmpLeft[tmpLeftIdx] = arr_[left_ + tmpLeftIdx];
    }
    for (size_t tmpRightIdx = 0; tmpRightIdx < tmpRightSize; tmpRightIdx++)
    {
        tmpRight[tmpRightIdx] = arr_[middle_ + 1 + tmpRightIdx];
    }

    // Merge the temp arrays back into arr_[left_..right_]
    size_t tmpLeftIdx = 0, tmpRightIdx = 0;
    size_t arrIdx = left_;

    while (tmpLeftIdx < tmpLeftSize && tmpRightIdx < tmpRightSize)
    {
        if (tmpLeft[tmpLeftIdx] <= tmpRight[tmpRightIdx])
        {
            arr_[arrIdx] = tmpLeft[tmpLeftIdx];
            ++tmpLeftIdx;
        }
        else
        {
            arr_[arrIdx] = tmpRight[tmpRightIdx];
            ++tmpRightIdx;
        }
        ++arrIdx;
    }

    // Copy the remaining elements of tmpLeft[], if there are any
    while (tmpLeftIdx < tmpLeftSize)
    {
        arr_[arrIdx] = tmpLeft[tmpLeftIdx];
        ++tmpLeftIdx;
        ++arrIdx;
    }

    // Copy the remaining elements of tmpRight[], if there are any
    while (tmpRightIdx < tmpRightSize)
    {
        arr_[arrIdx] = tmpRight[tmpRightIdx];
        ++tmpRightIdx;
        ++arrIdx;
    }
}

template <typename T>
void mergeSort(std::vector<T> &arr_, size_t left_, size_t right_)
{
    if (left_ >= right_)
    {
        return;
    }
    auto middle {left_+ (right_ - left_) / 2};
    mergeSort(arr_, left_, middle);
    mergeSort(arr_, middle + 1, right_);
    mergeSort(arr_, left_, middle, right_);
}


template <typename T>
void mergeSort(std::vector<T> &arr_)
{
    mergeSort(arr_, 0 , arr_.size());
}