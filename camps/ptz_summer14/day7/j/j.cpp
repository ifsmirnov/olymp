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

const int N = 300100;

vector <int> g[N];

long long b[N];

long long a0 = 0, a1 = 0;

void dfs(int v, long long h, int p) {
    a0 += ((long long)g[v].size() - 2) * h;
    for (int to : g[v]) {
        a1 -= h * (b[to] - b[v]);
        if (to != p) {
            dfs(to, h + 1, v);
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int n;
    //n = 2;
    scanf("%d", &n);
    
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        //x = 1, y = 2;
        scanf("%d%d", &x, &y);
        --x, --y;
        g[x].pb(y);
        g[y].pb(x);
    }
    
    for (int i = 0; i < n; ++i) {
        scanf("%lld", b + i);
    }
    //b[0] = 17, b[1] = 31;
    
    dfs(0, 0, 0);
    
    //cout << a1 << endl;
    
    //cout << a0 << endl;
    
    //cout << a0 << " " << a1 << endl;
    
    a1 = -2 * b[0] - a1;
    
    assert(a1 % a0 == 0);
    
    long long s = a1 / a0;
    
    
    //cout << s << endl;
    
    for (int i = 0; i < n; ++i) {
        long long delta = 0;
        for (int to : g[i]) {
            delta -= b[to] - b[i];
        }
        delta += s * ((long long)g[i].size() - 2);
        if (i) cout << " ";
        delta = -delta;
        assert(delta % 2 == 0);
        long long res = delta / 2;
        cout << res;
    }
    cout << endl;
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
