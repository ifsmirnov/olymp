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
const int maxn = 55;

char data[maxn][maxn + 1];
char need[maxn][maxn + 1];
int g[maxn][maxn], connect[maxn], used[maxn];
int n, m;

bool kuhn(int v)
{
    if (used[v]) return false;
    used[v] = 1;
    for (int to = 0; to < n; ++to)
        if (g[v][to] && (connect[to] == -1 || kuhn(connect[to])))
        {
            connect[to] = v;
            return true;
        }
    return false;
}

bool check()
{
    int prevcnt = m;
    for (int i = 0; i < n; ++i)
    {
        int cnt = 0;
        for (int j = 0; j < m; ++j)
            if (need[i][j] == 'x') cnt++;
        if (cnt > prevcnt) return false;
        prevcnt = cnt;
    }
    return true;
}

int canmake(char *a, char *b)
{
    for (int i = 0; i < m; ++i)
        if (a[i] != '?' && a[i] != b[i])
            return 0;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("lots.in", "r", stdin);
    freopen("lots.out", "w", stdout);
#endif
    while (scanf("%d%d\n", &n, &m) == 2)
    {
        if (n == 0 && m == 0) break;
        for (int i = 0; i < n; ++i)
            scanf("%s\n", data[i]);
        scanf("\n");
        for (int i = 0; i < n; ++i)
            scanf("%s\n", need[i]);
        if (!check()) cout << "NO\n";
        else
        {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                {
                    g[j][i] = canmake(data[i], need[j]);
//                     cout << g[i][j] << " ";
                }
            fill(connect, connect + n, -1);
            int ans = 0;
            for (int i = 0; i < n; ++i)
            {
                fill(used, used + n, 0);
                if (kuhn(i)) ans++;
            }
            if (ans != n) cout << "NO\n";
            else
            {
                cout << "YES\n";
                for (int i = 0; i < n; ++i)
                    cout << need[connect[i]] << '\n';
            }
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
