#include "livros.h"
#include <iostream>


// ---- cadastro e listagem ----

// Cadastra um livro no fim da lista.
// lista: lista de livros (por referência, pois é alterada)
// codigo, titulo, autor, quantidade: dados do livro (quantidade vale 1 se omitida)
// Retorna true se cadastrou, false se o código já existe.
bool cadastrarLivro(ListaLivros& lista, int codigo, string titulo, string autor, int quantidade) {
    if (quantidade <= 0) {
        return false;
    }

    // o código de cada livro é único
    if (buscarLivroPorCodigo(lista, codigo) != nullptr) {
        return false;
    }
    // new: o livro fica na memória até o removerLivro ou o limparListaLivros apagarem
    Livro* novo = new Livro;
    novo->codigo = codigo;
    novo->titulo = titulo;
    novo->autor = autor;
    novo->quantidade = quantidade;
    novo->disponiveis = quantidade;
    novo->proximo = nullptr;

    // Se a lista está vazia, o novo livro vira o primeiro.
    if (lista.primeiro == nullptr) {
        lista.primeiro = novo;
        return true;
    }

    // anda até o último livro da lista
    Livro* atual = lista.primeiro;
    while (atual->proximo != nullptr){
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return true;
}

// Mostra todos os livros cadastrados.
// lista: lista de livros a mostrar
// Não retorna nada, só imprime na tela.
void listarLivros(ListaLivros & lista) {
    if (lista.primeiro == nullptr) {
        cout << "Nenhum livro cadastrado\n";
        return;
    }

    Livro* atual = lista.primeiro;
    while (atual != nullptr) {
        cout << atual->codigo << " / " << atual->titulo << " / " << atual->autor
            << " / disponiveis: " << atual->disponiveis << " / " << atual->quantidade << "\n";
        atual = atual->proximo;
    }
}

// ---- busca ----

// Procura um livro pelo código.
// lista: lista onde procurar
// codigo: código do livro procurado
// Retorna o ponteiro do livro, ou nullptr se não achar.
Livro* buscarLivroPorCodigo(ListaLivros& lista, int codigo) {
    int comparacoes = 0;
    return buscarLivroPorCodigoContando(lista, codigo, comparacoes);
}

// Procura um livro pelo título (precisa ser igual).
// lista: lista onde procurar
// titulo: título procurado
// Retorna o ponteiro do livro, ou nullptr se não achar.
Livro* buscarLivroPorTitulo(ListaLivros& lista, string titulo) {
Livro* atual = lista.primeiro;
    while (atual != nullptr) {
        if (atual->titulo == titulo) {
            return atual;
        }
        atual = atual->proximo;
    }
    return nullptr;
}

// ---- remoção, contagem e limpeza ----

// Remove da lista o livro com o código informado e libera a memória dele.
// lista: lista de livros (por referência, pois é alterada)
// codigo: código do livro que vai sair
// Retorna true se removeu, false se não existe livro com esse código.
bool removerLivro(ListaLivros& lista, int codigo) {
    Livro* anterior = nullptr;
    Livro* atual = lista.primeiro;

    // procura o livro, guardando também o anterior
    while (atual != nullptr && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    // não encontrou
    if (atual == nullptr) {
        return false;
    }

    if (atual->disponiveis != atual->quantidade) {
        return false;
    }

    // se for o primeiro, a lista passa a começar no segundo
    // se não, o livro de trás pula o que vai sair
    if (anterior == nullptr) {
        lista.primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    // delete libera a memória do livro removido
    delete atual;
    atual = nullptr;
    return true;
}

// Conta os livros da lista de forma recursiva.
// livro: primeiro livro a contar (use lista.primeiro para contar todos)
// Retorna a quantidade de livros.
int contarLivros(Livro* livro) {
    if (livro == nullptr) {
        return 0;
    }
    return 1 + contarLivros(livro->proximo);
}

// Libera a memória de todos os livros e deixa a lista vazia.
// lista: lista a esvaziar (por referência)
// Não retorna nada.
void limparListaLivros(ListaLivros& lista) {
    while (lista.primeiro != nullptr) {
        Livro* apagar = lista.primeiro;
        lista.primeiro = lista.primeiro->proximo;
        delete apagar;
        apagar = nullptr;
    }
}

// ---- ordenação e busca binária ----

// Copia os ponteiros dos livros da lista para um vetor, sem duplicar os livros.
// lista: lista de onde copiar
// tamanho: recebe a quantidade de livros copiados (por referência)
// Retorna o vetor criado com new[]; quem chamar precisa liberar com delete[].
Livro** copiarLivrosParaVetor(ListaLivros& lista, int& tamanho) {
    tamanho = contarLivros(lista.primeiro);
    // new[]: vetor de ponteiros, liberado por quem chamar
    Livro** vetor = new Livro*[tamanho];

    Livro* atual = lista.primeiro;
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = atual;
        atual = atual->proximo;
    }
    return vetor;
}

// Ordena o vetor pelo código usando Insertion Sort.
// vetor: vetor de ponteiros de livro (fica em ordem crescente de código)
// tamanho: quantidade de livros no vetor
// Complexidade: O(n²) no pior caso (vetor invertido) e O(n) no melhor (já ordenado).
void ordenarLivrosPorCodigo(Livro** vetor, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        Livro* chave = vetor[i];
        int j = i - 1;

        // empurra pra direita os livros com código maior que a chave
        while (j >= 0 && vetor[j]->codigo > chave->codigo) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        // coloca a chave no buraco que sobrou
        vetor[j + 1] = chave;
    }
}

// Busca binária pelo código; o vetor precisa estar ordenado.
// vetor: vetor de ponteiros ordenado por código
// tamanho: quantidade de livros no vetor
// codigo: código procurado
// comparacoes: recebe quantas comparações foram feitas (por referência)
// Retorna o ponteiro do livro, ou nullptr se não achar.
// Complexidade: O(log n), a cada passo descarta metade do vetor.
Livro* buscarLivroBinaria(Livro** vetor, int tamanho, int codigo, int& comparacoes) {
    comparacoes = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        if (vetor[meio]->codigo == codigo) {
            return vetor[meio];
        }
        if (vetor[meio]->codigo < codigo) {
            inicio = meio + 1;   // metade da direita
        } else {
            fim = meio - 1;      // metade da esquerda
        }
    }
    return nullptr;
}

// Busca sequencial pelo código, contando as comparações.
// lista: lista onde procurar
// codigo: código procurado
// comparacoes: recebe quantos livros foram olhados (por referência)
// Retorna o ponteiro do livro, ou nullptr se não achar.
// Complexidade: O(n).
Livro* buscarLivroPorCodigoContando(ListaLivros& lista, int codigo, int& comparacoes) {
    comparacoes = 0;
    Livro* atual = lista.primeiro;
    while (atual != nullptr) {
        comparacoes++;
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->proximo;
    }
    return nullptr;
}








