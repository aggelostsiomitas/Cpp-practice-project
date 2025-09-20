#include "../inc/Matrix.hpp"

// Δημιουργία πίνακα (rows x cols)
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Invalid input for matrix");
    }
    data = new double[rows * cols](); // allocate + zero init
}

// Δημιουργία του 1D πίνακα
Matrix::Matrix(const double* arr, int size, bool isrows) {
    if (size <= 0) throw std::invalid_argument("Invalid array size");

    if (isrows) {
        rows = 1;
        cols = size;
    } else {
        rows = size;
        cols = 1;
    }

    data = new double[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[index(i, j)] = arr[isrows ? j : i];
        }
    }
}

// Δημιουργία 2D πίνακα με χρήση constructor
Matrix::Matrix(double** arr, int r, int c) : rows(r), cols(c) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Empty matrix");
    }
    data = new double[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[index(i, j)] = arr[i][j];
        }
    }
}

// Destructor
Matrix::~Matrix() {
    delete[] data;
}

// Copy constructor (deep copy)
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new double[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
        data[i] = other.data[i];
    }
}

// Copy assignment
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        delete[] data; // free old memory
        rows = other.rows;
        cols = other.cols;
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Move constructor
Matrix::Matrix(Matrix&& other) noexcept 
    : rows(other.rows), cols(other.cols), data(other.data) {
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
}

// Move assignment
Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        delete[] data;
        rows = other.rows;
        cols = other.cols;
        data = other.data;
        other.data = nullptr;
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

// --- Operators ---
// Υλοποίηση της πρόσθεσης πινάκων
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions must agree");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

Matrix Matrix::operator+(Matrix&& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions must agree");
    }
    for (int i = 0; i < rows * cols; i++) {
        other.data[i] += data[i];
    }
    return std::move(other);
}

// Υλοποίηση της αφαίρεσης πινάκων
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions must agree");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

Matrix Matrix::operator-(Matrix&& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions must agree");
    }
    for (int i = 0; i < rows * cols; i++) {
        other.data[i] = data[i] - other.data[i];
    }
    return std::move(other);
}

// Υλοποίηση του γινομένου πινάκων
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Invalid dimensions for multiplication");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols; k++) {
                sum += data[index(i, k)] * other.data[other.index(k, j)];
            }
            result.data[result.index(i, j)] = sum;
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions must agree");
    }
    for (int i = 0; i < rows * cols; i++) {
        data[i] += other.data[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions must agree");
    }
    for (int i = 0; i < rows * cols; i++) {
        data[i] -= other.data[i];
    }
    return *this;
}

// Υλοποίηση υπερφόρτωσης για ανάγνωση στοιχείων του πίνακα
double Matrix::operator()(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return data[index(row, col)];
}

// Υλοποίηση υπερφόρτωσης για πρόσβαση σε στοιχείο του πίνακα
double& Matrix::operator()(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return data[index(row, col)];
}

// Εκτύπωση πίνακα
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            os << matrix.data[matrix.index(i, j)] << " ";
        }
        os << std::endl;
    }
    return os;
}
