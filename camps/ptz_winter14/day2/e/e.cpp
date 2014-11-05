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

struct TPoint {
    double x, y, z;
    
    TPoint(double x = 0, double y = 0, double z = 0)
        : x(x)
        , y(y)
        , z(z)
    {
    }
    
    TPoint operator-(const TPoint &p) const {
        return TPoint(x - p.x, y - p.y, z - p.z);
    }
    
    double operator*(const TPoint &p) const {
        return x * p.x + y * p.y + z * p.z;
    }
    
    TPoint operator^(const TPoint &p) const {
        return TPoint(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
};

double vol(const TPoint &a, const TPoint &b, const TPoint &c, const TPoint &d) {
    return (b - a) * ((c - a) ^ (d - a));
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int N;
    cin >> N;
    vector<TPoint> a(N);
    vector<double> p(N);
    forn(i, N) {
        cin >> p[i] >> a[i].x >> a[i].y >> a[i].z;
    }
    double ans = 0;
    forn(i, N) {
        double q = 1.0;
        forn(j, N) {
            if (i == j) {
                q *= p[j];
            } else {
                q *= 1 - p[j];
            }
        }
        ans += q;
    }
    cerr << ans << '\n';
    forn(i, N) {
        for (int j = i + 1; j < N; ++j) {
            double q = 1.0;
            forn(k, N) {
                if (k == i || k == j) {
                    q *= p[k];
                } else {
                    q *= 1 - p[k];
                }
            }
            ans += 2 * q;
        }
    }
    cerr << ans << '\n';
    forn(i, N) {
        for (int j = i + 1; j < N; ++j) {
            for (int k = j + 1; k < N; ++k) {
                double q = 1.0;
                forn(l, N) {
                    if (l == i || l == j || l == k) {
                        q *= p[l];
                    } else {
                        q *= 1 - p[l];
                    }
                }
                ans += 3 * q;
            }
        }
    }
    //cerr << ans << '\n';
    
    forn(i, N) {
        forn(j, N) {
            if (i == j) {
                continue;
            }
            forn(k, N) {
                if (k == i || k == j) {
                    continue;
                }
                double total = 1.0, emp = 1.0;
                forn(l, N) {
                    if (l == i || l == j || l == k) {
                        total *= p[l];
                        emp *= p[l];
                    } else {
                        if (vol(p[i], p[j], p[k], p[l]) > 0.0) {
                            total *= 1 - p[l];
                            emp *= 1 - p[l];
                        } else {
                            emp *= 1 - p[l];
                        }
                    }
                }
                ans += total - emp;
            }
        }
    }
    printf("%.10lf\n", ans);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
