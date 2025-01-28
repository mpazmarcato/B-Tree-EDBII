#include "BTree.hpp"
#include "Node.hpp"
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int main()
{
    const std::string filename = "src/dadosB.txt";

    std::cout << "Bem-vindo(a) ao estoque do Brasil Material de Construção!\n";

    int order, operation = 0;
    std::cout << "Digite a ordem da árvore B: ";
    std::cin >> order;

    BTree *btree = new BTree(order);

    // Carrega os produtos do arquivo
    std::cout << "\n--- Carregando produtos do arquivo dadosB.txt ---\n";
    btree->loadFromFile(filename);

    std::cout << "====== ÁRVORE ATUAL ======\n";
    btree->printLevel();

    do
    {
        std::cout << "Qual operação deseja fazer?\n"
                  << "0 - Sair\n"
                  << "1 - Listar\n"
                  << "2 - Buscar\n"
                  << "3 - Inserir \n"
                  << "4 - Remover\n";
        std::cin >> operation;

        system(CLEAR);
        switch (operation)
        {
        case 0:
            break;
        case 1:
            std::cout << "====== ÁRVORE ATUAL ======\n";
            btree->printLevel();
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
            int stock;
            std::string name;
            std::cout << "Insira o nome do produto: ";
            std::cin >> name;
            std::cout << "Insira a quantidade em estoque: ";
            std::cin >> stock;

            if (stock < 0 || name.empty())
            {
                std::cout << "Dados inválidos! Não foi possível cadastrar. \n";
                break;
            }

            Node::Product product = Node::Product(name, stock);
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

    std::cout << "Agradecemos por visitar nossa loja!\n";

    delete btree;
    return EXIT_SUCCESS;
}
