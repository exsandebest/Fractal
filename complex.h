#ifndef COMPLEX_H
#define COMPLEX_H
#include <math.h>

class complex {
public:
    double r,i;
    complex(double re, double im){
        r = re;
        i = im;
    }
    complex(const complex & c){
        r = c.r;
        i = c.i;
    }
    ~complex(){}

    complex operator+(complex & c){

        return complex(this->r + c.r, this->i + c.i);
    }
    complex operator-(complex & c){
        return complex(this->r - c.r, this->i - c.i);
    }
    complex operator*(complex & c){
        return complex(this -> r * c.r - this -> i * c.i, this -> i * c.r + this -> r * c.i);
    }
    double v(){
        return sqrt(r*r+i*i);
    }
};

#endif // COMPLEX_H
