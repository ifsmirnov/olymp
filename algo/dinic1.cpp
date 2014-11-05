#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define forn(i, n) for(int i = 0; i < n; ++i)
const int maxn = 300;

int c[maxn][maxn];
int q[maxn], pos[maxn], d[maxn];
int n, s, t;

void scan() {
    int m;
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        c[u-1][v-1] += w;
    }
}

bool bfs() {
    int lq = 0, rq = 1;
    q[0] = s;
    forn(i, n) d[i] = maxn;
    d[s] = 0;
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
    if (v == t || curf == 0) return curf;
    for (int &i = pos[v]; i < n; ++i) {
        if (c[v][i] > 0 && d[i] == d[v]+1) {
            if (int ret = dfs(t, min(curf, c[v][i]))) {
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
        while (int ff = dfs(s, 1000000)) f += ff;
    }
    return f;
}

int main() {
    scan();
    s = 0; t = n-1;
    cout << dinic() << endl;
}
