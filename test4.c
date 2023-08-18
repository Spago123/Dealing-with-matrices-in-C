#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix matrix = ones(3);
    Matrix newMatrix = scalarMulty(&matrix, 3);
    printMatrixPtr(&newMatrix);
    clearAll();
}