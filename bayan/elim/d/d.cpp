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
const int maxn = 20;

int n, m;
int a[maxn][maxn];
int b[maxn*maxn];

int score() {
    int res = n*m + 2*(n*m)*(n*m+1);
    forn(i, n) forn(j, m) {
        if (i) res -= 2*min(a[i][j], a[i-1][j]);
        if (j) res -= 2*min(a[i][j], a[i][j-1]);
    }
    return res;
}

int go(int mn = inf) {
    bool pr = mn != inf;
    int k = n*m;
    forn(i, n*m) {
        b[i] = i+1;
    }
    int cnt = 0;
    do {
        forn(i, n) forn(j, m) a[i][j] = b[i*m+j];
        int t = score();
        if (t < mn) {
            assert(!pr);
            mn = t;
            cnt = 0;
        }
        if (t == mn) {
            ++cnt;
        }
        mn = min(mn, t);
        if (pr && t == mn && cnt == 1) {
            forn(i, n) {
                forn(j, m) {
                    cout << a[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            return -1;
        }
    } while (next_permutation(b, b+k));
    if (!pr) {
        cout << n << "*" << m << endl;
        cout << "mn = " << mn-n*m << endl;
//         cout << "cnt = " << cnt << endl;
//         cout << "pow = " << __builtin_ctz(cnt) << endl;
    }
    return mn;
}

void fill(int x, int y, int k, int dir) {
    cout << "go " << x << " " << y << endl;
    if (x == n || y == m) {
        return;
    }
    if (dir == 0) {
        fore(j, y, m-1) {
            a[x][j] = k++;
        }
        fill(x+1, y, k, !dir);
    } else {
        fore(i, x, n-1) {
            a[i][y] = k++;
        }
        fill(x, y+1, k, !dir);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> m;
    fill(0, 0, 1, 0);
    forn(i, n) {
        forn(j, m) cout << a[i][j] << " ";
        cout << endl;
    }
    cout << score() << endl;
    int mn = go();
    go(mn);


#ifdef HOME
//     cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
