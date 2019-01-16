#include<iostream>
#include<iomanip>
#include<map>
#include<vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

/****************Weight**************/
#define W_m1 10000		//該空格是否能讓我方形成連六子 
#define W_r1 9000		//該空格是否能讓敵方形成連六子
#define W_m2 3000		//我方下了該空位後會有兩個空位可以形成連六子
#define W_r2 2000		//敵方下了該空位後會有兩個空位可以形成連六子
#define W_m3 40			//我方下了該空位後是否能形成半活四 WBBB. 
#define W_r3 30			//敵方下了該空位後是否能形成半活四
#define Wlive_m1 15		//我方活1
#define Wlive_r1 5		//敵方活1
#define Wlive_m2 100	//我方活2
#define Wlive_r2 80		//敵方活2
#define Wlive_m3 500	//我方活3
#define Wlive_r3 360	//敵方活3
#define Wlive_m4 4500	//我方活4
#define Wlive_r4 9000	//敵方活4
#define Wlive_m5 4500	//我方活5
#define Wlive_r5 6000	//敵方活5
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
	cout<<"我方為(B/W) : ";
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
		if(FIRST_STEP)  //黑方先下一顆 
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
			//雙方輪流下兩顆棋 
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
	
	//我方連六子 
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
	//敵方連六子 
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
	//我方下了該空位後會有兩個空位可以形成連六子
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
	//敵方下了該空位後會有兩個空位可以形成連六子
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
	//我方活1~活5 
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
	//敵方活1~活5 
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
	//我方半活3~活4 
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
	//敵方半活3~活4 
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
	
	
	
Exit_Check: ; //離開權重設定	
	//maxP.x =0;
