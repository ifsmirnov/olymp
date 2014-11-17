// real    6m15.000s
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

const int maxn = (1<<16) + 5;

int d[maxn];
int q[maxn], lq, rq;
int a[4][4];
char s[10];
int m;

void scan() {
    forn(i, 4) {
        scanf("%s", s);
        forn(j, 4) m = m*2 + (s[j] == 'b');
    }
}

int move(int x, int p, int q) {
    int k = 15;
    forn(i, 4) forn(j, 4) {
        a[i][j] = 1&(x>>k);
        --k;
    }
    a[p][q] ^= 1;
    if (p) a[p-1][q] ^= 1;
    if (q) a[p][q-1] ^= 1;
    if (p != 3) a[p+1][q] ^= 1;
    if (q != 3) a[p][q+1] ^= 1;
    int m = 0;
    forn(i, 4) forn(j, 4) m = m*2 + a[i][j];
    return m;
}

void solve() {
    lq = 0, rq = 1;
    forn(i, 1<<16) d[i] = inf;
    d[m] = 0;
    q[0] = m;
    while (lq != rq) {
        int v = q[lq++];
        forn(i, 4) forn(j, 4) {
            int t = move(v, i, j);
            if (d[t] == inf) {
                d[t] = d[v] + 1;
                q[rq++] = t;
            }
        }
    }
    int res = min(d[0], d[(1<<16)-1]);
    if (res == inf) cout << "Impossible" << endl;
    else cout << res << endl;
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
