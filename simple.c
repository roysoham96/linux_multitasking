#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print_prime_factors(uint64_t n)
{
    // copy  your  print_prime_factors   from  previous  question  (or
    // better: move  it in  a separate module  and change  the makefile
    // accordingly)
    printf("%ju: ", n);

    if (n==1)
        printf("%ju", n);

    while (n%2==0)
    {
        printf("%d ", 2);
        n = n/2;
    }

    uint64_t sqroot = 1;

    //Find the square root
    while (sqroot*sqroot<=n)
    {
        sqroot+=1;
    }

    uint64_t i=3;
    for (; i<=sqroot; i=i+2)
    {
        while (n%i==0)
        {
            printf("%ju ", i);
            n/=i;
        }
    }
 
    if (n>2)
        printf ("%ju", n);

    printf ("\n");
}

int main(void)
{
    // your code goes  here: open the text file (e.g.  with fopen() ),
    // then read each line (e.g. with fgets() ), turn it into a number
    // (e.g. with atoll() ) and then pass it to print_prime_factors.
	FILE *numbers;
	char str[100];
	
    numbers = fopen ("medium.txt", "r");
    
    while (fgets (str, sizeof(str), numbers)!=NULL)
    {
        uint64_t num = atoll(str);
        print_prime_factors(num);
    }
    return 0;
}
