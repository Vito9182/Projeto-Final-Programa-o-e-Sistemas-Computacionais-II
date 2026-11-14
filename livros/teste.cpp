#include "livros.h"
#include <iostream>

int main() {
    Lista lista;
    cout << "total com a lista vazia: " << contar(lista.primeiro) << "\n";

    cadastrar(lista, 1, "Livro1", "Autor1", 1);
    cadastrar(lista, 2, "Livro2", "Autor2", 1);
    cadastrar(lista, 3, "Livro3", "Autor3", 1);
    cout << "total com tres livros: " << contar(lista.primeiro) << "\n";

    remover(lista, 2);
    cout << "total depois de remover um: " << contar(lista.primeiro) << "\n";

    limparLista(lista);
    cout << "total depois de limpar tudo: " << contar(lista.primeiro) << "\n";
    listar(lista);

    return 0;
}