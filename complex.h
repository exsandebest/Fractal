#ifndef COMPLEX_H
#define COMPLEX_H
#include <math.h>
#include <utility>

class complex {
public:
    double r;
    double i;
    complex(double r, double i): r(r), i(i) {}
    complex(const complex &c): r(c.r), i(c.i) {}
    ~complex(){}

    complex operator+(complex &c) {
        return complex(this->r + c.r, this->i + c.i);
    }
    complex operator-(complex &c) {
        return complex(this->r - c.r, this->i - c.i);
    }
    complex operator*(complex &c) {
        return complex(this->r * c.r - this->i * c.i, this->i * c.r + this->r * c.i);
    }
    complex& operator=(complex c) {
        std::swap(this->i, c.i);
        std::swap(this->r, c.r);
        return *this;
    }
    double v() {
        return sqrt(r*r + i*i);
    }
};

#endif // COMPLEX_H
