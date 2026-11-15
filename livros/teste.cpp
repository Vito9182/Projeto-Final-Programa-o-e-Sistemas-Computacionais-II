#include "livros.h"
#include <iostream>

void conferir(string teste, bool ok) {
    cout << (ok ? "[ok]   " : "[ERRO] ") << teste << "\n";
}

int main() {
    ListaLivros lista;
    cout << "--- cadastrar e listar ---\n";
    listarLivros(lista);
    conferir("cadastra livro 1", cadastrarLivro(lista, 1, "Livro1", "Autor1", 3));
    conferir("cadastra livro 2", cadastrarLivro(lista, 2, "Livro2", "Autor2", 2));
    conferir("cadastra livro 3", cadastrarLivro(lista, 3, "Livro3", "Autor3", 1));
    conferir("recusa codigo repetido", !cadastrarLivro(lista, 1, "Repetido", "Ninguem", 1));
    listarLivros(lista);

    cout << "--- quantidade padrao ---\n";
    cadastrarLivro(lista, 4, "Livro4", "Autor4");
    conferir("quantidade padrao vale 1", buscarLivroPorCodigo(lista, 4)->quantidade == 1);

    cout << "--- contar ---\n";
    conferir("conta 4 livros", contarLivros(lista.primeiro) == 4);

    cout << "--- buscas ---\n";
    Livro* achado = buscarLivroPorCodigo(lista, 2);
    conferir("buscarCodigo acha o 2", achado != nullptr && achado->titulo == "Livro2");
    conferir("buscarCodigo nao acha o 99", buscarLivroPorCodigo(lista, 99) == nullptr);
    achado = buscarLivroPorTitulo(lista, "Livro3");
    conferir("buscarTitulo acha o Livro3", achado != nullptr && achado->codigo == 3);
    conferir("buscarTitulo nao acha Inexistente", buscarLivroPorTitulo(lista, "Inexistente") == nullptr);

    cout << "--- remover ---\n";
    conferir("remove o primeiro (1)", removerLivro(lista, 1) && buscarLivroPorCodigo(lista, 1) == nullptr);
    conferir("remove um do meio (3)", removerLivro(lista, 3) && buscarLivroPorCodigo(lista, 3) == nullptr);
    conferir("remove o ultimo (4)", removerLivro(lista, 4) && buscarLivroPorCodigo(lista, 4) == nullptr);
    conferir("nao remove o 99", !removerLivro(lista, 99));
    conferir("sobrou so 1 livro", contarLivros(lista.primeiro) == 1);
    listarLivros(lista);

    cout << "--- limpar ---\n";
    limparListaLivros(lista);
    conferir("lista vazia depois de limpar", lista.primeiro == nullptr);

    cout << "--- ordenacao e busca binaria (1000 livros) ---\n";
    for (int i = 0; i < 1000; i++) {
        int codigo = (i * 7) % 1000 + 1;   // codigos de 1 a 1000 fora de ordem
        cadastrarLivro(lista, codigo, "Livro" + to_string(codigo), "Autor", 1);
    }

    int tamanho = 0;
    Livro** vetor = copiarLivrosParaVetor(lista, tamanho);
    ordenarLivrosPorCodigo(vetor, tamanho);

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
        Livro* a = buscarLivroPorCodigoContando(lista, codigo, compSequencial);
        Livro* b = buscarLivroBinaria(vetor, tamanho, codigo, compBinaria);

        conferir("sequencial e binaria concordam no codigo " + to_string(codigo), a == b);
        cout << "       sequencial " << compSequencial << " | binaria " << compBinaria
             << " comparacoes\n";
    }

    delete[] vetor;
    vetor = nullptr;
    limparListaLivros(lista);

    return 0;
}