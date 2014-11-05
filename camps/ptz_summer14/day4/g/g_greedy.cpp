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
#include <list>
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
typedef long long i64;
typedef unsigned long long u64;
const i64 inf = 1e18+100500;
typedef pair<i64, i64> pii;
const int maxn = 125;

int n, m;
int c[maxn][maxn];

list<pii> st[maxn];
list<pii> pl[maxn];
vector<pii> res[maxn][maxn];

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, n) forn(j, m) scanf("%d", &c[i][j]);
}

void insert_after(list<pii>& l, list<pii>::iterator it, const pii &val) {
    --it;
    i64 old_bot = it->fi;
    bool d = val.fi == it->se;
    if (d) it->se = val.se;
    ++it;
    bool u = val.se == it->fi;
    if (u) {
        if (d) {
            it->fi = old_bot;
            --it;
            l.erase(it);
        } else {
            it->fi = val.fi;
        }
    } else if (!d) {
        l.insert(it, val);
    }
}

void push(int i, int j) {
    i64 c = ::c[i][j];
    list<pii>::iterator it1 = st[j].begin();
    list<pii>::iterator it2 = pl[i].begin();
    while (c) {
        i64 l1 = it1->se;
        ++it1;
        i64 r1 = it1->fi;
        --it1;

        i64 l2 = it2->se;
        ++it2;
        i64 r2 = it2->fi;
        --it2;

        assert(r1 > l1);
        assert(r2 > l2);

        if (r2 <= l1) { ++it2; continue; }
        if (r1 <= l2) { ++it1; continue; }

        i64 d = min(c, min(r1, r2) - max(l1, l2));
        i64 s = max(l1, l2);
        res[i][j].pb(mp(s, s+d));

        ++it1; ++it2;
        insert_after(st[j], it1, mp(s, s+d));
        insert_after(pl[i], it2, mp(s, s+d));
        --it1; --it2;

        c -= d;
        if (c == 0) break;

        break;
    }
}

void solve() {
    forn(i, n) {
        pl[i].push_back(mp(-1, 0));
        pl[i].push_back(mp(inf, inf));
    }
    forn(j, m) {
        st[j].push_back(mp(-1, 0));
        st[j].push_back(mp(inf, inf));
    }
    forn(i, n) {
        forn(j, m) {
            push(i, j);
        }
    }
}

vector<i64> shr;
void shrink() {
    forn(i, n) forn(j, m) forn(k, res[i][j].size()) {
        shr.pb(res[i][j][k].fi);
        shr.pb(res[i][j][k].se);
    }
    sort(all(shr));
    shr.erase(unique(all(shr)), shr.end());
    assert(shr.size() < 100000u);
}

vi ans[100500];

void print() {
    shrink();
    forn(i, shr.size() - 1) ans[i].resize(n);
    forn(i, n) {
        forn(j, m) {
            for (auto x: res[i][j]) {
                int b = lower_bound(all(shr), x.fi) - shr.begin();
                int e = lower_bound(all(shr), x.se) - shr.begin();
                for (int k = b; k < e; ++k) ans[k][i] = j+1;
            }
        }
    }
    printf("%lld %d\n", shr.back(), (int)shr.size() - 1);
    forn(i, shr.size() - 1) {
        printf("%lld", shr[i+1] - shr[i]);
        forn(j, n) printf(" %d", ans[i][j]);
        printf("\n");
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();
    print();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
