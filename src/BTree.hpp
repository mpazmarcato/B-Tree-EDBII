#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"

/**
 * @class Classe BTree
 * @brief Uma classe que representa uma árvore B do gerenciador de estoque
 */

class BTree {

    private:
    
        int order;  ///< Ordem da árvore
        Node *root; ///< Ponteiro para a raiz da árvore
        Node *sentinel; ///< Ponteiro para o nó sentinela

    public:

        /**
         * @brief Construtor da classe BTree
         * @param order Ordem da árvore
         */
        BTree(int order) {
            this->order = order;
            this->root = nullptr;
            this->sentinel = new Node(0, order);
        }

        /**
         * @brief Destruidor da classe BTree
         */
        ~BTree() = default;

        /**
         * @brief Método que retorna a ordem da árvore
         * @return Ordem da árvore
         */
        int getOrder() {return this->order;}

        /**
         * @brief Método que retorna o ponteiro para a raiz da árvore
         * @return Ponteiro para a raiz da árvore
         */
        Node *getRoot() {return this->root;}

        /**
         * @brief Método que define o ponteiro para a raiz da árvore
         * @param root Ponteiro para a raiz da árvore
         */
        void setRoot(Node *root) {this->root = root;}

        /**
         * @brief Método que retorna o ponteiro para o nó sentinela
         * @return Ponteiro para o nó sentinela
         */
        Node *getSentinel() {return this->sentinel;}

        /**
         * @brief Método que define o ponteiro para o nó sentinela
         * @param sentinel Ponteiro para o nó sentinela
         */
        void setSentinel(Node *sentinel) {this->sentinel = sentinel;}

        /**
         * @brief Método que insere um nó na árvore
         * @param node Nó a ser inserido
         */
        void insert(Node *node);

        /**
         * @brief Método que busca um nó na árvore
         * @param id Identificador do nó a ser buscado
         * @return Nó buscado
         */
        Node *search(int id);

        /**
         * @brief Método que remove um nó da árvore
         * @param id Ident
         */
        void *remove(int id);
};

#endif
