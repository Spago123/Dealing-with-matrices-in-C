#include<stdio.h>
#include "matrix.h"

int main(){
    int m, n;
    printf("Type in the dimensions of your matrix: ");
    scanf("%d %d", &m, &n);
    Matrix matrix = inputMatrix(m, n);
    printMatrix(trans(&matrix));
    clearAll();
}