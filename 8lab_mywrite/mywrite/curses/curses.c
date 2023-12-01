#include<curses.h>
#include<stdio.h>
int main()
{
	initscr();
	printf("The screen is %d rows by %d columns\n", LINES,COLS);
	getchar();
	clear();
	move(10,10);
	addstr("Hello, world!");
	refresh();
	sleep(3);






	return 0;
}
