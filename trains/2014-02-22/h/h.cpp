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
const int maxn = 1110;

unsigned a[maxn][maxn];
int n;
int r;
char buf[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%s", buf);
        forn(j, n) {
            if (buf[j] == '1') {
                a[i][j>>5] |= 1u<<(j&31);
            }
        }
    }
    r = (n + 31) / 32;
}

void trc() {
    forn(k, n) forn(i, n) if (a[i][k>>5] & (1u<<(k&31))) {
        forn(j, (n+31)/32) a[i][j] |= a[k][j];
    }
}

void solve() {
    trc();
    forn(i, n) {
        forn(j, n) {
            if (i == j || !(a[i][j>>5] &  (1u<<(j&31)))) {
                putchar('0');
            } else {
                putchar('1');
            }
        }
        putchar('\n');
    }
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("return.in", "r", stdin);
    freopen("return.out", "w", stdout);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
