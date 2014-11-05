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
const int maxn = 15050000;

int tr[3][maxn];
int tc;
int b[maxn];
int can[2][maxn];

int xorTrees(int v, int u) {
    if (v == -1 && u == -1) {
        return -1;
    }
    int node = tc++;
    can[0][node] = can[1][node] = -1;
    tr[0][node] = xorTrees(tr[0][v], tr[0][u]);
    tr[1][node] = xorTrees(tr[1][v], tr[1][u]);
    tr[2][node] = -1;
    b[node] = b[v] ^ b[u];
    return node;
}

int buildTernary(int v) {
    if (tr[0][v] == -1 && tr[1][v] == -1) {
        return -1;
    }
    if (tr[2][v] != -1) {
        return tr[2][v];
    }
    tr[2][v] = xorTrees(tr[0][v], tr[1][v]);
    buildTernary(tr[2][v]);
}

bool ifCan(int v, int x) {
    if (v == -1) {
        return x == 0;
    }
    if (can[x][v] != -1) {
        return can[x][v] == 1;
    }
    forn(i, 3) {
        if (!ifCan(tr[i][v], x ^ b[v] ^ 1)) {
            return can[x][v] = 1;
        }
    }
    return can[x][v] = 0;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int N;
    cin >> N;
    forn(i, N) {
        cin >> tr[0][i] >> tr[1][i] >> b[i];
        //b[i] = 1;
        --tr[0][i];
        --tr[1][i];
        tr[2][i] = -1;
        can[0][i] = can[1][i] = -1;
    }
    tc = N;
    forn(i, N) {
        buildTernary(i);
    }
    forn(i, N) {
        cout <<  (ifCan(i, 0) ? "Ksusha" : "Sasha") << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
