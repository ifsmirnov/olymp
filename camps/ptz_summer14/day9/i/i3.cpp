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

typedef long double ld;
const int inf = 1e9+100500;
const ld eps = 1e-11;

ld res[19];

int n;

ld calcMean() {
    ld v = 0;
    for (int i = 0; i < n; ++i) {
        v += res[i];
    }
    v /= n;
    return v;
}

ld calcDev(ld med) {
    ld v = 0;
    for (int i = 0; i < n; ++i) {
        v += (med - res[i]) * (med - res[i]);
    }
    v /= n;
    return fabsl(v);
}

void gen(ld &avg, ld &dev, ld &med) {
    n = 19;
    forn(i, 19) {
        res[i] = rand() % 100;
    }
    sort(res, res + 19);
    avg = calcMean();
    dev = calcDev(avg);
    med = res[10];
    forn(i, 19) {
        res[i] = 0;
    }
}

ld m, s, h;

ld genMin()
{
    if (m > h)
    {
        ld q = (n * m - (n + 1) / 2 * h) / (n / 2);

    }
}

ld genMax()
{
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("stats.in", "r", stdin);
    freopen("stats.out", "w", stdout);
    srand(10);
    int t;
    scanf("%d", &t);
    while (t--) {
        cin >> m >> s >> h;
        s *= s;
        genMin();
        genMax();
        //gen(m, s, h);
        //cout << m << " " << s << " " << h << endl;
        char ok = false;
        for (n = 3; n <= 19 && !ok; n += 2) {
            res[n / 2] = h;
            ld left = 0, right = h;
            for (int it = 0; it < 100; ++it)
            {
                ld middle = (left + right) / 2;
                ld x = fillVals(n, m, h, middle);
                if (x > 100+eps || calcDev(m) > s+eps)
                    left = middle;
                else
                    right = middle;
            }
            fillVals(n, m, h, right);
            ld dev = calcDev(m);

            if (fabs(dev - s) < eps) {
                printf("%d", n);
                for (int i = 0; i < n; ++i) {
                    printf(" %.10f", (double) res[i]);
                }
                printf("\n");
                ok = true;
                break;
            }
        }
        if (!ok) {
            puts("-1");
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
