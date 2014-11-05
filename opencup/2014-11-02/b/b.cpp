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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d %d", &n, &m);
	
	map<int, int> nObjects;
	
	vector<pii> types(n);
	for (int i = 0; i < n; i++)
	{
		int cost, nn;
		scanf("%d %d", &cost, &nn);
		nObjects[cost] += nn;
	}
	
	for (auto it: nObjects)
		types.push_back(make_pair(it.first, it.second));

	n = (int)types.size();
	
	int total = 0;
	
	vector<int> p(n);
	for (int i = 0; i < n; i++)
	{
		p[i] = (i ? p[i - 1] : 0) + types[i].second;
		total += types[i].second;
	}
		
	ll totalLess = 0, totalEqual = 0, totalGreater = 0;
	for (int i = 0; i < m; i++)
	{
		int cost, nObjects;
		scanf("%d %d", &cost, &nObjects);
		
		auto it = lower_bound(types.begin(), types.end(), make_pair(cost, -1));
		
		int nLess = 0;
		if (it != types.begin())
			nLess = p[it - 1 - types.begin()];
		
		int nEqual = 0;
		if (it != types.end() && it->first == cost)
			nEqual = it->second;
		
		int nGreater = total - nLess - nEqual;
		
		totalLess += nLess * (ll)nObjects;
		totalEqual += nEqual * (ll)nObjects;
		totalGreater += nGreater * (ll)nObjects;
	}
	
	printf("%lld %lld %lld\n", totalGreater, totalEqual, totalLess);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
