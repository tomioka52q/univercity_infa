#pragma once
#include <cmath>
#include <stdexcept>

const double PI = 3.141592653589793;

double calculate_R(double x, double y) {
    // проверки входных данных
    if (x <= 0) throw std::invalid_argument("x должен быть положительным");
    if (x * y < 0) throw std::invalid_argument("x * y должны быть больше 0");
    double cos_x = std::cos(x);
    // защита от деления на ноль
    if (fabs(cos_x) < 1e-15) throw std::invalid_argument("cos(x) близок к нулю");
    double sec_x = 1.0 / cos_x;
    return std::sqrt(x * y) / fabs(sec_x);
}

inline double calculate_S(double x) {
    if (x <= 0) throw std::invalid_argument("x должен быть положительным");
    return (PI / 2.0) * (std::log(x) / std::log(5.0));
}

inline double calculate_C(double R, double S) {
    return (R > S) ? R : S;
}

