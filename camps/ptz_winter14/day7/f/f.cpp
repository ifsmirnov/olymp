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
const int maxn = 3010;
const int dx[] = {-1, 0, 1, 0 };
const int dy[] = {0, 1, 0, -1 };

#define ok(x,y) ((x)>=0&&(y)>=0&&(x)<N&&(y)<M)

int N, M;
int na, nb, id[44][44], e1[44][44];

void scan() {
    scanf("%d%d", &N, &M);
    na = nb = 0;
    forn(i, N) {
        forn(j, M) {
            scanf("%d", &e1[i][j]);
            if ((i+j)%2 == 0) {
                id[i][j] = na++;
            } else {
                id[i][j] = nb++;
            }
        }
    }
}

int n;
int ne;
int s, t;
int w[maxn], c[maxn], to[maxn];
vi e[maxn];

void addEdge(int u, int v, int w0, int c0) {
    to[ne] = v; c[ne] = c0; w[ne] = w0; e[u].pb(ne++);
    to[ne] = u; c[ne] = 0; w[ne] = -w0; e[v].pb(ne++);
}

bool buildGraph() {
    n = na+nb;
    s = n++;
    t = n++;
    forn(i, n) e[i].clear();
    ne = 0;
    int cnte = 0;
    forn(i, N) forn(j, M) if ((i+j)%2 == 0) forn(k, 4) {
        int tx = i+dx[k];
        int ty = j+dy[k];
        cnte += e1[i][j] % 2;
        if (ok(tx, ty)) {
            addEdge(id[i][j], id[tx][ty] + na, 1 - e1[i][j] % 2, 1);
        }
        e1[i][j] /= 2;
    }
    if (cnte < (N * M + 1) / 2) {
        return false;
    }

    forn(i, na) {
        addEdge(s, i, 0, 1000);
    }
    forn(i, nb) {
        addEdge(i+na, t, 0, 1000);
    }
    return true;
}

int d[maxn], q[maxn], anc[maxn], b[maxn];
int fb() {
    forn(i, n) d[i] = inf, b[i] = 0;
    d[s] = 0;
    q[0] = s;
    int lq = 0, rq = 1;
    while (lq != rq) {
        int v = q[lq++];
        if (lq == maxn) lq = 0;
        b[v] = false;
        forn(I, e[v].size()) {
            int i = e[v][I];
            int to = ::to[i];
            if (c[i] > 0 && d[to] > d[v] + w[i]) {
                anc[to] = i;
                d[to] = d[v] + w[i];
                if (!b[to]) {
                    b[to] = 1;
                    q[rq++] = to;
                    if (rq == maxn) rq = 0;
                }
            }
        }
    }
    if (d[t] == inf) {
        return d[t];
    }
    int w = d[t];
    int mn = 1000000;
    for (int p = t; p != s; ) {
        int r = to[anc[p] ^ 1];
        mn = min(mn, c[anc[p]]);
        c[anc[p]]--;
        c[anc[p] ^ 1]++;
        p = r;
    }
    assert(mn == 1);
    return w;
}

int flow() {
    int w = 0;
    forn(i, (N*M)/2) {
        w += fb();
    }
    assert(w < inf);
    return w;
}


void solve() {
    if (!buildGraph()) {
        printf("-1\n");
        return;
    } else {
        printf("%d\n", flow());
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t;
    scanf("%d", &t);
    forn(i, t) {
        scan();
        solve();
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
