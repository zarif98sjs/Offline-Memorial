#include<bits/stdc++.h>
#define BLACK 0
#define RED 1
using namespace std;
set<int>all;
int operation=1;
ifstream input,output;
void EXIT()
{
    input.close();
    output.close();
    exit(0);
}

vector<int> Extract(string s)
{
    vector<int>now;
    int cur=0;
    bool shuru=0;
    for(int i=0; i<s.size(); i++)
    {
        if(s[i]-'0'>=0&&s[i]-'0'<=9)
            cur=(10*cur+(s[i]-'0')),shuru=1;
        else
        {
            if(shuru)
                now.push_back(cur);
            cur=0;
            shuru=0;
        }
    }
    return now;
}
pair<int,int> createBST(string s,int h)
{
    if(s.size()==0) return {1,BLACK};
    //cout<<"S "<<s<<endl;
    int cur=0;
    int color=BLACK;
    int i;
    for(i=0;i<s.size();i++)
    {
        if(s[i]-'0'>=0&&s[i]-'0'<=9) cur=(cur*10+(s[i]-'0'));
        else
        {
            if(s[i+1]=='b') color=BLACK;
            else color=RED;
            i+=2;
            break;
        }
    }
    if(h==0&&color==RED)
    {
        cout<<"Wrong color at root"<<endl;
        cout<<"Operation: "<<operation<<endl;
        EXIT();
    }
    if(i==s.size()) return {1+!color,color};
    //cout<<"Cur: "<<cur<<endl;
    assert(s[i]=='(');
    int b1=i+1;
    int al=1;
    string s1,s2;
    for(int j=b1;j<s.size();j++)
    {
        if(s[j]=='(') al++;
        else if(s[j]==')') al--;
        if(al==0)
        {
            if(j!=b1) s1=string(s.begin()+b1,s.begin()+j);
            s2=string(s.begin()+j+2,s.end()-1);
            break;
        }
    }
    //cout<<"S1: "<<s1<<' '<<"S2: "<<s2<<endl;
    vector<int>v1,v2;
    v1=Extract(s1);
    v2=Extract(s2);

    if(!((v1.size()==0||*max_element(v1.begin(),v1.end())<cur)&&(v2.size()==0||*min_element(v2.begin(),v2.end())>cur)))
    {
        cout<<"Invalid BST at node: "<<cur<<endl;
        cout<<"Operation: "<<operation<<endl;
        EXIT();
    }

    pair<int,int> x=createBST(s1,1);
    pair<int,int> y=createBST(s2,1);
    if(x.first==y.first)
    {
        if(color==RED&&(x.second==RED||y.second==RED))
        {
            cout<<"Invalid child color at node: "<<cur<<endl;
            cout<<"Operation: "<<operation<<endl;
            EXIT();
        }
        return {x.first+!color,color};
    }
    else
    {
        cout<<"Wrong heights at node: "<<cur<<endl;
        cout<<"Operation: "<<operation<<endl;
        EXIT();
    }
}


main()
{
    input.open("input.txt",ios::in);
    output.open("output.txt",ios::in);

    char c;
    int x;
    string s;

    while(input>>c>>x)
    {
        getline(output,s);
        if(c=='F')
        {
            if(all.find(x)!=all.end())
            {
                if(s!="True")
                {
                    cout<<"Wrong in find"<<endl;
                    EXIT();
                }
            }
            else
            {
                if(s!="False")
                {
                    cout<<"Wrong in find"<<endl;
                    EXIT();
                }
            }
            operation++;
            continue;
        }
        else if(c=='I')
            all.insert(x);
        else if(c=='D')
            all.erase(x);
        vector<int>now=Extract(s);
        if(now.size()!=all.size()) {cout<<"Wrong D/I at operation: "<<operation<<endl;EXIT();}
        for(int u:now) if(all.find(u)==all.end()) {cout<<"Wrong D/I at operation: "<<operation<<endl;EXIT();}
        createBST(s,1);

        operation++;
    }
    cout<<"All done";
    EXIT();
}
