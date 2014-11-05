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

vector<int> nei[410], all[410], ced[2], ans;
map<string, int> places;
int num[410], col[410], n;
set<int> rooms[410];
int buf[1000];

void dfs(int v, int c)
{
	col[v] = c; ced[c].push_back(v);
	for (int i = 0; i < (int)all[v].size(); i++)
		if (col[all[v][i]] == -1)
			dfs(all[v][i], 1 - c);
		else assert(col[all[v][i]] != col[v]);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string s; int sz;
		cin >> s >> sz; nei[i].resize(sz);
		for (int j = 0; j < sz; j++)
		{
			cin >> nei[i][j];
			nei[i][j]--;
		}
		pair<map<string, int>::iterator, bool> val = places.insert( make_pair(s, places.size() + 1));
		num[i] = (*val.first).second; 
	}
	for (int i = 0; i < n; ++i) {
		nei[i].pb(i);
		sort(all(nei[i]));
	}
	forn(i, n) forn(j, i) if (num[i] != num[j]) {
		if (set_intersection(all(nei[i]), all(nei[j]), buf) != buf) {
			all[i].pb(j);
			all[j].pb(i);
		}
	}

	fill(col, col + n, -1);
	for (int i = 0; i < n; i++)
		if (col[i] == -1)
		{
			dfs(i, 0);
			int force = -1;
			for (int j = 0; j < 2; ++j) {
				for (auto x : ced[j]) {
					if (rooms[x].size() >= 3u) {
						force = j;
					}
				}
			}
			int x = (ced[0].size() < ced[1].size() ? 0 : 1);
			/*if (force != -1) {
				x = !force;
			}*/
			for (int j = 0; j < (int)ced[x].size(); j++)
				ans.push_back(ced[x][j]);
			ced[0].resize(0), ced[1].resize(0);
		}
	if (ans.size() == 0) ans.push_back(0);
	cout << ans.size() << endl;
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] + 1 << ' ';
	cout << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
