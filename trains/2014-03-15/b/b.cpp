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
const int maxn = 211;
const int base = 10000;

typedef vi ml;
ml operator+(const ml& a, const ml& b) {
    ml c(max(a.size(), b.size()) + 1);
    int cr = 0;
    for (size_t i = 0; i < c.size(); ++i) {
        c[i] = cr;
        if (i < a.size()) c[i] += a[i];
        if (i < b.size()) c[i] += b[i];
        cr = c[i] / base;
        c[i] %= base;
    }
    while (!c.empty() && !c.back()) c.pop_back();
    return c;
}
ml operator*(const ml& a, const ml& b) {
    ml c(a.size() + b.size());
    forn(i, a.size()) {
        int cr = 0;
        forn(j, b.size()) {
            c[i+j] += a[i]*b[j] + cr;
            cr = c[i+j] / base;
            c[i+j] %= base;
        }
        for (int j = b.size(); cr; ++j) {
            c[i+j] += cr;
            cr = c[i+j] / base;
            c[i+j] %= base;
        }
    }
    while (!c.empty() && !c.back()) c.pop_back();
    return c;
}
void pop1(ml& a) {
    int i = 0;
    while (a[i] == 0) a[i++] = base-1;
    --a[i];
    while (!a.empty() && !a.back()) a.pop_back();
}
void out(const ml& a) {
    printf("%d", a.back());
    ford(i, a.size()-1) {
        printf("%04d", a[i]);
    }
    printf("\n");
}

int n;
ml d[maxn];
ml c[maxn][maxn];
ml p2[maxn];

void compd() {
    d[0] = ml(1,1);
    for (int i = 1; i <= n; ++i) {
        d[i] = d[i-1] * ml(1, i);
        if (i%2==0) d[i] = d[i] + ml(1,1);
        else pop1(d[i]);
//         out(d[i]);
    }
}
void compcand2k() {
    c[0][0] = ml(1,1);
    for (int n = 1; n <= ::n; ++n) {
        c[n][0] = c[n][n] = ml(1,1);
        for (int k = 1; k < n; ++k) {
            c[n][k] = c[n-1][k] + c[n-1][k-1];
        }
    }

    p2[0] = ml(1,1);
    for (int i = 1; i <= n; ++i) {
        p2[i] = p2[i-1] * ml(1,2);
    }
//     out(p2[10]);
//     out(c[10][2]);
}

void solve() {
    ml res = ml(0,0);
    fore(k, 0, n) {
        res = res + (d[n-k] * c[n][k] * p2[n-k]);
    }
    out(res);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("derangements.in", "r", stdin);
    freopen("derangements.out", "w", stdout);

    cin >> n;
    compd();
    compcand2k();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
