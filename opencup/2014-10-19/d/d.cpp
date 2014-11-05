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
typedef unsigned u32;
const int inf = 1e9+100500;

u32 input[1<<16];
u32 output[1<<16];
u32 dp[1<<16][20];

void sum_in_submasks(int n) {
	for (int i = 0; i < (1 << n); i++)
		for (int j = 0; j <= n; j++)
			dp[i][j] = 0;
    forn(mask, 1<<n) {
        dp[mask][0] = input[mask];
        forn(k, n) {
            dp[mask][k+1] += dp[mask][k];
            if (mask&(1<<k)) {
                dp[mask][k+1] += dp[mask^(1<<k)][k+1];
            }
        }
        output[mask] = dp[mask][n];
    }
}

void reverse_sum_in_submasks(int n) {
	for (int i = 0; i < (1 << n); i++)
		for (int j = 0; j <= n; j++)
			dp[i][j] = 0;
    forn(mask, 1<<n) {
        dp[mask][0] = 0;
        forn(k, n) {
            dp[mask][k+1] += dp[mask][k];
            if (mask&(1<<k)) {
                dp[mask][k+1] += dp[mask^(1<<k)][k+1];
            }
        }
        output[mask] = input[mask] - dp[mask][n];
        forn(k, n+1) {
            dp[mask][k] += output[mask];
        }
    }
}

u32 a, b, cur = 0;
u32 nextRand16()
{
	cur = cur * a + b;
	return cur >> 16;
}

int n, t;
u32 h[1 << 16];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
	freopen("convolution.in", "r", stdin);
	freopen("convolution.out", "w", stdout);
#endif

    cin >> n >> t >> a >> b;
    for (int test = 0; test < t; test++)
    {
		for (int i = 0; i < (1 << n); i++)
		{
			input[i] = nextRand16();
//			cout << input[i] << ' ';
		}
//		cout << endl;
		sum_in_submasks(n);
		for (int i = 0; i < (1 << n); i++)
			h[i] = output[i];
		for (int i = 0; i < (1 << n); i++)
		{
			input[i] = nextRand16();
//			cout << input[i] << ' ';
		}
//		cout << endl;
		sum_in_submasks(n);
//		cout << h[0] << ' ' << output[0] << endl;
		for (int i = 0; i < (1 << n); i++)
			input[i] = h[i] * output[i];
//		cout << "asdasd " << input[0] << endl;
		reverse_sum_in_submasks(n);
		u32 ans = 0;
		for (u32 i = 0; i < (1 << n); i++)
		{
			ans += output[i] * (i + 1);
//			cout << output[i] << ' ';
		}
//		cout << endl;
		cout << ans << endl;
	}
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
