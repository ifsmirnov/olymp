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
const int maxn = 1010;
const int mod = 1000003;
int madd(int x, int y) { return (x+y)%mod; }
int mmul(int x, int y) { return (i64)x*y%mod; }

int n;
int a[maxn];

int c[maxn][maxn];
void compc() {
    c[0][0] = 1;
    fore(n, 1, 1001) {
        c[n][0] = c[n][n] = 1;
        fore(k, 1, n-1) {
            c[n][k] = madd(c[n-1][k], c[n-1][k-1]);
        }
    }
}

bool solve() {
    if (scanf("%d", &n) != 1) {
        return false;
    }
    forn(i, n) scanf("%d", &a[i]);
    for (int K = 1; K <= n; ++K) {
        int res = 0;
        for (int bb = 1; bb <= 1000000000; bb <<= 1) {
            int a = 0;
            int b = 0;
            forn(i, n) {
                if (::a[i] & bb) ++a;
                else ++b;
            }
            int tres = 0;
            for (int r = 1; r <= min(a, K); r += 2) {
                if (K-r <= b) {
                    tres = madd(tres, mmul(c[a][r], c[b][K-r]));
                }
            }
            res = madd(res, mmul(tres, bb));
        }
        printf("%d ", res);
    }
    printf("\n");
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    compc();
    while (solve());

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
