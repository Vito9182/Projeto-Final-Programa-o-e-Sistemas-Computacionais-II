#include "livros.h"
#include <iostream>



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

    //etapas até chegar no ultimo
    Livro* atual = lista.primeiro;
    while (atual->proximo != nullptr){
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return true;
}

//mostra os livros cadastrados
void listar(Lista & lista) {
    if (lista.primeiro == nullptr) {
        cout << "Nenhum livro cadastrado\n";
        return;
    }

    Livro* atual = lista.primeiro;
    while (atual != nullptr) {
        cout << atual->codigo << " / " << atual->titulo << " / " << atual->autor
            << " / disponiveis: " << atual->disponiveis << " / " << atual->quantidade << "\n";
        atual = atual->proximo;
    }
}









