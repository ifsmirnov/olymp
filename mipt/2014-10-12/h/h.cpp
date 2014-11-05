#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
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

int good[1<<10];

void fill_mask() {
    forn(mask, 1<<10) {
        int x = 0;
        forn(i, 10) {
            if (mask&(1<<i)) {
                x = __gcd(x, i);
            }
        }
        good[mask] = x == 1;
    }
}

int cnt[10];
int mask;

int n;
char s[maxn];
int k;

void addc(int c) {
    if (!(cnt[c]++)) {
        mask |= (1<<c);
    }
}
void delc(int c) {
    --cnt[c];
    if (!cnt[c]) {
        mask &= ~(1<<c);
    }
}

bool solve() {
    forn(i, 10) cnt[i] = 0;
    mask = 0;
    n = strlen(s);
    forn(i, k-1) {
        addc(s[i]-'0');
    }
//     forn(j, 10) cout << cnt[j] << " "; cout << endl; cout << endl;
    for (int i = k-1; i < n; ++i) {
        addc(s[i]-'0');
//         forn(j, 10) cout << cnt[j] << " "; cout << endl;
        if (!good[mask]) {
            return false;
        }
        delc(s[i-k+1]-'0');
//         forn(j, 10) cout << cnt[j] << " "; cout << endl; cout << endl;
    }
    return true;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("numbers.in", "r", stdin);
    freopen("numbers.out", "w", stdout);
    fill_mask();

    for (int t = 1;; ++t) {
        scanf("%s%d", s, &k);
        if (k == 0) {
            break;
        }
        printf("Number %d is %scrooked.\n", t, solve() ? "" : "not ");
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
