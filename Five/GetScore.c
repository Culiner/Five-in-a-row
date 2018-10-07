#include "Head.h"

//记录情况 有相邻的子数，是否被堵死。
typedef struct PointSituation
{
	int NeiSit[5];
} SITUATION;  //每个方向取5个子的情况


//得到一个方向的情况  并且存放在now数组里
void PointScore(int row,int col,int Player,const int Direction,const int newdata[15][15],SITUATION now[8])
{
	int i;
	const int DirAdd[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}}; //用来表示某一方向的row,colomn方向的单位增量。
	
	for(i=0;i<5;i++)
	{
		if( (row + (i+1)*DirAdd[Direction][0]) >= 0 && row + (i+1)*DirAdd[Direction][0] <H && col + (i+1)*DirAdd[Direction][1] >= 0 && col + (i+1)*DirAdd[Direction][1] <L ) //越界检查
		now[Direction].NeiSit[i]= newdata[ row + (i+1)*DirAdd[Direction][0] ][ col + (i+1)*DirAdd[Direction][1] ];   //将Direction 方向的棋子依次存入now数组对应位置。
		else
		now[Direction].NeiSit[i]= Player==1?2:1;
	}
}

int Merger(int i,int j,const int Player,SITUATION now[])
{
	int NSit[11];            //把两个方向的五个子合并成一路变成数组
	int p;
	char CSit[12];           //通过NSit过渡 最终变成CSit字符串形式。  字符串中 A代表己方 ？代表空格 X代表被堵

	NSit[5]=Player;
	CSit[11]='\0';

	for(p=0;p<5;p++)
	{
		NSit[4-p]=now[i].NeiSit[p];
	}
	for(p=0;p<5;p++)
	{
		NSit[6+p]=now[j].NeiSit[p];
	}                                          //合并成数组 

	for(p=0;p<11;p++)
	{
		CSit[p]='X';
		if(NSit[p]==Player)CSit[p]='A';
		if(NSit[p]==0)CSit[p]='?';
	}                                        

	CSit[11]='\0';                             //将数组转化成字符串

	// AAAAA    5000000 活5
	if(strstr(CSit,"AAAAA"))
	{
		return  5000000;
	}
	// ?AAAA?   1000000  活4
	if(strstr(CSit,"?AAAA?"))
	{
		return  1000000;
	}
	// ??AAA??  3000    活3
	if(strstr(CSit,"??AAA??"))
	{
		return  3000;
	}
	// AAA?A    2999    死4B
	if(strstr(CSit,"?AAA?A")||strstr(CSit,"A?AAA?"))
	{
		return  2999;
	}
	// AA?AA    2600    死4C
	if(strstr(CSit,"AA?AA"))
	{
		return  2600;
	}
	// AAAA?    2500    死4A
	if(strstr(CSit,"AAAA?")||strstr(CSit,"?AAAA"))
	{
		return  2500;
	}
	// ?A?AA?   800     死3B
	if(strstr(CSit,"?A?AA???")||strstr(CSit,"???AA?A?"))
	{
		return  800;
	}
	// ???AA??? 650     活2
	if(strstr(CSit,"???AA???"))
	{
		return  650;
	}
	// A??AA    600     死3C
	if(strstr(CSit,"A??AA?")||strstr(CSit,"?AA??A"))
	{
		return  600;
	}
	// A?A?A    550     死3D
	if(strstr(CSit,"A?A?A"))
	{
		return  550;
	}
	// AAA??    500     死3
	if(strstr(CSit,"AAA??")||strstr(CSit,"??AAA"))
	{
		return  500;
	}

	// ??A?A??  250     死2B
	if(strstr(CSit,"??A?A??"))
	{
		return  250;
	}
	// ?A??A?   200     死2C
	if(strstr(CSit,"?A??A?"))
	{
		return  200;
	}
	// AA???    150     死2A
	if(strstr(CSit,"AA???")||strstr(CSit,"???AA"))
	{
		return  150;
	}
	return 0;
}

int cmp(int *a,int *b)
{
	return *a>*b?*a-*b:*b-*a;
}
//将8个方向合并成4个方向 然后给分！
int ScoreSum(SITUATION now[],const int Player)
{
	int Score[4],ScoreSum;

	Score[0]=Merger(0,4,Player,now);
	Score[1]=Merger(1,5,Player,now);
	Score[2]=Merger(2,6,Player,now);
	Score[3]=Merger(3,7,Player,now);


	ScoreSum=Score[0]+Score[1]+Score[2]+Score[3];
	qsort(Score,4,sizeof(int),cmp);

	if( ((Score[0]>=2500 && Score[0]<=3000) && (Score[1]>=2500 && Score[1]<=3000) ) || (Score[1]>=2500 && Score[1]<=3000) && (Score[2]>=2500 && Score[2]<=3000)||(Score[2]>=2500 && Score[2]<=3000) && (Score[3]>=2500 && Score[3]<=3000))
	{
		ScoreSum+=300000;
	}

	return ScoreSum;
}


int JudgeEachScore(const int I,const int J,int newdata[15][15],int Player)
{
	SITUATION now[8];
	int i,j;
	int EightScore[8];
	int Sum;

	for(i=0; i<8; i++)
	{
		PointScore(I,J,Player,i,newdata,now);    // 收录该点8个方向的情况 i代表方向 正上方为0，顺时针依次加1.
	}

	Sum =  ScoreSum(now,Player);


	return Sum;

}
