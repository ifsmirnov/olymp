#include <iostream>
#include <algorithm>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)

struct node {
    int val, y;
    int c;
    node *l, *r;
    node(int val) : val(val), y(rand()), c(1), l(r=NULL) {}
    int ix() const {
        if (l) return l->c + 1;
        else return 1;
    }
};

node* norm(node* t) {
    if (t) {
        t->c = 1;
        if (t->l) {
            t->c += t->l->c;
        }
        if (t->r) {
            t->c += t->r->c;
        }
    }
    return t;
}

void split(node* t, node *&l, node *&r, int k) {
    if (!t) {
        l = r = NULL;
        return;
    }
    norm(t);
    if (k < t->ix())
        split(t->l, l, t->l, k), r = t;
    else
        split(t->r, t->r, r, k - t->ix()), l = t;
    norm(t);
}

node* merge(node *l, node *r) {
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

void out(node *t, bool fin=true) {
    if (t) {
        out(t->l, false);
        cout << t->val << " ";
        out(t->r, false);
    }
    if (fin) cout << endl;
}

int main() {
    int n = 10;
    node *t = NULL;
    forn(i, n) t = merge(t, new node(i));
    out(t);
    node *l,  *r;
    split(t, l, r, 5);
    t = merge(r, l);
    out(t);
}
