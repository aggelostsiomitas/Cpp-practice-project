#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows, cols;
    double* data; // raw pointer for storing matrix data

    int index(int row, int col) const { 
        return row * cols + col; 
    }

public:
    // --- Constructors ---
    Matrix(int rows, int cols); 
    Matrix(const double* arr, int size, bool isRows);   // from 1D array
    Matrix(double** arr, int r, int c);                 // from 2D array

    // --- Destructor ---
    ~Matrix();

    // --- Copy constructor & assignment ---
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    // --- Move constructor & assignment ---
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;

    // --- Operators ---
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    Matrix operator+(Matrix&& other) const;
    Matrix operator-(Matrix&& other) const;

    double operator()(int row, int col) const;
    double& operator()(int row, int col);

    // --- Getters ---
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // --- Friend for printing ---
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};
#endif