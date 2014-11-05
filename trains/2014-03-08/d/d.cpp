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
const int maxn = 100500;

bool cmp(pair<i64, i64> a, pair<i64, i64> b) {
    i64 delta = a.fi * b.se - a.se * b.fi;
    if (delta == 0) return a.fi < b.fi;
    return delta < 0;
}

void solve(int b, int n) {
    vector<pair<i64, i64> > res;
    for (int m = 1; m <= 2*n; ++m) if (m != n) {
        i64 num = (i64)b * m * (2*n - m);
        i64 den = (i64)n * n;
        if (num % den == 0 && num / den >= 0) {
            res.pb(mp(num/den, m));
        }
    }
    sort(all(res), cmp);
    forn(i, res.size()) {
        cout << res[i].fi << "/" << res[i].se << " \n"[i == (int)res.size() - 1];
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    int a, b;
    while (1) {
        cin >> a >> b;
        if (b == 0) break;
        solve(a, b);
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
