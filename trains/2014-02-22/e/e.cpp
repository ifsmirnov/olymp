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
const int maxn = 100500;
const int base = 1000000000;

typedef vector<int> ml;
ml operator+(const ml& a, const ml& b) {
    if (a.empty()) return b;
    if (b.empty()) return a;
    ml c(max(a.size(), b.size()) + 1);
    int cr = 0;
    for (size_t i = 0; i < c.size(); ++i) {
        c[i] = (i<a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0) + cr;
        cr = c[i] / base;
        c[i] %= base;
    }
    while (!c.empty() && !c.back()) c.pop_back();
    return c;
}
void out(const ml& a) {
    int n = a.size();
    printf("%d", a[n-1]);
    ford(i, n-1) printf("%09d", a[i]);
    printf("\n");
}

ml d[1011][1011];
int n;

void solve() {
    scanf("%d", &n);
    d[0][0] = ml(1,1);
    forn(i, n) forn(b, i+1) {
        d[i+1][b+1] = d[i+1][b+1] + d[i][b];
        if (b) {
            d[i+1][b-1] = d[i+1][b-1] + d[i][b];
        }
    }
    ml res;
    forn(i, n+1) res = res + d[n][i];
    out(res);
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("moria.in", "r", stdin);
    freopen("moria.out", "w", stdout);

    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
