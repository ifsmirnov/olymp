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
const int maxn = 10050;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
#define ok(x, y) ((x)>=0&&(y)>=0&&(x)<w&&(y)<h)

int w, h;
char c[105][105];
int lpos[256];
int idx[105][105];

int n, m;
vi e[maxn];
int mt[maxn], b[maxn];

bool kuhn(int v) {
    if (b[v]) return false;
    b[v] = 1;
    for (auto to : e[v]) {
        if (mt[to] == -1 || kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

bool matching() {
    forn(i, m) mt[i] = -1;
    forn(i, n) {
        forn(j, n) b[j] = 0;
        if (!kuhn(i)) {
            return false;
        }
    }
    return true;
}

void prepare() {
    forn(i, 256) lpos[i] = -1;
    forn(i, w) forn(j, h) {
        if (c[i][j] == '*') {
            idx[i][j] = ((i+j+1)%2 ? n : m)++;
        } else if (c[i][j] != '.') {
            if (lpos[c[i][j]] == -1) {
                lpos[c[i][j]] = ((i+j+1)%2 ? n : m)++;
            }
            idx[i][j] = lpos[c[i][j]];
        } else {
            idx[i][j] = -1;
        }
    }

//     forn(i, w) {
//         forn(j, h) cout << idx[i][j] << " ";
//         cout << endl;
//     }
//     cout << endl;
}

void build_graph() {
    forn(i, w) forn(j, h) if (idx[i][j] != -1 && (i+j)%2 == 0) {
        forn(d, 4) {
            int tx = i + dx[d];
            int ty = j + dy[d];
            if (ok(tx, ty) && idx[tx][ty] != -1) {
                e[idx[i][j]].pb(idx[tx][ty]);
            }
        }
    }
}

void scan() {
    scanf("%d%d", &w, &h);
    forn(i, w) {
        scanf("%s", c[i]);
    }
}

void paint(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        c[x1][min(y1, y2)] = '<';
        c[x1][max(y1, y2)] = '>';
    } else {
        c[min(x1, x2)][y1] = '^';
        c[max(x1, x2)][y1] = 'v';
    }
}

void out() {
    forn(i, w) forn(j, h) if ( (i+j)%2 && idx[i][j] != -1) {
//         cout << i << " " << j << endl;
        if (c[i][j] != '*') {
            c[i][j] = '@';
        }
        int v = idx[i][j];
        int to = mt[v];
        if (to == -1) {
            continue;
        }
        forn(d, 4) {
            int tx = i + dx[d];
            int ty = j + dy[d];
            if (ok(tx, ty) && idx[tx][ty] == to) {
                paint(i, j, tx, ty);
                mt[v] = -1;
                break;
            }
        }
//         assert(mt[v] == -1);
    }
    forn(i, w) forn(j, h) if (isalpha(c[i][j]) && isupper(c[i][j])) {
        c[i][j] = '@';
    }
    forn(i, w) {
        printf("%s\n", c[i]);
    }
}

void solve() {
    prepare();
    build_graph();

//     forn(i, n) {
//         cout << i << ": ";
//         for (auto j : e[i]) {
//             cout << j << " ";
//         }
//         cout << endl;
//     }
    if (m != n || !matching()) {
        printf("No\n");
        return;
    } else {
        printf("Yes\n");
        out();
    }
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
