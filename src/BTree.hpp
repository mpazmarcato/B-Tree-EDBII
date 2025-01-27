#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>


/**
 * @class Classe BTree
 * @brief Uma classe que representa uma árvore B do gerenciador de estoque
 */

class BTree {

    public:
    
        int order;  ///< Ordem da árvore
        Node *root; ///< Ponteiro para a raiz da árvore

        /**
         * @brief Construtor da classe BTree
         * @param order Ordem da árvore
         */
        BTree(int order) {
            this->order = order;
            this->root = nullptr;
        }

        /**
         * @brief Destruidor da classe BTree
         */
        ~BTree() {
            delete root;
        }

        /**
         * @brief Método que insere um nó na árvore
         * @param node Nó a ser inserido
         */
        void insert(Node::Product product) {
            if (this->root == nullptr) { // Se a árvore estiver vazia, cria a raiz
                this->root = new Node(product, this->order);
            } else {
                if (this->root->products.size() == this->root->MAX_PRODUCTS) { // Se a raiz estiver cheia, cria uma nova raiz e realiza o split
                    Node* newRoot = new Node(this->root->products[this->root->order - 1], this->order);
                    newRoot->children[0] = this->root;
                    split(newRoot, 0);
                    this->root = newRoot;
                }

                insertNonFull(this->root, product); // Insere no nó apropriado
            }
        }

         /**
         * @brief Método que insere um produto em um nó que não está cheio
         * @param node Ponteiro para o nó onde o produto será inserido
         */

       void insertNonFull(Node* node, Node::Product product) {
            int i = node->products.size() - 1;

            if (node->children.empty()) {
                // Insere na folha e ordena
                node->products.push_back(product);
                std::sort(node->products.begin(), node->products.end(), [](const Node::Product& a, const Node::Product& b) {
                    return a.id < b.id;
                });
                std::cout << "Produto inserido na folha. Total de produtos no nó: " << node->products.size() << std::endl;
            } else {
                // Encontra o filho apropriado
                while (i >= 0 && product.id < node->products[i].id) {
                    i--;
                }
                i++;

                // Inicializa o filho, se necessário
                if (node->children[i] == nullptr) {
                    node->children[i] = new Node(node->order);
                    node->children[i]->parent = node; // Atualiza o pai
                }

                // Verifica se o filho está cheio
                if (node->children[i]->isFull()) {
                    split(node, i);
                    if (product.id > node->products[i].id) {
                        i++;
                    }
                }

                // Insere recursivamente no filho apropriado
                insertNonFull(node->children[i], product);
            }
        }

        /**
         * @brief Método que busca um nó na árvore
         * @param id Identificador do nó a ser buscado
         * @return Produto buscado
         */
        Node::Product* search(int id) {
            return searchRecursive(this->root, id);
        }

        /**
         * @brief Método que remove um nó da árvore
         * @param id Ident
         */
        void *remove(int id);


        void loadFromFile(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
                return;
            }

            std::string line;
            while (std::getline(file, line)) {
                // Localizar as chaves '{' e '}'
                size_t start = line.find("{");
                size_t end = line.find("}");
                if (start == std::string::npos || end == std::string::npos || end <= start) {
                    std::cerr << "Linha inválida ignorada: " << line << std::endl;
                    continue;
                }

                // Extrair o conteúdo entre as chaves
                std::string content = line.substr(start + 1, end - start - 1);
                std::stringstream ss(content);

                // Extrair os campos separados por vírgula
                std::string idStr, name, stockStr;
                if (!std::getline(ss, idStr, ',') || !std::getline(ss, name, ',') || !std::getline(ss, stockStr, ',')) {
                    std::cerr << "Erro ao processar linha: " << line << std::endl;
                    continue;
                }

                // Limpar espaços em branco extras e aspas
                idStr.erase(0, idStr.find_first_not_of(" \t"));
                name.erase(0, name.find_first_not_of(" \t\""));
                name.erase(name.find_last_not_of(" \t\"") + 1);
                stockStr.erase(0, stockStr.find_first_not_of(" \t"));

                try {
                    // Converter os valores para os tipos apropriados
                    int id = std::stoi(idStr);
                    int stock = std::stoi(stockStr);

                    // Criar o produto e insere na árvore
                    Node::Product product(id, name, stock);
                    this->insert(product);

                    std::cout << "Produto inserido: ID = " << id
                            << ", Nome = " << name
                            << ", Estoque = " << stock << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Erro ao converter dados: " << line << ". Detalhes: " << e.what() << std::endl;
                }
            }

            file.close();
            std::cout << "Produtos carregados com sucesso do arquivo: " << filename << std::endl;
        }

    private: 
        
        /**
         * @brief Método que procura um produto na árvore de forma recursiva
         * @param node Nó a se realizar a busca
         * @param id Identificador do produto a ser buscado
         */
        Node::Product* searchRecursive(Node *node, int id) {
            
            if (node == nullptr) {
                return nullptr;
            }
            for (int i = 0; i < node->products.size(); i++) {
                if (node->products[i].id == id) {
                    return &node->products[i];
                } else if (node->products[i].id > id) {
                    return searchRecursive(node->children[i], id);
                } 
            }

            // Se o id for maior que todos os ids do nó, então o nó filho do último índice é o próximo a ser visitado
            if (node->children.size() > node->products.size()) {
                return searchRecursive(node->children[node->products.size()], id);
            } else {
                return nullptr;
            }    
        }

        /**
         * @brief Método que divide um nó
         * @param node Nó a ser dividido
         * @param index Índice do produto a ser promovido
         */
        void split(Node* parent, int index) {
            std::cout << "Dividindo o nó no índice: " << index << std::endl;

            Node* fullChild = parent->children[index];
            int mid = order - 1;

            // Cria o novo nó para as chaves maiores
            Node* newChild = new Node(order);
            newChild->depth = fullChild->depth;
            newChild->parent = parent; // Define o pai do novo nó

            // Transfere metade das chaves para o novo nó
            for (int j = mid + 1; j < fullChild->products.size(); j++) {
                newChild->products.push_back(fullChild->products[j]);
            }
            fullChild->products.resize(mid);

            // Transfere os filhos, se não for folha
            if (!fullChild->children.empty()) {
                for (int j = mid + 1; j <= fullChild->children.size(); j++) {
                    if (fullChild->children[j] != nullptr) {
                        newChild->children.push_back(fullChild->children[j]);
                        newChild->children.back()->parent = newChild; // Atualiza o pai dos filhos transferidos
                    }
                }
                fullChild->children.resize(mid + 1);
            }

            // Insere a chave do meio no nó pai
            parent->products.insert(parent->products.begin() + index, fullChild->products[mid]);
            parent->children.insert(parent->children.begin() + index + 1, newChild);

            std::cout << "Divisão concluída com sucesso." << std::endl;
        }
    
};

#endif