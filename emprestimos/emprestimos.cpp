#include "emprestimos.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

Emprestimo* buscarEmprestimo(Emprestimo* atual, int codigo) {
    while (atual != nullptr) {
        if (codigo == atual->codigo) {
            return atual;
        }
        atual = codigo < atual->codigo ? atual->esquerda : atual->direita;
    }
    return nullptr;
}

bool inserirEmprestimo(Emprestimo*& raiz, int codigo, int codigoUsuario, int codigoLivro) {
    if (raiz == nullptr) {
        raiz = new Emprestimo{codigo, codigoUsuario, codigoLivro, nullptr, nullptr};
        return true;
    }
    if (codigo == raiz->codigo) {
        return false;
    }
    return inserirEmprestimo(
        codigo < raiz->codigo ? raiz->esquerda : raiz->direita,
        codigo,
        codigoUsuario,
        codigoLivro
    );
}

Emprestimo* removerMenor(Emprestimo*& raiz) {
    if (raiz->esquerda == nullptr) {
        Emprestimo* menor = raiz;
        raiz = raiz->direita;
        return menor;
    }
    return removerMenor(raiz->esquerda);
}

bool removerEmprestimo(Emprestimo*& raiz, int codigo) {
    if (raiz == nullptr) {
        return false;
    }
    if (codigo < raiz->codigo) {
        return removerEmprestimo(raiz->esquerda, codigo);
    }
    if (codigo > raiz->codigo) {
        return removerEmprestimo(raiz->direita, codigo);
    }

    Emprestimo* apagar = raiz;
    if (raiz->esquerda == nullptr) {
        raiz = raiz->direita;
    } else if (raiz->direita == nullptr) {
        raiz = raiz->esquerda;
    } else {
        Emprestimo* sucessor = removerMenor(raiz->direita);
        sucessor->esquerda = raiz->esquerda;
        sucessor->direita = raiz->direita;
        raiz = sucessor;
    }
    delete apagar;
    return true;
}

void registrarEvento(PilhaHistoricoEmprestimos& historico, const std::string& descricao) {
    EventoEmprestimo* evento = new EventoEmprestimo{descricao, historico.topo};
    historico.topo = evento;
    ++historico.tamanho;
}

void enfileirar(FilaEspera& fila, int codigoUsuario, int codigoLivro) {
    SolicitacaoPendente* solicitacao =
        new SolicitacaoPendente{codigoUsuario, codigoLivro, nullptr};
    if (fila.fim == nullptr) {
        fila.inicio = solicitacao;
    } else {
        fila.fim->proxima = solicitacao;
    }
    fila.fim = solicitacao;
    ++fila.tamanho;
}

SolicitacaoPendente* desenfileirar(FilaEspera& fila) {
    if (fila.inicio == nullptr) {
        return nullptr;
    }
    SolicitacaoPendente* solicitacao = fila.inicio;
    fila.inicio = solicitacao->proxima;
    if (fila.inicio == nullptr) {
        fila.fim = nullptr;
    }
    solicitacao->proxima = nullptr;
    --fila.tamanho;
    return solicitacao;
}

int criarEmprestimo(
    ControleEmprestimos& controle,
    Livro& livro,
    int codigoUsuario
) {
    if (controle.proximoCodigoEmprestimo <= 0 || livro.disponiveis <= 0) {
        return 0;
    }

    const int codigo = controle.proximoCodigoEmprestimo;
    if (!inserirEmprestimo(controle.ativos.raiz, codigo, codigoUsuario, livro.codigo)) {
        return 0;
    }

    --livro.disponiveis;
    controle.proximoCodigoEmprestimo =
        codigo == std::numeric_limits<int>::max() ? 0 : codigo + 1;
    registrarEvento(
        controle.historico,
        "Emprestimo " + std::to_string(codigo) + ": usuario " +
            std::to_string(codigoUsuario) + ", livro " + std::to_string(livro.codigo)
    );
    return codigo;
}

void processarFilaParaLivro(
    ControleEmprestimos& controle,
    ListaLivros& livros,
    ListaUsuarios& usuarios,
    int codigoLivro
) {
    Livro* livro = buscarLivroPorCodigo(livros, codigoLivro);
    if (livro == nullptr || livro->disponiveis <= 0) {
        return;
    }

    const std::size_t solicitacoesNaFila = controle.filaEspera.tamanho;
    for (std::size_t i = 0; i < solicitacoesNaFila; ++i) {
        SolicitacaoPendente* solicitacao = desenfileirar(controle.filaEspera);
        if (solicitacao->codigoLivro != codigoLivro) {
            enfileirar(
                controle.filaEspera,
                solicitacao->codigoUsuario,
                solicitacao->codigoLivro
            );
            delete solicitacao;
            continue;
        }

        if (buscarUsuarioCodigo(usuarios, solicitacao->codigoUsuario) == nullptr) {
            registrarEvento(
                controle.historico,
                "Solicitacao descartada: usuario " +
                    std::to_string(solicitacao->codigoUsuario) + " nao existe mais"
            );
            delete solicitacao;
            continue;
        }

        const int codigoEmprestimo =
            criarEmprestimo(controle, *livro, solicitacao->codigoUsuario);
        if (codigoEmprestimo == 0) {
            enfileirar(
                controle.filaEspera,
                solicitacao->codigoUsuario,
                solicitacao->codigoLivro
            );
            delete solicitacao;
            continue;
        }
        delete solicitacao;
    }
}

