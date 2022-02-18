
#include<stdio.h>

int numReverse(int num)
{
    int reverse=0,rem;

    while(num!=0)
    {
        int rem = num%10;
        reverse = reverse*10+rem;
        num /= 10;
    }

    return reverse;
}

int main()
{
    int n;
    scanf("%d",&n);

    printf("%d\n",numReverse(n));

    return 0;
}
