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
const int maxn = 1050;

enum { NONE, NEVER, ALWAYS, EXISTS };

int n, m;
vi e[maxn], re[maxn];
int b[maxn], mt[maxn], mr[maxn];
int u[maxn];

int resa[maxn], resb[maxn];

void seta(int i, int val) {
    assert(resa[i] == val || resa[i] == NONE);
    resa[i] = val;
}
void setb(int i, int val) {
    assert(resb[i] == val || resb[i] == NONE);
    resb[i] = val;
}

bool kuhn(int v) {
    if (b[v]) return false;
    b[v] = true;
    forn(i, e[v].size()) {
        int to = e[v][i];
        u[to] = 1;
        if (mt[to] == -1 || kuhn(mt[to])) {
            mt[to] = v;
            mr[v] = to;
            return true;
        }
    }
    return false;
}

void greedy() {
    forn(i, n) {
        forn(j, e[i].size()) {
            int to = e[i][j];
            if (mt[to] == -1) {
                mt[to] = i;
                mr[i] = to;
                break;
            }
        }
    }
}

int matching() {
    forn(i, n) mr[i] = -1;
    forn(j, m) mt[j] = -1;
    greedy();
    int res = 0;
    forn(i, n) if (mr[i] == -1) {
        forn(j, n) b[j] = 0;
        forn(j, m) u[j] = 0;
        if (kuhn(i)) {
            ++res;
        } else {
            forn(j, n) if (b[j]) seta(j, NEVER);
            forn(j, m) if (u[j]) setb(j, ALWAYS);
        }
    }
//     forn(i, n) cout << mr[i] << " "; cout << endl;
    forn(i, n) if (mr[i] != -1) assert(mt[mr[i]] == i);
    return res;
}

bool dfs(int v) {
    if (b[v]) return false;
    b[v] = true;
    forn(i, re[v].size()) {
        int to = re[v][i];
        u[to] = 1;
        assert(mr[to] != -1);
        if (dfs(mr[to])) return true;
    }
    return false;
}

void run_dfs() {
    forn(i, m) if (mt[i] == -1) {
//         cout << "dfs from " << i << endl;
        forn(j, m) b[j] = 0;
        forn(j, n) u[j] = 0;
        if (!dfs(i)) {
            forn(j, m) if (b[j]) {
//                 cout << "set never on " << j << endl;
                setb(j, NEVER);
            }
            forn(j, n) if (u[j]) seta(j, ALWAYS);
        }
    }
}

void scan() {
    int k;
    scanf("%d%d%d", &n, &m, &k);
    forn(i, k) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        re[v].pb(u);
    }
}

void solve() {
    matching();
    run_dfs();

    char t[] = "ENAE";
    forn(i, n) {
        printf("%c", t[resa[i]]);
    }
    printf("\n");
    forn(j, m) {
        printf("%c", t[resb[j]]);
    }
    printf("\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
