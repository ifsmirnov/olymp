#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
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
const double eps = 1e-9;

struct pt {
    int x, y;
    pt(){}
    pt(int x, int y) : x(x), y(y) {}
    pt operator+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt operator-(const pt& p) const { return pt(x-p.x, y-p.y); }
    int operator*(const pt& p) const { return x*p.y - y*p.x; }
    int operator%(const pt& p) const { return x*p.x + y*p.y; }
    pt mid() const { return pt(x/2, y/2); }
    bool operator==(const pt& p) const { return x == p.x && y == p.y; }
};

pt p[10];

double ang(const pt& a, const pt& b) {
    return atan2(a*b, a%b);
}

bool inside(const pt& q) {
    double s = 0;
    forn(i, 5) {
        s += ang(p[i] - q, p[i+1] - q);
    }
    return abs(s) > 1.0;
}

bool onseg(const pt& a, const pt& b, const pt& p) { // strict
    if (a == p || b == p) return false;
    return (b-a) * (p-a) == 0 && (b-a) % (p-a) > 0 && (a-b) % (p-b) > 0;
}

int sgn(int x) {
    return (x>0) - (x<0);
}

bool both_sides(const pt& a, const pt& b, const pt& c, const pt& d) {
    int s1 = sgn((b-a) * (c-a));
    int s2 = sgn((b-a) * (d-a));
    return min(s1, s2) == -1 && max(s1, s2) == 1;
}

bool intersect(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (onseg(a, b, c) || onseg(a, b, d) || onseg(c, d, a) || onseg(c, d, b)) return true;
    return both_sides(a, b, c, d) && both_sides(c, d, a, b);
}

void solve() {
    forn(i, 5) {
        scanf("%d%d", &p[i].x, &p[i].y);
        p[i].x *= 2;
        p[i].y *= 2;
        p[i+5] = p[i];
    }

//     cout << onseg(p[1], p[3], p[4]) << endl;
//     cout << intersect(p[1], p[3], p[3], p[4]) << endl;

    int res = 0;
    forn(st, 5) {
        bool ok = true;
        for (int pd = st+2; pd <= st+3; ++pd) {
            if (!inside((p[st] + p[pd]).mid())) {
                ok = false;
                break;
            }
            forn(i, 5) {
                if (intersect(p[st], p[pd], p[i], p[i+1])) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
//         if (ok) {
//             cout << "st = " << st << endl;
//         }
        res += ok;
    }
    printf("%d\n", res);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("pentagon.in", "r", stdin);
    freopen("pentagon.out", "w", stdout);

    int t;
    scanf("%d", &t);
    forn(i, t) {
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
