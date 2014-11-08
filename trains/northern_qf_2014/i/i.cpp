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

int n, m, par[60], son[60][2], num[60], dp[60];
char tp[60];
vector<pair<int, int> > sw[60], all;

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> tp[i] >> par[i];
		if (son[par[i]][0] == 0) son[par[i]][0] = i;
		else son[par[i]][1] = i;
		if (tp[i] == 'p')
		{
			char c; cin >> c;
			num[c - 'a'] = i;
		}
	}

	for (int i = 0; i < 26; i++)
		if (num[i] != 0)
		{
			int cur = num[i];
			while (cur != 0)
				dp[i]++, cur = par[cur];
		}
	
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int ent; char dst;
		cin >> ent >> dst;
		int val = num[dst - 'a'];
		int cur = val, arr = dp[dst - 'a'] + ent;
		while (cur != 0)
		{
			arr--;
			if (son[par[cur]][1] != 0)
			{
				if (son[par[cur]][0] == cur)
					sw[par[cur]].push_back(make_pair(arr, 0));
				else
					sw[par[cur]].push_back(make_pair(arr, 1));
			}
			cur = par[cur];
		}
	}
	
	for (int i = 1; i <= n; i++)
	{
		if (son[i][1] == 0) continue;
		int st = (son[i][0] < son[i][1] ? 0 : 1);
		sort(sw[i].begin(), sw[i].end());
		for (int j = 0; j < (int)sw[i].size(); j++)
			if (sw[i][j].second != st)
				all.push_back(make_pair(sw[i][j].first, i)), st = 1 - st;
	}
	sort(all.begin(), all.end());
	cout << all.size() << endl;
	for (int i = 0; i < (int)all.size(); i++)
		cout << all[i].second << ' ' << all[i].first << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
