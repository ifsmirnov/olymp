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

const int maxn = 1<<20;
int a[maxn];

char buf[maxn + 1], *s = buf;

void gen(int n) {
    forn(i, n-1) *s++ = '0';
    int x = 0;
    forn(i, (1<<n)) {
        x = x&((1<<n)-1);
//         if (!a[(x*2+1)&((1<<n)-1)]) {
        if (!a[(x*2+1)&((1<<n)-1)]) {
            *s++ = '1'; x = x*2+1;
        } else {
            *s++ = '0'; x = x*2;
        }
        x = x&((1<<n)-1);
        a[x] = 1;
    }
    forn(i, 1<<n) assert(a[i]);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int n;
    scanf("%d", &n);
    gen(n);
    printf("%s\n", buf);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
