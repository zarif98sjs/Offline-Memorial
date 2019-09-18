#include<bits/stdc++.h>
using namespace std;

#define LL long long

int LCS_mem(string X,string Y,int lx,int ly,int **dp)
{
    if(lx==0||ly==0)
        return 0;

    int &ret = dp[lx][ly];

    if(ret!=-1)
        return ret;

    if(X[lx-1]==Y[ly-1])
        return ret = 1 + LCS_mem(X,Y,lx-1,ly-1,dp);
    else
        return ret = max(LCS_mem(X,Y,lx,ly-1,dp),LCS_mem(X,Y,lx-1,ly,dp));
}

string print_LCS(string X,string Y,int lx,int ly,int **dp)
{
    if(lx==0 || ly==0)
        return string("");

    if(X[lx-1]==Y[ly-1])
    {
        return  print_LCS(X,Y,lx-1,ly-1,dp) + Y[ly-1];
    }

    if(dp[lx-1][ly]>dp[lx][ly-1])
        return print_LCS(X,Y,lx-1,ly,dp);
    else
        return print_LCS(X,Y,lx,ly-1,dp);
}

int main()
{
    string X,Y;
    cin>>X>>Y;

    int lx = X.size();
    int ly = Y.size();

    int **dp;
    dp = new int *[lx+1];

    for(int i=0; i<=lx; i++)
        dp[i] = new int[ly+1];

    //memset(dp,-1,sizeof(int)*(lx+1)*(ly+1));

    for(int i=0; i<=lx; i++)
        for(int j=0; j<=ly; j++)
            dp[i][j] = -1;

    cout<<"Length of Longest Common Subsequence : "<<LCS_mem(X,Y,lx,ly,dp)<<endl;

//    for(int i=0; i<=lx; i++)
//    {
//        for(int j=0; j<=ly; j++)
//            cout<<dp[i][j]<<"\t";
//        cout<<endl;
//    }

    cout<<"Longest Common Subsequence : "<<print_LCS(X,Y,lx,ly,dp)<<endl;

    for(int i=0;i<=lx;i++)
        delete[] dp[i];
    delete[] dp;

    return 0;
}


