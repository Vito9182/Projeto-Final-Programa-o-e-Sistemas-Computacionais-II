#include <iostream>
#include <string>
#include <vector>
#include "livros/livros.h"
#include "usuarios/usuarios.h"
using namespace std;

using namespace std;

struct HistoricoEmprestimo {
    int codigoUsuario;
    int codigoLivro;
    string tipo; // "emprestimo" ou "devolucao"
};

void registrarHistorico(vector<HistoricoEmprestimo>& historico, int codigoUsuario, int codigoLivro, const string& tipo) {
    HistoricoEmprestimo item;
    item.codigoUsuario = codigoUsuario;
    item.codigoLivro = codigoLivro;
    item.tipo = tipo;
    historico.push_back(item);
}

void mostrarHistorico(vector<HistoricoEmprestimo>& historico) {
    if (historico.empty()) {
        cout << "Nenhum historico registrado.\n";
        return;
    }

    for (size_t i = 0; i < historico.size(); i++) {
        cout << "Usuario " << historico[i].codigoUsuario
             << " | Livro " << historico[i].codigoLivro
             << " | " << historico[i].tipo << "\n";
    }
}

void mostrarHistoricoPorUsuario(vector<HistoricoEmprestimo>& historico, int codigoUsuario) {
    bool encontrou = false;

    for (size_t i = 0; i < historico.size(); i++) {
        if (historico[i].codigoUsuario == codigoUsuario) {
            cout << "Usuario " << historico[i].codigoUsuario
                 << " | Livro " << historico[i].codigoLivro
                 << " | " << historico[i].tipo << "\n";
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Nenhum registro para esse usuario.\n";
    }
}

int main() {
    ListaUsuarios lista;
    ListaLivros livros;
    vector<HistoricoEmprestimo> historico;

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
        cout << "7 - Remover livro\n";
        cout << "8 - Remover todos os livros\n";
        cout << "9 - Emprestimo de livro\n";
        cout << "10 - Devolucao de livro\n";
        cout << "11 - Historico por usuario\n";
        cout << "12 - Historico geral\n";
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
        else if (opcao == 7) {
            int codigo;
            cout << "Codigo do livro: ";
            cin >> codigo;

            if (removerLivro(livros, codigo)) {
                cout << "Livro removido com sucesso!\n";
            } else {
                cout << "Livro nao encontrado.\n";
            }
        }
        else if (opcao == 8) {
            char confirmacao;
            cout << "Deseja remover todos os livros? (s/n): ";
            cin >> confirmacao;

            if (confirmacao == 's' || confirmacao == 'S') {
                limparListaLivros(livros);
                cout << "Todos os livros foram removidos.\n";
            } else {
                cout << "Operacao cancelada.\n";
            }
        }
        else if (opcao == 9) {
            int codigoUsuario, codigoLivro;
            cout << "Codigo do usuario: ";
            cin >> codigoUsuario;
            cout << "Codigo do livro: ";
            cin >> codigoLivro;

            Usuario* usuario = buscarUsuarioCodigo(lista, codigoUsuario);
            Livro* livro = buscarLivroPorCodigo(livros, codigoLivro);

            if (usuario == nullptr) {
                cout << "Usuario nao encontrado.\n";
            } else if (livro == nullptr) {
                cout << "Livro nao encontrado.\n";
            } else if (livro->disponiveis <= 0) {
                cout << "Livro indisponivel para emprestimo.\n";
            } else {
                livro->disponiveis--;
                registrarHistorico(historico, codigoUsuario, codigoLivro, "emprestimo");
                cout << "Emprestimo realizado com sucesso!\n";
            }
        }
        else if (opcao == 10) {
            int codigoUsuario, codigoLivro;
            cout << "Codigo do usuario: ";
            cin >> codigoUsuario;
            cout << "Codigo do livro: ";
            cin >> codigoLivro;

            Usuario* usuario = buscarUsuarioCodigo(lista, codigoUsuario);
            Livro* livro = buscarLivroPorCodigo(livros, codigoLivro);

            if (usuario == nullptr) {
                cout << "Usuario nao encontrado.\n";
            } else if (livro == nullptr) {
                cout << "Livro nao encontrado.\n";
            } else if (livro->disponiveis >= livro->quantidade) {
                cout << "Esse livro ja esta disponivel.\n";
            } else {
                livro->disponiveis++;
                registrarHistorico(historico, codigoUsuario, codigoLivro, "devolucao");
                cout << "Devolucao registrada com sucesso!\n";
            }
        }
        else if (opcao == 11) {
            int codigoUsuario;
            cout << "Codigo do usuario: ";
            cin >> codigoUsuario;
            mostrarHistoricoPorUsuario(historico, codigoUsuario);
        }
        else if (opcao == 12) {
            mostrarHistorico(historico);
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