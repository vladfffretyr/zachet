#include <iostream>
#include <cmath>

class Power {
private:
    double first;
    double second;
public:
    Power() : first(0), second(0) {} 
    Power(double f, double s = 0) : first(f), second(s) {} 
    double power() const { return std::pow(first, second); } 
};

int main() {
    Power p1; 
    std::cout << "p1.power() = " << p1.power() << std::endl; 

    Power p2(2.0, 3.0); 
    std::cout << "p2.power() = " << p2.power() << std::endl; 

    return 0;
}
