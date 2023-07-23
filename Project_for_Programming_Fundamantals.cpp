#include<iostream>
#include<windows.h>
#include<conio.h>
#define WIDTH 110
#define HEIGHT 27
#define WIN_WIDTH 83
#define MAX_WIDTH 84
#define MIN_WIDTH 2
#define MAX_HEIGHT 24
#define MIN_HEIGHT 2
int enemyX[3],enemyY[3];
int bullets[22][2];
int bIndex=0;
int score;
int enemyFlag[3];
int planPos=WIN_WIDTH/2;
char plan[3][5]={' ',' ','+',' ',' ',
                 '|','+','+','+','|',
		         '+','+','+','+','+'};

using namespace std;


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoxy(short x, short y)
{
	COORD pos ={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void borders()
{
	for(int i=0; i<=WIDTH; i++)
	{
		gotoxy(i,0);
		cout<<"*";
		gotoxy(i,HEIGHT);
		cout<<"*";
	}
	for(int i=1; i<=HEIGHT-1; i++)
	{
		gotoxy(0,i);
		cout<<"*";
		gotoxy(WIDTH,i);
		cout<<"*";
		gotoxy(WIN_WIDTH,i);
		cout<<"*";
	}
	
}
void genEnemy(int ind)
{
	enemyX[ind]= 3 + rand()%(WIN_WIDTH-8);
}
void drawEnemy(int ind)
{
	if(enemyFlag[ind] == true)
	{
		gotoxy(enemyX[ind],enemyY[ind]);
		cout<<"* *";
		gotoxy(enemyX[ind],enemyY[ind]+1);
		cout<<" * ";
	}
}
void eraseEnemy(int ind)
{
	if(enemyFlag[ind] == true)
	{
		gotoxy(enemyX[ind],enemyY[ind]);
		cout<<"   ";
		gotoxy(enemyX[ind],enemyY[ind]+1);
		cout<<"   ";
	}
}
void resetEnemy(int ind)
{
	eraseEnemy(ind);
	enemyY[ind]=2;
	genEnemy(ind);
}
void genBullets()
{
	bullets[bIndex][0]=20;
	bullets[bIndex][1]=planPos+2;
	bIndex++;
	if(bIndex == 21)
	{
		bIndex=0;
	}
}

void moveBullets()
{
	for(int i=0; i<22; i++)
	{
		if(bullets[i][0]>2)
		{
			bullets[i][0]-=1;
		}
		else 
		{
			bullets[i][0]=0;
		}
	}
}
void drawBullets()
{
	for(int i=0; i<22; i++)
	{
		gotoxy(bullets[i][1],bullets[i][0]);
		{
			cout<<".";
		}
	}
}
void eraseBullets()
{
	for(int i=0; i<22; i++)
	{
		gotoxy(bullets[i][1],bullets[i][0]);
		{
			cout<<" ";
		}
		
	}
}
void eraseBullet(int i)
{
	gotoxy(bullets[i][1],bullets[i][0]);
	{
		cout<<" ";
	}
}
void drawPlan()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<5; j++)
		{
			gotoxy(j+planPos,i+22);
			{
				cout<<plan[i][j];
			}
		}
	}
}
void erasePlan()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<5; j++)
		{
			gotoxy(j+planPos,i+22);
			{
				cout<<" ";
			}
		}
	}
}
int collision()
{
	if(enemyY[0]+2>=22)
	{
		if(enemyX[0]+2 - planPos >=-6 && enemyX[0]+2 - planPos<=6)
		{
			return 1;
		}
	}
	else 
	{
		return 0;
	}
    if(enemyY[1]+2>=22)
	{
		if(enemyX[1]+2 - planPos >=-6 && enemyX[1]+2 - planPos<=6)
		{
			return 1;
		}
	}
	else 
	{
		return 0;
	}
	if(enemyY[2]+2>=22)
	{
		if(enemyX[2]+2-planPos>=-1 && enemyX[2]+2 - planPos<= 6)
		{
			return 1;
		}
	}
	else return 0;
}
int hitBullet()
{
	for(int i=0; i<22; i++)
	{
		for(int j=0; j<2; j++)
		{
			if(bullets[i][j] != 0)
			{
				if(bullets[i][j] >= enemyY[0] && bullets[i][j] <= enemyY[0]+2)
				{
					if(bullets[i][j+1] >= enemyX[0] && bullets[i][j+1] <= enemyX[0]+2)
					{
						eraseBullet(i);
						bullets[i][j]=0;
						resetEnemy(0);
						return 1;
						
					}
				}
				else if(bullets[i][j] >= enemyY[1] && bullets[i][j] <= enemyY[1]+2)
				{
					if(bullets[i][j+1] >= enemyX[1] && bullets[i][j+1] <= enemyX[1]+2)
					{
						eraseBullet(i);
						bullets[i][j]=0;
						resetEnemy(1);
						return 1;
					}
				}
				else if(bullets[i][j] >= enemyY[2] && bullets[i][j] <= enemyY[2]+2)
				{
					if(bullets[i][j+1] >= enemyX[2] && bullets[i][j+1] <= enemyX[2]+2)
					{
						eraseBullet(i);
						bullets[i][j]=0;
						resetEnemy(2);
						return 1;
					}
				}
				
			}
		}
	}
}
void gameover()
{
	system("cls");
	gotoxy(48,7);
	cout<<"Space Shooter";
	gotoxy(44,9);
	cout<<"------------------------";
	gotoxy(44,10);
	cout<<"|";
	gotoxy(67,10);
	cout<<"|";
	gotoxy(44,11);
	cout<<"| Total Score = "<<score;
	gotoxy(67,11);
	cout<<"|";
	gotoxy(44,12);
	cout<<"| Press any to go menu";
	gotoxy(67,12);
	cout<<"|";
	gotoxy(44,13);
	cout<<"|";
	gotoxy(67,13);
	cout<<"|";
	gotoxy(44,14);
	cout<<"------------------------";
	getch();
	score=0;
}
void instructions()
{
	system("cls");
	cout<<endl<<endl<<endl;
	cout<<"\t\t------------------------- Instructions -------------------------"<<endl;
	cout<<endl;
	cout<<"\t\t----------------- To Shot bullet Press Space Bar ----------------"<<endl;
	cout<<"\t\t---------------- Go to Left by using left key or a --------------"<<endl;
	cout<<"\t\t--------------- Go to Right by using right key or d -------------"<<endl;
	cout<<"\t\t-------------- Press any key to go back to home !!!! ------------"<<endl;
	cout<<endl;
	cout<<"\t\t------------------------- Good Luck !!! ------------------------"<<endl;
	
	getch();
}
void updateScore()
{
	gotoxy(WIN_WIDTH+9,4);
	cout<<"Score "<<score;
}
void play()
{
	
	planPos=WIN_WIDTH/2;
	enemyY[0]=enemyY[1]=4;
	enemyFlag[0]=1;
	enemyFlag[1]=1;
	for(int i=0; i<22; i++)
	{
		bullets[i][0]=bullets[i][1]=0;
	}
	system("cls");
	borders();
	genEnemy(0);
	genEnemy(1);
	updateScore();
	gotoxy(WIN_WIDTH+4,8);cout<<" ----------------";
	gotoxy(WIN_WIDTH+4,10);cout<<" --SPACE SHOTER--";
	gotoxy(WIN_WIDTH+5,12);cout<<"----------------";
	gotoxy(WIN_WIDTH+5,14);cout<<" A key - Left  ";
	gotoxy(WIN_WIDTH+5,16);cout<<" D key - Right ";
	gotoxy(WIN_WIDTH+5,18);cout<<" Space - Shoot ";
	gotoxy(WIN_WIDTH+5,20);cout<<" Mode:Easy Game";
	gotoxy(WIN_WIDTH/2,HEIGHT/2);
	cout<<"Enter any key to play ";
	getch();
	gotoxy(WIN_WIDTH/2,HEIGHT/2);
	cout<<"                      ";
	while(1)
	{
		if(kbhit())
		{
			char ch=getch();
			if(ch == 'd'||ch == 'D'||ch == 77)
			{
				if(planPos<MAX_WIDTH-7)
				{
					planPos=planPos + 2;
				}
			}
			if(ch == 'a'||ch == 'A'||ch == 75)
			{	
				if(planPos>MIN_WIDTH)
				{
					planPos= planPos-2;
				}
			}
			if(ch == 32)
			{
				genBullets();
			}
			if(ch == 27)
			{
				break;
			}
			
		}
		drawPlan();
		drawEnemy(0);
		drawEnemy(1);
		drawBullets();
		if(collision() == 1)
		{
			gameover();
			break;
		}
		if(hitBullet()==1)
		{
			score++;
			updateScore();
		}
		Sleep(200);
		erasePlan();
		eraseEnemy(0);
		eraseEnemy(1);
		eraseBullets();
		moveBullets();
		if(enemyFlag[0] == 1)
		{
			enemyY[0]+=1;
		}
		if(enemyFlag[1] == 1)
		{
			enemyY[1]+=1;
		}
		if(enemyY[0] > HEIGHT-5)
		{
			resetEnemy(0);
		}
		if(enemyY[1] > HEIGHT-5)
		{
			resetEnemy(1);
		}
	}
}
void playHard()
{
	planPos=WIN_WIDTH/2;
	enemyY[0]=enemyY[1]=enemyY[2]=4;
	enemyFlag[0]=1;
	enemyFlag[1]=1;
	enemyFlag[2]=1;
	for(int i=0; i<22; i++)
	{
		bullets[i][0]=bullets[i][1]=0;
	}
	system("cls");
	borders();
	genEnemy(0);
	genEnemy(1);
	genEnemy(2);
	updateScore();
	gotoxy(WIN_WIDTH+4,8);cout<<" ----------------";
	gotoxy(WIN_WIDTH+4,10);cout<<" --SPACE SHOTER--";
	gotoxy(WIN_WIDTH+5,12);cout<<"----------------";
	gotoxy(WIN_WIDTH+5,14);cout<<" A key - Left  ";
	gotoxy(WIN_WIDTH+5,16);cout<<" D key - Right ";
	gotoxy(WIN_WIDTH+5,18);cout<<" Space - Shoot ";
	gotoxy(WIN_WIDTH+5,20);cout<<" Mode:HARD GAME";
	gotoxy(WIN_WIDTH/2,HEIGHT/2);
	cout<<"Enter any key to play ";
	getch();
	gotoxy(WIN_WIDTH/2,HEIGHT/2);
	cout<<"                      ";
	while(1)
	{
		if(kbhit())
		{
			char ch=getch();
			if(ch == 'd'||ch == 'D'||ch == 77)
			{
				if(planPos<MAX_WIDTH-4)
				{
					planPos=planPos + 2;
				}
			}
			if(ch == 'a'||ch == 'A'||ch == 75)
			{	
				if(planPos>MIN_WIDTH-4)
				{
					planPos= planPos-2;
				}
			}
			if(ch == 32)
			{
				genBullets();
			}
			if(ch == 27)
			{
				break;
			}
			
		}
		drawPlan();
		drawEnemy(0);
		drawEnemy(1);
		drawEnemy(2);
		drawBullets();
		if(collision() == 1)
		{
			gameover();
			break;
		}
		if(hitBullet()==1)
		{
			score++;
			updateScore();
		}
		Sleep(200);
		erasePlan();
		eraseEnemy(0);
		eraseEnemy(1);
		eraseEnemy(2);
		eraseBullets();
		moveBullets();
		if(enemyFlag[0] == 1)
		{
			enemyY[0]+=2;
		}
		if(enemyFlag[1] == 1)
		{
			enemyY[1]+=2;
		}
		if(enemyFlag[2] == 1)
		{
			enemyY[2]+=2;
		}
		if(enemyY[0] > HEIGHT-5)
		{
			resetEnemy(0);
		}
		if(enemyY[1] > HEIGHT-5)
		{
			resetEnemy(1);
		}
		if(enemyY[2] > HEIGHT-5)
		{
			resetEnemy(2);
		}
	}
}
main()
{
		setcursor(0,0); 
//	srand( (unsigned)time(NULL)); 
	do
	{
		system("cls");
				system("cls");
		gotoxy(WIN_WIDTH/2,8); cout<<" ++++++++++++++++++++++++++ "; 
		gotoxy(WIN_WIDTH/2,9); cout<<" |----> Space Shooter <---| "; 
		gotoxy(WIN_WIDTH/2,10); cout<<" ++++++++++++++++++++++++++";
		gotoxy(WIN_WIDTH/2,12); cout<<"1. Start Esay Game";
		gotoxy(WIN_WIDTH/2,13);cout<<"2. Start Hard Game";
		gotoxy(WIN_WIDTH/2,14); cout<<"3. Instructions";	 
		gotoxy(WIN_WIDTH/2,15); cout<<"4. Quit";
		gotoxy(WIN_WIDTH/2,17); cout<<"Select option: ";
		
		char op=getch();
		if(op == '1')
		{
			play();
		}
		else if(op == '2')
		{
			playHard();
		}
		else if(op == '3')
		{
			instructions();
		}
		else if(op == '4')
		{
			break;
		}
	}while(1);
}
