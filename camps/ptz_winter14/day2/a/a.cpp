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
const int maxn = 1000500;

int n;
int a[maxn];
int q;
int lp[maxn], rp[maxn];
int res[maxn];

vector<pii> lfr[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d", &a[i]);
    scanf("%d", &q);
    forn(i, q) {
        scanf("%d%d", &lp[i], &rp[i]);
        --lp[i];
        --rp[i];
        lfr[lp[i]].pb(mp(rp[i], i));
    }
    forn(i, n) {
        sort(all(lfr[i]));
        reverse(all(lfr[i]));
    }
}

bool cmp(int i, int j) { return rp[i] < rp[j]; }

int prim = 0, sec = 0;
struct node {
    int l, r;
    node *L, *R;
    vi vals;
    int mn;

    node(){}
    node(int lq, int rq) : l(lq), r(rq) {
        if (l == r) {
            L = R = NULL;
            vals.resize(lfr[l].size());
            forn(i, vals.size()) {
                vals[i] = lfr[l][i].se;
            }
            mn = vals.empty() ? inf : rp[vals.back()];
        } else {
            L = new node(lq, (lq+rq)/2);
            R = new node((lq+rq)/2+1, rq);
            mn = min(L->mn, R->mn);
        }
    }
    void remove(int lq, int rq, int mex) {
        if (l == 0 && r == n-1) ++prim;
        ++sec;
        if (lq <= l && rq >= r) {
            if (l == r) {
                while (!vals.empty() && rp[vals.back()] <= rq) {
                    res[vals.back()] = mex;
                    vals.pop_back();
                }
                mn = vals.empty() ? inf : rp[vals.back()];
            } else {
                if (L->mn <= rq) L->remove(lq, rq, mex);
                if (R->mn <= rq) R->remove(lq, rq, mex);
                mn = min(L->mn, R->mn);
            }
        } else if (lq > r || rq < l) {
        } else {
            L->remove(lq, rq, mex);
            R->remove(lq, rq, mex);
            mn = min(L->mn, R->mn);
        }
    }
};

#define fpos tratata_ya_ubil_traktorista
#define next trururu
int fpos[maxn], next[maxn], last[maxn];

void gennext() {
    forn(i, maxn) fpos[i] = -1;
    forn(i, maxn) next[i] = -1;
    forn(i, maxn) last[i] = -1;
    forn(i, n) {
        int c = a[i];
        if (fpos[c] == -1) {
            fpos[c] = i;
            last[c] = i;
        } else {
            next[last[c]] = i;
            last[c] = i;
        }
    }
}

void solve() {
    gennext();
    forn(i, q) res[i] = -1;

    node *t = new node(0, n-1);

    forn(i, maxn) {
        if (fpos[i] == -1) {
            forn(j, q) {
                if (res[j] == -1) {
                    res[j] = i;
                }
            }
            break;
        } else {
            int l = -1, r = fpos[i];
            while (1) {
                t->remove(l+1, r-1, i);
                if (r == n) break;
                l = r;
                r = next[r] == -1 ? n : next[r];
            }
        }
    }

    cerr << "prim = " << prim << endl;
    cerr << "sec = " << sec << endl;

    forn(i, q) {
        printf("%d\n", res[i]);
    }
}

void gen() {
    freopen("input.txt", "w", stdout);
    int n = 1000000;
    printf("%d\n", n);
//     forn(i, n) printf("%d ", rand()%10000);
    forn(i, n) printf("%d ", i);
    int q = 1000000;
    printf("\n%d\n", q);
    forn(i, q) {
        int l = rand()%n;
        int r = rand()%n;
        if (l > r) swap(l, r);
        printf("%d %d\n", l+1, r+1);
    }
    exit(0);
}

int main() {
//     gen();
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scan();
    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
