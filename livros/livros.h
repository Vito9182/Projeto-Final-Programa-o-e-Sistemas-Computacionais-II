#pragma once
#include <string>
using namespace std;

//Cabeçalho
//Uso de lista encadeada
struct Livro {
    int codigo;
    string titulo;
    string autor;
    int quantidade;
    int disponiveis;
    Livro* proximo;
};

struct ListaLivros {
    Livro* primeiro = nullptr;
};

//Cadastrar livro
bool cadastrarLivro(ListaLivros& lista, int codigo, string titulo, string autor, int quantidade = 1);
//Lista de livros cadastrados
void listarLivros(ListaLivros& lista);

//Busca de livros
Livro* buscarLivroPorCodigo(ListaLivros& lista, int codigo);
Livro* buscarLivroPorTitulo(ListaLivros& lista, string titulo);

//remoção de livros
bool removerLivro(ListaLivros& lista, int codigo);

//contagem de livros(usando recursividade) e limpeza da lista
int contarLivros(Livro* livro);
void limparListaLivros(ListaLivros& lista);

//--------------------------------//
//uso da ordenação e busca binária

//cópia dos livros para um vetor e ordenar por codigo
Livro** copiarLivrosParaVetor(ListaLivros& lista, int& tamanho);
void ordenarLivrosPorCodigo(Livro** vetor, int tamanho);

//busca binaria
Livro* buscarLivroBinaria(Livro** vetor, int tamanho, int codigo, int& comparacoes);
Livro* buscarLivroPorCodigoContando(ListaLivros& lista, int codigo, int& comparacoes);
