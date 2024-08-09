//Não esquecer de criar o score
#include "transportadora.h"
#include "transportadora.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main ()
{
    srand(time(NULL));

    ListaCliente listacliente;
    listacliente.prox = NULL;
    Fila *f = criarFila();
    Pilha *p = criarPilha();
    Fila *dev = criarFila();

    int id = 0;
    int score = 0;
    int op = 0;
    do{
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Cliente\n2 - Adicionar pedido\n3 - Mostrar Pedidos\n4 - Mostrar Clientes\n5 - Realizar Entrega\n6 - Mostrar Fila de devolucao\n7 - Score da trasnportadora\n0 - Sair\n");
        scanf(" %d", &op);
        getchar();

                switch (op)
                {
                case 1:
                    addLista(&listacliente, &id);
                    break;
                case 2:
                    printf("Adicionando um pedido\n");
                    cadastrarPedido(f, &listacliente);
                    break;
                case 3:
                    mostarFila(f);
                    break;
                case 4:
                    mostrarLista(&listacliente);
                    break;
                case 5:
                    entregar(f, &p, dev, &score);
                    break;
                case 6:
                    mostarFila(dev);
                    break;
                case 7:
                    printf("Score atual: %d\n", score);
                    break;
                case 0:
                    printf("\nSaindo...\n");
                    break;
                default:
                    break;
                }
    }while(op != 0);

    liberarLista(&listacliente);
    liberarPilha(&p);
    liberarFila(&f);
    liberarFila(&dev);

    return 0;
}