
/** Which of the favors of your Lord will you deny ? **/

#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define F first
#define S second

#define ALL(x)      (x).begin(), (x).end()
#define READ        freopen("alu.txt", "r", stdin)
#define WRITE       freopen("vorta.txt", "w", stdout)

#ifndef ONLINE_JUDGE
#define DBG(x)      cout << __LINE__ << " says: " << #x << " = " << (x) << endl
#else
#define DBG(x)
#define endl "\n"
#endif

struct Node
{
    int data,degree;
    Node *parent , *child , *sibling;

    vector<Node*>adj;

    Node(int data)
    {
        this->data = data;
        this->degree = 0;

        this->parent = NULL;
        this->child = NULL;
        this->sibling = NULL;
    }
};

struct BinomialHeap
{
    Node *head;

    BinomialHeap()
    {
        head = NULL;
    }

    bool isHeapEmpty()
    {
        return head == NULL;
    }

    int FindMin()
    {
        int key = -1;
        Node* ret = FindMin(head)[1];
        if(ret != NULL) key = ret->data;

        return key;
    }

    /// find minimum
    vector<Node*> FindMin(Node* h)
    {
        Node* temp = NULL;
        Node* tempPrv = NULL;

        Node* prv = NULL;
        Node* now = h;

        int mn = INT_MAX;

        while(now != NULL)
        {
            if(now->data < mn)
            {
                mn = now->data;
                tempPrv = prv;
                temp = now;
            }

            prv = now;
            now = now->sibling;
        }

        vector<Node*>ret;
        ret.push_back(tempPrv);
        ret.push_back(temp);

        return ret;
    }

    Node* reverseHeap(Node *h)
    {
        Node* tail = NULL;
        Node* nxt;

        if(h==NULL) return NULL;

        h->parent = NULL;

        while(h->sibling != NULL)
        {
            nxt = h->sibling;
            h->sibling = tail;
            tail = h;
            h = nxt;
            h->parent = NULL;
        }

        h->sibling = tail;

        return h;
    }

//    int extractMin()
//    {
//        Node *ret = __extractMin();
//        return ret->data;
//    }

    int extractMin()
    {
        vector<Node*>ret = FindMin(head);
        Node* prv = ret[0];
        Node* now = ret[1];

        if(now == NULL) return -1;

        if(prv != NULL) prv->sibling = now->sibling;
        else head = now->sibling;

        Node* temp = reverseHeap(now->child);

        head = merge(head,temp);

        int key = -1;
        if(now != NULL) key = now->data;
        free(now);

        return key;
    }

    /// both of them are binomial heaps : Bk-1 + Bk-1 = Bk
    void mergeSameOrderBinomialHeaps(Node* up,Node *down)
    {
        /// link up-down
        down->parent = up;
        /// update sibling
        down->sibling = up->child;

        up->child = down;

        /// as one child is added
        up->degree++;

        up->adj.push_back(down);
    }

    Node* sortedListMerge(Node* h1,Node* h2)
    {
        Node* h = NULL;
        Node** temp = &h;

        while(h1 && h2)
        {
            if(h1->degree <= h2->degree)
            {
                *temp = h1;
                h1 = h1->sibling;
            }
            else
            {
                *temp = h2;
                h2 = h2->sibling;
            }

            temp = &(*temp)->sibling;
        }

        if(h1) *temp = h1;
        else *temp = h2;

        return h;
    }

    Node* merge(Node* h1,Node* h2)
    {
        if(h1==NULL && h2==NULL) return NULL;

        if(h1==NULL) return h2;
        if(h2==NULL) return h1;

        Node* h = sortedListMerge(h1,h2);

        Node* prv = NULL;
        Node* now = h;
        Node* nxt = now->sibling;

        while(nxt != NULL)
        {
            /// all ok , nothing to merge
            if(now->degree != nxt->degree || (nxt->sibling != NULL && nxt->sibling->degree == now->degree))
            {
                prv = now;
                now = nxt;
            }
            else if(now->data <= nxt->data) /// order is ok
            {
                now->sibling = nxt->sibling; /// now is the new root
                mergeSameOrderBinomialHeaps(now,nxt);
            }
            else /// need to correct order
            {
                if(prv != NULL) prv->sibling = nxt;
                else h = nxt;

                mergeSameOrderBinomialHeaps(nxt,now);

                now = nxt;
            }

            nxt = now->sibling;
        }

        return h;
    }

    void Insert(int val)
    {
        Node *nodeToInsert = new Node(val);
        head = merge(head,nodeToInsert);
    }

    void bfs(Node *node)
    {
        queue<pair<Node*,int>>q;
        q.push({node,0});

        int prvL = -1;

        while(!q.empty())
        {
            Node *now = q.front().first;
            int lvl = q.front().second;
            q.pop();

            if(lvl != prvL)
            {
                if(prvL != -1) cout<<endl;

                cout<<"Level "<<lvl<<" : ";
                prvL = lvl;
            }

            cout<<now->data<<" ";

            vector<Node*>tempAdj = now->adj;

            reverse(ALL(tempAdj));

            for(Node *next:tempAdj)
            {
                q.push({next,lvl+1});
            }
        }

        cout<<endl;
    }

    void print()
    {
        cout<<"Printing Binomial Heap..."<<endl;

        Node* now = head;

        while(now != NULL)
        {
            cout<<"Binomial Tree, B"<<now->degree<<endl;
            bfs(now);
            now = now->sibling;
        }
    }

    void Union(vector<int>&v)
    {
        BinomialHeap bnew;
        for(int x:v) bnew.Insert(x);

        head = merge(head,bnew.head);
    }
};

vector<int> transform(string str)
{
    stringstream ss(str);

    int val;
    vector<int>v;

    while(ss>>val)
        v.push_back(val);

    return v;
}

int32_t main()
{

//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    BinomialHeap b;

    string option;

    while(cin>>option)
    {
        if(option=="F")
        {
            int ret = b.FindMin();
            if(ret != -1) cout<<"Find-Min returned "<<ret<<endl;
//            b.print();
        }
        else if(option=="E")
        {
            int ret = b.extractMin();
            if(ret != -1) cout<<"Extract-Min returned "<<ret<<endl;
//            b.print();
        }
        else if(option=="I")
        {
            int num;
            cin>>num;

            b.Insert(num);
//            b.print();
        }
        else if(option=="U")
        {
            string str;
            getline(cin,str);

            vector<int>v = transform(str);

            b.Union(v);
//            b.print();
        }
        else if(option=="P")
        {
            b.print();
        }
    }

    return 0;
}
