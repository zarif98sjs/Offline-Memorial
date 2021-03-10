
/*
 *
 * Hash Table : Separate Chaining Method
 *
 * - Md. Zarif Ul Alam
 * Staring at : 16 November 2020 6:10pm
 *
 * */


/* Which of the favors of your Lord will you deny ? */

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

template<class T1, class T2>
ostream &operator <<(ostream &os, pair<T1,T2>&p);
template <class T>
ostream &operator <<(ostream &os, vector<T>&v);
template <class T>
ostream &operator <<(ostream &os, set<T>&v);

struct Node
{
    string key;
    int val;
    Node* nxt;

    Node(){}

    Node(string key,int val)
    {
        this->key = key;
        this->val = val;
        this->nxt = NULL;
    }

    Node(string key,int val,Node* nxt)
    {
        this->key = key;
        this->val = val;
        this->nxt = nxt;
    }
};

struct HashTable_SeparateChaining
{
    int N; /* initial number of assumed data */
    int M; /* initial hast table size */

    vector<Node*>ht;

    HashTable_SeparateChaining()
    {
        N = 10000;
//        M = 1009; /*prime*/
        M = 13; /*prime*/

        ht = vector<Node*>(M);
    }

    int hash(string s)
    {
        int h = 0 , p = 31;
        for(int i=0;i<(int)s.size();i++)
        {
            h = (h * p + s[i])%M;
        }
        return h;
    }

    int search(string key)
    {
        int idx = hash(key);

        Node* now = ht[idx];

        while(now != NULL)
        {
            if(now->key == key)
                return now->val;

            now = now->nxt;
        }

        return INT_MIN; /*not found*/
    }

    bool insert(string key,int val)
    {
        int idx = hash(key);

        assert(idx<M);

        Node* now = ht[idx];

        while(now != NULL)
        {
            if(now->key == key)
                return false; /*already exists*/

            now = now->nxt;
        }

        ht[idx] = new Node(key,val,ht[idx]);

        return true;
    }

    void erase(string key)
    {
        int idx = hash(key);

        Node* prv = NULL;
        Node* now = ht[idx];

        while(now != NULL)
        {
            if(now->key == key)
            {
                if(prv) prv->nxt = now->nxt;
                else  ht[idx] = now->nxt;

                delete (now);
                return;
            }

            prv = now;
            now = now->nxt;
        }
    }

    void print()
    {
        for(int i=0;i<M;i++)
        {
            cout<<"Chain "<<i<<" : ";

            Node* now = ht[i];
            while(now != NULL) cout<< now->key<<" " , now = now->nxt;
            cout<<endl;
        }
    }
};

int32_t main()
{
    HashTable_SeparateChaining h;

    int q;
    cin>>q;

    int val = 1;

    while(q--)
    {
        string type;
        cin>>type;

        string s;
        cin>>s;

        if(type=="I")
        {
            if(h.insert(s,val)) val++;
        }
        else if(type=="F")
        {
            int ret = h.search(s);
            cout<<ret<<endl;
        }
        else if(type=="E")
        {
            h.erase(s);
        }

        h.print();

    }

    return 0;
}

/**

**/

template<class T1, class T2>
ostream &operator <<(ostream &os, pair<T1,T2>&p)
{
    os<<"{"<<p.first<<", "<<p.second<<"} ";
    return os;
}
template <class T>
ostream &operator <<(ostream &os, vector<T>&v)
{
    os<<"[ ";
    for(T i:v)
    {
        os<<i<<" " ;
    }
    os<<" ]";
    return os;
}

template <class T>
ostream &operator <<(ostream &os, set<T>&v)
{
    os<<"[ ";
    for(T i:v)
    {
        os<<i<<" ";
    }
    os<<" ]";
    return os;
}
