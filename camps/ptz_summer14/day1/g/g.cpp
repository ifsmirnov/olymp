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
const int maxn = 300300;

i64 h[maxn];
void fillh() {
    forn(i, 300000) h[i] = rand() ^ ((i64)rand() << 32);
}

struct rec {
    int n, k;
    vi a;
    rec():hh(-1){}
    i64 hh;
    rec(int n): n(n), k(0),hh(-1) {}
    void read() {
        a.resize(n);
        forn(i, n) scanf("%d", &a[i]), --a[i];
        int mx = -1;
        forn(i, n) if (a[i] > mx) ++k, mx = a[i];
    }
    i64 hash() {
        if (hh == -1) {
            i64 s = 0;
            forn(i, n) s += h[i] * a[i];
            return hh = s;
        }
        return hh;
    }

    void out() {
        printf("%d r", n);
        forn(i, n) printf(" %d", a[i] + 1);
        printf("\n");
    }
};

struct cyc {
    static int t[maxn];
    static int b[maxn];

    int n, k;
    vector<vi> a;
    i64 hh;
    cyc():hh(-1) {}
    cyc(int n): n(n), k(0),hh(-1) {}
    void read() {
        forn(i, n) scanf("%d", &t[i]), --t[i];
        forn(i, n) b[i] = 0;
        forn(i, n) if (b[i] == 0) {
            vi c;
            for (int j = i; !b[j]; j = t[j]) {
                c.pb(j);
                b[j] = 1;
            }
            ++k;
            a.pb(c);
        }
//         cout << "read cycle, k = " << k << endl;
    }

    void out() {
//         cout << "my h = " << hash() << endl;
        vi r(n);
        forn(i, a.size()) forn(j, a[i].size()) {
            r[a[i][j]] = a[i][(j+1)%a[i].size()];
        }
        printf("%d c", n);
        forn(i, n) printf(" %d", r[i]+1);
        printf("\n");
    }

    i64 hash() {
        if (hh==-1) {
            i64 s = 0;
            forn(i, a.size()) forn(j, a[i].size()) {
                s += h[300000 - 1 - j] * h[i] * a[i][j];
            }
            return hh=s;
        }
        return hh;
    }
};
int cyc::t[maxn];
int cyc::b[maxn];

vector<cyc> cycs;
vector<rec> recs;

map<pii, vi> bc;
map<pii, vi> br;

set<i64> hc;
set<i64> hr;

int fen[maxn];
void setf(int i, int x) {
    for (; i < maxn; i |= (i+1)) fen[i] += x;
}
int getf(int i) {
    int s = 0;
    for (; i >= 0; i = (i&(i+1))-1) s += fen[i];
    return s;
}

// generate

set<int> unused;
int n;
int n_rec;
vi curperm;
void gen_rec(int pos, int cur_rec, int last_max, int &lft, i64 curhash) {
    if (pos == n) {
        if (cur_rec != n_rec) return;
        if (hr.find(curhash) != hr.end()) return;
        --lft;
        recs.pb(rec(n));
        recs.back().a = curperm;
        br[mp(n, n_rec)].pb(recs.size() - 1);
        hr.insert(curhash);
        return;
    }
    if (cur_rec > n_rec) {
        return;
    } else if (cur_rec == n_rec) {
        if (*unused.rbegin() > last_max) {
            return;
        }
    } else {
        int lft_greater = n - pos - (last_max + 1 - getf(last_max));
        if (cur_rec + lft_greater < n_rec) {
            return;
        }
    }
    set<int>::iterator it = unused.begin();
    while (it != unused.end()) {
        int val = *it;
        setf(val, 1);
        unused.erase(it);
        curperm[pos] = val;
        int newcr = cur_rec;
        int newlm = last_max;
        if (val > last_max) {
            newcr++;
            newlm = val;
        }
        gen_rec(pos + 1, newcr, newlm, lft, curhash + h[pos] * val);
        if (lft == 0) {
            return;
        }
        it = unused.insert(val).first;
        ++it;
        setf(val, -1);
    }
}

void gen_rec(int n, int k, int num) {
//     cout << "generate " << num << " records using " << n << " " << k << endl;
    unused.clear();
    forn(i, n) unused.insert(i);
    forn(i, n) fen[i] = 0;
    curperm.assign(n, -1);
    ::n = n;
    ::n_rec = k;
    gen_rec(0, 0, -1, num, 0);
    assert(num == 0);
}

