#include "transportadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListaCliente *criarLista()
{
    ListaCliente *novaLista = (ListaCliente*)malloc(sizeof(ListaCliente));
    if (novaLista == NULL) 
    {
        printf("Erro ao alocar a lista de clientes.\n");
        exit(1);
    }
    
    novaLista->cliente = NULL;
    novaLista->prox = NULL;
    return novaLista;
}
void addLista(ListaCliente *l, int *id)
{
    if (l->prox == NULL)
    {
        printf("\nCadastrando um cliente:");
        ListaCliente *novo = (ListaCliente*)malloc(sizeof(ListaCliente));
        if (novo == NULL)
        {
            printf("\nErro ao alocar novo cliente!\n");
            exit(1);
        }

        novo->cliente = (Cliente*)malloc(sizeof(Cliente));
        if (novo->cliente == NULL) 
        {
            printf("Erro ao alocar clientes da lista.\n");
            exit(1);
        }

        printf("\nInforme o nome: ");
        fgets(novo->cliente->nome, sizeof(novo->cliente->nome), stdin);
        setbuf(stdin, NULL);

        printf("\nInforme o CPF: ");
        fgets(novo->cliente->cpf, sizeof(novo->cliente->cpf), stdin);
        setbuf(stdin, NULL);

        printf("\nInforme a Rua em que reside: ");
        fgets(novo->cliente->enderecoRua, sizeof(novo->cliente->enderecoRua), stdin);
        setbuf(stdin, NULL);

        printf("\nInforme o numero da casa: ");
        scanf("%d", &novo->cliente->numCasa);
        setbuf(stdin, NULL);

        novo->prox = NULL;
        novo->id = (*id)++;
        l->prox = novo;
    }
    else addLista(l->prox, id);
}
void mostrarLista(ListaCliente *l)
{
    printf("\nMostrando os Clientes: ");
    if (l == NULL || l->prox == NULL) printf("Lista vazia ");
    else
    {
        ListaCliente *aux = l->prox;
        while (aux != NULL)
        {
            printf("\nCliente ID %d", aux->id);
            printf("\nNome: %s", aux->cliente->nome);
            printf("\nCPF: %s", aux->cliente->cpf);
            printf("\nRua: %s", aux->cliente->enderecoRua);
            printf("\nNumero: %d", aux->cliente->numCasa);
            aux = aux->prox;
        }
    }
}
void liberarLista(ListaCliente *l)
{
    ListaCliente *aux = l;
    while(aux != NULL){
        ListaCliente *prox = aux->prox;
        if (aux->cliente != NULL) free(aux->cliente);
        free(aux);
        aux = prox;
    }
    free(l);
}
