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
const int maxn = 8010;

int n, k;
unsigned a[1010][1100/32];
int r[1010][1010];
int win[maxn];
char buf[10];

void scan() {
    scanf("%d%d", &n, &k);
    forn(i, k) {
        int h;
        scanf("%d", &h);
        forn(j, h) {
            int x;
            scanf("%d", &x);
            --x;
            a[i][x>>5] |= 1u<<(x&31);
        }
        scanf("%s", buf);
        if (buf[2] == 'r') // Girl
            win[i] = 0;
        else
            win[i] = 1;
    }
}

void reduct() {
    forn(i, k) {
        forn(j, i) {
            bool ok1 = true; // 2 is a submask of 1
            bool ok2 = true;
            forn(t, (n+91)/32) {
                ok1 &= ( (a[i][t] & a[j][t]) == a[j][t] );
                ok2 &= ( (a[j][t] & a[i][t]) == a[i][t] );
                if (!ok1 && !ok2) break;
            }
            r[i][j] = ok1;
            r[j][i] = ok2;
        }
    }
}

int p[maxn];
void init(int n) { forn(i, n) p[i] = i; }
int get(int x) { return (x == p[x]) ? (x) : (p[x] = get(p[x])); }
void unite(int x, int y) { p[get(x)] = get(y); }

int gs[maxn], gt[maxn];
int c[maxn], to[maxn], ne;
int used[maxn];
int tag;
vi e[maxn];
int comp[maxn];
int s, t;
void addEdge(int u, int v, int c0) {
    if (c0 == 0) return;
    to[ne] = v; c[ne] = c0; e[u].pb(ne++);
    to[ne] = u; c[ne] =  0; e[v].pb(ne++);
}

int flow(int v, int curf) {
    used[v] = tag;
    if (v == t || curf == 0) return curf;
    forn(I, e[v].size()) {
        int i = e[v][I];
        int to = ::to[i];
        if (used[to] != tag && c[i] > 0) {
            if (int ret = flow(to, min(curf, c[i]))) {
                c[i] -= ret;
                c[i^1] += ret;
                return ret;
            }
        }
    }
    return 0;
}

int fflow() {
    int f = 0;
    ++tag;
    while (int ff = flow(s, 1000000000)) {
        ++tag;
        f += ff;
    }
    return f;
}

void dfs(int v) {
    if (comp[v]) return;
    comp[v] = 1;
    forn(I, e[v].size()) {
        int i = e[v][I];
        int to = ::to[i];
        if (c[i]) dfs(to);
    }
}

void solve() {
    reduct();
    init(k);
    forn(i, k) forn(j, k) if (win[j] && !win[i] && r[i][j]) unite(i, j);
    forn(i, k) {
        if (win[i] == 0) {
            ++gs[get(i)];
        } else {
            ++gt[get(i)];
        }
    }
    s = k;
    t = k+1;
    forn(i, k) if (i == get(i)) {
        addEdge(s, i, gs[i]);
        addEdge(i, t, gt[i]);
    }
    int res = fflow();
    cout << res << "\n";

    dfs(s);

    vi ans;
//     forn(i, k) cout << comp[get(i)]; cout << endl;
    forn(i, k) if (win[i] == comp[get(i)]) {
        ans.pb(i);
    }
//     if (ans.size() != (size_t) res) {
//         cout << "sfsdkljfsdf" << endl;
//         return;
//     }
//     cout << "ans.size = " << ans.size() << endl;
    forn(i, ans.size()) {
        cout << ans[i] + 1 << "\n";
    }
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
