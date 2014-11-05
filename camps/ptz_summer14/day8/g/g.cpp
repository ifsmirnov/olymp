#include <bits/stdc++.h>

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

const int k = 4;

vector <vector <int> > a;

map <vector <vector <int> >, bool> ok[3];

int d;

bool solve(int step) {
    if (ok[step].count(a)) {
        return ok[step][a];
    }
    for (int j = 0; j < k; ++j) {
    for (int i = 0; i < (int)a[j].size(); ++i) {
        if (!a[j][i] && (!i || a[j][i - 1] != step) && (i == (int)a[j].size() || a[j][i + 1] != step)) {
            a[j][i] = step;
            bool res = solve((step & 1) + 1);
            a[j][i] = 0;
            if (!res) {
                d = i + 1;
                return ok[step][a] = true;
            }
        }
    }
}
    return ok[step][a] = false;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    /*int n = 4;
    a.resize(k);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            for (int d = j; d <= n; ++d) {
                for (int q = d; q <= n; ++q) {
            a[0].resize(i);
            a[1].resize(j);
            a[2].resize(d);
            a[3].resize(q);
            if (solve(1)) {
                cout << i << " " << j << " " << d << " " << q << endl;
            }
        }
        }
    }
    }*/
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    
    long long mod = 242121643;
    
    while (1) {
        int n, k;
        cin >> n >> k;
        
        if (!n) return 0;
        
        int a[n];
        
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        long long dp[n + 1][k + 1][2];
        
        memset(dp, 0, sizeof(dp));
        
        dp[0][0][0] = 1;
        
        for (int i = 0; i < n; ++i) {
            int p = a[i] == 1;
            if (p) {
                for (int j = 0; j <= k; ++j) {
                    if (j) {
                        dp[i + 1][j][0] += dp[i][j - 1][1];
                        dp[i + 1][j][1] += dp[i][j - 1][0];
                    }
                    dp[i + 1][j][0] += dp[i][j][0];
                    dp[i + 1][j][1] += dp[i][j][1];
                    while (dp[i + 1][j][0] >= mod) {
                        dp[i + 1][j][0] -= mod;
                    }
                    while (dp[i + 1][j][1] >= mod) {
                        dp[i + 1][j][1] -= mod;
                    }
                }
            } else {
                for (int j = 0; j <= k; ++j) {
                    if (j) {
                        dp[i + 1][j][0] += dp[i][j - 1][0];
                        dp[i + 1][j][1] += dp[i][j - 1][1];
                    }
                    dp[i + 1][j][0] += dp[i][j][0];
                    dp[i + 1][j][1] += dp[i][j][1];
                    while (dp[i + 1][j][0] >= mod) {
                        dp[i + 1][j][0] -= mod;
                    }
                    while (dp[i + 1][j][1] >= mod) {
                        dp[i + 1][j][1] -= mod;
                    }
                }
            }
        }
        
        cout << dp[n][k][1] << endl;
    }
    
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
