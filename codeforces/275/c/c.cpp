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
const int maxn = 55;

i64 cmn[maxn][maxn]; // str_idx, char
i64 d[1<<20];
double p[1<<20];
int n, m;
char s[maxn][maxn];

void scan() {
//     n = 50;
//     m = 20;
//     forn(i, n) forn(j, m) s[i][j] = rand()%2+'a';
    scanf("%d", &n);
    forn(i, n) scanf("%s", s[i]);
    while (s[0][m]) ++m;
}

void build_del() {
    forn(i, n) forn(j, n) forn(k, m) if (i != j && s[i][k] == s[j][k]) {
        cmn[i][k] |= 1ll<<j;
    }
}

double solve(int s) {
//     cout << "solve " << s << endl;
    forn(i, 1<<m) {
        d[i] = (1u<<n)-1;
        d[i] ^= 1u<<s;
        p[i] = 0;
    }
    p[0] = 1;
    double res = 0;
    forn(mask, 1<<m) {
        int pc = __builtin_popcount(mask);
        if (d[mask] == 0) {
            res += p[mask] * pc;
        } else {
            forn(i, m) if (!(mask&(1<<m))) {
                d[mask^(1<<i)] = d[mask] & cmn[s][i];
                p[mask^(1<<i)] += p[mask] / (m - pc);
            }
        }
    }
    return res;
}

void solve() {
    if (n == 0) {
        cout << "0" << endl;
        return;
    }
    double res = 0;
    forn(i, n) res += solve(i);
    cout.precision(10);
    cout << fixed;
    cout << res/n << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    build_del();
    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
