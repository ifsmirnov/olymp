#include <unordered_map>
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

const int maxn = 100600;

const int sz = 1<<17;
int rmq[sz*2];
void upd(int i, int x) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) {
        rmq[i] = __gcd(rmq[i*2], rmq[i*2+1]);
    }
}
int rmost(int x) {
    int v = 1;
    while (v < sz) {
        if (rmq[v*2] % x == 0) {
            v = v*2+1;
        } else {
            v = v*2;
        }
    }
    return v - sz;
}

int n;
int a[maxn];
unordered_map<int, i64> gc;

void scan() {
//     scanf("%d", &n);
//     forn(i, n) scanf("%d", &a[i]);
    n = 50000;
    forn(i, n) {
        a[i] = 1000000000 - rand()%1000;
    }
}

void precalc() {
    a[n] = 1;

    upd(n, 1);
    ford(i, n) {
        upd(i, a[i]);
        int x = a[i], pos = i;
        while (pos < n) {
            if (x == 1) {
                gc[1] += n-pos;
                break;
            }
            int npos = rmost(x);
            gc[x] += (i64)(npos - pos);
            x = __gcd(x, a[npos]);
            pos = npos;
        }
    }
}

int f(int x) {
    i64 cnt = 0;
    for (int r = 0; r < n; ++r) {
        int t = 0;
        for (int l = r; l < n; ++l) {
            t = __gcd(t, a[l]);
            if (t == x) ++cnt;
            if (t < x) break;
        }
    }
    return cnt;
}

void solve() {
    int q;
//     scanf("%d", &q);
    q = 10;
    forn(i, q) {
        int x;
//         scanf("%d", &x);
        x = i+1;
        assert(gc[x] == f(x));
        cout << gc[x] << "\n";
        cout << flush;
//         printf("%lld\n", gc[x]);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    scan();
    precalc();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
