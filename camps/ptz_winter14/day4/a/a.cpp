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
const int maxn = 50500;

int n;
char a[maxn][6];

unsigned bs[5][128][maxn/32];

inline void sbit(unsigned* a, int p) {
    a[p>>5] |= 1u << (p&31);
}

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%s", a[i]);
        forn(j, 5) {
            sbit(bs[j][a[i][j]], i);
        }
    }
}

pii ans[100100];
int na = 0;

void solve() {
    forn(i, n) {
        forn(j, n/8+1) {
            unsigned mask = 0;
            forn(k, 5) {
                mask |= bs[k][a[i][k]][j];
            }
            mask = ~mask;
            if (mask) {
                forn(k, 32) {
                    if (j * 32 + k >= n) {
                        break;
                    }
                    if ((mask&1u) && i < j*32+k) {
                        ans[na++] = mp(i, j*32+k);
                    }
                    if (na == 100000) goto out;
                    mask >>= 1;
                }
            }
        }
    } out:;

//     {
//     int cnt = 0;
//     forn(i, n) forn(j, i) {
//         bool ok = true;
//         forn(k, 5) ok &= a[i][k] != a[j][k];
//         cnt += ok;
//     }
// 
//     assert(cnt == (int)ans.size());
//     forn(I, ans.size()) {
//         int i = ans[I].fi;
//         int j = ans[I].se;
//         bool ok = true;
//         forn(k, 5) ok &= a[i][k] != a[j][k];
//         assert(ok);
//     }
//     }

    printf("%d\n", na);
    forn(i, na) {
        printf("%d %d\n", ans[i].fi+1, ans[i].se+1);
    }
}

int main() {
#ifdef HOME
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
