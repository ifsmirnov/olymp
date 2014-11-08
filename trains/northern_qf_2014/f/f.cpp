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
int zz[maxn];
pii a[maxn];
pii b[maxn];
int shr[maxn];
int res[maxn];
int dl[maxn], dr[maxn];
int cnt[maxn];
vi chains[maxn];
int sel[maxn];

void scan() {
//     scanf("%d", &n);
    nr = n;
    forn(i, n) {
//         scanf("%d", &a[i].fi);
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
    int l, r, lv, rv, idx;
    bool operator<(const seg& a) const { return mp(rv, idx) < mp(a.rv, a.idx); }
    int getp(int t) const {
        return a[l + (t - lv)].se;
    }
};

struct ev {
    int id, t, type;
    bool operator<(const ev& a) const { return mp(t, type) < mp(a.t, a.type); }
};

vector<seg> ss;

void go(int t) {
    if (sel[t] != -1) {
        return;
    }
    for (auto cc : chains[t]) {
        if (sel[t-1] != cc && sel[t+1] != cc) {
            sel[t] = cc;
            res[ss[cc].getp(t-1)] = 0;
            return;
        }
    }
    for (auto cc : chains[t]) {
        if (sel[t-1] == cc) {
            sel[t] = cc;
            sel[t-1] = -1;
            res[ss[cc].getp(t-1)] = 0;
            res[ss[cc].getp(t-2)] = 1;
            go(t-1);
            return;
        }
    }
    if (t > 1) {
        go(t-1);
    }
}

int solve() {
    int ns = 0;
    int l = 0;

    forn(i, n) {
        if (i == n-1 || a[i].fi + 1 != a[i+1].fi) {
            ss.pb({l, i, a[l].fi, a[i].fi, ns++});
            l = i+1;
        }
        cnt[a[i].fi]++;
        res[a[i].se] = 1;
    }

    forn(i, ss.size()) {
        fore(j, ss[i].lv + 1, ss[i].rv) {
            chains[j].pb(ss[i].idx);
        }
    }

    forn(i, 100010) {
        sel[i] = -1;
    }

    for (int t = 1; t < 100010; ++t) if (cnt[t]) {
        if (cnt[t-1] == 1) {
//             go(t);
            if (!chains[t].empty()) {
                assert(chains[t].size() == 1u);
                res[ss[chains[t][0]].getp(t-1)] = 0;
                sel[t] = chains[t][0];
//                 assert(sel[t-1] != chains[t][0]);
            }
        }

        if (cnt[t-1] >= 2) {
            go(t);
//             bool ok = false;
//             for (auto it : cur) {
//                 if (sel[t-1] != it.idx) {
//                     sel[t] = it.idx;
//                     res[it.getp(t-1)] = 0;
//                     ok = true;
//                     break;
//                 }
//             }
// 
//             if (!ok) {
// 
//             }
        }
    }

//     forn(i, 10) cout << sel[i] << " "; cout << endl;


    int total = count(res, res + nr, 1);
    return total;
    printf("%d\n", total);
    int last = -1;
    forn(i, nr) {
        if (res[i]) {
            printf("%d ", i - last);
            last = i;
        }
    }
    printf("\n");
    return -1;
}

int gen(int t) {
    int n = 10;
    int k = 5;
    vector<int> a;
    forn(i, n) a.pb(rand()%k);
    sort(all(a));
    vi b;
    forn(i, t) b.pb(rand()%n);
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    b.pb(n);
    int pos = 0;
    vi cur;
    vector<vi> res;
    forn(i, n+1) {
        if (b[pos] == i) {
            ++pos;
            res.pb(cur);
            cur.clear();
            if (i == n) break;
        }
        cur.pb(a[i]);
    }
    n = 0;
    random_shuffle(all(res));
    for (auto b : res) for (auto c : b) {
//         cout << c << " ";
        zz[n] = c;
        ::a[n++].fi = c;
    }
//     cout << endl;
    ::n = n;
//     cout << b.size() - 1 << endl;
    return b.size() - 1;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

//     scan();
//     solve();
// 
//     return 0;

    long long seed;
    asm("rdtsc":"=A"(seed));
    srand(seed);
    cout << "seed = " << seed << endl;
    int t = gen(rand()%4 + 1);
    scan();
    int res = solve();
    if (res > t+1) {
        cout << "err" << endl;
        cout << "ans = " << t+1 << endl;
        forn(i, nr) cout << zz[i] << " "; cout << endl;
        return 1;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
