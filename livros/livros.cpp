#include "livros.h"
#include <iostream>



//cadastrar livro que vai pro fim da lista
//lista por referencia, titulo e autor por valor
bool cadastrar(Lista& lista, int codigo, string titulo, string autor, int quantidade) {
    //Recusa de codigo repetido
    if (buscarCodigo(lista, codigo) != nullptr) {
        return false;
    }
    //Alocação de memória
    Livro* novo = new Livro;
    novo->codigo = codigo;
    novo->titulo = titulo;
    novo->autor = autor;
    novo->quantidade = quantidade;
    novo->disponiveis = quantidade;
    novo->proximo = nullptr;

    //se a lista estiver vazia, o novo livro vira o primeiro
    if (lista.primeiro == nullptr) {
        lista.primeiro = novo;
        return true;
    }

    //etapas até chegar no ultimo
    Livro* atual = lista.primeiro;
    while (atual->proximo != nullptr){
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return true;
}

//mostra os livros cadastrados
void listar(Lista & lista) {
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

//busca de livros por codigo
//volta nullptr ou o ponteiro se nao encontrar
Livro* buscarCodigo(Lista& lista, int codigo) {
    int comparacoes = 0;
    return buscarCodigoContando(lista, codigo, comparacoes);
}

//busca por titulo(nome precisa ser igual)
Livro* buscarTitulo(Lista& lista, string titulo) {
Livro* atual = lista.primeiro;
    while (atual != nullptr) {
        if (atual->titulo == titulo) {
            return atual;
        }
        atual = atual->proximo;
    }
    return nullptr;
}

//remove livro da lista pelo codigo
bool remover(Lista& lista, int codigo) {
    Livro* anterior = nullptr;
    Livro* atual = lista.primeiro;
    //movimento na lista
    while (atual != nullptr && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    //nao encontrou
    if (atual == nullptr) {
        return false;
    }
    //se for o primeiro a lista começa no segundo
    //se nao o livro de tras pula o que vai sair
    if (anterior == nullptr) {
        lista.primeiro = atual->proximo;
    } 
    
    else {
        anterior->proximo = atual->proximo;
    }

    //liberação da memoria
    delete atual;
    atual = nullptr;
    return true;
}

//contagem de livros
int contar(Livro* livro) {
    if (livro == nullptr) {
        return 0;
    }
    return 1 + contar(livro->proximo);
}

//apaga todos os livros da memoria
void limparLista(Lista& lista) {
    while (lista.primeiro != nullptr) {
        Livro* apagar = lista.primeiro;
        lista.primeiro = lista.primeiro->proximo;
        delete apagar;
        apagar = nullptr;
    }
}

//--------------------------------//
//Ordenação e busca binária

Livro** copiarParaVetor(Lista& lista, int& tamanho) {
    tamanho = contar(lista.primeiro);
    Livro** vetor = new Livro*[tamanho]; //alocação de vetor

    Livro* atual = lista.primeiro;
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = atual;
        atual = atual->proximo;
    }
    return vetor;
}

//ordena o vetor pelo codigo usando Insertion Sort
//O (n^2) no pior caso (vetor invertido) e O (n) no melhor (ja ordenado)
void ordenarPorCodigo(Livro** vetor, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        Livro* chave = vetor[i];
        int j = i - 1;

        //empurra pra direita os livros com codigo maior que a chave
        while (j >= 0 && vetor[j]->codigo > chave->codigo) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        //coloca a chave no buraco que sobrou
        vetor[j + 1] = chave;
    }
}

//Busca binaria no vetor
Livro* buscaBinaria(Livro** vetor, int tamanho, int codigo, int& comparacoes) {
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
            inicio = meio + 1;   //metade da direita
        } else {
            fim = meio - 1;      //metade da esquerda
        }
    }
    return nullptr;
}

// busca sequencial igual o buscarCodigo, mas conta quantas comparaçoes fez
Livro* buscarCodigoContando(Lista& lista, int codigo, int& comparacoes) {
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









