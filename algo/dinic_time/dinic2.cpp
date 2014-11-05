// real    2m46.967s
// 2014/11/04
#include <iostream>
#include <algorithm>
using namespace std;
#define forn(i, n) for (int i = 0; i < n; ++i)

const int maxn = 500;

int c[maxn][maxn], q[maxn], d[maxn], pos[maxn];
int n, m;

void scan() {
    cin >> n >> m;
    forn(i, m) {
        int u, v, f;
        cin >> u >> v >> f;
        c[--u][--v] = f;
        c[v][u] = f;
    }
}

bool bfs() {
    int lq = 0, rq = 1;
    q[0] = 0;
    forn(i, n) d[i] = maxn;
    d[0] = 0;
    while (lq != rq) {
        int v = q[lq++];
        forn(i, n) if (d[i] == maxn && c[v][i]) {
            d[i] = d[v]+1, q[rq++] = i;
        }
    }
    return d[n-1] != maxn;
}

int dfs(int v, int curf) {
    if (v == n-1 || curf == 0) return curf;
    for (int &i = pos[v]; i < n; ++i) {
        if (c[v][i] && d[v] + 1 == d[i]) {
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
        while (int ff = dfs(0, 1000000000)) {
            f += ff;
        }
    }
    return f;
}

int main() {
    scan();
    cout << dinic() << endl;
}
