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
const int maxn = 5050;

int n;
int a[maxn][maxn];
int b[maxn*2];
int ts[maxn*2], tspos;
int s[maxn], t[maxn];
char buf[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%s", buf);
        forn(j, n) a[i][j] = buf[j] == '1';
    }
}

bool dfs(int v) {
    b[v] = 1;

    if (v < n) {
        forn(i, n) if (a[v][i]) {
            if (b[i+n] == 1) return false;
            if (!b[i+n] && !dfs(i+n)) return false;
        }
    } else {
        forn(i, n) if (!a[i][v-n]) {
            if (b[i] == 1) return false;
            if (!b[i] && !dfs(i)) return false;
        }
    }

    b[v] = 2;

    ts[tspos++] = v;

    return true;
}

void solve() {
    forn(i, n*2) if (!b[i]) {
        if (!dfs(i)) {
            cout << "NO" << endl;
            return;
        }
//         cout << endl;
    }
    forn(i, n*2) {
        int v = ts[i];
        if (v < n) s[v] = i+1;
        else t[v-n] = -i-1;
    }

    forn(i, n) forn(j, n) assert(a[i][j] == (s[i] + t[j] >= 0));
    printf("YES\n");
    forn(i, n) {
        printf("%d %d\n", s[i], t[i]);
    }
    printf("0\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("powersum.in", "r", stdin);
    freopen("powersum.out", "w", stdout);

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
