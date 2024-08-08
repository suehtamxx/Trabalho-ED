#include "transportadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    ListaCliente *atual = listacliente->prox; 

    while (atual != NULL) {
        if (strcmp(atual->cliente->cpf, cpf) == 0) return atual->cliente;
        atual = atual->prox;
    }

    return NULL; 
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

        printf("\nInforme o CPF: ");
        fgets(novo->cliente->cpf, sizeof(novo->cliente->cpf), stdin);
        setbuf(stdin, NULL);
        
        if (buscarLista(l, novo->cliente->cpf) != NULL) {
            printf("\nCliente com CPF %s já cadastrado!\n", novo->cliente->cpf);
            free(novo->cliente);
            free(novo);
            return;
        }

        printf("\nInforme o nome: ");
        fgets(novo->cliente->nome, sizeof(novo->cliente->nome), stdin);
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
void mostarFila(Pedido *p)
{
    printf("mostrando os itens a ser entregue:\n");
    if(p == NULL) printf("Lista vazia!");
    else
    {
        Pedido *aux = p;
        while(aux != NULL)
        {
            printf("\nNome do item: %s\n", aux->nomeP);
            printf("\nQuantidade de itens: %d\n", aux->quantidade);
            //printf("\nNome do cliente: %s\n", aux->cliente->nome);
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

void cadastrarPedido(Pedido **p, ListaCliente *listacliente)
{
    if(listacliente->prox == NULL)
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
    char buscaCliente[50];
    printf("\nDigite o nome do cliente para entrega:\n");
    fgets(buscaCliente, sizeof(buscaCliente), stdin);

    buscaCliente[strcspn(buscaCliente, "\n")] = 0;
    setbuf(stdin, NULL);
    
    ListaCliente *cliente = listacliente->prox;
    while(cliente != NULL)
    {
        cliente->cliente->nome[strcspn(cliente->cliente->nome, "\n")] = 0;
        if(strcmp(cliente->cliente->nome, buscaCliente) == 0)
            break;
        cliente = cliente->prox;
    }
    if(cliente == NULL)
    {
        printf("Cliente nao encontrado!\n");
        free(novoPedido);
        return;
    }

    novoPedido->cliente = cliente->cliente;

    printf("\nDigite a quantidade de itens:\n");
    scanf("%d", &novoPedido->quantidade);
    setbuf(stdin, NULL);

    printf("\nNome do item que vai ser entregue:\n");
    fgets(novoPedido->nomeP, sizeof(novoPedido->nomeP), stdin);
    setbuf(stdin, NULL);

    novoPedido->prox = *p;
    *p = novoPedido;
    novoPedido->contador++;

    //printf("Pedido adicionado: %s, quantidade: %d, para o endereco: %s\n", novoPedido->nomeP, novoPedido->quantidade, novoPedido->cliente->enderecoRua);
}

// void agruparPorEndereco(Fila *f)
// {
//     if (f->inicio == NULL) {
//         return;
//     }

//     Fila filaaux = {NULL, NULL};
//     Entrega *entrega;

//     // Primeira passagem: mover todos os itens para filaaux
//     while ((entrega = retirarFila(f)) != NULL) {
//         addFila(&filaaux, entrega);
//     }

//     // Segunda passagem: processar filaaux e reordenar na fila original
//     while ((entrega = retirarFila(&filaaux)) != NULL) {
//         Fila grupoEndereco = {NULL, NULL};
//         addFila(&grupoEndereco, entrega);

//         Entrega *proximo;
//         while ((proximo = retirarFila(&filaaux)) != NULL) {
//             if (strcmp(entrega->cliente->enderecoRua, proximo->cliente->enderecoRua) == 0) {
//                 addFila(&grupoEndereco, proximo);
//             } else {
//                 addFila(&filaaux, proximo);
//             }
//         }

//         while ((entrega = retirarFila(&grupoEndereco)) != NULL) {
//             addFila(f, entrega);
    // if(f->inicio == NULL)
    //     return;

    // Fila filaaux;
    // filaaux.inicio = NULL;
    // filaaux.fim = NULL;

    // Entrega *entrega;

    // while((entrega = retirarFila(f)) != NULL)
    // {
    //     //agrupar com o mesmo endereço
    //     Fila grupoEndereco;
    //         grupoEndereco.inicio = NULL;
    //         grupoEndereco.fim = NULL;
    //     addFila(&grupoEndereco, entrega->cliente);

    //     Entrega *proxima;
    //     while((proxima = retirarFila(f)) != NULL){
    //         if(strcmp(entrega->cliente->enderecoRua, proxima->cliente->enderecoRua) == 0)
    //             addFila(&grupoEndereco, proxima->cliente);
    //         else 
    //             addFila(&filaaux, proxima->cliente);
    //         addFila(f, entrega->cliente);
    //     }

    //     //colocar grupos do mesmo endereço
    //     while((entrega = retirarFila(&grupoEndereco)) != NULL)
    //         addFila(f, entrega->cliente);

    //     //continuar processando a fila
    //     while((proxima = retirarFila(&filaaux)) != NULL)
    //         addFila(f, proxima->cliente);
    // }
        //}
    //}
//}


// void entregar(Fila *f, Pilha **p, Fila *dev)
// {
//     agruparPorEndereco(f);

//     while(f->inicio != NULL)
//     {
//         Entrega *entrega = retirarFila(f);
//         entrega->tentativa++;

//         if(entrega->tentativa == 1)
//         while(strcmp() == 0)
//         {
//             int i = rand() % 10;
            
//             if(i < 7) printf("Entrega realizada de primeira para %s.\n", entrega->cliente->nome);
//                 else{
//                     printf("Entrega nao efetuada, tentaremos de novo amanha\n");
//                     empilharPilha(p, entrega);
//                 }

//         } else {
//             empilharPilha(p, entrega);
//         }
//     }
//         while(*p != NULL)
//         {
//             Entrega *entrega = desempilharPilha(p);
//             int i = rand() % 10;

//             if(i < 7) printf("entrega efetuada na segunda tentativa para %s\n", entrega->cliente->nome);
//                 else{
//                     printf("Pedido sera devolvido pois nao conseguimos entregar(2 vezes) para %s\n", entrega->cliente->nome);
//                     addFila(dev, entrega);
//                 }
//             free(entrega);
//         }
// }

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


