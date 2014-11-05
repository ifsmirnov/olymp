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

const int MD = 1000000007;
int n, a, b, dp[2][310][2];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d%d", &n, &a, &b); a++; b++;
	for (int i = 0; i < 2; i++)
		fill(dp[i][0], dp[i][0] + a, 0),
		fill(dp[i][1], dp[i][1] + b, 0);
	dp[0][1][1] = 1;
	dp[0][1][0] = 1;
	int sn = 0, cnt = 2;
	while (cnt <= n)
	{
		sn = 1 - sn;
		dp[sn][1][1] = 0;
		for (int i = 0; i < a; i++)
		{
			dp[sn][1][1] += dp[1 - sn][i][0];
			if (dp[sn][1][1] >= MD) dp[sn][1][1] -= MD;
		}
		for (int i = 2; i < b; i++)
			dp[sn][i][1] = dp[1 - sn][i - 1][1];
		dp[sn][1][0] = 0;
		for (int i = 0; i < b; i++)
		{
			dp[sn][1][0] += dp[1 - sn][i][1];
			if (dp[sn][1][0] >= MD) dp[sn][1][0] -= MD;
		}
		for (int i = 2; i < a; i++)
			dp[sn][i][0] = dp[1 - sn][i - 1][0];
		cnt++;
		/*for (int i = 0; i < a; i++)
			fprintf(stderr, "%d ", dp[sn][i][0]);
		fprintf(stderr, "\n");
		for (int i = 0; i < b; i++)
			fprintf(stderr, "%d ", dp[sn][i][1]);
		fprintf(stderr, "\n");*/
	}
	int sum = 0;
	for (int i = 0; i < a; i++)
	{
		sum += dp[sn][i][0];
		if (sum >= MD) sum -= MD;
	}
	for (int i = 0; i < b; i++)
	{
		sum += dp[sn][i][1];
		if (sum >= MD) sum -= MD;
	}
	printf("%d\n", sum);
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
