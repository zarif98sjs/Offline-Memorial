
/**Which of the favors of your Lord will you deny ?**/

#include<bits/stdc++.h>
using namespace std;

#define NULL_VALUE -999999
#define INFI 999999

#define LL long long
#define PDI pair<double,int>
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define MP make_pair
#define F first
#define S second

double eps = 1e-6;

class Edge
{
    int u,v;
    double w;

public:
    Edge(int u,int v,double w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
    void setEdge(int u,int v,double w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
    int getU()
    {
        return u;
    }
    int getV()
    {
        return v;
    }
    double getW()
    {
        return w;
    }
    void setW(double w)
    {
        this->w = w;
    }
};

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    vector<vector<Edge>>adjList;
    vector<double> dist ;
    vector<int> par ;

    double** distanceMatrix;
    int** parentMatrix;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v, double weight);
    void removeEdge(int u, int v);
    void reweightEdge(int u, int v,double w);
    bool isEdge(int u, int v);
    void printGraph();
    double getWeight(int u,int v);
    Edge* searchEdge(int u,int v);

    void dijkstra(int src);
    bool bellman_ford(int source);

    void floydWarshall();
    void johnsonsAlgo();

    double getShortestPathWeight(int u,int v);
    void printShortestPath(int s,int t);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void cleanSPinfo();

};

Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    distanceMatrix = 0;
    parentMatrix = 0;
    directed = dir ;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    int alloc = n+1;
    adjList.resize(alloc);
    dist.resize(alloc);
    par.resize(alloc);

    distanceMatrix = new double*[alloc];
    parentMatrix = new int*[alloc];

    for(int i=0; i<=nVertices; i++)
    {
        distanceMatrix[i] = new double[alloc];
        parentMatrix[i] = new int[alloc];
        for(int j=0; j<=nVertices; j++)
        {
            distanceMatrix[i][j] = INFI;
            parentMatrix[i][j] = -1;
        }
    }
}

Graph::~Graph()
{
    for(int i = 0; i <nVertices; ++i)
    {
        if(parentMatrix[i])
            delete[] parentMatrix[i];
        if(distanceMatrix[i])
            delete[] distanceMatrix[i];
    }

    if(distanceMatrix)
        delete[] distanceMatrix;
    if(parentMatrix)
        delete[] parentMatrix;

    adjList.clear();
    dist.clear();
    par.clear();
}

bool Graph::addEdge(int u, int v,double weight)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    if(isEdge(u,v))
        return false;

    this->nEdges++ ;
    adjList[u].push_back({u,v,weight}) ;
    if(!directed)
        adjList[v].push_back({v,u,weight});

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
        if(adjList[u][i].getV()==v)
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
            if(adjList[v][i].getV()==u)
            {
                pos = i;
                break;
            }
        }
        adjList[v].erase(adjList[v].begin()+pos);
    }
}

Edge* Graph::searchEdge(int u,int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return NULL; //vertex out of range

    for(int i=0; i<adjList[u].size(); i++)
        if(adjList[u][i].getV()==v)
            return &adjList[u][i];

    return NULL;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    for(int i=0; i<adjList[u].size(); i++)
        if(adjList[u][i].getV()==v)
            return true;

    return false;
}

void Graph::reweightEdge(int u, int v,double w)
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
        if(adjList[u][i].getV()==v)
        {
            adjList[u][i].setW(w);
            break;
        }
    }

    if(!directed)
    {
        pos = 0;
        for(int i=0; i<adjList[v].size(); i++)
        {
            if(adjList[v][i].getV()==u)
            {
                adjList[v][i].setW(w);
                break;
            }
        }
    }
}

double Graph::getWeight(int u,int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return NULL_VALUE;

    if(!isEdge(u,v))
        return NULL_VALUE;

    for(int i=0; i<adjList[u].size(); i++)
    {
        if(adjList[u][i].getV()==v)
        {
            return adjList[u][i].getW();
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
            printf(" %d(%.2f)", adjList[i][j].getV() + 1,adjList[i][j].getW());  /** 1 indexing for answer **/
        }
        printf("\n");
    }
}

