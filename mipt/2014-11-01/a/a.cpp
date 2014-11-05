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

int n, m;
int a[maxn][maxn];
int cr[maxn][maxn];
int par[maxn][maxn];
vi res;

void scan() {
    scanf("%d%d", &n, &m);
    swap(n, m);
    int s = 0;
    forn(i, n) forn(j, m) {
        scanf("%d", &a[i][j]);
        cr[i][j] = ++s;
    }
}

int odd(int a, int b, int c, int d) {
    int x[4] = {a, b, c, d};
    int cnt = 0;
    forn(i, 4) {
        forn(j, 4-1) {
            if (x[j] > x[j+1]) {
                ++cnt;
                swap(x[j], x[j+1]);
            }
        }
    }
    return cnt % 2;
}

void reverse_row(int i) {
    res.pb(i+1);
    forn(j, m/2) {
        swap(a[i][j], a[i][m-j-1]);
        par[i][j] ^= 1;
    }
}

void reverse_col(int j) {
    res.pb(-j-1);
    forn(i, n/2) {
        swap(a[i][j], a[n-i-1][j]);
        par[i][j] ^= 1;
    }
}

bool check_mid() {
    if (m%2 == 1) {
        if (a[0][m/2] != cr[0][m/2]) {
            reverse_col(m/2);
        }
        forn(i, n) {
            if (a[i][m/2] != cr[i][m/2]) {
                return false;
            }
        }
    }
    if (n%2 == 1) {
        if (a[n/2][0] != cr[n/2][0]) {
            reverse_row(n/2);
        }
        forn(j, m) {
            if (a[n/2][j] != cr[n/2][j]) {
                return false;
            }
        }
    }
    return true;
}

bool check_general() {
    forn(i, n/2) forn(j, n/2) {
        vi x, y;
        x.pb(a[i][j]); x.pb(a[i][m-j-1]); x.pb(a[n-i-1][j]); x.pb(a[n-i-1][m-j-1]);
        y.pb(cr[i][j]); y.pb(cr[i][m-j-1]); y.pb(cr[n-i-1][j]); y.pb(cr[n-i-1][m-j-1]);
        sort(all(x));
        sort(all(y));
        if (x != y) {
            return false;
        }
    }
    return true;
}

bool prepare_oddity() {
    forn(i, n) forn(j, m) par[i][j] = 0;
    forn(i, n/2) forn(j, m/2) {
        par[i][j] = odd(a[i][j], a[i][m-j-1], a[n-i-1][j], a[n-i-1][m-j-1]);
    }
    forn(j, m/2) {
        if (par[0][j]) {
            reverse_col(j);
        }
    }
    forn(i, n/2) if (i) {
        if (par[i][0]) {
            reverse_row(i);
        }
    }
    forn(i, n/2) forn(j, m/2) {
        if (par[i][j]) {
            return false;
        }
    }
    return true;
}

void out() {
    forn(i, n) {
        forn(j, n) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void make_tr(int i, int j, int t) {
    int i1 = i, i2 = n-i-1;
    int j1 = j, j2 = m-j-1;
    if (t == 0) {
        reverse_col(j2); reverse_row(i2);
        reverse_col(j2); reverse_row(i2);
    } else if (t == 1) {
        reverse_col(j1); reverse_row(i2);
        reverse_col(j1); reverse_row(i2);
    } else if (t == 2) {
        reverse_col(j2); reverse_row(i1);
        reverse_col(j2); reverse_row(i1);
    } else {
        reverse_col(j1); reverse_row(i1);
        reverse_col(j1); reverse_row(i1);
    }
}

void triangulate() {
    forn(i, n/2) forn(j, m/2) {
        int c[4] = {cr[i][j], cr[i][m-j-1], cr[n-i-1][j], cr[n-i-1][m-j-1]};
        int cc = 0;
        while (1) {
            int x[4] = {a[i][j], a[i][m-j-1], a[n-i-1][j], a[n-i-1][m-j-1]};
            int cnt = 0;
            forn(k, 4) cnt += x[k] == c[k];
            if (cnt == 4) {
                break;
            } else if (cnt == 0) {
                make_tr(i, j, 0);
            } else {
                forn(k, 4) if (x[k] == c[k]) {
                    make_tr(i, j, k);
                    break;
                }
            }
            assert(++cc <= 3);
        }
    }
}

void print_ans() {
    assert(n*m*10 >= (int)res.size());
    forn(i, n) forn(j, m) assert(a[i][j] == cr[i][j]);
    printf("POSSIBLE %d", (int)res.size());
    forn(i, res.size()) {
        if (res[i] > 0) {
            printf(" R%d", res[i]);
        } else {
            printf(" C%d", -res[i]);
        }
    }
    printf("\n");
}

bool solve() {
    res.clear();
    if (!check_mid()) {
//         cerr << "mid chech failed" << endl;
        return false;
    }
    if (!check_general()) {
//         cerr << "general check failed" << endl;
        return false;
    }

    if (!prepare_oddity()) {
//         cerr << "oddity check failed" << endl;
        return false;
    }

    triangulate();
    print_ans();
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t;
    scanf("%d", &t);
    forn(i, t) {
        scan();
        if (!solve()) {
            printf("IMPOSSIBLE\n");
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
