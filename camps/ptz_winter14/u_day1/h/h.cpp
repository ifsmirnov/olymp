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
const int maxn = 301;

vi e[maxn];
i64 dp[maxn][2 * maxn + 1][3];
i64 temp[2 * maxn + 1][3];

const i64 P = 1000000000 + 7;

inline void norm(int i, int j, i64 A) {
    if (i < 0 || i >= 2 * maxn + 1) {
        return;
    }
    temp[i][j] += A;
    temp[i][j] %= P;
}

int cost(int k) {
    if (k == 2) {
        return 0;
    }
    return k == 1 ? 1 : -1;
}

int N;

void dfs(int v, int p) {
    dp[v][maxn][2] = 2;
    dp[v][maxn][1] = 1;
    dp[v][maxn][0] = 0;
    forn(i, e[v].size()) {
        int u = e[v][i];
        if (u == p) {
            continue;
        }
        dfs(u, v);
        //forn(j,  maxn + 1) forn(k, 3) temp[j][k] = 0;
        for (int j = -N; j <= N; ++j) forn(k, 3) temp[maxn + j][k] = 0;
        //forn(my, 2 * maxn + 1) {
            //forn(his, 2 * maxn + 1) {
        for (int my = -N; my <= N; ++my) {
            forn(myk, 3) {
                if (!dp[v][maxn + my][myk]) continue;
                for (int his = -N; his <= N; ++his) {
                    forn(hisk, 3) {
                        if (!dp[u][maxn + his][hisk]) continue;
                        i64 p = dp[v][maxn + my][myk] * dp[u][maxn + his][hisk] % P;
                        if (myk == 2) {
                            //temp[my + his + cost(hisk)][0] += dp[v][my][myk] * dp[u][his][hisk];
                            norm(my + his + maxn + cost(hisk), 2, p);
                            continue;
                        }
                        if (hisk == 2) {
                            //temp[my + his][myk] += dp[v][my][myk] * dp[u][his][hisk];
                            norm(my + his + maxn, myk, p);
                            continue;
                        }
                        //temp[my + his][(myk + hisk) & 1] += dp[v][my][myk] * dp[u][his][hisk];
                        norm(my + his + maxn, (myk + hisk) & 1, p);
                    }
                }
            }
        }
        //forn(j, 2 * maxn + 1) forn(k, 3) dp[v][j][k] = temp[j][k];
        for (int j = -N; j <= N; ++j) forn(k, 3) dp[v][j + maxn][k] = temp[j + maxn][k];
    }
    //forn(j, 2 * maxn + 1) forn(k, 3) if (dp[v][j][k]) cerr << v << ' ' << j - maxn << ' ' << k << ' ' << dp[v][j][k] << '\n';
    //cerr << v << '\n';
    
}

/*int ccnt[3], color[20];

int mdfs(int v, int p)
{
    int cnt = 1;
    for (size_t i = 0; i < e[v].size(); ++i)
    {
        if (e[v][i] == p) continue;
        int to = e[v][i], w = dfs(to, v);
        if (color[to] == color[v]) cnt = (cnt + w) & 1;
        else ccnt[color[to]] += w ? 1 : -1;
    }
    return cnt;
}

int dummy()
{
    int p3 = 1;
    for (int i = 0; i < n; ++i) p3 *= 3;
    for (int msk = 0; msk < p3; ++msk)
    {
        for (int i = 0, cm = msk; i < n; ++i, cm /= 3)
            color[i] = cm % 3;
        mdfs(0, -1, 1);
        
    }
}*/

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    while (cin >> N) {
        forn(i, N) {
            e[i].clear();
            for (int j = -N; j <= N; ++j) {
                forn(k, 3) {
                    dp[i][j + maxn][k] = 0;
                }
            }
        }
        forn(i, N - 1) {
            int x, y;
            cin >> x >> y;
            //cerr << x << ' ' << y << '\n';
            --x; --y;
            e[x].pb(y);
            e[y].pb(x);
        }
        dfs(0, -1);
        i64 ans = 0;
        //forn(j, 2 * maxn + 1) {
        for (int j = -N; j <= N; ++j) {
            forn(k, 3) {
                int c = j + cost(k);
                ans += max(c, 0) * dp[0][j + maxn][k];
                ans %= P;
            }
        }
        cout << (3 * ans) % P << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
