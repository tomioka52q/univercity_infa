#include <SFML/Graphics.hpp>

int main() {
    // —оздание окна 500x500 пикселей
    sf::RenderWindow window(sf::VideoMode(500, 500), "");

    int n = 10;
    int cellSize = 50;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // ќчистка экрана
        window.clear(sf::Color::Black);

        // ќтрисовка сетки и €чеек
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // —оздание пр€моугольника дл€ €чейки
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(j * cellSize, i * cellSize);
                
                // ќпределение цвета €чейки на лету
                if (i + j == 9) {
                    cell.setFillColor(sf::Color::Green); // «еленый дл€ побочной диагонали
                } else {
                    cell.setFillColor(sf::Color::White); // Ѕелый дл€ остальных €чеек
                }
                
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);

                // ќтрисовка €чейки
                window.draw(cell);
            }
        }

        // ќтображение результата
        window.display();
    }

    return 0;
}