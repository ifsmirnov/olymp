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
typedef double ld;

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("sqrooots.in", "r", stdin);
    freopen("sqrooots.out", "w", stdout);

    ld a, b, c;
    cin >> a >> b >> c;
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("-1\n");
            } else {
                printf("0\n");
            }
        } else {
            printf("1\n%.6lf\n", -(ld)c/b);
        }
    } else {
        if (a < 0) a = -a, b = -b, c = -c;
        ld d = b*b - a*c*4.0;
        if (fabsl(d) < 1e-11) {
            printf("1\n");
            printf("%.6lf\n", -(ld)b/a*0.5);
        } else if (d > 0) {
            printf("2\n");
            printf("%.6lf\n", (-b-sqrt(d))/a*0.5);
            printf("%.6lf\n", (-b+sqrt(d))/a*0.5);
        } else {
            printf("0\n");
        }
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
