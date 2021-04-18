/*
 * HEAP SORT
 * and the max heap data structure
 */
#include <bits/stdc++.h>
using namespace std;
class heap {
    // id starts at 1
    // a starts at 0
  public:
    void push(int val)
    {
        a.push_back(val);
        len++;
    }
    void swap(int x, int y)
    {
        int p = a[x];
        a[x] = a[y];
        a[y] = p;
    }
    inline int left(int i) { return 2 * i; }
    inline int right(int i) { return 2 * i + 1; }

    vector<int> a;
    int len = 0;
    int get_max()
    {
        if (len > 0)
            return a[0];
        else {
            cout << "error: heap is empty" << endl;
            exit(0);
        }
    }
    void print()
    {
        for (auto x : a) { cout << x << " "; }
        cout << endl;
    }
    inline bool exists(int id) { return id <= len and id >= 1; }
    bool is_heap(int id)
    {
        // O(n)
        if (!exists(id)) return false;
        if (exists(right(id))) {
            if (a[id - 1] >= a[right(id) - 1] and
                a[id - 1] >= a[left(id) - 1]) {
                return is_heap(right(id)) and is_heap(left(id));
            }
            return false;
        }
        if (exists(left(id))) {
            if (a[id - 1] >= a[left(id) - 1]) { return is_heap(left(id)); }
            return false;
        }
        return true;
    }
    void heapify(int id)
    {

        // two children of id are max-heaps this function makes all the
        // array a max heap theta(lgn)
        if (!exists(id)) return;
        if (exists(right(id))) {
            if (a[right(id) - 1] >= a[left(id) - 1]) {
                if (a[right(id) - 1] > a[id - 1]) {
                    swap(right(id) - 1, id - 1);
                    heapify(right(id));
                }

            } else {
                if (a[left(id) - 1] > a[id - 1]) {
                    swap(left(id) - 1, id - 1);
                    heapify(left(id));
                }
            }
        } else if (exists(left(id))) {
            if (a[left(id) - 1] > a[id - 1]) { swap(left(id) - 1, id - 1); }
        }
    }
    void max_heapify()
    {
        // theta(n)
        for (int i = len / 2; i > 0; i--) { heapify(i); }
    }
    void sort()
    {
        // theta(nlgn)

        int tmp = len;
        max_heapify();
        for (int i = 0; i < tmp; i++) {
            swap(0, len - 1);
            len--;
            heapify(1);
        }
        len = tmp;
    }
    void insert(int val)
    {
        // O(lgn)
        a.push_back(val);
        len++;
        int id = len;
        while (id > 1) {
            if (val > a[id / 2 - 1]) {
                swap(id / 2 - 1, id - 1);
            } else {
                return;
            }
            id = id / 2;
        }
    }
};


int main()
{
    heap he;
    he.push(12);
    he.push(11);
    he.push(10);
    he.push(9);
    he.push(8);
    he.push(7);
    he.push(6);
    he.push(5);
    he.push(4);
    he.push(3);
    he.push(2);
    he.push(1);

    he.print();
    cout << he.is_heap(1) << endl;
    he.max_heapify();
    he.print();
    cout << he.is_heap(1) << endl;
    he.insert(11);
    he.insert(21);
    he.insert(13);
    he.print();
    cout << he.is_heap(1) << endl;
    he.sort();
    he.print();

    cout << he.is_heap(1) << endl;
    return 0;
}
