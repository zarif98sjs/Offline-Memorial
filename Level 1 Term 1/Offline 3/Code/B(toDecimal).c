
#include<stdio.h>

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


int main()
{
    char ara[10000];
    scanf("%s",ara);

    int len,base;
    scanf("%d %d",&len,&base);

    printf("%d",toDecimal(ara,len,base));


    return 0;
}
