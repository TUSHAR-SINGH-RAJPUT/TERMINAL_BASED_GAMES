#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Direction states for paddle
enum GameState { RUNNING, LEFT, RIGHT };

GameState dir;
bool GAME_OVER = false;

// Game dimensions
int width = 40, height = 20;

// Ball variables
int x, y;      // position
int dx, dy;    // velocity

// Paddle variables
int px, py;

// Game stats
int score = 0;
int level = 1;
int speed = 120;   // lower = faster

class Bounce
{
public:
    // Initialize game variables
    void setup()
    {
        GAME_OVER = false;
        dir = RUNNING;

        // Ball starts in center
        x = width / 2;
        y = height / 2;
        dx = 1;
        dy = -1;

        // Paddle near bottom
        px = width / 2;
        py = height - 2;

        score = 0;
        level = 1;
        speed = 120;
    }

    // Draw game frame
    void draw()
    {
        system("cls");

        // Top wall
        for (int i = 0; i < width + 2; i++) cout << "_";
        cout << endl;

        // Game area
        for (int i = 0; i < height; i++)
        {
            cout << "|";
            for (int j = 0; j < width; j++)
            {
                if (i == py && j >= px && j < px + 4) cout << "=";   // Paddle
                else if (i == y && j == x) cout << "O";             // Ball
                else cout << " ";
            }
            cout << "|" << endl;
        }

        // Bottom wall
        for (int i = 0; i < width + 2; i++) cout << "_";

        cout << "\n\nSCORE: " << score << "  LEVEL: " << level;
    }

    // Handle keyboard input
    void input()
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'a') dir = LEFT;
            else if (ch == 'd') dir = RIGHT;
            else if (ch == 'x') GAME_OVER = true;
        }
    }

    // Game logic
    void logic()
    {
        // Paddle movement
        if (dir == LEFT && px > 0)
            px -= (score > 20 ? 2 : 1);
        else if (dir == RIGHT && px < width - 4)
            px += (score > 20 ? 2 : 1);

        // Ball movement
        x += dx;
        y += dy;

        // Wall collisions
        if (x <= 0 || x >= width - 1) dx = -dx;
        if (y <= 0) dy = -dy;

        // Paddle collision
        if (y == py - 1 && x >= px && x < px + 4)
        {
            dy = -dy;
            score += 10;
        }

        // Level progression
        if (score >= level * 100)
        {
            level++;
            speed = max(30, speed - 15);
        }

        // Game over condition
        if (y >= height - 1)
            GAME_OVER = true;
    }
};

int main()
{
    Bounce b;
    b.setup();

    while (!GAME_OVER)
    {
        b.draw();
        b.input();
        b.logic();
        Sleep(speed);   // control game speed
    }

    system("cls");
    cout << "GAME OVER\nFINAL SCORE: " << score;
    return 0;
}
