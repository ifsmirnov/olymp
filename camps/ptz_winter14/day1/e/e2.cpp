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
const int maxn = 100500;

ostream& operator<<(ostream& out, const vi& a) {
    forn(i, a.size()) out << a[i] << " ";
    return out;
}

int n;
map<vi, int> d;
vi res;

vi s4(vi a, int k) {
    assert(k + 3 < (int)a.size());
    swap(a[k], a[(k+3)%a.size()]);
    swap(a[(k+1)%a.size()], a[(k+2)%a.size()]);
    return a;

}
vi id(int n) {
    vi a(n);
    forn(i, n) a[i] = i;
    return a;
}

void dfs(const vi &a) {
    vi b;
    forn(i, a.size()-3) {
        b = s4(a, i);
        if (!d.count(b)) {
            d[b] = i;
            dfs(b);
        }
    }
}

void precalc() {
    d[id(6)] = -1;
    dfs(id(6));
}

void solve(vi t) {
    assert(d.count(t));
    while (d[t] != -1) {
        res.pb(d[t]);
        t = s4(t, d[t]);
        assert(d.count(t));
    }
}

int a[maxn];
void s4(int k) {
    swap(a[k], a[k+3]);
    swap(a[k+1], a[k+2]);
}

bool scan() {
    if (scanf("%d", &n) != 1) {
        return false;
    }
    n *= 2;
    forn(i, n) scanf("%d", &a[i]), --a[i];
    return true;
}

bool par() {
    int t = 0;
    forn(i, n) forn(j, i) if (a[i]<a[j]) ++t;
    return t%2 == 0;
}

void solve() {
    res.clear();
    if (n == 4) {
        while (a[0] != 0) {
            res.pb(-1);
            rotate(a, a+1, a+n);
        }
        if (a[1] != 1) {
            res.pb(0);
            s4(0);
            res.pb(-1);
            res.pb(-1);
            res.pb(-1);
        }
    } else {
        int _n = n;
        if (!par()) {
            res.pb(-1);
            rotate(a, a+1, a+n);
        }
        while (n > 6) {
            int j = n-1;
            int i = 0;
            while (a[i] != n-1) ++i;
            if (i == j) {
                --n;
                continue;
            } else if (i == j-1) {
                res.pb(j-4);
                s4(j-4);
                i = j-4;
            } else if (i == j-2) {
                res.pb(j-4);
                s4(j-4);
                i = j-3;
            } else if (i == 0) {
                res.pb(0);
                s4(0);
                i = 3;
            }
            while (i < j-3) {
                res.pb(i-1);
                s4(i-1);
                ++i;
            }
            assert(i == j-3);
            res.pb(i);
            s4(i);
            assert(a[n-1] == n-1);
            --n;
        }
        for (int i = 6; i < _n; ++i) assert(a[i] == i);
        solve(vi(a, a+6));
    }
    printf("%d\n", (int)res.size());
    forn(i, res.size()) {
        if (res[i] == -1) {
            printf("%d %d\n", 2, 1);
        } else {
            printf("%d %d\n", 1, res[i]+1);
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
#endif

    precalc();
    while (scan()) {
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
