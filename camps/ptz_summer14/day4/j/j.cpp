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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    
    double pr = p / 100.0;
    
    double dp[n + 1][m + 1];
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i <= m; ++i) {
        dp[n][i] = 0;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = 1e20;
        }
    }
    
    double l = 0, r = 1e9;
    int it = 100;
    while (it--) {
        double mid = (l + r) / 2;
        dp[0][0] = mid;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                if (!i && !j) continue;
                double a1 = dp[i + 1][j];
                double a2 = (j == m - 1) ? dp[0][0] : dp[i][j + 1]; 
                dp[i][j] = min(dp[0][0], pr * (1 + a1) + (1 - pr) * (1 + a2));
            }
        }
        double a1 = dp[1][0];
        double a2 = (0 == m - 1) ? dp[0][0] : dp[0][1];
        double res = pr * (1 + a1) + (1 - pr) * (1 + a2);
        if (res > mid) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << setprecision(10) << fixed;
    cout << l << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
