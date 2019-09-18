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
    int choice, n,*ara,*b;
    double ms_t = 0, qs_t = 0;

    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf("Number of elements: ");
            cin>>n;

            if(ara)
                delete [] ara;
            if(b)
                delete [] b;

            ara = new int[n];
            b = new int[n];

            for(int j=0; j<n; j++)
                ara[j] = rand(), b[j]=ara[j];  //avg case
            // do yourself
            break;

        case 2:
            printf("Number of elements: ");
            cin>>n;

            if(ara)
                delete [] ara;
            if(b)
                delete [] b;

            ara = new int[n];
            b = new int[n];

            for(int j=0; j<n; j++)
                ara[j] = j, b[j]=ara[j];
            // do yourself
            break;

        case 3:
            printf("Number of elements: ");
            cin>>n;

            if(ara)
                delete [] ara;
            if(b)
                delete [] b;

            ara = new int[n];
            b = new int[n];

            ara[0] = INT_MAX;
            b[0] = ara[0];

            for(int j=1; j<n; j++)
                ara[j] = ara[j-1] - rand(), b[j] = ara[j];
            // do yourself
            break;

        case 4:
        {
            printf("Applying merge sort\n");
            // do yourself

            for(int j=0; j<n; j++)
                ara[j] = b[j];

            ms_t = 0;
            auto start = high_resolution_clock::now();
            merge_sort(ara,0,n-1);
            auto stop = high_resolution_clock::now();
            //ms_t += duration_cast<microseconds>(stop - start).count();
            ms_t += duration_cast<nanoseconds>(stop - start).count();
            // this should transform the given array into a sorted array
            cout<<"Time taken to finish Merge Sort : "<<ms_t<<endl;
            break;

        }
        case 5:
        {
            printf("Applying quicksort\n");
            // do yourself

            for(int j=0; j<n; j++)
                ara[j] = b[j];

            qs_t = 0;
            auto start = high_resolution_clock::now();
            quick_sort(ara,0,n-1);
            auto stop = high_resolution_clock::now();
            //qs_t += duration_cast<microseconds>(stop - start).count();
            qs_t += duration_cast<nanoseconds>(stop - start).count();
            // this should transform the given array into a sorted array
            cout<<"Time taken to finish Quick Sort : "<<qs_t<<endl;
            break;

        }
        case 6:
            printf("Array : \n");
            print_ara(ara,n);
            // do yourself
            break;
        }
    }
}
