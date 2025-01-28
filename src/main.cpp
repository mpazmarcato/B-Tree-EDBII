#include "BTree.hpp"
#include "Node.hpp"
#include <iostream>

int main()
{
    std::cout << "Bem-vindo(a) ao estoque do Brasil Material de Construção!\n";

    int order;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;

    BTree *btree = new BTree(order);

    // Carrega os produtos do arquivo
    std::cout << "\n--- Carregando produtos do arquivo dadosB.txt ---\n";
    btree->loadFromFile("dadosB.txt");
    btree->printLevel(btree->root);

    int id = -1;
    while (id != 0)
    {
        std::cout << "Insira um ID de produto que deseja eliminar: ";
        std::cin >> id;
        btree->remove(id);
        btree->printLevel(btree->root);
    }

    // Finalizar
    delete btree;
    return EXIT_SUCCESS;
}
