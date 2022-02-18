#include<stdio.h>
#include<math.h>

void printBinary(int n)
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

int rightRotate(int x,int n)
{
    int t;
    int left=log2(x);
    for(t=1;t<=n;t++)
    {
        if((x&1)==0)
        {
            x=x>>1;
            x=x&(~(1<<left));
        }
        else
        {
            x=x>>1;
            x=x|(1<<left);
        }
    }

    return x;
}

void printZero(int n)
{
    if(n==0)
        return;
        printf("0");
    printZero(n-1);
}

int main()
{
    int x,n;
    scanf("%d %d",&x,&n);

    printBinary(x);
    printf("\n");

    int notun=rightRotate(x,n);

    int digit_before=log2(x)+1;
    int digit_after=log2(notun)+1;

    int zero=digit_before-digit_after;
    printZero(zero);
    printBinary(notun);

    return 0;
}
