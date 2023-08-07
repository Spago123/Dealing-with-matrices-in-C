#include "matrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

Matrix create_matrix(int rows, int columns){
    Matrix matrix = {rows, columns, (double**)malloc(sizeof(double*)*columns)};
    int i;
    for(i = 0; i < rows; i++){
        matrix.mat[i] = (double*)malloc(sizeof(double)*columns);
        int j;
        for(j = 0; j < columns; j++)
            matrix.mat[i][j] = 0.0;
    }
    return matrix;
}

Matrix zeros(int rows, int columns){
    return create_matrix(rows, columns);
}

void print_matrix(Matrix* matrix){
    int i, j;
    for(i = 0; i < (*matrix).rows; i++) {
        for(j = 0; j < (*matrix).columns; j++) {
            printf("%15.6f", (*matrix).mat[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(Matrix matrix){
    int i;
    for(i = 0; i < matrix.rows; i++)
        free(matrix.mat[i]);
    free(matrix.mat);
}

int getRows(Matrix *matrix){
    return (*matrix).rows;
}

int getColumns(Matrix *matrix){
    return (*matrix).columns;
}

double getValue(Matrix* matrix, int row, int col){
    return (*matrix).mat[row - 1][col - 1];
}

double* getElement(Matrix* matrix, int row, int col){
    return &((*matrix).mat[row - 1][col - 1]);
}



