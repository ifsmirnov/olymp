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


int n, m, all[1000100];
ll ans[1000100];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
	freopen("halloween.in", "r", stdin);
	freopen("halloween.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		int x; scanf("%d", &x);
		all[x]++;
	}
	fill(ans, ans + 1000100, -1);
	ll sum = 0;
	for (int i = 0; i < m; i++)
	{
		int x; scanf("%d", &x);
		if (ans[x] != -1) sum += ans[x];
		else
		{
			ans[x] = 0;
			ll cnt = 1;
			for (int i = x; i <= 1000000; i += x, cnt++)
				ans[x] += cnt * (ll)all[i];
			sum += ans[x];
		}
		//printf("cerr %lld\n", ans[x]);
	}
	printf("%lld\n", sum);
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
