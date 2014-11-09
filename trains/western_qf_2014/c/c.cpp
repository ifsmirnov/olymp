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

int n;
int d[maxn], d1[maxn];
vi e[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
}

void dfs(int v, int anc, int dd) {
    d[v] = dd;
    for (auto to : e[v]) if (to != anc) dfs(to, v, dd+1);
}

void solve() {
    dfs(0, -1, 0);
    int p = max_element(d, d+n) - d;
    dfs(p, -1, 0);
    int q = max_element(d, d+n) - d;
    forn(i, n) d1[i] = d[i];
    dfs(q, -1, 0);
    forn(i, n) printf("%d ", max(d1[i], d[i]));
    printf("\n");
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
