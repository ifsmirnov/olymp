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
const int maxn = 200500;

struct bset {
    u64 x[4];
    bset() { clear(); }
    void clear() { memset(x, 0, sizeof x); }
    int get(int i) { return 0 != (x[i/64]&(1ull<<(i%64))); }
    void set(int i, int v) {
        if (v) x[i/64] |= (1ull<<(i%64));
        else x[i/64] &=~ (1ull<<(i%64));
    }
    void operator|=(const bset& b) {
        forn(i, 4) x[i] |= b.x[i];
    }
    bool operator&(const bset& b) {
        forn(i, 4) if (x[i]&b.x[i]) return true;
        return false;
    }
};

int n, k;
vi e[maxn];

bset b[maxn][18];

void scan() {
    int m;
    scanf("%d%d%d", &n, &m, &k);
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
    forn(v, n) {
        sort(all(e[v]));
        e[v].erase(unique(all(e[v])), e[v].end());
    }
}

void build(int l, int r, int level) {
    int len = r-l+1;
    if (len <= k) return;
    int lq = l + (len-k)/2;
    int rq = r - (len-k+1)/2;

    // positive
    fore(i, lq, r) {
        if (i <= rq) b[i][level].set(i-lq, 1);
        for (auto to: e[i]) if (to > i && to <= r)
            b[to][level] |= b[i][level];
    }
    fore(i, lq, rq) b[i][level].clear();
    for (int i = rq; i >= l; --i) {
        if (i >= lq) {
            b[i][level].set(i-lq, 1);
        }
        for (auto to: e[i]) if (to < i && to >= l)
            b[to][level] |= b[i][level];
    }

    int m = (l+r)/2;
    build(l, m, level + 1);
    build(m+1, r, level + 1);
}

int cb;
int bb[maxn];
bool dfs(int v, int t) {
    bb[v] = cb;
    for (auto to: e[v]) {
        if (to > t || to < v) continue;
        if (to == t) return true;
        if (bb[to] != cb && dfs(to, t)) return true;
    }
    return false;
}

bool get(int lq, int rq, int l, int r, int level) {
    int len = r-l+1;
    int m = (l+r)/2;
    if (rq <= m) {
        return get(lq, rq, l, m, level + 1);
    } else if (lq >= m+1) {
        return get(lq, rq, m+1, r, level + 1);
    }

    int lp = l + (len-k)/2;
    int rp = r - (len-k+1)/2;
    assert(lq < lp || rq > rp);
    if (rq <= rp) {
        assert(rq >= lp);
        return b[lq][level].get(rq - lp);
    } else if (lq >= lp) {
        assert(lq <= rp);
        return b[rq][level].get(lq - lp);
    } else {
        return b[rq][level]&b[lq][level];
    }
}

bool query(int s, int t) {
    if (s == t) return false;
    ++cb;
    if (s > t) swap(s, t);
    if (t-s+1 <= k+1) return dfs(s, t);
    else {
        int p = get(s, t, 0, n-1, 0);
//         int r = dfs(s, t);
//         cout << p << endl;
//         assert(r == p);
        return p;
    }
}

void solve() {
    build(0, n-1, 0);

//     forn(i, n) {
//         fore(j, 0, n-1) cout << query(i, j) << " ";
//         cout << endl;
//     }
// 
//     return;
    int q;
    scanf("%d", &q);
    vi res;
    int last = -1;
    forn(i, q) {
        int x;
        scanf("%d", &x), --x;
        if (last == -1 || query(last, x)) {
            res.pb(x);
            last = x;
        }
    }
    printf("%d\n", (int)res.size());
    forn(i, res.size()) {
        printf("%d ", res[i]+1);
    }
    printf("\n");
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
