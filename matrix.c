#include "matrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

Matrix create_matrix(int rows, int columns){
    Matrix matrix = {rows, columns, (double**)malloc(sizeof(double*)*rows)};
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

Matrix conHorizontally(Matrix* mat1, Matrix* mat2){
    Matrix matrix = create_matrix(mat1->rows + mat2->rows, mat1->columns);
    
    pthread_t thread1, thread2;

    ConcatAndCopy con1 = {0, 0, &matrix, mat1};
    ConcatAndCopy con2 = {mat1->rows, 0, &matrix, mat2};

    pthread_create(&thread1, NULL, fillMatrix, (void*)(&con1));
    pthread_create(&thread2, NULL, fillMatrix, (void*)(&con2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return matrix;
}

Matrix conVertically(Matrix* mat1, Matrix* mat2){
    Matrix matrix = create_matrix(mat1->rows, mat1->columns + mat2->columns);

    pthread_t thread1, thread2;

    ConcatAndCopy con1 = {0, 0, &matrix, mat1};
    ConcatAndCopy con2 = {0, mat1->columns, &matrix, mat2};

    pthread_create(&thread1, NULL, fillMatrix, (void*)(&con1));
    pthread_create(&thread2, NULL, fillMatrix, (void*)(&con2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return matrix;    
}

Matrix copy(Matrix* matrix){
    Matrix copy = {matrix->rows, matrix->columns, (double**)malloc(sizeof(double*) * matrix->rows)};
    int i, j;
    for(i = 0; i < copy.rows; i++){
        copy.mat[i] = (double*)malloc(sizeof(double) * copy.columns);
        for(j = 0; j < copy.columns; j++){
            copy.mat[i][j] = matrix->mat[i][j];
        }
    }
    return copy;
}

void* fillMatrix(void* concatAndCopy){
    ConcatAndCopy* object = (ConcatAndCopy*)concatAndCopy;
    int i, j;
    for(i = object->startHorizontally; i < object->startHorizontally + object->origin->rows; i++){
        for(j = object->startVertically; j < object->startVertically + object->origin->columns; j++){
            object->dest->mat[i][j] = object->origin->mat[i-object->startHorizontally][j-object->startVertically];
        }
    }
}

