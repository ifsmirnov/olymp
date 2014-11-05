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
const int maxn = 200500;

#define assert(x) 

int p[maxn], rk[maxn];
void init(int n) {
    forn(i, n) p[i] = i, rk[i] = 0;
}
inline int get(int v) {
    while (v != p[v]) v = p[v];
    return v;
}
int stmp[100], dp;
inline int getfast(int v) {
    dp = 1;
    stmp[0] = v;
    while (v != p[v]) {
        stmp[dp++] = v = p[v];
    }
    forn(i, dp) p[stmp[i]] = v;
    return v;
}
inline bool unite(int x, int y, bool fast) {
    if (fast) {
        x = getfast(x);
        y = getfast(y);
    } else {
        x = get(x);
        y = get(y);
    }
    if (x == y) return false;
    if (rk[x] == rk[y]) ++rk[x];
    if (rk[x] > rk[y]) p[y] = x;
    else p[x] = y;
    return true;
}

struct Edge {
    int u, v, w, id;
    bool operator<(const Edge& e) const {
        return w < e.w;
    }
};

int n, m;
Edge e[maxn];
int use[maxn];
i64 res[maxn];

int cs = 0;
Edge *cur = new Edge[maxn];
Edge *tmp = new Edge[maxn];
int revp[maxn];
int local_ban[maxn];

// save DSU state
int np;
int prs[maxn];
int pp[maxn], pr[maxn];

void save() {
    forn(i, np) {
        pp[i] = p[prs[i]];
        pr[i] = rk[prs[i]];
    }
}
void restore() {
    forn(i, np) {
        p[prs[i]] = pp[i];
        rk[prs[i]] = pr[i];
    }
}

void clear_cur() {
    int n = cs;
    cs = 0;
    forn(i, n) if (use[cur[i].id]) {
        tmp[cs++] = cur[i];
    }
    swap(cur, tmp);
}

void process(int l, int r) {
    // add all edges in interval [l, r] assuming p contains correct info
    // about edges from 0 to l-1

    sort(e+l, e+r+1);
    merge(cur, cur+cs, e+l, e+r+1, tmp);
    swap(cur, tmp);
    cs += r-l+1;
    // cur: all edges from 0 to r, sorted

    // fill del and create useful edges
    init(n);
    int ptr = 0;
    forn(i, cs) {
        if (!unite(cur[i].u, cur[i].v, true) && use[cur[i].id]) {
            tmp[ptr++] = cur[i];
            use[cur[i].id] = false;
        }
        if (cur[i].id >= l) {
            tmp[ptr++] = cur[i];
        }
    }
    init(n);
    int mx = 0;
    i64 w = 0;
    forn(i, cs) if (cur[i].id < l && use[cur[i].id]) {
        if (unite(cur[i].u, cur[i].v, true)) {
            w += cur[i].w;
            mx = max(mx, cur[i].w);
        }
    }

    // debug output
//     cout << "Useful edges on stage " << l << " " << r << endl;
//     forn(i, ptr) cout << tmp[i].u << " " << tmp[i].v << " " << tmp[i].w << endl;
//     cout << endl;

    // save dsu state
    np = 0;
    forn(i, ptr) {
        prs[np++] = get(tmp[i].u);
        prs[np++] = get(tmp[i].v);
    }
    sort(prs, prs+np);
    np = unique(prs, prs+np) - prs;
    save();

    // proceed queries
    sort(tmp, tmp+ptr);
    forn(i, ptr) revp[tmp[i].id] = i;
    i64 tw = w;
    int tmx = mx;
    for (int T = l; T <= r; ++T) {
        if (T != l && T != r) {
            int pos = revp[T];
            if (unite(tmp[pos].u, tmp[pos].v, false)) {
                tw += tmp[pos].w;
                tmx = max(tmx, tmp[pos].w);
                res[T] = tw;
                continue;
            }
//             if (tmp[pos].w > tmx) {
//                 continue;
//             }
        }
        if (T != l) {
            restore();
        }
        tw = w;
        tmx = mx;
        forn(i, ptr) if (tmp[i].id <= T) {
            if (local_ban[i] == r) {
                continue;
            }
            if (unite(tmp[i].u, tmp[i].v, false)) {
                tw += tmp[i].w;
                tmx = max(tmx, tmp[i].w);
                if (T == r) {
                    assert(tmp[i].id >= l);
                    use[tmp[i].id] = 1;
                }
            } else {
                local_ban[i] = r;
            }
        }
        res[T] = tw;
    }
    clear_cur();
}

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        --e[i].u;
        --e[i].v;
        e[i].id = i;
    }
}

void solve() {
    const int K = 700;
    int l = 0, r = K;
    while (l < m) {
        process(l, min(r, m) - 1);
        l += K;
        r += K;
    }

    forn(i, m) printf("%lld\n", res[i]);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("joy.in", "r", stdin);
    freopen("joy.out", "w", stdout);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
