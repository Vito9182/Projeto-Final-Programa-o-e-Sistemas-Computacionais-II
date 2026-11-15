#include <string>
#pragma once
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

struct Lista {
    Livro* primeiro = nullptr;
};

//Cadastrar livro
bool cadastrar(Lista& lista, int codigo, string titulo, string autor, int quantidade);
//Lista de livros cadastrados
void listar(Lista& lista);

//Busca de livros
Livro* buscarCodigo(Lista& lista, int codigo);
Livro* buscarTitulo(Lista& lista, string titulo);

//remoção de livros
bool remover(Lista& lista, int codigo);

//contagem de livros(usando recursividade) e limpeza da lista
int contar(Livro* livro);
void limparLista(Lista& lista);

//--------------------------------//
//uso da ordenação e busca binária

//cópia dos livros para um vetor e ordenar por codigo
Livro** copiarParaVetor(Lista& lista, int& tamanho);
void ordenarPorCodigo(Livro** vetor, int tamanho);

//busca binaria
Livro* buscaBinaria(Livro** vetor, int tamanho, int codigo, int& comparacoes);
Livro* buscarCodigoContando(Lista& lista, int codigo, int& comparacoes);
