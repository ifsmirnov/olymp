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
#include <cmath>
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

const double PI = atan2(0, -1);

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    
    ios::sync_with_stdio(false);
    cout.precision(1);
    cout << fixed;
    int N;
    cin >> N;
    //while (N-->0) {
    forn(i, N) {
        double W, H, xp, yp, x0, y0, alpha, s;
        cin >> W >> H >> xp >> yp >> x0 >> y0 >> alpha >> s;
        //alpha /= PI;
        W *= s;
        H *= s;
        xp *= s;
        yp *= s;
        double cosa = cos(alpha / 180.0 * PI), sina = sin(alpha / 180.0 * PI);
        //cerr << cosa << ' ' << sina << '\n';
        double xr = W / 2 - xp, yr = H / 2 - yp;
        double xrr = xr * cosa - yr * sina, yrr = xr * sina + yr * cosa;
        //cerr << xr << ' ' << yr << ' ' << xrr << ' ' << yrr << '\n';
        /*double xpp = xp * cosa - yp * sina, ypp = xp * sina + yp * cosa;
        x0 -= xpp, y0 -= ypp;
        double x00 = x0 + W / 2 * cosa - H / 2 * sina - W / 2, y00 = y0 + W / 2 * sina + H / 2 * cosa - H / 2;*/
        double xc = x0 + xrr, yc = y0 + yrr;
        double x00 = xc - W / 2, y00 = yc - H / 2;
        cout << ".item" << i + 1 << " { width: " << W << "px; height: " << H << "px; left: " << x00 << "px; top: " << y00 << "px; transform: rotate(" << alpha << "deg); }\n";
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
