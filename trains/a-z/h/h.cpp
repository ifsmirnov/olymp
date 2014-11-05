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
const int maxn = 105;
#define ok(x,y) ((x)>=0&&(x)<n&&(y)>=0&&(y)<m)

int n, m, xs, ys, xt, yt, p, q;
int d[maxn][maxn];
pii anc[maxn][maxn];

void scan() {
    cin >> n >> m;
    cin >> p >> q;
    cin >> xt >> yt;
    cin >> xs >> ys;
    --xt;--yt;--xs;--ys;
}

void bfs() {
    forn(i, n) forn(j, m) d[i][j] = inf;
    d[xs][ys] = 0;
    queue<pii> Q;
    Q.push(mp(xs, ys));
    while (!Q.empty()) {
        int x = Q.front().fi;
        int y = Q.front().se;
        Q.pop();
#define TRY(tx,ty) if (ok(tx, ty) && d[tx][ty] == inf) d[tx][ty] = d[x][y]+1, Q.push(mp(tx, ty)), anc[tx][ty] = mp(x,y)
        TRY(x+p, y+q);
        TRY(x+p, y-q);
        TRY(x-p, y+q);
        TRY(x-p, y-q);
        TRY(x+q, y+p);
        TRY(x+q, y-p);
        TRY(x-q, y+p);
        TRY(x-q, y-p);
    }
    int x = xt, y = yt;
    if (d[x][y] == inf) {
        cout << -1 << endl;
        return;
    }
    cout << d[x][y] << endl;
    while (x != xs || y != ys) {
        cout << x+1 << " " << y+1 << endl;
        pii t = anc[x][y];
        x = t.fi;
        y = t.se;
    }
    cout << x+1 << " " << y+1 << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("horse.in", "r", stdin);
    freopen("horse.out", "w", stdout);

    scan();
    bfs();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
