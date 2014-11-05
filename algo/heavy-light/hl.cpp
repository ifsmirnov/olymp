#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
const int maxn = 100500;
const int inf = 1e9+100500;

const int sz = 1<<18;
int rmq[sz*2];
void upd(int i, int x) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) {
        rmq[i] = max(rmq[i*2], rmq[i*2+1]);
    }
}
int get(int l, int r) {
    l += sz;
    r += sz;
    int mn = -inf;
    while (l < r) {
        if (l%2 == 1) mn = max(mn, rmq[l]);
        if (r%2 == 0) mn = max(mn, rmq[r]);
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) mn = max(mn, rmq[l]);
    return mn;
}
int lfpos = 0;

int n;
vector<int> e[maxn];
int s[maxn], root[maxn], h[maxn], lpos[maxn], p[maxn];

int val[maxn];

void dfs1(int v, int anc) {
    p[v] = anc;
    s[v] = 1;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (to == anc) {
            swap(e[v][i], e[v].back());
            e[v].pop_back();
            --i;
            continue;
        }
        h[to] = h[v] + 1;
        dfs1(to, v);
        s[v] += s[to];
    }
}

void dfs2(int v, int cur_root) {
    root[v] = cur_root;
    if (e[v].empty()) {
        lpos[root[v]] = lfpos;
        lfpos += h[v] - h[root[v]] + 1;
        return;
    }

    int max_s = 0;
    int max_s_index = 0;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (s[to] > max_s) {
            max_s = s[to];
            max_s_index = i;
        }
    }

    forn(i, e[v].size()) {
        if (i == max_s_index) dfs2(e[v][i], cur_root);
        else dfs2(e[v][i], e[v][i]);
    }
}

void upd_hl(int v, int x) {
    upd(lpos[root[v]] + h[v] - h[root[v]], x);
}

int get_hl(int u, int v) {
    int mn = -inf;
    while (root[u] != root[v]) {
        if (h[root[u]] > h[root[v]]) {
            swap(u, v);
        }

        mn = max(mn, get(lpos[root[v]], lpos[root[v]] + h[v] - h[root[v]]));
        v = p[root[v]];
    }
    if (h[u] > h[v]) swap(u, v);
    mn = max(mn, get(lpos[root[u]] + h[u] - h[root[u]], lpos[root[v]] + h[v] - h[root[v]]));
    return mn;
}

void scan() {
    scanf("%d", &n);
    forn(i, n-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].push_back(--v);
        e[v].push_back(u);
    }
}

void solve() {
    dfs1(0, -1);
    dfs2(0, -1);
    forn(i, n) upd_hl(i, val[i]);
    int m;
    scanf("%d", &m);
    int u, v;
    char t[5];
    forn(i, m) {
        scanf("%s%d%d", t, &u, &v);
        if (t[0] == 'I') {
            val[--u] += v;
            upd_hl(u, val[u]);
        } else {
            printf("%d\n", get_hl(u-1, v-1));
        }
    }
}

int main() {
//     freopen("input.txt", "r", stdin);
    scan();
    solve();
}
