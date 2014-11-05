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
const int maxn = 100500;

int n, k;
int a[maxn];
int l[maxn], r[maxn], rev[maxn];
int lpos[maxn], rpos[maxn];
int np;

void scan() {
    scanf("%d%d", &n, &k);
    forn(i, n) scanf("%d", &a[i]), --a[i];
}

void add_seg(int l, int r, int rev) {
//     cout << l << " " << r << endl;
    if (r - l < 3) {
        fore(i, l, r) {
            ::l[np] = ::r[np] = a[i];
            lpos[np] = rpos[np] = i;
            ::rev[np++] = 0;
        }
        return;
    }
    int t = rand()%2;
    forn(i, t) {
        ::l[np] = ::r[np] = a[l+i];
        lpos[np] = rpos[np] = l+i;
        ::rev[np++] = 0;
    }
    l += 0;
    r -= 0;
    ::l[np] = a[l];
    ::r[np] = a[r];
    lpos[np] = l;
    rpos[np] = r;
//     if (rev == -1) swap(lpos[np], rpos[np]);

    ::rev[np++] = rev;

    rand()
    forn(i, rand()%2) {
        ::l[np] = ::r[np] = a[r+i+1];
        lpos[np] = rpos[np] = r+i+1;
        ::rev[np++] = 0;
    }
}

void split() {
    int l = 0;
    int dir = 0;
    forn(i, n) {
        if (i == 0) continue;
        if (abs(a[i] - a[i-1]) != 1 || (dir && a[i] - a[i-1] != dir)) {
//             cerr << "fail@ " << i << endl;
            add_seg(l, i-1, dir);
            l = i;
            dir = 0;
        } else {
            if (abs(a[i] - a[i-1]) == 1)
                dir = a[i] - a[i-1];
        }
    }
    add_seg(l, n-1, dir);
}



vector<pii> res;

void revseg(int i, int j) {
    fore(k, i, j) rev[k] *= -1;
    while (i < j) {
        swap(l[i], l[j]);
        swap(r[i], r[j]);
        swap(lpos[i], lpos[j]);
        swap(rpos[i], rpos[j]);
        swap(rev[i], rev[j]);
        ++i; --j;
    }
}

bool try0() {
    forn(i, np-1) if (l[i] < l[i+1] && rev[i] >= 0 && rev[i+1] >= 0) ; else return false;
    return rev[np-1] >= 0;
    return true;
}

bool try1(int k) {
    if (np > 16) return false;
    if (k == 0) return try0();
    int offset = 0;
    forn(i, np)
    {
        int len = 0;
        fore(j, i, np-1)
        {
            len += rpos[j] - lpos[j] + 1;
            res.pb(mp(offset, offset + len - 1)); // lpos & rpos SUCKS!!!11
            revseg(i, j);
            if (try1(k-1)) return true;
            revseg(i, j);
            res.pop_back();
        }
        offset += rpos[i] - lpos[i] + 1;
    }
    return false;
}

// void genYes(int n, int k)
// {
//     long long seed;
//     asm("rdtsc":"=A"(seed));
//
//     FILE *f = fopen("test.txt", "w");
//     int *data = new int[n];
//     for (int i = 0; i < n; ++i)
//         data[i] = i;
//     for (int i = 0; i < k; ++i)
//     {
//         int l = rand() % n;
//     }
//     fclose(f);
// }

void solve() {
    if (try1(k)) {
        cout << "TAK" << endl;
        forn(i, k)
        {
            if (res[i].fi > res[i].se) swap(res[i].fi, res[i].se);
            cout << res[i].fi+1 << " " << res[i].se+1 << endl;
        }
    } else {
        cout << "NIE" << endl;
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    split();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
