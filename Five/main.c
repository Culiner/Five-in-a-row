#include "Head.h"

int data[H][L];  // 1为黑棋  2为白棋
int player;
int Chesscount;            //落子数
int Mode;
struct playerdata
{
    char name[20];
    int winnum;
    int nowchess;
} playkid[2];


void newgame()
{
    int i,j;
    for (i=0; i<H; i++)
    {
        for (j=0; j<L; j++)
        {
            data[i][j]=0;
        }
    }
    player=1;
    Chesscount=0;
}

void paint()
{
    int i,j;
    for (i=0; i<H; i++)
    {
        printf("%x ",H-i);
        for (j=0; j<L; j++)
        {
            if (data[i][j]==0)
            {
                if (i==H/2 && j==H/2) printf("╋");
                else if (i==3 && j==3) printf("╋");
                else if (i==11 && j==3) printf("╋");
                else if (i==3 && j==11) printf("╋");
                else if (i==11 && j==11) printf("╋");
                else if (i==0)
                {
                    if (j==0) printf("┌");
                    else if (j==L-1) printf("┐");
                    else printf("┬");
                }
                else if (i==H-1)
                {
                    if (j==0) printf("└");
                    else if (j==L-1) printf("┘");
                    else printf("┴");
                }
                else
                {
                    if (j==0) printf("├");
                    else if (j==L-1) printf("┤");
                    else printf("┼");
                }
            }
            else if(data[i][j]==B) printf("○");
            else if(data[i][j]==W) printf("●");
        }
        if (i==H/2-1)
        {
            if (playkid[0].nowchess==B) printf("       Black chessman: %-8.8s  Win:%d",playkid[0].name,playkid[0].winnum);
            else printf("       Black chessman: %-8s  Win:%d",playkid[1].name,playkid[1].winnum);
        }
        if (i==H/2+1)
        {
            if (playkid[0].nowchess==W) printf("       White chessman: %-8.8s  Win:%d",playkid[0].name,playkid[0].winnum);
            else printf("       White chessman: %-8s  Win:%d",playkid[1].name,playkid[1].winnum);
        }
        printf("\n");
        if (i==H-1)
        {
            printf("  ");
            for (j=0; j<L; j++) printf(" %c",j+'A');
            printf("\n\n");
        }
    }
}

int judge(int i,int j)
{
    int ii,jj,total;

    ii=i-1;    //左上与右下
    jj=j-1;
    total=1;
    if (ii>=0 && jj>=0 && data[ii][jj]==player)
    {
        total++;
        ii--;
        jj--;
        while (ii>=0 && jj>=0 && data[ii][jj]==player)
        {
            total++;
            ii--;
            jj--;
        }
        if (total>=5) return 1;
    }
    ii=i+1;
    jj=j+1;
    if (ii<=H-1 && jj<=L-1 && data[ii][jj]==player)
    {
        total++;
        ii++;
        jj++;
        while (ii<=H-1 && jj<=L-1 && data[ii][jj]==player)
        {
            total++;
            ii++;
            jj++;
        }
        if (total>=5) return 1;
    }

    ii=i-1;   //右上和左下
    jj=j+1;
    total=1;
    if (ii>=0 && jj<=L-1 && data[ii][jj]==player)
    {
        total++;
        ii=ii-1;
        jj=jj+1;
        while (ii>=0 && jj<=L-1 && data[ii][jj]==player)
        {
            total++;
            ii=ii-1;
            jj=jj+1;
        }
        if (total>=5) return 1;
    }
    ii=i+1;
    jj=j-1;
    if (ii<=H-1 && jj>=0 && data[ii][jj]==player)
    {
        total++;
        ii=ii+1;
        jj=jj-1;
        while (ii<=H-1 && jj>=0 && data[ii][jj]==player)
        {
            total++;
            ii=ii+1;
            jj=jj-1;
        }
        if (total>=5) return 1;
    }

    ii=i-1;   //竖
    jj=j;
    total=1;
    if (ii>=0 && data[ii][jj]==player)
    {
        total++;
        ii=ii-1;
        while (ii>=0 && data[ii][jj]==player)
        {
            total++;
            ii=ii-1;
        }
        if (total>=5) return 1;
    }
    ii=i+1;
    if (ii<=H-1 && data[ii][jj]==player)
    {
        total++;
        ii=ii+1;
        while (ii<=H-1 && data[ii][jj]==player)
        {
            total++;
            ii=ii+1;
        }
        if (total>=5) return 1;
    }

    ii=i;   //横
    jj=j+1;
    total=1;
    if (jj<=L-1 && data[ii][jj]==player)
    {
        total++;
        jj=jj+1;
        while (jj<=L-1 && data[ii][jj]==player)
        {
            total++;
            jj=jj+1;
        }
        if (total>=5) return 1;
    }
    jj=j-1;
    if (jj>=0 && data[ii][jj]==player)
    {
        total++;
        jj=jj-1;
        while (jj>=0 && data[ii][jj]==player)
        {
            total++;
            jj=jj-1;
        }
        if (total>=5) return 1;
    }

    return 0;
}

