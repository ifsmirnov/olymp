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
typedef vector<pii> vp;
const int mod = 175781251;
const int maxn = 105;
int add(int x, int y) { return (x+y)%mod; }
int mul(int x, int y) { return (i64)x*y%mod; }
int sub(int x, int y) { return (x-y+mod)%mod; }

int mpow(int x, int k) {
    int a = 1;
    while (k) {
        if (k&1) a = mul(a, x);
        x = mul(x, x);
        k >>= 1;
    }
    return a;
}

int f[maxn][maxn]; // all
int g[maxn][maxn]; // connected;
int d[maxn];
int s[maxn];

int c[maxn][maxn];

void prepare() {
    forn(i, maxn) {
        d[i] = s[i] = -1;
        forn(j, maxn) f[i][j] = g[i][j] = -1;
    }

//     fact[0] = rfact[0] = 1;
//     fore(i, maxn-1) {
//         fact[i] = mul(fact[i-1], i);
//         rfact[i] = mul(rfact[i-1], mpow(i, mod-2));
//     }
    c[0][0] = 1;
    fore(n, 1, maxn-1) {
        c[n][0] = c[n][n] = 1;
        fore(k, 1, n-1) c[n][k] = add(c[n-1][k], c[n-1][k-1]);
    }
}

int F(int l, int r) {
    if (l == 0 || r == 0) return 1;
    if (l > r) return F(r, l);
    int &ret = f[l][r];
    if (ret == -1) {
        ret = mpow(3, l*r);

//         cout << "f " << l << " " << r << " = " << ret << endl;
    }
    return ret;
}

int G(int l, int r) {
    if (l == 0 || r == 0) return r+l == 1;
    if (l > r) return G(r, l);
    int &ret = g[l][r];
    if (ret == -1) {
        ret = F(l, r);
        fore(l1, 1, l) fore(r1, 0, r) if (l1 < l || r1 < r) {
            int subv = mul(
                    mul(c[l-1][l1-1], c[r][r1]),
                    mul(G(l1, r1), F(l-l1, r-r1)));
//             if (l == 2 && r == 2) {
//                 cout << "sub " << l1 << " " << r1 << ", v = " << subv << endl;
//             }
            ret = sub(ret, subv);
        }

//         cout << "g " << l << " " << r << " = " << ret << endl;
    }
    return ret;
}

int S(int n) {
    if (n == 1) return 1;
    if (n == 0) return 1;
    int &ret = s[n];
    if (ret == -1) {
        ret = 0;
        fore(i, 1, n-1) ret = add(ret, mul(c[n][i], G(i, n-i)));
        ret = mul(ret, mpow(2, mod - 2));
//         cout << "s " << n << " = " << ret << endl;
    }
    return ret;
}

int D(int n) {
    if (n == 0) return 1;
    int &ret = d[n];
    if (ret == -1) {
        ret = 0;
        fore(i, 1, n) {
            ret = add(ret, mul(mul(c[n-1][i-1], S(i)), D(n-i)));
        }
//         cout << "d " << n << " = " << ret << endl;
    }
    return ret;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);

    prepare();

    int n;
    while (1) {
        cin >> n;
        if (n == 0) break;
        cout << D(n) << endl;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

// 3
// d 1 = 1
// f 1 1 = 3
// g 1 1 = 2
// s 2 = 2
// d 2 = 4
// f 1 2 = 9
// g 1 2 = 4
// s 3 = 8
// d 3 = 26
// 26
// 
