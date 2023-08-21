#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix mat1 = ones(3);
    double arr[] = {1, 2, 3};
    Matrix mat2 = diag(arr, arr + 3);
    printMatrix(conHorizontally(mat1, mat2));
    printMatrix(sumMatrix(mat1, mat2));
    clearAll();
}