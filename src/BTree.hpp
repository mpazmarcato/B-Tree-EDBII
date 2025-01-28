#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @class Classe BTree
 * @brief Uma classe que representa uma árvore B do gerenciador de estoque
 */

class BTree
{
public:
    int order;  ///< Ordem da árvore
    Node *root; ///< Ponteiro para a raiz da árvore

    /**
     * @brief Construtor da classe BTree
     * @param order Ordem da árvore
     */
    BTree(int order)
    {
        this->order = order;
        this->root = nullptr;
    }

    /**
     * @brief Destruidor da classe BTree
     */
    ~BTree()
    {
        delete root;
    }

    /**
     * @brief Imprime a árvore B em níveis.
     */
    void printLevel(Node *node, int level = 0)
    {
        if (node == nullptr)
        {
            return;
        }

        // Indentar para representar o nível do nó
        std::cout << std::string(level * 2, ' ') << "Nível " << level << ": ";

        // Exibe os produtos do nó
        for (const auto &product : node->products)
        {
            std::cout << "[" << product.id << "]";
        }
        std::cout << std::endl;

        // Chama recursivamente para os filhos
        for (Node *child : node->children)
        {
            if (child != nullptr)
            {
                printLevel(child, level + 1);
            }
        }
    }

    // // Se a árvore estiver vazia, não há nada para imprimir
    // if (!root)
    //     return;

    // std::queue<Node *> queue;
    // queue.push(root); // Começa pela raiz
    // int level = 0;

    // while (!queue.empty())
    // {
    //     int levelSize = queue.size();
    //     std::cout << "Nível " << level << ": ";

    //     // Processa todos os nós no nível atual
    //     for (int i = 0; i < levelSize; i++)
    //     {
    //         Node *currentNode = queue.front();
    //         queue.pop();

    //         // Imprime os IDs do nó atual entre colchetes
    //         std::cout << "[";
    //         for (int j = 0; j < currentNode->products.size(); j++)
    //         {
    //             std::cout << currentNode->products[j].id; // Imprime o ID
    //             if (j < currentNode->products.size() - 1)
    //             {
    //                 std::cout << ", "; // Separa os IDs por vírgula
    //             }
    //         }
    //         std::cout << "] ";

    //         // Adiciona os filhos do nó atual à fila para processamento no próximo nível
    //         for (Node *child : currentNode->children)
    //         {
    //             if (child != nullptr)
    //             {
    //                 queue.push(child);
    //             }
    //         }
    //     }

    //     std::cout << "\n"; // Quebra de linha para separar os níveis
    //     level++;
    // }

    /**
     * @brief Carrega todos os produtos de um arquivo dentro da árvore.
     * @param filename Caminho do arquivo.
     */
    void
    loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo: " << filename << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            // Localizar as chaves '{' e '}'
            size_t start = line.find("{");
            size_t end = line.find("}");
            if (start == std::string::npos || end == std::string::npos || end <= start)
            {
                std::cerr << "Linha inválida ignorada: " << line << "\n";
                continue;
            }

            // Extrair o conteúdo entre as chaves
            std::string content = line.substr(start + 1, end - start - 1);
            std::stringstream ss(content);

            // Extrair os campos separados por vírgula
            std::string idStr, name, stockStr;
            if (!std::getline(ss, idStr, ',') || !std::getline(ss, name, ',') || !std::getline(ss, stockStr, ','))
            {
                std::cerr << "Erro ao processar linha: " << line << "\n";
                continue;
            }

            // Limpar espaços em branco extras e aspas
            idStr.erase(0, idStr.find_first_not_of(" \t"));
            name.erase(0, name.find_first_not_of(" \t\""));
            name.erase(name.find_last_not_of(" \t\"") + 1);
            stockStr.erase(0, stockStr.find_first_not_of(" \t"));

