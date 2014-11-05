#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstring>
#include <cstdlib>
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
#define clr(a) memset(a, 0, sizeof a);
const int maxn = 1000500;

struct node {
    int l, r;
    node *L, *R;
    int *a, *lp, *rp, *fen;
    node(int l, int r, int *val) : l(l), r(r) {
        int len = r-l+1;
        a = new int[len];
        lp = new int[len + 1];
        rp = new int[len + 1];
        fen = new int[len + 1];
        clr(a); clr(lp); clr(rp); clr(fen);
        if (l == r) {
            L = R = NULL;
            a[0] = val[l];
        } else {
            L = new node(l, (l+r)/2, val);
            R = new node((l+r)/2+1, r, val);

            int* la = L->a;
            int* ra = R->a;
            int ls = L->r - L->l + 1;
            int rs = R->r - R->l + 1;

            for (int i = 0, j = 0; i < ls || j < rs; ) {
                lp[i+j] = i;
                rp[i+j] = j;
                if (j == rs || la[i] < ra[j]) {
                    a[i+j] = la[i];
                    ++i;
                } else {
                    a[i+j] = ra[j];
                    ++j;
                }
            }
            lp[ls+rs-1] = ls;
            rp[ls+rs-1] = rs;
        }
    }

    int fen_get(int i) {
        for (; i >= 0; i = (i&(i+1))-1)
            if (fen[i])
                return 1;
        return 0;
    }
    void fen_put(int i) {
        for (; i < (r-l+1); i |= (i+1)) {
            ++fen[i];
        }
    }
    int get(int lq, int rq, int x, int pos = -1) {
        if (pos == -1) {
            pos = lower_bound(a, a+(r-l+1), x) - a;
//             cout << "pos for " << x << " = " << pos << endl;
        }
        if (lq <= l && rq >= r) {
            return fen_get(pos);
        } else if (lq > r || rq < l) {
            return 0;
        } else {
            return L->get(lq, rq, x, lp[pos]) || R->get(lq, rq, x, rp[pos]);
        }
    }
    void put(int i, int x, int pos = -1) {
        if (pos == -1) {
            pos = lower_bound(a, a+(r-l+1), x) - a;
//             cout << "pos for " << x << " = " << pos << endl;
        }
        fen_put(pos);
        if (l != r) {
            if (i <= (l+r)/2) L->put(i, x, lp[pos]);
            else R->put(i, x, rp[pos]);
        }
    }
};

int n;
int a[maxn], b[maxn];
int pa[maxn], pb[maxn];
int pba[maxn];
node *t;

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d", &a[i]), --a[i];
    forn(i, n) scanf("%d", &b[i]), --b[i];
    forn(i, n) pa[a[i]] = i, pb[b[i]] = i;
    forn(i, n) pba[i] = pb[a[i]];
}

void found(int x) {
    forn(i, n) if (i > x && pa[i] < pa[x] && pb[i] < pb[x]) {
        printf("%d %d\n", x+1, i+1);
        return;
    }
    assert(false);
}

void solve() {
    t = new node(0, n-1, pba);
    ford(i, n) {
        if (t->get(0, pa[i], pb[i])) {
            found(i);
            return;
        }
        t->put(pa[i], pb[i]);
    }
    printf("-1\n");
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
