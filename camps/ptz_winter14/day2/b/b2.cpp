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
typedef double ld;
typedef unsigned long long u64;
const int inf = 1e9+100500;
const int maxn = 100500;

const ld EPS = 1e-10;

struct TPoint {
    ld x, y;
    
    TPoint(ld x = 0.0, ld y = 0.0)
        : x(x)
        , y(y)
    {
    }
    
    TPoint operator+(const TPoint &p) const {
        return TPoint(x + p.x, y + p.y);
    }
    
    TPoint operator-(const TPoint &p) const {
        return TPoint(x - p.x, y - p.y);
    }
    
    ld operator%(const TPoint &p) const {
        return x * p.y - y * p.x;
    }
    
    ld operator*(const TPoint &p) const {
        return x * p.x + y * p.y;
    }
    
    TPoint operator*(ld k) const {
        return TPoint(x * k, y * k);
    }
    
    inline bool operator<(const TPoint &p) const {
        if (fabs(x - p.x) > EPS) {
            return x < p.x;
        }
        if (fabs(y - p.y) > EPS) {
            return y < p.y;
        }
        return false;
    }
};

TPoint cross(TPoint a, TPoint b, TPoint v, TPoint u) {
    ld t1 = ((b - a) % u) / (v % u);
    return a + v * t1;
}

const ld PI = atan2l(0, -1.0);

ld coss[300], sins[300];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    for (int K = 140; K <= 150; ++K) {
    //int K;
    //cin >> K;
    cerr << K << '\n';
    int ans = 0;
    forn(i, 2 * K) {
        coss[i] = cos(0.5 * i * PI / K);
        sins[i] = sin(0.5 * i * PI / K);
    }
    set<TPoint> ps;
    forn(i, 2 * K) {
        ps.insert(TPoint(coss[i], sins[i]));
    }
    
    for (int a = 1; a < 2 * K; ++a) {
        for (int c = 1; a + c < 2 * K; ++c) {
            TPoint P = cross(TPoint(0, 0), TPoint(1, 0), TPoint(coss[a], sins[a]), TPoint(-coss[c], sins[c]));
            for (int b = 1; a + b < 2 * K; ++b) {
                for (int d = 1; c + d < 2 * K && b + d < 2 * K; ++d) {
                    TPoint Q = cross(TPoint(0, 0), TPoint(1, 0), TPoint(coss[b], -sins[b]), TPoint(-coss[d], -sins[d]));
                    //ld ang = atan2((P) % (P - Q), (P) * (P - Q));
                    ld y = P % (P - Q), x = P * (P - Q);
                    ld l = hypot(x, y);
                    x /= l, y /= l;
                    //ld disc = ang / (0.5 * PI) * K;
                    if (ps.count(TPoint(x, y))) {
                        ++ans;
                        //cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
                    }
                }
            }
        }
    }
    cout << ans << '\n';
}

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
