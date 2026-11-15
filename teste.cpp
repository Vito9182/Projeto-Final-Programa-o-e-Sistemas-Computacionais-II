#include <iostream>
#include <string>
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
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1 - Cadastrar usuario\n";
        cout << "2 - Listar usuarios\n";
        cout << "3 - Buscar usuario por codigo\n";
        cout << "4 - Cadastrar livro\n";
        cout << "5 - Listar livros\n";
        cout << "6 - Buscar livro por codigo\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        if (opcao == 1) {
            int codigo;
            string nome, email;

            cout << "Codigo: ";
            cin >> codigo;
            cin.ignore();
            cout << "Nome: ";
            getline(cin, nome);
            cout << "Email: ";
            getline(cin, email);

            if (cadastrarUsuario(lista, codigo, nome, email)) {
                cout << "Usuario cadastrado!\n";
            } else {
                cout << "Codigo ja existe.\n";
            }
        }
        else if (opcao == 2) {
            listarUsuarios(lista);
        }
        else if (opcao == 3) {
            int codigo;
            cout << "Codigo do usuario: ";
            cin >> codigo;

            Usuario* usuario = buscarUsuarioCodigo(lista, codigo);
            if (usuario != nullptr) {
                cout << "Usuario encontrado:\n";
                cout << "Codigo: " << usuario->codigo << "\n";
                cout << "Nome: " << usuario->nome << "\n";
                cout << "Email: " << usuario->email << "\n";
            } else {
                cout << "Usuario nao encontrado.\n";
            }
        }
        else if (opcao == 4) {
            int codigo, quantidade;
            string titulo, autor;

            cout << "Codigo: ";
            cin >> codigo;
            cin.ignore();
            cout << "Titulo: ";
            getline(cin, titulo);
            cout << "Autor: ";
            getline(cin, autor);
            cout << "Quantidade: ";
            cin >> quantidade;

            if (cadastrarLivro(livros, codigo, titulo, autor, quantidade)) {
                cout << "Livro cadastrado!\n";
            } else {
                cout << "Codigo ja existe.\n";
            }
        }
        else if (opcao == 5) {
            listarLivros(livros);
        }
        else if (opcao == 6) {
            int codigo;
            cout << "Codigo do livro: ";
            cin >> codigo;

            Livro* livro = buscarLivroPorCodigo(livros, codigo);
            if (livro != nullptr) {
                cout << "Livro encontrado:\n";
                cout << "Codigo: " << livro->codigo << "\n";
                cout << "Titulo: " << livro->titulo << "\n";
                cout << "Autor: " << livro->autor << "\n";
                cout << "Quantidade: " << livro->quantidade << "\n";
                cout << "Disponiveis: " << livro->disponiveis << "\n";
            } else {
                cout << "Livro nao encontrado.\n";
            }
        }
        else if (opcao == 0) {
            cout << "Saindo...\n";
        }
        else {
            cout << "Opcao invalida!\n";
        }

        cout << "\n";
    } while (opcao != 0);

    limparListaUsuarios(lista);
    limparListaLivros(livros);

    return 0;
}