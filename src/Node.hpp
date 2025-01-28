#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include <algorithm>

/**
 * @class Classe Node
 * @brief Uma classe que representa um nó de uma árvore B gerenciadora de estoque
 */
class Node
{

public:
    struct Product
    {

        int id;           ///< ID do produto
        std::string name; ///< Nome do produto
        int stock;        ///< Quantidade em estoque

        /**
         * @brief Construtor padrão da classe Product
         */
        Product() : id(0), name(""), stock(0) {}

        /**
         * @brief Construtor da classe Product
         * @param id ID do produto
         */
        Product(int id)
        {
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
        Product(int id, std::string name, int stock)
        {
            this->id = id;
            this->name = name;
            this->stock = stock;
        }

        bool operator==(const Product &other) const
        {
            return this->id == other.id && this->name == other.name;
        }
    };

    int order;                     ///< Ordem da árvore
    int MAX_PRODUCTS;              ///< Número máximo de produtos por nó
    int MAX_CHILDREN;              ///< Número máximo de filhos por nó
    std::vector<Product> products; ///< Vetor de produtos
    std::vector<Node *> children;  ///< Vetor de ponteiros para os filhos

    bool isFull()
    {
        return products.size() == MAX_PRODUCTS;
    }
    /**
     * @brief Construtor da classe Node/produto
     * @param id Identificador do nó/ID do produto
     * @param order Ordem da árvore
     */
    Node(Product Product, int order)
    {
        MAX_PRODUCTS = 2 * order - 1;
        MAX_CHILDREN = 2 * order;
        this->order = order;
        this->children = std::vector<Node *>();
    }

    Node(int order)
    {
        MAX_PRODUCTS = 2 * order - 1;
        MAX_CHILDREN = 2 * order;
        this->products = std::vector<Node::Product>();
        this->order = order;
        this->children = std::vector<Node *>();
    }

    /**
     * @brief Destruidor da classe Node/produto
     */

    ~Node() = default;

    bool isLeaf()
    {
        return this->children.empty();
    }

    bool hasMinimumElements()
    {
        return this->products.size() >= order - 1;
    }
};

#endif