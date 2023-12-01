#include<stdio.h>

int main(int argc, char *argv[])
{
    if(argc == 0) return 0;
    for(int args = 1; args < argc; args++)
        for(int j = 0; argv[args][j] != '\0'; j++)
        {
            for(int k = 0; k < j+1; k++)
                if((((argv[args][k]) > 0x40) && (argv[args][k]) < 0x5B) || (((argv[args][k]) > 0x60) && (argv[args][k]) < 0x7B))     
                    printf("%c", argv[args][k]);
                    
            printf("\n");
        }
}
