#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
char getch(void);
int kbhit(void);
void delay(int mili);


int readyEnemy  = 0;
int position = 0;
int row = 20 , col = 30;
int enemyArray[20][2];
int gameover = 0;
int score = 0;
int out0 = 0 , out1 = 0;


void makeEnemy()
{
	//if(ready0==0 && ready1==0)
	if(readyEnemy==0)
	{
		int t = rand()%2;
		enemyArray[0][t] = 1;
		readyEnemy = rand()%3+rand()%2+7;
		
	}

}

void draw()
{
	int kx = 0 , ky = 0 ;
	printf("-----------CAR-GAME-----------\n");
	printf("==============================\n");
	for(int i = 0; i<row ; i++)
	{
		printf("=");
		if(i>=row-3)
		{
			if(position==0)
                        {
                                printf("     ###      ");
                                
                        }
                        else
                        {
                                printf("              ");
                        }

		}
		else
		{
			if(enemyArray[i][0]==1)
			{
				kx = 3;
			}
			if(kx>0)
			{
				printf("     ###      ");
				kx--;
			}
			else
			{
				printf("              ");
			}
		}

		printf("=");	

		
		if(i>=row-3)
		{
			if(position==1)
                        {
                                printf("     ###     ");
                        }
                        else
                        {
                                printf("             ");
                        }

		}
		else
		{	
			if(enemyArray[i][1]==1)
			{
				ky = 3;
			}
			if(ky>0)
			{       
			printf("     ###     ");
				ky--;
			}
	                else                    
			{
				printf("             ");
		        }
		}
		printf("=");
		printf("\n");
	}	


	printf("==============================\n");

//	printf("\n(A)->left\n(D)->right\n(x)->quit\n");	
	printf("\nyour Score : %d \n",score);
	printf("\t\t\t\t\t\tmade by: Tushar Malik\n");


}



void update()
{
	// increament enemy position +1
	
	for(int i = row-1 ; i>=0 ; i--)
	{
		if(enemyArray[i][0]==1)
		{
			enemyArray[i][0] = 0;
			if(i!=row-1)
			{
				enemyArray[i+1][0] = 1;

			}
		}

		if(enemyArray[i][1]==1)
		{

			enemyArray[i][1] = 0;
			if(i!=row-1)
			{
				enemyArray[i+1][1] = 1;
			}
		}
	}

	// variable to check enemy can be made or not
	if(readyEnemy>0) readyEnemy--;
	
	// variable to check game over condition
	if(enemyArray[row-4][0]==1) out0 = 3;
	else if(out0>0) out0--;
	
	if(enemyArray[row-4][1]==1) out1 = 3;
	else if(out1>0) out1--;
	
	// calculate score
	
	if(enemyArray[row-1][0]==1 || enemyArray[row-1][1]==1) score+=10;

}


void check()
{
	if(out0>0 && position==0) gameover = 1;
        if(out1>0 && position==1) gameover = 1;

}

void input()
{
	char key;
	if(kbhit()==1)
        {

                key = getch();
                if(key=='x')
                {
			gameover = 1;	
                        exit(0);
                }
		if(key=='a')
		{
			printf("a\n");
			position = 0;
		}
		if(key=='d')
		{
			printf("d \n");
			position = 1;
		}

        }

	
}


void setup()
{
	for(int i = 0;i<30;i++)
	{
		enemyArray[i][0]=0;
		enemyArray[i][1]=0;
	}
	score = 0;
}



void gameloop()
{

        while(1)
        {
		if(gameover==1)
                {
			printf("----|GAME OVER|----\n");
                        break;
                }
		makeEnemy();
		input();
                draw();
		update();
		check();
        	input();
		delay(200);
        }
}


int main()
{

	setup();
	system("clear");
	//enemyArray[0][0] = 1;
	//enemyArray[1][0] = 1;
	gameloop();

	return 0;

}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

char getch(void)
{
    char c;
    system("stty raw");
    c= getchar();
    system("stty sane");
    return(c);
}

void delay(int mili)
{
	clock_t start_time = clock();
	while(clock() < (start_time + mili*1000));
}
