#include <iostream>

class Complex
{
public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }

private:
    double real;
    double imag;
};

std::istream& operator>>(std::istream& is, Complex& complex)
{
    double real, imag;

    is >> real >> imag;

    complex.setReal(real);
    complex.setImag(imag);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
    os << "(" << complex.getReal() << ", " << complex.getImag() << ")";
    return os;
}

int main()
{
    Complex complex;
    std::cin >> complex;
    std::cout << complex;
}