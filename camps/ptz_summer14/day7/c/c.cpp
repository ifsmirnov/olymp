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
const int maxn = 205;
#define ok(x,y) ((x)>=0&&(y)>=0&&(x)<n&&(y)<m)

const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

int n, m;
int a[maxn][maxn];
int b[maxn][maxn];
int r[maxn][maxn];
pii q[maxn];
int qp;
char buf[maxn];

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, n) {
        scanf("%s", buf);
        forn(j, m) a[i][j] = buf[j]-'0';
    }
}

bool go() {
    if (qp == 0) return true;
//     forn(i, n) {
//         forn(j, m) cout << b[i][j] << " ";
//         cout << endl;
//     }
//     cout << endl;
    int i = qp - 1;
        int x = q[i].fi, y = q[i].se;
        int val = b[x][y];
        forn(d, 4) {
            int tx = x+dx[d], ty = y+dy[d];
            if (!ok(tx, ty) || !a[tx][ty] || b[tx][ty]) continue;
            b[tx][ty] = b[x][y] = val/2;
            int ret;
            if (val == 2) {
                swap(q[qp-1], q[i]);
                --qp;
                ret = go();
                ++qp;
                q[qp-1] = q[i];
                q[i] = mp(x, y);
            } else {
                q[qp++] = mp(tx, ty);
                ret = go();
                --qp;
            }
            b[tx][ty] = 0;
            b[x][y] = val;
            if (ret) return true;
        }
    return false;
}

bool run(int x, int y, int v) {
    if (v == 32) return false;
    if (v == 1) return true;
    b[x][y] = v;
    qp = 1;
    q[0] = mp(x, y);
    int ret = go();
    b[x][y] = 0;
    return ret;
}

void solve() {
    forn(i, n) forn(j, m) {
        if (a[i][j] == 0) {
            r[i][j] = 0;
            continue;
        }
        r[i][j] = 1;
        while (run(i, j, r[i][j]*2)) r[i][j] *= 2;
    }
    forn(i, n) {
        forn(j, m) printf("%d ", r[i][j]);
        printf("\n");
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
