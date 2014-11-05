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

int n, q;
map<pii, int> a;
int p;

void reflect(int x) {
    vector<pair<pii, int> > b;
    for (map<pii, int>::iterator it = a.begin(); it != a.end();) {
        int l = it->fi.fi, r = it->fi.se, c = it->se;
        if (l >= x) {
            ++it;
        } else if (r <= x) {
            b.pb(mp(mp(2*x - r, 2*x - l), c));
            auto itr = it;
            ++it;
            a.erase(itr);
        } else {
            b.pb(mp(mp(x, r), c));
            b.pb(mp(mp(x, 2*x - l), c));
            auto itr = it;
            ++it;
            a.erase(itr);
        }
    }
    forn(i, b.size()) a[b[i].fi] += b[i].se;
}

inline int intersect(int l, int r, int lq, int rq) {
    l = max(l, lq);
    r = min(r, rq);
    if (l < r) return r - l;
    else return 0;
}

int get(int l, int r) {
    int res = 0;
    for (const auto& it: a) {
        int lq = it.fi.fi, rq = it.fi.se;
        res += intersect(l, r, lq, rq) * it.se;
    }
    return res;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scanf("%d%d", &n, &q);
    a[mp(0, n)] = 1;
    forn(i, q) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int r;
            scanf("%d", &r);
            reflect(p + r);
            p += r;
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", get(p+l, p+r));
        }
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
