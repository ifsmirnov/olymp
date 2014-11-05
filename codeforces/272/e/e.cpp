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
const int sz = 1<<19;
#define MX(x, y, a) (x != -1 && a[x] < a[y] ? (x) : (y))

int get(int l, int r, int *rmq, int *a) {
    l += sz;
    r += sz;
    int res = -1;
    while (l < r) {
        if (l%2 == 1) res = MX(res, rmq[l], a);
        if (r%2 == 0) res = MX(res, rmq[r], a);
        l = (l+1)/2;
        r = (r-1)/2;
    }
    if (l == r) res = max(res, rmq[l], a);
    return res;
}

void upd(int i, int x, int *rmq, int *a) {
    i += sz;
    rmq[i] = x;
    for (i /= 2; i; i /= 2) {
        rmq[i] = MX(rmq[i*2], rmq[i*2+1], a);
    }
}

int first(int i, int val, int *rmq, int *a, int v = 1, int l = 0, int r = sz) {
    if (a[rmq[v]] >= val) return -1;
    if (l + 1 == r) return rmq[v];
    if (i == -1 || i < (l+r)/2) {
        int res = first(i, val, rmq, a, v*2, l, (l+r)/2);
        if (res == -1) {
            return first(-1, val, rmq, a, v*2+1, (l+r)/2, r);
        } else {
            return res;
        }
    } else {
        return first(i, val, rmq, a, v*2+1, (l+r)/2, r);
    }
}

int n;
int a[maxn]; // a
int ma[maxn]; // -a
int ap[maxn]; // a+2i
int map[maxn]; // -a+2i
int am[maxn]; // a-2i
int mam[maxn]; // -a+2i

int rmq[sz*2];
int mrmq[sz*2];
int aprmq[sz*2];
int maprmq[sz*2];
int amrmq[sz*2];
int mamrmq[sz*2];
int revrmq[sz*2];

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d", &a[i]);
}

void fill_rmqs() {
    forn(i, n) {
        ma[i] = -a[i];
        ap[i] = a[i]+2*i;
        map[i] = -a[i]+2*i;
        am[i] = a[i]-2*i;
        mam[i] = -a[i]-2*i;
    }
    forn(i, n) {
        upd(i, i, rmq, a);
        upd(i, i, mrmq, ma);
        upd(i, i, aprmq, ap);
        upd(i, i, maprmq, map);
        upd(i, i, amrmq, am);
        upd(i, i, mamrmq, mam);

        upd(i, n-i-1, revrmq, a);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif


    scan();
    fill_rmqs();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
