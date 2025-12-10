
#include <iostream>
#include "Calculator.h"

int main()
{
    double x, y;

    std::cout << "¬ведите x и y: ";
    std::cin >> x >> y;

    try
    {
        double R = calculate_R(x, y);
        double S = calculate_S(x);
        double C = calculate_C(R, S);

        std::cout << "R = " << R << std::endl;
        std::cout << "S = " << S << std::endl;
        std::cout << "C = " << C << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "ќшибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
