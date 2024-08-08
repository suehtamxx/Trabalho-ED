#include <stdio.h>
#include <stdlib.h>

void bubble(int vet[], int n)
{
    int aux = 0;
    int contador = 0;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(vet[j] < vet[i])
            {
                aux = vet[j];
                vet[j] = vet[i];
                vet[i] = aux;
            }
        }
        contador++;
    }
    printf("contador: %d\n", contador);
}

int main()
{
    int n = 10;
    int vet[] = {10, 5, 21, 19, 25, 13, 90, 55, 31, 1};
    bubble(vet, n);
    
    for(int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
}