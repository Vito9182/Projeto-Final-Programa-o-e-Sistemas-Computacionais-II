#include "livros.h"
#include <iostream>

int main() {
    Lista lista;
    cadastrar(lista, 30, "Livro30", "Autor30", 1);
    cadastrar(lista, 10, "Livro10", "Autor10", 1);
    cadastrar(lista, 20, "Livro20", "Autor20", 1);
    cadastrar(lista, 5, "Livro5", "Autor5", 1);

    cout << "--- lista na ordem de cadastro ---\n";
    listar(lista);

    int tamanho = 0;
    Livro** vetor = copiarParaVetor(lista, tamanho);
    ordenarPorCodigo(vetor, tamanho);

    cout << "--- vetor ordenado por codigo ---\n";
    for (int i = 0; i < tamanho; i++) {
        cout << vetor[i]->codigo << " / " << vetor[i]->titulo << "\n";
    }

    cout << "--- lista continua igual ---\n";
    listar(lista);

    delete[] vetor;
    vetor = nullptr;
    limparLista(lista);

    return 0;
}