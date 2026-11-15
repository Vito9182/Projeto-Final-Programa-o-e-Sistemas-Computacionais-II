
#include "usuarios.h"
#include <iostream>

// Cadastra um novo usuário na lista
// Retorna false se o código já estiver cadastrado
bool cadastrarUsuario(ListaUsuarios& lista, int codigo, string nome, string email) {
    if (buscarUsuarioCodigo(lista, codigo) != nullptr) {
        return false;
    }

    Usuario* novo = new Usuario;
    novo->codigo = codigo;
    novo->nome = nome;
    novo->email = email;
    novo->proximo = lista.primeiro;

    lista.primeiro = novo;
    return true;
}

// Exibe todos os usuários cadastrados
void listarUsuarios(ListaUsuarios& lista) {
    Usuario* atual = lista.primeiro;

    if (atual == nullptr) {
        cout << "Nenhum usuario cadastrado.\n";
        return;
    }

    while (atual != nullptr) {
        cout << "\nCodigo: " << atual->codigo;
        cout << "\nNome: " << atual->nome;
        cout << "\nEmail: " << atual->email << "\n";
        atual = atual->proximo;
    }
}

// Busca um usuário pelo código
// Retorna o endereço do usuário ou nullptr
Usuario* buscarUsuarioCodigo(ListaUsuarios& lista, int codigo) {
    Usuario* atual = lista.primeiro;

    while (atual != nullptr) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->proximo;
    }

    return nullptr;
}

// Remove um usuário pelo código
// Retorna false se não encontrar o usuário
bool removerUsuario(ListaUsuarios& lista, int codigo) {
    Usuario* atual = lista.primeiro;
    Usuario* anterior = nullptr;

    while (atual != nullptr && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        return false;
    }

    if (anterior == nullptr) {
        lista.primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;
    return true;
}

// Conta os usuários de forma recursiva
int contarUsuarios(Usuario* usuario) {
    if (usuario == nullptr) {
        return 0;
    }

    return 1 + contarUsuarios(usuario->proximo);
}

// Libera toda a memória da lista
void limparListaUsuarios(ListaUsuarios& lista) {
    Usuario* atual = lista.primeiro;

    while (atual != nullptr) {
        Usuario* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }

    lista.primeiro = nullptr;
}
