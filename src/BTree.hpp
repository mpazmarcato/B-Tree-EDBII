#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"

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
                // Insere na folha e mantém a ordem
                node->products.push_back(product);
                while (i >= 0 && node->products[i].id > product.id) {
                    std::swap(node->products[i + 1], node->products[i]);
                    i--;
                }
            } else {
                // Encontra o filho apropriado
                while (i >= 0 && node->products[i].id > product.id) {
                    i--;
                }
                i++;

                // Verifica se o filho está cheio
                if (node->children[i]->products.size() == node->MAX_PRODUCTS) {
                    split(node, i);
                    if (node->products[i].id < product.id) {
                        i++;
                    }
                }
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
        void split(Node* node, int index) {
        Node* child = node->children[index];
        Node* newChild = new Node(child->products[order], order);

        // Transfere metade das chaves
        for (int i = order; i < child->products.size(); i++) {
            newChild->products.push_back(child->products[i]);
        }
        child->products.resize(order - 1);

        // Transfere filhos, se existirem
        if (!child->children.empty()) {
            for (int i = order; i <= child->children.size(); i++) {
                newChild->children.push_back(child->children[i]);
            }
            child->children.resize(order);
        }

        // Ajusta no nó pai
        node->children.insert(node->children.begin() + index + 1, newChild);
        node->products.insert(node->products.begin() + index, child->products[order - 1]);
        }

};

#endif