            try
            {
                // Converte os valores para os tipos apropriados
                int id = std::stoi(idStr);
                int stock = std::stoi(stockStr);

                // Cria o produto e insere na árvore
                Node::Product product(id, name, stock);
                this->insert(product);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Erro ao converter dados: " << line << "! Detalhes: " << e.what() << "\n";
            }
        }

        file.close();
    }

    /**
     * @brief Método que insere um nó na árvore
     * @param node Nó a ser inserido
     */
    void insert(Node::Product product)
    {
        if (this->root == nullptr)
        { // Se a árvore estiver vazia, cria a raiz
            this->root = new Node(product, this->order);
        }
        else
        {
            if (this->root->products.size() == this->root->MAX_PRODUCTS)
            { // Se a raiz estiver cheia, cria uma nova raiz e realiza o split
                Node *newRoot = new Node(this->order);
                newRoot->children.push_back(this->root);
                split(newRoot, 0);
                this->root = newRoot;
            }

            insertNonFull(this->root, product); // Insere no nó apropriado
        }

        std::cout << "Produto inserido: ID = " << product.id
                  << ", Nome = " << product.name
                  << ", Estoque = " << product.stock << "\n";
    }

    /**
     * @brief Método que busca um nó na árvore
     * @param id Identificador do nó a ser buscado
     * @return Produto buscado
     */
    Node::Product *search(int id)
    {
        return searchRecursive(this->root, id);
    }

    /**
     * @brief Método que remove um produto na árvore com base em uma chave/produto
     * @param id Id do produto/chave
     */
    void remove(int id)
    {
        removeRecursive(id, this->root);
    }

