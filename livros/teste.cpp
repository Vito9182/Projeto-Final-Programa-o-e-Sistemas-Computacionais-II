#include "livros.h"
#include <iostream>

int main() {
    Lista lista;
    cadastrar(lista, 1, "Livro do vito", "Vito", 3);
    cadastrar(lista, 2, "Livro de historia", "Sr. Historia", 2);
    listar(lista);

    cout << "--- buscas ---\n";
    Livro* achado = buscarCodigo(lista, 2);
    if (achado != nullptr) {
        cout << "Achado por codigo: " << achado->titulo << "\n";
    }

    achado = buscarTitulo(lista, "Blackout");
    if (achado != nullptr) {
        cout << "Achado por titulo: " << achado->autor << "\n";
    }

    if (buscarCodigo(lista, 99) == nullptr) {
        cout << "Codigo 99 nao existe\n";
    }

    return 0;
}