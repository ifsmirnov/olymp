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
const int maxn = 55;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

#define ok(x, y) ((x)<n&&(y)<m&&(x)>=0&&(y)>=0)

int n, m;
int a[maxn][maxn];
int b[maxn][maxn];
int c[maxn][maxn];
pii order[maxn*maxn];
pii q[maxn*maxn];

bool cmp(const pii& x, const pii& y) {
    return a[x.fi][x.se] < a[y.fi][y.se];
}

void bfs(pii st) {
    forn(i, n) forn(j, m) b[i][j] = 0;
    assert(!c[st.fi][st.se]);
    b[st.fi][st.se] = 1;
    int lq = 0, rq = 1;
    q[0] = st;
    while (lq != rq) {
        int x = q[lq].fi, y = q[lq].se;
        ++lq;
        forn(i, 4) {
            int tx = x+dx[i], ty = y+dy[i];
            if (ok(tx, ty) && !b[tx][ty] && !c[tx][ty]) {
                b[tx][ty] = 1;
                q[rq++] = mp(tx, ty);
            }
        }
    }
}

void gen(int n_iter) {
    forn(i, n) forn(j, m) a[i][j] = 0;
    int x = rand()%n, y = rand()%m;
    forn(i, n_iter) {
        a[x][y] = i+1;
        int tx = x, ty = y;
        do {
            int p = rand()%4;
            x = tx+dx[p];
            y = ty+dy[p];
        } while (!ok(x, y));
    }
    forn(i, n) forn(j, m) assert(a[i][j]);
}

void solve() {
    n = 50;
    m = 50;
    gen(1000000);
//     cin >> n >> m;
//     forn(i, n) forn(j, m) cin >> a[i][j];
//     forn(i, n) {
//         forn(j, m) cout << a[i][j] << " ";
//         cout << endl;
//     }
    forn(i, n) forn(j, m) c[i][j] = 0;
    int k = 0;
    forn(i, n) forn(j, m) order[k++] = mp(i, j);
    sort(order, order+k, cmp);
    forn(I, k-1) {
        int cx = order[I].fi, cy = order[I].se;
        int tx = order[I+1].fi, ty = order[I+1].se;
//         cout << cx << " " << cy<< " -> " << tx << " " << ty << endl;
        if (a[cx][cy] == a[tx][ty]) {
            assert(false);
            goto bad;
        }
        if (((i64)a[cx][cy] + a[tx][ty] + cx - tx + cy - ty) % 2) {
            cerr << "odd\n";
            goto bad;
        }
        if (abs(cx-tx) + abs(cy-ty) > a[tx][ty] - a[cx][cy]) {
            cerr << "dist\n";
            goto bad;
        }
        forn(i, n) forn(j, m) b[i][j] = 0;
        bfs(order[I]);
        if (!b[tx][ty]) {
            cerr << "reach\n";
            goto bad;
        }
        bool nei = false;
        forn(i, 4) {
            int nx = tx+dx[i];
            int ny = ty+dy[i];
            if (ok(nx, ny) && (nx != cx || ny != cy) && b[nx][ny]) {
                nei = true;
            }
        }
        if (a[tx][ty] - a[cx][cy] != 1 && !nei) {
            cerr << "neighb" << endl;
            goto bad;
        }
        c[cx][cy] = 1;

    }

    printf("YES\n");
    return;
    bad: printf("NO\n");
    assert(false);
    return;
}


int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    forn(i,100) {
        solve();
    }
//     int t;
//     cin >> t;
//     fore(i, 1, t) {
//         cout << "Case #" << i << ":" << endl;
//         solve();
//     }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
