#include <iostream>
#include <avlset.hpp>
#include <graph.hpp>
#include <hash.hpp>
#include <queue.hpp>
#include <set.hpp>
#include <tree.hpp>
#include <trie.hpp>
#include <tuple_hash.hpp>

int main(int argc, char *argv[])
{
    AvlSet<int> set;
    set.push(4);
    set.push(6);
    set.push(7);
    set.push(2);
    set.push(8);
    std::cout << set.to_tree_string() << std::endl;

    set.push(10);
    std::cout << set.to_tree_string() << std::endl;

    set.push(9);
    std::cout << set.to_tree_string() << std::endl;

    return 0;
}
