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

typedef vector<vi> Matr;
Matr mul(const Matr& a, const Matr& b, int mod) {
    int n = a.size();
    Matr c(n, vi(n, 0));
    forn(i, n) forn(j, n) forn(k, n) {
        c[i][j] = ((i64)c[i][j] + (i64)a[i][k] * b[k][j]) % mod;
    }
    return c;
}

Matr mpow(Matr a, int k, int mod) {
    forn(i, a.size()) forn(j, a.size()) a[i][j] = (a[i][j]+mod) % mod;
    while (k) {
        a = mul(a,a, mod);
        k >>= 1;
    }
    return a;
}

void out(const Matr& a) {
    forn(i, a.size()) {
        forn(j, a[i].size()) cout << a[i][j] << " "; cout << endl;
    }
}

void read(Matr& a) {
    int n;
    cin >> n;
// n = 200;
    a = Matr(n, vi(n));
    forn(i, n) forn(j, n) cin >> a[i][j];
// forn(i, n) forn(j, n) a[i][j] = rand() % 50;
}

bool good(const Matr& a) {
    forn(i, a.size()) {
        forn(j, a[i].size()) if (a[i][j] == 0) return false;
    }
    return true;
}

Matr p[3];
int md[3] = {1000000007, 1000000009, 1000003};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    Matr a;
    read(a);
    cerr << "read" << endl;
    forn(i, 3) p[i] = mpow(a, 1<<2, md[i]);
    cerr << "pow" << endl;
    forn(i, a.size()) forn(j, a.size()) {
        bool ok = false;
        forn(t, 3) if (p[t][i][j]) { ok = true; break; }
        if (!ok) {
            cout << "NO" << endl;
            goto fff;
        }
    }
    cout << "YES" << endl;
    fff:;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
