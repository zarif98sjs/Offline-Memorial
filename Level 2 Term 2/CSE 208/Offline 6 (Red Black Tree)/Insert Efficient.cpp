
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

#define left 0
#define right 1

struct Node
{
    int data,color;
    Node *child[2];

    Node(int data,int color)
    {
        this->data = data;
        this->color = color;
        this->child[left] = NULL;
        this->child[right] = NULL;
    }
};

#define RED 0
#define BLACK 1

/// Red - 0 , Black - 1

struct RBT
{
    Node *root;

    RBT()
    {
        root = NULL;
    }

    bool red(Node *node)
    {
        if(node==NULL) return false;

        return node->color == RED;
    }

    void colorFlip(Node *node)
    {
        node->color = node->color^1;
        node->child[left]->color = node->child[left]->color^1;
        node->child[right]->color = node->child[right]->color^1;
    }

    Node* rotate(Node *node,bool dir)
    {
        Node *temp = node->child[!dir];
        node->child[!dir] = temp->child[dir];
        temp->child[dir] = node;

        temp->color = node->color;
        node->color = RED;

        return temp;
    }

    /// align reds  , then rotate
    Node* doubleRotate(Node *node,bool dir)
    {
        node->child[!dir] = rotate(node->child[!dir],!dir);
        return rotate(node,dir);
    }

    void insert(int data)
    {
        root = __insert(root,data);
        root->color = BLACK;
    }

    Node* __insert(Node *node,int data)
    {
        if(node == NULL) return new Node(data,RED);

        bool dir = data > node->data; /// left -> 0 , right -> 1
        node->child[dir] = __insert(node->child[dir],data);

        if(red(node->child[dir]))
        {
            /// case 1 : both child red => any one child has 2 reds in a row (LL LR RR RL) => flip colors
            if(red(node->child[!dir]))
            {
                if(red(node->child[dir]->child[dir]) || red(node->child[dir]->child[!dir]))
                {
//                    cout<<"Color Flip : "<<node->data<<endl;
                    colorFlip(node);
                }
            }
            else
            {
                /// case 2 : both child not red

                if(red(node->child[dir]->child[dir]))
                {
                    /// any one child has 2 reds in a row (LL RR) => rotate
//                    cout<<"Single Rotate : "<<node->data<<endl;
                    node = rotate(node,!dir);
                }
                else if(red(node->child[dir]->child[!dir]))
                {
                    /// any one child has 2 reds in a row (LR RL) => align first , then rotate
//                    cout<<"Double Rotate : "<<node->data<<endl;
                    node = doubleRotate(node,!dir);
                }
            }

        }

        return node;
    }

    void search(int data)
    {
        search(root,data);
    }

    Node* search(Node* node,int data)
    {
        if(node == NULL || node->data==data) return node;

        bool dir = data > node->data;

        return search(node->child[dir],data);
    }

    void preorder()
    {
        cout<<"Preorder : ";
        __preorder(root);
        cout<<endl;
    }

    void __preorder(Node *node)
    {
        if(node == NULL) return;

        cout<<node->data<<":"<<(node->color==RED ? "r":"b");

        if(node->child[left] || node->child[right]) cout<<"(";
        __preorder(node->child[left]);
        if(node->child[left] || node->child[right]) cout<<")";

        if(node->child[left] || node->child[right]) cout<<"(";
        __preorder(node->child[right]);
        if(node->child[left] || node->child[right]) cout<<")";
    }
};

int32_t main()
{

//    freopen("Insert2.txt","w",stdout);

    RBT r;

    int n;
    cin>>n;

    while(n--)
    {
        int x;
        cin>>x;

        r.insert(x);

        r.preorder();
    }

    return 0;
}
