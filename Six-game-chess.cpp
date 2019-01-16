#include<iostream>
#include<iomanip>
#include<map>
#include<vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

/****************Weight**************/
#define W_m1 10000		//�ӪŮ�O�_�����ڤ�Φ��s���l 
#define W_r1 9000		//�ӪŮ�O�_�����Ĥ�Φ��s���l
#define W_m2 3000		//�ڤ�U�F�ӪŦ��|����ӪŦ�i�H�Φ��s���l
#define W_r2 2000		//�Ĥ�U�F�ӪŦ��|����ӪŦ�i�H�Φ��s���l
#define W_m3 40			//�ڤ�U�F�ӪŦ��O�_��Φ��b���| WBBB. 
#define W_r3 30			//�Ĥ�U�F�ӪŦ��O�_��Φ��b���|
#define Wlive_m1 15		//�ڤ謡1
#define Wlive_r1 5		//�Ĥ謡1
#define Wlive_m2 100	//�ڤ謡2
#define Wlive_r2 80		//�Ĥ謡2
#define Wlive_m3 500	//�ڤ謡3
#define Wlive_r3 360	//�Ĥ謡3
#define Wlive_m4 4500	//�ڤ謡4
#define Wlive_r4 9000	//�Ĥ謡4
#define Wlive_m5 4500	//�ڤ謡5
#define Wlive_r5 6000	//�Ĥ謡5
#define Whelflive_m3 20
#define Whelflive_r3 15
#define Whelflive_m4_1 150
#define Whelflive_r4_1 50
#define Whelflive_m4_2 450
#define Whelflive_r4_2 350
/****************function**************/
void printCheckerboard();
void Strategy();
void rivalStrategy();
string judgeEnd();
void judge_printResult();
void init();
void printweight();
bool getWeight_six(int x, int y,string who);
void getWeight_six_2space(int x, int y,string who);
void getWeight_live(int x, int y,string who);
void getWeight_doublelive(int x, int y,string who);
/****************gobal variable**************/
string checkerboard[19][19];
int weight[19][19]={0};
int sameweight_x[361]={0};
int sameweight_y[361]={0};
int max_node = 0;
int max_weight = 0;
map<string,int> alphabetChangeN;	// alphabet is changed to number
string alphabet[19]={"A","B","C","D","E","F","G","H"
						,"I","J","K","L","M","N","O","P"
						,"Q","R","S"};
string me="B",rival="W";
bool END = false; 
int round = 0; 
				
struct position
{
	int x,y;
	
	position(){};
	position(int xx,int yy)
		:x(xx),y(yy)
	{}
	
};

//record the used chess
vector<position> ourTeam;
vector<position> RivalTeam;
position maxP;

int main()
{
	int i, j;
	bool FIRST_STEP = true;
	/****************judge:Black_White**************/
	cout<<"�ڤ謰(B/W) : ";
	cin>>me;
	
	if(me == "W")
		rival = "B";
		
	/****************init**************/
	for(i = 0 ; i < 19 ; i++)
	{	
		alphabetChangeN[alphabet[i]]=i;
		
		for(j = 0 ; j < 19 ; j++)
		{
			checkerboard[i][j] = ".";	
		}	
	}	

/****************playing chess**************/	
	for(;!END;)
	{	
		if(FIRST_STEP)  //�¤���U�@�� 
		{
			round++;
			
			if(me == "B") 
				Strategy();
			else
				rivalStrategy();	
		
			FIRST_STEP =false;	
		}
		else
		{
			round++;
			//������y�U������ 
			if(me == "B") 
			{
				/* first */
				rivalStrategy();		
				printCheckerboard();	
				judge_printResult();
				if(END) return 0;
				/* second */
				rivalStrategy();		
				printCheckerboard();	
				judge_printResult(); 
				if(END) return 0;
				/*** take turns ***/
				round++;
				/* first */
				Strategy();
				printCheckerboard();
				judge_printResult(); 
				if(END) return 0;	
				/* second */
				Strategy();
			}
			else
			{
				/* first */
				Strategy();
				printCheckerboard();
				judge_printResult();
				if(END) return 0;
				/* second */
				Strategy();
				printCheckerboard();
				judge_printResult(); 
				if(END) return 0;
				/*** take turns ***/
				round++;
				/* first */
				rivalStrategy();		
				printCheckerboard();	
				judge_printResult(); 
				if(END) return 0;
				/* second */
				rivalStrategy();	
			}
			
		}
		
		printCheckerboard();	
		judge_printResult();
		if(END) 
		{
			system("pause");
			return 0;
		}
		cout<<"round : "<<round<<"\n";
	}
	
	
	return 0;
}

