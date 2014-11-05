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

vi e[maxn];
int mt[maxn], b[maxn], fto[maxn], fv[maxn];
bool kuhn(int v) {
    if (b[v] || fv[v]) return false;
    b[v] = 1;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (!fto[to] && (mt[to] == -1 || kuhn(mt[to]))) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

vector<i64> factor(i64 n) {
    vector<i64> res;
    for (i64 i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            res.pb(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) res.pb(n);
    return res;
}

i64 A, B;
i64 prs[maxn];
vector<i64> fs[maxn];
i64 res[maxn];
int npr;
int n;
int prn(i64 pr) {
    return lower_bound(prs, prs+npr, pr) - prs;
}

bool matching(int n) {
    forn(i, npr) if (!fto[i]) mt[i] = -1;
    forn(i, n) {
        forn(j, n) b[j] = 0;
        if (!kuhn(i)) return false;
    }
    return true;
}

bool solve() {
    cin >> A >> B;
    if (B == 0) return false;

    npr = 0;
    for (i64 i = A; i <= B; ++i) {
        fs[i-A] = factor(i);
        for (auto j: fs[i-A]) prs[npr++] = j;
    }
    sort(prs, prs+npr);
    npr = unique(prs, prs+npr) - prs;
    n = B-A+1;

    forn(i, n) {
        e[n-i-1].clear();
        for (auto pr: fs[i]) {
            e[n-i-1].pb(prn(pr));
        }
    }
    forn(i, n) fv[i] = 0;
    forn(i, npr) fto[i] = 0;

    forn(num, n) {
        int idx = n-num-1;
        fv[idx] = true;
        bool ok = false;
        for (auto pr: fs[num]) {
            pr = prn(pr);
            if (!fto[pr]) {
                fto[pr] = true;
                mt[pr] = idx;
                if (matching(n-num-1)) {
                    res[num] = prs[pr];
                    ok = true;
                    break;
                }
                fto[pr] = false;
            }
        }
        if (!ok) cout << "not ok1@!@111!" << endl;
    }

    forn(i, n) {
        cout << res[i] << " \n"[i == n-1];
    }

    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    while (solve());

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
