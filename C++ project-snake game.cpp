#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fx, fy, score;
int tx[100], ty[100];
int n;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fx = rand() % width;
    fy = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls");
    cout<<"            WELCOME TO THE SNAKE GAME         \n";
    cout<<"Movement:\n a = RIGHT \n d = LEFT \n w = UP \n s = DOWN \n";
    cout << "Score:" << score << endl;
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fy && j == fx)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < n; k++)
                {
                    if (tx[k] == j && ty[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevx = tx[0];
    int prevy = ty[0];
    int prev2x, prev2y;
    tx[0] = x;
    ty[0] = y;
    for (int i = 1; i < n; i++)
    {
        prev2x = tx[i];
        prev2y = ty[i];
        tx[i] = prevx;
        ty[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
      gameOver = true;
    //if (x >= width) x = 0; else if (x < 0) x = width - 1;   //if want to make the snake go through walls
    //if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < n; i++)
        if (tx[i] == x && ty[i] == y)
            gameOver = true;

    if (x == fx && y == fy)
    {
        score += 10;
        fx = rand() % width;
        fy = rand() % height;
        n++;
    }

}
int main()
{
      Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}
