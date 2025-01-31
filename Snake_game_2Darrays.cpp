#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>

using namespace std;
const int ROWS = 20;
const int COLS = 30;
enum Direction { UP, DOWN, LEFT, RIGHT };
Direction currentDirection;

vector<vector<int>> grid(ROWS, vector<int>(COLS, 0)); // 0: empty, 1: snake, 2: food
vector<pair<int, int>> snake = {{10, 15}};            
pair<int, int> food;                                  
bool gameOver = false;
int score = 0;


void initializeGrid() {
    grid[snake[0].first][snake[0].second] = 1;
    srand(time(0)); 
    food = {rand() % ROWS, rand() % COLS};
    grid[food.first][food.second] = 2;
}

void drawGrid() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (grid[row][col] == 1) {
                cout << "S"; 
            } else if (grid[row][col] == 2) {
                cout << "F";
            } else {
                cout << "."; 
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void moveSnake() {
    pair<int, int> head = snake[0];
    if (currentDirection == UP) {
        head.first--;
    } else if (currentDirection == DOWN) {
        head.first++;
    } else if (currentDirection == LEFT) {
        head.second--;
    } else if (currentDirection == RIGHT) {
        head.second++;
    }

    if (head.first < 0 || head.first >= ROWS || head.second < 0 || head.second >= COLS || grid[head.first][head.second] == 1) {
        gameOver = true;
        return;
    }

    if (head == food) {
        score++;
        while (true) {
            food = {rand() % ROWS, rand() % COLS};
            if (grid[food.first][food.second] == 0) {
                grid[food.first][food.second] = 2;
                break;
            }
        }
    } else {
        pair<int, int> tail = snake.back();
        grid[tail.first][tail.second] = 0;
        snake.pop_back();
    }

    snake.insert(snake.begin(), head);
    grid[head.first][head.second] = 1;
}

void getInput() {
    char key;
    cout << "Enter direction (W/A/S/D): ";
    cin >> key;

    if (key == 'W' || key == 'w') {
        if (currentDirection != DOWN) currentDirection = UP;
    } else if (key == 'S' || key == 's') {
        if (currentDirection != UP) currentDirection = DOWN;
    } else if (key == 'A' || key == 'a') {
        if (currentDirection != RIGHT) currentDirection = LEFT;
    } else if (key == 'D' || key == 'd') {
        if (currentDirection != LEFT) currentDirection = RIGHT;
    }
}

void delay(int milliseconds) {
    for (int i = 0; i < milliseconds * 1000; i++) {
    }
}

int main() {
    initializeGrid();
    currentDirection = RIGHT;

    while (!gameOver) {
        drawGrid();
        getInput();
        moveSnake();
        delay(300);
    }

    cout << "Game Over! Final Score: " << score << endl;
    return 0;
} 