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
const int maxn = 501;

vi e[maxn];
int c[maxn];
int pn[maxn];
int m[maxn][maxn];
int used[maxn];
int vis[maxn];

int left(int a, int b) {
    return 3 - a - b;
}

vi q;

bool dfs(int v, int s, int cc) {
    //cerr << v << ' ' << s << ' ' << cc << '\n';
    if (!m[v][s]) return true;
    if (c[v] != -1 && c[v] != cc) return false;
    if (vis[v]) return true;
    vis[v] = true;
    if (c[v] == -1) {
        c[v] = cc;
        pn[v] = s;
        q.pb(v);
    }
    forn(i, e[v].size()) {
        int u = e[v][i];
        if (!dfs(u, s, left(cc, c[s]))) return false;
    }
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("mayors.in", "r", stdin);
    freopen("mayors.out", "w", stdout);
#endif

    int N, M;
    cin >> N >> M;
    forn(i, M) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        e[x].pb(y);
        e[y].pb(x);
        m[x][y] = m[y][x] = 1;
    }
    forn(i, N) {
        c[i] = -1;
        pn[i] = -1;
    }
    if (N == 1) {
        cout << "Plan OK\nR\n";
        return 0;
    }
    c[0] = 0;
    c[e[0][0]] = 1;
    pn[0] = e[0][0];
    int cur = 0;
    q.pb(0);
    bool ok = true;
    while (cur < q.size()) {
        int v = q[cur++];
        forn(i, N) vis[i] = false;
        if (!dfs(pn[v], v, c[pn[v]])) {
            ok = false;
            break;
        }
    }
    if (!ok) cout << "Plan failed\n";
    else {
        cout << "Plan OK\n";
        forn(i, N) {
            cout << "RGB"[c[i]];
        }
        cout << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
