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

int n;
pii a[5050];

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("segnemts.in", "r", stdin);
    freopen("segments.out", "w", stdout);

    cin >> n;
    forn(i, n) {
        cin >> a[i].fi >> a[i].se;
        if (a[i].fi > a[i].se) swap(a[i].fi, a[i].se);
    }
    sort(a, a+n);
    int res = 0;
    int cl = -inf, cr = -inf;
    forn(i, n) {
        if (a[i].fi > cr) {
            res += cr - cl;
            cl = a[i].fi;
            cr = a[i].se;
        } else {
            cr = max(cr, a[i].se);
        }
    }
    cout << res + (cr - cl) << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}