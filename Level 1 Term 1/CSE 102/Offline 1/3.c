#include<stdio.h>

int main()
{
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);

    int hi = a;

    if(b>hi)
        hi = b;
    if(c>hi)
        hi = c;
    if(d>hi)
        hi = d;

    printf("%d\n",hi);

    return 0;
}
