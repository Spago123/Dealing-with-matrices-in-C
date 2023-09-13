#include "matrix.h"

int main(){
    Matrix matrix = initMatrix(2, 3, (double[2][3]){{1.0, 7.0, 4.0}, {2.0, 3.0, 2.9}});
    printMatrix(matrix);
    clearAll();
    return 0;
}
