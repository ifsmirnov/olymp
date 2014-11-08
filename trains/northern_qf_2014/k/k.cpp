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
const int mod = 1000000007;
int add(int x, int y) { return (x+y)%mod; }
int mul(int x, int y) { return (i64)x*y%mod; }
const int maxn = 1010;

int cnk[maxn][maxn];
int nw[maxn][maxn];
int nws[maxn][maxn];

int n, t, tot;
int z[maxn];
int d[maxn*maxn];
int lp[maxn], rp[maxn];
int par[maxn*maxn];

void precalc() {
    cnk[0][0] = 1;
    fore(n, 1, maxn-1) {
        cnk[n][0] = cnk[n][n] = 1;
        fore(k, 1, n-1) {
            cnk[n][k] = add(cnk[n-1][k], cnk[n-1][k-1]);
        }
    }

    for (int n = 0; n < maxn; ++n) {
        for (int k = 0; k*t <= n && k < maxn; ++k) {
            nws[n][k] = nw[n][k] = cnk[n-k*t][k];
        }
        for (int k = 0; k < maxn; ++k) {
            nws[n][k] = add(nw[n][k], k ? nws[n][k-1] : 0);
        }
    }
}

void scan() {
    scanf("%d%d", &n, &t);
    int s = 0;
    forn(i, n) {
        int len;
        scanf("%d%d", &len, &z[i]);
        z[i] = len - z[i];
        lp[i] = s;
        rp[i] = s + len - 1;
        fore(j, lp[i], rp[i]) {
            par[j] = i;
        }
        s += len;
    }
    tot = s;
}

void solve() {
    precalc();

    d[0] = 1;

    forn(i, tot) {
        int bl = par[i];
        int k = i - lp[bl];
        int n = rp[bl] - lp[bl] + 1 - k;

        d[i+1] = add(d[i+1], d[i]);

        if (z[bl] >= 2) {
            for (int kp = 1; kp <= t; ++kp) {
                 int r = n - (t+1) - (t+1 - kp);
                 if (r >= 0) {
                     d[rp[bl] + kp + 1] = add(
                            d[rp[bl] + kp + 1],
                            mul(d[i], nws[r][z[bl] - 2])
                    );
                 }
            }
        }

        if (z[bl] >= 1) {
            if (i + (t+1) > rp[bl]) {
                d[i + t+1] = add(d[i + t+1], d[i]);
            } else {
                int r = n - (t+1);
                assert(r >= 0);
                d[rp[bl] + 1] = add(
                        d[rp[bl] + 1],
                        mul(d[i], nws[r][z[bl] - 1])
                );
            }
        }
    }
// 
//     forn(i, tot+5) {
//         cout << d[i] << " ";
//     }
//     cout << endl;

    i64 res = 0;
    forn(i, t+5) {
        res += d[tot+i];
    }

    cout << res % mod << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
