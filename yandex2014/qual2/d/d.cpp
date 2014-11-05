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

const int maxn = 100500;
int n;
int a[maxn];

int inv(const vi& a) {
    int res = 0;
    forn(i, a.size()) forn(j, i) {
        res += a[i] < a[j];
    }
    return res;
}

void out(const vi& a) {
    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
}

map<int, vi> d;

void gen_all(int n) {
    vi a(n);
    forn(i, n) a[i] = i;
    do {
        int t = inv(a);
        if (d[t].empty()) {
            d[t] = a;
        }
    } while (next_permutation(all(a)));
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    int n, k;
    cin >> k;
    if (k == 0) {
        cout << "1\n1\n";
        return 0;
    }
    n = 0;
    while (n*(n-1)/2 < k) ++n;
    int t = k-((n-1)*(n-2)/2)+1;
    printf("%d\n", n);
    printf("%d ", t);
    for (int i = n; i >= 1; --i) if (i != t) {
        printf("%d ", i);
    }
    printf("\n");
//     cin >> n;
//     gen_all(n);
//     for (auto p : d) {
//         cout << p.fi << ": ";
//         out(p.se);
//     }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
