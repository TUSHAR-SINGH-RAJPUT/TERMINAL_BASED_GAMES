// Input-output stream library (for cout, cin)
#include <iostream>

// For _kbhit() and _getch() → keyboard input without Enter
#include <conio.h>

// For general utilities (not strictly required here)
#include <cstdlib>

// For time-related functions (not used yet)
#include <ctime>

// For Sleep() function (delay in milliseconds)
#include <windows.h>

using namespace std;

// Enum to represent game states / directions
enum GameState
{
    RUNNING, // No movement
    LEFT,    // Paddle moving left
    RIGHT    // Paddle moving right
};

// Variable to store current paddle direction
GameState dir;

// Flag to stop the game loop
bool GAME_OVER = false;

// Game object positions and dimensions
int x, y;        // Ball position (x → column, y → row)
int dx, dy;      // ball velocity
int px, py;      // Paddle position (px → column, py → row)
int width = 40;  // Width of the game area
int height = 20; // Height of the game area
int score = 0;   // score for the game

// Game class
class Bounce
{
public:
    // Initializes game variables
    void setup()
    {
        GAME_OVER = false; // Game starts running
        dir = RUNNING;     // Paddle initially not moving

        // Ball direction
        dx = 1;
        dy = -1;

        x = width / 2;  // Ball starts at center (x-axis)
        y = height / 2; // Ball starts at center (y-axis)

        py = height - 2; // Paddle near bottom wall
        px = width / 2;  // Paddle starts in middle
    }

    // Draws the game frame
    void draw()
    {
        system("cls"); // Clears console screen (Windows)

        // Draw top wall
        for (int i = 0; i < width + 2; i++)
            cout << "_";
        cout << endl;

        // Draw game area
        for (int i = 0; i < height; i++)
        {
            cout << "|"; // Left wall

            for (int j = 0; j < width; j++)
            {
                // Draw paddle (width = 4)
                if (i == py && j >= px && j < px + 4)
                    cout << "=";

                // Draw ball
                else if (i == y && j == x)
                    cout << "O";

                // Empty space
                else
                    cout << " ";
            }

            cout << "|"; // Right wall

            cout << endl;
        }

        // Draw bottom wall
        for (int i = 0; i < width + 2; i++)
            cout << "_";
        cout << endl;
        cout << "\n\nSCORE : " << score;
    }

    // Handles keyboard input
    void input()
    {
        // Checks if a key is pressed (non-blocking)
        if (_kbhit())
        {
            char ch = _getch(); // Reads key without waiting for Enter

            switch (ch)
            {
            case 'a': // Move paddle left
                dir = LEFT;
                break;

            case 'd': // Move paddle right
                dir = RIGHT;
                break;

            case 'x': // Exit game
                GAME_OVER = true;
                break;
            }
        }
    }

    // Game logic (movement handling)
    void logic()
    {
        // Paddle movement
        if (dir == LEFT && px > 0)
            px--;
        else if (dir == RIGHT && px < width - 4)
            px++;

        // Ball movement
        x += dx;
        y += dy;

        // Left & right wall collision
        if (x <= 0 || x >= width - 1)
            dx = -dx;

        // Top wall collision
        if (y <= 0)
            dy = -dy;

        // Paddle collision
        if (y == py - 1 && x >= px && x < px + 4)
        {
            dy = -dy;
            score += 10;
        }

        // Game over (ball missed paddle)
        if (y >= height - 1)
            GAME_OVER = true;
    }
};

int main()
{
    Bounce b; // Create game object

    system("cls"); // Clear screen once
    b.setup();     // Initialize game

    // Game loop
    while (GAME_OVER != true)
    {
        b.draw();  // Render game
        b.input(); // Take user input
        b.logic(); // Update game logic

        Sleep(100); // Delay for smooth animation
    }

    return 0; // Exit program
}

/// i want to add levels in init if scored is crossed by 100 the speed increases