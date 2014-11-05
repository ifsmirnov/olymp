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
const int maxn = 100500;

int n;

int a[maxn], b[maxn];

set<pii> f;

vi res;

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d%d", &a[i], &b[i]);
}

void solve() {
    forn(i, n) {
        f.insert(mp(a[i], i));
    }

    int pos = 1e9;
    while (!f.empty()) {
        auto it = f.upper_bound(mp(pos, inf));
        if (it == f.begin()) {
            printf("No\n");
            return;
        }
        pii t = *--it;
        f.erase(t);
        res.pb(t.se);
        pos = b[t.se] - 1;
    }
    printf("Yes\n");
    forn(i, n) printf("%d ", res[i] + 1);
    printf("\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
