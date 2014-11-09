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
int d[maxn];
vi e[maxn];
int p[maxn], k;

vector<pii> es;

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d", &d[i]);
        e[d[i]].pb(i);
    }
}

void fail() {
    printf("Epic fail\n");
    exit(0);
}

void solve() {
    int a = max_element(d, d+n) - d;
    k = d[a];
    d[a] = -1;
    e[k].erase(find(all(e[k]), a));

    int b = max_element(d, d+n) - d;
    if (d[b] != k) {
        fail();
    }
    d[b] = -1;
    e[k].erase(find(all(e[k]), b));

    p[0] = a;
    p[k] = b;
    for (int i = 1; i < k; ++i) {
        int r = max(i, k-i);
        if (e[r].empty()) {
            fail();
        }
        int v = e[r].back();
        e[r].pop_back();
        p[i] = v;
        es.pb(mp(p[i-1], p[i]));
    }
    es.pb(mp(p[k-1], p[k]));

    int lim = (k+1) / 2 + 1;
    for (int s = 0; s <= k; ++s) {
        if (e[s].empty()) {
            continue;
        }
        if (k == 1) {
            fail();
        }
        if (s < lim) {
            fail();
        }
        int pos = k - s + 1;
        if (pos < 0 || pos > k) {
            fail();
        }
        if (max(pos, k - pos) + 1 != s) {
            fail();
        }
        for (auto to : e[s]) {
            es.pb(mp(to, p[pos]));
        }
    }

    printf("I got it\n");
    for (auto e: es) {
        printf("%d %d\n", e.fi+1, e.se+1);
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
