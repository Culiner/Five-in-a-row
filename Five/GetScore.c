#include "Head.h"

//��¼��� �����ڵ��������Ƿ񱻶�����
typedef struct PointSituation
{
	int NeiSit[5];
} SITUATION;  //ÿ������ȡ5���ӵ����


//�õ�һ����������  ���Ҵ����now������
void PointScore(int row,int col,int Player,const int Direction,const int newdata[15][15],SITUATION now[8])
{
	int i;
	const int DirAdd[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}}; //������ʾĳһ�����row,colomn����ĵ�λ������
	
	for(i=0;i<5;i++)
	{
		if( (row + (i+1)*DirAdd[Direction][0]) >= 0 && row + (i+1)*DirAdd[Direction][0] <H && col + (i+1)*DirAdd[Direction][1] >= 0 && col + (i+1)*DirAdd[Direction][1] <L ) //Խ����
		now[Direction].NeiSit[i]= newdata[ row + (i+1)*DirAdd[Direction][0] ][ col + (i+1)*DirAdd[Direction][1] ];   //��Direction ������������δ���now�����Ӧλ�á�
		else
		now[Direction].NeiSit[i]= Player==1?2:1;
	}
}

int Merger(int i,int j,const int Player,SITUATION now[])
{
	int NSit[11];            //���������������Ӻϲ���һ·�������
	int p;
	char CSit[12];           //ͨ��NSit���� ���ձ��CSit�ַ�����ʽ��  �ַ����� A������ ������ո� X������

	NSit[5]=Player;
	CSit[11]='\0';

	for(p=0;p<5;p++)
	{
		NSit[4-p]=now[i].NeiSit[p];
	}
	for(p=0;p<5;p++)
	{
		NSit[6+p]=now[j].NeiSit[p];
	}                                          //�ϲ������� 

	for(p=0;p<11;p++)
	{
		CSit[p]='X';
		if(NSit[p]==Player)CSit[p]='A';
		if(NSit[p]==0)CSit[p]='?';
	}                                        

	CSit[11]='\0';                             //������ת�����ַ���

	// AAAAA    5000000 ��5
	if(strstr(CSit,"AAAAA"))
	{
		return  5000000;
	}
	// ?AAAA?   1000000  ��4
	if(strstr(CSit,"?AAAA?"))
	{
		return  1000000;
	}
	// ??AAA??  3000    ��3
	if(strstr(CSit,"??AAA??"))
	{
		return  3000;
	}
	// AAA?A    2999    ��4B
	if(strstr(CSit,"?AAA?A")||strstr(CSit,"A?AAA?"))
	{
		return  2999;
	}
	// AA?AA    2600    ��4C
	if(strstr(CSit,"AA?AA"))
	{
		return  2600;
	}
	// AAAA?    2500    ��4A
	if(strstr(CSit,"AAAA?")||strstr(CSit,"?AAAA"))
	{
		return  2500;
	}
	// ?A?AA?   800     ��3B
	if(strstr(CSit,"?A?AA???")||strstr(CSit,"???AA?A?"))
	{
		return  800;
	}
	// ???AA??? 650     ��2
	if(strstr(CSit,"???AA???"))
	{
		return  650;
	}
	// A??AA    600     ��3C
	if(strstr(CSit,"A??AA?")||strstr(CSit,"?AA??A"))
	{
		return  600;
	}
	// A?A?A    550     ��3D
	if(strstr(CSit,"A?A?A"))
	{
		return  550;
	}
	// AAA??    500     ��3
	if(strstr(CSit,"AAA??")||strstr(CSit,"??AAA"))
	{
		return  500;
	}

	// ??A?A??  250     ��2B
	if(strstr(CSit,"??A?A??"))
	{
		return  250;
	}
	// ?A??A?   200     ��2C
	if(strstr(CSit,"?A??A?"))
	{
		return  200;
	}
	// AA???    150     ��2A
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
//��8������ϲ���4������ Ȼ����֣�
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
		PointScore(I,J,Player,i,newdata,now);    // ��¼�õ�8���������� i������ ���Ϸ�Ϊ0��˳ʱ�����μ�1.
	}

	Sum =  ScoreSum(now,Player);


	return Sum;

}
