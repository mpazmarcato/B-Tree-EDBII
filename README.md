# EDB II - 3ª Unidade

## Objetivo
Projeto que guarda as implementações realizadas para o trabalho final da 2ª Unidade de EDB II. O projeto implementa uma Árvore B para armazenar e organizar informações de um sistema de controle de estoque. Os algoritmos foram implementados todos na linguagem C++ e estão todos documentados.

## Demonstração

## Como compilar os arquivos

## Implementação Computacional 

A árvore B foi implementada para armazenar os itens de estoque, com as seguintes informações em cada nó:
- **ID do item**: chave única (inteiro).
- **Nome do item**: descrição (string).
- **Quantidade em estoque**: quantidade disponível (inteiro).

A árvore B possui as operações básicas:
- **Inserção**: Adiciona um novo item no sistema de controle de estoque.
- **Busca**: Permite buscar um item pelo ID (por exemplo, `buscar pelo ID 109` deve retornar `{109, "SSD", 30}`).
- **Exclusão**: Remove um item da árvore com base no ID (por exemplo, `excluir o ID 140`).
- **Visualização da Árvore**

## 3. Arquivo de Dados

Os dados dos itens de estoque a serem inseridos na árvore B estão disponíveis no arquivo [`./src/dadosB.txt`](./src/dadosB.txt). Este arquivo contém uma lista de itens no seguinte formato:

```text
{ID, "Nome", Quantidade}
```

## Operação de Busca

### Ambiente computacional

- Computador: Acer Aspire A315-23
- Processador: AMD Ryzen™ 3 3250U with Radeon™ Graphics × 4
- RAM: 08GB
- Editor de Texto: Visual Studio Code
- IDE: nenhuma
- Sistema Operacional: Ubuntu 24.04.1 LTS
- Softwares: C++
- Compiladores: GCC 13.3

## Operação de Inserção

### Ambiente computacional

- Computador: Dell G3 3590 
- Processador: Intel Core i5-9300H
- RAM: 08GB
- Editor de Texto: Visual Studio Code
- IDE: nenhuma
- Sistema Operacional: Windows 11 Pro versão 24H2
- Softwares: C++
- Compiladores: GCC 13.1

## Operação de Exclusão

### Ambiente computacional

- Computador: Acer Aspire A515-57
- Processador: Intel I5 12th Geração
- RAM: 08GB
- Editor de Texto: Visual Studio Code
- IDE: nenhuma
- Sistema Operacional: Windows 11 versão 23H2
- Softwares: OverLeaf e C++
- Compiladores: GCC 13.1

## Visualização e Fluxograma

### Ambiente computacional

- Computador: Genérico 
- Processador: AMD Ryzen 5 7600X 6-Core Processor 
- RAM: 16GB
- Editor de Texto: Visual Studio Code
- IDE: nenhuma
- Sistema Operacional: Windows 11 Pro versão 24H2
- Softwares: C++
- Compiladores: GCC 13.1

## Lista de Atividades

Aqui estão listadas as principais áreas do trabalho e quem predominantemente atuou nelas.

- Fluxograma de exclusão: Paz
- Função de buscar: Cauã
- Função de inserir: Victor
- Função de remover: Andriel
- Função de listar: Paz
