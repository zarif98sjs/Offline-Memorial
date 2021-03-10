
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

int eps = 1e-6;

struct Edge{
    int src,dst;
    flow_type capacity , flow;
    size_t rev; /// position of the reverse edge in destinations's adj list
};

class Graph
{
    int nVertices, nEdges;
    bool directed;
    vector<vector<Edge>>adjList;
    vector<Edge>edges;
    vector<int> dist ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);
    void reweightEdge(int u, int v,int w);
    bool isEdge(int u, int v);
    void printGraph();
    int getWeight(int u,int v);

    void PrimAlgoMinST(int src);
    void KruskalAlgoMinST();

    void printShortestPath(int s,int t);
    void cleanSPinfo();

};

Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    directed = dir ;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    int alloc = n+1;
    adjList.resize(alloc);
    dist.resize(alloc);
}

Graph::~Graph()
{
    adjList.clear();
    dist.clear();
}

bool Graph::addEdge(int u, int v,int weight)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;
//
//    if(isEdge(u,v))
//        return false;

    this->nEdges++ ;
    adjList[u].push_back({u,v,weight}) ;
    if(!directed)
        adjList[v].push_back({v,u,weight});

    edges.push_back({u,v,weight}); /** For KRUSKAL **/

    return true;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    if(!isEdge(u,v))
        return;
    this->nEdges--;

    int pos = 0;
    for(int i=0; i<adjList[u].size(); i++)
    {
        if(adjList[u][i].v==v)
        {
            pos = i;
            break;
        }
    }

    adjList[u].erase(adjList[u].begin()+pos);
    if(!directed)
    {
        pos = 0;
        for(int i=0; i<adjList[v].size(); i++)
        {
            if(adjList[v][i].v==u)
            {
                pos = i;
                break;
            }
        }
        adjList[v].erase(adjList[v].begin()+pos);
    }
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    for(int i=0; i<adjList[u].size(); i++)
        if(adjList[u][i].v==v)
            return true;

    return false;
}

void Graph::reweightEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return;
    if(!isEdge(u,v))
    {
        addEdge(u,v,w);
        return;
    }

    int pos = 0;
    for(int i=0; i<adjList[u].size(); i++)
    {
        if(adjList[u][i].v==v)
        {
            adjList[u][i].w = w;
            break;
        }
    }

    if(!directed)
    {
        pos = 0;
        for(int i=0; i<adjList[v].size(); i++)
        {
            if(adjList[v][i].v==u)
            {
                adjList[v][i].w = w;
                break;
            }
        }
    }
}

int Graph::getWeight(int u,int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return NULL_VALUE;

    if(!isEdge(u,v))
        return NULL_VALUE;

    for(int i=0; i<adjList[u].size(); i++)
    {
        if(adjList[u][i].v==v)
        {
            return adjList[u][i].w;
        }
    }
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i+1); /** 1 indexing for answer **/
        for(int j=0; j<adjList[i].size(); j++)
        {
            printf(" %d(%d)", adjList[i][j].v + 1,adjList[i][j].w);  /** 1 indexing for answer **/
        }
        printf("\n");
    }
}


int main()
{
//    freopen("in1.txt","r",stdin);
//    freopen("output1.txt","w",stdout);

    Graph g(false);

    int n,m;
    cin>>n>>m;

    g.setnVertices(n);

    for(int i=0; i<m; i++)
    {
        int a,b;
        int w;

        cin>>a>>b>>w;

        g.addEdge(a,b,w);
    }

    //cout<<"Graph Created"<<endl;

    g.KruskalAlgoMinST();
    g.PrimAlgoMinST(0);


    return 0;
}
