//
// Created by banli on 06/11/2021.
//

#ifndef COMPLEX_COMPLEX_H
#define COMPLEX_COMPLEX_H

class complex {
public:
    complex(double r = 0, double i = 0)
            : re(r), im(i) {}

    // 此函数在调用 complex c; 时，编译器不知道调用哪个, 因为有默认参数
    // complex()
    // : re(0), im(0) {}

    complex &operator+=(const complex &);

    // const 表示函数不会修改值
    double real() const { return re; } // inline function
    double imag() const { return im; }

    int func(const complex &param) {
        return param.re + param.im;
    }

private:
    double re, im;

    friend complex &__doapl(complex *, const complex &);
};

#endif //COMPLEX_COMPLEX_H
