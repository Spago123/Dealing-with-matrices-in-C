#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix mat = create_matrix(3, 3);
    print_matrix(&mat);
    *getElement(&mat, 3, 3) = 4;
    printf("Change\n");
    print_matrix(&mat);
    free_matrix(mat);
}