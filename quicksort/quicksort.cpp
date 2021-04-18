#include<bits/stdc++.h>
using namespace std;
inline void swaps(int *a, int x, int y)
{
    int b = a[x];
    a[x] = a[y];
    a[y] = b;
}
int q_partition(int *a, int l, int r)
{
    if (l >= r) return l;
    int i = l-1;
    int j = l;
    int x = a[r];
    for (; j < r; j++) {
        if (a[j] <= x) {
            i++;
            swaps(a, i, j);
        }
    }
    swaps(a, i + 1, r);
    return i + 1;
}
void quicksort(int *a, int l, int r)
{
    if (l >= r) return;
    int pivot = q_partition(a, l, r);
    quicksort(a, l, pivot - 1);
    quicksort(a, pivot + 1, r);
}
void print(int*a,int n)
{
    for(int i=0;i<n;i++)cout<<a[i]<<" \n"[i==n-1];
}
int main()
{
    int a[200];
    int n=10;
    for(int i=0;i<n;i++)
    {
        a[i]=(rand()-RAND_MAX/2)/1000;
    }
    print(a,n);
    quicksort(a, 0, n-1);
    print(a,n);



    return 0;
}

