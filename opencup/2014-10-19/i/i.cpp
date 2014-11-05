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
const int inf = 1e9+100500;
const int maxn = 5050;

int n, m;
vi e[maxn];
int d[maxn];
int fb[maxn][maxn];
int cc;
int s1, t1, s2, t2;
int q[maxn];
int anc[maxn];

vi p1, p2, p3, p4;

int bfs(int s, int t, vi& path) {
//     cout << "bfs " << s << " " << t << endl;
    path.clear();
    forn(i, n) d[i] = inf;
    d[s] = 0;
    int lq = 0, rq = 1;
    q[0] = s;
    while (lq != rq) {
        int v = q[lq++];
        for (auto to : e[v]) if (fb[v][to] != cc) {
//             cout << "go " << v << " " << to << endl;
//             cout << fb[v][to] << "!= " << cc << endl;
            if (d[to] == inf) {
                d[to] = d[v] + 1, q[rq++] = to, anc[to] = v;
            }
        }
    }
    if (d[t] == inf) return inf;
    path.pb(t);
    for (int p = t; p != s; p = anc[p]) {
        path.pb(anc[p]);
        fb[anc[p]][p] = cc;
//         cout << "fb " << anc[p] << " " << p << endl;
    }
    reverse(all(path));
    return d[t];
}

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u-1].pb(v-1);
    }
    scanf("%d%d%d%d", &s1, &t1, &s2, &t2);
    --s1;--t1;--s2;--t2;
}

void solve() {
    ++cc;
    int r1 = bfs(s1, t1, p1);
    r1 += bfs(s2, t2, p2);

    ++cc;
    int r2 = bfs(s2, t2, p3);
    r2 += bfs(s1, t1, p4);

//     cout << r1 << " " << r2 << endl;

    if (r1 > r2) {
        swap(r1, r2);
        swap(p1, p4);
        swap(p2, p3);
    }

    if (r1 >= inf) {
        printf("NO\n");
        return;
    }
    printf("YES\n");
    printf("%d\n", (int)p1.size());
    for (auto v : p1) {
        printf("%d ", v+1);
    }
    printf("\n");
    printf("%d\n", (int)p2.size());
    for (auto v : p2) {
        printf("%d ", v+1);
    }
    printf("\n");
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("two-paths.in", "r", stdin);
    freopen("two-paths.out", "w", stdout);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
