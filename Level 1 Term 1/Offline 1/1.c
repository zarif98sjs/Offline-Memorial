#include<stdio.h>

int main()
{
    int num;
    double ans=0;
    scanf("%d",&num);

    if(num<=50)
        ans = num * 0.5;

    else if(num>50&&num<=150)
        ans = 50 * 0.5 + (num-50) * 0.75;

    else if(num>150&&num<=250)
        ans = 50 * 0.5 + 100 * 0.75 + (num-150) * 1.2;

    else if(num>250)
        ans = 50 * 0.5 + 100 * 0.75 + 100 * 1.2 + (num-250) * 1.5;

    ans = ans + ans * 0.2;

    printf("%.2lf\n",ans);

    return 0;
}

