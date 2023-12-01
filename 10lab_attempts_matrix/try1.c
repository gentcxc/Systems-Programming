#include <curses.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>                 // for usleep()
#include <stdlib.h>                 // for atoi()
char randomchar();
void shiftColumn(char[],int);
void renderColumn(char[],int,int);
int main(int argc, char *argv[]) {
    initscr();
    int speed=1;
    if(argc==2)speed=atoi(argv[1]); // convert a char* to an int
    if(speed<0 || speed > 99){printf("Invalid Speed");return 1;}
    char z[COLS][LINES],str[COLS],buffer[5000][COLS];
    srand((long) time(NULL));
    /*
    for(int i=0; i<LINES;i++)
    {
        for(int j=0; j<COLS;j++)
        {
            int rn = rand() % 10;
            if(rn > 6)
                strcat(z[i],"1");
            else if(rn<3)
                strcat(z[i],"0");
            else
                strcat(z[i]," ");
	*/
        }
    }
    getchar();
    clear();
 while (1)
 { 
    for (int i = 0; i < COLS; i += 1) 
    {
      shiftColumn(z[i], LINES);
      renderColumn(z[i], LINES, i);
    }
    refresh();
    usleep(100000/speed);
}}
void shiftColumn(char column[], int length)
{
  for (int i = length - 1; i > 0; i -= 1) 
    column[i] = column[i - 1];
  
}
void renderColumn(char column[], int length, int position) 
{
  for (int i = 0; i < length; i += 1) 
  {
    move(i, position);
    addch(column[i]);
  }
}
char randomChar() 
{
  switch (rand() % 3) 
  {
    case 0: return '0';
    case 1: return '1';
    case 2: return ' ';
  }
}
