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
const int maxn = 2005000;

int a[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int N, K;
    scanf("%d%d", &N, &K);
    forn(i, N) {
        scanf("%d", &a[i]);
    }
    forn(i, K) {
        a[N + i] = N + i + 1;
    }
    set<int> s;
    forn(i, K) {
        s.insert(a[i]);
    }
    forn(i, N) {
        if (*s.begin() != a[i]) {
            sort(a + i, a + i + K);
            break;
        } else {
            s.erase(a[i]);
            s.insert(a[i + K]);
        }
    }
    forn(i, N) {
        printf("%d ", a[i]);
    }
    printf("\n");

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
