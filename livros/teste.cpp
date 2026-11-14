#include "livros.h"
#include <iostream>

int main() {
    Lista lista;
    cout << "--- vazio ---\n";
    listar(lista);

    cout << "--- um livro ---\n";
    cadastrar(lista, 1, "autor1", "autor2", 3);
    listar(lista);

    cout << "--- varios livros ---\n";
    cadastrar(lista, 2, "livro1", "livro2", 2);
    cadastrar(lista, 3, "historinha", "gibizinho", 5);
    cadastrar(lista, 4, "livrinho", "onepiece", 1);
    listar(lista);

    return 0;
}