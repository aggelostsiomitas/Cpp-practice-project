#include "../inc/Matrix.hpp"

//Δημιουργια πινακα
Matrix::Matrix(int rows,int cols){
    //έλεγχος για ακυρη εισοδος rows,cols
    if(rows<=0 ||cols<=0){
        throw std::invalid_argument("Invalid input for matrix");
    }
    this->rows=rows;
    this->cols=cols;
     //φτιαχνω εναν κενο πινακα με μηδενικα στην αρχη 
     data.resize(rows,std::vector<double>(cols,0.0));
}


//Δημιουργια του 1D πινακα 
Matrix::Matrix(const std::vector<double>&arr,bool isrows){
    //αν ειναι διανυσμα γραμμη 
   if(!isrows){
    rows=1;
    cols=arr.size();
    data.resize(1,std::vector<double>(cols));
    for(int i=0;i<cols;i++){
        data[0][i]=arr[i];
        }
   }
   //αλλιως θα ειναι διανυσμα στηλη 
   else{
    rows=arr.size();
    cols=1;
    data.resize(rows,std::vector<double>(1));
    for(int i=0;i<rows;i++){
        data[i][0]=arr[i];
    }
   }
}


//Δημιουργια 2D πινακα με χρηση του constructor
Matrix::Matrix(const std::vector<std::vector<double>>&arr){
    //αριθμος γραμμων 
    rows=arr.size();
    //αριθμος στυλων 
    cols=arr[0].size();
    data=arr;
    if(rows==0 ||cols==0){
        throw std::invalid_argument("Empty matrix");
    }
}



// Υλοποιηση της προσθεσης πινακων 
Matrix Matrix::operator+(const Matrix& other)const{
    //ελεγχος διαστασεων 
    if(rows!=other.rows ||cols!=other.cols){
        throw std::invalid_argument("Matrix dimensions must agree");
    }
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            result.data[i][j]=data[i][j]+other.data[i][j];
        }
    }
    return result;
}


// Υλοποιηση της αφαιρεσης πινακων 
Matrix Matrix::operator-(const Matrix& other)const{
    //ελεγχος διαστασεων 
     if(rows!=other.rows ||cols!=other.cols){
        throw std::invalid_argument("Matrix dimensions must agree");
    }
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            result.data[i][j]=data[i][j]-other.data[i][j];
        }
    }
    return result;
} 

//Υλοποιηση του γινομενου πινακων 
Matrix Matrix::operator*(const Matrix& other)const{
    //λεγχος γραμμων και στυλων, οι στυλες του πρωτου πρεπει να ειναι ιδιες με τις γραμμες του δυτερου
    if(cols!=other.rows)
    {
        throw std::invalid_argument("The columns of the first Matrix  must be the same with the rows of the second Matrix ");
    } 
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<other.cols;j++){
            for(int k=0;k<cols;k++){
                result.data[i][j]+=data[i][k]*other.data[k][j];
            }
        }
    }
    return result;
}

//Υλοποιηση υπερφορτωσης για αναγνωση στοιχειων του πινακα 
double Matrix::operator()(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return data[row][col];
}

//Υλοποιηση υπερφορτωσης για προσβαση σε  στοιχεια του πινακα 
double& Matrix::operator()(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
    return data[row][col];
}


//Υλοποιηση της εκτυπωσης του πινακα 
std::ostream& operator<<(std::ostream&os , const Matrix& matrix){
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}