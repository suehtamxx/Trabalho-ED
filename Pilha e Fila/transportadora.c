#include "transportadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Funções Cliente
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
Cliente* buscarLista(ListaCliente *l, const char *cpf) 
{
    ListaCliente *atual = l->prox; 

    while (atual != NULL) {
        if (strcmp(atual->cliente->cpf, cpf) == 0) 
            return atual->cliente;
        atual = atual->prox;
    }

    return NULL; 
}
void addLista(ListaCliente *l, int *id)
{
    char buscaCpf[14];

    printf("\nInforme o CPF: ");
    fgets(buscaCpf, sizeof(buscaCpf), stdin);
    buscaCpf[strcspn(buscaCpf, "\n")] = 0;
    setbuf(stdin, NULL);

    if (buscarLista(l, buscaCpf) != NULL) {
        printf("\nCliente com CPF %s ja cadastrado!\n", buscaCpf);
        return;
    }

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

    strcpy(novo->cliente->cpf, buscaCpf);
    
    printf("\nInforme o nome: ");
    fgets(novo->cliente->nome, sizeof(novo->cliente->nome), stdin);
    setbuf(stdin, NULL);

    printf("\nInforme a rua em que reside: ");
    fgets(novo->cliente->enderecoRua, sizeof(novo->cliente->enderecoRua), stdin);
    setbuf(stdin, NULL);
    
    printf("\nInforme o numero da casa: ");
    scanf("%d", &novo->cliente->numCasa);
    setbuf(stdin, NULL);

    novo->prox = NULL;
    novo->id = (*id)++;

    ListaCliente *atual = l;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;

    printf("\nCliente cadastrado com sucesso! ID: %d\n", novo->id);
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
            printf("Nome: %s", aux->cliente->nome);
            printf("CPF: %s", aux->cliente->cpf);
            printf("Rua: %s", aux->cliente->enderecoRua);
            printf("Numero: %d", aux->cliente->numCasa);
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


Pilha *criarPilha()
{
    return NULL;
}
void empilharPilha(Pilha **p, Entrega *entrega)
{
    Pilha *novo = (Pilha *)malloc(sizeof(Pilha));
    if(novo == NULL){
        printf("erro ao alocar memoria!\n");
        exit(1);
    }
    novo->entrega = entrega;
    novo->prox = *p;
    *p = novo;
}
Entrega *desempilharPilha(Pilha **p)
{
    if(*p == NULL)
    {
        printf("Pilha vazia!\n");
        return NULL;
    }
    Pilha *aux = *p;
    Entrega *remove = aux->entrega;
    *p = aux->prox;
    free(aux);
    return remove;
}
//contar a pilha para descontar no score
void mostrarPilha(Pilha *p)
{
    Pilha *atual = p;
    while(atual != NULL)
    {
        printf("Entrega para: %s\n", atual->entrega->pedido->cliente->nome);
        atual = atual->prox;
    }
}
void liberarPilha(Pilha **p)
{
    Pilha *aux;
    while(*p != NULL)
    {
        aux = *p;
        *p = (*p)->prox;
        free(aux);
    }
}


Fila *criarFila()
{
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if(novaFila == NULL)
    {
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    novaFila->inicio = NULL;
    novaFila->fim = NULL;
    return novaFila;
}
void addFila(Fila *f, Entrega *entrega)
{
    Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
    if(novaEntrega == NULL)
    {
        printf("erro ao alocar memoria!");
        exit(1);
    }
    *novaEntrega = *entrega; //copia o conteudo de entrega
    novaEntrega->prox = NULL;

    if(f->fim == NULL)
    {
        f->inicio = novaEntrega;
        f->fim = novaEntrega;
    }
    else
    {
        f->fim->prox = novaEntrega;
        f->fim = novaEntrega;
    }
    
}
Entrega *retirarFila(Fila *f)
{
    if(f->inicio == NULL)
    {
        printf("fila de entrega esta vazia!");
        return NULL;
    }

    Entrega *remover = f->inicio;
    f->inicio = f->inicio->prox;
    if(f->inicio == NULL)
        f->fim = NULL;

    remover->prox = NULL;
    return remover;

}
void mostarFila(Fila *f)
{
    if(f->inicio == NULL) printf("Fila vazia!");
    else
    {
        printf("Mostrando os itens a ser entregues:\n");
        Entrega *aux = f->inicio;
        while(aux != NULL)
        {
            printf("\nNome do cliente: %s", aux->pedido->cliente->nome);
            printf("\nNome do item: %s", aux->pedido->nomeP);
            printf("\nQuantidade de itens: %d", aux->pedido->quantidade);
            printf("\nEndereço: %s, N: %d", aux->pedido->cliente->enderecoRua, aux->pedido->cliente->numCasa);
            aux = aux->prox;
        }
    }
}
void liberarFila(Fila **f)
{
    Entrega *aux;
    while((*f)->inicio != NULL)
    {
        aux = (*f)->inicio;
        (*f)->inicio = (*f)->inicio->prox;
        free(aux);
    }
    free(*f);
    *f = NULL;
}

// Funções Pedido
void cadastrarPedido(Fila *f, ListaCliente *l)
{
    if(l->prox == NULL)
    {
        printf("Nenhum cliente cadastrado!\n");
        return;
    }

    Pedido *novoPedido = (Pedido *)malloc(sizeof(Pedido));
    if(novoPedido == NULL)
    {
        printf("erro ao alocar memoria!");
        exit(1);
    }

    char buscaCpf[14];
    printf("\nDigite o CPF do cliente para entrega:\n");
    fgets(buscaCpf, sizeof(buscaCpf), stdin);
    buscaCpf[strcspn(buscaCpf, "\n")] = 0; 
    setbuf(stdin, NULL);

    Cliente *cliente = buscarLista(l, buscaCpf);

    if (cliente == NULL)
    {
        printf("Cliente não encontrado!\n");
        free(novoPedido);
        return;
    }

    novoPedido->cliente = cliente;

    printf("\nDigite a quantidade de itens:\n");
    scanf("%d", &novoPedido->quantidade);
    setbuf(stdin, NULL);

    printf("\nNome do item que vai ser entregue:\n");
    fgets(novoPedido->nomeP, sizeof(novoPedido->nomeP), stdin);
    novoPedido->nomeP[strcspn(novoPedido->nomeP, "\n")] = 0;
    setbuf(stdin, NULL);

    // novoPedido->prox = *p;
    // *p = novoPedido;

    agruparPorEndereco(f, novoPedido);

    printf("Pedido adicionado: %s, quantidade: %d, para o endereco: %s\n", novoPedido->nomeP, novoPedido->quantidade, novoPedido->cliente->enderecoRua);
}

void agruparPorEndereco(Fila *f, Pedido *novoPedido)
{
    if (f->inicio == NULL) 
    {
        Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
        if (novaEntrega == NULL) {
            printf("Erro ao alocar memória para nova entrega!\n");
            exit(1);
        }
        novaEntrega->pedido = novoPedido;
        novaEntrega->tentativa = 0;
        novaEntrega->prox = NULL;
        addFila(f, novaEntrega);
        return;
    }
    
    int novaEntregaAdicionada = 0;

    Fila *filaAux = criarFila();
    Entrega *entrega;

    Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
    if (novaEntrega == NULL) {
        printf("Erro ao alocar memória para nova entrega!\n");
        exit(1);
    }

    novaEntrega->pedido = novoPedido;
    novaEntrega->tentativa = 0;
    novaEntrega->prox = NULL;

    while ((entrega = retirarFila(f)) != NULL) 
    {
        if (strcmp(novoPedido->cliente->enderecoRua, entrega->pedido->cliente->enderecoRua) == 0) 
        {
            addFila(filaAux, novaEntrega);
            novaEntregaAdicionada = 1;
        }
        addFila(filaAux, entrega);        
    }

    if(!novaEntregaAdicionada) addFila(filaAux, novaEntrega);
    
    while ((entrega = retirarFila(filaAux)) != NULL)
        addFila(f, entrega);
}

void entregar(Fila *f, Pilha **p, Fila *dev)
{
    //agruparPorEndereco(f);

    while (f->inicio != NULL)
    {
        Entrega *entrega = retirarFila(f);
        entrega->tentativa = 1;  // Primeira tentativa

        // Verifica se há entregas com o mesmo endereço
        printf("Iniciando a entrega para %s.\n", entrega->pedido->cliente->nome);
        int i = rand() % 10;
        int sucesso = (i < 7);

        if (sucesso)
        {
            printf("Entrega realizada para %s.\n", entrega->pedido->cliente->nome);
            //free(entrega);

            // Entregar todas as entregas seguintes com o mesmo endereço
            while (f->inicio != NULL && strcmp(entrega->pedido->cliente->enderecoRua, f->inicio->pedido->cliente->enderecoRua) == 0)
            {
                Entrega *proxEntrega = retirarFila(f);
                proxEntrega->tentativa = 1;
                printf("Entrega realizada para %s.\n", proxEntrega->pedido->cliente->nome);
                free(entrega);
                free(proxEntrega);
                
            }
            
        }
        else
        {
            printf("Entrega não efetuada, tentativa adicionada à pilha para %s.\n", entrega->pedido->cliente->nome);
            empilharPilha(p, entrega);  // Movendo para a pilha para nova tentativa
        }
    }

    // Tentar entregar os itens na pilha
    while (*p != NULL)
    {
        Entrega *entrega = desempilharPilha(p);
        entrega->tentativa = 2;  // Segunda tentativa

        int i = rand() % 10;
        if (i < 7)
        {
            printf("Entrega efetuada na segunda tentativa para %s.\n", entrega->pedido->cliente->nome);
            free(entrega);
        }
        else
        {
            printf("Pedido será devolvido pois não conseguimos entregar (2 tentativas) para %s.\n", entrega->pedido->cliente->nome);
            addFila(dev, entrega);  // Movendo para a fila de devolução
        }
    }
}


