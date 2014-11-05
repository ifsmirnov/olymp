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

typedef long double lf;

const int maxn = 3000;
const lf eps = 1e-15;

struct intpt
{
    i64 x, y;

    intpt(i64 nx = 0, i64 ny = 0): x(nx), y(ny) {}

    inline bool operator < (const intpt &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};

struct pt
{
    lf x, y;

    pt(lf nx = 0, lf ny = 0): x(nx), y(ny) {}

    void norm(lf len)
    {
        lf k = sqrtl(x * x + y * y);
        x *= len / k, y *= len / k;
    }
};

int n, m;
intpt data[maxn];

u64 sqr(i64 x)
{
    return x * x;
}

pt rotate(pt a, lf cosa, lf sina)
{
    return pt(a.x * cosa - a.y * sina, a.x * sina + a.y * cosa);
}

int find(pt a, int i, u64 b, u64 c)
{
    if (fabsl(a.x) > 1.5e9 || fabsl(a.y) > 1.5e9) return 0;
    for (int dx = -0; dx <= 0; ++dx)
        for (int dy = -0; dy <= 0; ++dy)
        {
            intpt p((i64) roundl(a.x) + dx, (i64) roundl(a.y) + dy);
//             cout << "Search " <<  p.x << " " << p.y << endl;
            if (sqr(p.x) + sqr(p.y) != b) continue;
            if (sqr(p.x - data[i].x) + sqr(p.y - data[i].y) != c) continue;
            int idx = lower_bound(data, data + n, p) - data;
//             if (idx >= 0 && idx < n) cout << "Found " << idx << " " << data[idx].x << " " << data[idx].y << endl;
            if (data[idx].x == p.x && data[idx].y == p.y) return 1;
        }
    return 0;
}

// bool check(u64 a, u64 b, u64 c)
// {
//     return a + b >= c && b + c >= a && a + c >= b;
// }

bool solve()
{
    cin >> n;
    if (n == 0) return false;
    for (int i = 0; i < n; ++i)
        cin >> data[i].x >> data[i].y;
    sort(data, data + n);

    cin >> m;
    for (int it = 0; it < m; ++it)
    {
        int ans = 0;
        u64 A, B, C;
        lf a, b, c;
        cin >> A >> B >> C;
        a = A, b = B, c = C;
//         if (!check(A, B, C))
//         {
//             cout << "ASDOJDSAF" << endl;
//             cout << 0 << '\n';
//             continue;
//         }
        lf cosa = (a + b - c) / (2 * sqrtl(a * b));
//         cout << "cos = " << cosa << endl;
        cosa = max(-1.0L, cosa);
        cosa = min( 1.0L, cosa);
        lf sina = sqrtl(1 - cosa * cosa);
        for (int j = 0; j < n; ++j)
        {
            if (sqr(data[j].x) + sqr(data[j].y) != A) continue;
//             cout << "OK: " << data[j].x << " " << data[j].y << endl;
            pt v(data[j].x, data[j].y);
            v.norm(sqrtl(b));

            v = rotate(v, cosa, sina);
            ans += find(v, j, B, C);
//             cout << v.x << " " << v.y << " " << ans << endl;

            if (A != B)
            {
                v = pt(data[j].x, data[j].y);
                v.norm(sqrtl(b));
                v = rotate(v, cosa, -sina);
                ans += find(v, j, B, C);
//                 cout << v.x << " " << v.y << " " << ans << endl;
            }
        }
        if (fabsl(cosa) > 1 - eps) ans /= 2;
        cout << ans << '\n';
    }
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("astronomy.in", "r", stdin);
    freopen("astronomy.out", "w", stdout);
#endif
    while (solve());

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
