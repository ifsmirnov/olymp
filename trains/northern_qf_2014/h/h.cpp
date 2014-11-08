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

int x[2020][3], y[2020][3], z[2020][3], num[2020][3], sz = 0, n, tag[6600], tg = 0;
pair<int, int> pos[6600];
vector<int> tri[6600], trivs[2200], path;
map<pair<int, int>, int> all;

bool dfs(int x, int limit)
{
//	cerr << "cerr " << x << ' ' << limit << ' ' << tri[x].size() << endl;
	if (x == sz - 2) path.clear();
	path.push_back(x); tag[x] = tg;
	if (x == sz - 1) return true;
	for (int i = 0; i < (int)tri[x].size(); i++)
		for (int j = 0; j < (int)trivs[tri[x][i]].size(); j++)
		{
			int u = trivs[tri[x][i]][j];
//			cerr << "cerr " << u << endl;
			if (z[pos[u].first][pos[u].second] > limit || tag[u] == tg) continue;
			if (dfs(u, limit)) return true;
		}
	path.pop_back();
	return false;
}

int sign(ll x)
{
	if (x == 0) return 0;
	return (x < 0 ? -1 : 1);
}

ll prod(int i1, int j1, int i2, int j2, int i3, int j3)
{
	return llabs((ll)(x[i2][j2] - x[i1][j1]) * (ll)(y[i3][j3] - y[i1][j1]) - (ll)(x[i3][j3] - x[i1][j1]) * (ll)(y[i2][j2] - y[i1][j1]));
};

bool isInside(int pt, int pi, int pj)
{
	ll sum = 0, area = prod(pt, 0, pt, 1, pt, 2);
	for (int i = 0; i < 3; i++)
		sum += prod(pi, pj, pt, i, pt, (i + 1) % 3);
	return (sum == area);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf("%d%d%d", &x[i][j], &y[i][j], &z[i][j]);
			map<pair<int, int>, int>::iterator it = all.find(make_pair(x[i][j], y[i][j]));
			if (it == all.end())
			{
				all[make_pair(x[i][j], y[i][j])] = sz;
				num[i][j] = sz; pos[sz] = make_pair(i, j);
				tri[sz].push_back(i);
				sz++;
			}
			else
			{
				num[i][j] = it->second;
				tri[num[i][j]].push_back(i);
			}
			trivs[i].push_back(num[i][j]);
		}
	}

	{
		scanf("%d%d%d", &x[n][0], &y[n][0], &z[n][0]);
//		cerr << "cerr " << x[n][0] << ' ' << y[n][0] << endl;
		pos[sz] = make_pair(n, 0), num[n][0] = sz;
		for (int i = 0; i < n; i++)
		{
			if (isInside(i, n, 0))
			{
				tri[sz].push_back(i);
				trivs[i].push_back(sz);
				break;
			}
		}
		sz++;
	}
	{
		scanf("%d%d%d", &x[n][1], &y[n][1], &z[n][1]);
		pos[sz] = make_pair(n, 1), num[n][1] = sz;
		for (int i = 0; i < n; i++)
		{
			if (isInside(i, n, 1))
			{
				tri[sz].push_back(i);
				trivs[i].push_back(sz);
				break;
			}
		}
		sz++;
	}

	int lt = max(z[n][0], z[n][1]), rt = 1000000;
//	cerr << "cerr " << sz << endl;
	while (lt < rt)
	{
		tg++;
		int mid = (lt + rt) / 2;
		if (dfs(sz - 2, mid)) rt = mid;
		else lt = mid + 1;
	}
	tg++;
	dfs(sz - 2, lt);
	printf("%d\n", (int)path.size());
	for (int i = 0; i < (int)path.size(); i++)
		printf("%d %d %d\n", x[pos[path[i]].first][pos[path[i]].second], y[pos[path[i]].first][pos[path[i]].second], z[pos[path[i]].first][pos[path[i]].second]);
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
