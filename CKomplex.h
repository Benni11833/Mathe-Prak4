#include <iostream>
#include <math.h>

class CKomplex{
private:
    double real_;
    double imag_;
public:
	CKomplex() {};
	CKomplex(double real, double imag);
    CKomplex(double phi);
	double re() const;
    double im() const;
    double abs() const;
    void print_complex() const;
    friend std::ostream& operator<<(std::ostream & os, const CKomplex& c);
    friend CKomplex operator+(const CKomplex& a, const CKomplex& b);
    friend CKomplex operator*(const CKomplex& a, const CKomplex& b);
	friend CKomplex operator*(const double& a, const CKomplex& b);
};