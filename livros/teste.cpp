#include "livros.h"
#include <iostream>

int main() {
    Lista lista;
    cadastrar(lista, 1, "Livro1", "Autor1", 1);
    cadastrar(lista, 2, "Livro2", "Autor2", 1);
    cadastrar(lista, 3, "Livro3", "Autor3", 1);
    cadastrar(lista, 4, "Livro4", "Autor4", 1);
    cout << "--- lista inicial ---\n";
    listar(lista);

    remover(lista, 1);
    cout << "--- removi o primeiro (codigo 1) ---\n";
    listar(lista);

    remover(lista, 3);
    cout << "--- removi do meio (codigo 3) ---\n";
    listar(lista);

    remover(lista, 4);
    cout << "--- removi do ultimo (codigo 4) ---\n";
    listar(lista);

    if (!remover(lista, 99)) {
        cout << "Codigo 99 nao existe, nao removeu\n";
    }

    remover(lista, 2);
    cout << "--- remove o que restava (codigo 2) ---\n";
    listar(lista);

    return 0;
}