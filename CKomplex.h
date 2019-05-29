#include <iostream>
#include <math.h>

class CKomplex{
private:
    double real_;
    double imag_;
public:
	CKomplex(double real = 0, double imag = 0);
    CKomplex(double phi);
	double re() const;
    double im() const;
    double abs() const;
    void print_complex() const;
    friend std::ostream& operator<<(std::ostream & os, CKomplex& c);
    friend CKomplex operator+(const CKomplex& a, const CKomplex& b);
    friend CKomplex operator*(const CKomplex& a, const CKomplex& b);
};