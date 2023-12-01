#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void prompt();
int primegen(int);
int largeprime;
int main()
{
    signal(SIGINT,prompt);
    int n;
    for(int i = 0; i<2000;i++)
    {
        for(n=2;n>0;n++)
            primegen(n);
        sleep(1);
    }
    return 0;
}
void prompt()
{   
    char yes=0;
    printf("    %d    Quit? [y / n]  ",largeprime);
    scanf("%c", &yes);
    if(yes==0x79)
    {
        printf("\nProgram Successfully Exited\n");
        signal(SIGINT,SIG_DFL); 
        raise(SIGINT);
    }
    else
	printf("\n");	    
		  
}
int primegen(int prev)
{
    int i,k=0;
    for(i=1;i<=prev;i++)
        if(prev%i==0)
            k++;
    if(k==2)
        largeprime=prev;
}
