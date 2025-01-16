#ifndef NODE_HPP
#define NODE_HPP

#include <string>

/**
 * @class Classe Node/produto
 * @brief Uma classe que representa um nó de uma árvore B/produto do gerenciador de estoque
 */
class Node {

    private:
        
        int id; ///< Identificador do nó/ID do produto
        std::string name;   ///< Nome do produto
        int stock;  ///< Quantidade em estoque
        int depth;  ///< Profundidade do nó na árvore  
        Node *parent;  ///< Ponteiro para o nó pai

    public:

        /**
         * @brief Construtor da classe Node/produto
         * @param id Identificador do nó/ID do produto
         */
        Node(int id) {
            this->id = id;
            this->name = "";
            this->stock = 0;
            this->depth = 0;
            this->parent = nullptr;
        }

        /**
         * @brief Destruidor da classe Node/produto
         */
        ~Node() = default;

        /**
         * @brief Método que retorna o identificador do nó/ID do produto
         * @return Identificador do nó/ID do produto
         */
        int getId() {return this->id;}

        /**
         * @brief Método que define o identificador do nó/ID do produto
         * @param id Identificador do nó/ID do produto
         */
        void setId(int id) {this->id = id;}

        /**
         * @brief Método que retorna o nome do produto
         * @return Nome do produto
         */
        std::string getName() {return this->name;}

        /**
         * @brief Método que define o nome do produto
         * @param name Nome do produto
         */
        void setName(std::string name) {this->name = name;}

        /**
         * @brief Método que retorna a quantidade em estoque
         * @return Quantidade em estoque
         */
        int getStock() {return this->stock;}


        /**
         * @brief Método que define a quantidade em estoque
         * @param stock Quantidade em estoque
         */
        void setStock(int stock) {this->stock = stock;}

        /**
         * @brief Método que retorna a profundidade do nó na árvore
         * @return Profundidade do nó na árvore
         */
        int getDepth() {return this->depth;}

        /**
         * @brief Método que define a profundidade do nó na árvore
         * @param depth Profundidade do nó na árvore
         */
        void setDepth(int depth) {this->depth = depth;}

        /**
         * @brief Método que retorna o nó pai
         * @return Nó pai
         */
        Node *getParent() {return this->parent;}

        /**
         * @brief Método que define o nó pai
         */
        void setParent(Node *parent) {this->parent = parent;}

};

#endif
