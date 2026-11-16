#include "emprestimos.h"

#include <iostream>

namespace {

int falhas = 0;

void conferir(const char* nome, bool resultado) {
    std::cout << (resultado ? "[ok]   " : "[ERRO] ") << nome << "\n";
    if (!resultado) {
        ++falhas;
    }
}

} // namespace

int main() {
    ListaLivros livros;
    ListaUsuarios usuarios;
    ControleEmprestimos controle;

    conferir("cadastra livro", cadastrarLivro(livros, 10, "Livro", "Autor", 1));
    conferir("recusa quantidade zero", !cadastrarLivro(livros, 11, "Invalido", "Autor", 0));
    conferir("cadastra usuarios", cadastrarUsuario(usuarios, 1, "Ana", "ana@email.com"));
    conferir("cadastra segundo usuario", cadastrarUsuario(usuarios, 2, "Bia", "bia@email.com"));

    SolicitacaoEmprestimo primeiro = solicitarEmprestimo(controle, livros, usuarios, 1, 10);
    conferir(
        "empresta exemplar disponivel",
        primeiro.resultado == ResultadoEmprestimo::Emprestado &&
            primeiro.codigoEmprestimo == 1
    );
    conferir(
        "quantidade disponivel diminui",
        buscarLivroPorCodigo(livros, 10)->disponiveis == 0
    );
    conferir(
        "nao remove livro emprestado",
        !removerLivro(livros, 10)
    );

    SolicitacaoEmprestimo segundo = solicitarEmprestimo(controle, livros, usuarios, 2, 10);
    conferir(
        "coloca solicitacao sem estoque na fila",
        segundo.resultado == ResultadoEmprestimo::EmFilaDeEspera &&
            controle.filaEspera.tamanho == 1
    );
    conferir(
        "recusa usuario inexistente",
        solicitarEmprestimo(controle, livros, usuarios, 99, 10).resultado ==
            ResultadoEmprestimo::UsuarioInexistente
    );
    conferir(
        "recusa livro inexistente",
        solicitarEmprestimo(controle, livros, usuarios, 1, 99).resultado ==
            ResultadoEmprestimo::LivroInexistente
    );

    conferir("registra devolucao", registrarDevolucao(controle, livros, usuarios, 1));
    conferir(
        "fila recebe o exemplar devolvido",
        controle.filaEspera.tamanho == 0 &&
            buscarLivroPorCodigo(livros, 10)->disponiveis == 0
    );
    conferir(
        "emprestimo da fila fica ativo na arvore",
        controle.ativos.raiz != nullptr &&
            controle.ativos.raiz->codigo == 2 &&
            controle.ativos.raiz->codigoUsuario == 2
    );
    conferir("nao devolve emprestimo duas vezes", !registrarDevolucao(controle, livros, usuarios, 1));
    conferir("devolve emprestimo atendido da fila", registrarDevolucao(controle, livros, usuarios, 2));
    conferir(
        "devolucao atualiza quantidade",
        buscarLivroPorCodigo(livros, 10)->disponiveis == 1
    );
    conferir("livro pode ser removido sem emprestimos", removerLivro(livros, 10));

    conferir("cadastra dois livros para testar fila por livro",
             cadastrarLivro(livros, 20, "Livro 20", "Autor", 1) &&
                 cadastrarLivro(livros, 30, "Livro 30", "Autor", 1));
    SolicitacaoEmprestimo livro20 =
        solicitarEmprestimo(controle, livros, usuarios, 1, 20);
    SolicitacaoEmprestimo livro30 =
        solicitarEmprestimo(controle, livros, usuarios, 1, 30);
    conferir(
        "empresta os dois novos livros",
        livro20.resultado == ResultadoEmprestimo::Emprestado &&
            livro30.resultado == ResultadoEmprestimo::Emprestado
    );
    solicitarEmprestimo(controle, livros, usuarios, 2, 20);
    solicitarEmprestimo(controle, livros, usuarios, 2, 30);
    conferir("duas solicitacoes aguardam na fila", controle.filaEspera.tamanho == 2);
    conferir(
        "devolucao atende solicitacao do mesmo livro",
        registrarDevolucao(controle, livros, usuarios, livro20.codigoEmprestimo) &&
            controle.filaEspera.tamanho == 1 &&
            buscarLivroPorCodigo(livros, 20)->disponiveis == 0
    );
    conferir(
        "fila preserva solicitacao de outro livro",
        registrarDevolucao(controle, livros, usuarios, livro30.codigoEmprestimo) &&
            controle.filaEspera.tamanho == 0 &&
            buscarLivroPorCodigo(livros, 30)->disponiveis == 0
    );
    conferir("devolve emprestimos atendidos pela fila",
             registrarDevolucao(controle, livros, usuarios, 5) &&
                 registrarDevolucao(controle, livros, usuarios, 6));
    conferir(
        "estoque dos dois livros foi atualizado",
        buscarLivroPorCodigo(livros, 20)->disponiveis == 1 &&
            buscarLivroPorCodigo(livros, 30)->disponiveis == 1
    );

    SolicitacaoEmprestimo ativoNaLimpeza =
        solicitarEmprestimo(controle, livros, usuarios, 1, 20);
    conferir(
        "emprestimo ativo antes da limpeza",
        ativoNaLimpeza.resultado == ResultadoEmprestimo::Emprestado &&
            buscarLivroPorCodigo(livros, 20)->disponiveis == 0
    );
    limparControleEmprestimos(controle, livros);
    conferir(
        "limpeza libera estruturas e restaura estoque",
        controle.ativos.raiz == nullptr && controle.filaEspera.tamanho == 0 &&
            controle.historico.topo == nullptr &&
            buscarLivroPorCodigo(livros, 20)->disponiveis == 1
    );
    limparListaLivros(livros);
    limparListaUsuarios(usuarios);

    return falhas == 0 ? 0 : 1;
}
