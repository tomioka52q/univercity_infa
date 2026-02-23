#include <iostream>
#include <cstdlib>
#include <cmath>

bool is_inside_rhombus(double x, double y) {
    return (fabs(x) / 4.0 + fabs(y) / 2.0 <= 1.0);
}

double monte_carlo_rhombus_area(int num_points) {
    int inside_points = 0;

    for (int i = 0; i < num_points; ++i) {
        double x = ((double)rand() / RAND_MAX) * 8.0 - 4.0;
        double y = ((double)rand() / RAND_MAX) * 4.0 - 2.0;

        if (is_inside_rhombus(x, y)) {
            inside_points++;
        }
    }

    double rectangle_area = 32.0;
    return (inside_points / (double)num_points) * rectangle_area;
}

int main() {
    std::cout << "N=100: " << monte_carlo_rhombus_area(1000) << std::endl;
    std::cout << "N=1000: " << monte_carlo_rhombus_area(1000) << std::endl;
    std::cout << "N=10000: " << monte_carlo_rhombus_area(10000) << std::endl;
    std::cout << "N=100000: " << monte_carlo_rhombus_area(100000) << std::endl;
    std::cout << "N=1000000: " << monte_carlo_rhombus_area(1000000) << std::endl;

    return 0;
}
