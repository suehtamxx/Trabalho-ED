#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    struct no *esquerda, *direita;
    int conteudo;
}No;

typedef struct{
    No *raiz;
}Arvb;

No *inserir(No *raiz, int valor){
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    else{
        if(valor < raiz->conteudo)
            raiz->esquerda = inserir(raiz->esquerda, valor);
        if(valor > raiz->conteudo)
            raiz->direita = inserir(raiz->direita, valor);
        return raiz;
    }
}

void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

int tamanho(No *raiz){
    if(raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

int pesquisa(No *raiz, int chave){
    if(raiz == NULL)
        return -1;

    if(raiz->conteudo == chave)
        return raiz->conteudo;

    else{
        if(chave < raiz->conteudo)
            return pesquisa(raiz->esquerda, chave);
        else   
            return pesquisa(raiz->direita, chave);
    }
}

No *remover(No *raiz, int chave){
    if(raiz == NULL){
        printf("valor nao encontrado!");
        return NULL;
    }
        if(raiz->conteudo == chave){
            //remove nos sem filhos
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                return NULL;
            }
            else{
                if(raiz->esquerda != NULL || raiz->direita != NULL){
                    No *aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                else
                    aux = raiz->direita;
                free(raiz);
                return aux;
                }
            }
        
        }else{
            if(chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
        return raiz;
    }
}

No *pesquisaNo(No *raiz, int chave){
    if(raiz == NULL)
        return NULL;

    if(raiz->conteudo == chave)
        return raiz;

    else{
        if(chave < raiz->conteudo)
            return pesquisaNo(raiz->esquerda, chave);
        else   
            return pesquisaNo(raiz->direita, chave);
    }
}

int alturaArv(No *raiz){
    if(raiz == NULL)
        return -1;
    else{
        int esq = 1 + alturaArv(raiz->esquerda);
        int dir = 1 + alturaArv(raiz->direita);
    if(esq > dir)
        return esq;
    else  
        return dir;
    }
}

int alturaNo(No *raiz, int chave){
    No *no = pesquisaNo(raiz, chave);
    if(no)
        return alturaArv(no);
    else
        return -1;
}

//funcoes arvores simples
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->conteudo = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

void inserir(No** raiz, int valor) {
    if (*raiz == NULL) {
        *raiz = criarNo(valor);
        return;
    }

    if ((*raiz)->esquerda == NULL) {
        inserir(&(*raiz)->esquerda, valor);
    } else {
        inserir(&(*raiz)->direita, valor);
    }
}

void imprimir(No* raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}
int main(){
    No *raiz = NULL;
    int op = 0, valor, tam = 0, chave = 0;

    do {
        printf("\n1- Inserir\n2 - Imprimir\n3 - Tamanho\n4 - Busca\n5 - remover\n6 - altura\n7 - altura do no\n0 - Sair\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
            case 1:
                printf("digite um valor: \n");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("impressao:\n");
                imprimir(raiz);
                break;
            case 3:
                tam = tamanho(raiz);
                printf("Tamanho da arvore: %d", tam);
                break;
            case 4:
                printf("digite o valor a ser buscado:\n");
                scanf("%d", &chave);
                printf("resultado da busca: %d\n", pesquisa(raiz, chave));
                break;
            case 5:
                printf("digite o valor a ser removido:\n");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
            case 6:
                printf("Altura da arvore: %d\n", alturaArv(raiz));
                break;
            case 7:
                printf("digite o no a ser calculado a altura:\n");
                scanf("%d", &chave);
                printf("A altura do no: %d\n", alturaNo(raiz, chave));
                break;
            case 0:
                printf("saindo");
                break;
            default:
                printf("opcao invalida!");
                break;
            }   
        }while(op != 0);
}