int playchess()
{
    extern COORD now;
    char c;
    int i,j;
    newgame();
    paint();

    now.X=16;
    now.Y=7;

    for (;;)
    {
        printf("○ is black chessman,● is white chessman\n Use WASD to move.Press Enter to confirm.Press Esc to quit.\n\n");
        if (player==W)
        {
            printf("It is time to white chessman.\n");
        }
        else if (player==B)
        {
            printf("It is time to black chessman.\n");
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),now);
        Input(&i,&j);

        data[i][j]=player;
        if (++Chesscount==H*L)
        {
            system("CLS");
            paint();
            printf("   Drawn game!\n");
            break;
        }
        if (judge(i,j)==0)
        {
            Clear();
            paint();
        }
        else
        {
            if (player==B)
            {
                if (playkid[0].nowchess==B)
                {
                    playkid[0].winnum++;
                    system("CLS");
                    paint();
                    printf("   Black chessman (%s) win!\n",playkid[0].name);
                }
                else
                {
                    playkid[1].winnum++;
                    system("CLS");
                    paint();
                    printf("   Black chessman (%s) win!\n",playkid[1].name);
                }
            }
            else if (player==W)
            {
                if (playkid[0].nowchess==W)
                {
                    playkid[0].winnum++;
                    system("CLS");
                    paint();
                    printf("   White chessman (%s) win!\n",playkid[1].name);
                }
                else
                {
                    playkid[1].winnum++;
                    system("CLS");
                    paint();
                    printf("   White chessman (%s) win!\n",playkid[1].name);
                }
            }
            break;
        }
        if (player==W) player=B;
        else if (player==B) player=W;
    }
    return 0;
}

int playchesswithAI()
{
    COORD coord = {0, 0};
    extern COORD now;
    char c;
    int i,j;
    int flog;
    newgame();
    paint();


    now.X=16;
    now.Y=7;

    for (;;)
    {
        printf("○ is black chessman,● is white chessman\n Use WASD to move.Press Enter to confirm.Press Esc to quit.\n\n");
        if (player==playkid[0].nowchess)
        {
            flog=Man;
            printf(" It is time to you.");
            if (player==B) printf("  ○      \n");
            else if (player==W) printf("  ●      \n");
        }
        else
        {
            flog=AI;
            //printf("It is time to Computer.\n");
        }

        if(flog==Man)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),now);
            Input(&i,&j);
            data[i][j]=player;
        }
        else if(flog==AI)
        {
            ChooseBestPlace(&i,&j);
            data[i][j]=player;
            now.X=(j+1)*2;
            now.Y=i;
        }

        if (++Chesscount==H*L)
        {
            system("CLS");
            paint();
            printf("   Drawn game!\n");
            break;
        }
        if (judge(i,j)==0)
        {
            Clear();
            paint();
        }
        else
        {
            if (playkid[0].nowchess==player)
            {
                playkid[0].winnum++;
                system("CLS");
                paint();
                printf("   You win!\n");
            }
            else
            {
                playkid[1].winnum++;
                system("CLS");
                paint();
                printf("   Computer win!\n");
            }
            break;
        }
        if (player==W) player=B;
        else if (player==B) player=W;
    }
    return 0;
}

