#include<iostream>
#include<time.h>
#include<chrono>
#include<stdint.h>

using namespace std;
using namespace std::chrono;

void insertion_sort(int a[],int len)
{
    for(int i=1; i<len; i++)
    {
        int temp = a[i];
        int j;

        for(j=i-1; j>=0 && a[j]>temp ; j--)
            a[j+1] = a[j];

        a[j+1] = temp;
    }
}

void selection_sort(int a[],int len)
{
    for (int i=0; i<len-1; i++)
    {
        int minn = i,temp;

        for (int j = i+1; j<len; j++)
            if (a[j]<=a[minn])
                minn = j;

        temp = a[i];
        a[i] = a[minn];
        a[minn] = temp;
    }
}

void print_ara(int a[],int len)
{
    for(int i=0; i<len; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

int main()
{
    int n,*ara,*b,temp;

    cin>>n;
    //n=10000;
    ara = new int[n];
    b = new int[n];

    srand(time(0));

//    for(int i=0; i<n; i++)
//        ara[i] = rand(); //avg case
//
//    //print_ara(ara,n);
//    insertion_sort(ara,n);

    int iter = 10;
    double is_ac=0,is_bc=0,is_wc=0;
    double ss_ac=0,ss_bc=0,ss_wc=0;

    for(int i=1; i<=iter; i++)
    {
        for(int j=0; j<n; j++)
            ara[j] = rand() , b[j]=ara[j]; //avg case

        auto start = high_resolution_clock::now();
        insertion_sort(ara,n);
        auto stop = high_resolution_clock::now();
        //is_ac += duration_cast<nanoseconds>(stop - start).count();
        is_ac += duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        selection_sort(b,n);
        stop = high_resolution_clock::now();
        //ss_ac += duration_cast<nanoseconds>(stop - start).count();
        ss_ac += duration_cast<microseconds>(stop - start).count();
    }

    cout<<"Insertion sort Avg Case : "<<is_ac/iter<<endl;
    cout<<"Selection sort Avg Case : "<<ss_ac/iter<<endl;

    for(int i=1; i<=iter; i++)
    {
        auto start = high_resolution_clock::now();
        insertion_sort(ara,n);
        auto stop = high_resolution_clock::now();
        //is_bc += duration_cast<nanoseconds>(stop - start).count();
        is_bc += duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        selection_sort(b,n);
        stop = high_resolution_clock::now();
        //ss_bc += duration_cast<nanoseconds>(stop - start).count();
        ss_bc += duration_cast<microseconds>(stop - start).count();
    }

    cout<<"Insertion sort Best Case : "<<is_bc/iter<<endl;
    cout<<"Selection sort Best Case : "<<ss_bc/iter<<endl;

    for(int i=1; i<=iter; i++)
    {
        ara[0] = INT_MAX;
        b[0] = ara[0];

        for(int j=1; j<n; j++)
            ara[j] = ara[j-1] - rand() , b[j] = ara[j];

        auto start = high_resolution_clock::now();
        insertion_sort(ara,n);
        auto stop = high_resolution_clock::now();
        //is_bc += duration_cast<nanoseconds>(stop - start).count();
        is_wc += duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        selection_sort(b,n);
        stop = high_resolution_clock::now();
        //ss_wc += duration_cast<nanoseconds>(stop - start).count();
        ss_wc += duration_cast<microseconds>(stop - start).count();
    }

    cout<<"Insertion sort Worst Case : "<<is_wc/iter<<endl;
    cout<<"Selection sort Worst Case : "<<ss_wc/iter<<endl;

    //print_ara(ara,n);
    return 0;

}
