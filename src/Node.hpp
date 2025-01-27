#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

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

        Product() {}

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
    };

    std::vector<Product> products; ///< Vetor de produtos
    int depth;                     ///< Profundidade do nó na árvore
    Node *parent;                  ///< Ponteiro para o nó pai
    std::vector<Node *> children;  ///< Vetor de ponteiros para os filhos

    /**
     * @brief Construtor da classe Node/produto
     * @param id Identificador do nó/ID do produto
     * @param order Ordem da árvore
     */
    Node(Product Product, int order) : MAX_CHILDREN(2 * order), MAX_PRODUCTS(2 * order - 1), MIN_CHILDREN(order)
    {
        this->products.push_back(Product);
        this->depth = 0;
        // this->parent = nullptr;
        this->children.resize(MAX_CHILDREN, nullptr);
    }

    /**
     * @brief Destruidor da classe Node/produto
     */

    ~Node() = default;

    void sortProducts()
    {
        std::sort(products.begin(), products.end(), [](Node::Product p1, Node::Product p2)
                  { return p1.id < p2.id; });
    }

    void replace(int oldProductIndex, Product *newProduct)
    {
        this->products.at(oldProductIndex) = *newProduct;
    }

    /// @overload
    /// @brief
    /// @param oldProduct
    /// @param newProduct
    void replace(Product oldProduct, Product *newProduct)
    {
        replace(this->getProductIndex(oldProduct.id), newProduct);
    }

    bool isLeaf()
    {
        return this->children.size() == 0;
    }

    bool hasMinimumElements()
    {
        return this->products.size() >= MIN_CHILDREN;
    }

    bool hasMoreThanMinimumProducts()
    {
        return this->products.size() > MIN_CHILDREN;
    }

    bool hasOverflowed()
    {
        return this->products.size() >= MAX_CHILDREN;
    }

    // FIXME: pensar em um jeito melhor de evitar essa duplicação de código pra duas funções que fazem a mesma coisa
    Node::Product *getProductWithBiggerId()
    {
        Product *product = &this->products.at(0);
        for (int i = 0; i < this->products.size(); i++)
        {
            if (this->products.at(i).id > product->id)
            {
                product = &this->products.at(i);
            }
        }

        return product;
    }

    Node::Product *getProductWithSmallerId()
    {
        Product *product = &this->products.at(0);
        for (int i = 0; i < this->products.size(); i++)
        {
            if (this->products.at(i).id < product->id)
            {
                product = &this->products.at(i);
            }
        }

        return product;
    }

    int getProductIndex(int id)
    {
        for (int i = 0; i < this->products.size(); i++)
        {
            if (this->products.at(i).id == id)
            {
                return i;
            }
        }

        return 0;
    }

private:
    const int MAX_PRODUCTS; ///< Número máximo de produtos por nó
    const int MAX_CHILDREN; ///< Número máximo de filhos por nó
    const int MIN_CHILDREN; ///< Número mínimo de filhos por nó
};

#endif
