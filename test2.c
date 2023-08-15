#include<stdio.h>
#include "matrix.h"

int main(){
    double arr1[] = {1, 3, 5};
    double arr2[] = {5, 7, 11};
    double arr3[] = {2, 3, 13};
    Matrix mat1 = arr2mat(arr1, arr1 + 3);
    Matrix mat2 = arr2mat(arr2, arr2 + 3);
    Matrix mat3 = arr2mat(arr3, arr3 + 3);
    Matrix mat4 = conVertically(&mat1, &mat2);
    Matrix mat5 = conVertically(&mat4, &mat3);
    print_matrix(&mat5);
    printf("Determinat of the matrix mat5 is : %f\n", det(&mat5));
    if(singularity(&mat5) == 1)
        printf("Mat5 is singular");
    else
        printf("Mat5 is regular");
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(mat3);
    free_matrix(mat4);
    free_matrix(mat5);
}