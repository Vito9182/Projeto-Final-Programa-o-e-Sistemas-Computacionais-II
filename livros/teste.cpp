#include "livros.h"
#include <iostream>

int main() {
    Lista lista;
    for (int i = 0; i < 1000; i++) {
        int codigo = (i * 7) % 1000 + 1;   // codigos de 1 a 1000 fora de ordem
        cadastrar(lista, codigo, "Livro" + to_string(codigo), "Autor", 1);
    }

    int tamanho = 0;
    Livro** vetor = copiarParaVetor(lista, tamanho);
    ordenarPorCodigo(vetor, tamanho);

    int procurados[] = {1, 500, 1000, 5000};
    for (int codigo : procurados) {
        int compSequencial = 0;
        int compBinaria = 0;
        Livro* a = buscarCodigoContando(lista, codigo, compSequencial);
        Livro* b = buscaBinaria(vetor, tamanho, codigo, compBinaria);

        cout << "codigo " << codigo << ": ";
        cout << (a != nullptr ? "achou" : "nao existe") << " | ";
        cout << "sequencial " << compSequencial << " comparacoes | ";
        cout << "binaria " << compBinaria << " comparacoes\n";
    }

    delete[] vetor;
    vetor = nullptr;
    limparLista(lista);

    return 0;
}