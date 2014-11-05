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
int check() { // 1: ok; 0: nothing; -1: too many
//     forn(i, n) {
//         forn(j, s) cout << c[i][j] << " ";
//         cout << endl;
//     }
//     cout << endl;

    forn(i, n) forn(j, 7) d[j][i] = 0;
    d[0][0] = 1;
    bool bad = false;
    forn(i, 6) {
        int cnt = 0;
        forn(j, n) {
            if (t[j]) cnt += d[i][j];
            if (cnt > des[i]) return -1;
            forn(k, s) if (c[j][k])
                d[i+1][c[j][k]-1] += d[i][j];
        }
        if (cnt != des[i]) bad = true;
    }
    int cnt = 0;
    forn(i, n) {
        if (t[i]) cnt += d[6][i];
    }
    if (cnt > des[6]) return -1;
    return !bad && cnt == des[6];
}

bool check_degs() {
    int c[10];
    forn(i, n) c[i+1] = 0;
    forn(i, s) c[::c[0][i]]++;
    fore(i, 2, n-1) if (c[i] < c[i+1]) return false;
    return true;
}

bool go(int cn, int cs) {
//     cout << cn << " " << cs << endl;
    if (cn == 0 && !check_degs()) return false;
    int cv = check();
    if (cv == -1) return 0;
    if (cv == 1) return 1;
    if (cs == s) ++cn, cs = 0;
    if (cn == n) return 0;

    int b = 1;
    if (cs) b = c[cn][cs - 1];
    fore(i, b, n) {
        c[cn][cs] = i;
        if (go(cn, cs+1)) return true;
//         if (n > 3 && i == b+1) break;
    }
    c[cn][cs] = 0;
    if (go(cn, s)) return true;
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
//     cout << go(0, 0) << endl;
//     return;
    while (1) {
        for (s = 1; s <= 10; ++s) {
            cout << "go " << n << " " << s << endl;
            forn(i, 1<<n) {
                forn(j, n) t[j] = 0 != (i&(1<<j));
                if (go(0, 0)) {
                    out();
                    return;
                }
            }
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
