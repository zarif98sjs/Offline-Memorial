
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



vector<vector<int>>d;

int min_cost = INT_MAX;

int calculate_cost(vector<int>&path)
{
    int cost = 0;

    for(int i=1;i<(int)path.size();i++) cost += d[path[i-1]][path[i]];

    cost += d[path.back()][path[0]];
    return cost;
}

void generate_all_paths(vector<int>&v)
{
    vector<int> permutation = v;

    do
    {
//        for(int x:permutation) cout<<x<<" ";
//        cout<<endl;

        int c_now = calculate_cost(permutation);
        min_cost = min(min_cost,c_now);
//        DBG(c_now);

    } while (next_permutation(ALL(permutation)));
}

int32_t main()
{
    optimizeIO();

//    freopen("att48_d.txt", "r", stdin);
    int n,x;

//    n = 5;
    cin>>n;
    d = vector<vector<int>>(n,vector<int>(n,0));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>x;
//            cout<<x<<"\t";
            d[i][j] = x;
        }
//        cout<<endl;
    }

//    DBG(d);

    vector<int>path(n);
    for(int i=0;i<n;i++) path[i] = i;

    generate_all_paths(path);
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