//	maxP.y = 0;	
//	max_weight = 0;
	//找權重最大值 
	for(i = 0 ; i <19 ; i++)
	{
		for(j = 0 ; j <19 ; j++)
		{
			if(weight[i][j]>max_weight)
				max_weight = weight[i][j];
		}
	}

	if(max_weight!=0)
	{	//cout<<"權重不等於0\n";
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
	else	//權重都=0,選擇第一個未使用 
	{	//cout<<"權重等於0\n";
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
	cout<<"第"<<round<<"回合: 我方( "<<alphabet[maxP.x]<<" , "<< maxP.y+1<<" )\n" ;	
}

/****************init**************/
void init()
{	//cout<<"初始化..........\n";
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

/****************連六子**************/
bool getWeight_six(int x, int y,string who)
{
	int i , j , six = 0;
	bool change = false;
	
	if(checkerboard[x][y]==".")
	{
		checkerboard[x][y]=who; 
		change = true;
	}
	
	// --- 檢查 -
	//移動到最前方 
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
	
	// ---- 檢查 |
	//移動到最前方 
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
	// --- 檢查 ＼
	//移動到最前方 
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
	//	cout<<"＼\n";
	//	printweight();
		return true;	
	}
	else
		six = 0;
	// ---- 檢查 /
	//移動到最前方
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

/****************連六子:2空位**************/
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
	//代表下該空格會有兩個空格可以形成連6子 
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

/****************活1~5**************/
void getWeight_live(int x, int y,string who)
{
	int i, j,count=0;
	bool change = false;
	
	if(checkerboard[x][y]==".")
	{
		checkerboard[x][y]=who; //cout<<"change: "<<x<<" "<<y<<" ";
		change = true;
	}
	// --- 檢查 -
	//移動到最前方 
	i = x; j = y;
	for(;checkerboard[i][j]==who && j>=1  ; j--) ; 
	//cout<<i<<"--i---j---"<<j<<"---";
	if(checkerboard[i][j]==".")	//起始為活路
	{
		j++;
		for(;checkerboard[i][j]==who && j<17  ;j++,count++) ; 
		//cout<<"活:"<<count<<"\n";
		if(checkerboard[i][j]==".") //結束為活路
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
	// ---- 檢查 |
	//移動到最前方 
	i = x; j = y; count = 0;
	for(;checkerboard[i][j]==who && i>=1; i--) 	;
	if(checkerboard[i][j]==".")	//起始為活路
	{
		i++;
		for(;checkerboard[i][j]==who && i<17  ;i++,count++) ;
		if(checkerboard[i][j]==".") //結束為活路
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
	// --- 檢查 ＼
	//移動到最前方 
	i = x; j = y; count = 0;
	for(;checkerboard[i][j]==who && i>=1 && j>=1 ; i--,j--) ;
	if(checkerboard[i][j]==".")	//起始為活路
	{
		if(i<17 && j<17)
		{
			i++; j++;	//cout<<i<<" "<<j<<"---\n";	
		}
		for(;checkerboard[i][j]==who && i<17 && j<17; i++,j++,count++); 
		if(checkerboard[i][j]==".") //結束為活路
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
			//cout<<"＼\n";
		}
	}
	// --- 檢查 /
	//移動到最前方 
	i = x; j = y; count = 0;
	for(;checkerboard[i][j]==who && i>=1 && j<17 ; i--,j++) ;
	if(checkerboard[i][j]==".")	//起始為活路
	{
		if(i<17 && j<=17 && j>1)
		{
			i++; j--;	//cout<<i<<" "<<j<<"---\n";	
		}
		for(;checkerboard[i][j]==who && i<17 && j>=1; i++,j--,count++) ;
		if(checkerboard[i][j]==".") //結束為活路
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

/****************雙半活四、一半活四、一半活三**************/
void getWeight_doublelive(int x, int y,string who)
{
	int i, j, count=0;
	bool one_empty=false,change = false;
	int n_four=0;	// 計算有沒有兩個以上的半活四
	
	if(checkerboard[x][y]==".")
	{
		checkerboard[x][y]=who; //cout<<"change: "<<x<<" "<<y<<" ";
		change = true;
	}
	// --- 檢查 -
	//移動到最前方 
	i = x; j = y; one_empty=false;
	for(;checkerboard[i][j]==who && j>=1  ; j--) ;
	if(checkerboard[i][j]=="." && j>=1)	//表示起始為活路
		one_empty=true; 
	j++;
	
	for(;checkerboard[i][j]==who && j<17  ;j++,count++) ; //計算個數
	if(checkerboard[i][j]==".") count++;
	
	if(count == 4) //連四子
		//表示已一活路,但非兩端皆活路
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //連三子
		//表示已一活路,但非兩端皆活路		
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
	// ---- 檢查 |
	//移動到最前方 
	i = x; j = y; count = 0; one_empty=false; 
	for(;checkerboard[i][j]==who && i>=1; i--) 	;
	if(checkerboard[i][j]=="." && i>=1) //表示起始為活路
		one_empty=true;
	i++;
	for(;checkerboard[i][j]==who && i<17  ;i++,count++) ;
	if(checkerboard[i][j]==".") count++;
	if(count == 4) //連四子
		//表示已一活路,但非兩端皆活路
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //連三子
		//表示已一活路,但非兩端皆活路		
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
	// --- 檢查 ＼
	//移動到最前方 
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
	if(count == 4) //連四子
		//表示已一活路,但非兩端皆活路
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //連三子
		//表示已一活路,但非兩端皆活路		
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
	// --- 檢查 /
	//移動到最前方 
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
	
	if(count == 4) //連四子
		//表示已一活路,但非兩端皆活路
		if((one_empty && checkerboard[i][j]!=".") || ( !one_empty && checkerboard[i][j]==".")) 
			n_four++;
	if(count == 3) //連三子
		//表示已一活路,但非兩端皆活路		
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
	
	cout<<"敵方x (A-S) : ";
	cin>>x_s;
	
	if( alphabetChangeN.find(x_s) == alphabetChangeN.end())
	{
		cout<<"請輸入正確範圍 A-S : \n";
		return rivalStrategy();
	}
	
	cout<<"敵方y (1-19) : ";
	cin>>y;
	
	x = alphabetChangeN[x_s];	// the alphabet is directly changed to number,not need to sub 1 

	if(	x < 0 || x >18  || y < 0 || y >19 )
	{
		cout<<"請輸入正確位置:\n ";
		return rivalStrategy();
	}
	if(checkerboard[x][y-1] != ".")
	{
		cout<<"位置已被佔據，請重新輸入: \n";
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
				cout<<"------我方勝利!!!------\n";
			else
				cout<<"------對方勝利!!!------\n";
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



