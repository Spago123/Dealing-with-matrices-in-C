#include<stdio.h>
#include "matrix.h"

int main(){
    int n;
    printf("Type in the dimensions of the square matrix: ");
    scanf("%d", &n);
    Matrix matrix = inputMatrix(n, n);
    printf("Inversion of your matrix is:\n");
    printMatrix(inv(&matrix));
    clearAll();
}