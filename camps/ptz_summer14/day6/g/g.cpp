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

int dp[100][100];

int bin[100][100];

int solve(int n, int m) {
    if (n == 0) {
        return 0;
    }
    return m > (1 << __builtin_ctz(n)) - 1;
}



int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    if (solve(n, m)) {
        puts("WIN");
        for (int i = 1; i <= min(n, m); ++i) {
            if (!solve(n - i, i)) {
                printf("%d\n", i);
                break;
            }
        }
    } else {
        puts("FAIL");
    }
    
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
