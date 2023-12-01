#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
void shift(char[], int);
char randomchar();
void render(char[],int,int);
int main(int argc, char* argv[])
{
  initscr();
  int sleep;
  if(argc<2)
    endwin();
  else
        sleep = atoi(argv[1]);
    endwin();
  char matrix[COLS][LINES];
  for (int i = 0; i < COLS; i += 1) 
  {
    for (int j = 0; j < LINES; j += 1) 
      matrix[i][j] = ' ';
  }    
  while (true) {
    for (int i = 0; i < COLS; i += 1) {
      shift(matrix[i], LINES);
      matrix[i][0] = randomchar();
      render(matrix[i], LINES, i);
    }
    refresh();
    usleep(1000000/sleep);
  }
  endwin();
}
void shift(char col[], int length) 
{
  for (int i = length - 1; i > 0; i -= 1) 
    col[i] = col[i - 1];
}
void render(char col[], int length, int position) 
{
  for (int i = 0; i < length; i += 1) 
  {
    move(i, position);
    addch(col[i]);
  }
}
char randomchar() 
{
  switch (rand() % 3) 
  {
    case 0: return '0';
    case 1: return '1';
    case 2: return ' ';
  }
}