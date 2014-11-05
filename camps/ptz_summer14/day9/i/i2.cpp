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

const ld eps = 1e-10;

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
//     v = sqrtl(fabs(v));
// 
//     return v;
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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
//     freopen("stats.in", "r", stdin);
//     freopen("stats.out", "w", stdout);
    srand(10);
    int t;
    scanf("%d", &t);
    while (t--) {
        ld m, s, h;
//         scanf("%lf%lf%lf", &m, &s, &h);
        cin >> m >> s >> h;
        s *= s;
        //gen(m, s, h);
        //cout << m << " " << s << " " << h << endl;
        char ok = false;
        for (n = 3; n <= 19 && !ok; n += 2) {
            if (m > h) {
                for (int i = 0; i < (n + 1) / 2; ++i) {
                    res[i] = h;
                }
                ld q = (m * n - ((n + 1) / 2) * h) / (n / 2);
                for (int i = (n + 1) / 2; i < n; ++i) {
                    res[i] = q;
                }

            } else {
                for (int i = n / 2; i < n; ++i) {
                    res[i] = h;
                }
                ld q = (m * n - ((n + 1) / 2) * h) / (n / 2);
                for (int i = 0; i < n / 2; ++i) {
                    res[i] = q;
                }
            }
            ld dev = calcDev(m);
            if (dev > s + eps) {
                continue;
            }
            int i = 0, j = n - 1;
            while (i < n / 2 && j > n / 2) {

                ld l = 0, r = min(res[i], 100.0 - res[j]);

                res[i] -= r;
                res[j] += r;

                if (calcDev(m) < s - eps) {
                    if (res[i] < eps) {
                        ++i;
                    } else {
                        --j;
                    }
                    continue;
                }


                res[i] += r;
                res[j] -= r;

                int it = 70;

                while (it--) {
                    ld mid = (l + r) / 2.0;

                    res[i] -= mid;
                    res[j] += mid;

                    if (calcDev(m) > s) {
                        r = mid;
                    } else {
                        l = mid;
                    }

                    res[i] += mid;
                    res[j] -= mid;
                }
                res[i] -= l;
                res[j] += l;
                break;
            }

            dev = calcDev(m);

            if (fabs(dev - s) < eps) {
            printf("dev = %.10lf\n", (double)sqrtl(dev));
                printf("%d", n);
                for (int i = 0; i < n; ++i) {
                    printf(" %.10f", (double)res[i]);
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
