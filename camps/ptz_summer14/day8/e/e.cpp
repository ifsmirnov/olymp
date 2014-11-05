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
const i64 inf = 1e18+100500;
const int maxn = 3030;

int n;
i64 c[maxn];
i64 s[maxn];

i64 add[maxn][maxn];
i64 d[maxn];

i64 gets(int i, int j) {
    if (i > j) return 0;
    return s[j] - (i ? s[i-1] : 0);
}

bool scan() {
    cin >> n;
    if (n == 0) return false;
    forn(i, n) cin >> c[i];
    return true;
}

void relax(i64& x, i64 y) {
    if (x > y) x = y;
}

void solve() {
    forn(i, n+2) {
        s[i] = c[i];
        if (i) s[i] += s[i-1];
    }

    forn(k, n) {
        i64 ts = 0;
        for (int i = k; i >= 0; --i) {
            ts += min(gets(i+1, k) + c[i] * i, c[i] * (3*k - 2*i));
            add[i][k] = ts;
        }
    }

//     forn(i, n) {
//         cout << add[0][i] << " ";
//     }
//     cout << endl;
//     cout << endl;

    forn(i, n+1) d[i] = inf;
    d[0] = 0;
    forn(b, n) {
//         cout << "b = " << b << endl;
//         forn(i, n+1) cout << d[i] << " "; cout << endl;
        i64 ds = 0;
        fore(e, b, n-1) {
            ds -= c[e] * b;
            relax(d[e+1], d[b] + add[b][e] + ds + gets(e+1, n-1) * (4 * (e-b+1) - 2));
        }
    }

    cout << d[n] << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("ebola.in", "r", stdin);
    freopen("ebola.out", "w", stdout);

    while (scan()) {
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
