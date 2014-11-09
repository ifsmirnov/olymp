#include <unordered_map>
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
    vector<vi> a;
    int n;
    int p;
    Fenwick() {}
    void setSize(int n) {
        this->n = n;
        a.resize(n);
    }
    int get(int d, int x) const {
        if (d >= n) return 0;
        return lower_bound(all(a[d]), x) - a[d].begin();
    }
    void add(int x, int d) {
        assert(d < n);
        ++p;
        a[d].pb(x);
        if (p == n) {
            forn(i, n) {
                sort(all(a[i]));
            }
        }
    }
};

vi e[maxn];
int s[maxn];
int h[maxn];
int closed[maxn];
int vpos;

void dfs(int v, int anc, int n, int& root, int *vertices) {
    vertices[vpos++] = v;
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
    int *vertices;
    int *height;
    int *component;
    Subtree ** children;
    Fenwick fromRoot;
    Fenwick fromCenter;
    Fenwick *parent;

    Subtree(int n, int root, Fenwick *parent = NULL) : n(n), root(root), parent(parent) {
        vertices = new int[n];
        height = new int[n];
        component = new int[n];
        center = -1;
        h[root] = 0;
        vpos = 0;
        dfs(root, -1, n, center, vertices);
        closed[center] = 1;

        sort(vertices, vertices + n);

        forn(i, n) {
            height[i] = h[vertices[i]];
        }
        component[verticePos(center)] = -1;
        fromRoot.setSize(*max_element(height, height + n) + 1);

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
            children = new Subtree*[candidates.size()];
            forn(i, candidates.size()) {
                int to = candidates[i].fi;
                int size = candidates[i].se;
                children[i] = new Subtree(size, to, &fromCenter);
                maxHeight = max(
                        maxHeight,
                        *max_element(
                                children[i]->height,
                                children[i]->height + size) + 1);

                forn(j, size) {
                    int v = children[i]->vertices[j];
                    component[verticePos(v)] = i;
                }
            }
            fromCenter.setSize(maxHeight + 1);
        }
    }

    int get(int v, int d, int k) {
        if (n == 1) {
            return fromRoot.get(d, k);
        }
        if (v == center) {
            return fromCenter.get(d, k);
        }

        int res = 0;

        int id = verticePos(v);
        int comp = component[id];
        int residualHeight = d - (children[comp]->verticeHeight(v) + 1);

        if (residualHeight >= 0) {
            res += fromCenter.get(residualHeight, k);
        }
        if (residualHeight > 0) {
            res -= children[comp]->fromRoot.get(residualHeight - 1, k);
        }

        return res + children[comp]->get(v, d, k);
    }

    int verticeHeight(int v) const {
        return height[verticePos(v)];
    }

    int verticePos(int v) const {
//         return vertexIndex.at(v);
        return lower_bound(vertices, vertices + n, v) - vertices;
    }

    void update(int v) {
        int id = verticePos(v);
        fromRoot.add(v, height[id]);
        if (parent) {
            parent->add(v, height[id] + 1);
        }
        if (v == center) {
            if (n != 1)
                fromCenter.add(v, 0);
        } else {
            children[component[id]]->update(v);
        }
    }

};

int n, q;
Subtree *t;
int w[maxn];

void scan() {
    scanf("%d", &n);
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
        t->update(i);

    int M;
    scanf("%d", &M);
    forn(i, M) {
        int v, d, k;
        scanf("%d%d%d", &v, &d, &k);
        --v;
        if (t->get(v, d, n) < k) {
            assert(false);
        }
        int l = 0, r = n, m;
        while (r-l>1) {
            m = (r+l)/2;
            if (t->get(v, d, m) >= k) {
                r = m;
            } else {
                l = m;
            }
        }
        printf("%d\n", r);
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
