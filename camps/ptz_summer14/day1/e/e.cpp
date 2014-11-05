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
#include <unordered_set>
#include <typeinfo>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fors(i, b, e) for (int i = min(b, e); i <= (int)(b) || i <= (int)(e); ++i)
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
const int maxn = 300;

const int dx[] = {-1, -1, 1, 1};
const int dy[] = {0, -1, 0, 1};
const char *c = "pqdb";

int **a;
int **h;
int **b;
int n;
i64 hh;
i64 ch;

void init() {
    a = new int*[maxn];
    forn(i, maxn) {
        a[i] = new int[maxn];
        a[i] += 150;
    }
    a += 150;

    h = new int*[maxn];
    forn(i, maxn) {
        h[i] = new int[maxn];
        forn(j, maxn) h[i][j] = rand() % 1000000000;
        h[i] += 150;
    }
    h += 150;

    b = new int*[maxn];
    forn(i, maxn) {
        b[i] = new int[maxn];
        b[i] += 150;
    }
    b += 150;
}

inline bool ok(int i, int j) {
    if (i > n || i < -n) return false;
    if (i < 0) return j >= i && j <= 0;
    else return j >= 0 && j <= i;
}

void fill() {
    fore(i, -n, -1) fore(j, i, 0) a[i][j] = 1, hh += h[i][j], ch += h[i][j] * 2;
    a[0][0] = 0;
    fore(i, 1, n) fore(j, 0, i) a[i][j] = 2, hh += h[i][j] * 2, ch += h[i][j];
}

void out() {
    fore(i, -n, -1) {
        fore(j, -n, i) putchar(' ');
        fore(j, i, 0) putchar('0'+a[i][j]), putchar(' ');
        putchar('\n');
    }
    fore(i, 0, n) {
        fore(j, i, n) putchar(' ');
        fore(j, 0, i) putchar('0'+a[i][j]), putchar(' ');
        putchar('\n');
    }
    putchar('\n');
}

int cx, cy;

int move(int d) {
    assert(a[cx][cy] == 0);
    int tx = cx;
    int ty = cy;
    forn(III, 2) {
        tx += dx[d];
        ty += dy[d];
        if (ok(tx, ty) && a[tx][ty] == d / 2 + 1) {
            hh -= a[cx][cy] * h[cx][cy];
            hh -= a[tx][ty] * h[tx][ty];
            swap(a[cx][cy], a[tx][ty]);
            hh += a[cx][cy] * h[cx][cy];
            hh += a[tx][ty] * h[tx][ty];

            cx = tx;
            cy = ty;
            return III + 1;
        }
    }
    return 0;
}

void rmove(int d, int k) {
    d ^= 2;
    int tx = cx + dx[d] * k;
    int ty = cy + dy[d] * k;
    hh -= a[cx][cy] * h[cx][cy];
    hh -= a[tx][ty] * h[tx][ty];
    swap(a[cx][cy], a[tx][ty]);
    hh += a[cx][cy] * h[cx][cy];
    hh += a[tx][ty] * h[tx][ty];
    cx = tx;
    cy = ty;
}

bool finished() {
    return hh == ch;
    if (cx || cy) return false;
    fore(i, -n, -1) fore(j, i, 0) if (a[i][j] != 2) return false;
    fore(i, 1, n) fore(j, 0, i) if (a[i][j] != 1) return false;
    return true;
}

bool prune1() {
    if (a[0][0] == 2 && a[-1][0] == 2 && a[-1][-1] == 2 && cx > 0) {
        return false;
    }
    if (a[0][0] == 1 && a[1][0] == 1 && a[1][1] == 1 && cx < 0) {
        return false;
    }
    return true;
}

int dfs1(int x, int y) {
    if (b[x][y] != -1) {
        int& ret = b[x][y];
        if (a[x][y] == 0) {
            return ret = 0xf;
        }
        ret = 0;
        int sd = a[x][y] == 1 ? 2 : 0;
        int td = sd + 1;

        int bit = 1;
        fore(mul, 1, 2) fore(d, sd, td) {
            if (bit != 1) bit <<= 1;
            int tx = x + ::dx[d] * mul;
            int ty = y + ::dy[d] * mul;
            if (!ok(tx, ty)) continue;

            if (a[tx][ty] == 0) {
                if (mul == 1) {
                    ret |= bit;
                } else if (a[(x+tx)/2][(y+ty)/2] != a[x][y]) {
                    ret |= bit;
                }
                continue;
            }
        }
    }
    return b[x][y];
}

unordered_set<i64> used;

int cntb = 0;

