#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"
#include <bits/stdc++.h>

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
     * @brief Método que insere um nó na árvore
     * @param node Nó a ser inserido
     */
    void insert(Node::Product product)
    {

        // Se a árvore estiver vazia, o nó inserido será a raiz
        if (this->root == nullptr)
        {
            this->root = new Node(product, this->order);
        }
        else if (this->root->children.size() == 0)
        { // Se a raiz não tiver filhos, insere o produto na raiz
            this->root->products.push_back(product);
        }
        // else if (this->root->products.size() == this->root->MAX_PRODUCTS) {
        //     Node *newRoot = new Node(this->root->products[this->root->order - 1], this->order);
        //     newRoot->children.push_back(this->root);
        //     this->root->parent = newRoot;
        //     this->root = newRoot;
        //     split(this->root, 0);
        // } else {
        //     insertRecursive(this->root, product);
        // }
    }

    /**
     * @brief Método que busca um nó na árvore
     * @param id Identificador do nó a ser buscado
     * @return Produto buscado
     */
    Node::Product *search(int id)
    {
        return searchRecursive(this->root, id);
    }

    void remove(int id)
    {
        removeRecursive(id, this->root);
    }

private:
    int getNodeIndex(Node *node, Node *parent = nullptr)
    {
        if (parent == nullptr)
            parent = node->parent;

        for (int i = 0; i < parent->children.size(); i++)
        {
            if (parent->children.at(i) == node)
            {
                return i;
            }
        }
    }

    Node *searchNodeWithProduct(int id, Node *currentNode = nullptr)
    {
        // Se o nó inicial não for passado, presuma que a busca inicia no começo da árvore.
        if (currentNode == nullptr)
        {
            currentNode = this->root;
        }

        // Se a chave está contida no nó atual, retorne-o.
        if (searchRecursive(currentNode, id) != nullptr)
        {
            return currentNode;
        }

        // Procure em cada filho do nó atual pelo produto e, caso encontre-o, retorne-o.
        for (int i = 0; i < currentNode->children.size(); i++)
        {
            auto product = searchRecursive(currentNode->children[i], id);
            if (product != nullptr)
            {
                return currentNode->children[i];
            }
        }

        // Se não encontrar em nenhum filho do nó inserido, retorne nulo.
        return nullptr;
    }

    /**
     * @brief Método que remove uma chave do nó
     */
    void removeRecursive(int id, Node *root)
    {
        Node *node = searchNodeWithProduct(id, root);

        // Se não há nó com a chave fornecida, não há o que remover.
        if (node == nullptr)
            return;

        Node::Product *productToDelete = searchRecursive(node, id);

        if (node->isLeaf())
        {
            auto it = std::remove(node->products.begin(), node->products.end(), productToDelete);
            node->products.erase(it);

            // Se o nó ficou desbalanceado, agora aplicamos alguma das técnicas para balancear.
            if (!node->hasMinimumElements())
            {
                int nodeIndex = getNodeIndex(node);
                // FIXME: parent não está preenchido, estou escrevendo logo a lógica pra depois cuidar no preenchimento
                Node *leftNode = getSibling(node, nodeIndex, true);
                Node *rightNode = getSibling(node, nodeIndex, false);

                if (!leftNode && !rightNode)
                {
                    // TODO: throw erro
                }

                if (leftNode && leftNode->hasMoreThanMinimumProducts())
                {
                    redistribute(node, leftNode, node->parent, nodeIndex - 1);
                    // nodeIndex - 1 sem problemas porque, se nodeIndex == 0, ele não tem leftNode e nem entra nesse if
                }
                else if (rightNode && rightNode->hasMoreThanMinimumProducts())
                {
                    redistribute(node, rightNode, node->parent, nodeIndex);
                }
                else
                {
                    if (leftNode)
                        concatenate(node, leftNode, node->parent, nodeIndex - 1);
                    else
                        concatenate(node, rightNode, node->parent, nodeIndex);
                }
            }
            // Caso 2: Se a chave foi removida e o nó e um de seus irmãos adjacentes tem menos que 2d elementos,
            // balanceie.

            // Caso 3: Se a chave foi removida e o nó e um de seus irmãos adjacentes tem 2d ou mais elementos,
            // balanceie.
        }

        // Caso 2: Se o nó não for folha, pegue o antecessor ou o sucessor e troque,
        // depois chama a remoção.
        else
        {
            Node::Product *replacement;
            int productToDeleteIndex = node->getProductIndex(productToDelete->id);

            Node *childNode = nullptr;
            // Pegar o nó com maior filhos para trocar para não haver muito desbalanceamento.
            bool leftChildHasMoreElementsThanRight = node->children.at(productToDeleteIndex)->products.size() > node->children.at(productToDeleteIndex + 1)->products.size();

            if (leftChildHasMoreElementsThanRight)
            {
                childNode = node->children.at(productToDeleteIndex);
                replacement = childNode->getProductWithBiggerId();
            }
            else
            {
                childNode = node->children.at(productToDeleteIndex + 1);
                replacement = childNode->getProductWithSmallerId();
            }
            node->replace(productToDeleteIndex, replacement);
            childNode->replace(*replacement, productToDelete);

            removeRecursive(replacement->id, childNode);
        }
    }

    void redistribute(Node *undeflowNode, Node *siblingNode, Node *parent, int keyIndex)
    {
        if (!siblingNode->hasMoreThanMinimumProducts())
        {
            // Não tem como redistribuir mais...
            return;
        }

        // Devemos pegar o último elemento de siblingNode (ou o primeiro, caso ele seja filho à direita),
        // e trocar de lugar com o separator.
        // Após isso, pega o separator e joga no underflowNode.

        Node::Product separator = parent->products.at(keyIndex);
        Node::Product newSeparator;

        if (siblingNode->products.back().id < separator.id)
        {
            newSeparator = siblingNode->products.back();
        }
        else if (siblingNode->products.at(0).id > separator.id)
        {
            newSeparator = siblingNode->products.at(0);
        }

        parent->products.at(keyIndex) = newSeparator;
        undeflowNode->products.push_back(separator);
    }

    void concatenate(Node *nodeA, Node *nodeB, Node *parent, int keyIndex)
    {
        Node::Product separator = parent->products.at(keyIndex);

        // NodeA e NodeB são agrupados em um novo nó, tanto seus elementos quanto suas chaves.
        // Além disso, o separator no Parent é transferido para o novo nó, deletando-o na lista de produtos e apagando um dos childrens.
        // O novo nó é colocado em parent->children(keyIndex)

        for (auto p : nodeB->products)
        {
            nodeA->products.push_back(p);
        }
        nodeA->products.push_back(separator);
        nodeA->sortProducts();

        eraseProduct(parent, &separator);
        erasePointer(parent, keyIndex);
        // TODO: Falta associar o "novo nó" ao pai.
        // E também verificar se o pai teve underflow. Se tiver, deve chamar o algoritmo de novo?
        if (!parent->hasMinimumElements())
        {
            // era pra chamar o concatenate tbm mas não sei como passar os parametros corretamente...
        }
    }

    void eraseProduct(Node *node, Node::Product *product)
    {
        auto it = std::remove(node->products.begin(), node->products.end(), product);
        node->products.erase(it);
    }

    void erasePointer(Node *node, int childrenIndex)
    {
        auto pointer = node->children.at(childrenIndex);
        auto it = std::remove(node->children.begin(), node->children.end(), node->children.at(childrenIndex));
        node->children.erase(it);
        delete pointer;
    }

    Node *getSibling(Node *node, int nodeIndex, bool left = true)
    {
        if (node == nullptr || node->parent == nullptr)
            return nullptr;

        Node *parent = node->parent;
        int siblingIndex = 0;

        // Se o nó é o 1º, só pode ter irmão à direita.
        if (nodeIndex == 0)
        {
            siblingIndex = 1;
        }
        // Se o nó é o último, só pode ter irmão à esquerda.
        else if (nodeIndex == parent->children.size() - 1)
        {
            siblingIndex = nodeIndex - 1;
        }
        // Se o nó não está nos extremos, determina com base no parametro "left".
        else
        {
            if (left)
                siblingIndex = nodeIndex - 1;
            else
                siblingIndex = nodeIndex + 1;
        }

        // Se o índice do irmão estiver nos limites, retorna o irmão
        if (siblingIndex >= 0 && siblingIndex < parent->children.size())
            return parent->children.at(siblingIndex);

        return nullptr; // Caso não haja irmão válido.
    }

    /**
     * @brief Método que procura um produto na árvore de forma recursiva
     * @param node Nó a se realizar a busca
     * @param id Identificador do produto a ser buscado
     */
    Node::Product *
    searchRecursive(Node *node, int id)
    {

        if (node == nullptr)
        {
            return nullptr;
        }
        for (int i = 0; i < node->products.size(); i++)
        {
            if (node->products[i].id == id)
            {
                return &node->products[i];
            }
            else if (node->products[i].id > id)
            {
                return searchRecursive(node->children[i], id);
            }
        }

        // Se o id for maior que todos os ids do nó, então o nó filho do último índice é o próximo a ser visitado
        if (node->children.size() > node->products.size())
        {
            return searchRecursive(node->children[node->products.size()], id);
        }
        else
        {
            return nullptr;
        }
    }

    /**
     * @brief Método que insere um produto na árvore de forma recursiva
     * @param node Nó a ser inserido o produto
     * @param product Produto a ser inserido
     */
    void insertRecursive(Node *node, Node::Product product);

    /**
     * @brief Método que divide um nó
     * @param node Nó a ser dividido
     * @param index Índice do produto a ser promovido
     */
    void split(Node *node, int index);
};

#endif
