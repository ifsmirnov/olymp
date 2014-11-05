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
typedef double lf;

const int inf = 1e9+100500;
const lf eps = 1e-9;
const int maxn = 100500;


struct pt
{
    lf x, y, z;
    pt(): x(0), y(0), z(0) {}

    pt(lf nx, lf ny, lf nz): x(nx), y(ny), z(nz) {}

    pt operator - (const pt &p) const
    {
        return pt(x - p.x, y - p.y, z - p.z);
    }

    lf operator * (const pt &p) const
    {
        return x * p.x + y * p.y + z * p.z;
    }

    pt operator % (const pt &p) const
    {
        return pt(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }

    pt operator * (const lf &k) const
    {
        return pt(x * k, y * k, z * k);
    }
};

ostream& operator<<(ostream& out, const pt& p) {
    out << p.x << " " << p.y << " " << p.z;
    return out;
}

inline lf sqlen(const pt &p)
{
    return p * p;
}

struct triangle
{
    pt a[3];
};

// void cross(const pt &s, const pt &d, const pt &a, const pt &b, vector<lf> &v)
// {
//     pt v1 = (a - s) % d, v2 = (b - s) % d;
//     assert(sqlen(v1 % v2) < eps);
//     if (v1 * v2 > eps) return;
//     if (sqlen(v1) < eps && sqlen(v2) < eps)
//     {
//         v.pb((a - s) * d / sqlen(d));
//         v.pb((b - s) * d / sqlen(d));
//     }
//     pt u1 = d % (b - a), u2 = (a - s) % (b - a);
//     lf alpha = u1 * u2 / sqlen(u1);
//     v.pb(alpha);
// }
void cross(const pt &s, const pt &d, const pt &a, const pt &b, vector<lf> &v)
{
    pt v1 = (a - s) % d, v2 = (b - s) % d;
    if (v1 * v2 > eps) return;
    if (sqlen(v1) < eps && sqlen(v2) < eps)
    {
        v.pb((a - s) * d / sqlen(d));
        v.pb((b - s) * d / sqlen(d));
    }
    pt u1 = d % (b - a), u2 = (a - s) % (b - a);
    lf alpha = u1 * u2 / sqlen(u1);
    v.pb(alpha);
}

void proj(const pt& a, const pt& d, pt& p) {
    p = p - d * (((p - a) * d) / sqlen(d));
}
inline void proj(const pt &a, const pt &d, triangle &t)
{
    for (int i = 0; i < 3; ++i)
        t.a[i] = t.a[i] - d * (((t.a[i] - a) * d) / sqlen(d));
//     for (int i = 0; i < 3; ++i) {
//         assert(abs((t.a[i] - a) * d) < eps);
//     }
}

inline void read(pt &a)
{
    scanf("%lf%lf%lf", &a.x, &a.y, &a.z);
}

triangle data[maxn];
pt s, t, d;
int n;

bool solve()
{
    if (scanf("%d", &n) != 1) return false;
    read(s);
    read(t);
    read(d);
    lf ans = 0;
    proj(s, d, t);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 3; ++j)
            read(data[i].a[j]);
        proj(s, d, data[i]);
        vector<lf> v;
        for (int j = 0; j < 3; ++j)
            if (sqlen(s - t) < eps)
                cross(s, pt(28, 91, -5) % d, data[i].a[j], data[i].a[(j + 1) % 3], v);
            else
                cross(s, t - s, data[i].a[j], data[i].a[(j + 1) % 3], v);
        if (v.size() > 0)
        {
            lf r = min(1.0, *max_element(v.begin(), v.end()));
            lf l = max(0.0, *min_element(v.begin(), v.end()));
            if (sqlen(s - t) < eps) ans += (l <= eps && r >= -eps) ? 1 : 0;
            else ans += max(0.0, r - l);
        }
    }
    printf("%.10lf\n", ans);
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    while (solve());

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
