#include<stdio.h>
/*
 * Programmer: Christiano Carta
 * Date: January 31, 2023
 * Prints Fizz, Buzz, and FizzBuzz based on modulo values of 3 and 5.
*/
void function(int);
int main()
{
 
	printf("Enter an integer: ");
 
	int a;
 
	scanf("%d", &a);
 
	function(a); 
 
	return 0;
}
void function(int x)
{
 
	if (x > 0) 
	{	 
	if (((x % 3) == 0) && ((x % 5) == 0))
        printf("FizzBuzz\n");
 
    else if ((x % 3) == 0) 
        printf("Fizz\n");
    else if ((x % 5) == 0)
        printf("Buzz\n");
    else
        printf("%d\n", x);
    
    function(x - 1); 
    }
 
    if ( x == 0)
    {
        printf("Fizzbuzz\n");
        return;
    }
 
    if ( x < 0)
    { 
        if (((x % 3) == 0) && ((x % 5) == 0))
            printf("FizzBuzz\n");
        else if ((x % 3) == 0)
            printf("Fizz\n");
        else if ((x % 5) == 0)
            printf("Buzz\n");
        else
            printf("%d\n", x);
 
        function(x + 1);
    }
}
 
