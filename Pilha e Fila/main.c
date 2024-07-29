//Não esquecer de criar o score
#include "transportadora.h"
#include "transportadora.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    int id = 0;
    ListaCliente *listaCliente = criarLista();

    addLista(listaCliente, &id);
    addLista(listaCliente, &id);
    mostrarLista(listaCliente);
    liberarLista(listaCliente);

    return 0;
}