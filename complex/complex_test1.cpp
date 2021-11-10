//
// Created by banli on 05/11/2021.
//
#include <iostream>
#include "complex.h"
using namespace std;

int main() {
//    complex c = complex(2, 1);
    complex c(2, 1);
    std::cout << c.real() << std::endl; // std::endl 是换行
    cout << c.imag() << endl;

    // 'im' is a private member of 'complex' 不能访问私有变量
    // std::cout << c.im << std::endl;

    complex c2; // complex c2();
    cout << c2.real() << endl; // std::endl 是换行
    cout << c2.imag() << endl;

    cout << "--- hello2 ---" << endl;
    c += c2;
    std::cout << c.real() << std::endl;

    cout << "--- hello3 ---" << endl;
    int a = c2.func(c);
    cout << a << endl << endl;
}
