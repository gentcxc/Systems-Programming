//Lab 7: Create program akin to unix find command
//Programmer:Christiano Rosario Carta
#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<limits.h>
char* modeToString(int,char []);
void find(char *dname, char *matcher);
int main(int argc, char *argv[])
{
char *matcher=argv[1], *start=argv[2];
find(start,matcher);
return 0;
}
char*modeToString(int mode, char str[])
{
    strcpy(str, "--------");
    if(S_ISDIR(mode))str[0]='d';
    if(S_ISCHR(mode)) str[0]='c';
    if(S_ISBLK(mode))str[0]='b';
    if(S_ISLNK(mode))str[0]='l';
    if(mode&S_IRUSR)str[1]='r';
    if(mode& S_IWUSR)str[2]='w';
    if(mode& S_IXUSR)str[3]='x';
    if(mode & S_IRGRP) str[4] = 'r';
    if(mode & S_IWGRP) str[5] = 'w';
    if(mode & S_IXGRP) str[6] = 'x';
    if(mode & S_IROTH) str[7] = 'r';
    if(mode & S_IWOTH) str[8] = 'w';
    if(mode & S_IXOTH) str[9] = 'x';
    return str;
}
void find(char *dname, char *matcher)
{
    int contains=0;
    char *pch,*bname,buf[PATH_MAX];
    DIR *dirptr=opendir(dname);
    if(!dirptr)perror(dname);
    struct dirent *entry;
    struct stat info;
    while((entry=readdir(dirptr))!=0)
    {
        char bufs[1024];
        strcpy(bufs, dname);
        strcat(bufs, "/");
        strcat(bufs, entry->d_name);
    if(stat(bufs, &info) ==-1)perror(entry->d_name);
    else
        if(!(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0))
        {
            if(S_ISDIR(info.st_mode))
                find(bufs,matcher);
            else
            {
                pch=strstr(entry->d_name,matcher);
                if(pch)
                {   
                    if(!contains)
                        printf("%s\n",bname=realpath(dname,buf));
                    printf("%s %s\n",entry->d_name,modeToString(info.st_mode,bufs));
                    contains=1;
                }

             }
        }
    }
    closedir(dirptr);
}