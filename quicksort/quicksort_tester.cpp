/*
 * this program intends to test the average case of quicksort vs its worst case
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
ll c = 0;
inline void print(int *a, int n)
{
    for (int i = 0; i < n; i++) { cout << a[i] << " \n"[i == n - 1]; }
}
inline void swaps(int *a, int x, int y)
{
    int b = a[x];
    a[x] = a[y];
    a[y] = b;
}
int q_partition(int *a, int l, int r)
{
    c++;
    if (l >= r) return l;
    int i = l-1;
    int j = l;
    int x = a[r];
    c += 3;
    for (; j < r; j++) {
        c += 3;
        if (a[j] <= x) {
            i++;
            swaps(a, i, j);
            c += 5;
        }
    }
    swaps(a, i + 1, r);
    c += 4;
    return i + 1;
}
void quicksort(int *a, int l, int r)
{
    if (l >= r) return;
    int pivot = q_partition(a, l, r);
    quicksort(a, l, pivot - 1);
    quicksort(a, pivot + 1, r);
}
void cp(int *a, int *q, int n)
{
    for (int i = 0; i < n; i++) q[i] = a[i];
}
void tester()
{
    vector<int> v;
    v.push_back(0);
    int a[2000000];

    string s1 = "";
    string s2 = "";
    for (int step = 2; step < 1000; step++) {
        //step is the length to be tested
        cout << step << endl;

        int n = step, t = 0;
        ll m=0;
        ld avgs = 0;

        for (int times = 0; times < 1000; times++) {

        // form a random array
            for (int i = 0; i < n; i++) { a[i] = rand(); }

            c = 0;
            quicksort(a, 0, n - 1);
            avgs += c;
            m = max(m, c);
            t++;
        }
        //this is the theoritical worst case of this quicksort O(n^2)
        for (int i = 0; i < n; i++) { a[i] = n - i; }
        c = 0;
        quicksort(a, 0, n - 1);
        avgs += c;
        m = max(m, c);
        t++;

        s1 += to_string(avgs / t) + ",";
        s2 += to_string(m) + ",";
    }
    cout << s1 << endl;
    cout << s2 << endl;
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie (nullptr);
    cout.tie(nullptr);
    cout << fixed;
    tester();
    return 0;
}