/****************Our Strategy: 1 step**************/
void Strategy()
{

	int i=0,j=0,temp ;
	
	init();
	
	//�ڤ�s���l 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{	
			if(checkerboard[i][j] == ".")
			{	
				if(getWeight_six(i,j,me))	
				{
					goto Exit_Check;	
				} 
			}	
		}
	} 	
	//�Ĥ�s���l 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(checkerboard[i][j] == "." )
			{	
				if(getWeight_six(i,j,rival)) 
				{
					
					goto Exit_Check;	
				} 	
			}	
		}
	}
	//�ڤ�U�F�ӪŦ��|����ӪŦ�i�H�Φ��s���l
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(checkerboard[i][j] == "." )
			{	
				getWeight_six_2space(i,j,me);
			}	
		}
	}
	//�Ĥ�U�F�ӪŦ��|����ӪŦ�i�H�Φ��s���l
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(checkerboard[i][j] == "." )
			{	
				getWeight_six_2space(i,j,rival);
			}	
		}
	}
	//�ڤ謡1~��5 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(checkerboard[i][j] == "." )
			{	
				getWeight_live(i,j,me);
			}	
		}
	}
	//�Ĥ謡1~��5 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(checkerboard[i][j] == "." )
			{	
				getWeight_live(i,j,rival);
			}	
		}
	}
	//�ڤ�b��3~��4 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(checkerboard[i][j] == "." )
			{	
				getWeight_doublelive(i,j,me);
			}	
		}
	}
	//�Ĥ�b��3~��4 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(checkerboard[i][j] == "." )
			{	
				getWeight_doublelive(i,j,rival);
			}	
		}
	}
	
	
	
Exit_Check: ; //���}�v���]�w	
	//maxP.x =0;
//	maxP.y = 0;	
//	max_weight = 0;
	//���v���̤j�� 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(weight[i][j]>max_weight)
				max_weight = weight[i][j];
		}
	}

	if(max_weight!=0)
	{	//cout<<"�v��������0\n";
		for(i=0 ; i<19 ; i++)
		{
			for(j = 0 ; j <19 ; j++)
			{
				if(weight[i][j] == max_weight)
				{
					sameweight_x[max_node] = i ;
					sameweight_y[max_node] = j ;
					max_node++;
				}
			}
		}
		srand( time(NULL) );
		temp = rand() % (max_node);
		maxP.x = sameweight_x[temp];
		maxP.y = sameweight_y[temp];
	}
	else	//�v����=0,��ܲĤ@�ӥ��ϥ� 
	{	//cout<<"�v������0\n";
		for(i=0 ; i<19 ; i++)
		{
			for(j = 0 ; j <19 ; j++)
			{
				if(checkerboard[i][j] == ".")
				{	
					maxP.x = i;
					maxP.y = j;
				}
			}
		}
	}
	//cout<<maxP.x<<" "<<maxP.y<<" ----------maxP\n";
	//if(checkerboard[maxP.x][maxP.x] == ".")
		checkerboard[maxP.x][maxP.y] = me;	
	cout<<"��"<<round<<"�^�X: �ڤ�( "<<alphabet[maxP.x]<<" , "<< maxP.y+1<<" )\n" ;	
}

/****************init**************/
void init()
{	//cout<<"��l��..........\n";
	fill(sameweight_x,sameweight_x+361,0);
	fill(sameweight_y,sameweight_y+361,0);
	maxP.x = 0;
	maxP.y = 0; 
	max_weight =0;
	max_node = 0;
	for(int i = 0 ; i < 19 ; i++)
	{
		for(int j = 0 ; j < 19 ; j++)
		{
			weight[i][j] = 0;
		}
	}
}

