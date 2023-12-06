#include <stdio.h>
#include <unistd.h> //getopt declared here
#include <fcntl.h>
#include <string.h>
#define CPMODE 0644
#define BS 1024     //buffersize
int main(int ac, char *av[])
{
    int flagB = 0, flagE=0, flagN=0, flagS=0, noflag=0, line=1, z = 1, src, numbytes, u,work=0, p;
    char buf[BS], option;
    if(av[z][0] == '-')
    {
        for(int x = 1; av[z][x] != '\0'; x++)
        {
            u = av[z][x];
            switch(u)
            {
                case 'b':
                flagB=1;
                break;
                
                case 'e':
                flagE=1;
                break;

                case 'n':
                flagN=1;
                break;

                case 's':
                flagS=1;
                break;
            }
        }
    }
    else
        ((noflag=1) && (printf("------No Flags------\n\n")));

    for(int i = 1; i < ac; i++)
    {
        if (av[i][0] == '-')      //flag precursor
            i++;
 
        src = open(av[i], O_RDONLY);
        while ((numbytes = read(src, buf, BS))>0)
        {
            if (noflag)
            {
               printf("%s", buf);
            }
            for (int k = 0; k < numbytes; k++)
            {
                if (flagE)
                {
                     if(buf[k] == '\n')
                        printf("$");
                }
                if(flagS)
                {   
                    if(buf[k] == '\n' && buf[k-2] == ' ')
                        k++;
                }
                if(flagN)
                    if(k==0)
                        printf("%d  ", line++);
                if(flagB && (!flagN))
                        if(k==0)
                            printf("%d  ", line++);
		if(!noflag)
                	printf("%c", buf[k]);                 //Print Statement
                if(flagN)
                {
                    if(buf[k] == '\n')
                        printf("%d  ", line++);
                }
                if(flagB && (!flagN))
                {
                    if(buf[k] == '\n')
		    {
		
		    	p=(k+1);
		   	work=0;
			for(; buf[p] != '\n';p++)
				if((buf[p] >='A' && buf[p] <= 'Z') || (buf[p]>='a' && buf[p]<='z'))
					work=1;
		    	if(work)
			    printf("%d  ", line++);
		    } 
                }
            }
        }
    }
    printf("\n");
    return 0;
}
