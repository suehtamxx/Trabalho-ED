#include <stdio.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Função de ordenação Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    // Um por um, move o limite da submatriz não ordenada
    for (i = 0; i < n-1; i++) {
        // Encontra o menor elemento na submatriz não ordenada
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Troca o menor elemento encontrado com o primeiro elemento
        swap(&arr[min_idx], &arr[i]);
    }
}

// Função para imprimir um array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Função principal
int main() {
    int arr[] = {10, 7, 55, 30, 1, 2, 1, 90, 20, 8};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Array original:\n");
    printArray(arr, n);
    selectionSort(arr, n);
    printf("Array ordenado:\n");
    printArray(arr, n);
    return 0;
}