#include<iostream>
#include<algorithm>
#include<time.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

void DPS(string str, int idx,string now)
{
    int n = str.length();

    if (idx == n)
    {
        //cout<<now<<endl;
        return;
    }

    DPS(str, idx + 1, now + str[idx]);
    while(str[idx]==str[idx+1])
        idx++;
    DPS(str, idx + 1, now);
}

int main()
{
    string data;
    int len;

    for(int i=0; i<26; i++)
    {
        data +='a'+i;
        data +='A'+i;
        if(i<10)
            data+='0'+i;
    }

    len = data.size();
    cout<<data<<endl;

    int n,temp;
    string inp="";

    cin>>n;

    srand(time(0));

    int iter = 100000;

    for(int i=0; i<n; i++)
    {
        inp += data[rand()%len];
    }

    //cout<<inp<<endl;

    double dps_time = 0;

    for(int q=1; q<=iter; q++)
    {
        string temp = inp;

        auto start = high_resolution_clock::now();
        sort(temp.begin(),temp.end());
        DPS(temp,0,"");
        auto stop = high_resolution_clock::now();
        dps_time += duration_cast<nanoseconds>(stop - start).count();

    }

    cout<<"Time Taken in ns : "<<dps_time/iter<<endl;

    return 0;

}


