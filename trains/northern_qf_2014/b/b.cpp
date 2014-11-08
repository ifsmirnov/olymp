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
#endif

	int baseHealth, nSlots, nDirect, nPercent;
	scanf("%d %d %d %d", &baseHealth, &nSlots, &nDirect, &nPercent);
	
	vector<pair<int, int>> d(nDirect);
	for (int i = 0; i < nDirect; i++)
	{
		scanf("%d", &d[i].first);
		d[i].second = i;
	}
	sort(d.rbegin(), d.rend());
		
	vector<pair<int, int>> p(nPercent);
	for (int i = 0; i < nPercent; i++)
	{
		scanf("%d", &p[i].first);
		p[i].second = i;
	}
	sort(p.rbegin(), p.rend());
	
	ll pSum = 0;
	ll healthSum = 0;
	
	int np = 0;
	for (int i = 0; i < min(nSlots, nPercent); i++)
	{
		pSum += p[i].first;
		np++;
	}
	
	ll maxHealth = 0;
	int useDirect = 0, usePercent = 0;
	
	for (int i = 0; i <= nDirect; i++)
	{
		if (i > nSlots) break;
		
		// use first i in directs
		
		while (np + i > nSlots)
		{
			np--;
			pSum -= p[np].first;
		}
		
		ll ansHealth = (baseHealth + healthSum) * (ll)(100 + pSum);
		if (ansHealth > maxHealth)
		{
			maxHealth = ansHealth;
			useDirect = i;
			usePercent = np;
		}
		
		// ...
		if (i != nDirect)
			healthSum += d[i].first;
	}
	
	printf("%d %d\n", useDirect, usePercent);
	for (int i = 0; i < useDirect; i++)
		printf("%d ", d[i].second + 1);
	printf("\n");
	for (int i = 0; i < usePercent; i++)
		printf("%d ", p[i].second + 1);
	printf("\n");

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
