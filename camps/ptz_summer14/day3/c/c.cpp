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
const int maxn = 10;

#define ok(x, y) ((x)>=0&&(y)>=0&&(x)<8&&(y)<8)

char board[maxn][maxn];
int attack[maxn][maxn];
int global_attack[maxn][maxn];
int wx, wy;

bool white(int i, int j) { return isupper(board[i][j]); }
bool black(int i, int j) { return islower(board[i][j]); }


void scan() {
    forn(i, 8) cin >> board[i];
    forn(i, 8) forn(j, 8) if (board[i][j] == 'K') wx = i, wy = j;
}

void knight(int x, int y) {
    static const int dx[] = {1,1,2,2,-1,-1,-2,-2};
    static const int dy[] = {2,-2,1,-1,2,-2,1,-1};
    forn(i, 8) {
        int tx = x+dx[i];
        int ty = y+dy[i];
        if (ok(tx, ty)) {
            attack[tx][ty] = 1;
        }
    }
}

void bishop(int x, int y) {
    static const int dx[] = {1,1,-1,-1};
    static const int dy[] = {-1,1,-1,1};
    forn(i, 4) {
        int tx = x+dx[i];
        int ty = y+dy[i];
        while (ok(tx, ty)) {
            attack[tx][ty] = 1;
            if (board[tx][ty] != '.') break;
            tx += dx[i];
            ty += dy[i];
        }
    }
}

void rook(int x, int y) {
    static const int dx[] = {0,0,1,-1};
    static const int dy[] = {1,-1,0,0};
    forn(i, 4) {
        int tx = x+dx[i];
        int ty = y+dy[i];
        while (ok(tx, ty)) {
            attack[tx][ty] = 1;
            if (board[tx][ty] != '.') break;
            tx += dx[i];
            ty += dy[i];
        }
    }
}

void king(int x, int y) {
    fore(dx, -1, 1) fore(dy, -1, 1) if ((dx||dy) && ok(x+dx, y+dy)) {
        attack[x+dx][y+dy] = 1;
    }
}

bool check(bool c = false) {
    forn(i, 8) forn(j, 8) attack[i][j] = false;
    forn(i, 8) forn(j, 8) {
        switch(board[i][j]) {
        case 'n': knight(i, j); break;
        case 'b': bishop(i, j); break;
        case 'r': rook(i, j); break;
        case 'q': bishop(i, j); rook(i, j); break;
        case 'k': king(i, j); break;
        }
        if (c && attack[wx][wy]) return true;
    }
    return false;
}

bool move_white(int x, int y, int tx, int ty) {
    if (ok(tx, ty) && !white(tx, ty)) {
        if (x == wx && y == wy) {
            wx = tx; wy = ty;
        }

        int rm = board[tx][ty];
        board[tx][ty] = board[x][y];
        board[x][y] = '.';

        bool ret = false;
        if (!check(true)) {
            ret = true;
        }

        /*
        if (ret) {
            forn(i, 8) cout << board[i] << endl;
            cout << endl;
            forn(i, 8) { forn(j, 8) cout << attack[i][j]; cout << endl; }
            cout << endl;
        }
        */

        board[x][y] = board[tx][ty];
        board[tx][ty] = rm;

        if (wx == tx && wy == ty) {
            wx = x; wy = y;
        }

        if (ret) return true;
    }
    return false;
}

bool Kn(int x, int y) {
    static const int dx[] = {1,1,2,2,-1,-1,-2,-2};
    static const int dy[] = {2,-2,1,-1,2,-2,1,-1};
    forn(i, 8) {
        int tx = x+dx[i];
        int ty = y+dy[i];
        if (move_white(x, y, tx, ty)) return true;
    }
    return false;
}

bool Bi(int x, int y) {
    static const int dx[] = {1,1,-1,-1};
    static const int dy[] = {-1,1,-1,1};
    forn(i, 4) {
        int tx = x+dx[i];
        int ty = y+dy[i];
        while (ok(tx, ty)) {
            if (move_white(x, y, tx, ty)) return true;
            if (board[tx][ty] != '.') break;
            tx += dx[i];
            ty += dy[i];
        }
    }
    return false;
}

bool Ro(int x, int y) {
    static const int dx[] = {0,0,1,-1};
    static const int dy[] = {1,-1,0,0};
    forn(i, 4) {
        int tx = x+dx[i];
        int ty = y+dy[i];
        while (ok(tx, ty)) {
            if (move_white(x, y, tx, ty)) return true;
            if (board[tx][ty] != '.') break;
            tx += dx[i];
            ty += dy[i];
        }
    }
    return false;
}

bool Ki(int x, int y) {
    fore(dx, -1, 1) fore(dy, -1, 1) if (dx||dy) {
        int tx = x+dx;
        int ty = y+dy;
//         if (ok(tx, ty) && !white(tx, ty) && !global_attack[tx][ty]) return true;
        if (ok(tx, ty) && move_white(x, y, tx, ty)) {
//             cerr << "move to " << tx << " " << ty << endl;
            return true;
        }
    }
    return false;
}

bool move_exists() {
    forn(i, 8) forn(j, 8) {
        switch(board[i][j]) {
        case 'N': if (Kn(i, j)) return true; break;
        case 'B': if (Bi(i, j)) return true; break;
        case 'R': if (Ro(i, j)) return true; break;
        case 'Q': if (Bi(i, j) || Ro(i, j)) return true; break;
        case 'K': if (Ki(i, j)) return true; break;
        }
    }
    return false;
}

void solve() {
    check();
    forn(i, 8) forn(j, 8) global_attack[i][j] = attack[i][j];
    bool is_checked = attack[wx][wy];
    bool can_move = move_exists();
    if (is_checked) {
        if (can_move) cout << "check\n";
        else cout << "checkmate\n";
    } else {
        if (can_move) cout << "ok\n";
        else cout << "stalemate\n";
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t;
    cin >> t;
    forn(i, t) {
        scan();
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
