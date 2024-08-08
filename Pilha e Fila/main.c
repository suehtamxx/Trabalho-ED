//Não esquecer de criar o score
#include "transportadora.h"
#include "transportadora.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    //Fila *fila = criarFila();
    Pedido *filapedidos = NULL;
    ListaCliente listacliente;
    listacliente.prox = NULL;
    Fila *f = criarFila();
    Pilha *p = criarPilha();
    Fila *dev = criarFila();
    //Entrega *entrega = fila;
    //Cliente cliente1 = {"Joao Silva", "12345678901", "Rua A", 123};
    //Cliente cliente2 = {"Maria Oliveira", "09876543210", "Rua B", 456};
    int id = 0;

    addLista(&listacliente, &id);
    addLista(&listacliente, &id);
    //addLista(&listacliente, &id);
    //addLista(&listacliente, &id);
    //mostrarLista(listaCliente);
    cadastrarPedido(&filapedidos, &listacliente);
    cadastrarPedido(&filapedidos, &listacliente);
    //cadastrarPedido(&filapedidos, &listacliente);
    //cadastrarPedido(&filapedidos, &listacliente);
    mostarFila(filapedidos);

    Pedido *atual = filapedidos;
    while(atual != NULL)
    {
        Entrega *novo = (Entrega *)malloc(sizeof(Entrega));
        if(novo == NULL)
        {
            printf("erro ao alocar memoria(main)");
            exit(1);
        }
        novo->pedido->cliente = atual->cliente;
        novo->tentativa = 0;
        novo->prox = NULL;

        addFila(f, novo);

        atual = atual->prox;
    }


    
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