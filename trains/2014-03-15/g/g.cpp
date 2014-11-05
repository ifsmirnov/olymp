//1:41
#include <iostream>
#include <queue>
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

int n;
int t[maxn], r[maxn];
pii a[maxn];
i64 res;
priority_queue<int, vi, greater<int> > q;

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d%d", &a[i].fi, &a[i].se);
    sort(a, a+n);
    forn(i, n) t[i] = a[i].fi, r[i] = a[i].se;
}

void solve() {
    i64 ct = 0;
    int ptr = 0;
    while (ptr < n || !q.empty()) {
        int md = 1000000500;
        if (!q.empty()) md = min(md, q.top());
        if (ptr < n) md = min(md, (int)(t[ptr] - ct));

        ct += md;
        if (!q.empty()) {
            int x = q.top() - md;
            q.pop();
            if (x) q.push(x);
            else res += ct;
        }
        while (ptr < n && t[ptr] == ct) {
            q.push(r[ptr++]);
        }
    }
    cout << res << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("pulp.in", "r", stdin);
    freopen("pulp.out", "w", stdout);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
