#include <iostream>
#include <cmath>
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

struct TEvent {
    double x;
    int p, t;
    
    TEvent(double x = 0, int p = 0, int t = 0)
        : x(x)
        , p(p)
        , t(t)
    {
    }
    
    bool operator<(const TEvent &ev) const {
        if (fabs(x - ev.x) > 1e-7) return x < ev.x;
        if (p != ev.p) return p < ev.p;
        return t > ev.t;
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("orcs.in", "r", stdin);
    freopen("orcs.out", "w", stdout);

    double va = 360.0 / 12 / 60 / 60;
    double vb = 360.0 / 60 / 60;
    double vc = 360.0 / 60;
    double vab = fabs(va - vb);
    double vac = fabs(va - vc);
    double vbc = fabs(vb - vc);
    
    int minab, maxab, minac, maxac, minbc, maxbc;
    cin >> minab >> maxab >> minac >> maxac >> minbc >> maxbc;
    vector<TEvent> evs;
    double T = 12 * 60 * 60;
    for (int k = 0; (360 + 360 * k) / vab < T + 1e-7; ++k) {
        if (minab)
            evs.pb(TEvent((minab + 360 * k) / vab, 0, 1));
        if (maxab != 180) {
            evs.pb(TEvent((maxab + 360 * k) / vab, 0, 0));
            evs.pb(TEvent((360 - maxab + 360 * k) / vab, 0, 1));
        }
        if (minab)
            evs.pb(TEvent((360 - minab + 360 * k) / vab, 0, 0));
    }
    for (int k = 0; (360 + 360 * k) / vac < T + 1e-7; ++k) {
        if (minac)
            evs.pb(TEvent((minac + 360 * k) / vac, 1, 1));
        if (maxac != 180) {
            evs.pb(TEvent((maxac + 360 * k) / vac, 1, 0));
            evs.pb(TEvent((360 - maxac + 360 * k) / vac, 1, 1));
        }
        if (minac)
            evs.pb(TEvent((360 - minac + 360 * k) / vac, 1, 0));
    }
    for (int k = 0; (360 + 360 * k) / vbc < T + 1e-7; ++k) {
        if (minbc)
            evs.pb(TEvent((minbc + 360 * k) / vbc, 2, 1));
        if (maxbc != 180) {
            evs.pb(TEvent((maxbc + 360 * k) / vbc, 2, 0));
            evs.pb(TEvent((360 - maxbc + 360 * k) / vbc, 2, 1));
        }
        if (minbc)
            evs.pb(TEvent((360 - minbc + 360 * k) / vbc, 2, 0));
    }
    evs.pb(TEvent(T, 0, 0));
    if (!minab) evs.pb(TEvent(0, 0, 1));
    if (!minac) evs.pb(TEvent(0, 1, 1));
    if (!minbc) evs.pb(TEvent(0, 2, 1));
    
    int open[3];
    forn(i, 3) open[i] = 0;
    sort(all(evs));
    double res = 0;
    forn(i, evs.size()) {
        if (open[0] && open[1] && open[2]) res += evs[i].x - evs[i - 1].x;
        open[evs[i].p] = evs[i].t;
    }
    printf("%.10lf\n", res * 2);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
