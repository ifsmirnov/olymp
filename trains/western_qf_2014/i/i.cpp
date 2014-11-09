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

int k, n, mn[1010][1010], a[1010][1010];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
	freopen("intelligent.in", "r", stdin);
	freopen("intelligent.out", "w", stdout);

	scanf("%d%d", &k, &n);
	for (int i = 0; i < n; i++)
		mn[i][0] = mn[i][1] = inf;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a[i][j]);
			if (mn[j][0] > a[i][j])
				mn[j][1] = mn[j][0], mn[j][0] = a[i][j];
			else if (mn[j][1] > a[i][j])
				mn[j][1] = a[i][j];
		}
	int best = 0;
	for (int i = 0; i < n; i++)
	{
		int profit = min(mn[i][1], 2 * mn[i][0]) - mn[i][0];
		if (profit > best) best = profit;
	}
	for (int i = 0; i < n; i++)
		best += mn[i][0];
	printf("%d\n", best);
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
