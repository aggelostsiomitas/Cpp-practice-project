#include "../inc/Matrix.hpp"
#include <iostream>

int main() {
    // --- 1D arrays as row and column ---
    double rowArr[3] = {1, 2, 3};
    double colArr[2] = {4, 5};

    Matrix rowMatrix(rowArr, 3, true);   // 1x3
    Matrix colMatrix(colArr, 2, false);  // 2x1

    // --- 2D arrays ---
    double mat2D[2][2] = {{1, 2}, {3, 4}};
    double* ptrMat2D[2] = { mat2D[0], mat2D[1] };
    Matrix M1(ptrMat2D, 2, 2);
    Matrix M2(ptrMat2D, 2, 2);

    // --- Empty 2x2 matrix ---
    Matrix emptyMat(2, 2);

    // --- Printing ---
    std::cout << "rowMatrix (1x3):\n" << rowMatrix;
    std::cout << "colMatrix (2x1):\n" << colMatrix;
    std::cout << "M1 (2x2):\n" << M1;
    std::cout << "M2 (2x2):\n" << M2;
    std::cout << "emptyMat (2x2):\n" << emptyMat;

    // --- Operations ---
    Matrix sum = M1 + M2;
    Matrix difference = M1 - M2;
    Matrix multiply = M1 * M2;

    std::cout << "\nM1 + M2:\n" << sum;
    std::cout << "\nM1 - M2:\n" << difference;
    std::cout << "\nM1 * M2:\n" << multiply;

    M1 += M2;
    std::cout << "\nM1 += M2:\n" << M1;

    M1 -= M2;
    std::cout << "\nM1 -= M2:\n" << M1;

    // --- More 2D arrays ---
    double A_arr[2][2] = {{1, 2}, {3, 4}};
    double B_arr[2][2] = {{5, 6}, {7, 8}};
    double* ptrA[2] = { A_arr[0], A_arr[1] };
    double* ptrB[2] = { B_arr[0], B_arr[1] };

    Matrix A(ptrA, 2, 2);
    Matrix B(ptrB, 2, 2);
    Matrix sum2 = A + B;

    std::cout << "A:\n" << A;
    std::cout << "B:\n" << B;
    std::cout << "A + B:\n" << sum2;

    double movedArr[2][2] = {{9, 8}, {7, 6}};
    double* ptrMoved[2] = { movedArr[0], movedArr[1] };
    Matrix movedMatrix = A + Matrix(ptrMoved, 2, 2);

    std::cout << "\nA + other matrix:\n" << movedMatrix;

    Matrix C = std::move(movedMatrix);
    std::cout << "\nC after move:\n" << C;

    return 0;
}
