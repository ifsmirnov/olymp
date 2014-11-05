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
const int maxn = 111;

int n, l;
int c[maxn][maxn];
int d[maxn], pos[maxn], q[maxn];
int s, t;

bool bfs() {
    forn(i, n) d[i] = maxn;
    int lq = 0, rq = 1;
    q[0] = s;
    d[s] = 0;
    while (lq != rq) {
        int v = q[lq++];
        forn(to, n) if (d[to] == maxn && c[v][to] > 0) {
            d[to] = d[v] + 1;
            q[rq++] = to;
        }
    }
    return d[t] <= l;
}

int dfs(int v, int curf) {
    if (v == t || !curf) {
        return curf;
    }
    for (int &to = pos[v]; to != n; ++to) {
        if (d[to] <= l && d[to] == d[v] + 1 && c[v][to] > 0) {
//             cout << v << " " << to  << endl;
            if (int ret = dfs(to, min(curf, c[v][to]))) {
                c[v][to] -= ret;
                c[to][v] += ret;
                return ret;
            }
        }
    }
    return 0;
}

int flow() {
    int ff = 0;
    while (bfs()) {
        forn(i, n) pos[i] = 0;
        while (int f = dfs(s, 1000000000)) {
            ff += f;
        }
//         cout << endl;
    }
    return ff;
}

void scan() {
    scanf("%d%d%d%d", &n, &s, &t, &l);
    forn(i, n) forn(j, n) scanf("%d", &c[i][j]);
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
    freopen("m2.in", "r", stdin);
    freopen("large.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);
    forn(i, t) {
        scan();
        printf("%lf\n", flow() / 8.0);
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
