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
const int maxn = 105;

int n, k;
int pos[maxn];
int rpos[maxn];

int dp[maxn][1<<20];
char buf[maxn];

void scan() {
    cin >> n;
    cin >> buf;
    k = 0;
    forn(i, n) {
        if (buf[i] == '1') {
            rpos[i] = k;
            pos[k++] = i;
        } else {
            rpos[i] = -1;
        }
    }
}

bool go(int move, int mask) {
    if (mask == 0) {
        return false;
    }
    int& res = dp[move][mask];
    if (res == -1) {
        forn(t, k) {
            if (mask & (1<<t)) {
                int nmask = mask ^ (1<<t);
                int rp = rpos[move];
                if (rp != -1 && nmask & (1<<rp)) {
                    nmask ^= (1<<rp);
                }
                if (!go(move + 1, nmask)) {
                    return (res = true);
                }
            }
        }
        return (res = false);
    }
    return res;
}

bool solve() {
    forn(i, n) forn(mask, 1<<k) {
        dp[i][mask] = -1;
    }
    return go(0, (1<<k) - 1);
}

int main() {
#ifdef HOME
    freopen("g1.in", "r", stdin);
    freopen("out1.out", "w", stdout);
#endif

    int t;
    cin >> t;
    forn(i, t) {
        cerr << "test " << i << " of " << t << endl;
        scan();
        if (!solve()) {
            cout << "Betka" << endl;
        } else {
            cout << "Adam" << endl;
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
