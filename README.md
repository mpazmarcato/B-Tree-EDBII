# EDB II - 3ª Unidade

## Objetivo
Projeto que guarda as implementações realizadas para o trabalho final da 3ª Unidade de EDB II. O projeto implementa uma Árvore B para armazenar e organizar informações de um sistema de controle de estoque. Os algoritmos foram implementados todos na linguagem C++ e estão todos documentados.

## Demonstração

Link do vídeo com explicação e demonstração do código: https://drive.google.com/file/d/1anFlgXEiB41V6QSJOHED-y0SwPCFCXfs/view

## Como compilar os arquivos

### Makefile
Na raiz do projeto, é possível digitar:
- `make all` para compilar o projeto;
- `make exec` para compilar e, em seguida, executar o projeto;
- `make clean` para limpar o arquivo executável gerado.

### VSCode
Caso esteja no VSCode, há a possibilidade de executar o programa direto nele via extensões, graças à existência dos arquivos `launch.json` e `tasks.json`. Para isso, basta estar no arquivo `main.cpp`, com a `C/C++ Extension Pack` instalada e clicar no ícone de "reprodução", que se encontra na barra superior com as janelas abertas.

ATENÇÃO: antes de executar o programa pelo VSCode, certifique-se de alterar a constante `filename` dentro de `main.cpp` para "dadosB.txt", ao invés de deixá-la como "src/dadosB.txt", para que o arquivo seja lido corretamente. Executando pelo Makefile tal problema não ocorre.

## Implementação Computacional 

A árvore B foi implementada para armazenar os itens de estoque, com as seguintes informações em cada nó:
- **ID do item**: chave única (inteiro).
- **Nome do item**: descrição (string).
- **Quantidade em estoque**: quantidade disponível (inteiro).

A árvore B possui as operações básicas:
- **Inserção**: Adiciona um novo item no sistema de controle de estoque.
- **Busca**: Permite buscar um item pelo ID (por exemplo, `buscar pelo ID 109` deve retornar `{109, "SSD", 30}`).
- **Exclusão**: Remove um item da árvore com base no ID (por exemplo, `excluir o ID 140`).
- **Visualização da Árvore em Nível**

## Arquivo de Dados

Os dados dos itens de estoque a serem inseridos na árvore B estão disponíveis no arquivo [`./src/dadosB.txt`](./src/dadosB.txt). Este arquivo contém uma lista de itens no seguinte formato:

```text
{ID, "Nome", Quantidade}
```

## Organização do Projeto

```plaintext
├── src
│   ├── BTree.hpp
│   ├── BTree.cpp
│   ├── Node.hpp
│   ├── Node.cpp
│   ├── main.cpp
│   └── dadosB.txt
├── Makefile
└── README.md
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
- Sistema Operacional: Debian GNU/Linux 12 (WSL) 
- Softwares:  C++
- Compiladores: GCC 12.2

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
- Função de listar: Paz/Andriel
