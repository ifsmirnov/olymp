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
const int sz = 1<<17;

i64 gcd(i64 a, i64 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

i64 rmq[sz*2];
void upd(int i, i64 x) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) {
        rmq[i] = gcd(rmq[i*2], rmq[i*2+1]);
    }
}

int rmost(i64 x) {
    int v = 1;
    assert(x != 1);
    assert(rmq[v] < x);
    while (v < sz) {
        if (gcd(rmq[v*2], x) >= x) {
            v = v*2+1;
        } else {
            v = v*2;
        }
    }
    return v - sz;
}

int n;
i64 a[sz];

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%lld", &a[i]);
    a[n] = 1;
}

void solve() {
    i64 best = n;
    forn(i, n) upd(i, 0);
    upd(n, 1);

    ford(st, n) {
//         cout << "st = " << st << endl;
        upd(st, a[st]);
        i64 cv = a[st];
        while (cv > 1) {
            int r = rmost(cv);
//             cout << "cv = " << cv << ", r = " << r << endl;
            best = max(best, cv * (r - st));
            cv = gcd(cv, a[r]);
        }
    }
    printf("%lld\n", best);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

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
