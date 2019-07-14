#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
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
    rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
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
    void bfs(int source); //will run bfs in the graph

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

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE;
        dist[i] = INFINITY;
    }

    Queue q;

    //color[source] = GREY;
    dist[source] = 0;
    q.enqueue(source);

    cout<<"-----BFS-----"<<endl;

    while(!q.empty())
    {
        int now = q.dequeue();

        cout<<now<<" ";

        int len = adjList[now].getLength();

        for(int i=0; i<len; i++)
        {
            int next = adjList[now].getItem(i);
            int ndis = weightList[now].getItem(i);

            if(dist[now]+ndis<dist[next])
            {
                //color[next] = GREY;
                dist[next] = dist[now]+ndis;
                q.enqueue(next);
            }
        }

        //color[now] = BLACK;
    }

    cout<<endl;

    cout<<"----Distance from Source----"<<endl;

    for(int i=0; i<nVertices; i++)
        cout<<i<<" : "<<dist[i]<<endl;


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
    if(inDeg)
        delete [] inDeg;
    if(color)
        delete [] color;
    if(dist)
        delete [] dist;

    adjList = 0;
    inDeg = 0;
    color = 0;
    dist = 0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
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
        printf("5. Print Graph. \t\t 10. Exit. \n");
        //printf("4. (Add from homework). 5. Print Graph  6. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v, w;
            cin>>u>>v>>w;
            g.addEdge(u, v,w);
        }
        else if(ch==2)
        {
            int u, v, w;
            cin>>u>>v>>w;
            g.removeEdge(u, v, w);
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
            cin>>u;
            cout<<"For Out Degree Press 1 , else 0"<<endl;
            cin>>b;

            cout<<g.getDegree(u,b)<<endl;

        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u;
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
            break;
        }
    }

}
