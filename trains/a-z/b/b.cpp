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
const int maxn = 260;

int n, m;
vi e[maxn];
int b[maxn], mt[maxn];

void scan() {
    cin >> n >> m;
    forn(i, n) {
        int x;
        while (1) {
            cin >> x;
            if (x == 0) break;
            else e[i].pb(x-1);
        }
    }
}

bool kuhn(int v) {
    if (b[v]) return false;
    b[v] = 1;
    forn(i, e[v].size()) {
        int to = e[v][i];
        if (mt[to] == -1 || kuhn(mt[to])) {
            mt[to] = v;
            return 1;
        }
    }
    return 0;
}

int matching() {
    int res = 0;
    forn(i, m) mt[i] =-1;
    forn(i, n) {
        forn(j, n) b[j] = 0;
        res += kuhn(i);
    }
    cout << res << endl;
    forn(i, m) if (mt[i] != -1) cout << mt[i]+1 << " " << i+1 << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("pairs.in", "r", stdin);
    freopen("pairs.out", "w", stdout);
#endif

    scan();
    matching();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
