#ifndef MATRIX_H
#define MATRIX_H

struct Matrix{
    int rows, columns;
    double **mat;
};

typedef struct Matrix Matrix;

struct ConcatAndCopy{
    int startHorizontally, startVertically;
    Matrix* dest;
    Matrix* origin;
};

typedef struct ConcatAndCopy ConcatAndCopy;

void* fillMatrix(void* concatAndCopy);

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
/*
    * Function that concats two matrices horizontally
    * number of columns must be the same for both matrices
*/
Matrix conHorizontally(Matrix* mat1, Matrix* mat2);
/*
    * Function that conctats two matrices vertically
    * number of rows must be the same for both matrices
*/
Matrix conVertically(Matrix* mat1, Matrix* mat2);

/*
    * Function that makes a deep copy of a matrix
*/
Matrix copy(Matrix* matrix);




#endif