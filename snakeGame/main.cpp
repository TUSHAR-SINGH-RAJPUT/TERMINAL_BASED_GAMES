#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    srand(time(0));   // Seed random

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw() {
    system("cls");

    // Top wall
    for (int i = 0; i < width + 2; i++)
        cout << "_";
    cout << endl;

    // Side walls & game area
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (j == 0)
                cout << "|";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
                cout << " ";

            if (j == width -1)
                cout << "|";
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < width + 2; i++)
        cout << "_";

    cout << "\nScore: " << score << endl;
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
        case 'a': if (dir != RIGHT) dir = LEFT; break;
        case 'd': if (dir != LEFT)  dir = RIGHT; break;
        case 'w': if (dir != DOWN)  dir = UP; break;
        case 's': if (dir != UP)    dir = DOWN; break;
        case 'x': gameOver = true; break;
        }
    }
}

void logic() {
    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default: break;
    }

    // Wall collision
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    // Fruit collision
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main() {
    cout << "Welcome to Snake Game!\n";
    Setup();

    while (!gameOver) {
        draw();  //draws the canvas
        input();
        logic();
        Sleep(100);
    }

   // system("cls");
    cout << "\n\n\tGAME OVER\n";
    cout << "\tFinal Score: " << score << "\n\n";

    return 0;
}
