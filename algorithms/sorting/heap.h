#include <vector>

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
void heapSort(std::vector<T>& arr_)
{
    // Build heap (rearrange array)
    for (int i = arr_.size() / 2 - 1; i >= 0; --i)
    {
        heapify(arr_, arr_.size(), static_cast<size_t>(i));
    }

    // One by one extract an element from heap
    for (int i = arr_.size() - 1; i >= 0; --i)
    {
        // Move current root to end, call max heapify on the reduced heap
        std::swap(arr_[0], arr_[static_cast<size_t>(i)]);
        heapify(arr_, i, 0);
    }
}
