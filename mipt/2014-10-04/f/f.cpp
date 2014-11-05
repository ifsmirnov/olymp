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
typedef long long i64;
typedef unsigned long long u64;
const int inf = 1e9+100500;
typedef pair<i64, int> pii;

i64 gcd(i64 a, i64 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

string s;
string ns;

i64 gen(char c, int x) {
    i64 res = 0;
    forn(i, s.size()) {
        res *= 10;
        if (s[i] == c) res += x;
    }
    return res;
}

i64 solve() {
    cin >> s;
    ns = s;
    sort(all(ns));
    ns.erase(unique(all(ns)), ns.end());

    i64 res = 0;
    if (ns.size() != 10u) {
        forn(i, ns.size()) res = gcd(res, gen(ns[i], 1));
    }
    forn(i, ns.size()) forn(j, i) {
        res = gcd(res, abs( (gen(ns[i], 1) + gen(ns[j], 2)) - (gen(ns[i], 2) + gen(ns[j], 1)) ));
    }
    return res;
}

vector<pii> factor(i64 x) {
    vector<pii> res;
    if (x % 2 == 0) {
        res.pb(mp(2, 0));
        while (x%2 == 0) {
            res.back().se++;
            x /= 2;
        }
    }
    for (int n = 3; (i64)n*n <= x; n += 2) {
        if (x % n == 0) {
            res.pb(mp(n, 0));
            while (x % n == 0) {
                res.back().se++;
                x /= n;
            }
        }
    }
    if (x != 1) {
        res.pb(mp(x, 1));
    }
    return res;
}

i64 divs[1000000];
int nd;
vector<pii> fs;
void go(int pos, i64 x) {
    if (pos == (int)fs.size()) {
        divs[nd++] = x;
        return;
    }
    fore(i, 0, fs[pos].se) {
        go(pos+1, x);
        x *= fs[pos].fi;
    }
}

void gen_divs(i64 x) {
    fs = factor(x);
    nd = 0;
    go(0, 1);
    sort(divs, divs + nd);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t;
    cin >> t;
    forn(i, t) {
        i64 x = solve();
//         i64 x = 9999991ll * 9999991ll;
        gen_divs(x);
        printf("Case %d:", i+1);
        forn(j, nd) {
            printf(" %lld", divs[j]);
        }
        printf("\n");
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
