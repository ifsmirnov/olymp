#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <cstring>
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
typedef vector<pii> vp;

const int maxn = 100;

int cnt = 0;

int used[maxn];
vector<int> g[maxn];

bool dfs(int v, int c)
{
    if (used[v] != -1 && used[v] != c) return false;
    if (used[v] != -1) return true;
    used[v] = c;
    for (int to : g[v])
        if (!dfs(to, 1 - c)) return false;
    return true;
}

bool check(int n)
{
    memset(used, -1, sizeof(used));
    for (int i = 0; i < n; ++i)
        if (used[i] == -1 && !dfs(i, 0))
            return false;
    return true;
}

int rec(int cur, int n)
{
    if (!check(cur)) return 0;
    if (cur == n) return 1;
    int ans = 0;
    for (int msk = 0; msk < (1 << cur); ++msk)
    {
        for (int i = 0; i < cur; ++i)
            if ((msk >> i) & 1)
                g[cur].pb(i), g[i].pb(cur);
        ans += (1 << __builtin_popcount(msk)) * rec(cur + 1, n);
        for (int i = 0; i < cur; ++i)
            if ((msk >> i) & 1)
                g[cur].pop_back(), g[i].pop_back();
    }
    return ans;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int n;
    while (cin >> n)
    {
        if (n == 0) break;
        cout << rec(0, n) << endl;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
