#include<iostream>
using namespace std;

class Stack
{
    int *ara;
    int tos;
    int maxSize;

public:

    Stack();
    Stack(int siz);
    Stack(const Stack &old);
    ~Stack();
    void push(int num);
    void push(int *arb,int siz);
    void push(Stack s);
    int pop();
    int top();
    int Size();
    void Resize(int siz);
    double SimilarityScore(Stack s);
};

Stack::Stack()
{
    maxSize=10;
    ara=new int[10];
    tos=0;

    cout<<"Default Constructor used and A stack of size "<<maxSize<<" has been allocated memory"<<endl;
}

Stack::Stack(int siz)
{
    maxSize=siz;
    ara=new int[siz];
    tos=0;

    cout<<"Parameterized Constructor used and A stack of size "<<maxSize<<" has been allocated memory"<<endl;
}

Stack::Stack(const Stack &old)
{
    maxSize=old.maxSize;
    ara=new int[maxSize];
    tos=old.tos;

    for(int i=0; i<maxSize; i++)
        ara[i]=old.ara[i];

    cout<<"Copy Constructor has been used"<<endl;
}

Stack::~Stack()
{
    cout<<"MEMORY DEALOCATED"<<endl;
    delete[] ara;
}

void Stack::push(int num)
{
    if(tos==maxSize)
    {
        //cout<<"Stack is full"<<endl;
        Resize(1);
        ara[tos++]=num;
        //cout<<"maxSIZE --> "<<maxSize<<" tos--> "<<tos<<endl;

    }
    else
        ara[tos++]=num;
}

void Stack::push(int *arb,int siz)
{
    if(tos+siz>maxSize)
    {
        Resize(siz);

    }

    for(int i=tos,j=0; i<tos+siz; i++,j++)
        ara[i]=arb[j];

    tos += siz;

//    for(int i=0; i<tos; i++)
//        cout<<ara[i]<<" - ";

}

void Stack::push(Stack s)
{
    if(tos+s.tos>maxSize)
    {
        Resize(s.tos);
        //cout<<"maxSIZE --> "<<maxSize<<" tos--> "<<tos<<endl;
    }

    for(int i=tos,j=s.tos-1; i<tos+s.tos; i++,j--)
        ara[i]=s.ara[j];

    tos += s.tos;

//    for(int i=0; i<tos; i++)
//        cout<<ara[i]<<" - ";

}

int Stack::pop()
{
    if(tos==0)
    {
        cout<<"Stack is empty"<<endl;
        return -1;
    }
    else if(maxSize-tos>=10)
    {
        Resize(-1);
        //cout<<"maxSIZE is "<<maxSize<<" tos--> "<<tos<<endl;
        return ara[--tos];
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

void Stack::Resize(int siz)
{
    if(siz!=-1 && tos+siz>maxSize)
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

    else if(maxSize-tos>=10)
    {
        maxSize-=10;

        int *temp;
        temp = new int[maxSize];

        for(int i=0; i<tos; i++)
            temp[i]=ara[i];

        delete[] ara;
        ara = new int[maxSize];

        for(int i=0; i<tos; i++)
            ara[i]=temp[i];

        delete[] temp;
        cout<<"Memory is shrinked"<<endl;
    }

}

double Stack::SimilarityScore(Stack s)
{
    int match=0;
    double avg=(Size()+s.Size())*0.5;
    int temp1=Size(),temp2=s.Size();

    while(Size()!=0 || s.Size()!=0)
    {
        if(pop()==s.pop())
            match++;
    }

    tos=temp1;
    s.tos=temp2;

//    cout<<"tos -> "<<tos<<" s.tos -> "<<s.tos<<endl;
//    cout<<"tos -> "<<Size()<<" s.tos -> "<<s.Size()<<endl;

    return match/avg;
}


int main()
{
    int input;
    Stack MainStk,*tempStk;

    while(1)
    {
        cout<<"1: Push an element \t 5: Top"<<endl;
        cout<<"2: Push an array   \t 6: Size"<<endl;
        cout<<"3: Push a stack    \t 7: Similarity"<<endl;
        cout<<"4: Pop             \t 8: Exit"<<endl;
        cout<<endl;

        cin>>input;

        if(input==1)
        {
            int x;
            cin>>x;
            MainStk.push(x);

        }
        else if(input==2)
        {
            int n,*arra;
            cout<<"Number of elements in array: ";
            cin>>n;
            arra = new int[n];
            cout<<"\nElements: ";

            for(int i=0; i<n; i++)
                cin>>arra[i];

            MainStk.push(arra,n);
            delete[] arra;
        }
        else if(input==3)
        {
            int n,x;
            cout<<"Number of elements in stack: ";
            cin>>n;

            //Stack tempStk(n);
            //tempStk = new Stack;
            tempStk = new Stack(n);
            cout<<"\nElements: ";

            for(int i=0; i<n; i++)
            {
                cin>>x;
                (*tempStk).push(x);
            }

            MainStk.push(*tempStk);
            delete tempStk;
        }
        else if(input==4)
        {
            cout<<"Popped value is : "<<MainStk.pop()<<endl;
        }
        else if(input==5)
        {
            cout<<"Value at the top of stack is : "<<MainStk.top()<<endl;

        }
        else if(input==6)
        {
            cout<<"Size of the stack is : "<<MainStk.Size()<<endl;
        }
        else if(input==7)
        {
            int n,x;
            cout<<"Number of elements in stack: ";
            cin>>n;
            //Stack tempStk(n);

            tempStk = new Stack(n);
            cout<<"\nElements: ";

            for(int i=0; i<n; i++)
            {
                cin>>x;
                (*tempStk).push(x);
            }

            cout<<MainStk.SimilarityScore(*tempStk)<<endl;
            delete tempStk;
        }
        else if(input==8)
        {
            cout<<"Exiting...."<<endl;
            cout<<"The stack is :"<<endl;

            while(MainStk.Size()!=0)
                cout<<MainStk.pop()<<endl;

            return 0;
        }
    }



    return 0;
}
