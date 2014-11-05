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
const int maxn = 1000500;

i64 hex(int n) {
    return 3ll * n * n + 3ll * n + 1;
}

i64 h[600000];
int nh;

void genh() {
    for (int n = 0; hex(n) <= 1000000000000ll; ++n) {
        h[nh++] = hex(n);
    }
    //cerr << nh << " hexagons" << endl;
    //cerr << h[nh-1] - h[nh-2] << endl;
}


int dp[maxn];
//int d1[maxn];

inline void relax(int x, int s/*, int s1*/) {
    if (dp[x] > s/* || (dp[x] == s && d1[x] < s1)*/) {
        dp[x] = s;
       // d1[x] = s1;
    }
}

void compdp() {
    forn(i, maxn) dp[i] = 1000000000;
    dp[0] = 0;
    forn(i, maxn) {
        //assert(dp[i] - d1[i] <= 3);
   //     if (d1[i] == 0 && dp[i] == 3) cout << "no 0 " << i << endl;
        for (int j = 0; i + h[j] < maxn; ++j) {
            dp[i + h[j]] = min(dp[i + h[j]], dp[i] + 1);
            //relax(i + h[j], dp[i] + 1/*, d1[i] + (j == 0)*/);
        }
    }
    //cerr << "computed" << endl;
}

int greedy(i64 x, int it) 
{
    if (x < maxn) return dp[x];
    if (it == 3)
    {
        int pos = upper_bound(h, h + nh, x) - h - 1, ans = greedy(x, it - 1);
        for (int i = 0; i < 2 && pos - i >= 0; ++i)
            ans = min(ans, greedy(x - h[pos - i], it - 1) + 1);
        return ans;
    }
    int ans = 9;
    
    if (ans == 9 && x % 2 != 0 && x % 3 == 0) return 3;
    return ans;
}


void check() {
    //compdp();
    //cerr << "generated" << endl;
    int cnt = 0;
    fore(i, 70000, 1000000 - 1) {
        if (i % 1000 == 0) cerr << i << endl;
        if (dp[i] != greedy(i, 3)) {
            cout << "fail@" << i << ": " << dp[i] << " " << greedy(i, 3) << endl;
            assert(i % 3 == 0);
            if (++cnt == 1000) {
                break;
            }
        }
    }
}

int main() {
#ifdef HOME
     freopen("input.txt", "r", stdin);
#endif

    genh();
  //  compdp();
    //check();
    //cerr << "ok!" << endl;
    //return 0;
    
    //cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
    i64 x;
    while (1) {
        cin >> x;
        if (x == 0) {
            break;
        } else {
            if (x % 6 == 1)
            {
                printf("%d\n", binary_search(h, h + nh, x) ? 1 : 7);
            }
            else if (x % 6 == 2)
            {
                int ptr = upper_bound(h, h + nh, x) - h - 1; 
                bool fl = false;
                for (int j = 0; j < nh && h[j] <= x; ++j)
                {
                    i64 y = x - h[j];
                    while (ptr > 0 && h[ptr] > y) ptr--;
                    if (y - h[ptr] == 0) fl = true;
                }
                printf("%d\n", fl ? 2 : 8);
            }
            else
                printf("%d\n", (x - 1) % 6 + 1);
        }
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