int md = 0;
string ans;
bool dfs(int depth = 0) {
    if (used.count(hh)) {
        return false;
    }
    used.insert(hh);

//     if (depth > md) {
//         cout << "depth = " << depth << endl;
//         out();
//         md = depth;
//     }

    if (finished()) return true;

//     if (!prune1()) return false;

    int order[4];
    forn(i, 4) order[i] = i;
    if (cx > 0) reverse(order, order + 4);
    bool all_zero = true;
    int ms[4];
    forn(I, 4) {
        int i = order[I];
        ms[i] = move(i);
        rmove(i, ms[i]);
        all_zero &= (ms[i] == 0);
    }

    if (all_zero) {
//         if (abs(cx) <= 2 && ++cntb < 20) {
//             out();
//         }
        return false;
    }


    for (int m = 2; m >= 1; --m) {
        forn(I, 4) {
            int i = order[I];
            if (ms[i] == m) {
                move(i);
                ans.pb(c[i]);
                if (dfs(depth + 1)) return true;
                ans.resize(ans.size() - 1);
                rmove(i, m);
            }
        }
    }
    return false;
}

void check(const string& s) {
    fill();
    cx = 0;
    cy = 0;
    for (auto c: s) {
        int d = 0;
        while (::c[d] != c) ++d;
        assert(0 != move(d));
        out();
    }
    assert(finished());
}

