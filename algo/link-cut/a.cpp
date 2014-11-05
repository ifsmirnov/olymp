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
const int maxn = 300500;

int val[maxn];

struct node {
    int x, y, s, ix;
    int mx;
    bool rev;
    node *l, *r, *p, *a;
    node(){}
    node(int x): x(x), y(rand()),
            s(1), ix(1), rev(false), l(r=p=a=NULL) {}
};

void out(node*, bool=true);
node* norm(node* t);
node* upd(node* t);

inline node* rev(node* t) {
    if (t) t->rev ^= 1;
    return t;
}
inline node* getp(node* t) {
    while (t && t->p) t = t->p;
    return t;
}
int pos(node* t) {
    static node* b[1000];
    int pb = 1;
    b[0] = t;
    while (t->p) {
        b[pb++] = t->p;
        t = t->p;
    }
    ford(i, pb) {
        norm(b[i]);
    }
    t = b[0];
    assert(!t->rev);
    int res = t->ix - 1;
    while (t->p) {
        assert(!t->p->rev);
        if (t == t->p->r) {
            res += t->p->ix;
        }
        t = t->p;
    }
    return res;
}

inline node* upd(node* t) {
    if (t) {
        if (t->rev) {
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
            swap(t->l, t->r);
            t->rev = 0;
        }
    }
    return t;
}

inline node* norm(node* t) {
    if (t) {
        upd(t);
        t->s = 1;
        t->mx = t->x;
        if (t->l) {
            t->l->a = NULL;
            t->s += t->l->s;
            t->l->p = t;
            if (val[t->l->mx] > val[t->mx]) {
                t->mx = t->l->mx;
            }
        }
        t->ix = t->s;
        if (t->r) {
            t->r->a = NULL;
            t->s += t->r->s;
            t->r->p = t;
            if (val[t->r->mx] > val[t->mx]) {
                t->mx = t->r->mx;
            }
        }
    }
    return t;
}

void split(node* t, node *&l, node *&r, int k) {
    norm(t);
    if (!t) return (void)(l=r=NULL);
    if (t->ix > k) {
        split(t->l, l, t->l, k);
        r = norm(t);
    } else {
        split(t->r, t->r, r, k-t->ix);
        l = norm(t);
    }
    if (l) l->p = NULL;
    if (r) r->p = NULL;
}
void split(node* t, node *&l, node *&m, node *&r, int lq, int rq) {
    split(t, t, r, rq+1);
    split(t, l, m, lq);
}

node* merge(node* l, node* r) {
    if (!l) return r;
    if (!r) return l;
    if (r->y > l->y) {
        norm(r);
        r->l = merge(l, r->l);
        return norm(r);
    } else {
        norm(l);
        l->r = merge(l->r, r);
        return norm(l);
    }
}

void verygood(node* t) {
    norm(t);
    if (t) {
        verygood(t->l);
        verygood(t->r);
    }
}

node *gright(node* t) {
    upd(t);
    while (t && t->r) {
        t = upd(t->r);
    }
    return t;
}
node *gleft(node* t) {
    upd(t);
    while (t && t->l) {
        t = upd(t->l);
    }
    return t;
}

bool check(node* t) {
    if (t) return true;
    if (t->l) {
        if (!check(t->l) || t->l->p != t) return false;
    }
    if (t->r) {
        if (!check(t->r) || t->r->p != t) return false;
    }
    return true;
}

template<typename ... Args>
node* merge(node* l, node* r, Args ... args) {
    return merge(merge(l, r), args ...);
}

void treapTests() {
    node* a[20];
    node* t = NULL;
    forn(i, 20) t = merge(t, a[i] = new node(i));
    assert(check(t));
    forn(i, 20) {
        assert(getp(a[i]) == t);
        assert(pos(a[i]) == i);
    }
    node *l, *m, *r;
    forn(III, 2) {
        split(t, l, m, r, 5, 8);
        rev(m);
        t = merge(l, m, r);
    }
    assert(check(t));
    forn(i, 20) {
        assert(getp(a[i]) == t);
        assert(pos(a[i]) == i);
    }
}

