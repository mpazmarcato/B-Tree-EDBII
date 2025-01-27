#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

/**
 * @class Classe Node
 * @brief Uma classe que representa um nó de uma árvore B gerenciadora de estoque
 */
class Node {

    public:
        
        struct Product {

            int id; ///< ID do produto
            std::string name;   ///< Nome do produto
            int stock;  ///< Quantidade em estoque

            /**
             * @brief Construtor padrão da classe Product
             */
            Product() : id(0), name(""), stock(0) {}


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
        const int MAX_PRODUCTS = 2 * order - 1;  ///< Número máximo de produtos por nó
        const int MAX_CHILDREN = 2 * order;  ///< Número máximo de filhos por nó
        std::vector<Product> products;   ///< Vetor de produtos
        int depth;  ///< Profundidade do nó na árvore  
        Node *parent;  ///< Ponteiro para o nó pai
        std::vector<Node *> children;   ///< Vetor de ponteiros para os filhos
        
        bool isFull() {
            return products.size() == MAX_PRODUCTS;
        }

        Node(int order) {
            this->order = order;
            this->depth = 0;
            this->parent = nullptr;
            this->children.resize(2 * order, nullptr);
        }
        /**
         * @brief Construtor da classe Node/produto
         * @param id Identificador do nó/ID do produto
         * @param order Ordem da árvore
         */
        Node(Product Product, int order) {
            this->products.push_back(Product);
            this->order = order;
            this->depth = 0;
            this->parent = nullptr;
            this->children.resize(MAX_CHILDREN, nullptr);
        }

        /**
         * @brief Destruidor da classe Node/produto
         */
        ~Node() = default;


};

#endif