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
        static int NEXT_ID; ///< Contador interno de ID

        int id;           ///< ID do produto
        std::string name; ///< Nome do produto
        int stock;        ///< Quantidade em estoque

        /**
         * @brief Construtor padrão da struct Product
         */
        Product() : id(0), name(""), stock(0) {}

        /**
         * @brief Construtor da struct Product
         * @param id ID do produto
         */
        Product(int id)
        {
            this->id = id;
            this->name = "";
            this->stock = 0;
            NEXT_ID = id + 1;
        }

        /**
         * @overload
         * @brief Construtor da struct Product
         * @param name Nome do produto
         * @param stock Quantidade em estoque
         * @details Determina o ID de forma automática com base no último inserido
         */
        Product(std::string name, int stock)
        {
            this->id = NEXT_ID;
            this->name = name;
            this->stock = stock;
            NEXT_ID = id + 1;
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
            NEXT_ID = id + 1;
        }

        bool operator==(const Product &other) const
        {
            return this->id == other.id && this->name == other.name;
        }
    };

    int order;                     ///< Ordem da árvore
    std::vector<Product> products; ///< Vetor de produtos
    std::vector<Node *> children;  ///< Vetor de ponteiros para os filhos

    /**
     * @brief Construtor da classe Node/produto
     * @param id Identificador do nó/ID do produto
     * @param order Ordem da árvore
     */
    Node(Product Product, int order)
    {
        this->order = order;
        this->children = std::vector<Node *>();
    }

    Node(int order)
    {
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

    bool isFull()
    {
        return products.size() >= 2 * order - 1;
    }
};

#endif