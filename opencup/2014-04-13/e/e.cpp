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
const int inf = 1e9+100500;
const int maxn = 100500;

struct pt
{
    i64 x, y;

    pt(i64 nx = 0, i64 ny = 0): x(nx), y(ny) {}
};

pt pts[maxn];
i64 value[maxn];
int n;

typedef float lf;

lf dist(const pt &p, const pt &dir, i64 c)
{
    return fabsf(p.x * dir.x + p.y * dir.y + c) / sqrtf(dir.x * dir.x + dir.y * dir.y);
}

int main() {
    srand(8475);
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
#endif
    cin >> n;
    int bound = sqrtl(n + .0) * 1.5 + 0.5;
    for (int i = 0; i < n; ++i)
        cin >> pts[i].x >> pts[i].y;
    for (;;)
    {
        pt dir = pt(rand() % 200000001 - 100000000, rand() % 200000001 - 100000000);
        for (int i = 0; i < n; ++i) value[i] = pts[i].x * dir.x + pts[i].y * dir.y;
        nth_element(value, value + n / 2, value + n);
        i64 left = -value[n / 2];
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            if (dist(pts[i], dir, left) < 0.72)
                ++cnt;
        if (cnt < bound)
        {
            printf("%d\n", cnt);
            for (int i = 0; i < n; ++i)
                if (dist(pts[i], dir, left) < 0.72)
                    printf("%d %d\n", (int) pts[i].x, (int) pts[i].y);
            return 0;
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
