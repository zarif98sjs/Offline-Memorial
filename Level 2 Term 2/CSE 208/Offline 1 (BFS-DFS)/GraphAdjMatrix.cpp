#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<chrono>

using namespace std;
using namespace std::chrono;

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ; //adjacency matrix to store the graph
    int* color ;
    int* dist ;
    int* par ;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    //int getDegree(int u,bool out = true);
    int getOutDegree(int u);
    int getInDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source); //will run dfs in the graph
    void dfs_trav(int source);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    color = 0;
    dist = 0;
    dist = 0;
    par = 0;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    color = new int[nVertices];
    dist = new int[nVertices];
    par = new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

bool Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return false;

    if(isEdge(u,v))
        return false;

    this->nEdges++;
    matrix[u][v]++;
    if(!directed)
        matrix[v][u]++;

    return true;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;
    if(!isEdge(u,v))
        return;
    this->nEdges--;
    matrix[u][v]--;
    //cout<<"yaa "<<matrix[u][v]<<endl;
    if(!directed)
    {
        matrix[v][u]--;
        //cout<<"hoiseee "<<matrix[v][u]<<endl;
    }

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    return matrix[u][v];
}

//int Graph::getDegree(int u,bool out)
//{
//    //returns the degree of vertex u
//    if(u<0 || u>=nVertices)
//        return NULL_VALUE;
//
//    int cnt = 0;
//    for(int i=0; i<nVertices; i++)
//        cnt+=matrix[u][i];
//
//    if(directed==false || out==true)
//        return cnt;
//
//    cnt = 0;
//    for(int i=0; i<nVertices; i++)
//        cnt+=matrix[i][u];
//
//    if(!out)
//        return cnt;
//
//}

int Graph::getOutDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)
        return NULL_VALUE;

    int cnt = 0;
    for(int i=0; i<nVertices; i++)
        cnt+=matrix[u][i];

    return cnt;

}

int Graph::getInDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)
        return NULL_VALUE;

    int cnt = 0;
    for(int i=0; i<nVertices; i++)
        cnt+=matrix[i][u];
    return cnt;

}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices)
        return;
    cout<<" Adjacent Vertices of "<<u<<" : ";
    for(int i=0; i<nVertices; i++)
        if(matrix[u][i])
            cout<<i<<" ";
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i]!=0 && matrix[v][i]!=0)
            return true;
    }

    return false;
}

void Graph::bfs(int source)
{
    //write this function

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE;
        dist[i] = INFINITY;
    }

    Queue q;

    color[source] = GREY;
    dist[source] = 0;
    q.enqueue(source);
//
//    cout<<"-----BFS-----"<<endl;

    while(!q.empty())
    {
        int now = q.dequeue();

//        cout<<now<<" ";

        for(int i=0; i<nVertices; i++)
        {
            if(matrix[now][i])
            {
                int next = i;
                if(color[next]==WHITE)
                {
                    color[next] = GREY;
                    dist[next] = dist[now]+1;
                    q.enqueue(next);
                }
            }
        }

        color[now] = BLACK;
    }

//    cout<<endl;
//
//    cout<<"----Distance from Source----"<<endl;
//
//    for(int i=0; i<nVertices; i++)
//        cout<<i<<" : "<<dist[i]<<endl;

}

void Graph::dfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE;
        par[i] = -1;
    }

    dfs_trav(source);

}

void Graph::dfs_trav(int source)
{
    color[source] = GREY;

    cout<<source<<" ";

    for(int i=0; i<nVertices; i++)
    {
        if(matrix[source][i])
        {
            int next = i;
            if(color[next]==WHITE)
            {
                par[next] = source;
                dfs_trav(next);
            }
        }
    }

    color[source] = BLACK;

}


int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);

    return dist[v];
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]!=0)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{

    for(int i = 0; i <nVertices; ++i)
    {
        if(matrix[i])
            delete[] matrix[i];
    }
    if(matrix)
        delete[] matrix;
    if(color)
        delete [] color;
    if(dist)
        delete [] dist;
    if(par)
        delete [] par;

    matrix = 0;
    color = 0;
    dist = 0;
    par = 0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    srand(time(0));

    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)
        dir = true;
    else if(choice == 2)
        dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge.    \t\t 6. Print Adjoint Vertices. \n");
        printf("2. Remove edge. \t\t 7. Has Common Adjacent ? \n");
        printf("3. Is Edge ?    \t\t 8. BFS. \n");
        printf("4. Get Degree   \t\t 9. Get Distance. \n");
        printf("5. Print Graph. \t\t 10. DFS. \n");
        printf("11. Measure Time. \t\t 12. Exit. \n");
        //printf("4. (Add from homework). 5. Print Graph  6. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            cin>>u>>v;
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            cin>>u>>v;
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            int u, v;
            cin>>u>>v;
            cout<<(g.isEdge(u,v)==true ? "Edge" :"No Edge")<<endl;
        }
        else if(ch==4)
        {
            int u;
            bool b;
            cout<<"Vertex : ";
            cin>>u;
            cout<<"For Out Degree Press 1 , else 0"<<endl;
            cin>>b;

            if(b==1)cout<<g.getOutDegree(u)<<endl;
            else cout<<g.getInDegree(u)<<endl;

        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u;
            cout<<"Vertex : ";
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==7)
        {
            int u,v;
            cin>>u>>v;
            cout<<(g.hasCommonAdjacent(u,v)==true ? "Has Common Adjacent Vertices." :"Don't Have Common Adjacent Vertices.")<<endl;
        }
        else if(ch==8)
        {
            int u;
            cout<<"Starting Vertex: ";
            cin>>u;
            g.bfs(u);
        }
        else if(ch==9)
        {
            int u, v;
            cin>>u>>v;
            int x = g.getDist(u,v);
            cout<<"Distance is : "<<x<<endl;
        }
        else if(ch==10)
        {
            int u;
            cout<<"Starting Vertex: ";
            cin>>u;
            cout<<"-----DFS-----"<<endl;
            g.dfs(u);
            cout<<endl;
        }
        else if(ch==11)
        {
            int ver = n, ed ;

            int upto = (ver*ver-ver)/8;

            int mul = 1;

            for(ed=ver; ed<=upto; ed = mul*ver)
            {

                for(int i=1; i<=ed; i++)
                {
                    int va = rand()%ver;
                    int vb = rand()%ver;

                    while(g.isEdge(va,vb))
                    {
                        va = (va+rand())%ver;
                        vb = (vb+rand())%ver;
                    }

                    g.addEdge(va,vb);
                }

                double tim = 0;

                auto start = steady_clock::now();

                for(int i=1; i<=10; i++)
                {
                    int src = rand()%ver;
                    g.bfs(src);
                }

                auto stop = steady_clock::now();

                tim = duration_cast<microseconds>(stop - start).count();

                mul = mul<<1;
                //cout<<"Mul : "<<mul<<endl;
                cout<<"Edge : "<<ed<<" , "<<"Time : "<<tim<<endl;
            }
        }
        else if(ch==12)
        {
            break;
        }
    }

}
