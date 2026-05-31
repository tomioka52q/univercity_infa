#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <ctime> // Для инициализации случайных чисел

using namespace std;
using namespace sf;

const int GRID_SIZE = 20;
const int CELL_SIZE = 30;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

enum CellType { EMPTY, OBSTACLE, START, END, PATH, VISITED };

struct Cell {
    int x, y;
    CellType type;
    int f, g, h;
    Cell* parent;

    Cell(int x, int y) : x(x), y(y), type(EMPTY), f(0), g(0), h(0), parent(nullptr) {}
};

// Чтобы очередь выбирала клетку с самым маленьким F
struct CompareCells {
    bool operator()(Cell* a, Cell* b) { return a->f > b->f; }
};

// Функция для вычисления эвристики (манхэттенское расстояние)
int heuristic(const Cell& a, const Cell& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Функция для проверки границ
bool isValid(int x, int y) {
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

// Функция для полной очистки в клетках
void resetGridData(vector<vector<Cell>>& grid) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j].g = 0;
            grid[i][j].f = 0;
            grid[i][j].h = 0;
            grid[i][j].parent = nullptr;
            if (grid[i][j].type == PATH || grid[i][j].type == VISITED) {
                grid[i][j].type = EMPTY;
            }
        }
    }
}

// Функция генерации случайных препятствий
void generateRandomObstacles(vector<vector<Cell>>& grid) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j].type = EMPTY;
            // 25% шанс, что клетка станет препятствием
            if (rand() % 100 < 25) {
                grid[i][j].type = OBSTACLE;
            }
        }
    }
}

void a_star_algorithm(vector<vector<Cell>>& grid, Cell* start, Cell* end) {
    priority_queue<Cell*, vector<Cell*>, CompareCells> open_list; // сортирует ячейки, чтобы наверху лежала ячейка с самым маленьким значением f 

    start->g = 0; // Расстояние от старта до старта 0 
    start->h = heuristic(*start, *end); // Примерное расстояние до цели
    start->f = start->g + start->h; // Итоговый вес
    open_list.push(start); // Кладем старт в очередь

    while (!open_list.empty()) {
        Cell* current = open_list.top(); // Берем ячейку с наименьшим f
        open_list.pop();

        if (current == end) {
            // Восстанавливаем путь
            Cell* temp = end->parent;
            while (temp != nullptr && temp->type != START) { // Идем назад до старта
                temp->type = PATH; // Помечаем каждую промежуточную ячейку как путь
                temp = temp->parent; // Переходим к следующему родителю
            }
            return;
        }

        if (current->type != START) current->type = VISITED;

        // Соседи (4 направления: вверх, вниз, влево, вправо)
        int dx[] = { 0, 0, 1, -1 };
        int dy[] = { 1, -1, 0, 0 };

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (isValid(nx, ny) && grid[nx][ny].type != OBSTACLE && grid[nx][ny].type != VISITED) { // Если координаты в сетке и это не стена и мы там еще не были
                int new_g = current->g + 1;

                if (new_g < grid[nx][ny].g || grid[nx][ny].g == 0) { // Если новый путь короче
                    grid[nx][ny].parent = current;
                    grid[nx][ny].g = new_g;
                    grid[nx][ny].h = heuristic(grid[nx][ny], *end);
                    grid[nx][ny].f = grid[nx][ny].g + grid[nx][ny].h;
                    open_list.push(&grid[nx][ny]);
                }
            }
        }
    }
}

int main() {
    srand(time(0)); // Чтобы рандом был всегда разным
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A* (Press SPACE to Solve, R to Randomize)");

    // Создаем сетку
    vector<vector<Cell>> grid;
    for (int i = 0; i < GRID_SIZE; ++i) {
        vector<Cell> row;
        for (int j = 0; j < GRID_SIZE; ++j) row.push_back(Cell(i, j));
        grid.push_back(row);
    }

    // Начальная генерация
    generateRandomObstacles(grid);
    Cell* startNode = &grid[0][0];
    Cell* endNode = &grid[GRID_SIZE - 1][GRID_SIZE - 1];
    startNode->type = START;
    endNode->type = END;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();

            // R - Генерировать новое поле
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                generateRandomObstacles(grid);
                startNode = &grid[0][0];
                endNode = &grid[GRID_SIZE - 1][GRID_SIZE - 1];
                startNode->type = START;
                endNode->type = END;
                resetGridData(grid);
            }

            // SPACE - Найти путь
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                a_star_algorithm(grid, startNode, endNode);
            }
        }

        window.clear();
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                RectangleShape rect(Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                rect.setPosition(i * CELL_SIZE, j * CELL_SIZE);

                switch (grid[i][j].type) {
                case EMPTY: rect.setFillColor(Color::White); break;
                case OBSTACLE: rect.setFillColor(Color::Black); break;
                case START: rect.setFillColor(Color::Green); break;
                case END: rect.setFillColor(Color::Red); break;
                case PATH: rect.setFillColor(Color::Blue); break;
                case VISITED: rect.setFillColor(Color::Cyan); break;
                }
                window.draw(rect);
            }
        }
        window.display();
    }
    return 0;
}