/****************�s���l**************/
bool getWeight_six(int x, int y,string who)
{
	int i , j , six = 0;
	bool change = false;
	
	if(checkerboard[x][y]==".")
	{
		checkerboard[x][y]=who; 
		change = true;
	}
	
	// --- �ˬd -
	//���ʨ�̫e�� 
	i = x; j = y;
	for(;checkerboard[i][j]==who && j>=1  ; j--) 
		;
	j++;
	for(;checkerboard[i][j]==who && j<18  ;j++) 
		six++;
	if(six>=5 && change)
	{	cout<<"recor change: "<<x<<" "<<y<<"\n";
		checkerboard[x][y]=".";
		if(who == me)
		{
			weight[x][y] +=W_m1;		
		}		
		else
		{
			weight[x][y] +=W_r1;
		}
//		cout<<"-\n";
//		printweight();
		return true;	
	}
	else
		six = 0;
	
	// ---- �ˬd |
	//���ʨ�̫e�� 
	i = x; j = y;
	for(;checkerboard[i][j]==who && i>=1; i--) 
		;
	i++; 
	for(;checkerboard[i][j]==who && i<18  ;i++) 
		six++; 
	if(six>=5 && change)
	{
		checkerboard[x][y]=".";
		
		if(who == me)
		{
			weight[x][y] +=W_m1;
		//	cout<<"me ::: weight["<<x<<"]["<<y<<"]:"<<weight[x][y]<<"\n";
		}		
		else
		{
			weight[x][y] +=W_r1;
		//	cout<<"r ::: weight["<<x<<"]["<<y<<"]:"<<weight[x][y]<<"\n";
		}
//		cout<<"|\n";
//		printweight();
		return true;	
	}
	else
		six = 0;
	// --- �ˬd �@
	//���ʨ�̫e�� 
	i = x; j = y;
	for(;checkerboard[i][j]==who && i>=1 && j>=1 ; i--,j--) 
		;
	if(i<18 && j<18)
	{
		i++; j++;	//cout<<i<<" "<<j<<"---\n";	
	}
	for(;checkerboard[i][j]==who && i<18 && j<18; i++,j++) 
		six++;
	if(six>=4 && change )
	{	//cout<<"recor change: "<<x<<" "<<y<<" ";
		checkerboard[x][y]=".";
		if(who == me)
		{
			weight[x][y] +=W_m1;
		//	cout<<"me ::: weight["<<x<<"]["<<y<<"]:"<<weight[x][y]<<"\n";
		}		
		else
		{
			weight[x][y] +=W_r1;
		//	cout<<"r ::: weight["<<x<<"]["<<y<<"]:"<<weight[x][y]<<"\n";
		}
	//	cout<<"�@\n";
	//	printweight();
		return true;	
	}
	else
		six = 0;
	// ---- �ˬd /
	//���ʨ�̫e��
	i = x; j = y;
	for(;checkerboard[i][j]==who && i>=1 && j<18 ; i--,j++) 
		;
	if(i<18 && j<=18 && j>0)
	{
		i++; j--;	//cout<<i<<" "<<j<<"---\n";	
	}
	for(;checkerboard[i][j]==who && i<18 && j>=1; i++,j--) 
		six++;
	if(six>=4 && change )
	{	
		checkerboard[x][y]=".";
		if(who == me)
		{
			weight[x][y] +=W_m1;
		}		
		else
		{
			weight[x][y] +=W_r1;
		}
	//	cout<<"//\n";
	//	printweight();
		return true;	
	}
	else
		six = 0;
	if(change)
		checkerboard[x][y]=".";
	return false;	
	if(change && six<4)
		checkerboard[x][y]=".";
	return false;	
		
}

