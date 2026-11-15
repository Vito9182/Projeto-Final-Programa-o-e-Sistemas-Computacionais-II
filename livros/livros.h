#pragma once
#include <string>
using namespace std;

// Cadastro de livros da biblioteca, feito com lista encadeada.

// Cada livro é um nó da lista.
struct Livro {
    int codigo;
    string titulo;
    string autor;
    int quantidade;     // total de exemplares.
    int disponiveis;    // exemplares que não estão emprestados.
    Livro* proximo;     // próximo livro da lista (nullptr no último).
};

// Guarda só o primeiro livro; os outros são alcançados pelo ponteiro proximo.
struct ListaLivros {
    Livro* primeiro = nullptr;  // nullptr = lista vazia.
};

// ---- cadastro e listagem ----
bool cadastrarLivro(ListaLivros& lista, int codigo, string titulo, string autor, int quantidade = 1);
void listarLivros(ListaLivros& lista);

// ---- busca de livros ----
Livro* buscarLivroPorCodigo(ListaLivros& lista, int codigo);
Livro* buscarLivroPorTitulo(ListaLivros& lista, string titulo);

// ---- remoção, contagem e limpeza ----
bool removerLivro(ListaLivros& lista, int codigo);
int contarLivros(Livro* livro);
void limparListaLivros(ListaLivros& lista);

// ---- ordenação e busca binária ----

// Cópia dos livros para um vetor e ordenar por codigo.
Livro** copiarLivrosParaVetor(ListaLivros& lista, int& tamanho);
void ordenarLivrosPorCodigo(Livro** vetor, int tamanho);

// Busca binária.
Livro* buscarLivroBinaria(Livro** vetor, int tamanho, int codigo, int& comparacoes);
Livro* buscarLivroPorCodigoContando(ListaLivros& lista, int codigo, int& comparacoes);
