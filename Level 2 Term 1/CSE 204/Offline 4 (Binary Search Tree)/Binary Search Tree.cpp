#include<iostream>
using namespace std;

class Node
{

public :
    int data;
    Node *left,*right;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class BST
{
    Node *root;
public :

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
    Node* getInorderSuccessor(Node* node);
    void inorder();
    void inorderTrav(Node* node);
    void preorder();
    void preorderTrav(Node* node);
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

void BST::inorder()
{
    cout<<"Inorder Traversal"<<endl;
    inorderTrav(root);
    cout<<"-----------------"<<endl;
}

void BST::preorder()
{
    cout<<"Preorder Traversal"<<endl;
    preorderTrav(root);
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
        node->left = insertNode(node->left, data);
    }

    else if (data > node->data)
    {
        //cout<<"right"<<endl;
        node->right = insertNode(node->right, data);
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
            if(node!=root) delete node;
            else root = NULL;
            return NULL;
        }
        else if(node->left==NULL || node->right==NULL)
        {
            Node* temp;
            if(node->left)
                temp = node->left;
            else if(node->right)
                temp = node->right;
            if(node!=root) delete node;
            else root = temp;
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

void BST::inorderTrav(Node* node)
{
    if(node==NULL)
        return;
    inorderTrav(node->left);
    cout<<"Data : "<<node->data<<endl;
    inorderTrav(node->right);
}

void BST::preorderTrav(Node* node)
{
    if(node==NULL)
        return;
    cout<<"Data : "<<node->data<<endl;
    preorderTrav(node->left);
    preorderTrav(node->right);

}

int main()
{
    BST b1;
    int x,num;

    cout<<"-----Binary Search Tree-----"<<endl;

    while(1)
    {
        cout<<"1. Insert \t\t 4. Inorder Traversal"<<endl;
        cout<<"2. Search \t\t 5. Preorder Traversal"<<endl;
        cout<<"3. Delete \t\t "<<endl;

        cout<<"Operation No. : ";
        cin>>x;

        if(x==1)
        {
            cout<<"Value to insert: ";
            cin>>num;
            b1.insert(num);
        }
        else if(x==2)
        {
            cout<<"Value to search: ";
            cin>>num;
            cout<< (b1.search(num) ? " Value Found ":" Value Not Found ")<<endl;

        }
        else if(x==3)
        {
            cout<<"Value to delete: ";
            cin>>num;
            if(!b1.search(num))
            {
                cout<<"Value not present in the BST"<<endl;
                continue;
            }
            b1._delete(num);
        }
        else if(x==4)
        {
            b1.inorder();
        }
        else if(x==5)
        {
            b1.preorder();
        }

    }



//    b1.insert(20);
//    b1.insert(10);
//    b1.insert(10);
//    b1.insert(60);
//    b1.insert(50);
//    b1.insert(70);
//    b1.insert(30);
//    b1.insert(55);
//    b1.insert(40);
//
//    cout<< (b1.search(20) ? "paisi":"nope")<<endl;
//    cout<< (b1.search(10) ? "paisi":"nope")<<endl;
//    cout<< (b1.search(300) ? "paisi":"nope")<<endl;
//    cout<< (b1.search(60) ? "paisi":"nope")<<endl;
//    cout<< (b1.search(50) ? "paisi":"nope")<<endl;
//
//    b1.preorder();
//
//    //b1._delete(20);
//    b1._delete(60);
//
//    b1.preorder();



    return 0;
}


