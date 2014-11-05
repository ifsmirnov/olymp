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

int ans[151] = {0, 0, 1,
12,
53,
120,
293,
412,
653,
1384,
1329,
1780,
2961,
2984,
3753,
7508,
5629,
6752,
9373,
9444,
11029,
16224,
14681,
16764,
21401,
21520,
24209,
30124,
30213,
33544,
44949,
40940,
45021,
53672,
53953,
58820,
67633,
69432,
75193,
86436,
87629,
94320,
108605,
108724,
116453,
131872,
132969,
141772,
156777,
160544,
170529,
187820,
191701,
202904,
221077,
226620,
239149,
259896,
265553,
279444,
306833,
308680,
324041,
348964,
356253,
373120,
399213,
408452,
426933,
455456,
465529,
485660,
515209,
527664,
549553,
583548,
595109,
618792,
653525,
668044,
693629,
730648,
746721,
774244,
815457,
831320,
860889,
903236,
922093,
953792,
1002733,
1019220,
1053061,
1100592,
1122953,
1159020,
1208585,
1233472,
1271873,
1324444,
1351029,
1391800,
1447269,
1475804,
1519145,
1580408,
1608049,
1653812,
1714465,
1747944,
1796329,
1861140,
1895741,
1946784,
2014349,
2051620,
2105429,
2176144,
2215833,
2272444,
2351673,
2388560,
2448081,
2525852,
2570053,
2632520,
2714917,
2760492,
2826013,
2910696,
2960129,
3028740,
3116321,
3169144,
3241081,
3334132,
3387789,
3462832,
3558045,
3616244,
3694629,
3794000,
3854761,
3936524,
4038649,
4103520,
4188769,
4296828,
4362773,
4451544,
4566629};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int K;
    cin >> K;
    cout << ans[K] << '\n';
    return 0;

    //for (int K = 2; K <= 150; ++K) {
    //int K;
    //cin >> K;
    /*cerr << K << '\n';
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
    cout << ans << '\n';*/


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
