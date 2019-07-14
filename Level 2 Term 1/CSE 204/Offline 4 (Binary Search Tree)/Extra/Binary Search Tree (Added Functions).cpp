#include<iostream>
using namespace std;

class Node
{

public :
    int data;
    Node *left,*right,*par;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->par = NULL;
    }
};

class BST
{

public :
    Node *root;
    BST()
    {
        root = NULL;
    }

    void insert(int data);
    Node* insertNode(Node* node,int data);
    bool search(int data);
    Node* searchNode(Node* node,int data);
    void _delete(int data);
    Node* deleteNode(Node* node,int data);
    Node* getMinimum(Node* node);
    Node* getMaximum(Node* node);
    Node* getInorderSuccessor(Node* node);
    Node* Successor(Node* node);
    Node* Predecessor(Node* node);

    void preorder();
    void preorderTrav(Node* node);
    void inorder();
    void inorderTrav(Node* node);
    void postorder();
    void postorderTrav(Node* node);

    int kthsmallest(int k);
    int kthsmallestHelper(Node* node,int k,int &cnt);

    int LCA(int v1,int v2);
    Node* LCAHelper(Node* node,int v1,int v2);
};

void BST::insert(int data)
{
    insertNode(root,data);
}

bool BST::search(int data)
{
    if(searchNode(root,data)==NULL)
        return false;
    return true;
}

void BST::_delete(int data)
{
    deleteNode(root,data);
}

void BST::preorder()
{
    cout<<"Preorder Traversal"<<endl;
    preorderTrav(root);
    cout<<"-----------------"<<endl;
}

void BST::inorder()
{
    cout<<"Inorder Traversal"<<endl;
    inorderTrav(root);
    cout<<"-----------------"<<endl;
}

void BST::postorder()
{
    cout<<"Postorder Traversal"<<endl;
    postorderTrav(root);
    cout<<"-----------------"<<endl;
}

Node* BST::insertNode(Node* node,int data)
{
    //cout<<"data : "<<data;

    if(root==NULL)
    {
        root=new Node(data);
        //cout<<" roooooot "<<endl;
        return root;
    }

    if(node==NULL)
    {
        node=new Node(data);
        //cout<<" hoiuseeee "<<endl;
        return node;
    }

    //cout<<" , Node data : "<<node->data<<endl;

    if(data < node->data)
    {
        //cout<<"left"<<endl;
        Node *lc = insertNode(node->left, data);
        node->left = lc;
        lc->par = node; // when parent pointer considered
    }

    else if (data > node->data)
    {
        //cout<<"right"<<endl;
        Node *rc = insertNode(node->right, data);
        node->right = rc;
        rc->par = node; // when parent pointer considered
    }

    return node;

}

Node* BST::searchNode(Node* node,int data)
{
    if(node==NULL || node->data==data)
        return node;
    if(data < node->data)
        return searchNode(node->left,data);
    else if(data > node->data)
        return searchNode(node->right,data);

}

Node* BST::deleteNode(Node* node,int data)
{
    if(node==NULL)
        return node;

    if(data < node->data)
        node->left = deleteNode(node->left,data);
    else if(data > node->data)
        node->right = deleteNode(node->right,data);
    else if(data == node->data)
    {
        if(node->left==NULL && node->right==NULL)
        {
            if(node!=root)
                delete node;
            else
                root = NULL;
            return NULL;
        }
        else if(node->left==NULL || node->right==NULL)
        {
            Node* temp;
            if(node->left)
                temp = node->left;
            else if(node->right)
                temp = node->right;
            temp->par = node->par; // when parent pointer considered
            if(node!=root)
                delete node;
            else
                root = temp;
            return temp;
        }

        Node* temp = getInorderSuccessor(node->right);

        node->data = temp->data;
        node->right = deleteNode(node->right,temp->data);
    }

    return node;

}

Node* BST::getInorderSuccessor(Node* node)
{
    Node* now = node;

    while (now && now->left != NULL)
        now = now->left;

    return now;

}

void BST::preorderTrav(Node* node)
{
    if(node==NULL)
        return;
    cout<<"Data : "<<node->data<<endl;
    preorderTrav(node->left);
    preorderTrav(node->right);

}

