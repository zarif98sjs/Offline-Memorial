
/**Which of the favors of your Lord will you deny ?**/

#include<bits/stdc++.h>
using namespace std;

#define NULL_VALUE -999999
#define INFI 1e9

#define LL long long
#define PDI pair<double,int>
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define MP make_pair
#define F first
#define S second

#define ALL(x)      (x).begin(), (x).end()

struct Edge
{
    int src,dst;
    int flow,capacity;
    bool isF;
};

class Graph
{
public:
    int nVertices;
    bool directed ;

    vector<vector<Edge>>adjList;

    Graph();
    Graph(bool dir,int n);
    ~Graph();
    bool addEdge(int u, int v,bool isF);
    void removeEdge(int u, int v);
    void reweightEdge(int u, int v,int w);
    bool isEdge(int u, int v);
    void printGraph();
    int getWeight(int u,int v);

};

Graph::Graph()
{
    nVertices = 0;
}

Graph::Graph(bool dir,int n)
{
    this->nVertices = n ;
    directed = dir ;

    int len = n+1;
    adjList = vector<vector<Edge>>(len);
}

Graph::~Graph()
{
    adjList.clear();
}

bool Graph::addEdge(int u, int v,bool isF)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    adjList[u].push_back({u,v,0,0,isF}) ;
    if(!directed) adjList[v].push_back({v,u,0,0,!isF});

    return true;
}

class FordFulkerson
{
    Graph g;

    int n, source, sink;
    vector<vector<int>> cap;
    vector<vector<int>> flow; /// just for printing
    vector<vector<int>> init;
    vector<bool>vis;
    vector<Edge>edges;

public:

    FordFulkerson(int n)
    {
        this->n = n;
        g = Graph(true,n); /// directed graph for max flow

        int len = n+1;
        vis = vector<bool>(len);
        cap = vector<vector<int>>(len,vector<int>(len,0));
        flow = vector<vector<int>>(len,vector<int>(len,0));
    }

    void add_edge(int src,int dst,int capacity)
    {
        g.addEdge(src,dst,true);
        g.addEdge(dst,src,false); /// reverse edge
        cap[src][dst] += capacity; /// using += for being in safezone for duplicate edges

        edges.push_back({src,dst,0,capacity,true});
    }

    int dfs(int u, int amount)
    {
        if(u==sink) return amount;

        vis[u] = true;

        for(auto next:g.adjList[u]) /// another way would be to make the adj list undirected and traverse over that
        {
            int v = next.dst;
            bool isF = next.isF;

            if(!vis[v] && cap[u][v]>0)
            {
                int sent = dfs(v,min(amount,cap[u][v]));

                if(sent > 0) /// if any path with bottleneck > 0 exists
                {
                    cout<<u<<" , "<<v<<endl; /// the path
                    cap[u][v] -= sent; /// bottleneck flow
                    cap[v][u] += sent; /// reverse edge

                    if(isF) flow[u][v] += sent;

                    return sent;
                }
            }
        }

        return 0;
    }

    int max_flow(int source,int sink)
    {
        this->source = source;
        this->sink = sink;

        init = cap;

        int MAXFLOW = 0;
        int sent = -1;

        while(sent != 0)
        {
            fill(ALL(vis),false);

            sent = dfs(source,INT_MAX);
            MAXFLOW += sent;

            cout<<"Flow"<<endl;
//            print_edges();
        }

        return MAXFLOW;
    }

    void print_edges()
    {
        for(auto e:edges)
        {
            int u = e.src , v = e.dst;
            cout<<u<<" "<<v<<" "<<flow[u][v]<<"/"<<init[u][v]<<endl;
        }
    }
};

int32_t main()
{
//    freopen("in7.txt", "r", stdin);
//    freopen("outF7.txt", "w", stdout);

    int n,m;
    cin>>n>>m;

    FordFulkerson ff(n);

    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;

        ff.add_edge(a,b,c);
    }

    int src,dst;
    cin>>src>>dst;

    int MAXFLOW = ff.max_flow(src,dst);
    cout<<MAXFLOW<<endl;

    ff.print_edges();

    return 0;
}

