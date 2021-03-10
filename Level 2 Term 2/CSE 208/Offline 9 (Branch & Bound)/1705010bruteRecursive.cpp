
/** Which of the favors of your Lord will you deny ? **/

#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define F first
#define S second

#define ALL(x)      (x).begin(), (x).end()
#define READ        freopen("alu.txt", "r", stdin)
#define WRITE       freopen("vorta.txt", "w", stdout)

#ifndef ONLINE_JUDGE
#define DBG(x)      cout << __LINE__ << " says: " << #x << " = " << (x) << endl
#else
#define DBG(x)
#define endl "\n"
#endif

template<class T1, class T2>
ostream &operator <<(ostream &os, pair<T1,T2>&p);
template <class T>
ostream &operator <<(ostream &os, vector<T>&v);
template <class T>
ostream &operator <<(ostream &os, set<T>&v);

inline void optimizeIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int nmax = 2e5+7;
int n;

vector<vector<int>>d;

int min_cost = INT_MAX;

int calculate_cost(vector<int>&p)
{
    int cost = 0;

    for(int i=1;i<(int)p.size();i++) cost += d[p[i-1]][p[i]];

    cost += d[p.back()][p[0]];
    return cost;
}

vector<int>path;
vector<int>permutation;
vector<bool>visited;

void generate_all_paths()
{
    if ((int)permutation.size() == n)
    {
//        cout << permutation << endl;
        min_cost = min(min_cost,calculate_cost(permutation));
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            continue;

        visited[i] = true;
        permutation.push_back(path[i]);
        generate_all_paths();

        // backtrack
        visited[i] = false;
        permutation.pop_back();
    }
}

int32_t main()
{
    optimizeIO();

//    freopen("att48_d.txt", "r", stdin);
    int x;

//    n = 5;
    cin>>n;
    d = vector<vector<int>>(n,vector<int>(n,0));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>x;
            d[i][j] = x;
        }
    }

//    DBG(d);

    path = vector<int>(n);
    visited = vector<bool>(n,false);
    for(int i=0;i<n;i++) path[i] = i;

    generate_all_paths();
//    DBG(min_cost);

    cout<<"Minimum Cost : "<<min_cost<<endl;

    #ifndef ONLINE_JUDGE
        cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n"<<endl;
        cout<<endl;
    #endif

    return 0;
}

/**

**/

template<class T1, class T2>
ostream &operator <<(ostream &os, pair<T1,T2>&p)
{
    os<<"{"<<p.first<<", "<<p.second<<"} ";
    return os;
}
template <class T>
ostream &operator <<(ostream &os, vector<T>&v)
{
    os<<"[ ";
    for(T i:v)
    {
        os<<i<<" " ;
    }
    os<<" ]";
    return os;
}

template <class T>
ostream &operator <<(ostream &os, set<T>&v)
{
    os<<"[ ";
    for(T i:v)
    {
        os<<i<<" ";
    }
    os<<" ]";
    return os;
}
