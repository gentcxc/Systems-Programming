#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#define bufsize 1024
int main(int argc,char *argv[])
{
	if(argc!=2)
		fprintf(stderr, "usage: %s ttyname\n",argv[0]);	
	else
	{
		int fd=open(argv[1],O_WRONLY);
		if(fd==-1)
		{
			perror(argv[1]);
			return 1;
		}
		else
		{
            char tbuf[bufsize];
            long int unixtime;
            struct utmp cr;
            int i =open(UTMP_FILE,O_RDONLY);
            while((read(i,&cr,sizeof(cr)))==sizeof(cr))
                unixtime=cr.ut_time;
            struct tm* local = localtime(&unixtime);
            strftime(tbuf,sizeof(tbuf), "%Y-%m-%d %H:%M", local);
            char buf[bufsize],eof[]="EOF \n \n ";
            char intro[]="Message from crcarta@cloudshell on";
            strcat(intro,ttyname(STDIN_FILENO));
            strcat(intro, " at " );
            strcat(intro, tbuf);
            strcat(intro, "\n\n");
            write(fd,intro,strlen(intro));
            while(fgets(buf,bufsize,stdin)!=0)
                if(write(fd,buf,strlen(buf))==-1)
                    break;
            write(fd,eof,strlen(eof));
            close(fd);
        }
    }
    return 0;
}