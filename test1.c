#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix mat1 = createMatrix(10, 10);
    Matrix mat2 = createMatrix(15, 10);
    printMatrix(mat1);
    *getElement(&mat1, 3, 3) = 4;
    printf("Change\n");
    printMatrix(mat1);
    Matrix mat3 = conHorizontally(mat1, mat2);
    printf("After conHorizonatlly %d\n", mat3.rows);
    printMatrix(mat3);



    printf("After conVertically\n");
    mat1 = createMatrix(10, 4);
    mat2 = createMatrix(10, 6);
    printf("Mat1\n");
    printMatrix(mat1);
    printf("Mat2\n");
    printMatrix(mat2);
    mat3 = conVertically(mat1, mat2);
    printf("Mat3\n");
    printMatrix(mat3);


    printf("Testing subMatrix\n");
    mat1 = createMatrix(4, 4);
    *(getElement(&mat1, 2, 2)) = -3.5;
    printMatrix(mat1);
    printf("After subMatrix\n");
    mat2 = subMatrix(mat1, 1, 2, 1, 4);
    printMatrix(mat2);


    double arr[] = {1, 2, 3, 4};
    mat1 = arr2mat(arr, arr + 4);
    mat2 = diag(arr, arr + 4);
    printf("arr2mat\n");
    printMatrix(mat1);
    printf("diag\n");
    printMatrix(mat2);


    printf("Testing sum and multiply functions:\n");
    double arr1[] = {4, 5, 6, 7, 10, 10, 10, 10};
    double arr2[] = {8, 9, 10, 11, -5, 45, 65, 80};
    mat1 = diag(arr1, arr1 + 8);
    mat2 = diag(arr2, arr2 + 8);
    printf("Sum function:\n");
    mat3 = sumMatrix(mat1, mat2);
    printMatrix(mat3);
    printf("Multiply function\n");
    mat3 = multiplyMatrix(mat1, mat2);
    printMatrix(mat3);

    printf("Testing modifyRow\n");
    mat1 = diag(arr1, arr1 + 5);
    printMatrix(mat1);
    printf("After modify\n");
    modifyRow(&mat1, 1, 5, 1);
    modifyColumn(&mat1, 1, 5, 1);
    printMatrix(mat1);
    clearAll();
}