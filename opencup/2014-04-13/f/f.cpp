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
#include <cmath>
#include <bitset>
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
const int maxn = 6050;
typedef long double ld;
#define rank sdfdsfsdfsdsfdsf

int n;
bitset<maxn> a[maxn];

int rank() {
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int pos = -1;
        for (int j = i; j < n; ++j)
            if (a[j][i]) pos = j;
        if (pos == -1) continue;
        if (++ans == 100) return ans;
        swap(a[pos], a[i]);
        for (int j = 0; j < n; ++j)
            if (j != i && a[j][i])
                a[j] ^= a[i];
    }
    return ans;
}

ld ff[maxn];
ld lf[maxn];

void compf() {
    ff[0] = 1;
    ff[1] = 1;
    lf[1] = 0;
    fore(i, 2, 6000) {
        lf[i] = lf[i-1] + logl((ld)i);
        ff[i] = ff[i-1] * i;
    }
}

// ld f(int n) {
//     if (n == 0) {
//         return 0;
//     }
//     ld res = 0;
//     ld log3 = logl(3.0);
//     ld log4 = logl(4.0);
//     for (int k = 1; k <= n; k += 2) {
//         res += expl( log3 * (n-k) - log4 * n + lf[n] - lf[k] - lf[n-k] );
//     }
//     return res;
// }
ld f(int n) {
//     cout << "r = " << n << endl;
    return 0.5l - powl(2, -n-1);
}
// ld f(int n) {
//     if (n == 0) {
//         return 0;
//     }
//     ld res = 0;
//     for (int k = 1; k <= n; k += 2) {
//         res += powl(3, n-k) / ff[k] / ff[n-k] * ff[n];
//     }
//     return res / powl(4, n);
// }

void readline(bitset<maxn> &a) {
    a.reset();
    string s;
    cin >> s;
    forn(i, n) {
        int x = s[i/6] - 48;
        a[i] = (bool)(x&(1<<(i%6)));
    }
}

bool scan() {
    if (scanf("%d", &n) != 1) {
        return false;
    }
    forn(i, n) readline(a[i]);
//     forn(i, n) {
//         forn(j, n) cout << a[i][j];
//         cout << endl;
//     }
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("prob.in", "r", stdin);
    freopen("prob.out", "w", stdout);
#endif

    compf();
    cout.precision(20);
    cout << fixed;
//     cout << f(100) << endl;
//     forn(i, 30) {
//         cout << f(i) << endl;
//     }

    while (scan()) {
        cout << f(rank()) << endl;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
