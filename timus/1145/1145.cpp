// real 3m44.586s
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

const int maxn = 1050;
#define ok(x, y) ((x)>=0&&(y)>=0&&(x)<n&&(y)<m)

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int n, m;
char s[maxn][maxn];
int d[maxn][maxn];

void dfs(int x, int y, int dd) {
    if (d[x][y]) {
        return;
    }
    d[x][y] = dd;
    forn(i, 4) {
        int tx = x+dx[i];
        int ty = y+dy[i];
        if(ok(tx, ty ) && s[tx][ty] == '.') dfs(tx, ty, dd+1);
    }
}

void scan() {
    scanf("%d%d", &n, &m);
    swap(n, m);
    forn(i, n) scanf("%s", s[i]);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    forn(i, n) forn(j, m) if (s[i][j] == '.') {
        dfs(i, j, 1);
        goto qq;
    }
    qq:;
    int mxx = 0, mxy = 0;
    forn(i, n) forn(j, m) if (d[i][j] > d[mxx][mxy]) mxx = i, mxy = j;
    forn(i, n) forn(j, m) d[i][j] = 0;
    dfs(mxx, mxy, 1);
    mxx = 0, mxy = 0;
    forn(i, n) forn(j, m) if (d[i][j] > d[mxx][mxy]) mxx = i, mxy = j;
    cout << d[mxx][mxy]-1 << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
