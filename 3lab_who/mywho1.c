#include<stdio.h>
#include<utmp.h>
#include <fcntl.h>
#include<unistd.h>
#include<time.h>
void fixtime(long int);
int main()
{
    struct utmp currentrecord;
    int recordlength = sizeof(currentrecord);
    int i=open(UTMP_FILE, O_RDONLY);
    if(i==-1){perror(UTMP_FILE);return 1;}

    while((read(i, &currentrecord, recordlength)) == (recordlength))
    {
        printf("%s  %s  \n", currentrecord.ut_user, currentrecord.ut_host);
        fixtime(currentrecord.ut_time);
    }
    close(i);
    printf("\n");
    return 0;
}
void fixtime(long unixtime)
{
    char c[100];
    struct tm* timestruct = localtime(&unixtime);
    strftime(c,sizeof(c), "%c", timestruct);
    printf("%s", c);
}

