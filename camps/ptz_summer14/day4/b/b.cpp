#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
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
const int inf = 1e9+2000500;
const int maxn = 2000500;

int n;
vi g[maxn];
vi e[maxn], re[maxn];
set<int> f;

void scan() {
    int m;
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u-1].pb(v-1);
        g[v-1].pb(u-1);
    }
}

void build_graph(int xx) {
    assert(f.empty());
    if (xx) {
        forn(i, n*2) e[i].clear();
    }
    forn(v, n) forn(i, g[v].size()) {
        int to = g[v][i];
        e[v*2+xx].pb(to*2+!xx);
        e[v*2+!xx].pb(to*2+xx);
    }
    forn(i, n*2) sort(all(e[i]));
    forn(i, n) {
        f.insert(i*2+!xx);
        e[i*2+xx].pb(10000000);
    }
}

int b[maxn];
int ts[maxn], tspos;
int c[maxn];

void dfs(int v, int xx, int cc) {
    b[v] = 1;
    c[v] = cc;
    if (v%2 == xx) { // a
        cout << "entered upper " << v << ", edges: ";
        forn(i, e[v].size()) cout << e[v][i] << " "; cout << endl;
        set<int>::iterator it = f.begin();
        int pos = 0;
        while (it != f.end()) {
            if (*it == e[v][pos]) {
                ++pos;
                ++it;
                continue;
            } else if (*it > e[v][pos]) {
                ++pos;
            } else {
                int to = *it;
                ++it;
                if (to == (v^1)) continue;
                re[to].pb(v);
                if (b[to]) continue;
                f.erase(to);
                cout << "go -edge " << v << " " << to << endl;
                if (!b[to]) dfs(to, xx, cc);
            }
        }
    } else {
        f.erase(v);
        forn(i, e[v].size()) {
            int to = e[v][i];
            re[to].pb(v);
            cout << "go edge " << v << " " << to << endl;
            if (!b[to]) dfs(to, xx, cc);
        }
    }
    if (xx == 0) ts[tspos++] = v;
}

void dfs1(int v, int cc) {
    b[v] = 1;
    c[v] = cc;
    forn(i, re[v].size()) {
        int to = re[v][i];
        if (!b[to]) {
            dfs1(to, cc);
        }
    }
}

void solve() {
    build_graph(0);
    forn(i, n*2) b[i] = 0;
    forn(i, n*2) if (!b[i]) {
        dfs(i, 0, 0);
    }
    cout << "-------------\n";

//     build_graph(1);
    forn(i, n*2) b[i] = 0;
    int cc = 0;
    forn(i, n*2) cout << ts[i] << " "; cout << endl;
    ford(I, n*2) {
        int i = ts[I];
        if (!b[i]) {
            ++cc;
            dfs1(i, cc);
            cout << endl;
        }
    }
    cout << "cc = " << cc << endl;
    forn(i, n) if (c[i*2] == c[i*2+1]) { cout << "no" << endl; return; }
    vi res;
    forn(i, n) if (c[i*2] > c[i*2+1]) {
        res.pb(i);
//         cout << i+1 << endl;
//         return;
    }
    for (auto i: res) {
        cout << res[i] << " ";
    }
    cout << endl;
    forn(i, res.size()) {
        if (g[res[i]].size() + 1 == res.size()) {
            cout << res[i]+1 << endl;
            return;
        }
    }
    assert(false);
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
