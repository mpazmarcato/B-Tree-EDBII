#include "BTree.hpp"
#include "Node.hpp"
#include <iostream>

int main() {
    std::cout << "Bem-vindo(a) ao estoque do Brasil Material de Construção!" << std::endl;

    int order;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;

    BTree* btree = new BTree(order);

    // Carrega os produtos do arquivo
    std::cout << "\n--- Carregando produtos do arquivo dadosB.txt ---" << std::endl;
    btree->loadFromFile("dadosB.txt");

    // Verificar se os produtos foram carregados corretamente
    for (int id : {85,101, 102, 103, 104, 105, 150}) { // IDs de exemplo
        Node::Product* result = btree->search(id);
        if (result != nullptr) {
            std::cout << "Produto encontrado: " << result->id << " - " << result->name
                      << " (Estoque: " << result->stock << ")" << std::endl;
        } else {
            std::cout << "Erro: Produto com ID " << id << " não encontrado!" << std::endl;
        }
    }

    // Finalizar
    delete btree;
    std::cout << "\nÁrvore construída com sucesso a partir do arquivo!" << std::endl;
    return 0;
}
