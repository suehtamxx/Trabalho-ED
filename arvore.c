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
        printf("elemento nao encontrado!");
        return NULL;
    }
    else{
        if(chave == raiz->conteudo){
            free(raiz);
            return NULL;
        }
            if(chave < raiz->conteudo){
                raiz->esquerda = remover(raiz->esquerda, chave);
            }
                if(chave > raiz->conteudo){
                    raiz->direita = remover(raiz->direita, chave);
                }
        }
    }
int main(){
    No *raiz = NULL;
    int op = 0, valor, tam = 0, chave = 0;

    do {
        printf("\n1- Inserir\n2 - Imprimir\n3 - Tamanho\n4 - Busca\n0 - Sair\n");
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
            case 0:
                printf("saindo");
                break;
            default:
                printf("opcao invalida!");
                break;
            }   
    }while(op != 0);
}
