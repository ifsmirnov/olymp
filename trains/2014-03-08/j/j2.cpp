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
const int maxn = 110;

int n;
int y[maxn];

int yp[maxn];
int minl[maxn];

bool scan() {
    scanf("%d", &n);
    if (n == 0) return false;
    forn(i, 40) y[i] = 0;
    forn(i, n) {
        int x, ty;
        scanf("%d%d", &x, &ty);
        y[x] |= 1<<(ty/2);
    }
    return true;
}
int best;
int solve(int mask) {
    int ct = __builtin_popcount(mask) + 1;
    if (ct - 1 >= best) {
        return best;
    }
    forn(i, ct) yp[i] = 0;
    int p = 0;
    forn(x, 19) {
        if (x && mask&(1<<(x-1))) ++p;
        if (y[x*2] & yp[p]) {
            return 100000;
        }
        yp[p] |= y[x*2];
    }
    forn(i, 20) minl[i] = 1000;
    forn(p, ct) {
        int last = -1;
        int y = yp[p];
        for (int i = 0; y; ++i) if (y & (1<<i)) {
            if (last != -1) {
                minl[last] = min(minl[last], i - 1);
            }
            last = i;
            y ^= (1<<i);
        }
    }

    int res = ct - 1;
    int cl = minl[0];
    forn(i, 20) {
        if (i > cl) {
            ++res;
            cl = minl[i];
        } else {
            cl = min(cl, minl[i]);
        }
    }
    return res;
}

void gen() {
}

int solve() {
    best = 10000;
    forn(i, 1<<18) {
        best = min(best, solve(i));
//         if (i == 1) break;
    }
    return best;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    while (scan()) {
        printf("%d\n", solve());
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
