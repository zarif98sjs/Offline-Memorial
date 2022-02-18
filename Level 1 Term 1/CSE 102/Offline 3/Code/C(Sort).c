
#include<stdio.h>

int main()
{
    printf("Num of elements to sort : ");

    int ara[100000],n,i,j,temp;
    scanf("%d",&n);

    for(i=1;i<=n;i++)
        scanf("%d",&ara[i]);

    for(i=1;i<=n;i++)
    {
        for(j=1;j<n-i+1;j++)
        {
            if(ara[j+1]<ara[j])
            {
                temp=ara[j];
                ara[j]=ara[j+1];
                ara[j+1]=temp;
            }
        }
    }

    for(i=1;i<=n;i++)
        printf("%d ",ara[i]);

    return 0;
}