/****************�s���l:2�Ŧ�**************/
void getWeight_six_2space(int x, int y,string who)
{
	int i,j,pi,pj,range,tempj;
	int win_count = 0;
	bool change = false;
	
	if(checkerboard[x][y]==".")
	{
		checkerboard[x][y]=who; //cout<<"change: "<<x<<" "<<y<<" ";
		change = true;
	}
	for(pi=x , range = 4 ; pi>0 && range>0 ; pi--,range--) ;
	for(pj=y , range = 4 ; pj>0 && range>0 ; pj--,range--) ;
	
	tempj = pj;
	for(i = 1 ; i<=11 && pi<=18 && win_count <=1 ; i++ , pi++) 
	{
		for(j = 1 ,pj=tempj ; j<=11 && pj<=18 && win_count <=1;j++,pj++)
		{
			if(checkerboard[x][y]==".")
			{
				if(getWeight_six( pi, pj, who))
				{
					win_count++;
					if(who == me)
						weight[pi][pj] -=W_m1;
					else
						weight[pi][pj] -=W_r1;
				}
			}
		}
	}
	//�N��U�ӪŮ�|����ӪŮ�i�H�Φ��s6�l 
	if(win_count>=2)
	{	//cout<<"wincount >2\n";
		if(who == me)
		{
			weight[x][y] += W_m2;
		}
			
		else
		{
			weight[x][y] += W_r2;
		}
			
	printweight();
	}
	
	if(win_count==1)
	{	cout<<"wincount ====1\n";
		if(who == me)
		{
			weight[x][y] += W_m3;
		}
			
		else
		{
			weight[x][y] += W_r3;
		}
		printweight();
	}
	
	if(change)
		checkerboard[x][y]=".";
	
}

