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
const int maxn = 500500;

int N;
vi e[maxn];
int a[maxn], d[maxn], par[maxn], out[maxn];
int val[maxn];

void dfs(int v, int p) {
    d[v] = (p == -1 ? 0 : d[p] + 1);
    par[v] = p;
    val[v] = a[v] + d[v];
    if (p != -1) {
        val[v] = max(val[v], val[p]);
    }
    forn(i, e[v].size()) {
        int u = e[v][i];
        if (u == p) {
            continue;
        }
        ++out[v];
        dfs(u, v);
    }
}

struct TNode {
    int L, R;
    int lc, rc;
    int key;
    
    TNode(int L = 0, int R = 0)
        : L(L)
        , R(R)
        , lc(-1)
        , rc(-1)
        , key(L)
    {
    }
};

TNode tree[3 * maxn];
int tc;

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

const int sz = 1<<20;
int rmq[sz*2];
void upd(int i, int x) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) {
        rmq[i] = max(rmq[i*2+1], rmq[i*2]);
    }
}
int get(int l, int r) {
    --r;
    if (l >= sz) return -1;
    if (l > r) return -1;
    r = min(r, sz-1);
    l = min(l, sz-1);
    l += sz; r += sz;
    int mx = -1;
    while (l < r) {
        if (l%2 == 1) mx = max(mx, rmq[l]);
        if (r%2 == 0) mx = max(mx, rmq[r]);
        l = (l+1)/2;
        r = (r-1)/2;
    }  
    if (l == r) mx = max(mx, rmq[l]);
    return mx;
}

/*int getkey(int node, int L, int R) {
    if (R <= tree[node].L || tree[node].R <= L) {
        return -1;
    }
    if (L <= tree[node].L && tree[node].R <= R) {
        return tree[node].key;
    }
    return max(getkey(tree[node].lc, L, R), getkey(tree[node].rc, L, R));
}

void put(int node, int i) {
    if (i < tree[node].L || tree[node].R <= i) {
        return;
    }
    if (i == tree[node].L && tree[node].R == i + 1) {
        tree[node].key = -1;
        return;
    }
    put(tree[node].lc, i);
    put(tree[node].rc, i);
    tree[node].key = max(tree[tree[node].lc].key, tree[tree[node].rc].key);
}*/

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scanf("%d", &N);
    forn(i, N) {
        scanf("%d", &a[i]);
    }
    forn(i, N-1) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].pb(--v);
        e[v].pb(u);
    }
    dfs(0, -1);
    set<pii> pr;
    vector<int> q;
    forn(i, N) {
        if (out[i] == 0) {
            pr.insert(mp(val[i], i));
        }
    }
    while (!pr.empty()) {
        int v = pr.rbegin()->second;
        pr.erase(--pr.end());
        q.pb(v);
        //cerr << v << ' ';
        int u = par[v];
        if (u != -1) {
            --out[u];
            if (out[u] == 0) {
                pr.insert(mp(val[u], u));
            }
        }
    }
    cerr << '\n';
    
    
    int L = *max_element(val, val + N) - 1;
    int R = L + 2 * N;
    while (R - L > 1) {
        forn(i, sz) upd(i,i);
        int M = L + (R - L) / 2;
        tc = 0;
        bool ok = true;
        forn(i, q.size()) {
            int v = q[i];
            int bord = M - val[v];
            int t = get(0, bord+1);
            if (t == -1) {
                ok = false;
                break;
            } else {
                upd(t, -1);
            }
        }
        if (ok) {
            R = M;
        } else {
            L = M;
        }
    }
    cout << R << '\n';

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
