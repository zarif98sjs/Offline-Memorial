
#include<stdio.h>

int facto(int n)
{
    int i,ans=1;

    for(i=2;i<=n;i++)
        ans = ans*i;

        return ans;
}

int nCr(int n,int r)
{
    int i,val=1;

    for(i=1;i<=r;i++)
    {
        val=val*n;
        n--;
    }

    int ans=val/facto(r);
    return ans;
}

int main()
{
    int i,j,n,r;
    scanf("%d",&n);

    //printf("%d",nCr(n,r));

    for(i=0;i<n;i++)
    {
        int sp;
        for(sp=1;sp<=n-i;sp++)
            printf(" ");

        for(j=0;j<=i;j++)
            printf("%d ",nCr(i,j));

        printf("\n");
    }



    return 0;
}
