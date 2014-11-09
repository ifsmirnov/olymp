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

int n, a, b;
long double c[55][55];
long double p, dp[55][55][55], f[55];

long double sumg(long double x, int N)
{
	return ((long double)1.0 - powl(x, (long double)N)) / ((long double)1.0 - x);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	cin >> n >> a >> b >> p;
	for (int L = 0; L <= 50; L++)
		for (int N = 0; N <= n; N++)
			for (int K = 0; K <= N; K++)
				if (L == 0 || N == 0) dp[L][N][K] = 1.0;
				else dp[L][N][K] = (long double)(N - K) / (long double)N * (p * dp[L - 1][N - 1][K] + ((long double)1.0 - p) * dp[L - 1][N][K]);
	f[0] = 1.0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = a; j <= b; j++)
			f[i] += dp[j][n][i];
		f[i] /= (long double)(b - a + 1);
	}
	
	for (int i = 0; i <= n; i++)
		c[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	
	int N = 1000000000;
	long double pn = 0;
	for (int i = 0; i <= n; i++)
		if (i & 1) pn -= (long double)c[n][i] * powl(f[i], (long double)N);
		else pn += (long double)c[n][i] * powl(f[i], (long double)N);
	pn = pn * (long double)N;
	pn = pn - (long double)N;
	for (int i = 1; i <= n; i++)
		if (i & 1) pn += (long double)c[n][i] * sumg(f[i], N);
		else pn -= (long double)c[n][i] * sumg(f[i], N);
	cout.precision(12); cout << fixed << pn << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
