#include<stdio.h>
#include "matrix.h"

int main(){
    double arr1[] = {1, 2, 3};
    double arr2[] = {3, 2, 3};
    double arr3[] = {2, 2, 4};
    Matrix mat1 = arr2mat(arr1, arr1 + 3);
    Matrix mat2 = arr2mat(arr2, arr2 + 3);
    Matrix mat3 = arr2mat(arr3, arr3 + 3);
    Matrix mat4 = conVertically(&mat1, &mat2);
    Matrix mat5 = conVertically(&mat4, &mat3);
    printMatrix(mat5);
    printf("hello\n");
    printMatrix(inv(&mat5));
    clearAll();
}