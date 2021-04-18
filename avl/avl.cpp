#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll MAXN = (ll)1e6 + 7;
const ll INF = (ll)__builtin_huge_vall(); // return float
const ll md = 1000000007;
#define PB       push_back
#define MP       make_pair
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define lp(i, n) for (int i = 0; i < (n); i++)
class avl {
  public:
    class node {
      public:
        int val;
        int h = 0;         // height of a node
        node *p = nullptr; // parent of a node
        node *left = nullptr;
        node *right = nullptr;
        node() { h = 0; }
    };

    node *root = nullptr;
    avl(int val)
    {
        node *tmp = new node();
        tmp->val = val;
        tmp->p = nullptr;
        root = tmp;
        root->h = 0;
    }
    void insert(int val)
    {
        if (root == nullptr) {
            node *tmp = new node();
            tmp->val = val;
            tmp->p = nullptr;
            root = tmp;
            return;
        }
        helper_insert(val, root);
    }
    void preorder_print()
    {
        helper_preprint(root);
        cout << endl;
    }
    void inorder_print()
    {
        helper_inprint(root);
        cout << endl;
    }
    void postorder_print()
    {
        helper_postprint(root);
        cout << endl;
    }
    node *search(int val) { return helper_search(val, root); }
    ~avl() { liber(root); }
    int maximum() { return helper_maximum(root)->val; }
    int minimum() { return helper_minimum(root)->val; }
    void deletes(node *nod) { return hdelete(nod); }
    void right_rotate(node *x) { return rr(x); }
    void left_rotate(node *x) { return lr(x); }
    bool check_balance() { return hcheck_balance(root); }

  private:
    int o(node *nod)
    {
        if (nod == nullptr) return 0;
        return max(o(nod->left), o(nod->right)) + 1;
    }
    bool hcheck_balance(node *nod)
    {
        if (nod == nullptr) return true;
        if (balance(nod) > 1) {
            cout << balance(nod) << " " << height(nod->left) << " "
                 << height(nod->right) << endl;
            cout << o(nod->left) << " " << o(nod->right) << endl;
            return false;
        }
        return hcheck_balance(nod->left) and hcheck_balance(nod->right);
    }
    int balance(node *x)
    {
        // return x == nullptr ? 0 : abs(o(x->right) - o(x->left));
        return x == nullptr ? 0 : abs(height(x->right) - height(x->left));
    }
    void lr(node *y)
    {
        // height of the upper tree isn't fixes
        if (y == nullptr) return;
        node *x = y->right;
        if (x == nullptr) return;
        if (y == root) {
            x->p = nullptr;
            root = x;
        } else {
            x->p = y->p;
            if (y->p->right == y) {
                y->p->right = x;
            } else if (y->p->left == y) {
                y->p->left = x;
            }
        }
        node *a = y->left;
        node *b = x->left;
        node *c = x->right;
        y->p = x;
        x->left = y;
        x->right = c;
        y->left = a;
        y->right = b;
        if (b != nullptr) b->p = y;
        y->h = max(height(y->left), height(y->right)) + 1;
        x->h = max(height(x->left), height(x->right)) + 1;
        if (x->p != nullptr)
            x->p->h = max(height(x->p->left), height(x->p->right)) + 1;
    }
    void rr(node *x)
    {
        // height of the upper tree isn't fixes
        if (x == nullptr) return;
        node *y = x->left;
        if (y == nullptr) return;
        if (x == root) {
            root = y;
            y->p = nullptr;
        } else {
            if (x->p->left == x) {
                x->p->left = y;
            } else if (x->p->right == x) {
                x->p->right = y;
            }
            y->p = x->p;
        }
        x->p = y;
        node *a = y->left;
        node *b = y->right;
        node *c = x->right;
        y->left = a;
        y->right = x;
        x->right = c;
        x->left = b;
        y->h = max(height(y->left), height(y->right)) + 1;
        x->h = max(height(x->left), height(x->right)) + 1;
        if (b != nullptr) b->p = x;
        if (y->p != nullptr)
            y->p->h = max(height(y->p->left), height(y->p->right)) + 1;
    }

