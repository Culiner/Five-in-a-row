#include "Head.h"

extern const int data[H][L];   //当前的棋盘
extern const int player;         //当前的选手
static count=0;

int CaseData[200][3]= {0};   //  每行的 [0]为i   [1]为j    [2]为Score
int CaseCount=0;

int ifempty()
{
    int newdata[H][L],i,j;
    memcpy(newdata,data,sizeof(data)); //来一个新棋盘
    for (i=0; i<H; i++)
    {
        for (j=0; j<L; j++)
        {
            if (newdata[i][j]!=0) return 0;
        }
    }
    return 1;
}

void ClearAwayCaseData()
{
    int i;
    /*for (i=0; i<CaseCount; i++)
    {
        CaseData[i][0]=0;
        CaseData[i][1]=0;
        CaseData[i][2]=0;
    }*/
    memset(CaseData,0,sizeof(CaseData));
    CaseCount=0;
}

int ScoreJudge(int i,int j)
{
    int newdata[H][L];
    int IfAttack;
    int ComputerPlayer=player,HumanPlayer;
    int ComScore,HumScore;

    memcpy(newdata,data,sizeof(data));

    if (player==B) IfAttack=1;
    else if(player==W) IfAttack=-1;

    if (ComputerPlayer==B) HumanPlayer=W;
    else if (ComputerPlayer==W) HumanPlayer=B;

//   JudgeEachScore(i,j,newdata,ComputerPlayer);
//   JudgeEachScore(i,j,newdata,HumanPlayer);

    newdata[i][j]=ComputerPlayer;
    ComScore=JudgeEachScore(i,j,newdata,ComputerPlayer)+IfAttack;

    newdata[i][j]=HumanPlayer;
    HumScore=JudgeEachScore(i,j,newdata,HumanPlayer);

    if (ComScore>=2000000) return -1;

    //if (HumScore<=700) return ComScore;

    if (ComScore>HumScore) return ComScore;
    else return HumScore;
}

void ChooseBestPlace(int *I,int *J)
{
    int i,j;

    int ScoreNow;

    int RandCase;

    if (ifempty()==1)
    {
        *I=H/2;
        *J=L/2;
        return;
    }

    ClearAwayCaseData();

    for (i=0; i<H; i++)
    {
        for (j=0; j<L; j++)
        {
            if (data[i][j]==0)
            {
                ScoreNow=ScoreJudge(i,j);
                if (ScoreNow==-1)
                {
                    *I=i;
                    *J=j;
                    return;
                }
                if (CaseCount==0)
                {
                    CaseData[0][0]=i;
                    CaseData[0][1]=j;
                    CaseData[0][2]=ScoreNow;
                    CaseCount++;
                }
                else if (ScoreNow==CaseData[0][2])
                {
                    CaseData[CaseCount][0]=i;
                    CaseData[CaseCount][1]=j;
                    CaseData[CaseCount][2]=ScoreNow;
                    CaseCount++;
                }
                else if (ScoreNow>CaseData[0][2])
                {
                    ClearAwayCaseData();
                    CaseData[0][0]=i;
                    CaseData[0][1]=j;
                    CaseData[0][2]=ScoreNow;
                    CaseCount++;
                }
            }
        }
    }

    srand(time(0));
    RandCase=rand()%CaseCount;

    *I=CaseData[RandCase][0];
    *J=CaseData[RandCase][1];
    return;

}