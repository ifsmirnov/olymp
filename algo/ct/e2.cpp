#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
const int inf = 1e9+100500;
const int maxn = 100500;

struct node {
    int x, y;
    int c;
    node *l, *r, *p;
    node(){}
    node(int x):x(x), y(rand()), c(1), l(r=p=NULL) {}

    bool isl() const { return p && p->l == this; }
    bool isr() const { return p && p->r == this; }
};

int cnt = 0;
inline node* norm(node* t) {
    ++cnt;
    if (t) {
        t->c = 1;
        if (t->l) {
            t->c += t->l->c;
            t->l->p = t;
        }
        if (t->r) {
            t->c += t->r->c;
            t->r->p = t;
        }
    }
    return t;
}

void split(node* t, node *&l, node *&r, int x) {
    if (!t) return (void)(l=r=NULL);
    if (x < t->x)
        split(t->l, l, t->l, x), r = t;
    else
        split(t->r, t->r, r, x), l = t;
    t->p = NULL;
    norm(t);
}

node *merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (r->y > l->y) {
        r->l = merge(l, r->l);
        return norm(r);
    } else {
        l->r = merge(l->r, r);
        return norm(l);
    }
}

inline node *find(node *t, int x) {
    node *lst = t;
    while (t) {
        if (t->x == x) return t;
        if (t->x < x) {
            lst = t;
            t = t->r;
        } else {
            t = t->l;
        }
    }
    return lst;
}

void fast_split(node *t, node *&l, node *&r, int x) {
    if (!t) return (void)(l=r=NULL);
    t = find(t, x);
    node *ll = t, *lr = t->r;
    if (lr) lr->p = NULL;
    t->r = NULL;
    norm(lr);
    norm(ll);
    bool lturn = true;
    while (t->p) {
        if (t->isl()) {
            t = t->p;
            if (lturn) {
                ll->p = NULL;
                t->l = lr;
            }
            lturn = 0;
            lr = t;
        } else {
            t = t->p;
            if (!lturn) {
                lr->p = NULL;
                t->r = ll;
            }
            lturn = 1;
            ll = t;
        }
        norm(t);
    }
    l = ll;
    r = lr;
}

void out(node *t, bool lst = true) {
    if (t) {
        out(t->l, 0);
        cout << t->x << " ";
        out(t->r, 0);
    }
    if (lst) cout << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int n = 3500000;
    node *t = NULL;
    forn(i, n) t = merge(t, new node(i));
    i64 cc = clock();
    forn(i, n) {
        node *l, *r;
        fast_split(t, l, r, i);
//         split(t, l, r, i);
//         out(l);
//         out(r);
//         assert(!l || l->c == i+1);
//         assert(!r || r->c == 9-i);
//         cout << endl;
        t = merge(l, r);
    }

    cerr << "cnt = " << cnt << endl;
#ifdef HOME
    cerr << "Time elapsed: " << (clock()-cc) / 1000 << " ms" << endl;
#endif
    return 0;
}
