#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include "Product.hpp"

/**
 * @class Classe Node
 * @brief Uma classe que representa um nó de uma árvore B gerenciadora de estoque
 */
class Node {

    private:
        
        std::vector<Product> products;   ///< Vetor de produtos
        int depth;  ///< Profundidade do nó na árvore  
        Node *parent;  ///< Ponteiro para o nó pai
        

    public:

        /**
         * @brief Construtor da classe Node/produto
         * @param id Identificador do nó/ID do produto
         */
        Node(int id) {
            this->products.push_back(Product(id));
            this->depth = 0;
            this->parent = nullptr;
        }

        /**
         * @brief Destruidor da classe Node/produto
         */
        ~Node() = default;

        /**
         * @brief Método que retorna o nome do produto
         * @param id ID do produto
         * @return Nome do produto
         */
        std::string getName(int id) {
            for (Product product : this->products) {
                if (product.getId() == id) {
                    return product.getName();
                }
            }
        }

        /**
         * @brief Método que define o nome do produto
         * @param name Nome do produto
         * @param id ID do produto
         */
        void setName(std::string name, int id) {
            for (Product &product : this->products) {
                if (product.getId() == id) {
                    product.setName(name);
                }
            }
        }

        /**
         * @brief Método que retorna a quantidade em estoque
         * @param id ID do produto
         * @return Quantidade em estoque
         */
        int getStock(int id) {
            for (Product product : this->products) {
                if (product.getId() == id) {
                    return product.getStock();
                }
            }
        }


        /**
         * @brief Método que define a quantidade em estoque
         * @param stock Quantidade em estoque
         * @param id ID do produto
         */
        void setStock(int stock, int id) {
            for (Product &product : this->products) {
                if (product.getId() == id) {
                    product.setStock(stock);
                }
            }
        }

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
