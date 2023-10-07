#include "matrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<stdarg.h>

struct MatrixGarbageCollector{
    int cnt;
    Matrix* matrices;
} matrixGarbageCollector = {.cnt = 0, .matrices = NULL};

const double EPS = 1e-5;


void beforeExit(char* error){
    printf("\n%s\n", error);
    clearAll();
    exit(0);
}

void addNewMatrix(Matrix matrix){
    matrixGarbageCollector.matrices = (Matrix*)realloc(matrixGarbageCollector.matrices, (matrixGarbageCollector.cnt + 1) * sizeof(Matrix));
    matrixGarbageCollector.matrices[matrixGarbageCollector.cnt] = matrix;
    matrixGarbageCollector.cnt += 1;
}


Matrix createMatrix(int rows, int columns){
    if(rows <= 0 || columns <= 0){
        beforeExit("ERROR: The matrix dimensions are not valid.");
    }
    Matrix matrix = {rows, columns, (double**)malloc(sizeof(double*)*rows)};
    int i;
    for(i = 0; i < rows; i++){
        matrix.mat[i] = (double*)malloc(sizeof(double)*columns);
        int j;
        for(j = 0; j < columns; j++)
            matrix.mat[i][j] = 0.0;
    }
    addNewMatrix(matrix);
    return matrix;
}

Matrix zeros(int rows, int columns){
    return createMatrix(rows, columns);
}

Matrix ones(int n){
    Matrix matrix = createMatrix(n, n);
    int i;
    for(i = 0; i < n; i++){
        matrix.mat[i][i] = 1.;
    }
    return matrix;
}


