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

struct TEdge {
    int x, y;
    i64 w;
    
    TEdge(int x = 0, int y = 0, i64 w = 0)
        : x(x)
        , y(y)
        , w(w)
    {
    }
    
    bool operator<(const TEdge &e) const {
        return w > e.w;
    }
};

const int maxm = 500001;
TEdge e[maxm];

int p[maxn];

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if ((x ^ y) & 1) {
        swap(x, y);
    }
    p[x] = y;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int N, M;
    scanf("%d%d", &N, &M);
    i64 sum = 0;
    //vector<
    forn(i, M) {
        int w;
        scanf("%d%d%d", &e[i].x, &e[i].y, &w);
        e[i].w = w;
        sum += w;
    }
    sort(e, e + M);
    forn(i, N) {
        p[i] = i;
    }
    forn(i, M) {
        if (e[i].w < 0) {
            break;
        }
        int x = e[i].x, y = e[i].y;
        if (root(x) != root(y)) {
            sum -= e[i].w;
            unite(x, y);
        }
    }
    cout << sum << '\n';

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
