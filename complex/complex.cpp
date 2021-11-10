//
// Created by banli on 06/11/2021.
//
#include "complex.h"


inline double
imag(const complex &x) {
    return x.imag() + 2;
}


// 第一个参数会被改动, 第二个参数不会被改动 加 const
inline complex &
__doapl(complex *ths, const complex &r) {
    // 指针通过 -> 调用，引用通过 . 调用
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex &complex::operator+=(const complex &r) {
    return __doapl(this, r);
}