void Graph::dijkstra(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        dist[i] = INFI;
        //par[i] = -1;
    }

    priority_queue< PDI,vector<PDI>,greater<PDI> >PQ;

    dist[source] = 0;
    PQ.push({dist[source],source});

    while(!PQ.empty())
    {
        int now = PQ.top().second;
        PQ.pop();

        int len = adjList[now].size();

        for(int i=0; i<len; i++)
        {
            int next = adjList[now][i].getV();
            double ndis = abs(adjList[now][i].getW());

            if(dist[now]+ndis<dist[next])
            {
                dist[next] = dist[now]+ndis;
                parentMatrix[source][next] = now;
                PQ.push({dist[next],next});
            }
        }
    }

//    cout<<"----Distance from Source(Dijkstra)----"<<endl;
//    for(int i=0; i<nVertices; i++)
//        cout<<i<<" : "<<dist[i]<<endl;

//    if(dist[des]==INFI)
//    {
//        cout<<"Can't reach destination from source"<<endl;
//        return;
//    }
//
//    printShortestPath(source,des);
}

bool Graph::bellman_ford(int source)
{
    bool is_neg_cycle;

    for(int i=0; i<nVertices; i++)
        dist[i] = INFI;

    dist[source] = 0;

    for(int i=0; i<nVertices; i++) /** n-1 + 1 **/
    {
        is_neg_cycle = false;

        for(int now=0; now<nVertices; now++)
        {
            int len = adjList[now].size();

            for(int j=0; j<len; j++)
            {
                int next = adjList[now][j].getV();
                double ndis = adjList[now][j].getW();

                if(dist[now]!=INFI && dist[now]+ndis<dist[next])
                {
                    dist[next] = dist[now]+ndis;
                    is_neg_cycle = true;
                }
            }
        }
    }
    if(is_neg_cycle)
        return true;

//    else if(dist[des]==INFI)
//    {
//        cout<<"Can't reach destination from source"<<endl;
//        return false;
//    }
//
//    printShortestPath(source,des);

//    cout<<"----Distance from Source(BellmanFord)----"<<endl;
//    for(int i=0; i<nVertices; i++)
//        cout<<i<<" -> "<<dist[i]<<endl;

    return false;
}

void Graph::floydWarshall()
{
    for(int u=0; u<nVertices; u++)
    {
        int len = adjList[u].size();

        for(int j=0; j<len; j++)
        {
            int v = adjList[u][j].getV();
            distanceMatrix[u][v] = adjList[u][j].getW();
            parentMatrix[u][v] = u;
        }
    }

    for(int i=0; i<nVertices; i++)
    {
        for (int j = 0; j <nVertices; j++)
        {
            if(i==j)
                distanceMatrix[i][j] = 0;
        }
    }

    for(int k=0; k<nVertices; k++)
    {
        for(int i=0; i<nVertices; i++)
        {
            for (int j = 0; j <nVertices; j++)
            {
                if (distanceMatrix[i][k]<INFI  && distanceMatrix[k][j]<INFI)
                {
                    if(distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j])
                    {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                        parentMatrix[i][j] = parentMatrix[k][j];
                    }
                }
            }
        }
    }
    cout<<"Floyd Warshall Algorithm implemented"<<endl;
}

void Graph::johnsonsAlgo()
{
    this->nVertices++;

    for(int i=0; i<nVertices-1; i++)
        addEdge(nVertices-1,i,0);

    bool isNegCycle = bellman_ford(nVertices-1);

    if(isNegCycle)
    {
        /** Readjust wrights **/

        cout<<"Johnson's Algorithm implemented"<<endl;
        cout<<"Negative Cycle Exists"<<endl;
        return;
    }

    this->nVertices--;

    vector<double> h = dist;

    for(int u=0; u<nVertices; u++)
    {
        int len = adjList[u].size();
        for(int j=0; j<len; j++)
        {
            int v = adjList[u][j].getV();
            adjList[u][j].setW(adjList[u][j].getW() + h[u] - h[v]);
            parentMatrix[u][v] = u;
        }
    }

    for(int u=0; u<nVertices; u++)
    {
        dijkstra(u);
        for(int v=0; v<nVertices; v++)
            distanceMatrix[u][v] = dist[v] + h[v]-h[u];
    }

    for(int u=0; u<nVertices; u++)
    {
        int len = adjList[u].size();
        for(int j=0; j<len; j++)
        {
            int v = adjList[u][j].getV();
            adjList[u][j].setW(adjList[u][j].getW() + h[v] - h[u]);
        }
    }
    cout<<"Johnson's Algorithm implemented"<<endl;
}

