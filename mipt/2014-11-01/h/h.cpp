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

const int maxn = 1000600;

#define y1 motherfucker

int n;
int x1[maxn], y1[maxn], z1[maxn], x2[maxn], y2[maxn], z2[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d%d%d%d%d%d", &x1[i], &y1[i], &z1[i], &x2[i], &y2[i], &z2[i]);
    }
    forn(i, n) {
        if (x1[i] > x2[i]) swap(x1[i], x2[i]);
        if (y1[i] > y2[i]) swap(y1[i], y2[i]);
        if (z1[i] > z2[i]) swap(z1[i], z2[i]);
    }
}

void rotate() {
    forn(i, n) {
        int t;
        t = x1[i]; x1[i] = y1[i]; y1[i] = z1[i]; z1[i] = t;
        t = x2[i]; x2[i] = y2[i]; y2[i] = z2[i]; z2[i] = t;
    }
}

bool check() {
    int mnx = -inf, mny = -inf, mxx = inf, mxy = inf, mnz = inf, mxz = -inf;
    int cnt = 0;
    forn(i, n) if (z1[i] == z2[i]) {
        ++cnt;
        mnx = max(mnx, x1[i]);
        mny = max(mny, y1[i]);
        mxx = min(mxx, x2[i]);
        mxy = min(mxy, y2[i]);

        mnz = min(mnz, z1[i]);
        mxz = max(mxz, z2[i]);
    }

    if (cnt == n || mnx == -inf) { // empty set A
        return false;
    }

#define in(x, y) (x>=mnx&&x<=mxx&&y>=mny&&y<=mxy)

    forn(i, n) {
        if (y1[i] == y2[i]) {
            if (z1[i] >= mnz || z2[i] <= mxz) {
                return false;
            }
            if ((in(x1[i], y1[i]) == in(x2[i], y2[i]))) {
                return false;
            }
        } else if (x1[i] == x2[i]) {
            if (z1[i] >= mnz || z2[i] <= mxz) {
                return false;
            }
            if ((in(x1[i], y1[i]) == in(x2[i], y2[i]))) {
                return false;
            }
        }
    }

    return true;
}

void solve() {
    forn(i, 3) {
        if (check()) {
            printf("YES\n");
            return;
        }
        rotate();
    }
    printf("NO\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif


    int t;
    scanf("%d", &t);
    forn(i, t) {
        scan();
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
