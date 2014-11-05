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

struct T {
    T(): a(0), b(0) {}
    T(i64 x, i64 y): a(x), b(y) {}
    T operator+(const T& t) const {
        return T(a+t.a, b+t.b);
    }
    T& operator+=(const T& t) {
        return *this = *this + t;
    }
    T operator*(int x) const {
        return T(a*x, b*x);
    }
    i64 a, b;
};

struct node {
    int l, r;
    node *L, *R;
    T add, s;
    node() {}
    node(int lq, int rq) {
        l = lq; r = rq;
        if (l == r) {
            L = R = NULL;
        } else {
            L = new node(l, (l+r)/2);
            R = new node((l+r)/2+1, r);
        }
    }

    // s : current info not including val here and above

    T get() {
        return s + add * (r-l+1);
    }
    void push() {
        if (L) {
            L->add += add;
            R->add += add;
            s = L->get() + R->get();
        } else {
            s = add * (r-l+1);
        }
        add = T(0,0);
    }
    T get(int lq, int rq) {
        if (lq <= l && rq >= r) {
            return get();
        } else if (lq > r || rq < l) {
            return T(0,0);
        } else {
            push();
            return L->get(lq, rq) + R->get(lq, rq);
        }
    }
    void upd(int lq, int rq, T t) {
        if (lq <= l && rq >= r) {
            add += t;
        } else if (lq > r || rq < l) {
        } else {
            push();
            L->upd(lq, rq, t);
            R->upd(lq, rq, t);
            push();
        }
    }
};

int n, w, h, q;

struct ev {
    int y;
    int x1, x2;
    int type; // -maxn+1: begin; -maxn+2: end; x/~x: query
    ev(){}
    ev(int y, int x1, int x2, int type): y(y), x1(x1), x2(x2), type(type) {}

    bool operator<(const ev& o) const {
        return y < o.y || (y == o.y && type < o.type);
    }
};
ev e[maxn * 4];
i64 res[maxn];
int ne;

void scan() {
    scanf("%d%d%d%d", &n, &q, &w, &h);
    forn(i, n) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        --x2;
        e[ne++] = ev(y1, x1, x2, -maxn-1);
        e[ne++] = ev(y2, x1, x2, -maxn-2);
    }
    forn(i, q) {
        int x, y;
        scanf("%d%d", &x, &y);
        e[ne++] = ev(y, x, x+w-1, i);
        e[ne++] = ev(y+h, x, x+w-1, ~i);
    }
}

void solve() {
    sort(e, e+ne);
    node* t = new node(0, 1000100);
    forn(i, ne) {
        ev& e = ::e[i];
        if (e.type == -maxn-1) { // add rect
            t->upd(e.x1, e.x2, T(1, -e.y));
        } else if (e.type == -maxn-2) { // remove rect
            t->upd(e.x1, e.x2, T(-1, e.y));
        } else {
            T v = t->get(e.x1, e.x2);
            i64 val = v.a * e.y + v.b;
            if (e.type >= 0) {
                res[e.type] -= val;
            } else {
                res[~e.type] += val;
            }
        }
    }

    forn(i, q) {
        cout << res[i] << "\n";
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