private:
    /**
     * @brief Remove, de forma recursiva, um produto de um nó.
     * @param id Id do produto a ser removido.
     * @param root Nó onde será feita a busca.
     * @details Por ser um algoritmo recursivo, caso não seja encontrado o produto naquele nó específico,
     * o método será chamado novamente mas em um nó filho.
     */
    void removeRecursive(int id, Node *root)
    {
        int productIndex = 0;
        while (productIndex < root->products.size() && root->products.at(productIndex).id < id)
        {
            productIndex++;
        }

        // Encontrou o produto
        if (productIndex < root->products.size() && root->products.at(productIndex).id == id)
        {
            // Caso mais simples
            if (root->isLeaf())
            {
                removeLeaf(productIndex, root);
            }
            // Caso onde há a necessidade de "descer" o produto encontrado até uma folha
            else
            {
                removeNonLeaf(productIndex, root);
            }
        }
        // Não encontrou e vai decidir se continua procurando ou não
        else
        {
            // Não tem mais filhos onde buscar.
            if (root->isLeaf())
            {
                std::cout << "Produto com ID " << id << " não encontrado!\n";
                return;
            }

            bool isProductOnLastChild = productIndex == root->products.size();

            if (isProductOnLastChild && productIndex > root->products.size())
                removeRecursive(id, root->children.at(productIndex - 1));
            else
                removeRecursive(id, root->children.at(productIndex));
        }

        // Checa se o filho respeita o balanceamento e, se não, ajusta
        verifyBalance(productIndex, root);
    }

    void verifyBalance(int index, Node *root)
    {
        // Índice inválido
        if (index < 0 || index >= root->children.size())
        {
            return;
        }

        if (!root->children[index]->hasMinimumElements())
        {
            // Redistribuição à esquerda
            if (index != 0 && root->children[index - 1]->products.size() >= order)
            {
                redistribute(index, root, true);
            }
            // Redistribuição à direita
            else if (index != root->products.size() && root->children[index + 1]->products.size() >= order)
            {
                redistribute(index, root, false);
            }
            // Se não, concatena
            else
            {
                if (index == root->products.size())
                    index--;

                concatenate(index, root);
            }
        }
    }

    void redistribute(int index, Node *root, bool leftSibling = true)
    {
        Node *child = root->children.at(index);
        Node *sibling;

        // Se é distribuição com o irmão da esquerda,
        // child é o nó da direita.
        if (leftSibling)
        {
            sibling = root->children.at(index - 1);

            // Transfere o "pai" dos dois nós para o início do nó à direita
            child->products.insert(child->products.begin(), root->products[index - 1]);

            // Transfere o ponteiro do nó à esquerda para o nó à direita
            if (!child->isLeaf())
            {
                child->children.insert(child->children.begin(), sibling->children.back());
                sibling->children.pop_back();
            }

            // Define que o elemento "separador"/"pai" será o último elemento do nó à esquerda.
            root->products[index - 1] = sibling->products.back();
            sibling->products.pop_back();
        }
        else
        {
            sibling = root->children.at(index + 1);

            // Transfere o "pai" dos dois nós para o final do nó à esquerda
            child->products.push_back(root->products[index]);

            // Transfere o primeiro nó do irmão para o final.
            if (!child->isLeaf())
            {
                child->children.push_back(sibling->children.front());
                sibling->children.erase(sibling->children.begin());
            }

            // Define que o elemento "separador"/"pai" será o primeiro elemento do nó à direita.
            root->products[index] = sibling->products.front();
            sibling->products.erase(sibling->products.begin());
        }
    }

    /**
     * @brief Método auxiliar que apaga uma chave no nó.
     * @param productIndex Índice da chave/produto no nó.
     * @param node Ponteiro para o nó.
     */
    void removeLeaf(int productIndex, Node *node)
    {
        node->products.erase(node->products.begin() + productIndex);
    }

    /**
     * @brief Método auxiliar que apaga uma chave de um nó que não é folha.
     * @param productIndex Índice da chave/produto no nó.
     * @param node Ponteiro para o nó.
     * @details Esse método rebaixa um produto para outro nó, trocando-o com outro produto,
     * OU concatena dois nós em um. Após isso, em todos os casos, chama o método da remoção recursiva,
     * aplicando a remoção no nó em que se encontra o produto a ser removido.
     */
    void removeNonLeaf(int productIndex, Node *node)
    {
        Node::Product product = node->products.at(productIndex);

        // Determina se vai trocar com o antecessor ou sucessor do elemento
        if (node->children[productIndex]->products.size() >= order - 1) // Antecessor
        {
            // Primeiro busca pelo anterior,
            // Depois substitui no lugar do antigo,
            // E, ao final, remove a duplicação do elemento no nó de onde foi retirado.
            Node::Product predecessor = node->children[productIndex]->products.back();
            node->products.at(productIndex) = predecessor;
            removeRecursive(predecessor.id, node->children[productIndex]);
        }
        else if (node->children[productIndex + 1]->products.size() >= order - 1) // Sucessor
        {
            // Análogo ao processo acima.
            Node::Product successor = node->children[productIndex + 1]->products.front();
            node->products.at(productIndex) = successor;
            removeRecursive(successor.id, node->children[productIndex + 1]);
        }
        // Se não dá pra trocar, concatena nós e chama a remoção novamente neste nó.
        else
        {
            concatenate(productIndex, node);
            removeRecursive(product.id, node->children[productIndex]);
        }
    }

    /**
     * @brief Método que faz a concatenação entre nós.
     * @param index Índice do elemento "pai" entre nós.
     * @param root Nó principal e pai dos nós a serem concatenados.
     */
    void concatenate(int index, Node *root)
    {
        if (root->isLeaf())
            return;

        // Child será o novo nó gerado a partir da concatenação entre ele e o irmão.
        // Não há necessidade de criar um novo nó literalmente, é possível utilizar um já existente.
        Node *child = root->children[index];
        Node *sibling = root->children[index + 1];

        // Adiciona o elemento "separador" dentro do novo nó
        child->products.push_back(root->products[index]);

        // Transfere todos os produtos do irmão para o novo nó
        for (int i = 0; i < sibling->products.size(); ++i)
        {
            child->products.push_back(sibling->products[i]);
        }

        // Transfere também todos os ponteiros do irmão para o novo nó, caso possua
        if (!child->isLeaf())
        {
            for (int i = 0; i < sibling->children.size(); ++i)
            {
                child->children.push_back(sibling->children[i]);
            }
        }

        // Remove o elemento que foi inserido dentro do novo nó e está duplicado
        root->products.erase(root->products.begin() + index);
        // Remove o ponteiro extra sem utilidade.
        root->children.erase(root->children.begin() + index + 1);
    }

    /**
     * @brief Método que procura um produto na árvore de forma recursiva
     * @param node Nó a se realizar a busca
     * @param id Identificador do produto a ser buscado
     */
    Node::Product *searchRecursive(Node *node, int id)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        for (int i = 0; i < node->products.size(); i++)
        {
            if (node->products[i].id == id)
            {
                return &node->products[i];
            }
            else if (node->products[i].id > id)
            {
                if (i < node->children.size() && node->children[i] != nullptr)
                {
                    return searchRecursive(node->children[i], id);
                }
                else
                {
                    return nullptr;
                }
            }
        }

        // Se o id for maior que todos os ids do nó, então o nó filho do último índice é o próximo a ser visitado
        if (node->children.size() > node->products.size() && node->children[node->products.size()] != nullptr)
        {
            return searchRecursive(node->children[node->products.size()], id);
        }
        else
        {
            return nullptr;
        }
    }

    /**
     * @brief Método que insere um produto em um nó que não está cheio
     * @param node Ponteiro para o nó onde o produto será inserido
     */
    void insertNonFull(Node *node, Node::Product product)
    {
        int i = node->products.size() - 1;

        if (node->children.empty())
        {
            // Insere na folha e mantém a ordem
            node->products.push_back(product);
            while (i >= 0 && node->products[i].id > product.id)
            {
                std::swap(node->products[i + 1], node->products[i]);
                i--;
            }
        }
        else
        {
            // Encontra o filho apropriado
            while (i >= 0 && node->products[i].id > product.id)
                i--;

            i++;

            // Verifica se o filho está cheio
            if (node->children[i]->products.size() == node->MAX_PRODUCTS)
            {
                split(node, i);
                if (node->products[i].id < product.id)
                    i++;
            }
            insertNonFull(node->children[i], product);
        }
    }

    /**
     * @brief Método que divide um nó afim de manter o balanceamento
     * @param node Nó a ser dividido
     * @param index Índice do produto a ser promovido
     */
    void split(Node *parent, int index)
    {
        // Verifica se o índice é válido
        if (index < 0 || index >= parent->children.size())
            return;

        // Cria um novo nó dentro do pai que é irmão do nó atual.
        Node *fullChild = parent->children[index];
        if (!fullChild)
        {
            std::cout << "O filho com o índice" << index << "não existe!\n";
            return;
        }
        Node *newChild = new Node(fullChild->order);

        int mid = fullChild->order - 1; // Índice da chave do meio

        // Promove a chave do meio ao nó pai antes de alterar fullChild
        parent->products.insert(parent->products.begin() + index, fullChild->products[mid]);

        // Copie as últimas chaves do filho atual para o novo nó
        for (int j = mid + 1; j < fullChild->products.size(); j++)
        {
            newChild->products.push_back(fullChild->products[j]);
        }

        // Se o filho atual não for folha, copie os filhos para o novo nó
        if (!fullChild->isLeaf())
        {
            for (int j = mid + 1; j < fullChild->children.size(); j++)
            {
                newChild->children.push_back(fullChild->children[j]);
                // newChild->children.back()->parent = newChild; // Atualiza o pai dos filhos transferidos
            }
            fullChild->children.resize(mid + 1); // Ajuste o vetor de filhos do nó cheio
        }

        // Agora que o filho atual teve suas chaves transferidas, basta reduzir para adequar o tamanho atual.
        fullChild->products.resize(mid);

        // Inserir o novo nó como um novo filho do nó pai
        parent->children.insert(parent->children.begin() + index + 1, newChild);
    }
};

#endif