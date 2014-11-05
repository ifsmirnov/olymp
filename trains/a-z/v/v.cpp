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
typedef long double ld;
const ld eps = 1e-9;
#define lt(x, y) ((x)<(y)-eps)
#define eq(x, y) (fabsl((x)-(y))<eps)

struct pt {
    ld x, y;
    pt(){}
    pt(ld x, ld y): x(x), y(y) {}
    pt operator+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt operator-(const pt& p) const { return pt(x-p.x, y-p.y); }
    pt operator*(ld k) const { return pt(x*k, y*k); }
    ld d2() const { return x*x+y*y; }
    pt turn(ld sina, ld cosa) {
        return pt(x*cosa-y*sina, x*sina+y*cosa);
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("circles.in", "r", stdin);
    freopen("circles.out", "w", stdout);

    int t;
    cin >> t;
    forn(i, t) {
        pt a, b;
        ld r1, r2;
        cin >> a.x >> a.y >> r1;
        cin >> b.x >> b.y >> r2;
        if (r1 < r2) swap(r1, r2), swap(a, b);
        if (eq(r1, r2) && eq(a.x, b.x) && eq(a.y, b.y)) {
            printf("I can't count them - too many points :(\n\n");
            continue;
        }
        ld d2 = (a-b).d2();
        ld d = sqrtl(d2);
        if (eq(d, r1+r2)) {
            printf("There are only 1 of them....\n");
            pt p = a + (b-a) * (r1 / d);
            printf("%.6lf %.6lf\n", (double)p.x, (double)p.y);
        } else if (eq(r1, r2 + d)) {
            printf("There are only 1 of them....\n");
            pt p = a + (b-a) * (r1 / d);
            printf("%.6lf %.6lf\n", (double)p.x, (double)p.y);
        } else if (lt(r1+r2, d) || lt(r2+d, r1)) {
            printf("There are no points!!!\n");
        } else {
            ld cosa = (r1*r1 + d2 - r2*r2) / (2.0 * r1 * d);
            ld sina = sqrtl(1.0 - cosa * cosa);
            pt dir = (b-a) * (r1 / d);
            pt p1 = a + ((b-a) * (r1 / d)).turn(sina, cosa);
            pt p2 = a + ((b-a) * (r1 / d)).turn(-sina, cosa);
            if (lt(p1.x, p2.x) || (eq(p1.x, p2.x) && lt(p1.y, p2.y))) {
                swap(p1, p2);
            }
            printf("There are only 2 of them....\n");
            printf("%.6lf %.6lf\n", (double)p2.x, (double)p2.y);
            printf("%.6lf %.6lf\n", (double)p1.x, (double)p1.y);

        }
        printf("\n");
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
