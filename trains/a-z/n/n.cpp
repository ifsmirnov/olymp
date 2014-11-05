#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <bitset>
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
const int maxn = 10010;

typedef bitset<20010> mask;

int n;
int a[maxn], X;
mask m[maxn];
int pl[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("nearest.in", "r", stdin);
    freopen("nearest.out", "w", stdout);

    cin >> n >> X;
    X += 10005;
    forn(i, n) cin >> a[i];
    m[1][10005+a[0]] = 1;
    forn(i, n) if (i) {
        m[i+1] |= m[i] >> abs(a[i]);
        m[i+1] |= m[i] << abs(a[i]);
    }
    int bst = inf;
    forn(i, 20010) {
        if (abs(X - i) < abs(bst - X) && m[n][i]) {
            bst = i;
        }
    }
    cout << bst-10005 << endl;
    int p = bst;
    ford(i, n) if (i) {
        if (m[i][p-a[i]]) {
            pl[i] = 1;
            p -= a[i];
        } else {
            assert(m[i][p+a[i]]);
            pl[i] = 0;
            p += a[i];
        }
    }
    forn(i, n) {
        if (i) {
            if (!pl[i]) printf("-");
            else printf("+");
        }
        printf("%d", a[i]);
    }
    printf("\n");

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
