#include<stdio.h>
#include "matrix.h"

int main(){
    int rows, columns;
    printf("Type in the dimensions of the matrix: ");
    scanf("%d %d", &rows, &columns);
    printf("Type in the elements of the matrix:\n");
    Matrix matrix = inputMatrix(rows, columns);
    printf("You've typed in the following matrix\n");
    print_matrix(&matrix);
    printf("The determinant of your matrix is: %g", det(&matrix));
    free_matrix(matrix);
}