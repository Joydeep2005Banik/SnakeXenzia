#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Direction dir;
bool gameover;
const int height = 20;
const int width = 20;
int tailx[100], taily[100];
int headx, heady, fruitx, fruity, score;
int tail_len;
void setup();
void draw();
void input();
void logic();
int main()
{
    char start;
    cout << "\t--------------------------------" << endl;
    cout << "\t\tSnake King" << endl;
    cout << "\t--------------------------------" << endl;
    cout << "Press 's' to start : ";
    cin >> start;
    if (start == 's')
    {
        setup();
        while (!gameover)
        {
            draw();
            input();
            logic();
            Sleep(30);
            system("cls");
            
        }
    }
    return 0;
}
void setup()
{
    gameover = false;
    dir = STOP;
    headx = width / 2;
    heady = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
}
void draw()
{
    system("cls");
    // upper border
    cout << "\t\t";
    for (int i = 0; i < width - 8; i++)
    {
        cout << "||";
    }
    cout << endl;
    // snake,fruit,space and sideborders
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // left border
            if (j == 0)
                cout << "\t\t||";
            // snake head
            if (i == heady && j == headx)
                cout << "O";
            // fruit
            else if (i == fruity && j == fruitx)
                cout << "*";
            // space snake tail
            else
            {
                bool print = false;
                for (int k = 0; k < tail_len; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                // space
                if(!print)
                cout<<" ";

            }
            //right border
            if(j==width-1)
            cout<<"||";
        }
        cout<<endl;
    }
    //lower border
    cout<<"\t\t";
    for(int i=0;i<width-8;i++)
    cout<<"||";
    cout<<endl;
    cout<<"\t\tScore:"<<score<<endl;
}
void input()
{
    if(_kbhit())
    switch(getch())
    {
        case 'a':
        dir=LEFT;
        break;
        case 'w':
        dir=UP;
        break;
        case 's':
        dir=DOWN;
        break;
        case 'd':
        dir=RIGHT;
        break;
        default:
        break;
    }
}
void logic()
{
    int prevx=tailx[0];
    int prevy=taily[0];
    int prev2x,prev2y;
    tailx[0]=headx;
    taily[0]=heady;
    for(int i=1;i<tail_len;i++)
    {
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }
    //direction logic
    switch(dir)
    {
        case LEFT:
        headx--;
        break;
        case RIGHT:
        headx++;
        break;
        case UP:
        heady--;
        break;
        case DOWN:
        heady++;
        break;
        default:
        break;
    }
    if(headx>=width)
    headx=0;
    else if(headx<0)
    headx=width-1;
    if(heady>=height)
    heady=0;
    else if(heady<0)
    heady=height-1;
    //snake biteitself
    for(int i=0;i<tail_len;i++)
    {
        if(tailx[i]==headx && taily[i]==heady)
        {
            gameover=true;
        }
    }
    //snake eat fruit
    if(headx==fruitx &&heady==fruity)
    {
        score+=10;
        fruitx=rand()%width;
        fruity=rand()%height;
        tail_len++;
    }
}