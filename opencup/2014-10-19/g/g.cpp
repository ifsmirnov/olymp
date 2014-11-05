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
const int maxn = 30;

#define ok(x, y) ((x)>=0&&(y)>=0&&(x)<n&&(y)<m)

int n, m;
int b[maxn][maxn];
int a[maxn][maxn];
int put(int x, int y, int d) {
    assert(d == -1 || !b[x][y]);
    int s = 0;
    fore(tx, x-1, x+1) fore(ty, y-1, y+1) {
        if (ok(tx, ty)) {
            s += b[tx][ty] != 0;
            b[tx][ty] += d;
        }
    }
    a[x][y] += d;
    return s;
}

void out() {
    forn(i, n+1) {
        forn(j, m+1) {
            bool t = 0;
            fore(di, i-1, i) fore(dj, j-1, j) {
                if (ok(di, dj) && a[di][dj]) {
                    t = 1;
                }
            }
            if (t) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
}

bool select_best() {
    int bv = inf;
    pii best(0, 0);
    forn(x, n) forn(y, m) if (!b[x][y]) {
        int t = put(x, y, 1);
        put(x, y, -1);
        if (t < bv) {
            bv = t;
            best = mp(x, y);
        }
    }
    if (bv == inf) {
//         cerr << "cannot take" << endl;
        return 0;
    }
//     cerr << "taken " << best.fi << " " << best.se << endl;
    put(best.fi, best.se, 1);
    return 1;
}

vector<pii> avail_moves() {
    vector<pii> t;
    forn(i, n) forn(j, m) if (!b[i][j]) {
        t.pb(mp(i, j));
    }
    return t;
}

bool random_move() {
    auto t = avail_moves();
    if (t.empty()) {
        return false;
    } else {
        pii a = t[rand()%t.size()];
        put(a.fi, a.se, 1);
        return true;
    }
}

void clear() {
    forn(i, n) forn(j, m) a[i][j] = b[i][j] = 0;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> m;
    --n;
    --m;
    int cw = 0, cl = 0;
    forn(i, 100) {
        clear();
        while (1) {
    //         printf("enemy:\n");
            if (random_move()) {
    //             out();
            } else {
                printf("won\n");
                ++cw;
                break;
            }
    //         printf("\n");
    //         printf("me\n");
            if (random_move()) {
    //             out();
            } else {
                printf("lose\n");
                ++cl;
                break;
            }
    //         printf("\n");
        }
    }
    cout << cw << " " << cl << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
