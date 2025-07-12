#include "../inc/Matrix.hpp"
#include <cassert>
#include <iostream>
#include<chrono>

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
    assert(C(0, 0) == 4);  
    assert(C(1, 1) == 8);  
}

void test_inplace_addition(){
    Matrix A({{1, 2}, {3, 4}});
    Matrix B({{2, 0}, {1, 2}});
    A+=B;
    assert(A(0,0)==6);
    assert(A(0,1)==2);
    assert(A(1,0)==4);
    assert(A(1,1)==12);
}

void test_inplace_substraction(){
    Matrix A({{5,5},{5,5}});
     Matrix B({{2,1},{3,4}});
     A-=B;
     assert(A(0,0)==3);
     assert(A(0,1)==4);
     assert(A(1,0)==2);
     assert(A(1,1)==1);

}

void test_move_addition(){
    Matrix A({ {1,1},{1,1}});
    Matrix B=A+Matrix({ {2,2},{2,2}});
    assert(B(0,0)==3);
}
void test_move_assignment(){
    Matrix A({{7,8},{9,10}});
    Matrix B=std::move(A);
    assert(B(1,1)==10);
}
int main() {

    auto t1=std::chrono::high_resolution_clock::now();
    test_addition();
    auto t2=std::chrono::high_resolution_clock::now();
    std::cout<<"\ntest duration for test_addition:"<<std::chrono::duration<double,std::micro>(t2-t1).count()<<"μs";

    test_subtraction();
    auto t3=std::chrono::high_resolution_clock::now();
    std::cout<<"\ntest duration for test_substraction:"<<std::chrono::duration<double,std::micro>(t3-t2).count()<<"μs";

    test_multiplication();
    auto t4=std::chrono::high_resolution_clock::now();
    std::cout<<"\ntest duration for test_multiplication:"<<std::chrono::duration<double,std::micro>(t4-t3).count()<<"μs";

    test_inplace_addition();
    auto t5=std::chrono::high_resolution_clock::now();
    std::cout<<"\ntest duration for test_inplace_addition:"<<std::chrono::duration<double,std::micro>(t5-t4).count()<<"μs";

    test_inplace_substraction();
    auto t6=std::chrono::high_resolution_clock::now();
    std::cout<<"\ntest duration for test_inplace_substarction:"<<std::chrono::duration<double,std::micro>(t6-t5).count()<<"μs";

    test_move_addition();
    auto t7=std::chrono::high_resolution_clock::now();
    std::cout<<"\ntest duration for test_move_addition:"<<std::chrono::duration<double,std::micro>(t7-t6).count()<<"μs";

    test_move_assignment();
    auto t8=std::chrono::high_resolution_clock::now();
    std::cout<<"\ntest duration for test_move_assignement:"<<std::chrono::duration<double,std::micro>(t8-t7).count()<<"μs";
    std::cout << "\nAll tests passed " << std::endl;
    return 0;
}
