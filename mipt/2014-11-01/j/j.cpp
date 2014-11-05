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

typedef long long ll;

void Solution(int test);

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	int tests;
	scanf("%d", &tests);
	for (int test = 1; test <= tests; test++)
		Solution(test);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

int n;
int mod, F[4010], b[4010], S[4010][4010];
int add(int x, int y) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}
int mul(int x, int y) {
    return (i64) x*y%mod;
}
int sub(int x, int y) {
    x -= y;
    if (x < 0) return x+mod;
    if (x >= mod) assert(false);
    return x;
}

int pow(int x, int cnt)
{
//	fprintf(stderr, "pow -- x = %lld; cnt = %lld;\n", x, cnt);
	if (cnt == 0) return 1;
	if (cnt == 1) return x;
	int res = pow(x, cnt / 2);
    res = mul(res, res);
	if (cnt % 2 == 1) res = mul(res, x);
//	fprintf(stderr, "res = %lld;\n", res);
	return res;
}

inline int rev(int x)
{
	return pow(x, mod - 2);
}

void Solution(int test)
{
	fill(F, F + n + 1, 0);
	fill(b, b + n + 1, 0);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			S[i][j] = 0;
	F[0] = 1; F[1] = 1; F[2] = 2;
	scanf("%d%d", &n, &mod);
	for (int i = 3; i <= n; i++)
        F[i] = add(F[i-1], F[i-2]);
// 		F[i] = (F[i - 1] + F[i - 2]) % mod;
	for (int i = 0; i < n; i++)
		S[i][0] = 1;
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= i; j++)
            S[i][j] = add(S[i-1][j], mul(S[i-1][j-1], F[i]));
// 			S[i][j] = (S[i - 1][j] + S[i - 1][j - 1] * F[i]) % mod;
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);
	for (int i = n - 1; i >= 0; i--)
	{
		int res = 0, delta;
		for (int j = 0; j <= i; j++)
		{
            delta = mul(b[i-j], S[i][j]);
// 			delta = b[i - j] * S[i][j] % mod;
// 			if (j % 2 == 1) delta = (mod - delta) % mod;
            if (j%2) res = sub(res, delta);
            else res = add(res, delta);
// 			res = (res + delta) % mod;
		}
		b[i] = res;
	}
	for (int i = 0; i < n; i++)
	{
		S[0][i] = F[i + 1];
		int delta = 0;
		for (int j = 1; j <= i; j++)
		{
            delta = sub(F[i+1], F[j]);
            S[j][i] = mul(S[j-1][i], delta);
// 			delta = (F[i + 1] - F[j] + mod) % mod;
// 			S[j][i] = (S[j - 1][i] * delta) % mod;
		}
	}
	
	for (int i = n - 1; i >= 0; i--)
	{
        b[i] = mul(b[i], rev(S[i][i]));
// 		b[i] = (b[i] * rev(S[i][i])) % mod;
		int delta;
		for (int j = i - 1; j >= 0; j--)
		{
            delta = mul(b[i], S[j][i]);
            b[j] = sub(b[j], delta);

// 			delta = (b[i] * S[j][i]) % mod;
// 			b[j] = (b[j] + mod - delta) % mod;
		}
	}
//	for (int i = 0; i < n; i++)
//		fprintf(stderr, "%lld ", b[i]);
//	fprintf(stderr, "\n%d\n", n);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
        ans = add(ans, mul(pow(F[i], n+1), b[i-1]));
// 		ans = (ans + pow(F[i], (ll)(n + 1)) * b[i - 1]) % mod;
//		fprintf(stderr, "i = %d; ans = %lld\n", i, ans);
	}
	printf("%d\n", ans);
}

