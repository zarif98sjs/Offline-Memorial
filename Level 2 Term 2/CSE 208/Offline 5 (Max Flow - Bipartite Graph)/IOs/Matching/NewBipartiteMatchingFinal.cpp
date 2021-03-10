
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
};

class Graph
{
public:
    int nVertices;
    bool directed ;

    vector<vector<int>>adjList;

    Graph();
    Graph(bool dir,int n);
    ~Graph();
    bool addEdge(int u, int v);
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
    adjList = vector<vector<int>>(len);
}

Graph::~Graph()
{
    adjList.clear();
}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    adjList[u].push_back(v) ;
    if(!directed) adjList[v].push_back(u);

    return true;
}

class FordFulkerson
{

public:

    Graph g;

    int n, source, sink;
    vector<vector<int>> cap;
    vector<vector<int>> init;
    vector<bool>vis;
    vector<Edge>edges;

    FordFulkerson(){}

    FordFulkerson(int n)
    {
        this->n = n;
        g = Graph(true,n); /// directed graph for max flow

        int len = n+1;
        vis = vector<bool>(len);
        cap = vector<vector<int>>(len,vector<int>(len,0));
    }

    void add_edge(int src,int dst,int capacity)
    {
        g.addEdge(src,dst);
        g.addEdge(dst,src); /// reverse edge
        cap[src][dst] += capacity; /// using += for being in safezone for duplicate edges

        edges.push_back({src,dst,0,capacity});
    }

    int dfs(int u, int amount)
    {
        if(u==sink) return amount;

        vis[u] = true;

        for(int v:g.adjList[u]) /// another way would be to make the adj list undirected and traverse over that
        {
            if(!vis[v] && cap[u][v]>0)
            {
                int sent = dfs(v,min(amount,cap[u][v]));

                if(sent > 0) /// if any path with bottleneck > 0 exists
                {
                    cap[u][v] -= sent; /// bottleneck flow
                    cap[v][u] += sent; /// reverse edge

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
//            cout<<"Done"<<endl;
            MAXFLOW += sent;
        }

        return MAXFLOW;
    }

    void print_edges()
    {
        for(auto e:edges)
        {
            int u = e.src , v = e.dst;
            int flow = init[u][v] - cap[u][v];

            if(u==source || v==sink || flow!=1) continue;

            cout<<u<<" "<<v<<" "<<endl;
        }
    }
};

class BipartiteMatching
{

public:

    Graph g;
    vector<Edge>edges;

    FordFulkerson f;
    int n;
    vector<bool>vis,col,bpvis;
    vector<vector<bool>>ed;

    int src,dst;

    BipartiteMatching(int n)
    {
        this->n = n;
        g = Graph(true,n+2);
        f = FordFulkerson(n+2); /// +src , +dst

        int len = n+3;
        vis = vector<bool>(len);
        bpvis = vector<bool>(len);
        col = vector<bool>(len);
        ed = vector<vector<bool>>(len,vector<bool>(len,false));
    }

    void add_edge(int a,int b,bool dir)
    {
        g.addEdge(a,b);
        if(!dir) g.addEdge(b,a);
        edges.push_back({a,b,0,1});

    }

    bool isBipartite(int u)
    {
        vis[u] = true;

        /// source , destination for bipartite
        if(!col[u]) f.add_edge(src,u,1);
        if(col[u]) f.add_edge(u,dst,1);

        for(int next:g.adjList[u])
        {
            if(!vis[next])
            {
                col[next] = !col[u];

                /// bipartite matching edge L -> R
                int tu = u , tv = next;
                if(!col[tv]) swap(tu,tv);

                if(ed[tu][tv]) continue;
                f.add_edge(tu,tv,1);
                ed[tu][tv] = true;

//                cout<<tu<<" , "<<tv<<endl;

                if(isBipartite(next)==false)
                    return false;
            }
            else if(col[next]==col[u])
                return false;
            else
            {

                /// bipartite matching edge L -> R
                int tu = u , tv = next;
                if(!col[tv]) swap(tu,tv);

                if(ed[tu][tv]) continue;
                f.add_edge(tu,tv,1);
                ed[tu][tv] = true;

//                cout<<tu<<" : "<<tv<<endl;
            }
        }

        return true;
    }

    void match()
    {
        this->src = n;
        this->dst = n+1;

        bool ok = true;

        for(int i=0;i<n;i++)
        {
            if(!vis[i])
            {
//                cout<<"Vertex : "<<i<<endl;
                if(!isBipartite(i)) ok = false;
            }
        }

        if(!ok)
        {
            cout<<"Not Bipartite"<<endl;
            return;
        }

        int max_match = f.max_flow(src,dst);

        cout<<max_match<<endl;

        f.print_edges();
    }

};

int32_t main()
{

//    freopen("in5.txt", "r", stdin);
//    freopen("outB5.txt", "w", stdout);

    int n,m;
    cin>>n>>m;

    BipartiteMatching bp(n);

    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;

        /// undirected

        bp.add_edge(a,b,false);
    }

    bp.match();

    return 0;
}
