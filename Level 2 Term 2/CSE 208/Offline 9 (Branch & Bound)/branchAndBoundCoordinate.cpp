
/** Which of the favors of your Lord will you deny ? **/

#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int,int>
#define PDD pair<double,double>
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
const int INF = 1e9+7;
vector<vector<double>>d;

int n;
int start = 0;

struct Node
{
    int id,count;
    double lb;// lb -> lower_bound
    vector<vector<double>>rcReducedMatrix;
};

struct cmp
{
    bool operator()(const Node &a, const Node &b) const
    {
        return a.lb > b.lb;
    }
};

struct TSP
{
    vector<vector<double>>d;

    TSP(vector<vector<double>> adj)
    {
        d = adj;
    }

    vector<double> rowReduce(vector<vector<double>>&rm)
    {
        vector<double>row_cost(n,INF);

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                row_cost[i] = min(row_cost[i],rm[i][j]);
            }
        }

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(row_cost[i]!=INF && rm[i][j] != INF)
                {
                    rm[i][j] -= row_cost[i];
                }
            }
        }

        return row_cost;
    }

    vector<double> columnReduce(vector<vector<double>>&rm)
    {
        vector<double>col_cost(n,INF);

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                col_cost[j] = min(col_cost[j],rm[i][j]);
            }
        }

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(col_cost[j]!=INF && rm[i][j] != INF)
                {
                    rm[i][j] -= col_cost[j];
                }
            }
        }

        return col_cost;
    }

    Node getReducedMatrix(vector<vector<double>>&d,int i,int j,int count)
    {
        Node temp;

        temp.rcReducedMatrix = d;

        if(count > 0)
        {
            for(int k=0;k<n;k++)
            {
                temp.rcReducedMatrix[i][k] = INF;
                temp.rcReducedMatrix[k][j] = INF;
            }
        }

        temp.rcReducedMatrix[j][start] = INF;
        temp.id = j;
        temp.count = count;

        vector<double>row_cost = rowReduce(temp.rcReducedMatrix);
        vector<double>col_cost = columnReduce(temp.rcReducedMatrix);

        temp.lb = 0;
        for(int x:row_cost) if(x != INF) temp.lb += x;
        for(int x:col_cost) if(x != INF) temp.lb += x;

        return temp;
    }


    double branchAndBound()
    {
//    DBG(d);

        priority_queue<Node,vector<Node>,cmp> pq;

        Node start_node = getReducedMatrix(d,-1,0,0);
        pq.push(start_node);

        while (!pq.empty())
        {
//        cout<<"here"<<endl;

            Node now = pq.top();
            pq.pop();

            if(now.count == n-1)
            {
//            cout<<"here"<<endl;
                return now.lb;
            }

            int id = now.id;

            for(int j=0;j<n;j++)
            {
                if(now.rcReducedMatrix[id][j] != INF)
                {
                    Node v = getReducedMatrix(now.rcReducedMatrix,id,j,now.count+1);

//                DBG(v.lb);
                    v.lb += (now.lb + now.rcReducedMatrix[id][j]);
//                DBG(v.lb);

                    pq.push(v);
                }
            }
        }

        return INT_MAX*1.0;
    }
};

double euclid(PDD &a,PDD &b)
{
    return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

int32_t main()
{
    optimizeIO();

//    freopen("att48_d.txt", "r", stdin);
    int x;

//    n = 5;
    cin>>n;
    d = vector<vector<double>>(n,vector<double>(n,0));

    /*adj matrixx input style*/

//    for(int i=0;i<n;i++)
//    {
//        for(int j=0;j<n;j++)
//        {
//            cin>>x;
//            d[i][j] = x;
//
//            if(i==j) d[i][j] = INF;
//        }
//    }

    /*coordinate input style*/

    vector<PDD>coord;

    for(int i=0;i<n;i++)
    {
        int id;
        double x,y;
        cin>>id>>x>>y;

        coord.push_back({x,y});
    }


    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            d[i][j] = euclid(coord[i],coord[j]);

            if(i==j) d[i][j] = INF;
        }
    }

    TSP t(d);
    double ans = t.branchAndBound();
//    DBG(ans);

    cout<<"Minimum Cost : "<<ans<<endl;

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