double Graph::getShortestPathWeight(int u,int v)
{
    return distanceMatrix[u][v];
}

void Graph::printShortestPath(int s,int t)
{
    double tempdistanceMatrix[nVertices][nVertices];

    for(int u=0; u<nVertices; u++)
    {
        int len = adjList[u].size();

        for(int j=0; j<len; j++)
        {
            int v = adjList[u][j].getV();
            tempdistanceMatrix[u][v] = adjList[u][j].getW();
        }
    }
    int src = s;
    int des = t;

    vector<int>path;
    while(parentMatrix[s][t]!=s)
    {
        path.push_back(parentMatrix[s][t]);
        t = parentMatrix[s][t];
    }

    reverse(path.begin(),path.end());
    int sz = path.size();

    if(abs(distanceMatrix[src][des]-INFI)<eps)
        return;

    /** Answer **/

    printf("Shortest Path Weight : %.2f\n",distanceMatrix[src][des]);

    cout<<"Path : "<<src+1<<" -> "; /** 1 indexing for answer **/
    for(int x:path)
    {
        printf("%d(%.2f) -> ",x+1,tempdistanceMatrix[s][x]); /** 1 indexing for answer **/
        s = x;
    }

    printf("%d(%.2f)\n",des+1,tempdistanceMatrix[s][des]); /** 1 indexing for answer **/
}

void Graph::printDistanceMatrix()
{
    cout<<"Distance Matrix:"<<endl;
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            if(abs(distanceMatrix[i][j]-INFI)<eps)
                cout<<"INF\t";
            else
                printf("%.2f\t",distanceMatrix[i][j]);
        }
        cout<<endl;
    }
}

void Graph::printPredecessorMatrix()
{
    cout<<"Predecessor Matrix:"<<endl;
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            if(parentMatrix[i][j]==-1)
                cout<<"NIL\t";
            else
                cout<<parentMatrix[i][j]+1<<"\t";
        }
        cout<<endl;
    }
}

void Graph::cleanSPinfo()
{
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            distanceMatrix[i][j] = INFI;
            parentMatrix[i][j] = -1;
        }
    }
}

int main()
{
//    freopen("input.txt","r",stdin);
//    freopen("outputFloydJohnson.txt","w",stdout);

    Graph g(true);

    int n,m;
    cin>>n>>m;

    g.setnVertices(n);

    for(int i=0; i<m; i++)
    {
        int a,b;
        double w;

        cin>>a>>b>>w;

        a--,b--; /** 0 indexing **/

        g.addEdge(a,b,w);
    }

    cout<<"Graph Created"<<endl;

    while(1)
    {
        int COMMAND;
        cin>>COMMAND;

        if(COMMAND==1)
        {
            g.cleanSPinfo();
            cout<<"APSP matrices cleared"<<endl;
        }
        else if(COMMAND==2)
        {
            g.floydWarshall();
        }
        else if(COMMAND==3)
        {
            g.johnsonsAlgo();
            /**  JOHNSON **/
        }
        else if(COMMAND==4)
        {
            int s,t;
            cin>>s>>t;

            s--,t--; /** 0 indexing **/

            g.printShortestPath(s,t);

        }
        else if(COMMAND==5)
        {
            g.printGraph();

        }
        else if(COMMAND==6)
        {
            g.printDistanceMatrix();
        }
        else if(COMMAND==7)
        {
            g.printPredecessorMatrix();
        }
        else
        {
            break;
        }
    }
    return 0;
}
