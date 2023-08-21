#include<stdio.h>
#include "matrix.h"

int main(){
    double arr1[] = {1, 2, 5, 0.8};
    double arr2[] = {1, 2, 11, 3.4};
    double arr3[] = {1, 2, 13, 3};
    double arr4[] = {1, 2, 3, 5};
    Matrix mat1 = arr2mat(arr1, arr1 + 4);
    Matrix mat2 = arr2mat(arr2, arr2 + 4);
    Matrix mat3 = arr2mat(arr3, arr3 + 4);
    Matrix mat4 = arr2mat(arr4, arr4 + 4);
    Matrix mat5 = conVertically(mat1, mat2);
    Matrix mat6 = conVertically(mat3, mat4);
    Matrix mat7 = conVertically(mat5, mat6);
    printMatrix(mat7);
    printf("Determinat of the matrix mat7 is : %f\n", det(mat7));
    if(singularity(mat7) == 1)
        printf("Mat7 is singular");
    else
        printf("Mat7 is regular");
    clearAll();
}