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
const int maxn = 1<<21;

int mrand() {
    static int x = 1;
    return ++x;
}

int n, m, teams;

char c[6][maxn+10];
int ta[10], tb[10];
int d[maxn], l[maxn], r[maxn], p[maxn];
char buf[maxn+10];

void scan() {
//     n = 21;
//     m = 2;
//     teams = 1;
//     forn(i, 1<<n) forn(j, 2) c[j][i] = __builtin_popcount(i) == 9 && rand()%5 == 0;
//     forn(j, 2) ford(i, 1<<n) forn(k, n) if (i&(1<<k)) {
//         c[j][i^(1<<k)] |= c[j][i];
//     }
//     ta[0] = ta[1] = 0;
//     ta[1] = 1;
    scanf("%d%d%d", &n, &m, &teams);
    forn(i, m) {
        scanf("%s", c[i]);
        forn(j, 1<<n) c[i][j] -= '0';
    }
    forn(i, teams) {
        scanf("%d%d", &ta[i], &tb[i]);
    }
}

// void solve(char *p1, char *p2) {
//     forn(i, 1<<n) {
//         d[i] = l[i] = r[i] = p[i] = 0;
//     }
//     forn(mask, 1<<n) {
//         if (!d[mask]) {
//             if (p1[mask]) {
//                 d[mask] = 1;
//                 l[mask] = mask;
//             } else if (p2[mask]) {
//                 d[mask] = 1;
//                 r[mask] = mask;
//             }
//         }
// 
//         if (!d[mask] && p[mask] && (n <= 17 || (mrand()&511) == 0)) {
//             for (int submask = mask; submask; submask = (submask - 1) & mask) {
//                 if (p1[submask] && p2[mask^submask]) {
//                     d[mask] = 1;
//                     l[mask] = submask;
//                     r[mask] = mask^submask;
//                     break;
//                 }
//             }
//         }
// 
//         if (d[mask]) {
//             forn(i, n) if (!(mask&(1<<i))) {
//                 int nmask = mask ^ (1<<i);
//                 p[nmask] = 1;
//                 {
//                     int nl = l[mask] ^ (1<<i);
//                     int nr = r[mask];
//                     if (p1[nl]) {
//                         d[nmask] = 1;
//                         l[nmask] = nl;
//                         r[nmask] = nr;
//                     }
//                 }
//                 {
//                     int nl = l[mask];
//                     int nr = r[mask] ^ (1<<i);
//                     if (p2[nr]) {
//                         d[nmask] = 1;
//                         l[nmask] = nl;
//                         r[nmask] = nr;
//                     }
//                 }
//             }
//         }
//     }
// }

template<typename T>
void conv(T *a, int sign) {
    forn(i, n) {
        int mask = (1<<n) - 1 - (1<<i);
        for (int sm = mask;; sm = (sm-1) & mask) {
            a[sm | (1<<i)] += a[sm] * sign;
            if (!sm) {
                break;
            }
        }
    }
}

template<typename T>
void out(T *a) {
    forn(i, 1<<n) {
        cout << (int)a[i] << " ";
    }
    cout << endl;
}

void solve(char *p1, char *p2) {
    out(p1);
    conv(p1, 1);
    out(p1);
    cout << endl;

    out(p2);
    conv(p2, 1);
    out(p2);
    cout << endl;

    forn(i, 1<<n) {
        d[i] = p1[i] * p2[i];
    }
    out(d);
    conv(d, -1);
    out(d);
}

void solve() {
    forn(I, teams) {
        solve(c[ta[I]], c[tb[I]]);
        forn(i, 1<<n) {
            buf[i] = d[i] + '0';
        }
        buf[1<<n] = '\n';
        printf("%s", buf);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
