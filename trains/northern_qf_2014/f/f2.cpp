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
const int maxn = 100500;

int n, nr;
pii a[maxn];
pii b[maxn];
int shr[maxn];
int res[maxn];
int dl[maxn], dr[maxn];
int cnt[maxn];

void scan() {
    scanf("%d", &n);
    nr = n;
    forn(i, n) {
        scanf("%d", &a[i].fi);
        a[i].se = i;
        shr[i] = a[i].fi;
    }
    sort(shr, shr+n);
    int k = unique(shr, shr+n) - shr;
    forn(i, n) {
        a[i].fi = lower_bound(shr, shr+k, a[i].fi) - shr;
    }

    k = 0;
    forn(i, n) {
        if (i == n-1 || a[i].fi != a[i+1].fi) {
            b[k++] = a[i];
        }
    }
    forn(i, k) {
        a[i] = b[i];
    }
    n = k;
}

struct seg {
    int l, r, lv, rv;
    bool operator<(const seg& a) const { return mp(lv, rv) < mp(a.lv, a.rv); }
};

void solve() {
    vector<seg> ss;
    int l = 0;

//     forn(i, n) {
//         cout << a[i].fi << " " << a[i].se << endl;
//     }

    forn(i, n) {
        if (i == n-1 || a[i].fi + 1 != a[i+1].fi) {
            res[a[i].se] = 1;
            ss.pb({l, i, a[l].fi, a[i].fi});
//             cout << "add seg " << l << " " << i << endl;
            l = i+1;
        }
        cnt[a[i].fi]++;
    }

    sort(all(ss));
    for (auto s : ss) {
        int l = s.l, r = s.r;
        bool last = false;
        fore(i, l, r-1) {
            int x = a[i].fi;
            int y = a[i+1].fi;
            int pp = a[i].se;
            if (
                    (cnt[x] > 1 && last) ||
                    (cnt[x] > 1 && dl[x]) ||
                    (cnt[y] > 1 && dr[y])
            ) {
                last = false;
                res[pp] = 1;
            } else {
                last = true;
                if (cnt[x] > 1) dl[x] = 1;
                if (cnt[y] > 1) dr[y] = 1;
            }
        }
    }

    int total = count(res, res + nr, 1);
    printf("%d\n", total);
    int last = -1;
    forn(i, nr) {
        if (res[i]) {
//             cout << i << " ";
            printf("%d ", i - last);
            last = i;
        }
    }
    printf("\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