    void transplant(node *u, node *v)
    {
        if (u->p == nullptr) {
            this->root = v;
        } else if (u == u->p->left) {
            u->p->left = v;
        } else {
            u->p->right = v;
        }
        if (v != nullptr) v->p = u->p;
        delete u;
    }
    void hdelete(node *nod)
    {

        if (nod == nullptr) return;
        if (nod->left == nullptr and nod->right == nullptr) {
            transplant(nod, nullptr);
            return;
        }
        if (nod->left == nullptr) {
            transplant(nod, nod->right);
            return;
        }
        if (nod->right == nullptr) {
            transplant(nod, nod->left);
            return;
        }
        node *y = helper_minimum(nod->right);
        nod->val = y->val;
        transplant(y, y->right);
        // balancer(nod);
    }
    void balancer(node *nod)
    {
        while (nod != nullptr) {
            if (balance(nod) > 1) {
                if (height(nod->left) > height(nod->right)) {
                    rr(nod);
                } else {
                    lr(nod);
                }
            }
            nod = nod->p;
        }
    }
    node *helper_minimum(node *nod)
    {
        if (nod->left == nullptr) return nod;
        return helper_minimum(nod->left);
    }
    node *helper_maximum(node *nod)
    {
        if (nod->right == nullptr) return nod;
        return helper_maximum(nod->right);
    }
    node *helper_search(int val, node *nod)
    {
        if (val == nod->val) return nod;
        if (val > nod->val) {
            if (nod->right != nullptr) return helper_search(val, nod->right);
            return nullptr;
        }
        if (val < nod->val) {
            if (nod->left != nullptr) return helper_search(val, nod->left);
            return nullptr;
        }
        return nullptr;
    }
    void liber(node *nod)
    {
        node *l = nod->left;
        node *r = nod->right;
        if (l == nullptr and r == nullptr) {
            delete nod;
            return;
        }
        if (l != nullptr) { liber(nod->left); }
        if (r != nullptr) { liber(nod->right); }
        delete nod;
    }
    void helper_preprint(node *nod)
    {
        cout << nod->val << ' ';
        if (nod->left != nullptr) { helper_preprint(nod->left); }
        if (nod->right != nullptr) { helper_preprint(nod->right); }
        return;
    }
    void helper_inprint(node *nod)
    {
        if (nod->left != nullptr) { helper_inprint(nod->left); }
        cout << nod->val << ' ';
        if (nod->right != nullptr) { helper_inprint(nod->right); }
    }
    void helper_postprint(node *nod)
    {
        if (nod->left != nullptr) { helper_postprint(nod->left); }
        if (nod->right != nullptr) { helper_postprint(nod->right); }
        cout << nod->val << ' ';
        return;
    }
    void helper_insert(int val, node *nod)
    {
        if (val > nod->val) {
            if (nod->right == nullptr) {
                node *tmp = new node();
                tmp->val = val;
                nod->right = tmp;
                tmp->p = nod;
            } else
                helper_insert(val, nod->right);
        }
        if (val <= nod->val) {
            if (nod->left == nullptr) {
                node *tmp = new node();
                tmp->val = val;
                nod->left = tmp;
                tmp->p = nod;

            } else
                helper_insert(val, nod->left);
        }
        nod->h = max(height(nod->left), height(nod->right)) + 1;
        if (nod->p != nullptr)
            nod->p->h = max(height(nod->left), height(nod->right)) + 1;
        if (balance(nod) <= 1) return;
        // left
        if (val <= nod->val) {
            // left left
            if (val <= nod->left->val) {
                rr(nod);
            }
            // left right
            else if (val > nod->left->val) {
                lr(nod->left);
                rr(nod);
            }
        }
        // right
        else if (val > nod->val) {
            // right left
            if (val <= nod->right->val) {
                rr(nod->right);
                lr(nod);
            }
            // right right
            else if (val > nod->right->val) {
                lr(nod);
            }
        }
        nod->h = max(height(nod->left), height(nod->right)) + 1;
        if (nod->p != nullptr)
            nod->p->h = max(height(nod->left), height(nod->right)) + 1;
    }
    int height(node *nod)
    {
        if (nod == nullptr) return -1;
        return nod->h;
    }
};
void print2DUtil(avl::node *root, int space)
{

    int COUNT = 15;
    if (root == NULL) return;

    space += COUNT;
    print2DUtil(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    printf("%d\n", root->val);
    print2DUtil(root->left, space);
}
void solve()
{
    avl tree = avl(10);
    int i = 50;
    vector<int> s;
    srand(time(NULL));
    while (i--) {
        int x = rand();
        tree.insert(x);
        s.PB(x);
    }
    cout << tree.check_balance() << endl;
    // print2DUtil(tree.root, 20);
    i = 20;
    random_shuffle(all(s));
    while (i--) {
        cout << "eer" << endl;
        int a = s[s.size() - 1];
        s.pop_back();
        tree.deletes(tree.search(a));
    }
    // print2DUtil(tree.root, 20);


    // tree.preorder_print();
    // tree.inorder_print();
    // cout << endl;
    cout << tree.check_balance() << endl;


    // tree.preorder_print();
    // tree.deletes(tree.search(6));
    // cout<<tree.check_balance();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed;
    // freopen("f.in", "r", stdin);
    int times = 1;
    // cin>>times;
    while (times--) { solve(); }
    return 0;
}
