#include "BTree.hpp"
#include "Node.hpp"
#include <iostream>

int main()
{
    std::cout << "Bem-vindo(a) ao estoque do Brasil Material de Construção!" << std::endl;

    int order;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;

    BTree *btree = new BTree(order);

    // Carrega os produtos do arquivo
    std::cout << "\n--- Carregando produtos do arquivo dadosB.txt ---" << std::endl;
    btree->loadFromFile("dadosB.txt");
    btree->printTree(btree->root);

    int id = -1;
    while (id != 0)
    {
        std::cout << "Insira um ID de produto que deseja eliminar: ";
        std::cin >> id;
        btree->remove(id);
        std::cout << "Removido produto com ID " << id << "!\n";
        btree->printTree(btree->root);
    }

    // Finalizar
    delete btree;
    std::cout << "\nÁrvore construída com sucesso a partir do arquivo!" << std::endl;
    return 0;
}
