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

    void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            // Localizar as chaves '{' e '}'
            size_t start = line.find("{");
            size_t end = line.find("}");
            if (start == std::string::npos || end == std::string::npos || end <= start)
            {
                std::cerr << "Linha inválida ignorada: " << line << std::endl;
                continue;
            }

            // Extrair o conteúdo entre as chaves
            std::string content = line.substr(start + 1, end - start - 1);
            std::stringstream ss(content);

            // Extrair os campos separados por vírgula
            std::string idStr, name, stockStr;
            if (!std::getline(ss, idStr, ',') || !std::getline(ss, name, ',') || !std::getline(ss, stockStr, ','))
            {
                std::cerr << "Erro ao processar linha: " << line << std::endl;
                continue;
            }

            // Limpar espaços em branco extras e aspas
            idStr.erase(0, idStr.find_first_not_of(" \t"));
            name.erase(0, name.find_first_not_of(" \t\""));
            name.erase(name.find_last_not_of(" \t\"") + 1);
            stockStr.erase(0, stockStr.find_first_not_of(" \t"));

            try
            {
                // Converter os valores para os tipos apropriados
                int id = std::stoi(idStr);
                int stock = std::stoi(stockStr);

                // Criar o produto e insere na árvore
                Node::Product product(id, name, stock);
                this->insert(product);

                std::cout << "Produto inserido: ID = " << id
                          << ", Nome = " << name
                          << ", Estoque = " << stock << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << "Erro ao converter dados: " << line << ". Detalhes: " << e.what() << std::endl;
            }
        }

        file.close();
        std::cout << "Produtos carregados com sucesso do arquivo: " << filename << std::endl;
    }

    /**
     * @brief Método que insere um nó na árvore
     * @param node Nó a ser inserido
     */
    void insert(Node::Product product)
    {
        if (this->root == nullptr)
        { // Se a árvore estiver vazia, cria a raiz
            this->root = new Node(product, this->order);
        }
        else
        {
            if (this->root->products.size() == this->root->MAX_PRODUCTS)
            { // Se a raiz estiver cheia, cria uma nova raiz e realiza o split
                Node *newRoot = new Node(this->order);
                newRoot->children.push_back(this->root);
                split(newRoot, 0);
                this->root = newRoot;
            }

            insertNonFull(this->root, product); // Insere no nó apropriado
        }
    }

    /**
     * @brief Método que insere um produto em um nó que não está cheio
     * @param node Ponteiro para o nó onde o produto será inserido
     */

    void insertNonFull(Node *node, Node::Product product)
    {
        int i = node->products.size() - 1;

        if (node->children.empty())
        {
            // Insere na folha e mantém a ordem
            node->products.push_back(product);
            while (i >= 0 && node->products[i].id > product.id)
            {
                std::swap(node->products[i + 1], node->products[i]);
                i--;
            }
        }
        else
        {
            // Encontra o filho apropriado
            while (i >= 0 && node->products[i].id > product.id)
            {
                i--;
            }
            i++;

            // Verifica se o filho está cheio
            if (node->children[i]->products.size() == node->MAX_PRODUCTS)
            {
                split(node, i);
                if (node->products[i].id < product.id)
                {
                    i++;
                }
            }
            insertNonFull(node->children[i], product);
        }
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
            auto it = std::remove(node->products.begin(), node->products.end(), *productToDelete);
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

        eraseProduct(parent, separator);
        erasePointer(parent, keyIndex);
        // TODO: Falta associar o "novo nó" ao pai.
        // E também verificar se o pai teve underflow. Se tiver, deve chamar o algoritmo de novo?
        if (!parent->hasMinimumElements())
        {
            // era pra chamar o concatenate tbm mas não sei como passar os parametros corretamente...
        }
    }

    void eraseProduct(Node *node, Node::Product &product)
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
    Node::Product *searchRecursive(Node *node, int id)
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
     * @brief Método que divide um nó
     * @param node Nó a ser dividido
     * @param index Índice do produto a ser promovido
     */
    void split(Node *parent, int index)
    {
        // Node *child = node->children[index];
        // Node *newChild = new Node(order);

        // // // Transfere metade das chaves
        // // for (int i = order; i < child->products.size(); i++)
        // // {
        // //     newChild->products.push_back(child->products[i]);
        // // }
        // // child->products.resize(order - 1);

        // // Transfere filhos, se existirem
        // if (!child->isLeaf()) // !child->children.empty()
        // {
        //     for (int i = order; i < child->children.size(); i++)
        //     {
        //         newChild->children.push_back(child->children[i]);
        //     }
        //     child->children.resize(order);
        // }

        // // Ajusta no nó pai
        // node->children.insert(node->children.begin() + index + 1, newChild);
        // node->products.insert(node->products.begin() + index, child->products[order / 2]);
        // eraseProduct(child, child->products[order / 2]);
        std::cout << "Dividindo o filho no índice: " << index << std::endl;

        // Verifique se o índice é válido
        if (index < 0 || index >= parent->children.size())
        {
            throw std::out_of_range("Índice fora do intervalo válido.");
        }

        // Passo 1: Crie um novo nó z que será o irmão do filho i
        Node *fullChild = parent->children[index];
        if (!fullChild)
        {
            throw std::runtime_error("O filho especificado é nulo.");
        }

        Node *newChild = new Node(fullChild->order); // Cria o novo nó irmão
        newChild->depth = fullChild->depth;
        newChild->parent = parent;

        int mid = fullChild->order - 1; // Índice da chave do meio

        // Passo 2: Promova a chave do meio ao nó pai antes de alterar fullChild
        parent->products.insert(parent->products.begin() + index, fullChild->products[mid]);

        // Passo 3: Copie as últimas chaves do filho i para o novo nó z
        for (int j = mid + 1; j < fullChild->products.size(); j++)
        {
            newChild->products.push_back(fullChild->products[j]);
        }

        // Passo 4: Se o filho i não for folha, copie os filhos para o novo nó z
        if (!fullChild->children.empty())
        {
            for (int j = mid + 1; j < fullChild->children.size(); j++)
            {
                newChild->children.push_back(fullChild->children[j]);
                newChild->children.back()->parent = newChild; // Atualiza o pai dos filhos transferidos
            }
            fullChild->children.resize(mid + 1); // Ajuste o vetor de filhos do nó cheio
        }

        // Passo 5: Reduza o número de chaves do filho i
        fullChild->products.resize(mid);

        // Passo 6: Insira o novo nó z como um novo filho do nó pai
        parent->children.insert(parent->children.begin() + index + 1, newChild);
    }

public:
    void printTree(Node *node, int level = 0)
    {
        if (node == nullptr)
        {
            return;
        }

        // Indentar para representar o nível do nó
        std::cout << std::string(level * 2, ' ') << "Nível " << level << ": ";

        // Exibe os produtos do nó
        for (const auto &product : node->products)
        {
            std::cout << "[" << product.id << "]";
        }
        std::cout << std::endl;

        // Chama recursivamente para os filhos
        for (Node *child : node->children)
        {
            if (child != nullptr)
            {
                printTree(child, level + 1);
            }
        }
    }
};

#endif