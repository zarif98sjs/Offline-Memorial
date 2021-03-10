
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
#define DOUBLE_BLACK 1

/// Red - 0 , Black - 1 , Double Black - 2

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

    bool doubleBlack(Node *node)
    {
        return node->color == DOUBLE_BLACK;
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

    Node* shiftRedLeft(Node *node)
    {
        colorFlip(node);
        if(red(node->right->left))
        {
            node->right = rightRotate(node->right);
            node = leftRotate(node);
            colorFlip(node);
        }
        return node;
    }

    Node* shiftRedRight(Node *node)
    {
        colorFlip(node);
        if(red(node->left->right))
        {
            node->left = leftRotate(node->left);
            node = rightRotate(node);
            colorFlip(node);
        }
        return node;
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
        else if(data > node->data) node->right = __insert(node->right,data);

        /// case 1 : both child red => any one child has 2 reds in a row (LL LR RR RL) => flip colors
        if(red(node->left) && red(node->right))
        {
            if(red(node->left->left) || red(node->left->right) || red(node->right->left) || red(node->right->right) )
            {
                colorFlip(node);
            }
        }

        /// case 2 part 1 : both of the child are not red => making the red child LL or RR using rotation
        if(red(node->left) && red(node->left->right)) node->left = leftRotate(node->left);
        if(red(node->right) && red(node->right->left)) node->right = rightRotate(node->right);

        /// case 2 part 2 : both of the child are not red => any one child has 2 reds in a row (LL RR) => rotate
        if(red(node->left) && red(node->left->left)) node = rightRotate(node);
        if(red(node->right) && red(node->right->right)) node = leftRotate(node);


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

    void delete_(int data)
    {
        __delete(root,data);
    }

    Node* __delete(Node *node,int data)
    {
        if(node == NULL) return node;

        if(data < node->data) node->left = __delete(node->left,data);
        else if(data > node->data) node->right = __delete(node->right,data);
        else if(data == node->data)
        {
            if(node->left==NULL && node->right==NULL)
            {
                if(red(node))
                {
                    delete node;
                    return NULL;
                }
                else
                {
//                    node->color = 2; /// double black
                    delete node;

                    return NULL;
                }
            }
            else if(node->left==NULL || node->right==NULL)
            {
                /// a red node can't have a single black child
                /// a black node can't have a single black child
                /// a black node will have a single red child , just swap and delete and keep the color black . so black height doesn't change

                Node *temp;
                if(node->left) temp = node->left;
                if(node->right) temp = node->right;

                temp->color = node->color;

                delete node;
                return temp;
            }
            else
            {
                Node* temp  = getInorderPredecessor(node->left);

                node->data = temp->data;
                node->left = __delete(node->left,node->data);
            }
        }

        /// cases



        DBG(node->data);


        return node;
    }


    Node* getInorderPredecessor(Node* node)
    {
        Node* now = node;

        while (now && now->right != NULL)
            now = now->right;

        return now;
    }
};

int32_t main()
{

    freopen("Insert1.txt","w",stdout);

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

//    while(true)
//    {
//        int x;
//        cin>>x;
//
//        r.delete_(x);
//    }

    return 0;
}

/**
9
1 3 2 5 7 4 6 8 10
**/
