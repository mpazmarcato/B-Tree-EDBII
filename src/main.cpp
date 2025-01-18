#include "BTree.hpp"
#include "Node.hpp"

#include <iostream>


int main() {


    std::cout << "Bem vindo(a) ao estoque do Brasil Material de Construção!!!!" << std::endl;
    int order;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;
    BTree *btree = new BTree(order);
    
    //teste na raiz vazia
    Node::Product product(20, "chave regulável 7' tramontina", 10);
    btree->insert(product);
    std::cout << btree->search(20)->id << std::endl;
    std::cout << "Passou o id" << std::endl;
    std::cout << btree->search(20)->name << std::endl;
    std::cout << "Passou o nome" << std::endl;
    std::cout << btree->search(20)->stock << std::endl;
    std::cout << "Passou o stock" << std::endl;

    //teste na raiz com um produto
    Node::Product product2(30, "tubo sold 20mm fortlev", 20);
    btree->insert(product2);
    std::cout << btree->search(30)->id << std::endl;
    std::cout << "Passou o id" << std::endl;
    std::cout << btree->search(30)->name << std::endl;
    std::cout << "Passou o nome" << std::endl;
    std::cout << btree->search(30)->stock << std::endl;
    std::cout << "Passou o stock" << std::endl;
    
    delete btree;
    return 0;

}
