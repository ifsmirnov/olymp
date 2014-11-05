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

typedef long double ld;

int n, k;
ld p;

ld ff[maxn];
ld lf[maxn];

void compf() {
    ff[0] = 1;
    ff[1] = 1;
    lf[1] = 0;
    fore(i, 2, 10010) {
        lf[i] = lf[i-1] + logl((ld)i);
        ff[i] = ff[i-1] * i;
    }
}

ld solved(int n, int k, ld p) {
    ld res = 0;
    ld logp = logl(p);
    ld log1p = logl(1-p);
    for (int t = k; t < 2000; ++t) {
        res += exp(lf[t-1] - lf[k-1] - lf[t-k] + k*logp + (t-k)*log1p +
            t * log1p);
//         res += ff[t-1] / ff[k-1] / ff[t-k] * powl(p, k) * powl(1-p, t-k) *
//             powl(1-p, t);
    }
    return res * (n-1);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("stat.in", "r", stdin);
    freopen("stat.out", "w", stdout);
#endif
    compf();
    scanf("%d%d%Lf", &n, &k, &p);
    cout.precision(20);
    cout << fixed;
    cout << n-solved(n, k, p) << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
