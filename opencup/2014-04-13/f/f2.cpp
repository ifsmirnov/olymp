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
const int maxn = 6666;
typedef long double ld;
#define rank sdfdsfsdfsdsfdsf

int n;
bitset<maxn> a[maxn];

int rank() {
    int ans = 0;
    int lp = 0;
    for (int i = 0; i < n; ++i)
    {
        int pos = -1;
lp = i;
        for (int j = lp; j < n; ++j)
            if (a[j][i]) pos = j;
        if (pos == -1) continue;
        if (++ans == 100) return ans;
        swap(a[pos], a[lp]);
        for (int j = 0; j < n; ++j)
            if (j != lp && a[j][i])
                a[j] ^= a[lp];
        ++lp;
    }
    return ans;
}

ld f(int n) {
    ld x = 1;
    for (int i = 0; i < n + 1; ++i) x /= 2.0;
    return 0.5l - x;
}

void readline(bitset<maxn> &a) {
    int np = (n+5)/6*6;
//     for (int i = 0; i < np; ++i)
//         a.set(i, 0);
    string s;
    cin >> s;
    forn(i, np) {
        int x = s[i/6] - 48;
        a[i] = (bool)(x&(1<<(i%6)));
    }
}

bool scan() {
    if (scanf("%d", &n) != 1) {
        return false;
    }
    int np = (n+5)/6*6;
    forn(i, np) {
        a[i].reset();
    }
    forn(i, n) readline(a[i]);
    n = np;
    forn(i, n) {
        forn(j, n) cout << a[i][j];
        cout << endl;
    }
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("prob.in", "r", stdin);
    freopen("prob.out", "w", stdout);
#endif

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
