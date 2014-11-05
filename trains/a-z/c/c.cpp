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

const int maxn = 105;
int d[maxn][maxn];
int anc[maxn][maxn];
char s[maxn], t[maxn];
int n, m;

void scan() {
    cin >> s >> t;
    n = strlen(s);
    m = strlen(t);
}

void relax(int val, int of, int i, int j) {
    if (d[i][j] < val) {
        d[i][j] = val;
        anc[i][j] = of;
    }
}

void dp() {
    forn(i, n+1) forn(j, m+1) d[i][j] = -10000;
    d[0][0] = 0;
    forn(i, n+1) forn(j, m+1) {
        if (i != n) relax(d[i][j], 1, i+1, j);
        if (j != m) relax(d[i][j], 2, i, j+1);
        if (i != n && j != m && s[i] == t[j]) relax(d[i][j]+1, 3, i+1, j+1);
    }
    vector<int> r1, r2;
    int i = n, j = m;
    while (i||j) {
        int di = anc[i][j]&1;
        int dj = anc[i][j]>>1;
        if (di && dj) r1.pb(i), r2.pb(j);
        i -= di;
        j -= dj;
    }
    reverse(all(r1));
    reverse(all(r2));
    cout << r1.size() << endl;
    forn(i, r1.size()) cout << r1[i] << " "; cout << endl;
    forn(i, r2.size()) cout << r2[i] << " "; cout << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("maxcon.im", "r", stdin);
    freopen("maxcom.out", "w", stdout);

    scan();
    dp();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
