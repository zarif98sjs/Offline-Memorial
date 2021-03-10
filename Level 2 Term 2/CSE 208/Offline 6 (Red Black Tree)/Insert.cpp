
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

    bool red(Node *node)
    {
        if(node==NULL) return false;

        return node->color == RED;
    }

    void colorFlip(Node *node)
    {
        node->color = node->color^1;
        node->left->color = node->left->color^1;
        node->right->color = node->right->color^1;
    }

    Node* leftRotate(Node *node)
    {
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;

        temp->color = node->color;
        node->color = RED;

        return temp;
    }

    Node* rightRotate(Node *node)
    {
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;

        temp->color = node->color;
        node->color = RED;

        return temp;
    }

    void insert(int data)
    {
        root = __insert(root,data);
        root->color = BLACK;
    }

    Node* __insert(Node *node,int data)
    {
        if(node == NULL) return new Node(data,RED);

        if(data < node->data) node->left = __insert(node->left,data);
        else node->right = __insert(node->right,data);

        if(red(node->left) && red(node->right))
        {
            if(red(node->left->left) || red(node->left->right) || red(node->right->left) || red(node->right->right) )
            {
                cout<<"Color Flip : "<<node->data<<endl;
                colorFlip(node);
            }
        }

        DBG(node->data);

//        if(node->right)
//        {
//            if(red(node->right) && red(node->right->left))
//            {
//                cout<<"YES";
//            }
//            else
//                cout<<"NO";
//
//        }

        if(red(node->left) && red(node->left->right)) node->left = leftRotate(node->left);
        if(red(node->right) && red(node->right->left)) node->right = rightRotate(node->right);

        if(red(node->left) && red(node->left->left)) node = rightRotate(node);
        if(red(node->right) && red(node->right->right)) node = leftRotate(node);


        return node;
    }

    void search(int data)
    {
        search(root,data);
    }

    Node* search(Node* node,int data)
    {
        if(node == NULL || node->data==data) return node;

        if(data < node->data) return search(node->left,data);
        else if(data > node->data) return search(node->right,data);
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
