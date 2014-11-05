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

// struct edge
// {
//     int to, w;
//     
//     edge(int nto, int nw): to(nto), w(nw) {}
// };
// 
// int n, m, used[maxn];
// vector<edge> edges;
// vector<int> tree[maxn];
// 
// vector<int> path;
// 
// inline int dfs(int u, int v)
// {
//     if (u == v) 
//     {
//         path.pb(v);
//         return 0;
//     }
//     if (used[v]) return -1;
//     used[v] = 1;
//     for (size_t i = 0; i < tree[u].size(); ++i)
//     {
//         int id = tree[u][i];
//         int x = dfs(e.to, v);
//         if (x != -1)
//         {
//             path.pb(u);
//             return x + 1;
//         }
//     }
//     return -1;
// }
// 
// inline int unite(int u, int v)
// {
//     path.clear();
//     fill(used, used + n, 0);
//     int res = dfs(u, v);
//     for (size_t i = 0; i < path.size(); ++i)
//                 
// }

int main() 
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    srand(time(0));
    int n, m;
    n = 100000;
    m = 200000;
    cout << n << " " << m << endl;
    for (int i = 0; i < m; ++i)
    {
        int a = rand() % n, b = rand() % n, c = rand() % 1000000000 + 1;
        cout << a+1 << " " << b+1 << " " << c << "\n";
    }
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