void listarEmprestimosEmOrdem(const Emprestimo* atual) {
    if (atual == nullptr) {
        return;
    }
    listarEmprestimosEmOrdem(atual->esquerda);
    std::cout << "Emprestimo " << atual->codigo << " / usuario " << atual->codigoUsuario
              << " / livro " << atual->codigoLivro << "\n";
    listarEmprestimosEmOrdem(atual->direita);
}

void liberarArvore(Emprestimo* atual) {
    if (atual == nullptr) {
        return;
    }
    liberarArvore(atual->esquerda);
    liberarArvore(atual->direita);
    delete atual;
}

void restaurarExemplares(const Emprestimo* atual, ListaLivros& livros) {
    if (atual == nullptr) {
        return;
    }

    restaurarExemplares(atual->esquerda, livros);
    Livro* livro = buscarLivroPorCodigo(livros, atual->codigoLivro);
    if (livro != nullptr && livro->disponiveis < livro->quantidade) {
        ++livro->disponiveis;
    }
    restaurarExemplares(atual->direita, livros);
}

} // namespace

SolicitacaoEmprestimo solicitarEmprestimo(
    ControleEmprestimos& controle,
    ListaLivros& livros,
    ListaUsuarios& usuarios,
    int codigoUsuario,
    int codigoLivro
) {
    if (buscarUsuarioCodigo(usuarios, codigoUsuario) == nullptr) {
        return {ResultadoEmprestimo::UsuarioInexistente, 0};
    }

    Livro* livro = buscarLivroPorCodigo(livros, codigoLivro);
    if (livro == nullptr) {
        return {ResultadoEmprestimo::LivroInexistente, 0};
    }

    if (livro->disponiveis <= 0) {
        enfileirar(controle.filaEspera, codigoUsuario, codigoLivro);
        registrarEvento(
            controle.historico,
            "Usuario " + std::to_string(codigoUsuario) + " entrou na fila do livro " +
                std::to_string(codigoLivro)
        );
        return {ResultadoEmprestimo::EmFilaDeEspera, 0};
    }

    const int codigoEmprestimo = criarEmprestimo(controle, *livro, codigoUsuario);
    if (codigoEmprestimo == 0) {
        enfileirar(controle.filaEspera, codigoUsuario, codigoLivro);
        registrarEvento(
            controle.historico,
            "Usuario " + std::to_string(codigoUsuario) + " entrou na fila do livro " +
                std::to_string(codigoLivro)
        );
        return {ResultadoEmprestimo::EmFilaDeEspera, 0};
    }
    return {ResultadoEmprestimo::Emprestado, codigoEmprestimo};
}

bool registrarDevolucao(
    ControleEmprestimos& controle,
    ListaLivros& livros,
    ListaUsuarios& usuarios,
    int codigoEmprestimo
) {
    Emprestimo* emprestimo = buscarEmprestimo(controle.ativos.raiz, codigoEmprestimo);
    if (emprestimo == nullptr) {
        return false;
    }

    const int codigoLivro = emprestimo->codigoLivro;
    const int codigoUsuario = emprestimo->codigoUsuario;
    Livro* livro = buscarLivroPorCodigo(livros, codigoLivro);
    if (livro == nullptr || livro->disponiveis >= livro->quantidade) {
        return false;
    }

    if (!removerEmprestimo(controle.ativos.raiz, codigoEmprestimo)) {
        return false;
    }

    ++livro->disponiveis;
    registrarEvento(
        controle.historico,
        "Devolucao do emprestimo " + std::to_string(codigoEmprestimo) + ": usuario " +
            std::to_string(codigoUsuario) + ", livro " + std::to_string(codigoLivro)
    );
    processarFilaParaLivro(controle, livros, usuarios, codigoLivro);
    return true;
}

void listarEmprestimosAtivos(const ControleEmprestimos& controle) {
    if (controle.ativos.raiz == nullptr) {
        std::cout << "Nenhum emprestimo ativo.\n";
        return;
    }
    listarEmprestimosEmOrdem(controle.ativos.raiz);
}

void listarFilaEspera(const ControleEmprestimos& controle) {
    if (controle.filaEspera.inicio == nullptr) {
        std::cout << "Fila de espera vazia.\n";
        return;
    }
    const SolicitacaoPendente* atual = controle.filaEspera.inicio;
    while (atual != nullptr) {
        std::cout << "Usuario " << atual->codigoUsuario << " / livro " << atual->codigoLivro
                  << "\n";
        atual = atual->proxima;
    }
}

void listarHistoricoEmprestimos(const ControleEmprestimos& controle) {
    if (controle.historico.topo == nullptr) {
        std::cout << "Historico vazio.\n";
        return;
    }
    const EventoEmprestimo* atual = controle.historico.topo;
    while (atual != nullptr) {
        std::cout << atual->descricao << "\n";
        atual = atual->proximo;
    }
}

void limparControleEmprestimos(ControleEmprestimos& controle, ListaLivros& livros) {
    while (SolicitacaoPendente* solicitacao = desenfileirar(controle.filaEspera)) {
        delete solicitacao;
    }
    while (controle.historico.topo != nullptr) {
        EventoEmprestimo* evento = controle.historico.topo;
        controle.historico.topo = evento->proximo;
        delete evento;
        --controle.historico.tamanho;
    }
    restaurarExemplares(controle.ativos.raiz, livros);
    liberarArvore(controle.ativos.raiz);
    controle.ativos.raiz = nullptr;
    controle.proximoCodigoEmprestimo = 1;
}
