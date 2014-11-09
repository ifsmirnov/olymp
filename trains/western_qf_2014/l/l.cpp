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

typedef long long ll;

const ll INF = 1000000000000ll;

int n, m;
vector<pair<int, int> > all[100100];
ll dp[100100];
priority_queue<pair<ll, int> > heap;
bool used[100100];

void dijkstra()
{
	fill(used, used + n, false);
	fill(dp, dp + n, INF); dp[0] = 0;
	while (!heap.empty()) heap.pop();
	for (int i = 0; i < n; i++)
		heap.push(make_pair(-dp[i], i));
	while (true)
	{
		while (!heap.empty() && used[heap.top().second]) heap.pop();
		if (heap.empty()) break;
		int mn = heap.top().second;
//		cerr << "cerr " << mn << ' ' << dp[mn] << endl;
		heap.pop(); used[mn] = true;
		if (dp[mn] == INF) break;
		for (int i = 0; i < (int)all[mn].size(); i++)
		{
			int v = all[mn][i].first;
			if (!used[v] && dp[v] > dp[mn] + all[mn][i].second)
			{
				dp[v] = dp[mn] + all[mn][i].second;
				heap.push(make_pair(-dp[v], v));
			}
		}
	}
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		u--; v--;
		all[u].push_back(make_pair(v, w));
	}

	dijkstra();
	if (dp[n - 1] == INF) printf("Infinity\n");
	else printf("%lld\n", dp[n - 1]);
	
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
