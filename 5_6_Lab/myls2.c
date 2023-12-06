#include<stdio.h>
#include<dirent.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ioctl.h>
#include<getopt.h>
int main(int ac, char *av[])
{
    struct winsize wbuf;
    ioctl(0, TIOCGWINSZ, &wbuf);
    printf("%d rows x %d cols\n" , wbuf.ws_row, wbuf.ws_col);
    int flagS=0, flagA=0, flagR=0, noflag=0,i,j,count=0, n,p=1,u,term, greatcounter;
    unsigned long counter=0;
    char option, files[200][60],temp[60];
    if(av[p][0]=='-')
        for(int x = 1; av[p][x] != '\0'; x++)
        {
            u = av[p][x];
            switch(u)
            {
            case 'a':
            flagA=1;
            printf("a enable\n");
            break;
            case 's':
            flagS=1;
            printf("s enable\n");
            break;
            case 'r':
            flagR=1;
            printf("r enable\n");
            break;
            }
        }
        else
            noflag=1;    
    char *dir_name;
    if(ac > 2) 
        dir_name=av[2];
    else
        dir_name= ".";
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    dir_ptr=opendir(dir_name);
    if(dir_ptr ==0) 
        perror(dir_name);
    else
    {   
        count=0;
        if(flagA)
        {
            while((dirent_ptr=readdir(dir_ptr))!=0)
                if((dirent_ptr->d_name[1] != '\0') || (dirent_ptr->d_name[0] == '.'))
                    strcpy(files[count],dirent_ptr->d_name) && count++; 
        }
        if(noflag)
            while((dirent_ptr=readdir(dir_ptr))!=0)
                if((dirent_ptr->d_name[1]!='\0') && (dirent_ptr->d_name[0] != '.'))
                    strcpy(files[count], dirent_ptr->d_name) && count++;
    }
        if(flagS==1)   
        {
            for(i=0;i<count;i++)
                for(j=i+1;j<count;j++)
                    if(strcmp(files[i],files[j])>0)
                    {
                        strcpy(temp,files[i]);
                        strcpy(files[i],files[j]);
                        strcpy(files[j],temp);
                    }
        }
        if(flagR)
        {
            for(i=0;i<count;i++)
                for(j=i+1;j<count;j++)
                    if(strcmp(files[i],files[j])<0)
                    {
                        strcpy(temp,files[i]);
                        strcpy(files[i],files[j]);
                        strcpy(files[j],temp);
                    }
        }
    printf("%s", files[0]);
    for(i=1;i<count;i++)
    {
        greatcounter = strlen(files[i]);
        if(wbuf.ws_col > greatcounter)
        {
            printf("\t%s", files[i]);
            greatcounter+=((strlen(files[i+1]))+4);
        }
        else
        {
            greatcounter=0;
            printf("\n%s",files[i]);
        }
    }        
    closedir(dir_ptr);
    printf("\n");
    return 0;
}
