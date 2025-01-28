#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @class Classe BTree
 * @brief Uma classe que representa uma árvore B do gerenciador de estoque
 */

class BTree
{
public:
    int order;  ///< Ordem da árvore
    Node *root; ///< Ponteiro para a raiz da árvore

    /**
     * @brief Construtor da classe BTree
     * @param order Ordem da árvore
     */
    BTree(int order)
    {
        this->order = order;
        this->root = nullptr;
    }

    /**
     * @brief Destruidor da classe BTree
     */
    ~BTree()
    {
        delete root;
    }

    /**
     * @brief Imprime a árvore B em níveis.
     */
    void printLevel();

    /**
     * @brief Carrega todos os produtos de um arquivo dentro da árvore.
     * @param filename Caminho do arquivo.
     */
    void
    loadFromFile(const std::string &filename);

    /**
     * @brief Método que busca um nó na árvore
     * @param id Identificador do nó a ser buscado
     * @return Produto buscado
     */
    Node::Product *search(int id);

    /**
     * @brief Método que insere um produto na árvore
     * @param product Produto a ser inserido
     */
    void insert(Node::Product product);

    /**
     * @brief Método que remove um produto na árvore com base em uma chave/produto
     * @param id Id do produto/chave
     */
    void remove(int id);

private:
    /**
     * @brief Método que procura um produto na árvore de forma recursiva
     * @param node Nó a se realizar a busca
     * @param id Identificador do produto a ser buscado
     */
    Node::Product *searchRecursive(Node *node, int id);

    /**
     * @brief Método que insere um produto em um nó que não está cheio
     * @param node Ponteiro para o nó onde o produto será inserido
     */
    void insertNonFull(Node *node, Node::Product product);

    /**
     * @brief Método que divide um nó afim de manter o balanceamento
     * @param node Nó a ser dividido
     * @param index Índice do produto a ser promovido
     */
    void split(Node *parent, int index);

    /**
     * @brief Remove, de forma recursiva, um produto de um nó.
     * @param id Id do produto a ser removido.
     * @param root Nó onde será feita a busca.
     * @details Por ser um algoritmo recursivo, caso não seja encontrado o produto naquele nó específico,
     * o método será chamado novamente mas em um nó filho.
     */
    void removeRecursive(int id, Node *root);

    /**
     * @brief Método auxiliar que verifica se o filho atual do nó está balanceado.
     * @param index Índice do nó filho
     * @param root Nó pai
     */
    void verifyBalance(int index, Node *root);

    /**
     * @brief Método auxiliar que faz a redistribuição de chaves entre nós.
     * @param index Índice do produto "pai" entre os nós.
     * @param root Nó principal e pai dos nós.
     * @param leftSibling Flag que indica se a redistribuição ocorrerá com o nó à esquerda ou direita.
     */
    void redistribute(int index, Node *root, bool leftSibling = true);

    /**
     * @brief Método que faz a concatenação entre nós.
     * @param index Índice do produto "pai" entre os nós.
     * @param root Nó principal e pai dos nós a serem concatenados.
     */
    void concatenate(int index, Node *root);

    /**
     * @brief Método auxiliar que apaga uma chave no nó.
     * @param productIndex Índice da chave/produto no nó.
     * @param node Ponteiro para o nó.
     */
    void removeLeaf(int productIndex, Node *node);

    /**
     * @brief Método auxiliar que apaga uma chave de um nó que não é folha.
     * @param productIndex Índice da chave/produto no nó.
     * @param node Ponteiro para o nó.
     * @details Esse método rebaixa um produto para outro nó, trocando-o com outro produto,
     * OU concatena dois nós em um. Após isso, em todos os casos, chama o método da remoção recursiva,
     * aplicando a remoção no nó em que se encontra o produto a ser removido.
     */
    void removeNonLeaf(int productIndex, Node *node);
};

#endif