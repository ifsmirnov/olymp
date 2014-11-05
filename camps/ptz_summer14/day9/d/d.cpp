#include <functional>
#include <algorithm>
#include <cstring>
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
const int mod = 1000000007;
int add(int x, int y) { return (x+y)%mod; }
const int maxn = 55;

int n, m;
char s[maxn], t[maxn];

int go(int k, const vector<pii> &a) {
    if (k == n+m) return 1;
    int res = 0;
    forn(d, 2) {
        vector<pii> b;
        for (auto p: a) {
            if (p.fi != n && s[p.fi] - '0' == d)
                b.pb(mp(p.fi+1, p.se));
            if (p.se != m && t[p.se] - '0' == d)
                b.pb(mp(p.fi, p.se+1));
        }
        if (!b.empty())
            res = add(res, go(k+1, b));
    }
    return res;
}

int d[maxn][maxn];

int depth;
int f(int i, int j, int k, int l) {
    if (i == k && j == l) return d[i][j];
    assert(i<=n&&j<=m&&k<=n&&l<=m);
    int res = 0;
    if (s[i] && s[i] == s[k]) res += f(i+1, j, k+1, l);
    if (t[j] && t[j] == s[k]) res += f(i, j+1, k+1, l);
    if (s[i] && s[i] == t[l]) res += f(i+1, j, k, l+1);
    if (t[j] && t[j] == t[l]) res += f(i, j+1, k, l+1);
    if (s[i] && s[i] != s[k] && s[i] != t[l]) res += d[i+1][j];
    if (t[j] && t[j] != s[k] && t[j] != t[l]) res += d[i][j+1];
    if (s[k] && s[k] != s[i] && s[k] != t[j]) res += d[k+1][l];
    if (t[l] && t[l] != s[i] && t[l] != t[j]) res += d[k][l+1];
    return res;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    long long seed;
    asm("rdtsc":"=A"(seed));
    srand(seed);

    n = 10;
    m = 10;
    forn(i, n) s[i] = rand()%2+'0';
    forn(i, m) t[i] = rand()%2+'0';
    forn(i, n) forn(j, m) d[i][j] = 1;
    forn(i, n-1) {
        forn(j, m-1) cout << f(i+1, j, i, j+1) << " " << flush;
        cout << endl;
    }

    int res = go(0, {{0,0}});
    cout << res << " " << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
