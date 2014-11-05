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

const int maxn = 50050;
int n;
i64 x[maxn], y[maxn];

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("area.ln", "r", stdin);
    freopen("area.out", "w", stdout);

    cin >> n;
    forn(i, n) cin >> x[i] >> y[i];
    x[n] = x[0];
    y[n] = y[0];
    i64 res = 0;
    forn(i, n) res += (y[i+1]-y[i]) * (x[i]+x[i+1]);
    res = abs(res);
    printf("%d.", (int)res/2);
    printf("%d", res%2?5:0);
    forn(i, 599) printf("0");
    printf("\n");


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