const char* res[] = {
"pdpqbq",
"pddpqbqpddbpbqqbpbdpqbq",
"pddpppdddpppddbdqpqbbqqpbdbbpqqqbbqqbppbddbpbqqqpbdpqbq",
"pddpppddddppppddddpppqpbddbbdqppddbddqppqbbqqpbdbbpqqpbqdbbbqqpddbbqpqqqbbbqqqqbbbqqbpqbbdbpdqpqpbdpqbq",
"pddpppddddpppppdddddpppppddddbdqpppqppbddddpppqpqbddbbdqppqpbddbbdqpppddbbbdqqpqbbqqpbdbbpqqpbqqbdbdbbbqpqpqdbbbqqpddbbqpqqqbbbbqqqqqpbbdbddqppqqqbbbbqqqqbbbqqbpqbbdbpdqpqpbdpqbq",
"pddpppddddpppppddddddppppppddddddpppppqpbddddbbdqppppddddbddqppppqppqbddddbdqpppqppbddddpppqpqbddbbdqppqpqbbddbbdqbbqpqppqpbdddpppddbbbbdqqpqbbqqpbdbbbdqqpqpbqqqbdbdbbpqpqqbdbdbbbqpqpqdbbbqqpddbbbqqpqqqbbbbbqqqqqpbbdbbqpqqqqbbbbbqqqqqqbbbbbqqqqbbbdddqppqbpqqbbqdbpbdbdqpqpbdpqbdqpqbbq",
"pddpppddddpppppddddddpppppppdddddddpppppppddddddbdqpppppqppbddddddpppppqpqbddddbbdqppppqpbddddbbdqpppppddddbbbdqqpppqppqbddddbddqppppqppqbbddddbdqpppqppbddddpppqpqbddbbdqppqpqqbbddbbdqbbbqpqppqpqbbdddbbqpqppqpbdddpppddbbbbdqqpqbbqqpbdbbbbbdqqqpqpbqqqbdbdbbbdqqppqqqbbdbdbbpqpqqbdbdbbbqpqpqdbbbqqpddbbbbqqbbqpqqqqbbbbbqqqqqpbbdbbpqqqqbbbbbbqqqqqqqpbbbdbbqpqqqqqbbbbbbqqqqqqbbbbbqqqqbbbdddqppqbpqqbbqdbpbdbdqpqpbdpqbdqpqbbq",
"pddpppddddpppppddddddpppppppddddddddppppppppddddddddpppppppqpbddddddbbdqppppppddddddbddqppppppqppqbddddddbdqpppppqppbddddddpppppqpqbddddbbdqppppqpqbbddddbbdqbbqpqppppqpbdddddpppppddddbbbbdqqpppqppqbddddbbbdqqpppqppqqbbddddbddqppppqppqbbddddbdqpppqppbddddpppqpqbddbbdqppqpqqbbddbbdqbbbqpqppqpqqbbbdddbbbqqpqppqpqbbdddbbqpqppqpbdddpppddbbbbdqqpqbbqqpbdbbbbbbdqqqpqpbqqqbdbdbbbbbdqqqppqqqqbbdbdbbbdqqppqqqbbdbdbbpqpqqbdbdbbbqpqpqdbbbqqpddbbbbqqbbbqqpqqqqbbbbbqqqqqpbbdbbbbqpqqqqqbbbbbbbqqqqqqqpbbbdbbpqqqqqbbbbbbbqqqqqqqqbbbbbbbqqqqqqbbbbbdqpqqqbbbbqqqbpqqqdbbpbbqdqbbpbdbddqppqbddqpqqbpbdpqbdqpqbbq",
"pddpppddddpppppddddddpppppppddddddddpppppppppdddddddddpppppppppddddddddbdqpppppppqppbddddddddpppppppqpqbddddddbbdqppppppqpbddddddbbdqpppppppddddddbbbdqqpppppqppqbddddddbddqppppppqppqbbddddddbdqpppppqppbddddddpppppqpqbddddbbdqppppqpqqbbddddbbdqbbbqpqppppqpqbbdddddbbqpqppppqpbdddddpppppddddbbbbdqqpppqppqbddddbbbbbdqqqpppqppqqbbddddbbbdqqpppqppqqbbbddddbddqppppqppqbbddddbdqpppqppbddddpppqpqbddbbdqppqpqqbbddbbdqbbbqpqppqpqqqbbbdddbbbbqqpqppqpqqbbbdddbbbqqpqppqpqbbdddbbqpqppqpbdddpppddbbbbdqqpqbbqqpbdbbbbbbdqqqpqpbqqqbdbdbbbbbbbdqqqqppqqqqbbdbdbbbbbdqqqppqqqqbbbdbdbbbdqqppqqqbbdbdbbpqpqqbdbdbbbqpqpqdbbbqqpddbbbbqqbbbbqqpqqqqbbbbbqqqqqpbbdbbbbbqqpqqqqqbbbbbbbqqqqqqqpbbbdbbbbqpqqqqqqbbbbbbbbqqqqqqqqqpbbbbdbbpqqqqqqbbbbbbbbqqqqqqqqbbbbbbbqqqqqqbbbbbdqpqqqbbbbqqqbpqqqdbbpbbqdqbbpbdbddqppqbddqpqqbpbdpqbdqpqbbq",
"pddpppddddpppppddddddpppppppddddddddpppppppppddddddddddppppppppppddddddddddpppppppppqpbddddddddbbdqppppppppddddddddbddqppppppppqppqbddddddddbdqpppppppqppbddddddddpppppppqpqbddddddbbdqppppppqpqbbddddddbbdqbbqpqppppppqpbdddddddpppppppddddddbbbbdqqpppppqppqbddddddbbbdqqpppppqppqqbbddddddbddqppppppqppqbbddddddbdqpppppqppbddddddpppppqpqbddddbbdqppppqpqqbbddddbbdqbbbqpqppppqpqqbbbdddddbbbqqpqppppqpqbbdddddbbqpqppppqpbdddddpppppddddbbbbdqqpppqppqbddddbbbbbbdqqqpppqppqqbbddddbbbbbdqqqpppqppqqqbbbddddbbbdqqpppqppqqbbbddddbddqppppqppqbbddddbdqpppqppbddddpppqpqbddbbdqppqpqqbbddbbdqbbbqpqppqpqqqbbbdddbbbbqqpqppqpqqqbbbbdddbbbbqqqpqppqpqqbbbdddbbbqqpqppqpqbbdddbbqpqppqpbdddpppddbbbbdqqpqbbqqpbdbbbbbbdqqqpqpbqqqbdbdbbbbbbbbdqqqqppqqqqbbdbdbbbbbbbdqqqqppqqqqqbbbdbdbbbbbdqqqppqqqqbbbdbdbbbdqqppqqqbbdbdbbpqpqqbdbdbbbqpqpqdbbbqqpddbbbbqqbbbbqqpqqqqbbbbbqqqqqpbbdbbbbbbqqqbbqpqqqqqqbbbbbbbqqqqqqqpbbbdbbbbpqqqqqqbbbbbbbbbqqqqqqqqqpbbbbdbbbbqpqqqqqqqbbbbbbbbbqqqqqqqqqqbbbbbbbbbqqqqqqqqbbbbbbbqqqqqqbbbbbqqqqbbbdbbpqqqbpqqqqdbbpbbbbdbbpqqpqqdqbbqbqbqpbbdbddqppqbddqpqqbpbdpqbdqpqbbq",
};

int main() {
    init();
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
//     freopen("hourglass.in", "r", stdin);
//     freopen("hourglass.out", "w", stdout);
    cin >> n;
//     cout << res[n-1] << endl;
//     return 0;
//     n = 5;
    fill();
    dfs();
    cout << ans << endl;
    check(ans);
    cerr << "used.size() = " << used.size() << endl;

//     forn(d, 4) {
//         int t = move(d);
//         out();
//         rmove(d, t);
//     }
//     out();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
