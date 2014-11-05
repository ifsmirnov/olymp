#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
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

#define move mov

int n, m;
int a[maxn], b[maxn];
int d[maxn][maxn][maxn][maxn][2];
int move[maxn][maxn][maxn][maxn][2];
int get(int l1, int r1, int l2, int r2, int m) {
//     cout << "get " << l1 << " "<< r1 << " " << m << endl;
    int& res = d[l1][r1][l2][r2][m];
    if (l1 > r1 && l2 > r2) return 0;
    if (res == inf) {
        if (m == 0) { // max
            res = -inf;
            if (l1 <= r1) {
                int t = get(l1+1, r1, l2, r2, 1) + a[l1];
                if (t > res) res = t, move[l1][r1][l2][r2][0] = 0;
            }
            if (l2 <= r2) {
                int t = get(l1, r1, l2+1, r2, 1) + b[l2];
                if (t >= res) res = t, move[l1][r1][l2][r2][0] = 1;
            }
            return res;
        } else { // min
            res = inf;
            if (l1 <= r1) {
                int t = get(l1, r1-1, l2, r2, 0) - a[r1];
                if (t < res) res = t, move[l1][r1][l2][r2][1] = 0;
            }
            if (l2 <= r2) {
                int t = get(l1, r1, l2, r2-1, 0) - b[r2];
                if (t <= res) res = t, move[l1][r1][l2][r2][1] = 1;
            }
            return res;
        }
    }
    return res;
}

void solve() {
    forn(i, maxn) forn(j, maxn) forn(k, maxn) forn(t, maxn) forn(r, 2)
        d[i][j][k][t][r] = inf, move[i][j][k][t][r] = -1;
    int n, m;
    cin>> n >> m;
//     forn(i, n) cin >> a[i];
//     forn(j, m) cin >> b[j];
    forn(j, m) b[j] = rand() % 100;
    forn(i, n) a[i] = rand() % 100;
    forn(i, n) cout << a[i] << " "; cout << endl;
    forn(j, m) cout << b[j] << " "; cout << endl;
    cout << get(0,n-1,0,m-1,0) << endl;
    int q = 0, w = n-1, e = 0, r = m-1, st = 0;
    forn(i, n+m) {
        cout << move[q][w][e][r][st] << " ";
        if (i%2 == 1) cout << endl;
        if (move[q][w][e][r][st] == 0) {
            if (st) --w; else ++q;
        } else {
            if (st) --r; else ++e;
        }
        st = !st;
    }
    cout << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
