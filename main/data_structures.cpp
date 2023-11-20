#include <iostream>
#include <avlset.hpp>
#include <redblackset.hpp>
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

    return 0;
}
