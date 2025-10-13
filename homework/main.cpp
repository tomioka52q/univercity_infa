#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath>

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); // Вычисление значения функции

        // Преобразование координат в экранные
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        // Добавление точки в массив вершин
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Приложение для вывода графиков");

    // Переменная для хранения пользовательской точки
    sf::CircleShape userPoint(5); // Радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // Переменная для проверки существования пользовательской точки

    // 1 _ Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
 
    }

    // 2 _ Текст для отображения координат точки
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);

    // Текст для отображения зоны
    sf::Text zoneText;
    zoneText.setFont(font);
    zoneText.setCharacterSize(20);
    zoneText.setFillColor(sf::Color::White);
    zoneText.setPosition(10, 40);

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300); // Начало оси X
    xAxis[0].color = sf::Color::White; // Цвет оси
    xAxis[1].position = sf::Vector2f(750, 300); // Конец оси X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50); // Начало оси Y
    yAxis[0].color = sf::Color::White; // Цвет оси
    yAxis[1].position = sf::Vector2f(400, 550); // Конец оси Y
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Проверка клика мышью
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получение позиции клика
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в "математические"
                    float mathX = (mousePos.x - 400) / 30.0f; // Масштаб 30 по X
                    float mathY = -(mousePos.y - 300) / 30.0f; // Масштаб 30 по Y

                    // Установка новой пользовательской точки
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // Помечаем, что точка существует

                    // 3 _ Логика проверки точки по переменным mathX и mathY
                    float y1 = -5 * mathX + 3;
                    float y2 = 3 * mathX - 6;

                    std::string zone = "";

                    // Определение зон
                    if (mathY > y1 && mathY > y2) {
                        zone = "Zone 3";
                    }
                    else if (mathY < y1 && mathY < y2) {
                        zone = "Zone 2";
                    }
                    else if (mathY > y1 && mathY < y2) {
                        zone = "Zone 4";
                    }
                    else if (mathY < y1 && mathY > y2) {
                        zone = "Zone 1";
                    }
                    else {
                        zone = "NO";
                    }


                    // Обновление текста с координатами точки
                    coordinatesText.setString("Coordinates: (" +
                        std::to_string(static_cast<int>(mathX * 100) / 100.0f).substr(0, 4) + ", " +
                        std::to_string(static_cast<int>(mathY * 100) / 100.0f).substr(0, 4) + ")");

                    zoneText.setString(zone);
                }
            }
        }

        // 4 _ Очистка экрана
        window.clear(sf::Color::Black);

        // Отрисовка осей
        window.draw(xAxis);
        window.draw(yAxis);

        // 5 _ Отрисовка графика y1 = -5*x + 3
        drawGraph(window, [](float x) { return -5 * x + 3; }, -10, 10, 30, 30, sf::Color::Red);

        // 5 _ Отрисовка графика y2 = 3*x - 6
        drawGraph(window, [](float x) { return 3 * x - 6; }, -10, 10, 30, 30, sf::Color::Blue);

        // Отрисовка пользовательской точки, если она существует
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
            window.draw(zoneText);
        }

        // Отображение нового кадра
        window.display();
    }

    return 0;
}