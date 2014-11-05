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

int n = 26, m, tag[30], tg = 0, onstag[30], otg = 0, dp[30], fr[30];
char c[2];
bool all[30][30];
vector<int> path, ans, cycle;

bool dfs(int v)
{
	path.push_back(v);
	tag[v] = tg; onstag[v] = otg;
//	fprintf(stderr, "%d %d\n", v, path.size());
	for (int i = 0; i < n; i++)
	{
		if (!all[v][i]) continue;
//		fprintf(stderr, "asd %d %d\n", i, tag[i] == tg);
		if (onstag[i] == otg)
		{
			while (path.back() != i)
				cycle.push_back(path.back()), path.pop_back();
			cycle.push_back(i);
			return true;
		}
		if (tag[i] == tg) continue;
		if (dfs(i))
			return true;
	}
	onstag[v] = otg - 1;
	path.pop_back();
	return false;
}

int count(int v)
{
	if (dp[v] != -1) return dp[v];
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		if (!all[v][i]) continue;
		int val = 1 + count(i);
		if (res < val)
			res = val, fr[v] = i;
	}
	dp[v] = res;
	return res;
}

void Solution(int test)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			all[i][j] = true;
	scanf("%d", &m);
//	fprintf(stderr, "%d\n", test);
	for (int i = 0; i < m; i++)
	{
		scanf("%s", c);
		all[(int)(c[0] - 'a')][(int)(c[1] - 'a')] = false;
	}
	cycle.clear();
	ans.clear();
	tg++;
	for (int i = 0; i < n; i++)
	{
		otg++;
		path.clear();
		if (dfs(i)) break;
	}
//	fprintf(stderr, "%d %d\n", test, cycle.size());
	if (cycle.size() > 0)
	{
		reverse(cycle.begin(), cycle.end());
		ans.resize(39);
		for (int i = 0; i < 39; i++)
			ans[i] = cycle[i % cycle.size()];
	}
	else
	{
		fill(dp, dp + n, -1);
		fill(fr, fr + n, -1);
		for (int i = 0; i < n; i++)
			if (dp[i] == -1) dp[i] = count(i);
		int mx = 0;
		for (int i = 0; i < n; i++)
			if (dp[i] > dp[mx]) mx = i;
		int cur = mx;
		while (cur != -1)
			ans.push_back(cur), cur = fr[cur];
	}
	m = (ans.size() + 1) / 2;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%c", (char)(ans[i + j]) + 'a');
		printf("\n");
	}
}

