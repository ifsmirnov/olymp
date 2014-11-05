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

int n, s, k;
int c[100][100];
int d[100][100];
bool t[100];

int des[] = {1, 1, 2, 5, 14, 42, 0};
int bad_mask[1<<3];
int check() { // 1: ok; 0: nothing; -1: too many
//     forn(i, n) {
//         forn(j, s) cout << c[i][j] << " ";
//         cout << endl;
//     }
//     cout << endl;

    forn(i, n) forn(j, 7) d[j][i] = 0;

    d[0][0] = 1;
    forn(i, 6) {
        forn(j, n) {
            forn(k, s) if (c[j][k])
                d[i+1][c[j][k]-1] += d[i][j];
        }
    }

    forn(i, 1<<(n-1)) bad_mask[i] = 1;
    forn(i, 7) {
        forn(tm, 1<<(n-1)) {
            int mask = (tm<<1)|1;
            int cnt = 0;
            forn(j, n) if (mask&(1<<j)) cnt += d[i][j];
            if (cnt > des[i])
                bad_mask[tm] = -1;
            else if (cnt != des[i] && bad_mask[tm] != -1)
                bad_mask[tm] = 0;
        }
    }

    bool f0 = false;
    forn(tm, 1<<(n-1)) {
        if (bad_mask[tm] == 1) {
            tm = (tm<<1)|1;
            forn(i, n) t[i] = 0 != (tm&(1<<i));
            return 1;
        } else if (bad_mask[tm] == 0) {
            f0 = true;
        }
    }
    if (f0) return 0;
    else return -1;
}

bool check_degs() {
    int c[10];
    forn(i, n) c[i+1] = 0;
    forn(i, s) c[::c[0][i]]++;
    fore(i, 1, n-1) if (c[i] < c[i+1]) return false;
    return true;
}

int cpos[10];

bool go(int fp) {
    if (fp == n*s) return false;
//     if (!check_degs()) return false;
//     if (cn == 0 && !check_degs()) return false;
    int cv = check();
    if (cv == -1) return 0;
    if (cv == 1) return 1;
//     if (cs == n) ++cn, cs = 0;
//     if (cn == n) return 0;

//     forn(i, n) {
//         forn(j, s) cout << c[i][j] << " ";
//         cout << endl;
//     }
//     cout << endl;

    forn(i, 3) {
        int to = rand() % n + 1;
        int cn = rand() % n;

        while (cpos[cn] == s) cn = rand() % n;
        c[cn][cpos[cn]++] = to;
        if (go(fp+1)) return true;
        c[cn][--cpos[cn]] = 0;
    }
    return false;
}

void out() {
    cout << "found " << n << " " << s << endl;
    forn(i, n) cout << t[i] << " "; cout << endl;
    forn(i, n) {
        forn(j, s) cout << c[i][j] << " "; cout << endl;
    }
}

void solve(int k) {
    des[6] = k;
    n = 2;
//     n = 3;
//     s = 4;
//     cout << go(0) << endl;
//     return;
    while (1) {
        for (s = 1; s <= 10; ++s) {
            cout << "go " << n << " " << s << endl;
            if (go(0)) {
                out();
                return;
            }
            cout << clock()/1000 << endl;
        }
        ++n;
    }
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
//     freopen("output.txt", "w", stdout);

//     cin >> n >> s;
//     forn(i, n) cin >> t[i];
//     forn(i, n) forn(j, s) cin >> c[i][j];
//     des[6] = 131;
//     cout << check() << endl;

    cin >> k;
//     k = 131;
    solve(k);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
