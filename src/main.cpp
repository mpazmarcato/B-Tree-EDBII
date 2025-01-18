#include "BTree.hpp"
#include "Node.hpp"

#include <iostream>


int main() {

    int order;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;
    Node::Product product(20, "caixa", 10);
    BTree *btree = new BTree(order);
    btree->insert(product);
    std::cout << btree->search(20)->id << std::endl;
    std::cout << "Passou o id" << std::endl;
    std::cout << btree->search(20)->name << std::endl;
    std::cout << "Passou o nome" << std::endl;
    std::cout << btree->search(20)->stock << std::endl;
    std::cout << "Passou o stock" << std::endl;
    
    delete btree;
    return 0;

}
