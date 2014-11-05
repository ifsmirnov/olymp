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

double res[19];

int n;

double calcMean() {
    double v = 0;
    for (int i = 0; i < n; ++i) {
        v += res[i];
    }
    v /= n;
    return v;
}

double calcDev(double med) {
    double v = 0;
    for (int i = 0; i < n; ++i) {
        v += (med - res[i]) * (med - res[i]);
    }
    v /= n;
    v = sqrt(fabs(v));

    return v;
}

void gen(double &avg, double &dev, double &med) {
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
        double m, s, h;
        scanf("%lf%lf%lf", &m, &s, &h);
        //gen(m, s, h);
        //cout << m << " " << s << " " << h << endl;
        char ok = false;
        for (n = 3; n <= 19 && !ok; n += 2) {
            res[n / 2] = h;
            ld left = 0, right = h;
            for (int it = 0; it < 70; ++it)
            {
                ld middle = (left + right) / 2;
                for (int i = 0; i < n / 2; ++i) {
                    res[i] = middle;
                }
                double q = (m * n - (n / 2) * middle - h) / (n / 2);
                for (int i = n / 2 + 1; i < n; ++i)
                    res[i] = q;

                if (calcDev(m) > s)
                    left = middle;
                else
                    right = middle;
            }
//             if (m > h) {
//                 double q = (m * n - ((n + 1) / 2) * h) / (n / 2);
//                 for (int i = (n + 1) / 2; i < n; ++i) {
//                     res[i] = q;
//                 }
// 
//             } else {
//                 for (int i = n / 2; i < n; ++i) {
//                     res[i] = h;
//                 }
//                 double q = (m * n - ((n + 1) / 2) * h) / (n / 2);
//                 for (int i = 0; i < n / 2; ++i) {
//                     res[i] = q;
//                 }
//             }
//             double dev = calcDev(m);
//             if (dev > s + 5e-8) {
//                 continue;
//             }
//             int i = 0, j = n - 1;
//             while (i < n / 2 && j > n / 2) {
// 
//                 double l = 0, r = min(res[i], 100.0 - res[j]);
// 
//                 res[i] -= r;
//                 res[j] += r;
// 
//                 if (calcDev(m) < s - 5e-8) {
//                     if (res[i] < 1e-9) {
//                         ++i;
//                     } else {
//                         --j;
//                     }
//                     continue;
//                 }
// 
// 
//                 res[i] += r;
//                 res[j] -= r;
// 
//                 int it = 70;
// 
//                 while (it--) {
//                     double mid = (l + r) / 2.0;
// 
//                     res[i] -= mid;
//                     res[j] += mid;
// 
//                     if (calcDev(m) > s) {
//                         r = mid;
//                     } else {
//                         l = mid;
//                     }
// 
//                     res[i] += mid;
//                     res[j] -= mid;
//                 }
//                 res[i] -= l;
//                 res[j] += l;
//                 break;
//             }
// 
            fillVals(left);
            dev = calcDev(m);

            if (fabs(dev - s) < 5e-8) {
                printf("dev = %.10lf\n", dev);
                printf("%d", n);
                for (int i = 0; i < n; ++i) {
                    printf(" %.10f", res[i]);
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
