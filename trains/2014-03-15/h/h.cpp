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
const int maxn = 250;

int n, K, m;
unsigned e[maxn][maxn/32];
unsigned a[maxn][maxn/32];

void floyd(bool pr) {
    forn(i, n) forn(j, K) a[i][j] = e[i][j];
    forn(k, n) forn(i, n) if (a[i][k>>5]&(1u<<(k&31)))
        forn(j, K) a[i][j] |= a[k][j];
    int cnt = 0;
    forn(i, n) forn(j, K) cnt += __builtin_popcount(a[i][j]);
    if (pr) printf("%d\n", cnt);
}
bool adj(int i, int j) {
    return a[i][j>>5]&(1u<<(j&31));
}

char s[10];
void solve() {
    scanf("%d%d", &n, &m);
    K = (n+31)/32;
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u; --v;
        e[u][v>>5] |= 1u<<(v&31);
    }
    floyd(true);
    int q;
    scanf("%d", &q);
    forn(i, q) {
        int u, v;
        scanf("%s%d%d", s, &u, &v);
        --u; --v;
        if (s[0] == '+' || s[0] == '-') {
            e[u][v>>5] ^= 1u<<(v&31);
            floyd(true);
        }
        else printf("%s\n", adj(u, v) ? "YES" : "NO");
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    freopen("settling.in", "r", stdin);
    freopen("settling.out", "w", stdout);

    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
