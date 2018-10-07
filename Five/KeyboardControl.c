#include "Head.h"

COORD now;

/*清屏程序干净版*/
void Clear()
{
    COORD coord = {0, 0};
    //Set the position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void CheckCursorOverBorder()
{
    if(now.X<2)
    {
        now.X=30;
    }
    if(now.X>30)
    {
        now.X=2;
    }
    if(now.Y>14)
    {
        now.Y=0;
    }
    if(now.Y<0)
    {
        now.Y=14;
    }
}

int CheckIfChess(const int i,const int j)
{
    extern int data[15][15];

    return data[i][j];
}
void ScreenMove(int keyboard)
{
    switch(keyboard)
    {
    case'A':
    case'a':
        now.X-=2;
        break;

    case'W':
    case'w':
        now.Y--;
        break;

    case'D':
    case'd':
        now.X+=2;
        break;

    case'S':
    case's':
        now.Y++;
        break;
    default:
        break;
    }


    CheckCursorOverBorder();

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),now);

}

void Input(int *i,int*j)
{
    int keyboard;
    int flag=YES;               //检查是否能下子！


    while(1)
    {
        flag = NO;
        keyboard=getch();
        if (keyboard==13)
        {
            if( CheckIfChess(now.Y,now.X/2-1)==NO ) //如果没棋子
                flag=YES;
        }
        if(keyboard == 'w'|| keyboard == 'a'||keyboard =='s'||keyboard =='d'||keyboard =='W'||keyboard =='A'||keyboard =='S'||keyboard =='D')
        {
            ScreenMove(keyboard);
        }
        if(flag==YES)break;
    }

    /*	printf("Y=%d X=%d",now.Y,now.X);
    	getchar();
    */

    (*i)=now.Y  ;
    (*j)=now.X/2-1;

    return;
}
