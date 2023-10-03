#include"matrix.h"
#include<stdio.h>

int main(){
    Matrix matrix = initMatrix(2, 2, 1, 2, 3, 4);
    printMatrix(matrix);
    clearAll();
    return 0;
}

