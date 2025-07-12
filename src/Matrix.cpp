#include "../inc/Matrix.hpp"

//Δημιουργια πινακα
Matrix::Matrix(int rows,int cols):rows(rows),cols(cols),data(rows*cols,0.0){
    //έλεγχος για ακυρη εισοδος rows,cols
    if(rows<=0 ||cols<=0){
        throw std::invalid_argument("Invalid input for matrix");
    }
}


//Δημιουργια του 1D πινακα 
Matrix::Matrix(const std::vector<double>&arr,bool isrows){
    //αν ειναι διανυσμα γραμμη 
   if(isrows){
    rows=1;
    cols=arr.size();
   }
   //αλλιως θα ειναι διανυσμα στηλη 
   else{
    rows=arr.size();
    cols=1;
   }
   data.resize(rows*cols);

   for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
     data[index(i, j)] = arr[isrows ? j : i];
    }
   }
}


//Δημιουργια 2D πινακα με χρηση του constructor
Matrix::Matrix(const std::vector<std::vector<double>>&arr){
    //αριθμος γραμμων 
    rows=arr.size();
    //αριθμος στυλων 
    cols=arr[0].size();
    if(rows==0 ||cols==0){
        throw std::invalid_argument("Empty matrix");
    }
    data.resize(rows*cols);
    for(int i=0;i<rows;i++){
        if(arr[i].size()!=cols){
          throw std::invalid_argument("Inconsistent column sizes in data.");
        }
        for (int j = 0; j < cols; ++j) {
            data[index(i, j)] = arr[i][j];
        }
    }
}



// Υλοποιηση της προσθεσης πινακων 
Matrix Matrix::operator+(const Matrix& other)const{
  std::cout<<"Operator + called with second mar=trix reference\n";
  Matrix result(*this); 
  result+=other; 
  return result;
}

Matrix Matrix::operator+(Matrix&&other)const{
    std::cout<<"operator + called with temporary matrix reference\n";
    other+=*this;
    return std::move(other);
}


// Υλοποιηση της αφαιρεσης πινακων 
Matrix Matrix::operator-(const Matrix& other)const{
    if(rows!=other.rows ||cols!=other.cols){
        throw std::invalid_argument("the dimensions of the matrixes must be the same");
    }
std::cout<<"operator - called with second marix reference\n";
 Matrix result(*this);
 result-=other;
 return result;
} 

Matrix Matrix::operator-(Matrix&&other)const{
    std::cout<<"operator - called with temporary matrix reference\n";
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            other(i, j) = (*this)(i, j) - other(i, j);
    return std::move(other);
}


//Υλοποιηση του γινομενου πινακων 
Matrix Matrix::operator*(const Matrix& other)const{
    std::cout<<"operator * called\n";
    if(cols!=other.rows)
    {
        throw std::invalid_argument("The columns of the first Matrix  must be the same with the rows of the second Matrix ");
    } 
    Matrix result(rows,other.cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<other.cols;j++){
            double sum = 0.0;
            for(int k=0;k<cols;k++){
        sum+=data[index(i,k)]*other.data[other.index(k,j)];          
      }
      result.data[result.index(i,j)]=sum;
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix&other){
    std::cout<<"operator +=called\n";
    if(rows!=other.rows ||cols!=other.cols){
        throw std::invalid_argument("dimensions must agreee");
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            data[index(i,j)]+=other.data[index(i,j)];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix&other){
    std::cout<<"operator -= called\n";
    if(rows!=other.rows ||cols!=other.cols){
        throw std::invalid_argument("dimensions must agreee");
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            data[index(i,j)]-=other.data[index(i,j)];
        }
    }
    return *this;
}

//Υλοποιηση υπερφορτωσης για αναγνωση στοιχειων του πινακα 
double Matrix::operator()(int row, int col) const {
    std::cout<<"accessing an element\n";
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return data[index(row, col)];  
}

//Υλοποιηση υπερφορτωσης για προσβαση σε  στοιχεια του πινακα 
double& Matrix::operator()(int row, int col) {
    std::cout<<"changing an element of the matrix\n";
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return data[index(row, col)]; 
}


//Υλοποιηση της εκτυπωσης του πινακα 
std::ostream& operator<<(std::ostream&os , const Matrix& matrix){
    std::cout<<"printinh the matrix\n";
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            os << matrix.data[matrix.index(i,j)] << " ";
        }
        os << std::endl;
    }
    return os;
}


Matrix::Matrix(Matrix&&other) noexcept:rows(other.rows),cols(other.cols),data(std::move(other.data)){
    other.rows=0;
    other.cols=0;
}

Matrix& Matrix::operator=(Matrix&&other)noexcept{
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = std::move(other.data);
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}