int n;

void out(node* t, bool st) {
    norm(t);
    if (t) {
        out(t->l, false);
        if (t->x < n) cout << t->x << " ";
        else cout << "[" << val[t->x] << "] ";
        out(t->r, false);
    }
    if (st) cout << endl;
}

node* mytree[maxn];
int p[maxn];

int make_root(int v, bool toPrint = false) {
    node *res = NULL;
    node *t = mytree[v];
    while (1) {
        int k = pos(t);
        t = getp(t);
        node *nt = t->a;
        node *l, *r;
        split(t, l, r, k+1);
        assert(l);
        if (r) {
            r->a = gright(l);
        }
        res = merge(l, res);
        if (!nt) {
            res->a = NULL;
            break;
        }
        t = nt;
    }
    if (toPrint) out(res);
    int vv = gleft(res)->x;
    rev(res);
    return vv;
}

void eraseEdge(int u, int v) {
    make_root(u);
    node* pu = getp(mytree[u]);
    node* pv = getp(mytree[v]);
    if (pu == pv) {
        assert(pos(mytree[u]) == 0 && 1 == pos(mytree[v]));
        node* tmp1, *tmp2;
        split(pu, tmp1, tmp2, 1);
    } else {
        assert(pv->a == mytree[u]);
        pv->a = NULL;
    }
}

void addEdge(int u, int v) {
    make_root(u);
    assert(make_root(v) != u);
    getp(mytree[v])->a = mytree[u];
}

void printAllTree() {
    ford(i, n) make_root(i);
    forn(i, n) {
        make_root(make_root(i, true));
    }
}

// int val[maxn]; // defined earlier
int u[maxn], v[maxn];
int ne; // = n

i64 ans = 0;

void removeSuperEdge(int id) {
//     cout << "remove edge " << u[id] << " " << v[id] << endl;
    make_root(u[id]);
    assert(make_root(v[id]) == u[id]);

    node *vp = getp(mytree[v[id]]);
    node *tmp;

    split(vp, vp, tmp, 2);
    split(vp, vp, tmp, 1);

//     assert(getp(mytree[u[id]])->s == 1);
    getp(mytree[u[id]])->a = NULL;
    make_root(1);
}

void addSuperEdge(int u, int v, int id, int w) {
//     cout << "add Super Edge " << u << " " << v << ", w =  " << w << endl;
    ::u[id] = u;
    ::v[id] = v;
    val[id] = w;

    make_root(u);
    assert(make_root(v) != u);

    getp(mytree[v])->a = mytree[id];
    mytree[id]->a = mytree[u];
}

void killCycle(int u, int v, int w) {
    make_root(u);
    if (make_root(v) != u) {
//         cerr << u << " " << v << " " << w << endl;
        int id = ne++;
        mytree[id] = new node(id);
        ans += w;
        addSuperEdge(u, v, id, w);
    } else {
        int mx = getp(mytree[v])->mx;
        if (val[mx] > w) {
            removeSuperEdge(mx);
            ans += w-val[mx];
            addSuperEdge(u, v, mx, w);
        }
    }
}

void solve() {
    int m;
    scanf("%d%d", &n, &m);
    ne = n;
    forn(i, n) mytree[i] = new node(i);
    forn(i, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u; --v;
        killCycle(u, v, w);
        printf("%lld\n", ans);
//         cout << "-----\n";
//         printAllTree();
//         cout << "-----\n";
    }

}

void do_something_i_dunno_yet() {
    printAllTree();
    while (1) {
        int u, v, t;
        cin >> t >> u >> v;
        if (t == 0) {
            eraseEdge(u, v);
        } else {
            addEdge(u, v);
        }
        printAllTree();
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
//     freopen("/dev/null", "w", stdout);
#else
    freopen("joy.in", "r", stdin);
    freopen("joy.out", "w", stdout);
#endif

    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
