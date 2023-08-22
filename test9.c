#include<stdio.h>
#include "matrix.h"

int main(){
    int m, n;
    printf("Type in matrix1 dimensions: ");
    scanf("%d %d", &m, &n);
    Matrix matrix1 = inputMatrix(m, n);

    printf("\nType in matrix2 dimensions: ");
    scanf("%d %d", &m, &n);
    Matrix matrix2 = inputMatrix(m, n);

    printf("\nmatrix1 + matrix2 = \n");
    printMatrix(sumMatrix(matrix1, matrix2));

    printf("\nmatrix1 x matrix2 = \n");
    printMatrix(multiplyMatrix(matrix1, matrix2));
    clearAll();
}