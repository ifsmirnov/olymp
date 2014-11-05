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

int p[maxn], s[maxn], t[maxn];
int get(int x) { return x == p[x] ? x : (p[x] = get(p[x])); }
void unite(int x, int y) {
    x = get(x); y = get(y);
    if (x != y) {
        p[x] = y;
        s[y] += s[x] + 1;
        t[y] += t[x];
    } else {
        ++s[x];
    }
}


const int base = 1000000000;
int a[maxn];
int n;

void mul(int N) {
    n = 1;
    a[0] = 1;
    forn(III, N) {
        int cr = 0;
        forn(i, n) {
            a[i] = a[i] * 2 + cr;
            cr = a[i] / base;
            a[i] %= base;
        }
        if (cr) {
            a[n++] = cr;
        }
    }
    printf("%d", a[n-1]);
    ford(i, n-1) {
        printf("%09d", a[i]);
    }
    printf("\n");
}

void solve() {
    int n;
    scanf("%d", &n);
    forn(i, n) p[i] = i, s[i] = 0, t[i] = 1;
    forn(i, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u; --v;
        unite(u, v);
    }
    int k = 0;
    forn(i, n) if (i == p[i]) {
        if (t[i] != s[i]) {
            cout << 0 << endl;
            return;
        }
        ++k;
    }
    mul(k);
}


int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("arda.in", "r", stdin);
    freopen("arda.out", "w", stdout);

    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
