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
    novo->cliente->nome[strcspn(novo->cliente->nome, "\n")] = '\0'; //remove o \n

    printf("\nInforme a rua em que reside: ");
    fgets(novo->cliente->enderecoRua, sizeof(novo->cliente->enderecoRua), stdin);
    
    
    printf("\nInforme o numero da casa: ");
    scanf("%d", &novo->cliente->numCasa);
    getchar();

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
    printf("\nMostrando os Clientes:\n ");
    if (l == NULL || l->prox == NULL) printf("Lista vazia ");
    else
    {
        ListaCliente *aux = l->prox;
        while (aux != NULL)
        {
            printf("\nCliente ID %d\n", aux->id);
            printf("Nome: %s", aux->cliente->nome);
            printf("CPF: %s\n", aux->cliente->cpf);
            printf("Rua: %s", aux->cliente->enderecoRua);
            printf("Numero: %d\n", aux->cliente->numCasa);
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
    entrega->prox = NULL;

    if(f->inicio == NULL)
    {
        f->inicio = entrega;
        f->fim = entrega;
    } else {
        f->fim->prox = entrega;
        f->fim = entrega;
    }
}
Entrega *retirarFila(Fila *f)
{
    if(f->inicio == NULL)
        return NULL;

    Entrega *remover = f->inicio;
    f->inicio = f->inicio->prox;

    if(f->inicio == NULL)
        f->fim = NULL;

    return remover;

}
void mostarFila(Fila *f)
{
    if(f->inicio == NULL) printf("Fila vazia!\n");
    else
    {
        printf("Mostrando os itens a ser entregues:\n");
        Entrega *aux = f->inicio;
        while(aux != NULL)
        {
            printf("\nNome do cliente: %s", aux->pedido->cliente->nome);
            printf("Nome do item: %s\n", aux->pedido->nomeP);
            printf("Quantidade de itens: %d\n", aux->pedido->quantidade);
            printf("Endereco: %sNum: %d\n", aux->pedido->cliente->enderecoRua, aux->pedido->cliente->numCasa);
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
    

    printf("\nNome do item que vai ser entregue:\n");
    fgets(novoPedido->nomeP, sizeof(novoPedido->nomeP), stdin);
    novoPedido->nomeP[strcspn(novoPedido->nomeP, "\n")] = 0;
    getchar();

    // novoPedido->prox = *p;
    // *p = novoPedido;

    agruparPorEndereco(f, novoPedido);

    printf("Pedido adicionado: %s, quantidade: %d, para o endereco: %s\n", novoPedido->nomeP, novoPedido->quantidade, novoPedido->cliente->enderecoRua);
}

// void agruparPorEndereco(Fila *f, Pedido *novoPedido)
// {
//     if (f->inicio == NULL) 
//     {
//         Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
//         if (novaEntrega == NULL) {
//             printf("Erro ao alocar memória para nova entrega!\n");
//             exit(1);
//         }
//         novaEntrega->pedido = novoPedido;
//         novaEntrega->tentativa = 0;
//         novaEntrega->prox = NULL;
//         addFila(f, novaEntrega);
//         return;
//     }
    
//     int novaEntregaAdicionada = 0;

//     Fila *filaAux = criarFila();
//     Entrega *entrega;

//     Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
//     if (novaEntrega == NULL) {
//         printf("Erro ao alocar memória para nova entrega!\n");
//         exit(1);
//     }

//     novaEntrega->pedido = novoPedido;
//     novaEntrega->tentativa = 0;
//     novaEntrega->prox = NULL;

//     while ((entrega = retirarFila(f)) != NULL) 
//     {
//         if (strcmp(novoPedido->cliente->enderecoRua, entrega->pedido->cliente->enderecoRua) == 0) 
//         {
//             addFila(filaAux, novaEntrega);
//             novaEntregaAdicionada = 1;
//         }
//         addFila(filaAux, entrega);        
//     }

//     if(!novaEntregaAdicionada) addFila(filaAux, novaEntrega);
    
//     while ((entrega = retirarFila(filaAux)) != NULL)
//         addFila(f, entrega);
// }

void agruparPorEndereco(Fila *f, Pedido *novoPedido)
{
    Entrega *novaEntrega = (Entrega *)malloc(sizeof(Entrega));
    if (novaEntrega == NULL) {
        printf("Erro ao alocar memória para nova entrega!\n");
        exit(1);
    }
    novaEntrega->pedido = novoPedido;
    novaEntrega->tentativa = 0;
    novaEntrega->prox = NULL;

    Fila *filaAux = criarFila();
    Entrega *entrega;
    int novaEntregaAdicionada = 0;

    while (f->inicio != NULL) 
    {
        entrega = retirarFila(f);

        if (!novaEntregaAdicionada && strcmp(novoPedido->cliente->enderecoRua, entrega->pedido->cliente->enderecoRua) == 0) 
        {
            addFila(filaAux, novaEntrega);
            novaEntregaAdicionada = 1;
        }

        addFila(filaAux, entrega);
    }

    if (!novaEntregaAdicionada)
        addFila(filaAux, novaEntrega);

    while ((entrega = retirarFila(filaAux)) != NULL)
        addFila(f, entrega);

    liberarFila(&filaAux); // Libera a memória usada pela fila auxiliar
}

void entregar(Fila *f, Pilha **p, Fila *dev, int *score)
{
    srand(time(NULL));

    while (f->inicio != NULL)
    {
        // Retira o primeiro pedido da fila
        Entrega *entrega = retirarFila(f);
        entrega->tentativa = 1;  // Primeira tentativa

        // Verifica o sucesso da entrega
        printf("Iniciando a entrega para %s.\n", entrega->pedido->cliente->nome);
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
                printf("Entrega realizada para %s.\n", proxEntrega->pedido->cliente->nome);
                free(proxEntrega);
                *score += 5;
            }

            free(entrega);
        }
        else
        {
            printf("Entrega nao efetuada, pedido adicionado a pilha para %s.\n", entrega->pedido->cliente->nome);
            empilharPilha(p, entrega);  // Movendo para a pilha para nova tentativa

            // Também empilha todas as entregas seguintes com o mesmo endereço
            Entrega *proxEntrega;
            while (f->inicio != NULL && strcmp(entrega->pedido->cliente->enderecoRua, f->inicio->pedido->cliente->enderecoRua) == 0)
            {
                proxEntrega = retirarFila(f);
                proxEntrega->tentativa = 1;
                printf("Entrega nao efetuada, pedido adicionado a pilha para %s.\n", proxEntrega->pedido->cliente->nome);
                empilharPilha(p, proxEntrega);
            }
            
            free(entrega);
        }
    }

    // Tentar entregar os itens na pilha
    while (*p != NULL)
    {
        Entrega *entrega = desempilharPilha(p);
        entrega->tentativa = 2;  // Segunda tentativa

        // Verifica o sucesso da segunda tentativa
        printf("Iniciando a entrega na segunda tentativa para %s.\n", entrega->pedido->cliente->nome);
        int i = rand() % 2;
        int sucesso = (i == 1);

        if (sucesso)
        {
            printf("Entrega efetuada na segunda tentativa para %s.\n", entrega->pedido->cliente->nome);
            *score += 3;

            // Entregar todas as entregas seguintes com o mesmo endereço
            Entrega *proxEntrega;
            while (*p != NULL && strcmp(entrega->pedido->cliente->enderecoRua, (*p)->entrega->pedido->cliente->enderecoRua) == 0)
            {
                proxEntrega = desempilharPilha(p);
                proxEntrega->tentativa = 2;
                printf("Entrega efetuada na segunda tentativa para %s.\n", proxEntrega->pedido->cliente->nome);
                free(proxEntrega);
                free(entrega);
                *score += 3;
            }

        }
        else
        {
            
            printf("Pedido sera devolvido pois nao conseguimos entregar (2 tentativas) para %s.", entrega->pedido->cliente->nome);
            addFila(dev, entrega);  // Movendo para a fila de devolução
            *score -= 1;

            // Também devolve todas as entregas seguintes com o mesmo endereço
            Entrega *proxEntrega;
            while (*p != NULL && strcmp(entrega->pedido->cliente->enderecoRua, (*p)->entrega->pedido->cliente->enderecoRua) == 0)
            {
                proxEntrega = desempilharPilha(p);
                printf("Pedido sera devolvido pois nao conseguimos entregar (2 tentativas) para %s.", proxEntrega->pedido->cliente->nome);
                addFila(dev, proxEntrega);
                *score -= 1;
            }

            free(entrega);
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