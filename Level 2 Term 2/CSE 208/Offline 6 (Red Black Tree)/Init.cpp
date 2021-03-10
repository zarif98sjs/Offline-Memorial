

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

struct Node
{
    int data,color;
    Node *left,*right;

    Node(int data,int color)
    {
        this->data = data;
        this->color = color;
        this->left = NULL;
        this->right = NULL;
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

    void insert(int data)
    {
        root = __insert(root,data);
    }

    Node* __insert(Node *node,int data)
    {
        if(node == NULL) return new Node(data,RED);

        if(data < node->data) node->left = __insert(node->left,data);
        else if(data > node->data) node->right = __insert(node->right,data);

        return node;
    }

    void search(int data)
    {
        __search(root,data);
    }

    Node* __search(Node* node,int data)
    {
        if(node == NULL || node->data==data) return node;

        if(data < node->data) return __search(node->left,data);
        else if(data > node->data) return __search(node->right,data);
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

        if(node->left || node->right) cout<<"(";
        __preorder(node->left);
        if(node->left || node->right) cout<<")";
        if(node->left || node->right) cout<<"(";
        __preorder(node->right);
        if(node->left || node->right) cout<<")";
    }
};

int32_t main()
{

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