int ModeChoose()
{
    int keyboard;
    int modenow=Twoman;
    COORD coord = {28, 10};

    printf("\n\n\n\n\n\n\n\n                               Which Mode ?\n\n                            ○ Human vs Human\n\n                            ○ Human vs Computer\n\n\n                    (Use W S to move.Press Enter to confirm.)\n\n\n\n                           Made by  Chen RanZhen\n\n                                    Deng GaoShan");

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    while(1)
    {
        keyboard=getch();
        if (keyboard=='s' || keyboard=='S')
        {
            modenow=AI;
            coord.X = 28;
            coord.Y = 12;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
        if(keyboard=='w' || keyboard=='W' )
        {
            modenow=Twoman;
            coord.X = 28;
            coord.Y = 10;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
        if (keyboard==13) return modenow;
    }
}

int main()
{
    char fname[20];
    char c;
    int n;

    Mode=ModeChoose();
    system("CLS");

    if (Mode==Twoman)
    {
        printf("\n\n\n\n\n\n\n\n                       What is First  player's name?\n\n                       ");
        gets(playkid[0].name);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n                       What is Second player's name?\n\n                       ");
        gets(playkid[1].name);
        system("CLS");
        playkid[0].nowchess=B;
        playkid[1].nowchess=W;
        playkid[0].winnum=0;
        playkid[1].winnum=0;
        Clear();
        for (;;)
        {
            playchess();
            printf("   Again?(Y/N) \n   ");
            c=getchar();
            getchar();
            if (c=='N' || c=='n')
            {
                if (playkid[0].winnum>playkid[1].winnum) printf("   %s is win!\n",playkid[0].name);
                else if (playkid[1].winnum>playkid[0].winnum) printf("   %s is win!\n",playkid[1].name);
                else printf("   It is Gobang a draw!\n");
                printf("\n   Press any key to quit.\n   ");
                getchar();
                break;
            }
            if (playkid[0].nowchess==B)
            {
                playkid[0].nowchess=W;
                playkid[1].nowchess=B;
            }
            else
            {
                playkid[1].nowchess=W;
                playkid[0].nowchess=B;
            }
            system("CLS");
        }
    }
    else if (Mode==AI)
    {
        printf("\n\n\n\n\n\n\n\n                       What is player's name?\n\n                       ");
        gets(playkid[0].name);
        system("CLS");
        strcpy(playkid[1].name,"Computer");
        printf("\n\n\n\n\n\n\n\n                       Are you first?(Y or any/N)\n\n                       ");
        c=getchar();
        getchar();
        if (c=='N'||c=='n')
        {
            playkid[0].nowchess=W;
            playkid[1].nowchess=B;
        }
        else
        {
            playkid[0].nowchess=B;
            playkid[1].nowchess=W;
        }
        playkid[0].winnum=0;
        playkid[1].winnum=0;
        system("CLS");

        for (;;)
        {
            playchesswithAI();
            printf("   Again?(Y/N) \n   ");
            c=getchar();
            getchar();
            if (c=='N' || c=='n')
            {
                if (playkid[0].winnum>playkid[1].winnum) printf("   You win!\n");
                else if (playkid[1].winnum>playkid[0].winnum) printf("   Computer win!\n");
                else printf("   It is Gobang a draw!\n");
                printf("\n   Press any key to quit.\n   ");
                getchar();
                break;
            }
            if (playkid[0].nowchess==B)
            {
                playkid[0].nowchess=W;
                playkid[1].nowchess=B;
            }
            else
            {
                playkid[1].nowchess=W;
                playkid[0].nowchess=B;
            }
            system("CLS");
        }
    }
    return 0;
}
