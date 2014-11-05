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
const int maxn = 1000500;
const int mod = 1000003;
const int phi = mod - 1;
int madd(int x, int y) { return (x + y) % phi; }
int msub(int x, int y) { return ((x - y + phi) % phi + phi) % phi; }

int ppow[maxn];
int rpow[maxn];

void proot() {
    int t = 1;
    forn(i, mod) ppow[i] = rpow[i] = -1;
    forn(i, phi) {
        ppow[i] = t;
        assert(rpow[t] == -1);
        rpow[t] = i;
        t = t * 2 % mod;
    }
}

int n, k;
vi e[maxn];
int lbl[maxn];
int cura, curb;
void relax(int a, int b) {
    if (a > b) swap(a, b);
    if (a < cura || (a == cura && b < curb)) {
        cura = a;
        curb = b;
    }
}

void put(map<int, int>& a, int key, int value) {
    if (a.count(key)) {
        a[key] = min(a[key], value);
    } else {
        a[key] = value;
    }
}

struct Info {
    map<int, int>* a;
    int add;
    Info(){}
    Info(map<int, int>* a, int add) : a(a), add(add) {}
};

Info merge(Info a, Info b, int root) {
    if (a.a->size() < b.a->size()) {
        swap(a, b);
    }
    // now b < a

    // 1) long for an answer
    for (auto it: *b.a) {
        int x = msub(k, it.fi + root + a.add + b.add);
        if (a.a->count(x)) {
            relax(it.se, a.a->at(x));
        }
    }

    // 2) merge
    int add = msub(b.add, a.add);
    for (auto it: *b.a) {
        put(*a.a, madd(it.fi, add), it.se);
    }

    return a;
}

Info dfs(int v, int anc) {
    forn(i, e[v].size()) {
        if (e[v][i] == anc) {
            swap(e[v][i], e[v].back());
            e[v].pop_back();
            break;
        }
    }
    Info t(new map<int, int>, 0);
    put(*t.a, 0, v);
    forn(i, e[v].size()) {
        t = merge(t, dfs(e[v][i], v), lbl[v]);
    }
    t.add = madd(t.add, lbl[v]);
    return t;
}

bool scan() {
    if (scanf("%d%d", &n, &k) != 2) {
        return false;
    }
    k = rpow[k];
    forn(i, n) e[i].clear();
    forn(i, n) {
        int x;
        scanf("%d", &x);
        lbl[i] = rpow[x];
    }
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
    return true;
}

void solve() {
    cura = curb = n;
    dfs(0, -1);
    if (cura == n) {
        cout << "No solution" << endl;
    } else {
        cout << cura+1 << " " << curb+1 << endl;
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    proot();
    while (scan()) {
        solve();
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
