#include <iostream>
#include "livros/livros.h"
#include "usuarios/usuarios.h"

using namespace std;

int main() {
    ListaUsuarios lista;
    ListaLivros livros;

    cadastrarUsuario(lista, 1, "Henrique", "henrique@email.com");
    cadastrarLivro(livros, 10, "C++ Basico", "Autor X", 2);

    int opcao;
    do {
        cout << "\n==== MENU PRINCIPAL ====\n";
        cout << "1 - Listar usuarios\n";
        cout << "2 - Listar livros\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                listarUsuarios(lista);
                break;
            case 2:
                listarLivros(livros);
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != 0);

    limparListaUsuarios(lista);
    limparListaLivros(livros);

    return 0;
}