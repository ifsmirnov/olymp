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
const int maxn = 505;
const int maxw = 20010;
const i64 inf = 1e18+100500;


int n, k;
int a[maxn], d[maxn], c[maxn]; // constant, delta, amount
int q[maxn];

void scan() {
    scanf("%d%d", &n, &k);
    forn(i, n) scanf("%d%d%d", &a[i], &d[i], &c[i]);
    forn(i, k) scanf("%d", &q[i]);
}

i64 ks[maxn][maxw];

inline i64 getCost(int k, i64 cnt) {
    return (2ll * a[k] - 1ll * d[k] * (cnt - 1)) * cnt / 2;
}

// n * n * w
void buildKS() {
    forn(fb, n) {
        forn(j, maxw) ks[fb][j] = inf;
        ks[fb][0] = 0;
        forn(i, n) if (i != fb) {
            i64 cc = getCost(i, c[i]);
            for (int j = maxw-1; j >= c[i]; --j) {
                if (ks[fb][j-c[i]] != inf) {
                    ks[fb][j] = min(
                            ks[fb][j],
                            ks[fb][j-c[i]] + cc);
                }
            }
        }
    }
}

int order[maxn];

// n * w
i64 solve(int m) {
    i64 res = inf;
    forn(i, n) order[i] = i;
    random_shuffle(order, order+n);
    forn(V, n) { // what to take
        int v = order[V];
        for (int z = 0; z <= min(m, c[v]); ++z) {
            i64 cost = getCost(v, z);
            if (cost >= res) {
                break;
            }
            res = min(res, cost + ks[v][m-z]);
        }
    }
    return res;
}

void solve() {
    buildKS();
    forn(i, k) {
        cout << solve(q[i]) << "\n";
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
