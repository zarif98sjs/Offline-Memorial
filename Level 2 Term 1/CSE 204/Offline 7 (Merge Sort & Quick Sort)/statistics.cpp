#include<iostream>
#include<time.h>
#include<chrono>
#include<stdint.h>

using namespace std;
using namespace std::chrono;

void merge(int ara[], int lo, int mid, int hi)
{
    int n1 = mid - lo + 1;
    int n2 =  hi - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = ara[lo + i];
    for (int j = 0; j < n2; j++)
        R[j] = ara[mid + j+ 1];

    int i = 0,j = 0, k = lo;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            ara[k] = L[i];
            i++;
        }
        else
        {
            ara[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        ara[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        ara[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int lo, int hi)
{
    if (lo < hi)
    {
        int mid = (lo+hi)/2;

        merge_sort(arr, lo, mid);
        merge_sort(arr, mid+1, hi);

        merge(arr, lo, mid, hi);
    }
}

int partition(int ara[],int lo,int hi)
{
    int piv = ara[hi];
    int i = lo-1;

    for (int j=lo; j<=hi-1; j++)
    {
        if (ara[j]<=piv)
        {
            i++;
            int temp = ara[i];
            ara[i] = ara[j];
            ara[j] = temp;
        }
    }

    int temp = ara[i+1];
    ara[i+1] = ara[hi];
    ara[hi]  = temp;
    return (i + 1);
}


void quick_sort(int ara[],int lo,int hi)
{
    if(lo<hi)
    {
        int piv = partition(ara,lo,hi);

        quick_sort(ara,lo,piv-1);
        quick_sort(ara,piv+1,hi);
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
//    print_ara(ara,n);
//    quick_sort(ara,0,n-1);
//    print_ara(ara,n);

    int iter = 1e6/n;
    double ms_ac=0,ms_bc=0,ms_wc=0;
    double qs_ac=0,qs_bc=0,qs_wc=0;

    for(int i=1; i<=iter; i++)
    {
        for(int j=0; j<n; j++)
            ara[j] = rand(), b[j]=ara[j];  //avg case

        auto start = high_resolution_clock::now();
        merge_sort(ara,0,n-1);
        auto stop = high_resolution_clock::now();
        //is_ac += duration_cast<nanoseconds>(stop - start).count();
        ms_ac += duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        quick_sort(b,0,n-1);
        stop = high_resolution_clock::now();
        //ss_ac += duration_cast<nanoseconds>(stop - start).count();
        qs_ac += duration_cast<microseconds>(stop - start).count();
    }

    cout<<"Merge sort Avg Case : "<<ms_ac/iter<<endl;
    cout<<"Quick sort Avg Case : "<<qs_ac/iter<<endl;

    for(int i=1; i<=iter; i++)
    {
        auto start = high_resolution_clock::now();
        merge_sort(ara,0,n-1);
        auto stop = high_resolution_clock::now();
        //is_bc += duration_cast<nanoseconds>(stop - start).count();
        ms_bc += duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        quick_sort(b,0,n-1);
        stop = high_resolution_clock::now();
        //ss_bc += duration_cast<nanoseconds>(stop - start).count();
        qs_bc += duration_cast<microseconds>(stop - start).count();
    }

    cout<<"Merge sort Best Case : "<<ms_bc/iter<<endl;
    cout<<"Quick sort Best Case : "<<qs_bc/iter<<endl;

    for(int i=1; i<=iter; i++)
    {
        ara[0] = INT_MAX;
        b[0] = ara[0];

        for(int j=1; j<n; j++)
            ara[j] = ara[j-1] - rand(), b[j] = ara[j];

        auto start = high_resolution_clock::now();
        merge_sort(ara,0,n-1);
        auto stop = high_resolution_clock::now();
        //is_bc += duration_cast<nanoseconds>(stop - start).count();
        ms_wc += duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        quick_sort(b,0,n-1);
        stop = high_resolution_clock::now();
        //ss_wc += duration_cast<nanoseconds>(stop - start).count();
        qs_wc += duration_cast<microseconds>(stop - start).count();
    }

    cout<<"Merge sort Worst Case : "<<ms_wc/iter<<endl;
    cout<<"Quick sort Worst Case : "<<qs_wc/iter<<endl;

    //print_ara(ara,n);
    return 0;

}
