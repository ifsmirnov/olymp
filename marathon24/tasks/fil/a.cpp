#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <cstring>
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
int a[maxn], b[maxn];
char s[maxn];
int need1, need2;
int c[maxn], pc;

bool cmp(int i, int j) {
    if (i == need1 || i == need2) return true;
    else if (j == need1 || j == need2) return false;
    return a[i] > a[j];
}

int getp(int p, bool t1, bool t2) {
    if (t1&&t2&&k==0) return -1;
    if ((t1^t2) && k <= 1) return -1;
//     if (!(t1&&t2)) return -1;
//     cout << "get " << p << " " << t1 << " " << t2 << endl;
    if (pc == 1) {
        return a[c[0]];
    }
    need1 = need2 = -1;
    if (t1) {
        if (b[0] == 1) need1 = 0;
        else return -1;
    }
    if (t2) {
        if (b[n-1] == 1) need2 = n-1;
        else return -1;
    }
    sort(c, c+pc, cmp);
//     forn(i, pc) cout << c[i] << " "; cout << endl;
//     cout << "pc = " << pc << endl;
    int s = 0;
    forn(i, min(p, pc)) {
        s += a[c[i]];
    }

    // test
    int q = 0;
    forn(i, n) q += a[i];
//     cout << "q = " << q << endl;
    return s;
}

void solve() {
    scanf("%d%s", &k, s);
    char c = s[0];
    int l = 0;
    n = 0;
    int len = strlen(s);
    for (int i = 1; i <= len; ++i) {
        if (s[i] != c) {
            b[n] = (c == 'D');
            a[n] = i - l;
            c = s[i];
            l = i;
            ++n;
        }
    }
    pc = 0;
    forn(i, n) if (b[i]) ::c[pc++] = i;

    int mx = -1;
    forn(a, 2) forn(b, 2) mx = max(mx, getp((k+a+b+2)/2, a, b));
    cout << mx << endl;

//     forn(i, n) if (b[i]) cout << a[i] << " "; cout << endl;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    int t;
    scanf("%d", &t);
    forn(i, t) {
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
