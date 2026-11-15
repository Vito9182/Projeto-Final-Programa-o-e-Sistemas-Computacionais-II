# Projeto-Final-Programa-o-e-Sistemas-Computacionais-II

Sistema de biblioteca para cadastrar livros e usuários, controlar empréstimos e devoluções e guardar o histórico por usuário.

## Divisão de responsabilidades
- **Vitor:** Cadastro de livros (`livros/`)
- **Henrique:** Cadastro de usuários
- **Arthur:** Empréstimos e devoluções
- **Elei:** Menu principal, integração e histórico

---

## Cadastro de livros (`livros/`)

Esta parte guarda os livros da biblioteca e permite cadastrar, listar, buscar e remover.

### Arquivos
- `livros.h`: header com structs iniciais. struct Livro(nó) e struct Lista que guarda o primeiro livro.
- `livros.cpp`: código das funções
- `teste.cpp`: programa para testes

### Funções
- `cadastrar`: adiciona um livro (título, autor, código e quantidade) no fim da lista
- `listar` : mostra todos os livros cadastrados
- `buscarCodigo`: procura um livro pelo código e devolve o ponteiro dele
- `buscarTitulo`: procura um livro pelo título e devolve o ponteiro dele
- `remover`: tira um livro da lista pelo código e libera a memória com `delete`
- `contar`: conta quantos livros existem na lista (recursiva)
- `limparLista`: libera da memória todos os livros da lista
- `copiarParaVetor`: copia os ponteiros dos livros da lista para um vetor
- `ordenarPorCodigo`: ordena o vetor pelo código com Insertion Sort (O(n²) no pior caso, O(n) no melhor)