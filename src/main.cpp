#include "BTree.hpp"

#include <iostream>


int main() {

    int order;
    int id;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;
    std::cout << "Digite o id do primeiro produto: ";
    std::cin >> id;
    BTree *btree = new BTree(order);

    delete btree;
    return 0;

}
