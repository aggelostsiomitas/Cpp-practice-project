#pragma once 
#include<vector>
#include<iostream>
#include<stdexcept>

class Matrix{
    private:
    //Οι μεταβλητες μου 
        int rows,cols;
        std::vector<double>data;
        int index(int row, int col) const { return row * cols + col; } //function for faster matrix index access

    public:
        // οι constructors μου 
        Matrix(int rows,int cols); 
        Matrix(const std::vector<double>&arr,bool isrows); //1D 
        Matrix(const std::vector<std::vector<double>>&arr); //2D

        // Οι υπερφορτωσεις που θα χρειαστω 
        Matrix operator+(const Matrix& other) const;  //για το αθροισμα πινακων 
        Matrix operator-(const Matrix& other) const; //για την αφαιρεση πινακων 
        Matrix operator*(const Matrix& other) const; // για το γινομενο πινακων 

        Matrix& operator+=(const Matrix&other);
        Matrix& operator-=(const Matrix&other);


        //copy constructor
        Matrix(Matrix&& other) noexcept;
        Matrix& operator=(Matrix&& other) noexcept;        
        Matrix(const Matrix& other) = default;
        Matrix&operator=(const Matrix&other)=default;
        Matrix operator+(Matrix&& other) const;
        Matrix operator-(Matrix&& other) const;


        double operator()(int row, int col) const;
        double& operator()(int row, int col);


        //βοηθητικες συναρτησεις για εκτυπωση , και για τις γραμμες και τις στυλες 
        int getRows()const{return rows;}
        int getCols()const {return cols;}
        

        //Υπερφορτωση τελεστη <<  για εκτυπωση του πινακα 
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};
