#include <iostream>
#include <c2ga/Mvec.hpp>

using namespace c2ga;

int main(){

    // sample instructions
    std::cout << "metric : \n" << c2ga::metric << std::endl;

    // accessor
    Mvec<double> mv1;
    mv1[scalar] = 1.0;
    mv1[E0] = 42.0;
    std::cout << "mv1 : " << mv1 << std::endl;

    Mvec<double> mv2;
    mv2[E0] = 1.0;
    mv2[E1] = 2.0;
    mv2 += I<double>() + 2*e01<double>();
    std::cout << "mv2 : " << mv2 << std::endl << std::endl;

    // some products
    std::cout << "outer product     : " << (mv1 ^ mv2) << std::endl;
    std::cout << "inner product     : " << (mv1 | mv2) << std::endl;
    std::cout << "geometric product : " << (mv1 * mv2) << std::endl;
    std::cout << "left contraction  : " << (mv1 < mv2) << std::endl;
    std::cout << "right contraction : " << (mv1 > mv2) << std::endl;
    std::cout << std::endl;

    // some tools
    std::cout << "grade : " << mv1.grade()  << std::endl;
    std::cout << "norm  : " << mv1.norm()  << std::endl;
    mv1.clear();
    if(mv1.isEmpty()) std::cout << "mv1 is empty: ok" << std::endl;

    return 0;
}
