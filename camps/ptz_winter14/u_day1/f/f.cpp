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

int n, m, K;
int ne;
int to[maxn], w[maxn], c[maxn];

vi e[maxn];

void addEdge(int u, int v, int w0, int c0) {
    to[ne] = v; w[ne] = w0; c[ne] = c0; e[u].pb(ne++);
    to[ne] = u; w[ne] = -w0; c[ne] = 0; e[v].pb(ne++);
}

bool scan() {
    if (scanf("%d%d%d", &n, &m, &K) != 3) return false;

    forn(i, n) e[i].clear();

    ne = 0;
    forn(i, m) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, 1, c);
        addEdge(b, a, 1, c);
    }

    return true;
}

int s, t;
int q[maxn], inq[maxn], d[maxn], anc[maxn];
pii fb() { // weight, len
    int lq = 0, rq = 1;
    forn(i, n) d[i] = inf, inq[i] = false;
    q[0] = s;
    d[s] = 0;
    while (lq != rq) {
        int v = q[lq++];
        if (lq == maxn) lq = 0;
        inq[v] = false;
        forn(I, e[v].size()) {
            int i = e[v][I];
            int to = ::to[i];
//             cout << ::to[i] << " " << c[i] << " " << w[i] << endl;
            if (c[i] > 0 && d[to] > d[v] + w[i]) {
                d[to] = d[v] + w[i];
                anc[to] = i;
                if (!inq[to]) {
                    inq[to] = true;
                    q[rq++] = to;
                    if (rq == maxn) rq = 0;
                }
            }
        }
    }

//     forn(i, n) cout << d[i] << " "; cout << endl;

    if (d[t] == inf) {
        return mp(-1, -1);
    } else {
        int p = t;
        int minc = inf;
        while (p != s) {
            minc = min(minc, c[anc[p]]);
            p = to[anc[p]^1];
        }

//         cerr << "pushing " << minc << " flow" << endl;

        p = t;
        while (p != s) {
//             cout << p << " ";
            c[anc[p]] -= minc;
            c[anc[p]^1] += minc;
            p = to[anc[p]^1];
        }
//         cout << endl;

        return mp(d[t], minc);
    }
}

int mx(const vector<pii>& f, int d) {
    i64 res = 0;
    forn(i, f.size()) {
        if (f[i].fi <= d) {
            res += (i64)f[i].se * (d - f[i].fi + 1);
        }
    }
    return min(res, 2000000000ll);
}

void solve() {
    s = 0;
    t = n-1;
    vector<pii> f;
    while (1) {
        pii t = fb();
        if (t.fi != -1) {
            f.pb(t);
        } else {
            break;
        }
    }

    if (K == 0) {
        cout << 0 << endl;
        return;
    } else if (f.empty()) {
        cout << "No solution\n";
        return;
    }

    int l = 0, r = 1111111111, m;
    while (l + 1 < r) {
        m = (l+r)/2;
        if (mx(f, m) >= K) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << r << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    while (scan()) {
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
