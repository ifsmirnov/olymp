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

int n,m;
int g[10000][8];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &g[i][j]);
    for (int i = 1; i < m; ++i)
    {
        bool fail = true;
        for (int j = 0; j < n; ++j)
            fail &= g[i][j] == g[0][j];
        if (fail) printf("-1\n"), exit(0);
    }
    vector< vector<int> > ans;
    for (int i = 0; i < (1 << n); ++i)
    {
        int bits = __builtin_popcount(i) & 1;
        vector<int> cur;
        cur.pb(bits ? -10 : 10);
        bool fail = false;
        for (int j = 0; j < n; ++j)
        {
            int c = (i >> j) & 1;
            if (g[0][j] - c == 0) fail = true;
            else cur.pb(g[0][j] - c);
        }
        if (!fail) ans.pb(cur);
    }
    printf("%d\n", (int) ans.size());
    for (size_t i = 0; i < ans.size(); ++i)
    {
        for (size_t j = 0; j < ans[i].size(); ++j)
            printf("%d ", ans[i][j]);
        printf("\n");
    }
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
