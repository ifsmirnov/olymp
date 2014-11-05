#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <ctime>
#include <queue>
#include <set>
#include <map>
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

struct summator {
    summator(int l, int r) {
        a.resize(r-l+1);
    }
    void upd(int l, int r, int x) {
        fore(i, l, r) a[i] = x;
    }
    int get(int l, int r) {
        return accumulate(a.begin()+l, a.begin()+r+1, 0);
    }
    int gets() { return accumulate(all(a), 0); }
    vi a;
};

struct node {
    int l, r;
    node *L, *R;
    int val, s;
    node(int l, int r) : l(l), r(r) {
        if (l == r) {
            L = R = NULL;
            val = s = 0;
        } else {
            L = new node(l, (l+r)/2);
            R = new node((l+r)/2+1, r);
            val = -1;
            s = 0;
        }
    }
    void push() {
        if (L && val != -1) {
            L->val = val;
            R->val = val;
            s = val * (r-l+1);
            val = -1;
        }
    }
    int gets() {
        if (val == -1)
            return s;
        else
            return val * (r-l+1);
    }
    void norm() {
        if (L && val == -1) s = L->gets() + R->gets();
    }
    int get(int lq, int rq) {
        if (lq <= l && rq >= r) {
            return gets();
        } else if (lq <= r && rq >= l) {
            if (val != -1) {
                return val * (min(r, rq) - max(l, lq) + 1);
            } else {
                return L->get(lq, rq) + R->get(lq, rq);
            }
        }
        return 0;
    }
    void upd(int lq, int rq, int x) {
        if (lq <= l && rq >= r) val = x;
        else if (lq <= r && rq >= l) {
            push();
            L->upd(lq, rq, x);
            R->upd(lq, rq, x);
            norm();
        }
    }
    template<typename T>
    void get_values(int lq, int rq, T a[]) {
        if (lq <= r && rq >= l) {
            if (val != -1) {
                fore(i, max(l, lq), min(r, rq)) a[i] = val;
            } else {
                L->get_values(lq, rq, a);
                R->get_values(lq, rq, a);
            }
        }
    }

    template<typename T>
    void set_values(int lq, int rq, T a[]) {
        if (l == r && l >= lq && r <= rq) {
            val = a[l];
        } else if (lq <= r && rq >= l) {
            push();
            L->set_values(lq, rq, a);
            R->set_values(lq, rq, a);
            norm();
        }
    }
};

template<typename A, typename B>
void test() {
    int n = 100000;
    A *a = new A(0, n-1);
    B *b = new B(0, n-1);
    a->upd(0, n-1, 0);
    b->upd(0, n-1, 0);

    forn(i, n) {
        int l = rand() % n;
        int r = rand() % n;
        int c = rand() % 50;
        if (l > r) swap(l, r);
        if (rand()%2) {
            a->upd(l, r, c);
            b->upd(l, r, c);
        } else {
            assert(a->get(l, r) == b->get(l, r));
        }
    }
}

int res1[maxn];
int res2[maxn];
int n, k, q;

namespace pal {

int n, b, e;
int offset;
char s[maxn];
int h[maxn], rh[maxn], p[maxn] = {-1};
const int base = 10099;

inline int geth(int i, int j) {
    return h[j] - (i ? h[i-1] * p[j-i+1] : 0);
}

inline int getrh(int i, int j) {
    i = n-i-1;
    j = n-j-1;
    return rh[i] - (j ? rh[j-1] * p[i-j+1] : 0);
}

bool pal(int i, int j) {
    return geth(i, j) == getrh(i, j);
}

void find_pals(int,int);

void build(int n, int b, int e, char* t, int offset = 0) {
    if (p[0] == -1) {
        p[0] = 1;
        fore(i, 1, maxn-1) p[i] = p[i-1] * base;
    }

    pal::n = n;
    pal::offset = offset;

    forn(i, n) s[i] = t[i];
    forn(i, n) {
        h[i] = s[i];
        if (i) h[i] += h[i-1] * base;
        rh[i] = s[n-i-1];
        if (i) rh[i] += rh[i-1] * base;
    }
    find_pals(b, e);
}

void find_pals(int b, int e) {
    // odd
    fore(i, b, e) {
        int l = 1, r = min(i + 1, n - i) + 1, m;
        r = min(r, (k+1)/2 + 1);
        assert(r == (k+1)/2+1 || offset == 0 || offset + n == ::n);
        while (r-l > 1) {
            m = (l+r)/2;
            if (pal(i-m+1, i+m-1))
                l = m;
            else
                r = m;
        }
        res1[i + offset] = l;
    }
    // even
    fore(i, b, e) {
        if (k == 1 || s[i] != s[i+1]) {
            res2[i + offset] = 0;
            continue;
        }
        int l = 1, r = min(i + 1, n - i - 1) + 1, m;
        r = min(r, k/2 + 1);
        while (r-l > 1) {
            m = (l+r)/2;
            if (pal(i-m+1, i+m))
                l = m;
            else
                r = m;
        }
        res2[i + offset] = l;
    }
}

}

