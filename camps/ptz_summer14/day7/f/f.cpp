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
const int maxn = 1000500;

int n;
int a[maxn];
i64 s[maxn];
int even[maxn], odd[maxn];
int ne, no;

void scan() {
    scanf("%d", &n);
    forn(i, n) scanf("%d", &a[i]);
}

void solve() {
    sort(a, a+n, greater<int>());
    forn(i, n) {
        s[i] = a[i];
        if (i) s[i] += s[i-1];
        if (a[i]%2) odd[no++] = i;
        else even[ne++] = i;
    }
    even[ne] = maxn;
    odd[no] = maxn;

    int q;
    scanf("%d", &q);
    forn(i, q) {
        int k;
        scanf("%d", &k);
        --k;
        i64 res = s[k];
        if (res%2) {
            printf("%lld\n", res);
            continue;
        }
        res = -1;
        int pe = upper_bound(even, even + ne, k) - even;
        int po = upper_bound(odd, odd + no, k) - odd;
//         cout << "po,pe: " << po << " " << pe << endl;
        if (even[pe] != maxn && po != 0) {
//             cout << "Wer" << endl;
            res = max(res, s[k] + a[even[pe]] - a[odd[po-1]]);
        }
        po = upper_bound(odd, odd + no, k) - odd;
        pe = upper_bound(even, even + ne, k) - even;
//         cout << "pe,po: " << pe << " " << po << endl;
        if (odd[po] != maxn && pe != 0) {
            res = max(res, s[k] + a[odd[po]] - a[even[pe - 1]]);
        }
        printf("%lld\n", res);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
