#ifndef TRANSPORTADORA_H
#define TRANSPORTADORA_H

typedef struct cliente
{
    char nome[50];
    char cpf[14];
    char enderecoRua[50];
    int numCasa;
} Cliente;

typedef struct listacliente
{
    Cliente *cliente;
    int id;
    struct listacliente *prox;
} ListaCliente;

typedef struct pedido
{
    Cliente *cliente;
    int contador;
    int quantidade;
    struct pedido *prox;
} Pedido;

typedef struct fila
{
    struct pedido *inicio;
    struct pedido *fim;
} Fila;

typedef struct pilha
{
    Pedido *pedido;
    struct pilha *prox;
} Pilha;

// Funções da Lista de Clientes
ListaCliente *criarLista();
void addLista(ListaCliente *l, int *id);
void mostrarLista(ListaCliente *l);
void liberarLista(ListaCliente *l);

// Funções da Pilha da segunda tentativa
Pilha *criarPilha();
Pilha *empilharPilha(Pilha *p);
Pilha *desempilharPilha(Pilha *p);
//contar a pilha para descontar no score
void mostrarPilha(Pilha *p);
void liberarPilha(Pilha *p);

// Funções da Fila
Fila *criarFila();
Fila *addFila(Fila *f, Pedido *pedido);
Fila *buscarFila(Fila *f); //buscar pedidos na mesma rua e ordenar caso tenha 
void *retirarFila(Fila *f);
void mostarFila(Fila *f);
void liberarFila(Fila *f);

void cadastarPedido();
void cadastrarCliente();
int buscarCliente(ListaCliente *l); //retornar 1 (encontrou) ou 0 (não encontrou)

// Funções da rota
//gerar números 1 até 7 pra entregar e 8 até 10 pra não entregar (adicionar o score, contador e na pilha)
//pegar a pilha e adicionar na fila de devolução

#endif // TRANSPORTADORA_H
