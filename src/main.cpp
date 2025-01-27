#include "BTree.hpp"
#include "Node.hpp"
#include <iostream>

int main() {
    std::cout << "Bem-vindo(a) ao estoque do Brasil Material de Construção!" << std::endl;

    int order;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;

    // Cria a árvore B com a ordem especificada
    BTree *btree = new BTree(order);

    // Teste na raiz vazia
    std::cout << "\n--- Teste: Inserção na raiz vazia ---" << std::endl;
    Node::Product product1(20, "chave regulável 7' tramontina", 10);
    btree->insert(product1);

    // Verificar se o produto foi inserido corretamente
    auto *result = btree->search(20);
    if (result != nullptr) {
        std::cout << "Produto encontrado: " << result->id << " - " << result->name
                  << " (Estoque: " << result->stock << ")" << std::endl;
    } else {
        std::cout << "Erro: Produto não encontrado!" << std::endl;
    }

    // Teste com múltiplos produtos
    std::cout << "\n--- Teste: Inserção de múltiplos produtos ---" << std::endl;
    Node::Product product2(30, "tubo sold 20mm fortlev", 20);
    Node::Product product3(10, "parafuso 5mm", 50);
    Node::Product product4(40, "martelo 10kg", 5);
    Node::Product product5(25, "broca de aço 8mm", 15);

    btree->insert(product2);
    btree->insert(product3);
    btree->insert(product4);
    btree->insert(product5);

    // Verificar as inserções
    for (int id : {30, 10, 40, 25}) {
        result = btree->search(id);
        if (result != nullptr) {
            std::cout << "Produto encontrado: " << result->id << " - " << result->name
                      << " (Estoque: " << result->stock << ")" << std::endl;
        } else {
            std::cout << "Erro: Produto com ID " << id << " não encontrado!" << std::endl;
        }
    }

    // Teste de divisão (split)
    std::cout << "\n--- Teste: Divisão da raiz ---" << std::endl;
    Node::Product product6(50, "serra elétrica", 7);
    btree->insert(product6);

    result = btree->search(50);
    if (result != nullptr) {
        std::cout << "Produto encontrado: " << result->id << " - " << result->name
                  << " (Estoque: " << result->stock << ")" << std::endl;
    } else {
        std::cout << "Erro: Produto com ID 50 não encontrado!" << std::endl;
    }

    // Testar chaves em diferentes níveis
    std::cout << "\n--- Teste: Inserção em níveis inferiores ---" << std::endl;
    Node::Product product7(15, "trena 5m", 12);
    Node::Product product8(35, "lixa d'água", 30);

    btree->insert(product7);
    btree->insert(product8);

    for (int id : {15, 35}) {
        result = btree->search(id);
        if (result != nullptr) {
            std::cout << "Produto encontrado: " << result->id << " - " << result->name
                      << " (Estoque: " << result->stock << ")" << std::endl;
        } else {
            std::cout << "Erro: Produto com ID " << id << " não encontrado!" << std::endl;
        }
    }

    // Finalizar
    delete btree;
    std::cout << "\nTeste concluído." << std::endl;
    return 0;
}