/****************��1~5**************/
void getWeight_live(int x, int y,string who)
{
	int i, j,count=0;
	bool change = false;
	
	if(checkerboard[x][y]==".")
	{
		checkerboard[x][y]=who; //cout<<"change: "<<x<<" "<<y<<" ";
		change = true;
	}
	// --- �ˬd -
	//���ʨ�̫e�� 
	i = x; j = y;
	for(;checkerboard[i][j]==who && j>=1  ; j--) ; 
	//cout<<i<<"--i---j---"<<j<<"---";
	if(checkerboard[i][j]==".")	//�_�l������
	{
		j++;
		for(;checkerboard[i][j]==who && j<17  ;j++,count++) ; 
		//cout<<"��:"<<count<<"\n";
		if(checkerboard[i][j]==".") //����������
		{
			if(count==5)
			{	
				if(who==me)
						weight[x][y] +=Wlive_m5;
				else
						weight[x][y] +=Wlive_r5;
			}
			if(count==4)
			{
				if(who==me)
						weight[x][y] +=Wlive_m4;
				else
						weight[x][y] +=Wlive_r4;
			}
			if(count==3)
			{
				if(who==me)
						weight[x][y] +=Wlive_m3;
				else
						weight[x][y] +=Wlive_r3;
			}
			if(count==2)
			{
				if(who==me)
						weight[x][y] +=Wlive_m2;
				else
						weight[x][y] +=Wlive_r2;
			}
			if(count==1)
			{
				if(who==me)
						weight[x][y] +=Wlive_m1;
				else
						weight[x][y] +=Wlive_r1;
			}
		//	cout<<"-";
		//	printweight();
		} 
	} 
	// ---- �ˬd |
	//���ʨ�̫e�� 
	i = x; j = y; count = 0;
	for(;checkerboard[i][j]==who && i>=1; i--) 	;
	if(checkerboard[i][j]==".")	//�_�l������
	{
		i++;
		for(;checkerboard[i][j]==who && i<17  ;i++,count++) ;
		if(checkerboard[i][j]==".") //����������
		{
			if(count==5)
			{	
				if(who==me)
						weight[x][y] +=Wlive_m5;
				else
						weight[x][y] +=Wlive_r5;
			}
			if(count==4)
			{
				if(who==me)
						weight[x][y] +=Wlive_m4;
				else
						weight[x][y] +=Wlive_r4;
			}
			if(count==3)
			{
				if(who==me)
						weight[x][y] +=Wlive_m3;
				else
						weight[x][y] +=Wlive_r3;
			}
			if(count==2)
			{
				if(who==me)
						weight[x][y] +=Wlive_m2;
				else
						weight[x][y] +=Wlive_r2;
			}
			if(count==1)
			{
				if(who==me)
						weight[x][y] +=Wlive_m1;
				else
						weight[x][y] +=Wlive_r1;
			}
		//	cout<<"|\n";
		}
	}
	// --- �ˬd �@
	//���ʨ�̫e�� 
	i = x; j = y; count = 0;
	for(;checkerboard[i][j]==who && i>=1 && j>=1 ; i--,j--) ;
	if(checkerboard[i][j]==".")	//�_�l������
	{
		if(i<17 && j<17)
		{
			i++; j++;	//cout<<i<<" "<<j<<"---\n";	
		}
		for(;checkerboard[i][j]==who && i<17 && j<17; i++,j++,count++); 
		if(checkerboard[i][j]==".") //����������
		{
			if(count==5)
			{	
				if(who==me)
						weight[x][y] +=Wlive_m5;
				else
						weight[x][y] +=Wlive_r5;
			}
			if(count==4)
			{
				if(who==me)
						weight[x][y] +=Wlive_m4;
				else
						weight[x][y] +=Wlive_r4;
			}
			if(count==3)
			{
				if(who==me)
						weight[x][y] +=Wlive_m3;
				else
						weight[x][y] +=Wlive_r3;
			}
			if(count==2)
			{
				if(who==me)
						weight[x][y] +=Wlive_m2;
				else
						weight[x][y] +=Wlive_r2;
			}
			if(count==1)
			{
				if(who==me)
						weight[x][y] +=Wlive_m1;
				else
						weight[x][y] +=Wlive_r1;
			}
			//cout<<"�@\n";
		}
	}
	// --- �ˬd /
	//���ʨ�̫e�� 
	i = x; j = y; count = 0;
	for(;checkerboard[i][j]==who && i>=1 && j<17 ; i--,j++) ;
	if(checkerboard[i][j]==".")	//�_�l������
	{
		if(i<17 && j<=17 && j>1)
		{
			i++; j--;	//cout<<i<<" "<<j<<"---\n";	
		}
		for(;checkerboard[i][j]==who && i<17 && j>=1; i++,j--,count++) ;
		if(checkerboard[i][j]==".") //����������
		{
			if(count==5)
			{	
				if(who==me)
						weight[x][y] +=Wlive_m5;
				else
						weight[x][y] +=Wlive_r5;
			}
			if(count==4)
			{
				if(who==me)
						weight[x][y] +=Wlive_m4;
				else
						weight[x][y] +=Wlive_r4;
			}
			if(count==3)
			{
				if(who==me)
						weight[x][y] +=Wlive_m3;
				else
						weight[x][y] +=Wlive_r3;
			}
			if(count==2)
			{
				if(who==me)
						weight[x][y] +=Wlive_m2;
				else
						weight[x][y] +=Wlive_r2;
			}
			if(count==1)
			{
				if(who==me)
						weight[x][y] +=Wlive_m1;
				else
						weight[x][y] +=Wlive_r1;
			}
			//cout<<"/";
		//	printweight();
		} 
	}
	if(change)
		checkerboard[x][y]=".";
}

