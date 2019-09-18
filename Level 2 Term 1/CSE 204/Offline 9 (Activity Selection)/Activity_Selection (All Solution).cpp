/*Which of the favors of your Lord will you deny ?*/

#include<bits/stdc++.h>
#include<time.h>
using namespace std;

#define LL long long
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define MP make_pair
#define F first
#define S second
#define INF INT_MAX

inline void optimizeIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int nmax = 1e5+7;
const LL LINF = 1e17;

string to_str(LL x)
{
    stringstream ss;
    ss<<x;
    return ss.str();
}

struct el
{
    int st,en,pos;
};

bool cmp(const el &a,const el &b)
{
    return a.st<b.st;
}

bool cmp2(const el &a,const el &b)
{
    return a.en<b.en;
}

int n;
int max_subset_size;
int cur_val;

vector<el>v(nmax);
int dp[nmax];
int path[nmax];

//int sara[] = {1,3,0,5,3,5,6,8,8,2,12};
//int eara[] = {4,5,6,7,8,9,10,11,12,13,14};
//int sara[] = {1,2,3,4,9,10,11,12,17,18,19,20};
//int eara[] = {5,6,7,8,13,14,15,16,21,22,23,24};
int sara[nmax];
int eara[nmax];

int get_start_end(int n)
{
    sara[0] = 1+rand()%10;
    eara[0] = sara[0] + rand() % 10 + 1;
    for(int i=1; i<n; i++)
    {
        eara[i] = eara[i-1] + rand()%10;
        sara[i] = eara[i] - rand()%sara[i-1] - 1;
    }
}

int get_max_activity()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(v[j].en<v[i].st && dp[i]<dp[j])
            {
                dp[i] = dp[j];
            }
        }
        dp[i]++;
        //cout<<dp[i]<<endl;
    }

    int maxx = 0;

    for(int i=0; i<n; i++)
        maxx = max(maxx,dp[i]);

    return maxx;
}
int cnt = 0;
int st[nmax];
int st_index;

void rec(int index)
{
    if (dp[index] == 1)
    {
        //cout << "Another sequence: (Size: "<<st_index<<" )"<<endl;
        if(st_index==max_subset_size-1)
        {
            cout<<"A maximum subset : ";
            for (int i = st_index-1; i >=0 ; i--)
            {
                cout << st[i] <<" ";
            }

            cout<<cur_val<<endl;
            cnt++;
        }
    }
    for (int j = index-1; j >=0; j--)
    {
        //cout<<"::  "<<dp[j]<<" "<<dp[index]-1<<endl;
        if (dp[j] == dp[index] - 1 && v[j].en <= v[index].st)
        {
            st[st_index++] = v[j].pos;
            //cout<<"-> "<<st[st_index]<<endl;
            rec(j);
            st_index--;
        }
    }
}

int main()
{
    //optimizeIO();

    srand(time(0));
    cout<<"Number of Activities : ";
    cin>>n;
    get_start_end(n);
    //n = sizeof(sara)/sizeof(sara[0]);

    cout<<"Give Start and End Time of Activities. "<<endl;

    for(int i=0;i<n;i++)
        cin>>sara[i]>>eara[i];

    for(int i=0; i<n; i++)
    {
        v[i].st = sara[i];
        v[i].en = eara[i];
        v[i].pos = i+1;

        cout<<v[i].st<<" "<<v[i].en<<" "<<v[i].pos<<endl;
    }

    sort(v.begin(),v.begin()+n,cmp);
    memset(dp,0,sizeof dp);

    max_subset_size = get_max_activity();
    cout<<"Maximum number of activity : "<<max_subset_size<<endl;
    for(int i=n-1; i>=0; i--)
    {
        //cout<<"i is "<<i<<endl;
        cur_val = v[i].pos;
        rec(i);
    }

    cout<<"Total Answers : "<<cnt<<endl;
    memset(path,-1,sizeof path);


    return 0;
}


