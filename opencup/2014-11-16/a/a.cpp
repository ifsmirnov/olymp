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

int n, m;
vector<pair<pair<int, int>, int> > all[21];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		int a, b, d; scanf("%d%d%d", &a, &b, &d); d--;
		all[d].push_back(make_pair(make_pair(a, b), i + 1));
	}
	for (int i = 0; i < m; i++)
	{
		if (all[i].size() < 2) { printf("NIE\n"); continue; }
		int best = 0;
		for (int j = 1; j < all[i].size(); j++)
			if (all[i][j].first > all[i][best].first) best = j;
		int left = -1;
		for (int j = 0; j < all[i].size(); j++)
			if (all[i][j].first.second < all[i][best].first.first)
			{
				left = j;
				break;
			}
		if (left == -1) printf("NIE\n");
		else printf("TAK %d %d\n", all[i][left].second, all[i][best].second);
	}

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
