#pragma once

#include <vector>

template<typename T>
class MaxHeap
{
public:
    void push(T value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop()
    {
        if (size() > 0)
        {
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);
        }
    }

    const T& top() const
    {
        return heap[0];
    }


    size_t size() const
    {
        return heap.size();
    }

private:
    std::vector<T> heap;

    void heapifyUp(size_t index)
    {
        while (index > 0)
        {
            const size_t parent {(index - 1) / 2};
            if (heap[index] > heap[parent])
            {
                std::swap(heap[index], heap[parent]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(size_t index)
    {
        const size_t size {heap.size()};
        while (2 * index + 1 < size)
        {
            const size_t leftChild  {2 * index + 1};
            const size_t rightChild {2 * index + 2};
            size_t largest {index};
            if (leftChild < size && heap[leftChild] > heap[largest])
            {
                largest = leftChild;
            }

            if (rightChild < size && heap[rightChild] > heap[largest])
            {
                largest = rightChild;
            }

            if (largest != index)
            {
                std::swap(heap[index], heap[largest]);
                index = largest;
            }
            else
            {
                break;
            }
        }
    }
};
