#include <string>
#pragma once
using namespace std;

//cabeçalho, lista encadeada
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

bool cadastrar(Lista& lista, int codigo, string titulo, string autor, int quantidade);
void listar(Lista& lista);