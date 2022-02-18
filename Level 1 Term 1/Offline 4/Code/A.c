#include<stdio.h>

void printBinary(unsigned int n)
{
    if(n==0)
    {
        printf("0");
        return;
    }
    else if(n==1)
    {
        printf("1");
        return;
    }
    else
        printBinary(n>>1);
    printf("%d",n&1);
}

int main()
{
    unsigned int x;
    scanf("%u",&x);

    printBinary(x);

    return 0;
}
