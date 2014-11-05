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
const int maxn = 50000;

int k, n;
vi ps[maxn];
vi e[maxn];
int deg[maxn];

int id(const vi& p) {
    return lower_bound(ps, ps+n, p) - ps;
}

void gen() {
    forn(i, k) ps[0].pb(i);
    n = 1;
    while (1) {
        ps[n] = ps[n-1];
        if (next_permutation(all(ps[n]))) {
            ++n;
        } else {
            break;
        }
    }
    cout << "n = " << n << endl;
    forn(i, n) {
        vi t = ps[i];
        forn(j, k-1) {
            swap(t[j], t[j+1]);
            e[i].pb(id(t));
            swap(t[j], t[j+1]);
        }
        deg[i] = k-1;
    }
}

int b[maxn];
vi path;
int mx = 0;
bool go(int v) {
    path.pb(v);
    if ((int)path.size() > mx) {
        mx = path.size();
        cout << mx << endl;
    }
//     cout << string(path.size(), ' ');
//     forn(i, k) cout << ps[v][i] << " "; cout << endl;
    if ((int)path.size() == n) {
        return true;
    }
//     forn(i, n) if (!b[i] && deg[i] == 0) {
//         path.pop_back();
//         return false;
//     }
    b[v] = 1;
    forn(i, e[v].size()) --deg[e[v][i]];

    int mn = 100;
    forn(i, e[v].size()) if (!b[e[v][i]]) {
        mn = min(mn, deg[e[v][i]]);
    }
//     forn(i, e[v].size()) if (!b[e[v][i]] && deg[e[v][i]] == mn) {
//         if (go(e[v][i]))
//             return true;
//     }
    int order[10];
    forn(i, k-1) order[i] = i;
    random_shuffle(order, order + k-1);
    forn(I, e[v].size()) {
        int i = order[I];
        int to = e[v][i];
        if (!b[to] && deg[to] == mn) {
            if (go(to))
                return true;
        }
    }

    path.pop_back();
    b[v] = 0;
    forn(i, e[v].size()) ++deg[e[v][i]];

    return false;
}

int main() {
#ifdef HOME
#endif
//     freopen("perm.in", "r", stdin);
//     freopen("perm.out", "w", stdout);

    cin >> k;
    gen();
    cout << go(0) << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
