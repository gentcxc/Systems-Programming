#include <curses.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>                 // for usleep()
#include <stdlib.h>                 // for atoi()
int main(int argc, char *argv[]) {
    initscr();
    int speed=1;                
    if(argc==2)speed=atoi(argv[1]); // convert a char* to an int
    if(speed<0 || speed > 99){printf("Invalid Speed");return 1;}
    char z[LINES][COLS],str[COLS];
    srand((long) time(NULL));
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
        }
    }
    getchar();
    clear();
    while(1)
    {	
	    for(int x=0;x<LINES;x++)
        for(int l=0;l<COLS;l++)
            str[l] = z[x][l];
        addstr(str);
        refresh();
        usleep(1000000/speed);
    }
    endwin();                
}

