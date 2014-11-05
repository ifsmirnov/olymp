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
const int maxn = 100;
const int mod = 998244353;
int add(int x, int y) { return (x+y)%mod; }
int mul(int x, int y) { return (i64)x*y%mod; }

int rev(int x) {
    int k = mod - 2;
    int a = 1;
    while (k) {
        if (k&1) a = mul(a, x);
        x = mul(x,x);
        k >>= 1;
    }
    return a;
}

int d[maxn][maxn][maxn][2];
int s[maxn][maxn];
int sp[maxn];

int get(int n, int p) {
    int b = 95 - p;
    int e = 95;

    int res = 0;
    fore(x, b, e) {
        int num = sp[x], den = 1;
        fore(x1, b, e) if (x1 != x) {
            num = mul(num, add(n, mod - x1));
            den = mul(den, add(x, mod - x1));
        }
        res = add(res, mul(num, rev(den)));
    }
    return res;
}

void relax(int &x, int y) { x = add(x, y); }

void compd() {
    d[2][0][0][1] = 1;
    d[2][1][0][0] = 1;
    fore(i, 2, 95) forn(j, i) forn(k, i-1) forn(t, 2) {
        int val = d[i][j][k][t];
        if (val == 0) continue;
        forn(x, i+1) {
            if ((x > j) == t)
                relax(d[i+1][x][k+1][!t], val);
            else
                relax(d[i+1][x][k][t], val);
        }
    }

    fore(n, 3, 95) fore(k, 0, n) forn(j, n) forn(t, 2)
        relax(s[n][k], d[n][j][k][t]);
}

void compsp(int p) {
    fore(k, 1, 95) {
        int mv = 1;
        forn(i, p) mv = mul(mv, k);
        fore(n, 3, 95) {
            relax(sp[n], mul(mv, s[n][k]));
        }
    }
    int f = rev(2);
    fore(n, 3, 95) {
        f = mul(f, rev(n));
        sp[n] = mul(sp[n], f);
    }
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    compd();

//     int y;
//     cin >> y;
//     fore(k, 0, y-2) cout << s[y][k] << " ";
//     cout << endl;
//     return 0;

    int k;
    i64 n;
    cin >> k >> n;
    compsp(k);
    if (n < 70) cout << sp[n] << endl;
    else cout << get(n % mod, k) << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