void printMatrix(Matrix matrix){
    int i, j;
    for(i = 0; i < matrix.rows; i++) {
        for(j = 0; j < matrix.columns; j++) {
            printf("%15.4f", matrix.mat[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(Matrix matrix){
    int i;
    for(i = 0; i < matrix.rows; i++)
        free(matrix.mat[i]);
    free(matrix.mat);
}

void clearAll(){
    int i;
    for(i = 0; i < matrixGarbageCollector.cnt; i++){
        freeMatrix(matrixGarbageCollector.matrices[i]);
    }
    free(matrixGarbageCollector.matrices);
    matrixGarbageCollector.cnt = 0;
}

Matrix inputMatrix(int rows, int columns){
    Matrix matrix = createMatrix(rows, columns);
    int i, j;
    for(i = 1; i <= rows; i++){
        for(j = 1; j <= columns; j++){
            scanf("%lf", getElement(&matrix, i, j));
        }
    }
    return matrix;
}

Matrix initMatrix(int rows, int columns, ...){
    Matrix matrix = createMatrix(rows, columns);
    va_list args;
    va_start(args, columns);

    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            matrix.mat[i][j] = va_arg(args, double);;
        }
    }
    return matrix;
}

int getRows(Matrix *matrix){
    return matrix->rows;
}

int getColumns(Matrix *matrix){
    return matrix->columns;
}

double getValue(Matrix* matrix, int row, int col){
    return matrix->mat[row - 1][col - 1];
}

double* getElement(Matrix* matrix, int row, int col){
    return &(matrix->mat[row - 1][col - 1]);
}

Matrix conHorizontally(Matrix mat1, Matrix mat2){
    if(mat1.columns != mat2.columns){
        beforeExit("ERROR: The matrices are not compatible for horizontal concatenation.");
    }
    Matrix matrix = createMatrix(mat1.rows + mat2.rows, mat1.columns);
    
    pthread_t thread1, thread2;

    ConcatAndCopy con1 = {0, 0, &matrix, &mat1};
    ConcatAndCopy con2 = {mat1.rows, 0, &matrix, &mat2};

    pthread_create(&thread1, NULL, fillMatrix, (void*)(&con1));
    pthread_create(&thread2, NULL, fillMatrix, (void*)(&con2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return matrix;
}

Matrix conVertically(Matrix mat1, Matrix mat2){
    if(mat1.rows != mat2.rows){
        beforeExit("ERROR: The matrices are not compatible for vertical concatenation.");
    }    
    Matrix matrix = createMatrix(mat1.rows, mat1.columns + mat2.columns);

    pthread_t thread1, thread2;

    ConcatAndCopy con1 = {0, 0, &matrix, &mat1};
    ConcatAndCopy con2 = {0, mat1.columns, &matrix, &mat2};

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

Matrix subMatrix(Matrix matrix, int rowBegin, int rowEnd, int colBegin, int colEnd){
    if((rowBegin < 1 || rowBegin > rowEnd || rowBegin > matrix.rows) 
        || (rowEnd < 1 || rowEnd > matrix.rows)
        || (colBegin < 1 || colBegin > colEnd || colBegin > matrix.columns)
        || (colEnd < 1 || colEnd > matrix.columns)){
            beforeExit("ERROR: The parametars for subMatrix function are not valid.");
        }
    rowBegin--, rowEnd--, colBegin--, colEnd--; 
    Matrix sub = createMatrix(rowEnd - rowBegin + 1, colEnd - colBegin + 1);
    int i, j;
    for(i = rowBegin; i <= rowEnd; i++){
        for(j = colBegin; j <= colEnd; j++){
            sub.mat[i - rowBegin][j - colBegin] = matrix.mat[i][j];
        }
    } 
    return sub;
}

Matrix arr2mat(double* begin, double* end){
    Matrix matrix = createMatrix(end - begin, 1);
    double* help = begin;
    for(; help < end; help++){
        matrix.mat[help - begin][0] = *help;
    }
    return matrix;
}

Matrix diag(double* begin, double* end){
    Matrix matrix = createMatrix(end - begin, end - begin);
    double* help = begin;
    for(; help < end; help++){
        matrix.mat[help - begin][help - begin] = *help;
    }
    return matrix;
}

Matrix sumMatrix(Matrix mat1, Matrix mat2){
    if(mat1.rows != mat2.rows || mat1.columns != mat2.columns){
        beforeExit("ERROR: The matrices are not compatible for summation.");
    }
    Matrix sum = createMatrix(mat1.rows, mat1.columns);
    int i, j;
    for(i = 0; i < sum.rows; i++){
        for(j = 0; j < sum.columns; j++){
            sum.mat[i][j] = mat1.mat[i][j] + mat2.mat[i][j];
        }
    }
    return sum;
}

Matrix multiplyMatrix(Matrix mat1, Matrix mat2){
    if(mat1.columns != mat2.rows){
        beforeExit("ERROR: The matrices are not compatible for multiplication.");
    }
    Matrix product = createMatrix(mat1.rows, mat2.columns);
    int i, j, k;
    for(i = 0; i < mat1.rows; i++){
        for(j = 0; j < mat2.columns; j++){
            for(k = 0; k < mat1.rows; k++){
                product.mat[i][j] += mat1.mat[i][k] * mat2.mat[k][j];
            }
        }
    }
    return product;
}

void modifyRow(Matrix* matrix, double value, int rowDest, int rowOrig){
    int j;
    rowDest -= 1; rowOrig -= 1;
    for(j = 0; j < matrix->columns; j++){
        matrix->mat[rowDest][j] += value * matrix->mat[rowOrig][j];
    }
}

void modifyColumn(Matrix* matrix, double value, int columnDest, int columnOrig){
    int i;
    columnDest -= 1; columnOrig -= 1;
    for(i = 0; i < matrix->rows; i++){
        matrix->mat[i][columnDest] += value * matrix->mat[i][columnOrig];
    }
}

double det(Matrix matrix){
    Matrix copyMatrix = copy(&matrix);
    int i, j, sign = 1;
    for(i = 1; i <= matrix.rows;  i++){
        for(j = i + 1; j <= matrix.rows; j++){
            int k = j;
            for(k = j; k <= matrix.rows && getValue(&copyMatrix, i, i) == 0; k++){
                swapRows(&copyMatrix, i, k);
                sign *= -1;
            }
            if(k == matrix.rows + 1 && getValue(&copyMatrix, i, i) == 0)
                return 0.;
            modifyRow(&copyMatrix, -getValue(&copyMatrix, j, i)/getValue(&copyMatrix, i, i), j, i);
        }
    }

    double det = matrixTrace(copyMatrix) * sign;
    return det;
}


int singularity(Matrix matrix){
    return (abs(det(matrix)) <= EPS) ? 1:0;
}

double matrixTrace(Matrix matrix){
    double trace = 1.;
    int i;
    for(i = 0; i < matrix.rows; i++)
        trace *= matrix.mat[i][i];
    return trace;
}

void swapRows(Matrix* matrix, int row1, int row2){
    row1 -= 1; row2 -= 1;
    double* helper = matrix->mat[row1];
    matrix->mat[row1] = matrix->mat[row2];
    matrix->mat[row2] = helper;
}

void swapColumns(Matrix* matrix, int col1, int col2){
    col1 -= 1; col2 -= 1;
    int i;
    for(i = 0; i < matrix->rows; i++){
        double helper = matrix->mat[i][col1];
        matrix->mat[i][col1] = matrix->mat[i][col2];
        matrix->mat[i][col2] = helper;
    }
}

Matrix scalarMulty(Matrix matrix, double scalar){
    Matrix newMatrix = createMatrix(matrix.rows, matrix.columns);
    int i, j;
    for(i = 1; i <= newMatrix.rows; i++){
        for(j = 1; j <= newMatrix.columns; j++){
            *getElement(&newMatrix, i, j) = scalar * getValue(&matrix, i, j);
        }
    }
    return newMatrix;
}

void multiplyRow(Matrix* matrix, double value, int row){
    row--;
    int j;
    for(j = 0; j < matrix->columns; j++){
        matrix->mat[row][j] *= value;
    }
}

Matrix inv(Matrix matrix){
    Matrix I = ones(matrix.rows);
    Matrix matrixI = conVertically(matrix, I);

    int i, j;
    for(i = 1; i <= matrixI.rows;  i++){
        for(j = i + 1; j <= matrixI.rows; j++){
            int k = j;
            for(k = j; k <= matrixI.rows && getValue(&matrixI, i, i) == 0; k++){
                swapRows(&matrixI, i, k);
            }
            if(k == matrixI.rows + 1 && getValue(&matrixI, i, i) == 0) {
                beforeExit("ERROR: The matrix is singular.");
            }
            modifyRow(&matrixI, -getValue(&matrixI, j, i)/getValue(&matrixI, i, i), j, i);
        }
    }


    for(i = 0; i < matrixI.rows; i++){
        for(j = i + 1; j < matrixI.rows; j++){
            modifyRow(&matrixI, -getValue(&matrixI, matrixI.rows - j, matrixI.rows - i)/getValue(&matrixI, matrixI.rows - i, matrixI.rows - i),
            matrixI.rows - j, matrixI.rows - i);
        }
    }



    for(i = 1; i <= matrixI.rows; i++){
        multiplyRow(&matrixI, 1/getValue(&matrixI, i, i), i);
    }

    matrixI = subMatrix(matrixI, 1, matrix.rows, matrix.rows + 1, 2 * matrix.rows);
    return matrixI;
}

Matrix trans(Matrix matrix){
    Matrix trans = createMatrix(matrix.columns, matrix.rows);
    int i, j;
    for(i = 0; i < matrix.rows; i++){
        for(j = 0; j < matrix.columns; j++){
            *getElement(&trans, j + 1, i + 1) = getValue(&matrix, i + 1, j + 1);
        }
    }
    return trans;
}

Matrix square(Matrix matrix){
    return multiplyMatrix(matrix, matrix);
}

Matrix powMatrix(Matrix matrix, int degree){
    if(degree < 1){
        beforeExit("ERROR: The exponent must by number grether than 0.");
    }
    if(degree == 1){
        return copy(&matrix);
    }
    Matrix modification = ones(matrix.rows);


    Matrix result = ones(matrix.rows);
    for(; degree > 0; degree--){
        result = multiplyMatrix(result, matrix);
    }

    return result;
}

int equalsMatrix(Matrix mat1, Matrix mat2){
    if(mat1.rows != mat2.rows || mat1.columns != mat2.columns){
        return 0;
    }
    int i, j;
    for(i = 0; i < mat1.rows; i++){
        for(j = 0; j < mat1.columns; j++){
            if(mat1.mat[i][j] != mat2.mat[i][j]){
                return 0;
            }
        }
    }
    return 1;
}