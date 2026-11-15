#include "livros.h"
#include <iostream>

void conferir(string teste, bool ok) {
    cout << (ok ? "[ok]   " : "[ERRO] ") << teste << "\n";
}

int main() {
    Lista lista;
    cout << "--- cadastrar e listar ---\n";
    listar(lista);
    conferir("cadastra livro 1", cadastrar(lista, 1, "Livro1", "Autor1", 3));
    conferir("cadastra livro 2", cadastrar(lista, 2, "Livro2", "Autor2", 2));
    conferir("cadastra livro 3", cadastrar(lista, 3, "Livro3", "Autor3", 1));
    conferir("recusa codigo repetido", !cadastrar(lista, 1, "Repetido", "Ninguem", 1));
    listar(lista);

    cout << "--- quantidade padrao ---\n";
    cadastrar(lista, 4, "Livro4", "Autor4");
    conferir("quantidade padrao vale 1", buscarCodigo(lista, 4)->quantidade == 1);

    cout << "--- contar ---\n";
    conferir("conta 4 livros", contar(lista.primeiro) == 4);

    cout << "--- buscas ---\n";
    Livro* achado = buscarCodigo(lista, 2);
    conferir("buscarCodigo acha o 2", achado != nullptr && achado->titulo == "Livro2");
    conferir("buscarCodigo nao acha o 99", buscarCodigo(lista, 99) == nullptr);
    achado = buscarTitulo(lista, "Livro3");
    conferir("buscarTitulo acha o Livro3", achado != nullptr && achado->codigo == 3);
    conferir("buscarTitulo nao acha Inexistente", buscarTitulo(lista, "Inexistente") == nullptr);

    cout << "--- remover ---\n";
    conferir("remove o primeiro (1)", remover(lista, 1) && buscarCodigo(lista, 1) == nullptr);
    conferir("remove um do meio (3)", remover(lista, 3) && buscarCodigo(lista, 3) == nullptr);
    conferir("remove o ultimo (4)", remover(lista, 4) && buscarCodigo(lista, 4) == nullptr);
    conferir("nao remove o 99", !remover(lista, 99));
    conferir("sobrou so 1 livro", contar(lista.primeiro) == 1);
    listar(lista);

    cout << "--- limpar ---\n";
    limparLista(lista);
    conferir("lista vazia depois de limpar", lista.primeiro == nullptr);

    cout << "--- ordenacao e busca binaria (1000 livros) ---\n";
    for (int i = 0; i < 1000; i++) {
        int codigo = (i * 7) % 1000 + 1;   // codigos de 1 a 1000 fora de ordem
        cadastrar(lista, codigo, "Livro" + to_string(codigo), "Autor", 1);
    }

    int tamanho = 0;
    Livro** vetor = copiarParaVetor(lista, tamanho);
    ordenarPorCodigo(vetor, tamanho);

    bool ordenado = true;
    for (int i = 1; i < tamanho; i++) {
        if (vetor[i - 1]->codigo > vetor[i]->codigo) {
            ordenado = false;
        }
    }
    conferir("vetor ordenado por codigo", tamanho == 1000 && ordenado);
    conferir("lista continua na ordem de cadastro",
             lista.primeiro->codigo == 1 && lista.primeiro->proximo->codigo == 8);

    int procurados[] = {1, 500, 1000, 5000};
    for (int codigo : procurados) {
        int compSequencial = 0;
        int compBinaria = 0;
        Livro* a = buscarCodigoContando(lista, codigo, compSequencial);
        Livro* b = buscaBinaria(vetor, tamanho, codigo, compBinaria);

        conferir("sequencial e binaria concordam no codigo " + to_string(codigo), a == b);
        cout << "       sequencial " << compSequencial << " | binaria " << compBinaria
             << " comparacoes\n";
    }

    delete[] vetor;
    vetor = nullptr;
    limparLista(lista);

    return 0;
}