node *even, *odd, *chars;

char s[maxn];

void scan() {
    scanf("%s%d%d", s, &k, &q);
    n = strlen(s);
}

void art_scan() {
    n = 100000;
    k = 50;
    q = 100000;
    forn(i, n) s[i] = rand()%2+'a';
}

void build() {
    pal::build(n, 0, n-1, s);
    even = new node(0, n-1);
    odd = new node(0, n-1);
    chars = new node(0, n-1);

    odd->set_values(0, n-1, res1);
    even->set_values(0, n-1, res2);
    chars->set_values(0, n-1, s);
}

void update(int ls, int lq, int rq, int rs) {
    ls = max(ls, 0);
    lq = max(lq, 0);
    rq = min(rq, n-1);
    rs = min(rs, n-1);

    chars->get_values(ls, rs, s);
    pal::build(rs-ls+1, lq-ls, rq-ls, s+ls, ls);
    odd->set_values(lq, rq, res1);
    even->set_values(lq, rq, res2);

}

void update(int l, int r, int c) {
    const static int small = k/2+2;
    const static int large = k+3;

    chars->upd(l, r, c);
    update(l - large, l - small, l + small, l + large);
    update(r - large, r - small, r + small, r + large);

    int lq = l + small + 1, rq = r - small - 1;
    if (lq <= rq) {
        odd->upd(lq, rq, (k+1)/2);
        even->upd(lq, rq, k/2);
    }
}

int get(int l, int r) {
    int lq = min(l + k/2 + 2, n - 1);
    int rq = max(r - k/2 - 2, 0);

    int res = 0;
    if (lq+1 <= rq-1) {
        res += even->get(lq+1, rq-1) + odd->get(lq+1, rq-1);

        odd->get_values(l, lq, res1);
        even->get_values(l, lq, res2);
        fore(i, l, lq) {
            res += min(res1[i], min(i - l + 1, r - i + 1));
            res += min(res2[i], min(i - l + 1, r - i));
        }

        odd->get_values(rq, r, res1);
        even->get_values(rq, r, res2);
        fore(i, rq, r) {
            res += min(res1[i], min(i - l + 1, r - i + 1));
            res += min(res2[i], min(i - l + 1, r - i));
        }
    } else {
        odd->get_values(l, r, res1);
        even->get_values(l, r, res2);
        fore(i, l, r) {
            res += min(res1[i], min(i - l + 1, r - i + 1));
            res += min(res2[i], min(i - l + 1, r - i));
        }
    }
    return res;
}

void solve() {
    int x, l, r;
    char t[10];
    forn(i, q) {
        scanf("%d%d%d", &x, &l, &r);
        if (x == 2) {
            printf("%d\n", get(l-1, r-1));
        } else {
            scanf("%s", t);
            update(l-1, r-1, t[0]);
        }
    }
}
void art_solve() {
    int x, l, r;
    forn(i, q) {
        l = rand()%n+1;
        r = rand()%n+1;
        if (l>r) swap(l,r);
//         if (x == 2) {
        if (rand()%10 == 0) {
            get(l-1, r-1);
        } else {
            update(l-1, r-1, rand()%26+'a');
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scan();
//     art_scan();
    build();
    solve();
//     art_solve();

#ifdef HOME
//     cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
