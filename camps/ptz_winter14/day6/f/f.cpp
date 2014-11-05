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
const int maxn = 400500;

int x[maxn], y[maxn]; // dup

int mmax(int i, int j) {
    bool tt;
    if (y[i] != y[j]) tt = y[i] > y[j];
    else if (x[i] != x[j]) tt = x[i] < x[j];
    else tt = i < j;
    return tt ? i : j;
}
const int sz = 1<<19;
int rmq[sz*2];
void init() {
    y[maxn-1] = -1;
    forn(i, sz*2) rmq[i] = maxn-1;
}
int get(int l, int r) {
    l += sz;
    r += sz;
    int mx = maxn-1;
    while (l < r) {
        if (l%2 == 1) mx = mmax(mx, rmq[l]);
        if (r%2 == 0) mx = mmax(mx, rmq[r]);
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) mx = mmax(mx, rmq[l]);
    return mx;
}
void upd(int i, int x) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) {
        rmq[i] = mmax(rmq[i*2], rmq[i*2+1]);
    }
}

int shr[maxn], k;
int n;
int order[maxn];
int pos[maxn];
int taken[maxn];
bool cmp(int i, int j) {
    if (x[i] != x[j]) return x[i] < x[j];
    else if (y[i] != y[j]) return y[i] > y[j];
    else return i < j;
}

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d%d", &x[i], &y[i]);
    forn(i, n) shr[i] = x[i];
    forn(i, n) shr[i+n] = y[i];
    sort(shr, shr+2*n);
    k = unique(shr, shr+2*n) - shr;

    forn(i, n) {
        y[i+n] = x[i] = lower_bound(shr, shr+k, x[i]) - shr;
        x[i+n] = y[i] = lower_bound(shr, shr+k, y[i]) - shr;
    }
}

void solve() {
    forn(i, n) taken[i] = 0;
    forn(i, n*2) order[i] = i;
    sort(order, order+n*2, cmp);
    forn(i, n*2) upd(i, order[i]);
    forn(i, n*2) pos[order[i]] = i;

//     forn(i, n*2) cout << x[i] << " " << y[i] << endl;
//     cout << endl;
//     forn(i, n*2) cout << order[i] << " "; cout << endl;

    vector<int> res;
    int last = -1;
    int cnt = 0;
    while (1) {
//         if (++cnt == 100) break;
        int t = get(last + 1, n*2-1);
        if (t == maxn-1) break;
        if (taken[t%n]) {
            upd(pos[t], maxn-1);
            continue;
        }
        else taken[t%n] = 1;
        upd(pos[t], maxn-1);
        res.pb(t);
        last = pos[t];
    }

    if (res.size() == (size_t) n) {
        printf("yes\n");
        forn(i, res.size()) {
            printf("%d %d\n", shr[x[res[i]]], shr[y[res[i]]]);
        }
    } else {
        printf("no\n");
    }
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    init();
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
