// 11:14
#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
const int maxn = 300500;

struct node {
    int x, y;
    node *l, *r;
    int c;
    int ix() const { return 1 + (l?l->c:0); }
    bool ok;
    int mx, mn;
    node(){}
    node(int x): x(x), y(rand()^(rand()<<16)), l(r=NULL), c(1), ok(true), mx(mn=x) {}
};

node* norm(node* t) {
    if (t) {
        t->c = 1;
        t->ok = 1;
        if (t->l) t->c += t->l->c, t->ok &= t->l->ok;
        if (t->r) t->c += t->r->c, t->ok &= t->r->ok;
        t->mx = t->r ? t->r->mx : t->x;
        t->mn = t->l ? t->l->mn : t->x;
        if (t->l) t->ok &= (t->l->mx <= t->x);
        if (t->r) t->ok &= (t->r->mn >= t->x);
    }
    return t;
}

void split(node *t, node *&l, node *&r, int k) {
    if (!t) {
        l = r = NULL;
        return;
    }
    if (t->ix() > k)
        split(t->l, l, t->l, k), r = t;
    else
        split(t->r, t->r, r, k - t->ix()), l = t;
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

node *item(node *t, int x, int y) {
    if (x == t->ix() - 1) {
        t->x = y;
        return norm(t);
    } else if (x < t->ix() - 1) {
        return norm(item(t->l, x, y));
    } else {
        return norm(item(t->r, x - t->ix(), y));
    }
}

void out(node *t) {
    if (t) {
        out(t->l);
        cout << t->x << " ";
        out(t->r);
    }
}

node *t;
int n;
int q;
int a[maxn];

void scan() {
    scanf("%d", &n);
    scanf("%d", &q);
    forn(i, n) {
        int x;
        scanf("%d", &x);
        a[i] = x;
        t = merge(t, new node(x));
    }
}

void solve() {
    int s = 0;
    forn(i, q) {
        int tt, l, r;
        scanf("%d%d%d", &tt, &l, &r);
        --l;--r;
        if (tt == 1) {
            assert(l <= r);
            if (l != r) {
                node *ll, *lp, *m, *rp, *rr;
                split(t, t, rr, r + 1);
                split(t, t, rp, r);
                split(t, t, m, l + 1);
                split(t, ll, lp, l);
                swap(lp->x, rp->x);
                norm(lp);
                norm(rp);
                t = merge(ll, merge(lp, merge(m, merge(rp, rr))));
            }
        } else {
            node *lq, *rq;
            split(t, t, rq, r + 1);
            split(t, lq, t, l);
            if (norm(t)->ok) printf("Ja\n"), s += 1145;
            else printf("Nein\n"), s += 3412;
            s *= 179;
            t = merge(lq, merge(t, rq));
        }
    }
    cerr << s << endl;
}

int main() {
//     freopen("/dev/null", "w", stdout);
//     freopen("input.txt", "r", stdin);
    scan();
    solve();
}
