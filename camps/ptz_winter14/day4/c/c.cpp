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
const int maxn = 2050;

int n;
vi e[maxn];
vi re[maxn];
int b[maxn], c[maxn];
vi ans;

void dfs(const vi* e, int* b, int v) {
    b[v] = 1;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (!b[to]) {
            dfs(e, b, to);
        }
    }
}

void solve(int v) {
    forn(i, n) b[i] = 0, c[i] = 0;
    dfs(e, b, v);
    dfs(re, c, v);

    int cnt = 0;
    forn(i, n) cnt += b[i] && c[i];
    if (cnt == 1) return;

    vi res;
    res.pb(v);
    int p = v;
    do {
        forn(i, e[p].size() if (b[e[p][i]] && c[e[p][i]])) {
            p = c;
            res.pb(p);
        }
    } while (p != v);
    p.pop_back();
    ans = min(ans, res);
}

void solve() {
    ans.pb(n+1);
    forn(i, n) solve(i);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
