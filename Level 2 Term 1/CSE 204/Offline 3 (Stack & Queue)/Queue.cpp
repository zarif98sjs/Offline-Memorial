#include<iostream>
using namespace std;

class Queue
{
    int *ara;
    int head;
    int tail;
    int maxSize;

public:

    Queue();
    ~Queue();
    bool Empty();
    bool Full();
    void enqueue(int num);
    int dequeue();
    int front();
    int rear();
    int Size();
    void Resize();
    void print();
};

Queue::Queue()
{
    maxSize = 10;
    ara = new int[10];
    head = -1;
    tail = -1;

}

Queue::~Queue()
{
    cout<<"MEMORY DEALOCATED"<<endl;
    delete[] ara;
}

bool Queue::Empty()
{
    if(head==-1)
        return true;

    return false;
}

bool Queue::Full()
{
    if( (head == tail + 1) || (head == 0 && tail == maxSize-1))
        return 1;
    return 0;
}

void Queue::enqueue(int num)
{
//    if(Full())
//    {
//        cout<<"Fullll"<<endl;
//        Resize();
//    }

    if(head==-1)
        head = 0;

    tail = (tail+1)%maxSize;
    ara[tail] = num;

}

int Queue::dequeue()
{
    if(Empty())
    {
        cout<<"Stack is empty "<<endl;
    }
    int el = ara[head];
    if(head==tail)
    {
        head = -1;
        tail = -1;
    }
    else
        head = (head+1)%maxSize;

    return el;
}

int Queue::front()
{
    if(Empty())
        return INT_MIN;
    return ara[head];
}
int Queue::rear()
{
    if(Empty())
        return INT_MIN;
    return ara[tail];
}

int Queue::Size()
{
    if(head==-1 && tail==-1)
        return 0;
    if(tail>=head)
        return tail-head+1;
    else
        return (tail+1 + maxSize-head);
}

void Queue::Resize()
{
    int siz = Size();
    //cout<<"Size is "<<siz<<endl;

    maxSize+=10;

    int *temp;
    temp = new int[maxSize];

    for(int i=0; i<siz; i++)
        temp[i]=ara[i];

    delete[] ara;
    ara = new int[maxSize];

    for(int i=0; i<siz; i++)
        ara[i]=temp[i];

    delete[] temp;

    cout<<"Memory is expanded"<<endl;

    if(tail<head)
    {
//        for(int i=0; i<maxSize; i++)
//            cout<<ara[i]<<" ";
//        cout<<endl;

        for(int i=maxSize-10-1; i>=head; i--)
            ara[i+10] = ara[i];

        head+=10;

//        for(int i=0; i<maxSize; i++)
//            cout<<ara[i]<<" ";
//        cout<<endl;

        cout<<"...Shift..."<<endl;
    }

}

void Queue::print()
{
    for(int i=0; i<maxSize; i++)
        cout<<ara[i]<<" ";
    cout<<endl;

}

int main()
{
    Queue q;

    cout<<"Queue is "<< ((q.Empty()) ? "Empty" : "Not Empty") <<endl;
    cout<<"Queue Size : "<<q.Size()<<endl;

    for(int i=1; i<=15; i++)
    {
        if(q.Full())
            q.Resize();
        q.enqueue(i*10);
        cout<<q.rear()<<endl;
    }


    cout<<"Queue is "<< ((q.Empty()) ? "Empty" : "Not Empty") <<endl;
    cout<<"Queue Size : "<<q.Size()<<endl;


    cout<<"Front Element : "<<q.front()<<endl;
    cout<<"Rear Element : "<<q.rear()<<endl;
    cout<<"Dequeued Value : "<<q.dequeue()<<endl;
    cout<<"Dequeued Value : "<<q.dequeue()<<endl;
    cout<<"Dequeued Value : "<<q.dequeue()<<endl;


    return 0;
}


