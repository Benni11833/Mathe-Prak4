#include "CKomplex.h"


int main(){

    CKomplex c1{-7, 5};
    std::cout << c1 << std::endl;
    CKomplex c2{3, -3};
    std::cout << c2 << std::endl;
    CKomplex c3{0, 0};
    c3 = c1*c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    std::cout << "Betrag: " << c3.abs() << std::endl;

    return 0;
}