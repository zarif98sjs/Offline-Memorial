#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

#define PII pair<int,int>
#define NULL_VALUE -999999
#define INFI 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length )
        return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE )
        return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
        return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)
        return true;
    else
        return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list)
        delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    ArrayList  * weightList ;
    int* inDeg ;
    int* color ;
    int* dist ;
    int* par ;
    int* par_dist;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v, int weight);
    bool isEdge(int u, int v);
    int getDegree(int u,bool out = true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void dijkstra(int source,int des); //will run bfs in the graph
    int bellman_ford(int source,int des);
    void getsp(int src,int des);

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    weightList = 0;
    inDeg = 0 ;
    color = 0 ;
    dist = 0 ;
    par = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0)
        delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    weightList = new ArrayList[nVertices] ;
    inDeg = new int[nVertices] ;
    color = new int[nVertices] ;
    dist = new int[nVertices] ;
    par = new int[nVertices] ;

    for(int i=0; i<nVertices; i++)
    {
        inDeg[i] = 0;
    }
}

void Graph::addEdge(int u, int v,int weight)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    weightList[u].insertItem(weight);
    if(!directed)
        adjList[v].insertItem(u), weightList[v].insertItem(weight);
    if(directed)
        inDeg[v]++;
}

void Graph::removeEdge(int u, int v,int weight)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    if(!isEdge(u,v))
        return;
    this->nEdges--;
    int lu = adjList[u].getLength(),vp;
    for(int i=0; i<lu; i++)
    {
        if(adjList[u].getItem(i)==v && weightList[u].getItem(i)==weight)
        {
            vp = i;
        }
    }

    adjList[u].removeItemAt(vp);
    weightList[u].removeItemAt(vp);
    if(!directed)
    {
        int lu = adjList[v].getLength(),up;
        for(int i=0; i<lu; i++)
        {
            if(adjList[v].getItem(i)==u && weightList[v].getItem(i)==weight)
            {
                up = i;
            }
        }
        adjList[v].removeItemAt(up);
        weightList[v].removeItemAt(up);
    }

}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    if(adjList[u].searchItem(v)==NULL_VALUE)
        return false;

    return true;

    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u,bool out)
{
    if(u<0 || u>=nVertices)
        return NULL_VALUE;
    if(directed==false || out==true)
        return adjList[u].getLength();

    if(!out)
        return inDeg[u];

    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    if(u<0 || u>=nVertices)
        return;
    int len = adjList[u].getLength();
    cout<<" Adjacent Vertices of "<<u<<" : ";
    for(int i=0; i<len; i++)
        cout<<adjList[u].getItem(i)<<" ";
    cout<<endl;
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    int lu = adjList[u].getLength();
    int lv = adjList[v].getLength();

    for(int i=0; i<lu; i++)
    {
        int val = adjList[u].getItem(i);

        if(adjList[v].searchItem(val)!=NULL_VALUE)
            return true;
    }

    return false;

}

void Graph::dijkstra(int source,int des)
{
    //complete this function
    //initialize BFS variables for all n vertices first

    for(int i=0; i<nVertices; i++)
    {
        //color[i] = WHITE;
        dist[i] = INFI;
        par[i] = -1;
    }

    priority_queue< PII,vector<PII>,greater<PII> >PQ;

    //color[source] = GREY;
    dist[source] = 0;
    PQ.push({dist[source],source});

    while(!PQ.empty())
    {
        int now = PQ.top().second;
        PQ.pop();

        int len = adjList[now].getLength();

        for(int i=0; i<len; i++)
        {
            int next = adjList[now].getItem(i);
            int ndis = abs(weightList[now].getItem(i));

            if(dist[now]+ndis<dist[next])
            {
                //color[next] = GREY;
                dist[next] = dist[now]+ndis;
                par[next] = now;
                PQ.push({dist[next],next});
            }
        }

        //color[now] = BLACK;
    }

//    cout<<endl;
//
//    cout<<"----Distance from Source----"<<endl;
//
//    for(int i=0; i<nVertices; i++)
//        cout<<i<<" : "<<dist[i]<<endl;

    if(dist[des]==INFI)
    {
        cout<<"Can't reach destination from source"<<endl;
        return;
    }

    getsp(source,des);

}

int Graph::bellman_ford(int source,int des)
{
    bool is_neg_cycle;

    for(int i=0; i<nVertices; i++)
    {
        //color[i] = WHITE;
        dist[i] = INFI;
        par[i] = -1;
    }

    dist[source] = 0;

    for(int i=0; i<nVertices; i++) /** n-1 + 1 **/
    {
        is_neg_cycle = false;

        for(int now=0; now<nVertices; now++)
        {
            int len = adjList[now].getLength();

            for(int j=0; j<len; j++)
            {
                int next = adjList[now].getItem(j);
                int ndis = weightList[now].getItem(j);

                if(dist[now]!=INFI && dist[now]+ndis<dist[next])
                {
                    //color[next] = GREY;
                    dist[next] = dist[now]+ndis;
                    par[next] = now;
                    is_neg_cycle = true;
                }
            }
        }
    }

    if(is_neg_cycle)
    {
        cout<<"Negative Cycle Exists"<<endl;
        return -1;
    }
    else if(dist[des]==INFI)
    {
        cout<<"Can't reach destination from source"<<endl;
        return -1;
    }

    getsp(source,des);

//
//    for(int i=0; i<nVertices; i++)
//        cout<<i<<" -> "<<dist[i]<<endl;

    return 1;
}

void Graph::getsp(int s,int t)
{
    int des = t;
    vector<int>path;
    while(par[t]!=-1)
    {
        path.push_back(par[t]);
        t = par[t];
    }

    reverse(path.begin(),path.end());

    cout<<dist[des]<<endl;

    for(int x:path)
        cout<<x<<" -> ";
    cout<<des<<endl;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance

    dijkstra(u,v);

    return dist[v];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(adjList)
        delete [] adjList;
    if(weightList)
        delete [] weightList;
    if(inDeg)
        delete [] inDeg;
    if(color)
        delete [] color;
    if(dist)
        delete [] dist;
    if(par)
        delete [] par;

    adjList = 0;
    inDeg = 0;
    color = 0;
    dist = 0;
    par = 0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{

    freopen("input.txt","r",stdin);
    freopen("outputCombined.txt","w",stdout);

    Graph g(true);

    int n,m;
    cin>>n>>m;

    g.setnVertices(n);

    for(int i=0; i<m; i++)
    {
        int a,b,w;
        cin>>a>>b>>w;

        g.addEdge(a,b,w);
    }

    int src,des;
    cin>>src>>des;

    cout<<"Bellman Ford Algorithm:"<<endl;
    g.bellman_ford(src,des);

    cout<<endl;

    cout<<"Dijkstra Algorithm:"<<endl;
    g.dijkstra(src,des);



}
