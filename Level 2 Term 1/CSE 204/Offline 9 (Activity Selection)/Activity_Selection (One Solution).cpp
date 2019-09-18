#include<bits/stdc++.h>
#include<time.h>
using namespace std;

#define LL long long

inline void optimizeIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int nmax = 1e5+7;
const LL LINF = 1e17;

struct el
{
    int st,en,pos;
};

//bool cmp(const el &a,const el &b)
//{
//    return a.st<b.st;
//}

bool cmp2(const el &a,const el &b)
{
    return a.en<b.en;
}

void merge(el ara[], int lo, int mid, int hi, bool (*cmp)(const el&,const el&))
{
    int n1 = mid - lo + 1;
    int n2 =  hi - mid;

    el L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = ara[lo + i];
    for (int j = 0; j < n2; j++)
        R[j] = ara[mid + j+ 1];

    int i = 0,j = 0, k = lo;

    while (i < n1 && j < n2)
    {
        //if (L[i] <= R[j])
        if(cmp2(L[i],R[j])==1)
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

void merge_sort(el arr[], int lo, int hi ,bool (*cmp)(const el&,const el&))
{
    if (lo < hi)
    {
        int mid = (lo+hi)/2;

        merge_sort(arr, lo, mid ,cmp);
        merge_sort(arr, mid+1, hi ,cmp);

        merge(arr, lo, mid, hi,cmp);
    }
}

int n;
int max_subset_size;
int cur_val;

//int sara[] = {1,3,0,5,3,5,6,8,8,2,12};
//int eara[] = {4,5,6,7,8,9,10,11,12,13,14};
//int sara[] = {1,2,3,4,9,10,11,12,17,18,19,20};
//int eara[] = {5,6,7,8,13,14,15,16,21,22,23,24};

//int get_start_end(int sara[],int eara[],int n)
//{
//    sara[0] = 1+rand()%10;
//    eara[0] = sara[0] + rand() % 10 + 1;
//    for(int i=1; i<n; i++)
//    {
//        eara[i] = eara[i-1] + rand()%10;
//        sara[i] = eara[i] - rand()%sara[i-1] - 1;
//    }
//}

int main()
{
    srand(time(0));
    el* v;
    int* sara;
    int* eara;
    cout<<"Number of Activities : ";
    cin>>n;
    sara = new int[n];
    eara = new int[n];
    v = new el[n];
    //get_start_end(sara,eara,n);
    //n = sizeof(sara)/sizeof(sara[0]);

    cout<<"Give Start and End Time of Activities. "<<endl;

    for(int i=0;i<n;i++)
        cin>>sara[i]>>eara[i];

    for(int i=0; i<n; i++)
    {
        v[i].st = sara[i];
        v[i].en = eara[i];
        v[i].pos = i+1;

        //cout<<v[i].st<<" "<<v[i].en<<" "<<v[i].pos<<endl;
    }

    merge_sort(v,0,n-1,cmp2);

//    cout<<"------------------------------------"<<endl;
//
//    for(int i=0; i<n; i++)
//        cout<<v[i].st<<" "<<v[i].en<<" "<<v[i].pos<<endl;

    cout<<"An optimal solution : "<<endl;

    cout<<"Index : "<<v[0].pos<<" , Activity : ("<<v[0].st<<" , "<<v[0].en<<")"<<endl;

    int cur = 0;

    for(int i=1;i<n;i++)
    {
        if(v[i].st>=v[cur].en)
        {
            cout<<"Index : "<<v[i].pos<<" , Activity : ("<<v[i].st<<" , "<<v[i].en<<")"<<endl;
            cur = i;
        }
    }

    return 0;
}


