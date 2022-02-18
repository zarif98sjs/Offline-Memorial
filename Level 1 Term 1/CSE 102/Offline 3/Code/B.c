
#include<stdio.h>
#include<math.h>

int toDecimal(char ara[],int len,int base)
{
    int i,dec=0,j=0;

    for(i=len-1;i>=0;i--)
    {
        if(ara[i]-'0'>=0 && ara[i]-'0'<=9)
        {
            int k=0,val=1;

            for(k=1;k<=j;k++)
                val = val*base;

            dec = dec + (ara[i]-'0')*val;
        }
        else
        {
            int k=0,val=1;

            for(k=1;k<=j;k++)
                val = val*base;

            //printf("%d\n",ara[i]);
             dec = dec + (ara[i]-55)*val;

        }

        j++;
    }

    return dec;

}

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
    char ara[10000];
    char ara2[10000];

    int base,len;
    scanf("%d %d",&base,&len);


    //getchar();
    //gets(ara);

    //printf("sfkas");

    int i,j;

    for(i=0;i<len;i++)
        scanf(" %c",&ara[i]);

    /*for(i=0,j=0;i<2*len-1;i++)
    {
        if(ara[i]==' ')
            continue;
        ara2[j]=ara[i];
        j++;
    }*/

    int n = toDecimal(ara,len,base);
    int rev = numReverse(n);

    //printf("%d %d\n",n,rev);

    int flag=0;

    if(isPrime(n)==1)
        printf("Prime\n"),flag=1;
    if(isPrime(rev)==1)
        printf("Emirp\n"),flag=1;

    if(flag==0)
        printf("None\n");


    return 0;
}
