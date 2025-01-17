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
    std::cout << btree->order << std::endl;
    btree->sentinel->products[0].id = id;
    std::cout << "cadastrou o id" << std::endl;
    btree->sentinel->products[0].name = "Produto 1";
    std::cout << "cadastrou o nome" << std::endl;
    btree->sentinel->products[0].stock = 10;
    std::cout << "cadastrou o estoque" << std::endl;

    std::cout << btree->search(id)->id << std::endl;
    std::cout << btree->search(id)->name << std::endl;
    std::cout << btree->search(id)->stock << std::endl;

    delete btree;
    return 0;

}
