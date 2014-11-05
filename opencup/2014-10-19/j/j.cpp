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


ll minAns = -1;
ll minA = 0, minB = 0, minC = 0, minD = 0;

inline void trySolution(ll a, ll b, ll c, ll d)
{
	if (a + b + c + d < minAns || minAns == -1)
	{
		minAns = a + b + c + d;
		minA = a;
		minB = b;
		minC = c;
		minD = d;
	}
}

int solve(long long s)
{
	minAns = -1;
	
	int maxSmall = 1;
	
	/*int sqS = (int)sqrtl(s);
	int sqStep = min(100000, sqS);
	
	maxSmall = (int)sqrtl(2 * 1e8 / sqStep);
	
	for (int c = 1; c <= maxSmall; c++)
		for (int d = c; d <= maxSmall; d++)
		{
			long long needFac = s - c * d;
			if (needFac < 1) continue;
			
			//printf("fac %lld\n", needFac);
			
			int until = sqS + sqStep;
			if (until > needFac)
				until = needFac;
			
			for (int i = max(sqS - sqStep, 1); i <= sqS + 1; i++)
				if (needFac % i == 0)
				{
					trySolution(i, needFac / i, c, d);
				}
		}
	*/
	ll bd = max(s - 1000000, 1ll);
	for (ll d = 0; ; d++)
	{
		if (d % (1<<10) == 0) {
			if ((double)clock()/CLOCKS_PER_SEC > 1.5) {
				break;
			}
		}
		long double d2 = (long double)d / 2;
		ll x = (ll)(sqrtl(s + d2 * d2) - d2);
		while (x * (x + d) >= bd)
		{
			int val = s - x * (x + d);
			for (int div = (int)sqrtl(val + 0.5); div > 0; div--)
				if (val % div == 0)
				{
					trySolution(x, x + d, div, val / div);
					break;
				}
			x--;
		}
	}
	
	cout << (long long)minAns * 2 << "\n" << minA << " " << minB << "\n" << minC << " " << minD << endl;
	
#ifdef HOME
	cout << endl;
#endif
	
	return minAns;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    
    /*assert(solve((ll)1e18) == (ll)2e9 + 2);
    assert(solve((ll)1e18 + 1) == (ll)2e9 + 2);
    assert(solve(5) == 6);
    assert(solve(8) == 8);*/
#else
	freopen("two-rectangles.in", "r", stdin);
	freopen("two-rectangles.out", "w", stdout);
#endif
	long long s;
	cin >> s;
	solve(s);
	
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
