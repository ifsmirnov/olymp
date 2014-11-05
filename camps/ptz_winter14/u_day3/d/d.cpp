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

struct TPoint {
    double x, y;
    
    TPoint(double x = 0, double y = 0)
        : x(x)
        , y(y)
    {
    }
    
    TPoint operator-(const TPoint &p) const {
        return TPoint(x - p.x, y - p.y);
    }
    
    double operator*(const TPoint &p) const {
        return x * p.x + y * p.y;
    }
    
    double operator~() const {
        return *this * *this;
    }
};

double maxdist(const TPoint &p, const vector<pair<TPoint, double> > &c) {
    double res = 0.0;
    forn(i, c.size()) {
        res = max(res, sqrt(~(p - c[i].first)) + c[i].second);
    }
    return res;
}

const int ITC = 40;
const double R = 100;

double search2(const vector<pair<TPoint, double> > &c, double x) {
    double l = -R, r = R;
    forn(I, ITC) {
        double m1 = (l + l + r) / 3, m2 = (l + r + r) / 3;
        double f1 = maxdist(TPoint(x, m1), c), f2 = maxdist(TPoint(x, m2), c);
        if (f1 < f2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return maxdist(TPoint(x, l), c);
}

double search1(const vector<pair<TPoint, double> > &c) {
    double l = -R, r = R;
    forn(I, ITC) {
        double m1 = (l + l + r) / 3, m2 = (l + r + r) / 3;
        double f1 = search2(c, m1), f2 = search2(c, m2);
        if (f1 < f2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return search2(c, l);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int N;
    scanf("%d", &N);
    forn(i, N) {
        double r1, r2, r3;
        scanf("%lf%lf%lf", &r1, &r2, &r3);
        if (r1 < r2) {
            swap(r1, r2);
        }
        if (r2 < r3) {
            swap(r2, r3);
        }
        if (r1 < r2) {
            swap(r1, r2);
        }
        
        TPoint A = TPoint(0, 0);
        TPoint B = TPoint(r1 + r2, 0);
        double d = r1 + r2;
        double cosa = -((r2 + r3) * (r2 + r3) - (r1 + r2) * (r1 + r2) - (r1 + r3) * (r1 + r3)) / (2 * (r1 + r2) * (r1 + r3));
        double sina = sqrt(1 - cosa * cosa);
        TPoint C = TPoint((r1 + r3) * cosa, (r1 + r3) * sina);
        double l = max(max(r1, r2), r3), r = 250;
        forn(it, ITC) {
            double m = 0.5 * (l + r);
            double R1 = m - r1, R2 = m - r2;
            if (R1 + R2 < d) {
                l = m;
                continue;
            }
            double cosb = (R1 * R1 + d * d - R2 * R2) / (2 * R1 * d);
            double sinb = sqrt(1 - cosb * cosb);
            double R3 = m - r3;
            TPoint D = TPoint(R1 * cosb, R1 * sinb);
        //    cerr << C.x << ' ' << C.y << ' ' << D.x << ' ' << D.y << ' ' << R3 << '\n';
            if (sqrt(~(C - D)) < R3) {
                r = m;
            } else {
                l = m;
            }
        }
        printf("%.10lf\n", l);
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
