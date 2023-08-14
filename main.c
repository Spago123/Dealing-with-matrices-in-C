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
    printf("Mat3\n");
    print_matrix(&mat3);
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(mat3);


    printf("Testing subMatrix\n");
    mat1 = create_matrix(4, 4);
    *(getElement(&mat1, 2, 2)) = -3.5;
    print_matrix(&mat1);
    printf("After subMatrix\n");
    mat2 = subMatrix(&mat1, 1, 2, 1, 4);
    print_matrix(&mat2);
    free_matrix(mat1);
    free_matrix(mat2);

    double arr[] = {1, 2, 3, 4};
    mat1 = arr2mat(arr, arr + 4);
    mat2 = diag(arr, arr + 4);
    printf("arr2mat\n");
    print_matrix(&mat1);
    printf("diag\n");
    print_matrix(&mat2);
    free_matrix(mat1);
    free_matrix(mat2);

    printf("Testing sum and multiply functions:\n");
    double arr1[] = {4, 5, 6, 7, 10, 10, 10, 10};
    double arr2[] = {8, 9, 10, 11, -5, 45, 65, 80};
    mat1 = diag(arr1, arr1 + 8);
    mat2 = diag(arr2, arr2 + 8);
    printf("Sum function:\n");
    mat3 = sumMatrix(&mat1, &mat2);
    print_matrix(&mat3);
    free_matrix(mat3);
    printf("Multiply function\n");
    mat3 = multiplyMatrix(&mat1, &mat2);
    print_matrix(&mat3);
    free_matrix(mat3);
}