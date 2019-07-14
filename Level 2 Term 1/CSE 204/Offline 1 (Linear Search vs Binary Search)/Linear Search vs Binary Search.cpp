#include<iostream>
#include<time.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

bool linear_s(int ar[],int n,int val)
{
    for(int i=0; i<n; i++)
        if(ar[i]==val)
            return true;

    return false;
}

bool binary_s(int ar[],int n,int val)
{
    int lo = 0, hi = n-1, mid = lo + (hi-lo)/2;

    while(lo<=hi)
    {
        //cout<<lo<<" "<<mid<<" "<<hi<<endl;

        if(ar[mid]==val)
            return true;
        else if(ar[mid]<val)
            lo = mid+1;
        else if(ar[mid]>val)
            hi = mid-1;

        mid = lo + (hi-lo)/2;
    }

    return false;
}

int main()
{
    int n,*ara,temp;

    cin>>n;
    //n=10000;

    ara = new int[n];

    srand(time(0));

    for(int i=0; i<n; i++)
        ara[i] = rand();

//    for(int i=0;i<n;i++)
//        cout<<ara[i]<<" ";
//    cout<<endl;


    for(int i=0; i<n; i++)
        for(int j=0; j<n-i-1; j++)
            if(ara[j]>ara[j+1])
            {
                temp = ara[j];
                ara[j] = ara[j+1];
                ara[j+1] = temp;
            }

    int v = rand();

    double lt = 0, bt = 0;

    int iter = 100000;

    bool ans;

    for(int i=1; i<=iter; i++)
    {
        auto start = high_resolution_clock::now();
        ans = linear_s(ara,n,v);
        auto stop = high_resolution_clock::now();
        lt += duration_cast<nanoseconds>(stop - start).count();

        start = high_resolution_clock::now();
        ans = binary_s(ara,n,v);
        stop = high_resolution_clock::now();
        bt += duration_cast<nanoseconds>(stop - start).count();

    }

    cout<<"Linear Search Result : "<< (ans == true ? "Found": "Not Found" )<<endl;
    cout<<"Linear Search Time : "<< lt/iter << " nanoseconds" << endl;

    cout<<"Binary Search Result : "<< (ans == true ? "Found": "Not Found" )<<endl;
    cout<<"Binary Search Time : "<< bt/iter << " nanoseconds" << endl;

    delete[] ara;

    return 0;
}
