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

i64 dp[20][1500];
int happy[1500];

int sqs(int x) {
    int s = 0;
    while (x) {
        s += (x % 10) * (x % 10);
        x /= 10;
    }
    return s;
}

bool dfs(int x) {
    if (happy[x] != -1) {
        return happy[x] == 1;
    }
    happy[x] = -2;
    happy[x] = (dfs(sqs(x)) ? 1 : 0);
    return happy[x] == 1;
}

i64 getS(i64 N) {
    int add = 0;
    i64 ans = 0;
    while (N) {
        i64 q = 1;
        int p = 0;
        while (q <= N / 10) {
            q *= 10;
            ++p;
        }
        //cerr << '!' << N << '\n';
        for (int d = 0; d < 10; ++d) {
            if (q * (d + 1) <= N) {
                forn(s, 1500) {
                    int ss = s + d * d + add;
                    if (ss >= 1500) continue;
                    if (happy[ss] && dp[p][s]) {
                        //cerr << p << ' ' << s << ' ' << dp[p][s] << '\n';
                        ans += dp[p][s];
                    }
                }
            } else {
                N -= d * q;
                add += d * d;
                break;
            }
        }
    }
    return ans;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    dp[0][0] = 1;
    for (int i = 0; i <= 18; ++i) {
        forn(s, 1500) {
            forn(d, 10) {
                int ss = s + d * d;
                if (ss >= 1500) continue;
                dp[i + 1][ss] += dp[i][s];
            }
        }
    }
    
    forn(i, 1500) happy[i] = -1;
    happy[1] = 1;
    forn(i, 1500) {
        dfs(i);
        //if (happy[i]) cout << i << '\n';
    }
    i64 L, R;
    while (true) {
        cin >> L >> R;
        if (!L) break;
        //cout << getS(L) << '\n';
        //cout << getS(R + 1) << '\n';
        cout << R - L + 1 - (getS(R + 1) - getS(L)) << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
