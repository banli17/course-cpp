# cpp

## git push clone 不了

测试
```
ssh -T git@github.com
```

``` 
vim ~/.ssh/config
```

添加内容

``` 
Host github.com
  Hostname ssh.github.com
  Port 443
```

https://www.jianshu.com/p/d837b98a2d74

## mac clion 第一次运行时报错

是删除了 xcode 导致编译器找不到了。重置一下

``` 
sudo xcode-select -r

xcode-select --switch /Library/Developer/CommandLineTools

xcode-select -p
```

```
/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_DEPENDS_USE_COMPILER=FALSE -G "CodeBlocks - Unix Makefiles" /Users/banli/Desktop/course/course-cpp/complex
-- The C compiler identification is unknown
-- The CXX compiler identification is unknown
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - failed
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc - broken
CMake Error at /Applications/CLion.app/Contents/bin/cmake/mac/share/cmake-3.20/Modules/CMakeTestCCompiler.cmake:66 (message):
The C compiler

    "/usr/bin/cc"

is not able to compile a simple test program.

It fails with the following output:

    Change Dir: /Users/banli/Desktop/course/course-cpp/complex/cmake-build-debug/CMakeFiles/CMakeTmp
    
    Run Build Command(s):/usr/bin/make -f Makefile cmTC_48a47/fast && xcrun: error: active developer path ("/Applications/Xcode.app/Contents/Developer") does not exist
    Use `sudo xcode-select --switch path/to/Xcode.app` to specify the Xcode that you wish to use for command line developer tools, or use `xcode-select --install` to install the standalone command line developer tools.
    See `man xcode-select` for more details.
```

## 头文件和类声明

### c vs c++ 关于函数和数据

c: data (创建变量) + functions  -> varible 
type(built-in, struct)
没有特殊的关键字，数据和方法都是可以随意访问了
c++: member data + member functions -> object 
class, struct

数据的类型 (值类型和引用类型)
complex 
- 数据：实部，虚部， 可以有多个复数, 存的是值
- 操作数据的函数： 只有一份

string
- 数据：字符，如hello world，实际存的是指针 ptr 指向一串字符
- 函数

Object Based(基于对象) 面向单一 class 的设计
Object Oriented(面向对象) 面向多重 class 的设计, class 与 class 之间的关系

class 的两个经典分类：
- class without pointer member(s)
  - complex
- class with pointer member(s)
  - string


c++ programs 代码基本形式, 可以是下面组合

- .h(header files): class declaration 声明
- .cpp/.ex 文件, 不一定是 .cpp, 有 `main()` 函数
  - `#include <iostream.h>`
  - `#include "complex.h"`
- .h(header files): standard library 标准库

扩展文件名不一定是 .h 或 .cpp。也可能是 .hpp 或其他或没有扩展名。

Outpub, C++ vs. C

C++ 通过如 `cout << "i=" << i << endl;`
C 通过 `print("i=%d \n", i)`

### Header(头文件)防卫式声明

```c++
#ifndef __COMPLEX__  // 如果没有定义过 __COMPLEX__
#define __COMPLEX__  // 就定义 __COMPLEX__

...

#endif
```

### class 声明(declaration)

- class head
- class body

```c++

```

### class template(模版) 简介

比如想将实部、虚部的类型不写固定 double。

```c++
template<typename T>
class complex
        {
    private:
            T re, im;
        };

complex<double> c1(2.5, 1.5);
complex<int> c2(2, 6);
```

## 构造函数

### inline 函数

直接在class 内定义的函数叫做 inline 函数(一般短的, 简单的函数)。
编译器决定是否 inline，写的 inline 只是对编译器的建议而已。

### access level (访问级别)

- public
- private
- protect

可以多段分开写都行

```c++
class complex
{
  public:
    ...
  private:
    ...
  public:
    ...
}```

### constructor (ctor, 构造函数)

创建对象时自动调用。

创建方式

```c++
complex c1(2, 1);
complex c2;
complex* p = new complex(4);
```

- 参数支持默认值

构造函数不需要返回值
- 因为它本身就是来创建某种对象的
- : 后面用来设置初始值, 叫做初值列

```c++
complex (double r = 0, double i = 0)
    : re(r), im(i) // 设初值
    {
        // 函数体
    }
```

为什么在初值列设置，而不在函数体里？
变量包含两个阶段：声明和赋值。相当于放弃了初始化阶段。
写在函数体中，效率差一些。

构造函数可以有多个 - overloading(重载)。
希望对象创建支持多种方式。
不同的构造函数会编译为不同的函数名 `?real@Complex@@+hash6值`
把构造函数放在 private 区域。Singleton 单例模式

```c++
class A{
public:
    static A& getInstance();
    setup() {...}
private:
    A();
    A(const A& rhs);
};

A& A::getInstance() // 只能通过这个方法来调用
{
    static A a;
    return a;
}
```

const member functions(常量成员函数)

成员函数包括会改变数据，或不会改变数据。如果不改变，就加 const。

不加可能导致使用者调用时出现问题。
```c++
const complex c1(2, 1); // 使用者说不可以改, 但是设计类说可能改, 编译器报错
cout << c1.real();
```

### 参数传递 pass by value vs. pass by reference(to const)

pass by value 参数整包传递过去(有可能很大)
pass by reference(推荐) 和传指针一样快，底层就是一个指针, 传递内容很小

### return by value vs. return by reference

返回值尽量用 reference。

```
complex &operator += (const complex &)
double real() const { return re; }
```

什么情况下使用 value, reference?

返回值如果要放在参数里(已经存在的), 就返回 reference。
如果是局部变量，就要返回 value，因为函数执行完变量就销毁了, 如果返回 reference 就获取不到了。

return by reference 
传递者无需知道接收者是以 reference 形式接收

```cpp
// 接收的是一个引用 &
inline complex &
__doapl(complex *ths, const complex &r) {
    // ...
    return *ths; // 返回的是一个对象(东西), 是一个 value
}

inline complex&
complex::operator += (const complex &) // c += c1;
{
    // 为什么需要返回值, 不能是 void
    // c3 += c2 += c1
    return __doapl(this, r); 
}
```
### friend(友元)

```c++
class complex
{
    private:
        double re, im;
        friend complex& __doapl (complex*, const complex &);
};
```

相同 class 的各个 objects 互为 friends(友元)


总结 class 写法：
1. 数据用 private
2. 参数尽量用 reference 来传递, 要不要加 const ?
3. 返回值尽量用 reference 来传递。
4. body 里的函数应该加 const 就要加。
5. constructor 要用初值列。

### operator overloading (操作符重载入)

**成员函数(有 this)**
c2 += c1;
操作符是作用与左值的, 在 c2 上调用,
操作符函数会自动注入一个 this, 这里 this 是编译器注入的, 不需要程序员写。不同编译器行为不一样,有可能注入到最后一个参数。

```cpp
inline complex&
complex::operator += (this, const complex& r)
{
  return  __doapl (this, r);
}
```

任何成员函数都有个隐藏的 this, 指向调用者。

**非成员函数(无 this)**
`+ 重载`
为了满足 client 写法, + 重载需要写三个函数
- 复数 + 复数
- 复数 + double
- double + 复数

temp object(临时对象) typename() 需要return by value