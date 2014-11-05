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

int x[10], y[10];

void get2nd(int i, int j, int k) {
    x[k] = x[i]-y[j]+y[i]+x[j];
    y[k] = y[i]+x[j]-x[i]+y[j];
    x[k] /= 2;
    y[k] /= 2;
}



int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    freopen("equal-squares.in", "r", stdin);
    freopen("equal-squares.out", "w", stdout);

    set<pair<pii, int> > res;
    cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[4] >> y[4] >> x[5] >> y[5];
    forn(i, 8) x[i] *= 2, y[i] *= 2;
    get2nd(0, 1, 2);
    get2nd(1, 0, 3);
    get2nd(4, 5, 6);
    get2nd(5, 4, 7);

    int cntg = 0;
    forn(i, 4) fore(j, 4, 7) {
        if (x[i] == x[j] && y[i] == y[j]) {
            ++cntg;
            continue;
        }
        int a = y[i] - y[j];
        int b = x[j] - x[i];
        int g = __gcd(a, b);
        a /= g;
        b /= g;
        if (mp(-a, -b) < mp(a, b)) {
            a *= -1;
            b *= -1;
        }
        int c = -(x[i]*a + y[i]*b);

        int sp = 0, sm = 0;
        forn(k, 4) {
            int t = a*x[k] + b*y[k] + c;
            if (t > 0) sp = 1;
            if (t < 0) sm = 1;
        }
        if (sp&&sm) continue;
        sp = 0, sm = 0;
        fore(k, 4, 7) {
            int t = a*x[k] + b*y[k] + c;
            if (t > 0) sp = 1;
            if (t < 0) sm = 1;
        }
        if (sp&&sm) continue;
        res.insert(mp(mp(a, b), c));
    }
    if (cntg == 1) {
        cout << "Infinity" << endl;
    } else {
        cout << res.size() << endl;
//         for (auto x: res) {
//             cout << x.fi.fi << " " << x.fi.se << " " << x.se << endl;
//         }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
