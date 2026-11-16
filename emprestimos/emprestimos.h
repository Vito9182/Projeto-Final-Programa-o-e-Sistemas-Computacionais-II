#pragma once

#include "../livros/livros.h"
#include "../usuarios/usuarios.h"

#include <cstddef>
#include <string>

enum class ResultadoEmprestimo {
    Emprestado,
    EmFilaDeEspera,
    UsuarioInexistente,
    LivroInexistente
};

struct SolicitacaoEmprestimo {
    ResultadoEmprestimo resultado;
    int codigoEmprestimo;
};

struct SolicitacaoPendente {
    int codigoUsuario;
    int codigoLivro;
    SolicitacaoPendente* proxima;
};

struct FilaEspera {
    SolicitacaoPendente* inicio = nullptr;
    SolicitacaoPendente* fim = nullptr;
    std::size_t tamanho = 0;
};

struct EventoEmprestimo {
    std::string descricao;
    EventoEmprestimo* proximo;
};

struct PilhaHistoricoEmprestimos {
    EventoEmprestimo* topo = nullptr;
    std::size_t tamanho = 0;
};

struct Emprestimo {
    int codigo;
    int codigoUsuario;
    int codigoLivro;
    Emprestimo* esquerda;
    Emprestimo* direita;
};

struct ArvoreEmprestimos {
    Emprestimo* raiz = nullptr;
};

struct ControleEmprestimos {
    FilaEspera filaEspera;
    PilhaHistoricoEmprestimos historico;
    ArvoreEmprestimos ativos;
    int proximoCodigoEmprestimo = 1;
};

SolicitacaoEmprestimo solicitarEmprestimo(
    ControleEmprestimos& controle,
    ListaLivros& livros,
    ListaUsuarios& usuarios,
    int codigoUsuario,
    int codigoLivro
);

bool registrarDevolucao(
    ControleEmprestimos& controle,
    ListaLivros& livros,
    ListaUsuarios& usuarios,
    int codigoEmprestimo
);

void listarEmprestimosAtivos(const ControleEmprestimos& controle);
void listarFilaEspera(const ControleEmprestimos& controle);
void listarHistoricoEmprestimos(const ControleEmprestimos& controle);
void limparControleEmprestimos(ControleEmprestimos& controle, ListaLivros& livros);
