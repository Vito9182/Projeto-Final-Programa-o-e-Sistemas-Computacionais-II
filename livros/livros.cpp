#include <iostream>
#include "livros.h"


//cadastrar livro que vai pro fim da lista
//lista por referencia, titulo e autor por valor
bool cadastrar(Lista& lista, int codigo, string titulo, string autor, int quantidade) {
    //memoria
    Livro* novo = new Livro;
    novo->codigo = codigo;
    novo->titulo = titulo;
    novo->autor = autor;
    novo->quantidade = quantidade;
    novo->disponiveis = quantidade;
    novo->proximo = nullptr;

    //se a lista estiver vazia, o novo livro vira o primeira
    if (lista.primeiro == nullptr) {
        lista.primeiro = novo;
        return true;
    }

    //chegar no ultimo
    Livro* atual = lista.primeiro;
    while (atual->proximo != nullptr){
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return true;
}




//livros cadastrados



