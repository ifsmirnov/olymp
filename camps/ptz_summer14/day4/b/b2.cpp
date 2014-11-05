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

int n, m, deg[1000100];
vector<pii> v;

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b), --a, --b;
        deg[a]++, deg[b]++;
    }
    for (int i = 0; i < n; ++i)
        v.pb(mp(deg[i] + 1, i));
    sort(all(v));
//     for (int i = 0; i < n; ++i)
//         cout << v[i].first << " " << v[i].second << endl;
    for (size_t i = 0; i < v.size(); ++i)
        if (v[i].first == n - i)
        {
            cout << v[i].second + 1 << '\n';
            return 0;
        }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
