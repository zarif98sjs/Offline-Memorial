#include<stdio.h>
#include<math.h>

int parityCheck(int n)
{
    int i,one=0;

    for(i=0;i<32;i++)
    {
        if((n&(1<<i))!=0)
            one++;
    }

    if(one%2==0)
        return 1;
    else
        return 0;
}

int main()
{
    int x;
    scanf("%d",&x);

    int i=log2(x);
    for(;i>=0;i--)
    {
        if((x&(1<<i))==0)
            printf("0");
        else
            printf("1");
    }

    if(parityCheck(x))
        printf("\nYes\n");
    else
        printf("\nNo\n");

    return 0;
}

