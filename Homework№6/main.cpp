#include <SFML/Graphics.hpp>

int main() {
    // �������� ���� 500x500 ��������
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

        // ������� ������
        window.clear(sf::Color::Black);

        // ��������� ����� � �����
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // �������� �������������� ��� ������
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(j * cellSize, i * cellSize);
                
                // ����������� ����� ������ �� ����
                if (i + j == 9) {
                    cell.setFillColor(sf::Color::Green); // ������� ��� �������� ���������
                } else {
                    cell.setFillColor(sf::Color::White); // ����� ��� ��������� �����
                }
                
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);

                // ��������� ������
                window.draw(cell);
            }
        }

        // ����������� ����������
        window.display();
    }

    return 0;
}