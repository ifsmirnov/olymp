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
const int maxn = 100500;

const int maxx = 10;

vector< pair<double, int> > can[maxx + 1];

void precalc(int x, int n, int cnt, double sum)
{
    if (n > x)
    {
        can[x].pb(mp(sum, cnt));
        return;
    }
    for (int k = 0; k < n; ++k)
        precalc(x, n + 1, cnt + k, sum + k * x / n);
}

bool solve()
{
    int x, y;
    if (!(cin >> x >> y)) return false;
    int ans = inf;
    for (auto p : can[x])
    {
        int k = ceil((y - p.first) / x) - 1;
        if (k + 1 < (y + 1 - p.first) / x)
            ans = min(ans, p.second + k + x - 1);
    }
    printf("%d\n", ans);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    for (int i = 1; i <= 10; ++i)
        precalc(i, 2, 0, 0);
    while (solve());
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
