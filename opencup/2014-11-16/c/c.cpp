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
#include <cstring>
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

const int maxN = 17;
int w[1 << maxN], d[1 << maxN];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	memset(w, 0x3F, sizeof(w));
	memset(d, 0x3F, sizeof(d));

	//const int inf = w[0];
	//printf("%d\n", w[0]);

	//printf("%d\n%d\n", 2 * 1000000 * 16, w[0]);

	int nShops, nProducts;
	scanf("%d %d", &nShops, &nProducts);

	for (int i = 0; i < nShops; i++)
	{
		int base;
		scanf("%d", &base);
		
		vector<int> c(nProducts);
		for (int j = 0; j < nProducts; j++)
		{
			scanf("%d", &c[j]);
		}
		
		for (int mask = 0; mask < (1 << nProducts); mask++)
		{
			int cost = 0;
			for (int i = 0; i < nProducts; i++)
				if (mask & (1 << i))
					cost += c[i];
			w[mask] = min(w[mask], cost + base);
		}
	}
	
	//for (int mask = 0; mask < (1 << nProducts); mask++)
	//	printf("%d - %d\n", mask, w[mask]);
	
	d[0] = 0;
	for (int mask = 0; mask < (1 << nProducts); mask++)
	{
		int paired = (~mask & ((1 << nProducts) - 1));
		
		for (int submask = paired; submask > 0; submask = (submask - 1) & paired)
		{
			d[mask | submask] = min(d[mask | submask], d[mask] + w[submask]);
			//printf("mask %d submask %d\n", mask, submask);
		}
	}
	
	printf("%d\n", d[(1 << nProducts) - 1]);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
