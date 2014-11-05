#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 500;
#define forn(i, n) for (int i = 0; i < n; ++i)

int n;
int c[maxn][maxn];
int q[maxn], pos[maxn], d[maxn];

void scan() {
    cin >> n;
    int m;
    cin >> m;
    forn(i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        ::c[u-1][v-1] += c;
    }
}

bool bfs() {
    forn(i, n) d[i] = maxn;
    d[0] = 0;
    int lq = 0, rq = 1;
    q[0] = 0;
    while (lq != rq) {
        int v = q[lq++];
        forn(i, n) if (d[i] == maxn && c[v][i] > 0) {
            d[i] = d[v] + 1;
            q[rq++] = i;
        }
    }
    return d[n-1] != maxn;
}

int dfs(int v, int curf) {
    if (v == n-1 || !curf) return curf;
    for (int &i = pos[v]; i < n; ++i) {
        if (c[v][i] > 0 && d[i] == d[v] + 1) {
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
        while (int ff = dfs(0, 10000)) f += ff;
    }
    return f;
}

int main() {
    scan();
    cout << dinic() << endl;
}
