#include <iostream>
#include <avlset.hpp>
#include <redblackset.hpp>
#include <maxheap.hpp>
#include <graph.hpp>
#include <hash.hpp>
#include <queue.hpp>
#include <set.hpp>
#include <tree.hpp>
#include <trie.hpp>
#include <tuple_hash.hpp>

int main(int argc, char *argv[])
{
    AvlSet<int> avlSet;
    RedBlackSet<int> redBlackSet;
    for (int i : std::vector<int>{4, 6, 7, 8, 2, 10, 1, 9, 2, 3, 12, -1, 14, 15})
    {
        avlSet.push(i);
        redBlackSet.push(i);
    }
    std::cout << avlSet.to_tree_string() << std::endl;
    std::cout << redBlackSet.to_tree_string() << std::endl;


    MaxHeap<int> maxHeap;
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(15);
    maxHeap.push(15);
    maxHeap.push(15);
    maxHeap.push(50);
    maxHeap.push(40);

    std::cout << "Heap size: " << maxHeap.size() << std::endl;
    while (maxHeap.size() > 0)
    {
        std::cout << "Extracted max element: " << maxHeap.top() << std::endl;
        maxHeap.pop();
    }

    return 0;
}
