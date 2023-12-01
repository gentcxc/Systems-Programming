#include<stdio.h>
#include<unistd.h>
#include<utmp.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>
char* nullname(char*);
char* usrsearch(char*,char*);
char* nulline(char*);
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"usage: ./prog user\n"); 
        return -1;
    }

    char lnbuf[512], ttybuf[512],name[512],greetbuf[1024],timebuf[256];
    int tty=-1;
    time_t rawtime;
    struct tm* timestruct;
    time(&rawtime);
    timestruct=localtime(&rawtime);
    sprintf(timebuf,"%02d:%02d",timestruct->tm_hour,timestruct->tm_min);
    gethostname(name, sizeof(name));
    strcpy(greetbuf,"Message from ");
    strcat(greetbuf, getlogin());
    strcat(greetbuf, "@");
    strcat(greetbuf, name);
    strcat(greetbuf, " on ");
    strcat(greetbuf, ttyname(STDIN_FILENO));
    strcat(greetbuf, " at ");
    strcat(greetbuf, timebuf);
    strcat(greetbuf, " \n\n");
    if(usrsearch(argv[1], ttybuf)!=NULL)
    {
        if((tty=open(ttybuf,O_WRONLY))>=0)
        {
            write(tty,greetbuf,strlen(greetbuf));
            while(fgets(lnbuf,512,stdin)!=NULL)
                write(tty,lnbuf,strlen(lnbuf));
            write(tty,"EOF\n", 4);
            close(tty);
        }
    }
    else 
        printf("User %s not found\nProgram Ending\n",argv[1]);
    return 0;
}
char* nullname(char* username)
{
    username[UT_NAMESIZE -1]='\0';
    return username;
}
char* usrsearch(char* usr, char* buf)
{
    int i=open(UTMP_FILE, O_RDONLY),t=0;
    struct utmp file;
    if(i>=0)
        while((read(i,&file,sizeof(struct utmp))))
            if(strcmp(usr,nullname(file.ut_user))==0)
            {
                strcpy(buf,"/dev/");
                strcat(buf, nulline(file.ut_line));
                t=1;
            }
    if(t)return buf;
    return NULL;
}
char* nulline(char* ln)
{
    ln[UT_LINESIZE - 1]='\0';
    return ln;
}