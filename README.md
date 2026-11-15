# Projeto-Final-Programa-o-e-Sistemas-Computacionais-II

Sistema de biblioteca para cadastrar livros e usuários, controlar empréstimos e devoluções e guardar o histórico por usuário.

## Divisão de responsabilidades

### Vitor: Cadastro de livros (`livros/`)
- Criar o cadastro de livros
- Registrar título, autor, código e quantidade
- Listar os livros cadastrados
- Implementar busca de livros

### Henrique: Cadastro de usuários
- Cadastrar os usuários da biblioteca
- Registrar nome e código de identificação
- Listar usuários cadastrados
- Implementar busca por usuário

### Arthur: Empréstimos e devoluções
- Implementar empréstimo de livros
- Verificar se existem exemplares disponíveis
- Registrar devoluções
- Atualizar a quantidade de livros disponíveis

### Elei: Menu principal, integração e histórico
- Desenvolver o menu principal do sistema
- Integrar as funcionalidades dos outros integrantes
- Criar histórico de empréstimos por usuário
- Realizar testes e verificar possíveis erros

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
- `buscarCodigoContando`: busca sequencial que conta as comparações, O(n)
- `buscarBinaria`: busca binária no vetor ordenado que conta as comparações, O(log n)

### Estrutura de dados: lista encadeada
Cada livro é um nó com um ponteiro `proximo` que aponta para o livro seguinte. A lista só guarda o `primeiro`, e o último aponta para `nullptr`.

```
primeiro -> [1 | Livro1] -> [2 | Livro2] -> [3 | Livro3] -> nullptr
```

### Ordenação e busca binária
A lista encadeada fica na ordem de cadastro. Para ordenar, os ponteiros dos livros são copiados para um vetor, que é ordenado por código. Assim a lista original não muda e os livros não são duplicados. A busca binária só funciona nesse vetor ordenado, porque precisa acessar qualquer posição direto, o que a lista encadeada não permite.

```
vetor -> [ ptr | ptr | ptr | ptr ]
            |     |     |     |
            v     v     v     v
         livros que continuam na lista
```

### Requisitos usados nesta parte
- **Funções:** cada função faz uma coisa só; a lista é passada por referência (`&`) para alterar a original; o `cadastrar` tem parâmetro default (`quantidade = 1`)
- **Ponteiros:** o campo `proximo`, os ponteiros `atual` e `anterior` que percorrem a lista, e o vetor de ponteiros `Livro**`
- **Memória dinâmica:** `new` ao cadastrar e `delete` no `remover` e no `limparLista`; `new[]` no `copiarParaVetor` e `delete[]` por quem chama
- **Lista encadeada:** inserção no fim, remoção (primeiro, meio e último) e travessia
- **Recursividade:** a função `contar`
- **Algoritmo de ordenação:** Insertion Sort em `ordenarPorCodigo`
- **Algoritmos de busca:** busca sequencial e busca binária, com a comparação por contagem de operações

### Como testar
Na pasta do projeto:
```
g++ livros/teste.cpp livros/livros.cpp -o livros/teste.exe
.\livros\teste.exe
```