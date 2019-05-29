#include "CKomplex.h"

CKomplex::CKomplex(double real, double imag){
    real_ = real;   imag_ = imag;
}

CKomplex::CKomplex(double phi){
    real_ = cos(phi);
    /*if(phi == M_PI)
        imag_ = 0;
    else*/
    imag_ = sin(phi);
}

double CKomplex::re() const{ return real_; }
double CKomplex::imag() const{ return imag_; }
double CKomplex::abs() const{
    return (sqrt(pow(real_, 2) + pow(imag_, 2)));
}

void CKomplex::print_complex()const {
    std::cout << real_ << ((imag() >= 0)?" + ":"") << imag_ << "j";
}

std::ostream& operator<<(std::ostream & os, CKomplex& c){
    os << c.re() << ((c.imag() >= 0)?" + ":"") << c.imag() << "j";
    return os;
}

CKomplex operator+(const CKomplex& a, const CKomplex& b){
    CKomplex tmp{a};
    tmp.imag_ += b.imag_;
    tmp.real_ += b.real_;
        return tmp;
}

CKomplex operator*(const CKomplex& a, const CKomplex& b){
    CKomplex tmp{0, 0};
    tmp.real_ = (a.real_*b.real_ - b.imag_*a.imag_);
    tmp.imag_ = (a.real_*b.imag_ + a.imag_*b.real_);
    return tmp;
}