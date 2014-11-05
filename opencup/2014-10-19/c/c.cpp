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

int n, m;
vi e[maxn];
int c[maxn];
int inq[maxn];
queue<int> q;
int cc[3];

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
}

void relax(int v) {
    inq[v] = false;
    forn(i, 3) cc[i] = 0;
    for (auto to : e[v]) {
        cc[c[to]]++;
    }
    if (cc[c[v]] <= 1) {
        return;
    }
    int nc = min_element(cc, cc+3) - cc;
    c[v] = nc;
    assert(cc[nc] <= 1);
    for (auto to : e[v]) {
        if (c[to] == nc) {
            if (!inq[to]) {
                inq[to] = 1;
                q.push(to);
            }
        }
    }
}

void solve() {
    forn(i, n) {
        c[i] = rand()%3;
        inq[i] = 1;
        q.push(i);
    }
    int iter = 0;
    while (!q.empty()) {
        ++iter;
        relax(q.front());
        q.pop();
    }
//     cerr << "iter = " << iter << endl;
    forn(i, n) {
        printf("%d%c", c[i]+1, " \n"[i == n-1]);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("coloring.in", "r", stdin);
    freopen("coloring.out", "w", stdout);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
