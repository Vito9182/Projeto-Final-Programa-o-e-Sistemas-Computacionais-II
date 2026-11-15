
#include <string>
#pragma once
using namespace std;

// Cabeçalho
// Uso de lista encadeada
struct Usuario {
    int codigo;
    string nome;
    string email;
    Usuario* proximo;
};

struct ListaUsuarios {
    Usuario* primeiro = nullptr;
};

// Cadastrar usuário
bool cadastrarUsuario(ListaUsuarios& lista, int codigo, string nome, string email);

// Listar usuários cadastrados
void listarUsuarios(ListaUsuarios& lista);

// Buscar usuário pelo código
Usuario* buscarUsuarioCodigo(ListaUsuarios& lista, int codigo);

// Remover usuário
bool removerUsuario(ListaUsuarios& lista, int codigo);

// Contagem de usuários (usando recursividade)
// e limpeza da lista
int contarUsuarios(Usuario* usuario);
void limparListaUsuarios(ListaUsuarios& lista);
