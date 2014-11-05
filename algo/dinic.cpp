#include <iostream>
#include <algorithm>
using namespace std;
#define forn(i, n) for (int i = 0; i < n; ++i)
const int maxn = 310;

int c[maxn][maxn];
int d[maxn], q[maxn], pos[maxn];
int n;
int s, t;

bool bfs() {
    int lq = 0, rq = 1;
    forn(i, n) d[i] = maxn;
    d[s] = 0;
    q[0] = s;
    while (lq != rq) {
        int v = q[lq++];
        forn(i, n) if (c[v][i] > 0 && d[i] > d[v] + 1) {
            d[i] = d[v] + 1;
            q[rq++] = i;
        }
    }
    return d[t] != maxn;
}
int dfs(int v, int curf) {
    if (v == t || !curf) return curf;
    for (int &i = pos[v]; i < n; ++i) {
        if (d[i] == d[v] + 1 && c[v][i] > 0) {
            if (int ret = dfs(i, min(curf, c[v][i]))) {
                c[v][i] -= ret;
                c[i][v] += ret;
                return ret;
            }
        }
    }
    return 0;
}
int dinic() {
    int f = 0;
    while (bfs()) {
        forn(i, n) pos[i] = 0;
        while (int ff = dfs(s, 100000)) {
            f += ff;
        }
    }
    return f;
}
int main() {
    int m;
    cin >> n >> m;
    forn(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        c[u-1][v-1] += w;
    }
    s = 0;
    t = n-1;
    cout << dinic() << endl;
    return 0;
}
