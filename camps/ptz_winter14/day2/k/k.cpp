//zzyzx
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
const int maxn = 200500;

struct TData {
    int lm, rm, dif;
    
    TData(int lm = -1, int rm = -1, int dif = -1)
        : lm(lm)
        , rm(rm)
        , dif(dif)
    {
    }
    
    TData operator+(const TData &d) const {
        if (lm == -1) {
            return d;
        }
        if (d.lm == -1){
            return *this;
        }
        return TData(lm, d.rm, dif + d.dif + (rm == d.lm ? 0 : 1));
    }
    
    TData reverse() const {
        return TData(rm, lm, dif);
    }
};

struct TNode {
    int L, R;
    int lc, rc;
    int val;
    TData data;
    
    TNode(int L = 0, int R = 0)
        : L(L)
        , R(R)
        , lc(0)
        , rc(0)
        , val(-1)
        , data()
    {
    }
};

TNode tree[maxn * 10];
int tc = 0;

int build(int L, int R) {
    int node = tc++;
    tree[node] = TNode(L, R);
    if (R - L > 1) {
        int M = (L + R) / 2;
        tree[node].lc = build(L, M);
        tree[node].rc = build(M, R);
    }
    return node;
}

void push(int node) {
    //int left = tree[node].lc, right = tree[node].rc;
        
    if (tree[node].val != -1) {
        int v = tree[node].val;
        tree[node].val = -1;
        tree[node].data.lm = tree[node].data.rm = v;
        tree[node].data.dif = 0;
        if (tree[node].R - tree[node].L > 1) {
            tree[tree[node].lc].val = tree[tree[node].rc].val = v;
        }
    }
}

void combine(int node) {
    int left = tree[node].lc, right = tree[node].rc;
    tree[node].data = tree[left].data + tree[right].data;
}

TData segdif(int node, int L, int R) {
    push(node);
    if (tree[node].L >= R || L >= tree[node].R) {
        return TData();
    }
    if (L <= tree[node].L && tree[node].R <= R) {
        return tree[node].data;
    }
    return segdif(tree[node].lc, L, R) + segdif(tree[node].rc, L, R);
}

void assign(int node, int L, int R, int x) {
    push(node);
    if (tree[node].L >= R || L >= tree[node].R) {
        return;
    }
    if (L <= tree[node].L && tree[node].R <= R) {
        tree[node].val = x;
        push(node);
        return;
    }
    assign(tree[node].lc, L, R, x);
    assign(tree[node].rc, L, R, x);
    combine(node);
}

vi e[maxn];
int par[maxn], d[maxn], w[maxn];
int root[maxn], len[maxn], tr[maxn], sky[maxn];

void dfs_build(int v, int p) {
    par[v] = p;
    d[v] = (p == -1 ? 0 : d[p] + 1);
    w[v] = 1;
    root[v] = v;
    len[v] = 1;
    sky[v] = par[v];
    forn(i, e[v].size()) {
        int u = e[v][i];
        if (u == p) {
            continue;
        }
        dfs_build(u, v);
        w[v] += w[u];
    }
    forn(i, e[v].size()) {
        int u = e[v][i];
        if (u == p) {
            continue;
        }
        if (w[u] * 2 >= w[v]) {
            root[v] = root[u];
            ++len[root[v]];
            sky[root[v]] = par[v];
        }
    }
}

int N;
const int maxk = 19;
int up[maxk + 1][maxn];

void build_up() {
    forn(i, N) {
        up[0][i] = par[i];
    }
    forn(i, maxk) {
        forn(j, N) {
            up[i + 1][j] = up[i][j] == -1 ? -1 : up[i][up[i][j]];
        }
    }
}

int get_up(int v, int x) {
    for (int k = maxk - 1; k >= 0; --k) {
        if ((1 << k) <= x) {
            x -= 1 << k;
            v = up[k][v];
        }
    }
    return v;
}

int lca(int u, int v) {
    if (d[u] < d[v]) {
        swap(u, v);
    }
    u = get_up(u, d[u] - d[v]);
    if (u == v) {
        return v;
    }
    for (int k = maxk - 1; k >= 0; --k) {
        if (up[k][v] != up[k][u]) {
            v = up[k][v];
            u = up[k][u];
        }
    }
    return par[v];
}

void assign_up(int v, int x, int y) {
    int r = root[v];
    int p = d[r] - d[v];
    if (p + x <= len[r]) {
        assign(tr[r], p, p + x, y);
    } else {
        assign(tr[r], p, len[r], y);
        assign_up(sky[r], x - (len[r] - p), y);
    }
}

TData segdif_up(int v, int x) {
    int r = root[v];
    int p = d[r] - d[v];
    if (p + x <= len[r]) {
        return segdif(tr[r], p, p + x);
    } else {
        return segdif(tr[r], p, len[r]) + segdif_up(sky[r], x - (len[r] - p));
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    
    scanf("%d", &N);
    forn(i, N - 1) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x; --y;
        e[x].pb(y);
        e[y].pb(x);
    }
    dfs_build(0, -1);
    forn(i, N) {
        if (root[i] == i) {
            tr[i] = build(0, len[i]);
        }
    }
    build_up();
    forn(i, N) {
        assign_up(i, 1, i);
    }
    /*forn(i, N) {
        printf("%d %d %d\n", par[i], d[i], w[i]);
    }*/
    int Q;
    scanf("%d", &Q);
    forn(q, Q) {
        int t, u, v;
        scanf("%d%d%d", &t, &u, &v);
        --u; --v;
        int w = lca(u, v);
        //printf("%d\n", w);
        if (t == 0) {
            int ans = (segdif_up(u, d[u] - d[w] + 1) + segdif_up(v, d[v] - d[w]).reverse()).dif;
            printf("%d\n", ans);
        } else {
            assign_up(u, d[u] - d[w] + 1, N + q);
            assign_up(v, d[v] - d[w], N + q);
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
