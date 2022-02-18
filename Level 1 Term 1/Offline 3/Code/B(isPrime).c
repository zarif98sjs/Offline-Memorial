
#include<stdio.h>
#include<math.h>

int isPrime(int num)
{
    if(num<2)
        return 0;

    int i,flag=1;

    for(i=2;i<=sqrt(num);i++)
    {
        if(num%i==0)
        {
            flag=0;
            break;
        }
    }

    return flag;
}

int main()
{
    int n;
    scanf("%d",&n);

    if(isPrime(n)==1 & n>=2)
        printf("Prime\n");
    else
        printf("Not Prime\n");


    return 0;
}