/****************���b���|�B�@�b���|�B�@�b���T**************/
void getWeight_doublelive(int x, int y,string who)
{
	int i, j, count=0;
	bool one_empty=false,change = false;
	int n_four=0;	// �p�⦳�S����ӥH�W���b���|
	
	if(checkerboard[x][y]==".")
	{
		checkerboard[x][y]=who; //cout<<"change: "<<x<<" "<<y<<" ";
		change = true;
	}
	// --- �ˬd -
	//���ʨ�̫e�� 
	i = x; j = y; one_empty=false;
	for(;checkerboard[i][j]==who && j>=1  ; j--) ;
	if(checkerboard[i][j]=="." && j>=1)	//��ܰ_�l������
		one_empty=true; 
	j++;
	
	for(;checkerboard[i][j]==who && j<17  ;j++,count++) ; //�p��Ӽ�
	if(checkerboard[i][j]==".") count++;
	
	if(count == 4) //�s�|�l
		//��ܤw�@����,���D��ݬҬ���
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //�s�T�l
		//��ܤw�@����,���D��ݬҬ���		
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
		{
			if(who==me)
					weight[x][y] +=Whelflive_m3;
			else
					weight[x][y] +=Whelflive_r3;
		}
	if(n_four >=2)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_2;
		else
				weight[x][y] +=Whelflive_r4_2;
	}
	if(n_four ==1)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_1;
		else
				weight[x][y] +=Whelflive_r4_1;
	}
	// ---- �ˬd |
	//���ʨ�̫e�� 
	i = x; j = y; count = 0; one_empty=false; 
	for(;checkerboard[i][j]==who && i>=1; i--) 	;
	if(checkerboard[i][j]=="." && i>=1) //��ܰ_�l������
		one_empty=true;
	i++;
	for(;checkerboard[i][j]==who && i<17  ;i++,count++) ;
	if(checkerboard[i][j]==".") count++;
	if(count == 4) //�s�|�l
		//��ܤw�@����,���D��ݬҬ���
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //�s�T�l
		//��ܤw�@����,���D��ݬҬ���		
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
		{
			if(who==me)
					weight[x][y] +=Whelflive_m3;
			else
					weight[x][y] +=Whelflive_r3;
		}
	if(n_four >=2)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_2;
		else
				weight[x][y] +=Whelflive_r4_2;
	}
	if(n_four ==1)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_1;
		else
				weight[x][y] +=Whelflive_r4_1;
	}
	// --- �ˬd �@
	//���ʨ�̫e�� 
	i = x; j = y; count = 0; one_empty=false; 
	for(;checkerboard[i][j]==who && i>=1 && j>=1 ; i--,j--) ;
	if(checkerboard[i][j]=="." && i>=1 && j >=1)
		one_empty=true;
	if(i<17 && j<17)
	{
		i++; j++;	
	}
	for(;checkerboard[i][j]==who && i<17 && j<17; i++,j++,count++); 	
	if(checkerboard[i][j]==".") count++;
	if(count == 4) //�s�|�l
		//��ܤw�@����,���D��ݬҬ���
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //�s�T�l
		//��ܤw�@����,���D��ݬҬ���		
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
		{
			if(who==me)
					weight[x][y] +=Whelflive_m3;
			else
					weight[x][y] +=Whelflive_r3;
		}
	if(n_four >=2)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_2;
		else
				weight[x][y] +=Whelflive_r4_2;
	}
	if(n_four ==1)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_1;
		else
				weight[x][y] +=Whelflive_r4_1;
	}
	// --- �ˬd /
	//���ʨ�̫e�� 
	i = x; j = y; count = 0; one_empty=false; 
	for(;checkerboard[i][j]==who && i>=1 && j<17 ; i--,j++) ;
	if(checkerboard[i][j]=="." && i>=1 && j <17)//
		one_empty=true;
	if(i<17 && j<=17 && j>1)
	{
		i++; j--;		
	}
	for(;checkerboard[i][j]==who && i<17 && j>=1; i++,j--,count++) ;
	if(checkerboard[i][j]==".") count++;
	
	if(count == 4) //�s�|�l
		//��ܤw�@����,���D��ݬҬ���
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //�s�T�l
		//��ܤw�@����,���D��ݬҬ���		
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
		{
			if(who==me)
					weight[x][y] +=Whelflive_m3;
			else
					weight[x][y] +=Whelflive_r3;
		}
	if(n_four >=2)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_2;
		else
				weight[x][y] +=Whelflive_r4_2;
	}
	if(n_four ==1)
	{
		if(who==me)
				weight[x][y] +=Whelflive_m4_1;
		else
				weight[x][y] +=Whelflive_r4_1;
	}
	if(change)
		checkerboard[x][y]=".";
}
/****************print Current weight**************/
void printweight()
{
	int i , j ;
	for(int i = 0 ; i < 19; i++)
	{
		for(int j = 0 ; j < 19 ; j++)
		{
			cout<<weight[i][j]<<" ";
		}
		cout<<"\n";
	}
}
/****************rival Strategy: 1 step**************/
void rivalStrategy()
{
	int x,y;
	string x_s;
	
	cout<<"�Ĥ�x (A-S) : ";
	cin>>x_s;
	
	if( alphabetChangeN.find(x_s) == alphabetChangeN.end())
	{
		cout<<"�п�J���T�d�� A-S : \n";
		return rivalStrategy();
	}
	
	cout<<"�Ĥ�y (1-19) : ";
	cin>>y;
	
	x = alphabetChangeN[x_s];	// the alphabet is directly changed to number,not need to sub 1 

	if(	x < 0 || x >18  || y < 0 || y >19 )
	{
		cout<<"�п�J���T��m:\n ";
		return rivalStrategy();
	}
	if(checkerboard[x][y-1] != ".")
	{
		cout<<"��m�w�Q���ڡA�Э��s��J: \n";
		return rivalStrategy();
	}
	checkerboard[x][y-1] = rival;
	RivalTeam.push_back(position(x,y-1));
	
	return;	
}

