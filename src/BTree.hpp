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
        void insert(Node *node);

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
