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
    scanf(" %[^\n]", buscaCpf);
    setbuf(stdin, NULL);

    if (buscarLista(l, buscaCpf) != NULL) {
        printf("\nCliente com CPF %s ja cadastrado!\n", buscaCpf);
        return;
    }

    printf("\nCadastrando um cliente:\n");
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
    scanf(" %49[^\n]", novo->cliente->nome);
    setbuf(stdin, NULL);

    printf("\nInforme a rua em que reside: ");
    scanf(" %[^\n]", novo->cliente->enderecoRua);
    setbuf(stdin, NULL);
    
    printf("\nInforme o numero da casa: ");
    scanf(" %d", &novo->cliente->numCasa);
    setbuf(stdin, NULL);

    novo->prox = NULL;
    novo->id = (*id)++;

    ListaCliente *atual = l;
    while (atual->prox != NULL) 
        atual = atual->prox;

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
            printf("\nNome: %s", aux->cliente->nome);
            printf("\nCPF: %s", aux->cliente->cpf);
            printf("\nRua: %s", aux->cliente->enderecoRua);
            printf("\nNumero: %d", aux->cliente->numCasa);
            printf("\n");
            aux = aux->prox;
        }
    }
}
void liberarLista(ListaCliente *l)
{
    ListaCliente *aux = l;
    while(aux != NULL)
    {
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
        printf("Erro ao alocar memoria!\n");
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
void mostrarPilha(Pilha *p)
{
    Pilha *atual = p;
    while(atual != NULL)
    {
        printf("\nEntrega para: %s \n", atual->entrega->pedido->cliente->nome);
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
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    novaFila->inicio = NULL;
    novaFila->fim = NULL;
    return novaFila;
}
void addFila(Fila *f, Entrega *entrega)
{
    entrega->prox = NULL;

    if(f->inicio == NULL)
    {
        f->inicio = entrega;
        f->fim = entrega;
    } 
    else 
    {
        f->fim->prox = entrega;
        f->fim = entrega;
    }
}
Entrega *retirarFila(Fila *f)
{
    if(f->inicio == NULL) return NULL;

    Entrega *remover = f->inicio;
    f->inicio = f->inicio->prox;

    if(f->inicio == NULL) f->fim = NULL;

    return remover;

}
void mostarFila(Fila *f)
{
    if(f->inicio == NULL) printf("Fila vazia!\n");
    else
    {
        printf("\nMostrando os itens a ser entregues:");
        Entrega *aux = f->inicio;
        while(aux != NULL)
        {
            printf("\nNome do cliente: %s", aux->pedido->cliente->nome);
            printf("\nNome do item: %s", aux->pedido->nomeP);
            printf("\nQuantidade de itens: %d", aux->pedido->quantidade);
            printf("\nEndereco: %s, Num: %d", aux->pedido->cliente->enderecoRua, aux->pedido->cliente->numCasa);
            printf("\n");
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
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }

    Pedido *novoPedido = (Pedido *)malloc(sizeof(Pedido));
    if(novoPedido == NULL)
    {
        printf("\nErro ao alocar memoria!");
        exit(1);
    }

    char buscaCpf[14];
    printf("\nDigite o CPF do cliente para entrega: ");
    scanf(" %[^\n]", buscaCpf);
    setbuf(stdin, NULL);

    Cliente *cliente = buscarLista(l, buscaCpf);

    if (cliente == NULL)
    {
        printf("Cliente nao encontrado!\n");
        free(novoPedido);
        return;
    }

    novoPedido->cliente = cliente;

    printf("\nNome do item que vai ser entregue: ");
    scanf("%[^\n]", novoPedido->nomeP);
    setbuf(stdin, NULL);

    printf("\nDigite a quantidade de itens: ");
    scanf(" %d", &novoPedido->quantidade);
    setbuf(stdin, NULL);
    
    agruparPorEndereco(f, novoPedido);

    printf("Pedido adicionado!\n");
    printf("Nome: %s, quantidade: %d, para o endereco: %s \n", novoPedido->nomeP, novoPedido->quantidade, novoPedido->cliente->enderecoRua);
}

void agruparPorEndereco(Fila *f, Pedido *novoPedido)
{
    if (f->inicio == NULL) 
    {
        Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
        if (novaEntrega == NULL) 
        {
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
    if (novaEntrega == NULL) 
    {
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

// void agruparPorEndereco(Fila *f, Pedido *novoPedido)
// {
//     Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
//     if (novaEntrega == NULL) {
//         printf("Erro ao alocar memória para nova entrega!\n");
//         exit(1);
//     }
//     novaEntrega->pedido = novoPedido;
//     novaEntrega->tentativa = 0;
//     novaEntrega->prox = NULL;

//     Fila *filaAux = criarFila();
//     Entrega *entrega;
//     int novaEntregaAdicionada = 0;

//     while (f->inicio != NULL) 
//     {
//         entrega = retirarFila(f);

//         if (!novaEntregaAdicionada && strcmp(novoPedido->cliente->enderecoRua, entrega->pedido->cliente->enderecoRua) == 0) 
//         {
//             addFila(filaAux, novaEntrega);
//             novaEntregaAdicionada = 1;
//         }

//         addFila(filaAux, entrega);
//     }

//     if (!novaEntregaAdicionada)
//         addFila(filaAux, novaEntrega);

//     while ((entrega = retirarFila(filaAux)) != NULL)
//         addFila(f, entrega);

//     liberarFila(&filaAux); // Libera a memória usada pela fila auxiliar
// }

void entregar(Fila *f, Pilha **p, Fila *dev, int *score)
{
    srand(time(NULL));

    while (f->inicio != NULL)
    {
        // Retira o primeiro pedido da fila
        Entrega *entrega = retirarFila(f);
        entrega->tentativa = 1; // Primeira tentativa

        // Verifica o sucesso da entrega
        printf("\nIniciando a entrega para %s.", entrega->pedido->cliente->nome);
        int i = rand() % 2;
        int sucesso = (i == 1);

        if (sucesso)
        {
            printf("Entrega realizada para %s.\n", entrega->pedido->cliente->nome);
            *score += 5;

            // Entregar todas as entregas seguintes com o mesmo endereço
            Entrega *proxEntrega;
            while (f->inicio != NULL && strcmp(entrega->pedido->cliente->enderecoRua, f->inicio->pedido->cliente->enderecoRua) == 0)
            {
                proxEntrega = retirarFila(f);
                proxEntrega->tentativa = 1;
                printf("Entrega realizada para %s.", proxEntrega->pedido->cliente->nome);
                free(proxEntrega);
                *score += 5;
            }

            free(entrega);
        }

        else
        {
            printf("Entrega nao efetuada! Pedido adicionado a pilha para %s.", entrega->pedido->cliente->nome);
            empilharPilha(p, entrega);  // Movendo para a pilha para nova tentativa

            // Também empilha todas as entregas seguintes com o mesmo endereço
            while (f->inicio != NULL && strcmp(entrega->pedido->cliente->enderecoRua, f->inicio->pedido->cliente->enderecoRua) == 0)
            {
                Entrega *proxEntrega = retirarFila(f);;
                proxEntrega->tentativa = 1;
                printf("Entrega nao efetuada! Pedido adicionado a pilha para %s.", proxEntrega->pedido->cliente->nome);
                empilharPilha(p, proxEntrega);
            }
            
        }
    }

    // Tentar entregar os itens na pilha
    while (*p != NULL)
    {
        Entrega *entrega = desempilharPilha(p);
        entrega->tentativa = 2;  // Segunda tentativa

        // Verifica o sucesso da segunda tentativa
        printf("\nIniciando a entrega na segunda tentativa para %s.\n", entrega->pedido->cliente->nome);
        int i = rand() % 2;
        int sucesso = (i == 1);

        if (sucesso)
        {
            printf("Entrega efetuada na segunda tentativa para %s.\n", entrega->pedido->cliente->nome);
            *score += 3;

            // Entregar todas as entregas seguintes com o mesmo endereço
            while (*p != NULL && strcmp(entrega->pedido->cliente->enderecoRua, (*p)->entrega->pedido->cliente->enderecoRua) == 0)
            {
                Entrega *proxEntrega = desempilharPilha(p);
                proxEntrega->tentativa = 2;
                printf("Entrega efetuada na segunda tentativa para %s.\n", proxEntrega->pedido->cliente->nome);
                free(proxEntrega);
                *score += 3;
            }

            free(entrega);
        }
        else
        {
            
            printf("Pedido sera devolvido, pois nao conseguimos entregar (2 tentativas) para %s.\n", entrega->pedido->cliente->nome);
            addFila(dev, entrega);  // Movendo para a fila de devolução
            *score -= 1;

            // Também devolve todas as entregas seguintes com o mesmo endereço
            while (*p != NULL && strcmp(entrega->pedido->cliente->enderecoRua, (*p)->entrega->pedido->cliente->enderecoRua) == 0)
            {
                Entrega *proxEntrega = desempilharPilha(p);
                printf("Pedido sera devolvido pois nao conseguimos entregar (2 tentativas) para %s.", proxEntrega->pedido->cliente->nome);
                addFila(dev, proxEntrega);
                *score -= 1;
            }

        }
    }
}
// void entregar(Fila *f, Pilha **p, Fila *dev, int *score)
// {
//     srand(time(NULL));
//     //agruparPorEndereco(f);

//     while (f->inicio != NULL)
//     {
//         Entrega *entrega = retirarFila(f);
//         entrega->tentativa = 1;  // Primeira tentativa

//         // Verifica se há entregas com o mesmo endereço
//         printf("Iniciando a entrega para %s.\n", entrega->pedido->cliente->nome);
//         int i = rand() % 10;
//         int sucesso = (i < 7);

//         if (sucesso)
//         {
//             printf("Entrega realizada para %s.\n", entrega->pedido->cliente->nome);
//             *score += 5;
//             // Entregar todas as entregas seguintes com o mesmo endereço
//             while (f->inicio != NULL && strcmp(entrega->pedido->cliente->enderecoRua, f->inicio->pedido->cliente->enderecoRua) == 0)
//             {
//                 Entrega *proxEntrega = retirarFila(f);
//                 proxEntrega->tentativa = 1;
//                 printf("Entrega realizada para %s.\n", proxEntrega->pedido->cliente->nome);
//                 free(entrega);
//                 free(proxEntrega);
                
//             }
            
//         }
//         else
//         {
//             printf("Entrega não efetuada, tentativa adicionada a pilha para %s.\n", entrega->pedido->cliente->nome);
//             empilharPilha(p, entrega);  // Movendo para a pilha para nova tentativa
//         }
//     }

//     // Tentar entregar os itens na pilha
//     while (*p != NULL)
//     {
//         Entrega *entrega = desempilharPilha(p);
//         entrega->tentativa = 2;  // Segunda tentativa

//         int i = rand() % 10;
//         if (i < 7) 
//         {
//             printf("Entrega efetuada na segunda tentativa para %s.\n", entrega->pedido->cliente->nome);
//             free(entrega);
//             *score += 3;
//         }
//         else
//         {
//             printf("Pedido sera devolvido pois não conseguimos entregar (2 tentativas) para %s.\n", entrega->pedido->cliente->nome);
//             addFila(dev, entrega);  // Movendo para a fila de devolução
//             *score -= 1;
//         }
//     }
// }