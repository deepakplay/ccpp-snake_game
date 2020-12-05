#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#define X 65
#define Y 20

int sx=18, sy=10, life=3, len=2 , fx=0, fy=0;
int game=1, score=0, catch=1;
int tailx[25], taily[25], tempx[25], tempy[25];
char grid[X][Y];
enum dir{LEFT, RIGHT, UP, DOWN}move;

void setgrid();
void disgrid();
void food();
void tail();

int main()
{
    for(int i=0;i<=25;i++){
        tailx[i]=10;
        taily[i]=10;
        tempx[i]=10;
        tempy[i]=10;
    }
	
	setgrid();
	food();
	disgrid();
	system("pause>nul");
	while(life){
		if(game==0){
			setgrid();
			life--;
		}
		game=1;
		sx=18;
		sy=10;
		move=RIGHT;
		while(game){
			if(life==0)
				break;
			if(_kbhit()){
				switch(_getch()){
					case 'w':
					case 'W':{
						if(move==RIGHT||move==LEFT)
							move=UP;
						break;
					}
					case 's':
					case 'S':{
						if(move==RIGHT||move==LEFT)
							move=DOWN;
						break;
					}
					case 'a':
					case 'A':{
						if(move==UP||move==DOWN)
							move=LEFT;
						break;
					}
					case 'd':
					case 'D':{
						if(move==UP||move==DOWN)
							move=RIGHT;
						break;
					}
					case 'x':
					case 'X':{
						system("pause>nul");
					}
				}
			}
			switch(move){
				case UP:{
					if(sy>1){
						grid[sx][sy] = ' ';
						sy--;
						grid[sx][sy] = '^';
						tailx[0] = sx;
						taily[0] = sy+1;
					}else{
						game=0;

						for(int i=0;i<=len+1;i++){
							tailx[i]=sx;
							taily[i]=sy;
						}
					}
					break;
				}
				case DOWN:{
					if(sy<Y-1){
						grid[sx][sy] = ' ';
						sy++;
						grid[sx][sy] = 'v';
						tailx[0] = sx;
						taily[0] = sy-1;
					}else{
						game=0;
						for(int i=0;i<=len+1;i++){
							tailx[i]=sx;
							taily[i]=sy;
						}
					}
					break;
				}
				case RIGHT:{
					if(sx<X-1){
						grid[sx][sy] = ' ';
						sx++;
						grid[sx][sy] = '>';
						tailx[0] = sx-1;
						taily[0] = sy;
					}else{
						game=0;
						for(int i=0;i<=len+1;i++){
							tailx[i]=sx;
							taily[i]=sy;
						}
					}
					break;
				}
				case LEFT:{
					if(sx>1){
						grid[sx][sy] = ' ';
						sx--;
						grid[sx][sy] = '<';
						tailx[0] = sx+1;
						taily[0] = sy;
					}else{
						game=0;
						for(int i=0;i<=len+1;i++){
							tailx[i]=sx;
							taily[i]=sy;
						}
					}
					break;
				}
			}
			if(sx==fx && sy==fy){
				score+=5;
				if(catch==3){
					len+=1;
					catch=0;
				}
				catch++;
				grid[fx][fy]=' ';
				food();
			}
			tail();
			disgrid();
			Sleep(60);
		}
	}
	system("cls");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t Game Over!!!!");
	printf("\n\t\t\t\tYour Score : %d",score);
	system("pause>nul");
	return 0;
}

void tail(){
//////////////////////////////////////////////BUG
	tempx[0]=tailx[0];
	tempy[0]=taily[0];
	for(int i=1;i<=len+1;i++){
		tempx[1]=tailx[i];
		tempy[1]=taily[i];
		tailx[i]=tempx[0];
		taily[i]=tempy[0];
		tempx[0]=tempx[1];
		tempy[0]=tempy[1];
	}
//////////////////////////////////////////////BUG
	for(int i=0;i<=len+1;i++){
		grid[tailx[i]][taily[i]]='*';
	}
	grid[tailx[len+1]][taily[len+1]]=' ';
	for(int i=0;i<=len+1;i++){
		if(sx==tailx[i] && sy==taily[i]){
			game=0;
			for(int i=0;i<=len+1;i++){
				tailx[i]=sx;
				taily[i]=sy;
			}
		}
	}
}

void food(){
	int rtn=1;
	while(rtn){
		srand((unsigned)time(NULL));
		fx = rand() % (X-1);
		fy = rand() % (Y-1);
		if(fx<=1)
			fx++;
		if(fy<=1)
			fy++;
		if(grid[fx][fy]=='*' || grid[fx][fy]=='+'){
			rtn =1;
		}else{
			rtn = 0;
		}
	}

}

void disgrid(){
	grid[fx][fy]='O';
	system("cls");
	printf("\n\t  Score: %d\t\t\t\t\t\tLife: %d",score,life);
	for(int y=0;y<=Y;y++){
		printf("\n       ");
		for(int x=0;x<=X;x++){
			putchar(grid[x][y]);
		}
	}
}

void setgrid(){
	for(int y=0;y<=Y;y++){
		for(int x=0;x<=X;x++){
			if(y>=1 && y<=Y-1 && x>=1 && x<=X-1){
				if(x == sx && y == sy){
					grid[x][y] = '>';
				}
				else{
					grid[x][y] = ' ';
				}
			}else{
				grid[x][y] = '+';
			}
		}
	}
}
