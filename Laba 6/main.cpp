#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace sf;

// Константы (сделал 10, чтобы было как на фото)
const int GRID_SIZE = 10;
const int CELL_SIZE = 60;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

enum CellType {
    EMPTY,
    OBSTACLE,
    START,
    END,
    PATH,
    VISITED
};

struct Cell {
    int x, y;
    CellType type;
    int f, g, h;
    Cell* parent;

    Cell(int x, int y) : x(x), y(y), type(EMPTY), f(0), g(0), h(0), parent(nullptr) {}

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

// Чтобы очередь выбирала клетку с самым маленьким F
struct CompareCells {
    bool operator()(Cell* a, Cell* b) {
        return a->f > b->f;
    }
};

// Функция для вычисления эвристики (манхэттенское расстояние)
int heuristic(const Cell& a, const Cell& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Функция для проверки границ
bool isValid(int x, int y) {
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

// Метод A*
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
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A* Pathfinding");

    // Создаем сетку
    vector<vector<Cell>> grid;
    for (int i = 0; i < GRID_SIZE; ++i) {
        vector<Cell> row;
        for (int j = 0; j < GRID_SIZE; ++j) {
            row.push_back(Cell(i, j));
        }
        grid.push_back(row);
    }

    // Расставляем препятствия с фото (X - столбец, Y - строка)
    vector<pair<int, int>> obs = {
        {3,0}, {8,0}, {9,0}, 
        {0,1}, {1,1}, {2,1}, {7,1},
        {1,2}, {2,2}, {5,2}, {7,2},
        {0,3}, {2,3}, {5,3}, {9,3},
        {5,4},
        {3,5}, {6,5}, {8,5},
        {2,6}, {4,6}, {6,6}, {7,6},
        {0,7}, {1,7}, {3,7}, {4,7}, {6,7},
        {1,8}, { 3,8 }, {6,8}, {7,8},
        {0,9}, {2,9}, {8,9}
    };
    for (auto p : obs) grid[p.first][p.second].type = OBSTACLE;

    // Старт и конец
    Cell* startNode = &grid[0][5]; startNode->type = START;
    Cell* endNode = &grid[9][9];   endNode->type = END;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();

            // Запуск на Пробел
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                a_star_algorithm(grid, startNode, endNode);
            }
        }

        window.clear();

        // шаблон отрисовки
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                RectangleShape cell(Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);

                switch (grid[i][j].type) {
                case EMPTY: cell.setFillColor(Color::White); break;
                case OBSTACLE: cell.setFillColor(Color::Black); break;
                case START: cell.setFillColor(Color::Green); break; // Король
                case END: cell.setFillColor(Color::Red); break; // Крестик
                case PATH: cell.setFillColor(Color::Blue); break;
                case VISITED: cell.setFillColor(Color::Cyan); break;
                }

                window.draw(cell);
            }
        }
        window.display();
    }

    return 0;
}
