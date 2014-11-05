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
const int maxn = 1000500;

const int sz = 1<<20;
int rmq[sz * 2];
void upd(int i, int d) {
    i += sz;
    for (; i; i /= 2) rmq[i] += d;
}
int get(int l, int r) {
    l += sz;
    r += sz;
    int res = 0;
    while (l < r) {
        if (l%2 == 1) res += rmq[l];
        if (r%2 == 0) res += rmq[r];
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) res += rmq[l];
    return res;
}

int rpoint(int k) {
    --k;
    int v = 1;
    do {
        if (rmq[v * 2] > k) {
            v *= 2;
        } else {
            k -= rmq[v * 2];
            v = v*2+1;
        }
    } while (v < sz);
    return v - sz;
}

int n, k;

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("joseph.1n", "r", stdin);
    freopen("joseph.out", "w", stdout);

    int n, P;
    cin >> n >> P;
    forn(i, n) upd(i, 1);
    int k, p;
    k = 0;
    forn(i, n) {
        p = P%(n-i);
        if (p == 0) p += n-i;
        int t = get(k, n-1);
        if (t < p) {
            p -= t;
            k = 0;
        }

        k = rpoint(k == 0 ? p : p + ((n-i) - t));
//         cout << "take " << k << endl;
        upd(k, -1);
        if (i == n-1) {
            printf("%d\n", k+1);
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
