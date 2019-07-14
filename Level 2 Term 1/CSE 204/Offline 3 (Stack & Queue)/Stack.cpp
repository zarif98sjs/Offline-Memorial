#include<iostream>
using namespace std;

class Stack
{
    int *ara;
    int tos;
    int maxSize;

public:

    Stack();
    ~Stack();
    void push(int num);
    bool Empty();
    int pop();
    int top();
    int Size();
    void Resize();
    int getMaxSize();
};

Stack::Stack()
{
    maxSize=10;
    ara=new int[10];
    tos=0;
}

Stack::~Stack()
{
    cout<<"MEMORY DEALOCATED"<<endl;
    delete[] ara;
}

bool Stack::Empty()
{
    return !tos;
}

void Stack::push(int num)
{
    ara[tos++]=num;
}

int Stack::pop()
{
    if(tos==0)
    {
        cout<<"Stack is empty"<<endl;
        return INT_MIN;
    }
    else
        return ara[--tos];
}

int Stack::top()
{
    return ara[tos-1];
}

int Stack::Size()
{
    return tos;
}

int Stack::getMaxSize()
{
    return maxSize;
}

void Stack::Resize()
{
    if(tos+1>maxSize)
    {
        maxSize+=10;

        int *temp;
        temp = new int[maxSize];

        for(int i=0; i<tos; i++)
            temp[i]=ara[i];

        delete[] ara;
        ara = new int[maxSize];

        for(int i=0; i<tos; i++)
            ara[i]=temp[i];

        delete[] temp;

        cout<<"Memory is expanded"<<endl;
    }

}



int main()
{

    Stack stckA;

    cout<<"Stack is "<< ((stckA.Empty()) ? "Empty" : "Not Empty") <<endl;
    cout<<"Stack Size : "<<stckA.Size()<<endl;

    for(int i=1; i<=15; i++)
    {
        if(stckA.Size()==stckA.getMaxSize())
            stckA.Resize();
        stckA.push(i*10);
        cout<<stckA.top()<<endl;
    }


    cout<<"Stack is "<< ((stckA.Empty()) ? "Empty" : "Not Empty") <<endl;
    cout<<"Stack Size : "<<stckA.Size()<<endl;

    cout<<"Top Element : "<<stckA.top()<<endl;
    cout<<"Popped Value : "<<stckA.pop()<<endl;
    cout<<"Popped Value : "<<stckA.pop()<<endl;
    cout<<"Popped Value : "<<stckA.pop()<<endl;


    return 0;
}

