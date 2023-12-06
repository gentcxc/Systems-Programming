#include<stdio.h>
#include<dirent.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<getopt.h>
int main(int argc, char **argv)
{
    int flagS=0, flagA=0, flagR=0,flagNoarg=0,i,j,count=0;
    char option, files[5000][60],temp[60];
    if((option = getopt(argc,argv,"asr")) == -1)
            flagNoarg=1;
        while((option = getopt(argc, argv, "asr")) != 1)
        {
            switch(option)
            {
                case 's':flagS=1;printf("s on");break;
                case 'a':flagA=1;printf("a on");break;
                case 'r':flagR=1;printf("r on");break;
            }
        }
    char *dir_name;
    if(argc > 2) 
        dir_name=argv[2];
    else
        dir_name= ".";
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    dir_ptr=opendir(dir_name);
    if(dir_ptr ==0) 
        perror(dir_name);
    else
    {
        if(flagA)
            while((dirent_ptr=readdir(dir_ptr))!=0)
                if((dirent_ptr->d_name[1] != '\0')||(dirent_ptr->d_name[0]=='.'))
                    printf("%s \n", dirent_ptr->d_name);
        if(flagNoarg)
            while((dirent_ptr=readdir(dir_ptr))!=0)
                if((dirent_ptr->d_name[1]!='\0') && (dirent_ptr->d_name[0] != '.'))
                    printf("%s \n", dirent_ptr->d_name);
        if(flagS)
            
        {
            for(;(dirent_ptr=readdir(dir_ptr))!=0;count++)
            {
                strcpy(files[count],dirent_ptr->d_name);
                count++;
            }
            for(i=0;i<count;i++)
                for(j=i+1;j<count;j++)
                    if(strcmp(files[i],files[j])>0)
                    {
                        strcpy(temp,files[i]);
                        strcpy(files[i],files[j]);
                        strcpy(files[j],temp);
                    }
            for(i=0;i<count;i++)
                if(files[i][0]!='.')
                    printf("%s\n", files[i]);
        }
        if(flagR)
        {
            int i, j, count=0;
            for(;((dirent_ptr=readdir(dir_ptr))!=0);count++)
                strcpy(files[count],dirent_ptr->d_name);
            for(i=0;i<count;i++)
                for(j=i+1;j<count;j++)
                    if(strcmp(files[i],files[j])<0)
                    {
                        strcpy(temp,files[i]);
                        strcpy(files[i],files[j]);
                        strcpy(files[j],temp);
                    }
            for(i=0;i<count;i++)
                if(files[i][0]!='.')
                    printf("%s\n",files[i]);
        } 
    }
    closedir(dir_ptr);
    return 0;
}