void BST::inorderTrav(Node* node)
{
    if(node==NULL)
        return;
    inorderTrav(node->left);
    cout<<"Data : "<<node->data;
    if(node->par!=NULL)
        cout<<"  Parent : "<<node->par->data<<endl;
    else
        cout<<"  Parent : Null"<<endl;

    inorderTrav(node->right);
}

void BST::postorderTrav(Node* node)
{
    if(node==NULL)
        return;
    postorderTrav(node->left);
    postorderTrav(node->right);
    cout<<"Data : "<<node->data<<endl;
}

Node* BST::getMinimum(Node* node)
{
    Node* now = node;

    while(now->left!=NULL)
        now = now->left;

    return now;
}
Node* BST::getMaximum(Node* node)
{
    Node* now = node;

    while(now->right!=NULL)
        now = now->right;

    return now;
}

Node* BST::Successor(Node* node)
{
    if(node->right!=NULL)
        return getMinimum(node->right);

    Node *now = node->par;

    while(now!=NULL && node==now->right)
    {
        node = now;
        now = now->par;
    }

    return now;
}

Node* BST::Predecessor(Node* node)
{
    if(node->left!=NULL)
        return getMaximum(node->left);

    Node *now = node->par;

    while(now!=NULL && node==now->left)
    {
        node = now;
        now = now->par;
    }

    return now;
}

int BST::kthsmallest(int k)
{
    int cnt = 0;
    return kthsmallestHelper(root,k,cnt);

}

int BST::kthsmallestHelper(Node* node,int k,int &cnt)
{
    if(node==NULL)
        return INT_MAX;
    int l = kthsmallestHelper(node->left,k,cnt);
    if(l!=INT_MAX) return l;

    if(++cnt==k) return node->data;
    //cout<<"Data : "<<node->data<<endl;
    return kthsmallestHelper(node->right,k,cnt);

}

int BST::LCA(int v1,int v2)
{
    Node* temp = LCAHelper(root,v1,v2);

    return temp->data;
}
Node* BST::LCAHelper(Node* node,int v1,int v2)
{
    if(node==NULL)
        return NULL;

    //cout<<" Node : "<<node->data<<endl;

    if(node->data > max(v1,v2))
        return LCAHelper(node->left,v1,v2);
    else if(node->data < min(v1,v2))
        return LCAHelper(node->right,v1,v2);

    return node;
}

int main()
{
    BST b1;
    int x,num;

    cout<<"-----Binary Search Tree-----"<<endl;

//    while(1)
//    {
//        cout<<"1. Insert \t\t 4. Inorder Traversal"<<endl;
//        cout<<"2. Search \t\t 5. Postorder Traversal"<<endl;
//        cout<<"3. Delete \t\t "<<endl;
//
//        cout<<"Operation No. : ";
//        cin>>x;
//
//        if(x==1)
//        {
//            cout<<"Value to insert: ";
//            cin>>num;
//            b1.insert(num);
//        }
//        else if(x==2)
//        {
//            cout<<"Value to search: ";
//            cin>>num;
//            b1.search(num);
//
//        }
//        else if(x==3)
//        {
//            cout<<"Value to delete: ";
//            cin>>num;
//            b1._delete(num);
//        }
//        else if(x==4)
//        {
//            b1.inorder();
//        }
//        else if(x==5)
//        {
//            b1.postorder();
//        }
//
//    }



    b1.insert(20);
    b1.insert(10);
    b1.insert(10);
    b1.insert(60);
    b1.insert(50);
    b1.insert(70);
    b1.insert(30);
    b1.insert(55);
    b1.insert(40);

    cout<< (b1.search(20) ? "paisi":"nope")<<endl;
    cout<< (b1.search(10) ? "paisi":"nope")<<endl;
    cout<< (b1.search(300) ? "paisi":"nope")<<endl;
    cout<< (b1.search(60) ? "paisi":"nope")<<endl;
    cout<< (b1.search(50) ? "paisi":"nope")<<endl;

    b1.inorder();

    cout<<(b1.Predecessor(b1.searchNode(b1.root,55)))->data<<endl;
    cout<<(b1.Successor(b1.searchNode(b1.root,55)))->data<<endl;
    cout<<"LCA : "<<b1.LCA(40,70)<<endl;
    b1._delete(20);
    //b1._delete(30);

    b1.inorder();





    return 0;
}
