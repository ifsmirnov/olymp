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
#include <tuple>
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
const int maxn = 2050;

int p[maxn], sz[maxn];
void init() { forn(i, maxn) p[i] = i, sz[i] = 1; }
int get(int x) { return p[x] == x ? x : (p[x] = get(p[x])); }
void unite(int x, int y) {
    assert(p[x] == x);
    assert(p[y] == y);
    p[y] = x;
    sz[x] += sz[y];
}

int n;
int d[maxn][maxn];
int ltime[maxn];
int moscow_time = 0;
int realnum[maxn];
int curnum;

priority_queue<tuple<double, pii, int>> q;

void join(double val, int x, int y, int tm) {
    if (tm < max(ltime[x], ltime[y])) {
        return;
    }
    ltime[x] = ltime[y] = ++moscow_time;

    forn(i, n) {
        d[x][i] += d[y][i];
        d[i][x] += d[i][y];
    }
    unite(x, y);
//     cout << "sz[" << x << "] = " << sz[x] << endl;
    forn(i, n) if (i != x && i == p[i]) {
        q.push(make_tuple(
            -(double)d[x][i] / (sz[x] * sz[i]),
            mp(x, i),
            moscow_time
        ));
    }

    printf("%d %d %.10lf\n", realnum[x], realnum[y], val);
    realnum[x] = ++curnum;

//     forn(i, n) {
//         forn(j, n) {
//             cout << d[i][j] << " ";
//         }
//         cout << endl;
//     }
//     cout << endl;
}

void solve() {
    forn(i, n) forn(j, i) {
        q.push(make_tuple(
            -(double)d[i][j] / (1 * 1),
            mp(i, j),
            0
        ));
    }
    forn(i, n) {
        realnum[i] = ++curnum;
    }

    while (curnum < 2*n-1) {
        assert(!q.empty());
        auto t = q.top();
        q.pop();
        join(-get<0>(t), get<1>(t).fi, get<1>(t).se, get<2>(t));
    }
}

char buf[maxn];
void scan() {
//     n = 2000;
//     forn(i, n) forn(j, n) d[i][j] = rand()%10;
    scanf("%d", &n);
    forn(i, n) {
        scanf("%s", buf);
        forn(j, n) {
            d[i][j] = buf[j] - '0';
        }
    }
}

int main() {
// #ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
// #endif

    init();
    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
