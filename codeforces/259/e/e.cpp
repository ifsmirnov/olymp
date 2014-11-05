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
#define forp(i, b, e) for (int i = (int)(b); i < (int)(e); ++i)
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
const int K = 120;
const int nbl = maxn / K + 5;

int n;
int st[maxn], man[maxn], reg[maxn], fd[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d%d%d", &st[i], &man[i], &reg[i]);
        if (reg[i] == 0) fd[i] = inf;
        else fd[i] = (man[i] + reg[i] - 1) / reg[i];
    }
}

int cur[maxn];
int lbl[maxn];
int updt[nbl];
int clrt[nbl];
i64 sr[nbl];
i64 sc[nbl];
vector<pair<int, pii> > rm[nbl];
vector<pair<int, pii> > crm[nbl];

inline int death_time(int i) {
    if (reg[i] == 0) return inf;
    return (man[i] - cur[i] + reg[i] - 1) / reg[i];
}

void apply_block(int bn, int t) {
    if (clrt[bn] > updt[bn]) {
        int lq = bn * K;
        int rq = min(lq + K, n);
        int d = t - clrt[bn];

        forp(i, lq, rq) {
            i64 c = min((i64)d * reg[i], (i64)man[i]);
            cur[i] = c;
        }
    } else {
        int lq = bn * K;
        int rq = min(lq + K, n);
        int d = t - updt[bn];

        forp(i, lq, rq) {
            i64 c = min(cur[i] + (i64)d * reg[i], (i64)man[i]);
            cur[i] = c;
        }
    }
        int lq = bn * K;
        int rq = min(lq + K, n);
    sc[bn] = 0;
    forp(i, lq, rq) sc[bn] += cur[i];
}

void update_block(int bn, int t) {
    int lq = bn * K;
    int rq = min(lq + K, n);

    updt[bn] = t;

    vector<pii> deaths;
    forp(i, lq, rq) {
        deaths.pb(mp(death_time(i), i));
    }
    sort(all(deaths));

    rm[bn].clear();
    rm[bn].pb(mp(0, mp(0, 0)));
    i64 cr = 0, cm = 0;
    forn(i, deaths.size()) {
        cr += reg[deaths[i].se];
        cm += man[deaths[i].se] - cur[deaths[i].se];
        rm[bn].pb(mp(deaths[i].fi, mp(cr, cm)));
    }
    rm[bn].pb(mp(inf, mp(0, 0)));
}

i64 get_entire_block(int bn, int t) {
    vector<pair<int, pii> > &r =
        clrt[bn] > updt[bn] ?
        crm[bn] :
        rm[bn];
    int tpos = max(clrt[bn], updt[bn]);
    pair<int, pii> v = *--upper_bound(all(r), mp(t - tpos, mp(-1, -1)));
    return (i64)(sr[bn] - v.se.fi) * (t - tpos) + v.se.se + sc[bn];
}

void init() {
    forn(i, (n+K-1)/K) {
        update_block(i, 0);
        crm[i].swap(rm[i]);
    }
    forn(i, n/K+1) clrt[i] = -1;
    forn(i, n) cur[i] = st[i];
    forn(i, (n+K-1)/K) {
        update_block(i, 0);
    }
    forn(i, n) sr[i/K] += reg[i], sc[i/K] += cur[i];
}

i64 get_part_block(int t, int l, int r) {
    int bn = l/K;
    apply_block(bn, t);
    int res = 0;
    fore(i, l, r) {
        res += cur[i];
        cur[i] = 0;
    }
    updt[bn] = t;
    return res;
}

i64 query(int t, int l, int r) {
    int lq = l/K;
    int rq = r/K;
    if (lq == rq) {
        return get_part_block(t, l, r);
    } else {
        i64 res = 0;
        res += get_part_block(t, l, lq * K + K - 1);
        res += get_part_block(t, rq * K, r);
        for (int i = lq + 1; i < rq; ++i) {
            res += get_entire_block(i, t);
            clrt[i] = t;
            sc[i] = 0;
        }
        return res;
    }
}

void solve() {
    int q;
    scanf("%d", &q);
    forn(i, q) {
        int t, l, r;
        scanf("%d%d%d", &t, &l, &r);
        --l; --r;
        cout << query(t, l, r) << "\n";
    }
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    scan();
    init();
//     for (auto i: crm[0]) {
//         cout << i.fi << ": " << i.se.fi << " " << i.se.se << endl;
//     }
    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
