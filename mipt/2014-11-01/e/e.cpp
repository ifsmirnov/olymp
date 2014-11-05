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
typedef pair<i64, i64> pii;
typedef unsigned long long u64;
const int inf = 1e9+100500;
const int maxn = 200500;

int n, T;
i64 w[maxn];
vi e[maxn];

void scan() {
    scanf("%d%d", &n, &T); --T;
    forn(i, n) scanf("%lld", &w[i]);
    forn(i, n+1) e[i].clear();
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
    e[T].pb(n);
    e[n].pb(T);
    w[n] = 200000000000000ll;
    ++n;
}

struct mset {
    set<pii> *a;
};

mset merge(mset A, mset B) {
    // b -> a, b is smaller
    if (A.a->size() < B.a->size()) {
        swap(A, B);
    }

    set<pii> &a = *A.a;
    set<pii> &b = *B.a;

    for (auto elem : b) {
        i64 add = 0;
        auto it = a.upper_bound(mp(elem.fi, 1000000000000000000ll));
        if (it != a.begin()) {
            --it;
            if (it->se >= elem.fi) {
                add += elem.se - elem.fi;
            } else {
                it = a.insert(elem).fi;
            }
        }
        auto it1 = it;
        ++it1;
        while (it1 != a.end() && it1->fi <= it->se + add) {
            add += it1->se - it1->fi;
            ++it1;
        }
        i64 nse = it->se + add;
        i64 nfi = it->fi;
        a.erase(it, it1);
        a.insert(mp(nfi, nse));
    }

    return A;
}

void out(mset a) {
    for (auto x : *a.a) {
        cout << -x.fi << " " << x.se << "    ";
    }
    cout << endl;
}

mset eat(mset A, i64 val) {
//     cerr <<" begin eat" << endl;
    set<pii> &a = *A.a;
    auto it = a.begin();
    while (it != a.end() && val < 0) {
        if (-val + it->fi < it->se) {
            i64 nfi = it->fi - val;
            i64 nse = it->se;
            ++it;
            a.erase(a.begin(), it);
            a.insert(mp(nfi, nse));
            val = 0;
            break;
        }
        val += it->se - it->fi;
    }
    if (val < 0) {
        a.clear();
    }
//     cerr << "end eat" << endl;

    return A;
}

mset dfs(int v, int anc) {
//     cout << "go " << v << endl;
    mset cur;
    cur.a = new set<pii>;
    if (w[v] > 0) {
        cur.a->insert(mp(0, w[v]));
    }

    forn(i, e[v].size()) {
        int to = e[v][i];
        if (to == anc) continue;
        mset nxt = dfs(to, v);
        cur = merge(cur, nxt);
    }

    if (w[v] < 0 && !cur.a->empty()) {
        cur = eat(cur, w[v]);
    }

    if (!cur.a->empty() && cur.a->begin()->fi >= cur.a->begin()->se) {
        cur.a->clear();
    }

//     cout << v << endl;
//     out(cur);

    return cur;
}


void solve() {
    mset a = dfs(0, -1);
    if (!a.a->empty() && a.a->begin()->fi == 0 && a.a->begin()->se > 100000000000000ll) {
        printf("escaped\n");
    } else {
        printf("trapped\n");
    }
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t;
    scanf("%d", &t);
    forn(i, t) {
        scan();
        solve();
    }


#ifdef HOME
//     cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
