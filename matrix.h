#ifndef MATRIX_H
#define MATRIX_H

struct Matrix{
    int columns, rows;
    double **mat;
};

typedef struct Matrix Matrix;

/*
    * Function that creates a matrix
    * arguments number of rows and columns
    * the elements are set to zero by default
*/

Matrix create_matrix(int rows, int columns);
/*
    * Function that creates a zero matrix
*/
Matrix zeros(int rows, int columns);
/*
    * This function is used to print a matrix 
    * argument is a matrix
*/
void print_matrix(Matrix* matrix);
/*
    * This function is used to free the space occupied by the Matrix object
    * This function should be used for any number of Matrix object created at the end of the program
    *
*/
void free_matrix(Matrix matrix);
/*
    * Get number of rows
*/
int getRows(Matrix *matrix);
/*
    * Get number of columns
*/
int getColmns(Matrix* matrix);
/*
    * Get elements value, using this function you cannot modify the elements value
*/
double getValue(Matrix *matrix, int row, int col); 
/*
    * Get pointer to element, using this you can modify the value
*/
double* getElement(Matrix* matrix, int row, int col);


#endif