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
    char nomeP[50];
    int contador;
    int quantidade;
    struct pedido *prox;
} Pedido;

typedef struct Entrega {
    Cliente *cliente;
    int tentativa;
    struct Entrega *prox;
} Entrega;

typedef struct fila
{
    Entrega *inicio;
    Entrega *fim;
} Fila;

typedef struct pilha
{
    struct pilha *prox;
    Entrega *entrega;
} Pilha;


// Funções da Lista de Clientes
ListaCliente *criarLista();
void addLista(ListaCliente *l, int *id);
void mostrarLista(ListaCliente *l);
void liberarLista(ListaCliente *l);

// Funções da Pilha da segunda tentativa
Pilha *criarPilha();
void empilharPilha(Pilha **p, Entrega *entrega);
Entrega *desempilharPilha(Pilha **p);
//contar a pilha para descontar no score
void mostrarPilha(Pilha *p);
void liberarPilha(Pilha **p);

// Funções da Fila
Fila *criarFila();
void addFila(Fila *f, Entrega *entrega);
Fila *buscarFila(Fila *f); //buscar pedidos na mesma rua e ordenar caso tenha 
Entrega *retirarFila(Fila *f);
void mostarFila(Pedido *p);
void liberarFila(Fila **f);

void cadastarPedido(Pedido **p, ListaCliente *cliente);
void cadastrarCliente(Pedido **p, Cliente *cliente);
int buscarCliente(ListaCliente *l); //retornar 1 (encontrou) ou 0 (não encontrou)
void entregar(Fila *f, Pilha **p, Fila *dev);
void agruparPorEndereco(Fila *f);
// Funções da rota
//gerar números 1 até 7 pra entregar e 8 até 10 pra não entregar (adicionar o score, contador e na pilha)
//pegar a pilha e adicionar na fila de devolução

#endif // TRANSPORTADORA_H
