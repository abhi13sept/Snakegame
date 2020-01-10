#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20; //width of the game
const int height = 20; //height of the game
int x, y, fx, fy, score;
int tx[100], ty[100];
int n;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN}; //basic directions
eDirecton dir; //Store the Directions after key hit
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2; //x-axis postioning of the snake
    y = height / 2; //y-axis postioning of the sanke
    fx = rand() % width; //x-axis postioning of the fruit
    fy = rand() % height; //y-axis postioning of the fruit
    score = 0;
}
void Draw()
{
    system("cls");
    cout<<"            WELCOME TO THE SNAKE GAME         \n";
    cout<<"Movement:\n a = RIGHT \n d = LEFT \n w = UP \n s = DOWN \n";
    cout << "Score:" << score << endl;
    for (int i = 0; i < width+2; i++)   //Drawing the boundaries for the game
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";  //Drawing the boundaries for the game
            if (i == y && j == x)
                cout << "O";   // Drawing Snake head 
            else if (i == fy && j == fx)
                cout << "F";   //Drawing the fruit
            else
            {
                bool print = false;
                for (int k = 0; k < n; k++)
                {
                    if (tx[k] == j && ty[k] == i)
                    {
                        cout << "o";  //Adding to sankes body if it eats a fruit
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";  //Drawing the boundaries for the game
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";  //Drawing the boundaries for the game
    cout << endl;

}
void Input()
{
    if (_kbhit())  //to get the keyboard a hit 
    {
        switch (_getch()) //Reading char and matching it
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
    switch (dir) //switch case for movement of the snake
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
    if (x > width || x < 0 || y > height || y < 0) //Gameover if snake hits the wall
      gameOver = true;
    //if (x >= width) x = 0; else if (x < 0) x = width - 1;   //if want to make the snake go through walls
    //if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < n; i++)
        if (tx[i] == x && ty[i] == y)
            gameOver = true;  //Gameover if it's head hits the tail

    if (x == fx && y == fy)
    {
        score += 10;   //increasing points everytime it eats a fruit 
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
