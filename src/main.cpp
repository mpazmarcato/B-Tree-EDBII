#include "BTree.hpp"
#include "Node.hpp"
#include <iostream>

int main()
{
    std::cout << "Bem-vindo(a) ao estoque do Brasil Material de Construção!\n";

    int order, operation = 0;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;

    BTree *btree = new BTree(order);

    // Carrega os produtos do arquivo
    std::cout << "\n--- Carregando produtos do arquivo dadosB.txt ---\n";
    btree->loadFromFile("dadosB.txt");
    std::cout << "====== ÁRVORE ATUAL ======\n";
    btree->printLevel(btree->root);

    do
    {
        std::cout << "Qual operação deseja fazer?\n"
                  << "0 - Sair\n"
                  << "1 - Listar\n"
                  << "2 - Buscar\n"
                  << "3 - Inserir \n"
                  << "4 - Remover\n";
        std::cin >> operation;

        switch (operation)
        {
        case 0:
            break;
        case 1:
            std::cout << "====== ÁRVORE ATUAL ======\n";
            btree->printLevel(btree->root);
            break;
        case 2:
        {
            int id;
            std::cout << "Insira o ID do produto a ser buscado: ";
            std::cin >> id;
            Node::Product *product = btree->search(id);
            if (product)
            {
                std::cout << "{" << product->id << ", '" << product->name << "', " << product->stock << "}\n";
            }
            else
            {
                std::cout << "Não existe produto com ID " << id << "\n";
            }
            break;
        }
        case 3:
        {
            int stock, id;
            std::string name;
            std::cout << "Insira o ID do produto: ";
            std::cin >> id;
            std::cout << "Insira o nome do produto: ";
            std::cin >> name;
            std::cout << "Insira a quantidade em estoque: ";
            std::cin >> stock;
            Node::Product product = Node::Product(id, name, stock);
            btree->insert(product);
            break;
        }
        case 4:
        {
            int id;
            std::cout << "Insira o ID do produto a ser removido: ";
            std::cin >> id;
            btree->remove(id);
            break;
        }

        default:
            std::cout << "Operação inválida! Tente novamente!\n";
            break;
        }
    } while (operation != 0);

    // Finalizar
    delete btree;
    return EXIT_SUCCESS;
}
