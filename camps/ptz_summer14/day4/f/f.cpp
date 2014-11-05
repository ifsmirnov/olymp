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

const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

struct pt {
    int x, y;
    pt():x(0),y(0) {}
    pt(int x, int y):x(x), y(y) {}
    pt operator+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt operator-(const pt& p) const { return pt(x-p.x, y-p.y); }
    pt operator-() const { return pt(-x, -y); }
    pt(int x) {
        assert(x == -1);
        this->x = this->y = -1;
    }
    pt turnCCW() const { return pt(-y, x); }
    pt turnCW() const { return pt(y, -x); }
};

ostream& operator<<(ostream& out, const pt& p) {
    out << p.x << " " << p.y;
    return out;
}

namespace dsu {
    int p[maxn];
    int get(int x) {
        if (x == p[x]) return x;
        return p[x] = get(p[x]);
    }
    void unite(int x, int y) { p[get(x)] = get(y); }
    void clear() { forn(i, maxn) p[i] = i; }
};

using dsu::unite;
using dsu::get;
using dsu::clear;

int n, m;
char c[maxn][maxn];
int otvet[maxn];
int id[maxn][maxn];
int e[maxn];
int b[maxn];
int ded[maxn];
pt p[maxn];
int np;

pt zero;

pt get_pos(pt et, pt p, bool reflect, int rot) {
    if (reflect) p.x = 2*zero.x - p.x;
    p = p - zero;
    if (rot == 1) p = p.turnCCW();
    else if (rot == 2) p = -p;
    else if (rot == 3) p = p.turnCW();
    return p + et;
}

bool ok(const pt& p) {
    return p.x >= 0 && p.y >= 0 && p.x < n && p.y < m;
}

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, n) scanf("%s", c[i]);
}

void print_sol() {
    forn(i, np) {
        c[p[i].x][p[i].y] = otvet[i] + 'A' - !!'A';
    }
    printf("YES\n");
    forn(i, n) {
        printf("%s\n", c[i]);
    }
}

bool solve() {
    forn(i, n) forn(j, m) if (c[i][j] == 'X') {
        id[i][j] = np;
        p[np++] = {i, j};
    } else id[i][j] = -1;

    zero = p[0];

    forn(reflect, 2) forn(rotate, 4) forn(k, np) if (k) {
        queue<int> q;
        forn(i, np) ded[i] = 0;
        forn(i, np) otvet[i] = 0;
        forn(i, np) b[i] = 0;

        // build graph
        forn(i, np) {
            pt nxt = get_pos(p[k], p[i], reflect, rotate);
            if (ok(nxt) && c[nxt.x][nxt.y] == 'X') {
                e[i] = id[nxt.x][nxt.y];
                ++ded[e[i]];
            } else {
                e[i] = -1;
            }
            if (e[i] == i) goto fail;
        }

        // paths
        forn(i, np) if (ded[i] == 0) {
            int c = 0;
            for (int j = i; j != -1; j = e[j], c = !c) {
                b[j] = 1;
                otvet[j] = c + 1;
            }
            if (c == 1) {
                goto fail;
            }
        }


        // cycles
        forn(i, np) if (otvet[i] == 1 || i == 0) q.push(i), b[i] = 1;
        if (otvet[0] == 0) {
            b[0] = 1;
            assert(e[0] != -1);
            otvet[0] = 1;
            otvet[e[0]] = 2;
            b[e[0]] = 1;
            if (e[e[0]] != 0)
                goto fail;
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();


            int x = p[v].x, y = p[v].y;
            forn(i, 4) {
                int tx = x + dx[i], ty = y + dy[i];
                if (ok(pt(tx, ty)) && c[tx][ty] == 'X') {
                    int to = id[tx][ty];
                    if (b[to]) continue;
                    otvet[to] = b[to] = 1;
                    q.push(to);
                    assert(e[to] != -1);
                    otvet[e[to]] = 2;
                    b[e[to]] = 1;
                    if (e[e[to]] != to) {
                        goto fail;
                    }
                }
            }
        }

        forn(i, np) if (otvet[i] == 0) goto fail;

        clear();
        forn(i, np) if (otvet[i] == 1) {
            int x = p[i].x, y = p[i].y;
            forn(j, 4) {
                int tx = x + dx[j], ty = y + dy[j];
                if (ok(pt(tx, ty)) && c[tx][ty] == 'X' && otvet[id[tx][ty]] == 1) {
                    int to = id[tx][ty];
                    unite(i, to);
                }
            }
        }
        forn(i, np) if (otvet[i] == 1 && get(i) != get(0)) goto fail;
        print_sol();
        return true;

        fail:;
    }
    printf("NO\n");
    return false;
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
