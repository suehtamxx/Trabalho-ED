//Não esquecer de criar o score
#include "transportadora.h"
#include "transportadora.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    //Fila *fila = criarFila();
    ListaCliente listacliente;
    listacliente.prox = NULL;
    Fila *f = criarFila();
    Pilha *p = criarPilha();
    Fila *dev = criarFila();
    //Entrega *entrega = fila;

    int id = 0;

    addLista(&listacliente, &id);
    addLista(&listacliente, &id);
    addLista(&listacliente, &id);
    addLista(&listacliente, &id);
    mostrarLista(&listacliente);

    cadastrarPedido(f, &listacliente);
    cadastrarPedido(f, &listacliente);
    cadastrarPedido(f, &listacliente);
    cadastrarPedido(f, &listacliente);
    cadastrarPedido(f, &listacliente);
    mostarFila(f);

    // Entrega *atual = filapedidos;
    // while(atual != NULL)
    // {
    //     Entrega *novo = (Entrega *)malloc(sizeof(Entrega));
    //     if(novo == NULL)
    //     {
    //         printf("erro ao alocar memoria(main)");
    //         exit(1);
    //     }
    //     novo->pedido->cliente = atual->cliente;
    //     novo->tentativa = 0;
    //     novo->prox = NULL;

    //     addFila(f, novo);

    //     atual = atual->prox;
    // }


    
    //addFila(fila, &cliente1);

    entregar(f, &p, dev);
    //printf("Fila de devolucoes:\n");
    //Entrega *e;
    // while((e = retirarFila(f)) != NULL){
    //     printf("Devolucao para %s, %s\n", e->cliente->nome, e->cliente->enderecoRua);
    //     free(e);    
    // }
    liberarLista(&listacliente);
    liberarPilha(&p);
    liberarFila(&f);
    liberarFila(&dev);

    return 0;
}