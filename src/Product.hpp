#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
    
    private:
        
        int id; ///<ID do produto
        std::string name;   ///< Nome do produto
        int stock;  ///< Quantidade em estoque
        
    public:

        /**
         * @brief Construtor da classe Produto
         * @param id ID do produto
         */
        Product(int id) {
            this->id = id;
            this->name = "";
            this->stock = 0;
        }

        /**
         * @brief Destruidor da classe Produto
         */
        ~Product() = default;

        /**
         * @brief Método que retorna o ID do produto
         * @return ID do produto
         */
        int getId() {return this->id;}

        /**
         * @brief Método que define o identificador do ID do produto
         * @param id ID do produto
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
       
};

#endif
