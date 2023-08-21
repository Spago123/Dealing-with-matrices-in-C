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

Matrix createMatrix(int rows, int columns);
/*
    * Function that creates a zero matrix
*/
Matrix zeros(int rows, int columns);

/*
    * Function that return an identity matrix
*/
Matrix ones(int n);

/*
    * This function is used to print a matrix 
    * argument is a matrix
*/
void printMatrix(Matrix matrix);
/*
    * This function is used to print a matrix 
    * argument is a pointer to matrix
*/
void printMatrixPtr(Matrix* matrix);
/*
    * This function is used to free the space occupied by the Matrix object
    * This function should be used for any number of Matrix object created at the end of the program
*/
void freeMatrix(Matrix matrix);

/*
    * Function that will erase every instance of the Matrix object ever created in the program
*/
void clearAll();

/*
    * Function used to type in a matrix from standard user input
*/
Matrix inputMatrix(int rows, int columns);
/*
    * Get number of rows
*/
int getRows(Matrix *matrix);

/*
    * Get number of columns
*/
int getColumns(Matrix* matrix);
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
Matrix conHorizontally(Matrix mat1, Matrix mat2);
/*
    * Function that conctats two matrices vertically
    * number of rows must be the same for both matrices
*/
Matrix conVertically(Matrix mat1, Matrix mat2);

/*
    * Function that makes a deep copy of a matrix
*/
Matrix copy(Matrix* matrix);

/*
    * Function that makes a submatrix of a matrix
*/

Matrix subMatrix(Matrix matrix, int horBegin, int verBegin, int horEnd, int verEnd);

/*
    * Function that makes a vector out of an array
*/
Matrix arr2mat(double* begin, double* end);

/*
    * Function that generates a diagobal matrix with elements on the diagonal that 
    * are equal to the element of the array
*/
Matrix diag(double* begin, double* end);

/*
    * Function that sums two matrices   
*/
Matrix sumMatrix(Matrix mat1, Matrix mat2);

/*
    * Function that multiplies two matrices
*/
Matrix multiplyMatrix(Matrix mat1, Matrix mat2);

/*
    * Function that returns the determinant of a matrix
*/
double det(Matrix matrix);

/*
    * Function that returns if a matrix is singular or not
    * return 1 for singular matrix, 0 for regular matrix
*/
int singularity(Matrix matrix);

/*
    * Function that return the inverse of a matrix
*/
Matrix inv(Matrix matrix);

/*
    * Function to modify a rows value
*/
void modifyRow(Matrix* matrix, double value, int rowDest, int rowOrig);

/*
    * Function to modify a columns value
*/
void modifyColumn(Matrix* matrix, double value, int columnDest, int columnOrig);

/*
    * Function that calculates the product of the element on the main diagonal
*/
double matrixTrace(Matrix matrix);

/*
    * Function that swaps two rows of a matrix
*/
void swapRows(Matrix* matrix, int row1, int row2);

/*
    * Funtion that swaps two columns of a matrix
*/
void swapColumns(Matrix* matrix, int col1, int col2);

/*
    * Function that multiplies each element of a matrix with a scalar
*/
Matrix scalarMulty(Matrix matrix, double scalar);

/*
    * Function that transposes a matrix
*/
Matrix trans(Matrix matrix);


#endif