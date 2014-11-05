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

struct Fenwick {
    int *a;
    int n;
    Fenwick() {}
    void setSize(int n) {
        this->n = n;
        a = new int[n];
        forn(i, n) a[i] = 0;
    }
    int get(int i) const {
        i = min(i, n - 1);
        int res = 0;
        for (; i >= 0; i = (i&(i+1))-1)
            res += a[i];
        return res;
    }
    void update(int i, int x) {
        for (; i < n; i |= (i+1))
            a[i] += x;
    }
    void print() {
        volatile int p;
        int d = 0;
        forn(i, n) {
            int t = get(i);
            cout << t - d << " ";
            d = t;
        }
        cout << endl;
    }
};

vi e[maxn];
int s[maxn];
int h[maxn];
int closed[maxn];

void dfs(int v, int anc, int n, int& root, vector<int>& vertices) {
    vertices.pb(v);
    s[v] = 1;
    int max_subtree = 0;

    for (auto to: e[v]) {
        if (closed[to] || to == anc) continue;

        h[to] = h[v] + 1;
        dfs(to, v, n, root, vertices);
        s[v] += s[to];
        max_subtree = max(max_subtree, s[to]);
    }

    if (root == -1 && max(max_subtree, n - s[v]) <= n / 2) {
        root = v;
    }
}

struct Subtree {
    int n;
    int root;
    int center;
    vector<int> vertices;
    vector<int> height;
    vector<int> component;
    vector<Subtree*> children;
    Fenwick fromRoot;
    Fenwick fromCenter;
    Fenwick *parent;

    Subtree(int n, int root, Fenwick *parent = NULL) : n(n), root(root), parent(parent) {
        center = -1;
        h[root] = 0;
        dfs(root, -1, n, center, vertices);
        closed[center] = 1;

//         cout << "build subtree: ";
//         for (auto v: vertices) cout << v << " ";
//         cout << endl;

//         assert(center != -1);
//         assert(n == (int)vertices.size());

        sort(all(vertices));
        height.resize(n);
        component.resize(n);

        forn(i, n) {
            height[i] = h[vertices[i]];
        }
        component[verticePos(center)] = -1;
        fromRoot.setSize(*max_element(all(height)) + 1);

        if (n > 1) {
            vector<pii> candidates; // <index, size>
            for (auto to: e[center]) {
                if (closed[to]) continue;
                int size;
                if (h[to] > h[center])
                    size = s[to];
                else
                    size = n - s[center];
                candidates.pb(mp(to, size));
            }

            int maxHeight = 0;
            children.resize(candidates.size());
            forn(i, candidates.size()) {
                int to = candidates[i].fi;
                int size = candidates[i].se;
                children[i] = new Subtree(size, to, &fromCenter);
                maxHeight = max(
                        maxHeight,
                        *max_element(all(children[i]->height)) + 1);

                for (auto v: children[i]->vertices)
                    component[verticePos(v)] = i;
            }
            fromCenter.setSize(maxHeight + 1);
        }
    }

    void update(int v, int delta) {
        int id = verticePos(v);
        fromRoot.update(height[id], delta);
        if (parent) {
            parent->update(height[id] + 1, delta);
        }
        if (v == center) {
            if (n != 1)
                fromCenter.update(0, delta);
        } else {
            children[component[id]]->update(v, delta);
        }
    }

    int get(int v, int d) {
        if (n == 1) {
            return fromRoot.get(0);
        }
        if (v == center) {
            return fromCenter.get(d);
        }

        int res = 0;

        int id = verticePos(v);
        int comp = component[id];
        int residualHeight = d - (children[comp]->verticeHeight(v) + 1);

        if (residualHeight >= 0) {
            res += fromCenter.get(residualHeight);
        }
        if (residualHeight > 0) {
            res -= children[comp]->fromRoot.get(residualHeight - 1);
        }

        return res + children[comp]->get(v, d);
    }

    int verticeHeight(int v) const {
        return height[verticePos(v)];
    }

    int verticePos(int v) const {
        return lower_bound(all(vertices), v) - vertices.begin();
    }
};

int n, q;
Subtree *t;
int w[maxn];

void scan() {
    scanf("%d%d", &n, &q);
    forn(i, n) scanf("%d", &w[i]);
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
         --u, --v;
        e[u].pb(v);
        e[v].pb(u);
    }
}

int solve_dfs(int v, int d, int anc = -1) {
    int res = w[v];
    if (d == 0) return res;
    for (auto to: e[v]) {
        if (to == anc) continue;
        res += solve_dfs(to, d - 1, v);
    }
    return res;
}

void solve() {
    t = new Subtree(n, 0);
    forn(i, n)
        t->update(i, w[i]);
    char tt[2];
    forn(i, q) {
        int a, b;
        scanf("%s%d%d", tt, &a, &b);
        --a;
        if (tt[0] == '!') {
            t->update(a, b - w[a]);
            w[a] = b;
        } else {
            int res = t->get(a, b);
//             int correct = solve_dfs(a, b);
//             assert(res == correct);
            printf("%d\n", res);
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("/dev/null", "w", stdout);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
