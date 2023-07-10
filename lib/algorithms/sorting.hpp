#pragma once

#include <vector>
#include <algorithm>

namespace sorting
{
    namespace details
    {
        // To heapify a subtree rooted with node i which is an index in arr[]. n is size of heap
        template <typename T>
        void heapify(std::vector<T>& arr_, size_t n_, size_t rootIdx_)
        {
            auto largestIdx {rootIdx_};
            auto leftIdx {2 * rootIdx_ + 1};
            auto rightIdx {2 * rootIdx_ + 2};

            if (leftIdx < n_ && arr_[leftIdx] > arr_[largestIdx])
            {
                largestIdx = leftIdx;
            }

            if (rightIdx < n_ && arr_[rightIdx] > arr_[largestIdx])
            {
                largestIdx = rightIdx;
            }

            if (largestIdx != rootIdx_)
            {
                std::swap(arr_[rootIdx_], arr_[largestIdx]);
                heapify(arr_, n_, largestIdx);
            }
        }

        template <typename T>
        void merge(std::vector<T> &arr_, size_t left_, size_t middle_, size_t right_)
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
        void merge_sort(std::vector<T> &arr_, size_t left_, size_t right_)
        {
            if (left_ >= right_)
            {
                return;
            }
            auto middle {left_+ (right_ - left_) / 2};
            merge_sort(arr_, left_, middle);
            merge_sort(arr_, middle + 1, right_);
            merge(arr_, left_, middle, right_);
        }

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
        void quick_sort(std::vector<T>& arr_, int low_, int high_)
        {
            if (low_ < high_)
            {
                auto partitionIdx {partition(arr_, low_, high_)};
                quick_sort(arr_, low_, partitionIdx - 1);
                quick_sort(arr_, partitionIdx + 1, high_);
            }
        }
    }

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

    template <typename T>
    void heapSort(std::vector<T>& arr_)
    {
        // Build heap (rearrange array)
        for (int i = arr_.size() / 2 - 1; i >= 0; --i)
        {
            details::heapify(arr_, arr_.size(), static_cast<size_t>(i));
        }

        // One by one extract an element from heap
        for (int i = arr_.size() - 1; i >= 0; --i)
        {
            // Move current root to end, call max heapify on the reduced heap
            std::swap(arr_[0], arr_[static_cast<size_t>(i)]);
            details::heapify(arr_, i, 0);
        }
    }

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

    template <typename T>
    void mergeSort(std::vector<T> &arr_)
    {
        details::merge_sort(arr_, 0 , arr_.size());
    }

    template <typename T>
    void quickSort(std::vector<T>& arr_)
    {
        details::quick_sort(arr_, 0, arr_.size() - 1);
    }

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

    template <typename T>
    void bucketSort(std::vector<T>& arr_)
    {
        std::vector<T> bucketVect[arr_.size()];
        const T max {*std::max_element(std::begin(arr_), std::end(arr_))};

        for (size_t i = 0; i < arr_.size(); ++i)
        {
            // We need max to fit bucketIdx in the tmp array
            const auto bucketIdx {std::min(static_cast<size_t>(arr_.size() * arr_[i] / max), arr_.size() - 1)};
            bucketVect[bucketIdx].emplace_back(arr_[i]);
        }

        // Sort individual buckets
        for (size_t i = 0; i < arr_.size(); ++i)
        {
            quickSort(bucketVect[i]);
        }

        // Concatenate all buckets into arr_
        size_t index = 0;
        for (size_t i = 0; i < arr_.size(); i++)
        {
            for (size_t j = 0; j < bucketVect[i].size(); ++j)
            {
                arr_[index++] = bucketVect[i][j];
            }
        }
    }
}
