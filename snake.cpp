#include<iostream>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

using namespace std;

struct coordinate{
	int x;
	int y;
}snake, food;

enum sdir{LEFT, RIGHT, UP, DOWN}move;

long int game_end=1, life=3, score=0, Snake_t=3, tailX[100], tailY[100], TempX[2], TempY[2];

const int gridx=72, gridy=21;
char grid[gridx][gridy];

void check();
void genfood();
void s_snake();
void getinput();
void setfield();
void disfield();


int main()
{
	setfield();
	genfood();
	disfield();
	system("pause>nul");
	while(game_end){
		s_snake();
		grid[0][0]='+';
		getinput();
		disfield();
		check();
	}
	return 0;
}

void setfield(){
	snake.x=30, snake.y=24;
	for(int y=0; y<=gridy; y++){
		for(int x=0; x<=gridx; x++){
			if(x>=1 && x<=gridx-1 && y>=1 && y<=gridy-1){
				grid[x][y]=' ';
			}else{
				grid[x][y]='+';
			}
		}
	}
	grid[snake.x][snake.y]='>';
}

void genfood(){
	int rtn = 1;
	while(rtn){
		srand((unsigned)time(NULL));
		food.x = rand() % (gridx-1);
		food.y = rand() % (gridy-1);
		if(food.x == 0){
			food.x++;
		}
		if(food.y == 0){
			food.y++;
		}
		if(grid[food.x][food.y] == '*' || grid[food.x][food.y] == '+'){
			rtn = 1;
		}else{
			rtn = 0;
		}
	}
	grid[food.x][food.y]='O';
}

void check(){
	if(snake.y == 0 || snake.y == gridy || snake.x == 0 || snake.x == gridx){
		game_end--;
		life--;
	}
}

void getinput(){
	if(_kbhit()){
		switch(_getch()){
			case 72:
			case 'w':
			case 'W':{
				move = UP;
				break;
			}
			case 80:
			case 's':
			case 'S':{
				move = DOWN;
				break;
			}
			case 75:
			case 'a':
			case 'A':{
				move = LEFT;
				break;
			}
			case 77:
			case 'd':
			case 'D':{
				move = RIGHT;
				break;
			}
			case 'x':
			case 'X':{
				system("pause>nul");
			}
		}
	}
}

void s_snake(){
	switch(move){
		case UP:{
			//grid[snake.x][snake.y]=' ';
			snake.y--;
			grid[snake.x][snake.y]='^';
			tailX[0] = snake.x;
			tailY[0] = snake.y+1;
			break;
		}
		case DOWN:{
			//grid[snake.x][snake.y]=' ';
			snake.y++;
			grid[snake.x][snake.y]='v';
			tailX[0] = snake.x;
			tailY[0] = snake.y-1;
			break;
		}
		case LEFT:{
			//grid[snake.x][snake.y]=' ';
			snake.x--;
			grid[snake.x][snake.y]='<';
			tailX[0] = snake.x+1;
			tailY[0] = snake.y;
			break;
		}
		case RIGHT:{
			//grid[snake.x][snake.y]=' ';
			snake.x++;
			grid[snake.x][snake.y]='>';
			tailX[0] = snake.x-1;
			tailY[0] = snake.y;
			break;
		}
	}
	if(grid[snake.x][snake.y] == grid[food.x][food.y]){
		genfood();
		Snake_t++;
		score=score+50;
	}
	TempX[0] = tailX[0];
	TempY[0] = tailY[0];
	for(int i=1; i<=Snake_t; i++){
		 TempX[1] = tailX[i];
		 TempY[1] = tailY[i];
		 tailX[i] = TempX[0];
		 tailY[i] = TempY[0];
		 TempX[0] = TempX[1];
		 TempY[0] = TempY[1];
	}
	for(int l=0; l<=Snake_t; l++){
		grid[tailX[l]][tailY[l]]='o';
	}
	grid[tailX[Snake_t]][tailY[Snake_t]]=' ';
}

void disfield(){
	system("cls");
	cout<< endl <<"\tScore: "<< score <<"\t\t\t\t\t\tLife: "<<life;
	for(int y=0;y<=gridy;y++){
		cout<<endl<<"   ";
		for(int x=0;x<=gridx;x++){
			cout<<grid[x][y];
		}
	}
	Sleep(100);
}