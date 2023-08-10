#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix mat1 = create_matrix(10, 10);
    Matrix mat2 = create_matrix(15, 10);
    print_matrix(&mat1);
    *getElement(&mat1, 3, 3) = 4;
    printf("Change\n");
    print_matrix(&mat1);
    //printf("%d %d %d %d", mat1.rows, mat1.columns, mat2.rows, mat2.columns);
    Matrix mat3 = conHorizontally(&mat1, &mat2);
    printf("After conHorizonatlly %d\n", mat3.rows);
    //print_matrix(&mat2);
    print_matrix(&mat3);
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(mat3);


    printf("After conVertically\n");
    mat1 = create_matrix(10, 4);
    mat2 = create_matrix(10, 6);
    printf("Mat1\n");
    print_matrix(&mat1);
    printf("Mat2\n");
    print_matrix(&mat2);
    mat3 = conVertically(&mat1, &mat2);
    printf("Mat6\n");
    print_matrix(&mat3);
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(mat3);
}