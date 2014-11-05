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
    int *a, *fen;
    node(int l, int r, int *val) : l(l), r(r) {
        int len = r-l+1;
        a = new int[len];
        fen = new int[len];
        forn(i, r-l+1) a[i] = fen[i] = 0;
//         clr(a); clr(fen);
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

            merge(la, la+ls, ra, ra+rs, a);
        }
    }

    int fen_get(int i) {
        for (; i >= 0; i = (i&(i+1))-1)
            if (fen[i]) {
                return 1;
            }
        return 0;
    }
    void fen_put(int i) {
        for (; i < (r-l+1); i |= (i+1)) {
            ++fen[i];
        }
    }
    int get(int lq, int rq, int x) {
        int pos = upper_bound(a, a+(r-l+1), x) - a - 1;
        if (lq <= l && rq >= r) {
            return fen_get(pos);
        } else if (lq > r || rq < l) {
            return 0;
        } else {
            return L->get(lq, rq, x) || R->get(lq, rq, x);
        }
    }
    void put(int i, int x) {
        int pos = lower_bound(a, a+(r-l+1), x) - a;
        assert(a[pos] == x);
        fen_put(pos);
        if (l != r) {
            if (i <= (l+r)/2) L->put(i, x);
            else R->put(i, x);
        }
    }
};

int n;
int a[maxn], b[maxn];
int pa[maxn], pb[maxn];
int pba[maxn];
node *t;

int fen[maxn];
int get(int i) {
    int mx = inf;
    for (; i >= 0; i = (i&(i+1))-1) {
        mx = min(mx, fen[i]);
    }
    return mx;
}
void put(int i, int x) {
    for (; i < n; i |= (i+1)) {
        fen[i] = min(fen[i], x);
    }
}

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
//     cout << "failed on " << x << endl;
    assert(false);
//     printf("ololo");
//     assert(false);
}

void solve() {
    forn(i, n) fen[i] = inf;
    ford(i, n) {
//         cout << "add " << pa[i] << " " << pb[i] << endl;
        if (get(pa[i]) < pb[i]) {
            found(i);
            return;
        }
        put(pa[i], pb[i]);
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