int n_cyc;
vector<vi> curc;
void gen_cycle(int pos, int maxc, int &lft, i64 curhash) {
    if (pos == n) {
        if (maxc + 1 != n_cyc) return;
        if (hc.find(curhash) != hc.end()) return;
        --lft;
        cycs.pb(cyc(n));
        cycs.back().a = curc;
        assert(curhash == cycs.back().hash());
        bc[mp(n, n_cyc)].pb(cycs.size() - 1);
        hc.insert(curhash);
        return;
    }
    if (maxc + 1 + (n - pos) < n_cyc) return;
    if (maxc != -1) {
        set<int>::iterator it = unused.begin();
        while (it != unused.end()) {
            int val = *it;
            unused.erase(it);

            curc[maxc].pb(val);
            gen_cycle(pos + 1, maxc, lft, curhash + h[maxc] * h[300000 - 1 - (curc[maxc].size() - 1)] * val);
            if (lft == 0) return;
            curc[maxc].pop_back();

            it = unused.insert(val).first;
            ++it;
        }
    }

    if (maxc + 1 < n_cyc) {
        ++maxc;
        int val = *unused.begin();
        unused.erase(unused.begin());

        curc[maxc].pb(val);
        gen_cycle(pos + 1, maxc, lft, curhash + h[maxc] * h[300000 - 1] * val);
        curc[maxc].pop_back();
        unused.insert(val);
    }
}

void gen_cycle(int n, int k, int num) {
//     cout << "generate " << num << " cycles" << endl;
    ::n = n;
    n_cyc = k;
    curc.assign(k, vi());
    unused.clear();
    forn(i, n) unused.insert(i);
    gen_cycle(0, -1, num, 0);
    assert(num == 0);
}

// end_generate

int num_inp;
int ord[maxn];
void read() {
    scanf("%d", &num_inp);
    char t[3];
    forn(i, num_inp) {
        int n;
        scanf("%d", &n);
        scanf("%s", t);
        if (t[0] == 'r') {
            recs.pb(rec(n));
            recs.back().read();
            if (!hr.count(recs.back().hash())) {
                hr.insert(recs.back().hash());
                br[mp(n, recs.back().k)].pb(recs.size() - 1);
            }
            ord[i] = 0;
        } else {
            cycs.pb(cyc(n));
            cycs.back().read();
            if (!hc.count(cycs.back().hash())) {
                hc.insert(cycs.back().hash());
                bc[mp(n, cycs.back().k)].pb(cycs.size() - 1);
            }
            ord[i] = 1;
        }
    }
}

map<i64, int> r2c, c2r;

void solve() {
//     cout << "cycles: " << endl;
    for (map<pii, vi>::iterator it = bc.begin(); it != bc.end(); ++it) {
        int mcnt = it->se.size();
        auto it1 = br.find(it->fi);
        int rcnt = it1 == br.end() ? 0 : it1->se.size();
//         cout << it->fi.fi << " " << it->fi.se << ": " << mcnt << " " << rcnt << endl;
        if (mcnt > rcnt) {
            gen_rec(it->fi.fi, it->fi.se, mcnt - rcnt);
        }
    }
//     cout << "records: " << endl;
    for (map<pii, vi>::iterator it = br.begin(); it != br.end(); ++it) {
        int mcnt = it->se.size();
        auto it1 = bc.find(it->fi);
        int rcnt = it1 == bc.end() ? 0 : it1->se.size();
//         cout << it->fi.fi << " " << it->fi.se << ": " << mcnt << " " << rcnt << endl;
        if (mcnt > rcnt) {
            gen_cycle(it->fi.fi, it->fi.se, mcnt - rcnt);
        }
    }

    for (map<pii, vi>::iterator it = bc.begin(); it != bc.end(); ++it) {
        const vi& cycn = it->se;
        const vi& recn = br[it->fi];
        assert(cycn.size() == recn.size());
        forn(i, cycn.size()) {
            i64 chc = cycs[cycn[i]].hash();
            i64 chr = recs[recn[i]].hash();
            c2r[chc] = recn[i];
            r2c[chr] = cycn[i];
        }
    }
}

void out() {
    int rp = 0, cp = 0;
    forn(i, num_inp) {
        if (ord[i] == 0) {
//             cout << "wanter.hash() = " << recs[rp].hash() << endl;
//             cout << "id = " << r2c[recs[rp].hash()] << endl;
            cycs[r2c[recs[rp++].hash()]].out();
        } else {
            recs[c2r[cycs[cp++].hash()]].out();
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("records-and-cycles.in", "r", stdin);
    freopen("records-and-cycles.out", "w", stdout);

    fillh();
    read();
    solve();
    printf("%d\n", num_inp);
    out();
//     gen_cycle(300000, 300, 10);
//     cout << cycs.size() << endl;
//     gen_rec(300000, 300, 10);
//     cout << recs.size() << endl;
//     forn(i, cycs.size()) {
//         auto& a = cycs[i].a;
//         forn(j, a.size()) {
//             forn(k, a[j].size()) cout << a[j][k] << " ";
//             cout << endl;
//         }
//         cout << "---\n";
//     }
//     cout << "------------------" << endl;
//     cout << recs.size() << endl;
//     forn(i, recs.size()) {
//         forn(j, recs[i].a.size()) cout << recs[i].a[j] << " ";
//         cout << endl;
//     }
// 
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
