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
const int maxn = 105;

int n;
int a[maxn][maxn];

void floyd() {
    forn(k, n) forn(i, n) forn(j, n)
        a[i][j] = min(a[i][j], a[i][k]+a[k][j]);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("average.in", "r", stdin);
    freopen("average.out", "w", stdout);

    int m;
    cin >> n >> m;
    forn(i, m) {
        int u, v, l;
        cin >> u >> v >> l;
        a[u-1][v-1] = l;
    }
    forn(i, n) forn(j, n) if (a[i][j] == 0) a[i][j] = inf;
    floyd();
    i64 res = 0;
    int cnt = 0;
    forn(i, n) forn(j, n) if (i != j && a[i][j] != inf) res += a[i][j], ++cnt;
    printf("%.6lf\n", (double)res/cnt);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
