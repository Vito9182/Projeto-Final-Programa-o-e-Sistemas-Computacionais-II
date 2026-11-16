# 📚 Sistema de Gerenciamento de Biblioteca

## 1. Sobre o projeto

Este projeto consiste no desenvolvimento de um sistema de gerenciamento de biblioteca utilizando a linguagem C++. Foi desenvolvido como trabalho final da disciplina **Programação e Sistemas Computacionais II**, do curso de Engenharia de Software do Centro Universitário Campo Real.

O sistema tem como objetivo realizar o gerenciamento de livros, usuários, empréstimos e devoluções, aplicando estruturas de dados e conceitos fundamentais de programação estudados durante a disciplina.

## 2. Funcionalidades

### 📖 Gerenciamento de livros
- Cadastro de livros.
- Listagem dos livros cadastrados.
- Busca de livros por código e título.
- Remoção de livros.
- Controle de quantidade disponível.
- Contagem recursiva de livros.
- Ordenação dos livros utilizando Insertion Sort.
- Busca sequencial e busca binária.

### 👤 Gerenciamento de usuários
- Cadastro de usuários.
- Consulta de usuários cadastrados.
- Gerenciamento dos dados dos usuários.
- Verificação de usuários durante as operações de empréstimo.

### 🔄 Gerenciamento de empréstimos
- Realização de empréstimos.
- Registro de devoluções.
- Controle de disponibilidade dos livros.
- Fila de espera para livros indisponíveis.
- Histórico de empréstimos e devoluções.
- Consulta de empréstimos ativos.

## 3. Estruturas de dados utilizadas

O projeto utiliza diferentes estruturas de dados para organizar e gerenciar as informações.

### Lista encadeada
Utilizada no gerenciamento dos livros, permitindo inserção, remoção, busca e percorrimento dos registros.

Representação:

```text
[Livro 1] -> [Livro 2] -> [Livro 3] -> nullptr
```

### Fila (FIFO)
Utilizada para organizar a lista de espera de empréstimos. O primeiro usuário que entra na fila é o primeiro a ser atendido.

Representação:

```text
INÍCIO -> [Usuário 1] -> [Usuário 2] -> [Usuário 3] -> FIM
```

### Pilha (LIFO)
Utilizada para armazenar o histórico de operações de empréstimos e devoluções, permitindo consultar os registros na ordem inversa de inserção.

Representação:

```text
TOPO
 |
[Registro 3]
 |
[Registro 2]
 |
[Registro 1]
```

### Árvore Binária de Busca (BST)
Utilizada para organizar os empréstimos ativos, permitindo inserção, busca e consulta dos registros por meio da estrutura hierárquica.

Representação ilustrativa:

```text
        [Registro 2]
        /          \
 [Registro 1]   [Registro 3]
```

## 4. Algoritmos de ordenação e busca

O sistema aplica algoritmos desenvolvidos durante a disciplina:

- **Insertion Sort:** utilizado para ordenar os livros.
- **Busca sequencial:** percorre os elementos até encontrar o registro desejado.
- **Busca binária:** realiza a busca em uma sequência ordenada, reduzindo o espaço de pesquisa a cada etapa.

Também são realizadas comparações da quantidade de operações das buscas para observar as diferenças de desempenho.

## 5. Gerenciamento de memória

O projeto utiliza alocação dinâmica de memória por meio de `new` e liberação por meio de `delete`, permitindo a criação e remoção de elementos das estruturas de dados.

Os ponteiros são utilizados para manipular os elementos das estruturas, com atenção à liberação da memória para evitar vazamentos.

## 6. Organização do projeto

```text
Projeto-Final-Programa-o-e-Sistemas-Computacionais-II/
│
├── emprestimos/
│   ├── emprestimos.cpp
│   └── teste.cpp
│
├── livros/
│   ├── livros.cpp
│   └── teste.cpp
│
├── usuarios/
│   └── usuarios.cpp
│
├── README.md
└── teste.cpp
```

## 7. Divisão de responsabilidades

O desenvolvimento foi dividido entre os integrantes da equipe, com cada participante responsável por um módulo do sistema.

| Integrante | Responsabilidade |
|---|---|
| Vitor | Gerenciamento de livros |
| Henrique | Cadastro e gerenciamento de usuários |
| Arthur | Empréstimos e devoluções |
| Elei | Menu principal, integração dos módulos, histórico e testes |

## 8. Testes

Foram desenvolvidos testes para verificar o funcionamento das operações dos módulos de livros e empréstimos.

Os testes verificam situações como:

- Cadastro e remoção de livros.
- Cadastro de usuários.
- Busca e ordenação.
- Controle de quantidade disponível.
- Realização de empréstimos.
- Devolução de livros.
- Funcionamento da fila de espera.
- Controle de empréstimos ativos.

## 9. Tecnologias utilizadas

- Linguagem C++.
- Git.
- GitHub.
- Visual Studio Code.
- Compilador G++.

## 10. Integrantes

Projeto desenvolvido por estudantes do curso de Engenharia de Software do Centro Universitário Campo Real.

**Disciplina:** Programação e Sistemas Computacionais II  
**Professor:** Giovane Galvão  
**Instituição:** Centro Universitário Campo Real  
**Ano:** 2026

---

Desenvolvido como projeto acadêmico para aplicação prática dos conceitos de programação e estruturas de dados.

# Código de execução 

g++ main.cpp emprestimos/emprestimos.cpp livros/livros.cpp usuarios/usuarios.cpp -o biblioteca.exe

.\biblioteca.exe