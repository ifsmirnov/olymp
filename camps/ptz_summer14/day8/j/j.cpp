#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <cstring>
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
const int maxn = 100500;

int n;
int lp[30];
char s[maxn];
int nxt[maxn][26];

void scan() {
    scanf("%s", s);
    n = strlen(s);
}

void genlp() {
    forn(i, 26) lp[i] = n;
    ford(i, n) {
        lp[s[i]-'a'] = i;
        forn(j, 26) nxt[i][j] = lp[j];
    }
}

pii t[28];
map<int, int> res;
void solve() {
    genlp();
    res.clear();
    forn(i, n) {
        forn(j, 26) t[j] = mp(nxt[i][j], j);
        t[26] = mp(n, 0);
        sort(t, t+27);
        int mask = 0;
        forn(j, 27) {
            if (t[j].fi != i) res[mask] = max(res[mask], t[j].fi - i);
            mask |= 1<<t[j].se;
            if (t[j].fi == n) break;
        }
    }

    i64 s = 0;
    for (auto t: res) {
//         cout << t.fi << ": " << t.se << endl;
        s += __builtin_popcount(t.fi) * t.se;
    }
    printf("%d %lld\n", (int)res.size(), s);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("jingles.in", "r", stdin);
    freopen("jingles.out", "w", stdout);

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
