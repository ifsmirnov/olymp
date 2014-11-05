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
vi y[maxn];

int k[maxn];
int a[maxn][maxn];

bool scan() {
    scanf("%d", &n);
    if (n == 0) return false;
    forn(i, 40) y[i].clear();
    forn(i, n) {
        int x, ty;
        scanf("%d%d", &x, &ty);
        y[x].pb(ty);
    }
    forn(i, 19) sort(all(y[i*2]));
    return true;
}

vector<pii> prs;

int best;
int solveseg(int res) {
    if (res >= best) return res;
    sort(all(prs));
//     forn(i, prs.size()) cout << prs[i].fi << " " << prs[i].se << endl;
    int cnt = 0;
    int miny = 0;
    prs.pb(mp(100000, 100000));
    forn(i, prs.size()) {
        if (res >= best) return res;
        if (cnt == 0) {
            miny = prs[i].se;
            cnt = 1;
        } else if (prs[i].fi > miny) {
            ++res;
            miny = prs[i].se;
            cnt = 1;
        } else {
            miny = min(miny, prs[i].se);
            ++cnt;
        }
    }
//     cout << "res = " << res+1 << endl;
    return res;
}

int solve(int mask) {
//     cout << "mask = " << mask << endl;
    int ct = __builtin_popcount(mask) + 1;
    forn(i, ct) k[i] = 0;
    int p = 0;
    forn(x, 19) {
        if (x && mask&(1<<(x-1))) ++p;
        forn(i, y[x*2].size()) a[p][k[p]++] = y[x*2][i];
    }
    prs.clear();
    forn(p, ct) {
        stable_sort(a[p], a[p]+k[p]);
        forn(i, k[p]) if (i) {
            if (i && a[p][i-1] == a[p][i]) {
                return 100000;
            }
            prs.pb(mp(a[p][i-1] + 1, a[p][i] - 1));
        }
    }
    return solveseg(ct - 1);
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