/****************judgeEnd: win / lose / continue**************/
string judgeEnd()
{
	//me
	int r[19][19]={0};   
	int c[19][19]={0};
	int v[19][19]={0};
	int iv[19][19]={0};	
	//rival
	int rr[19][19]={0};   
	int rc[19][19]={0};
	int rv[19][19]={0};
	int riv[19][19]={0};
	
	for(int i=0;i<19;i++)
	{
		for(int j=0;j<19;j++)
		{
			//me
			if(checkerboard[i][j]=="."||checkerboard[i][j]==rival)
			{
			
				r[i][j]=0;	c[i][j]=0;	v[i][j]=0;	iv[i][j]=0;
			}
			else
			{
				if(i>=1) r[i][j]=r[i-1][j]+1;
				else	r[i][j]=1;
				if(j>=1)	c[i][j]=c[i][j-1]+1;
				else	c[i][j]=1;
				if(i>=1||j>=1) v[i][j]=v[i-1][j-1]+1;			
				else v[i][j]=1;
				if(i<18||j<18) iv[i][j]=iv[i-1][j+1]+1;	
				else iv[i][j]=1;	
				
			}
			if(r[i][j]==6||c[i][j]==6||v[i][j]==6||iv[i][j]==6)
				return "win";
			
			//rival
			if(checkerboard[i][j]=="."||checkerboard[i][j]==me)
			{
			
				rr[i][j]=0;
				rc[i][j]=0;
				rv[i][j]=0;
				riv[i][j]=0;
			}
			else
			{
				if(i>=1) rr[i][j]=rr[i-1][j]+1;
				else	rr[i][j]=1;
				if(j>=1)	rc[i][j]=rc[i][j-1]+1;
				else	rc[i][j]=1;
				if(i>=1||j>=1) rv[i][j]=rv[i-1][j-1]+1;			
				else rv[i][j]=1;
				if(i<18||j<18) riv[i][j]=riv[i-1][j+1]+1;	
				else riv[i][j]=1;	
				
			}
			if(rr[i][j]==6||rc[i][j]==6||rv[i][j]==6||riv[i][j]==6)
				return "lose";
		}
	}
	
	return "continue";

}

/****************judge & print result**************/
void judge_printResult()
{
		if(judgeEnd() !="continue")
		{
			if(judgeEnd() =="win")
				cout<<"------�ڤ�ӧQ!!!------\n";
			else
				cout<<"------���ӧQ!!!------\n";
			END = true;
		}
}


/****************print Current Checkerboard**************/
void printCheckerboard()
{
	int i , j ;
	cout<<setw(3)<<" "<<setw(3)<<"1"<<setw(3)<<"2"
	    <<setw(3)<<"3"<<setw(3)<<"4"<<setw(3)<<"5"
	    <<setw(3)<<"6"<<setw(3)<<"7"<<setw(3)<<"8"
	    <<setw(3)<<"9"<<setw(3)<<"10"<<setw(3)<<"11"
	    <<setw(3)<<"12"<<setw(3)<<"13"<<setw(3)<<"14"
	    <<setw(3)<<"15"<<setw(3)<<"16"<<setw(3)<<"17"
	    <<setw(3)<<"18"<<setw(3)<<"19"<<"\n";
	
	for(i = 0 ; i < 19 ; i++)
	{
		cout<<setw(3)<<alphabet[i];
		
		for(j = 0 ; j < 19 ; j++)
		{
			cout<<setw(3)<<checkerboard[i][j];
		}
		cout<<"\n";
	}
}



