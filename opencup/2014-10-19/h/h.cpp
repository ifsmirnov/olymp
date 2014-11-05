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
const int maxn = 100500;

int n, m;
vi e[maxn];
int d[maxn][2];
int rf[maxn];
int mn1[maxn], s1[maxn], s0[maxn];
bool leaf[maxn];
int b[maxn];

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (u == 0 || v == 0) {
            leaf[u+v-1] = 1;
        } else {
            e[--u].pb(--v);
            e[v].pb(u);
        }
    }
}

void dfs(int v, int anc) {
    b[v] = 1;
    forn(i, e[v].size()) {
        if (e[v][i] == anc) {
            swap(e[v][i], e[v].back());
            e[v].pop_back();
            break;
        }
    }
    if (e[v].empty()) {
        d[v][1] = leaf[v];
        d[v][0] = 0;
        rf[v] = d[v][0] - d[v][1];
        return;
    }

    mn1[v] = e[v][0];
    for (auto to : e[v]) {
        assert(!b[to]);
        dfs(to, v);

        if (rf[mn1[v]] > rf[to]) {
            mn1[v] = to;
        }
        s0[v] += d[to][0];
        s1[v] += d[to][1];
    }

    if (leaf[v]) {
        d[v][0] = s1[v];
        d[v][1] = 1 + s0[v];
    } else {
        d[v][0] = s1[v] + rf[mn1[v]];
        d[v][1] = min(s1[v], s0[v] + 1);
    }
    d[v][0] = min(d[v][0], d[v][1]);
    rf[v] = d[v][0] - d[v][1];
}

vi ans;

void recover(int v, int k) {
    if (e[v].empty()) {
        if (leaf[v] && k) {
            ans.pb(v);
        }
        return;
    }

    if (k == 0 && d[v][0] == d[v][1]) {
        k = 1;
    }

    if (leaf[v]) {
        if (k == 0) {
            for (auto to : e[v]) {
                recover(to, 1);
            }
        } else {
            ans.pb(v);
            for (auto to : e[v]) {
                recover(to, 0);
            }
        }
    } else {
        if (k == 1) {
            if (s1[v] < s0[v] + 1) {
                for (auto to : e[v]) {
                    recover(to, 1);
                }
            } else {
                ans.pb(v);
                for (auto to : e[v]) {
                    recover(to, 0);
                }
            }
        } else {
            for (auto to : e[v]) {
                if (to == mn1[v]) {
                    recover(to, 0);
                } else {
                    recover(to, 1);
                }
            }
        }
    }

}

void solve() {
    int res = 0;
    forn(i, n) {
        if (!b[i]) {
            dfs(i, -1);
            res += d[i][0];
            recover(i, 0);
//             if (leaf[i]) {
//                 res += d[i][1];
//                 recover(i, 1);
//             } else {
//                 res += d[i][0];
//                 recover(i, 0);
//             }
        }
    }
//     forn(i, n) {
//         cout << d[i][0] << " " << d[i][1] << endl;
//     }
    assert(res == (int)ans.size());
    printf("%d\n", res);
    forn(i, res) {
        printf("%d%c", ans[i]+1, " \n"[i==res-1]);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("removing.in", "r", stdin);
    freopen("removing.out", "w", stdout);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
