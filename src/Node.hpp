#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

/**
 * @class Classe Node
 * @brief Uma classe que representa um nó de uma árvore B gerenciadora de estoque
 */
class Node {

    private:
        
        struct Product {

            int id; ///< ID do produto
            std::string name;   ///< Nome do produto
            int stock;  ///< Quantidade em estoque

            /**
             * @brief Construtor da classe Product
             * @param id ID do produto
             */
            Product(int id) {
                this->id = id;
                this->name = "";
                this->stock = 0;
            }

            /**
             * @overload overload do construtor da classe Product
             * @brief Construtor da classe Product
             * @param id ID do produto
             * @param name Nome do produto
             * @param stock Quantidade em estoque
             */
            Product(int id, std::string name, int stock) {
                this->id = id;
                this->name = name;
                this->stock = stock;
            }

        };

        int order; ///< Ordem da árvore
        const int MAX_PRODUCTS = 2 * order;  ///< Número máximo de produtos por nó
        std::vector<Product> products;   ///< Vetor de produtos
        int depth;  ///< Profundidade do nó na árvore  
        Node *parent;  ///< Ponteiro para o nó pai
        

    public:

        /**
         * @brief Construtor da classe Node/produto
         * @param id Identificador do nó/ID do produto
         */
        Node(int id, int order) {
            this->products.push_back(Product(id));
            this->order = order;
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
                if (product.id == id) {
                    return product.name;
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
                if (product.id == id) {
                    product.name = name;
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
                if (product.id == id) {
                    return product.stock;
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
                if (product.id == id) {
                    product.stock = stock;
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
