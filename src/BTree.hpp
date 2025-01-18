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
        void insert(Node::Product product){
            
            // Se a árvore estiver vazia, o nó inserido será a raiz
            if (this->root == nullptr) {
                this->root = new Node(product, this->order);
            } else if (this->root->children.size() == 0) { // Se a raiz não tiver filhos, insere o produto na raiz
                this->root->products.push_back(product);
            } 
            // else if (this->root->products.size() == this->root->MAX_PRODUCTS) {
            //     Node *newRoot = new Node(this->root->products[this->root->order - 1], this->order);
            //     newRoot->children.push_back(this->root);
            //     this->root->parent = newRoot;
            //     this->root = newRoot;
            //     split(this->root, 0);
            // } else {
            //     insertRecursive(this->root, product);
            // }
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
};

#endif
