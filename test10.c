#include<stdio.h>
#include "matrix.h"

int main(){
    int n, degree;
    printf("Type in the dimensions of the square matrix: ");
    scanf("%d", &n);
    Matrix matrix = inputMatrix(n, n);
    printf("Type in the degree: ");
    scanf("%d", &degree);
    printMatrix(powMatrix(matrix, degree));
    clearAll();
}