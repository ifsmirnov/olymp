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
const int mod = 1000000007;
const int maxn = 55;
int add(int x, int y) { return (x+y)%mod; }
int sub(int x, int y) { return (x-y+mod)%mod; }
int mul(int x, int y) { return (i64)x*y%mod; }
void madd(int &x, int y) { x = (x+y) % mod; }

int mpow(int x, int k) {
    if (k == 0) return 1;
    return mul(x, mpow(x, k-1));
}

int N, B;

int C[maxn][maxn], F[maxn], G[maxn], H[maxn], I[maxn][maxn], J[maxn][maxn], d[maxn][maxn];
int res[maxn][maxn];

void compC() {
    C[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k <= n-1; ++k) {
            C[n][k] = add(C[n-1][k-1], C[n-1][k]);
        }
    }
}

void compF() {
    for (int i = 0; i <= N; ++i) {
        F[i] = mpow(2, i * (i-1) / 2);
    }
}

void compG() {
     G[0] = 1;
     for (int n = 1; n <= N; ++n) {
         for (int k = 1; k <= n-1; ++k) {
            madd(G[n], mul(G[k], mul(F[n-k], C[n-1][k-1])));
         }
         G[n] = sub(F[n], G[n]);
     }
}

void compI() {
    I[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
        for (int k = 1; k <= n; ++k) {
            for (int s = 1; s <= n-k+1; ++s) {
                madd(I[n][k], mul(mul(I[n-s][k-1], G[s]), mul(s, C[n-1][s-1])));
            }
        }
    }
}

void compH() {
    H[0] = 1;
    for (int n = 1; n <= N; ++n) {
        for (int k = 1; k <= n-1; ++k) {
            int t = mul(H[k], C[n-1][k-1]);
            int p = 0;
            for (int r = 1; r <= n-k; ++r) {
                madd(p, mul(I[n-k][r], mpow(k, r)));
            }
            madd(H[n], mul(t, p));
        }
        H[n] = sub(G[n], H[n]);
    }
}

void compJ() {
    J[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
        for (int s = 1; s <= n; ++s) {
            memset(d, 0, sizeof d);
            d[0][0] = 1;
            for (int k = 0; k < n-s; ++k) {
                for (int r = 0; r <= k; ++r) {
                    if (d[k][r] == 0) {
                        continue;
                    }
                    for (int nk = 1; k + nk <= n-s; ++nk) {
                        for (int nr = 0; nr <= nk-1; ++nr) {
                            madd(d[k+nk][r+1+nr],
                                mul(d[k][r],
                                    mul( mul(J[nk][nr], s),
                                         mul(nk, C[n-s-k-1][nk-1])
                                    )));
                        }
                    }
                }
            }

            for (int b = 0; b < n; ++b) {
                madd(J[n][b], mul(mul(C[n-1][s-1], H[s]), d[n-s][b]));
            }
        }
    }


    for (int n = 1; n <= N; ++n) {
        for (int b = 0; b <= n; ++b) {
//             cout << n << " " << b << ": " << J[n][b] << endl;
            for (int t = 0; t <= b; ++t) {
                madd(res[n][b], J[n][t]);
            }
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cin >> N >> B;
    B = min(B, N-1);

    compC();
    compF();
    compG();
    compI();
    compH();
    compJ();

    cout << res[N][B] << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
