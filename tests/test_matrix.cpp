#include "../inc/Matrix.hpp"
#include <cassert>
#include <iostream>

void test_addition() {
    Matrix A({{1, 2}, {3, 4}});
    Matrix B({{5, 6}, {7, 8}});
    Matrix C = A + B;
    assert(C.getRows() == 2 && C.getCols() == 2);
    assert(C(0, 0) == 6);
    assert(C(1, 1) == 12);
}

void test_subtraction() {
    Matrix A({{5, 5}, {5, 5}});
    Matrix B({{2, 1}, {3, 4}});
    Matrix C = A - B;
    assert(C(0, 0) == 3);
    assert(C(1, 1) == 1);
}

void test_multiplication() {
    Matrix A({{1, 2}, {3, 4}});
    Matrix B({{2, 0}, {1, 2}});
    Matrix C = A * B;
    assert(C.getRows() == 2 && C.getCols() == 2);
    assert(C(0, 0) == 4);  // 1×2 + 2×1
    assert(C(1, 1) == 8);  // 3×0 + 4×2
}

int main() {
    test_addition();
    test_subtraction();
    test_multiplication();
    std::cout << "All tests passed " << std::endl;
    return 0;
}
