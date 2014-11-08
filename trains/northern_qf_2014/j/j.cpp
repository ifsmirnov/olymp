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

struct windChange
{
	ll tStart, wx, wy;
};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	ll sx, sy, fx, fy;
	scanf("%lld %lld %lld %lld", &sx, &sy, &fx, &fy);
	
	fx -= sx;
	fy -= sy;
	
	ll nChanges, totalSeconds, vMax;
	scanf("%lld %lld %lld", &nChanges, &totalSeconds, &vMax);
	
	ll wxTotal = 0, wyTotal = 0;
	
	vector<windChange> changes(nChanges);
	for (int i = 0; i < nChanges; i++)
	{
		scanf("%lld %lld %lld", &changes[i].tStart, &changes[i].wx, &changes[i].wy);
	}
	
	for (int i = 0; i < nChanges; i++)
	{
		ll until = (i == nChanges - 1) ? totalSeconds : changes[i + 1].tStart;
		ll dt = until - changes[i].tStart;
		
		wxTotal += dt * changes[i].wx;
		wyTotal += dt * changes[i].wy;
	}
	
	ll ffx = fx - wxTotal, ffy = fy - wyTotal;
	
	if (ffx * ffx + ffy * ffy > vMax * vMax * totalSeconds * totalSeconds)
	{
		printf("No\n");
		return 0;
	}
	
	//double l = sqrtl(ffx * ffx + ffy * ffy);
	double vx = ffx / (double)totalSeconds;
	double vy = ffy / (double)totalSeconds;
	
	//printf("v %.6f %.6f\n", vx, vy);
	
	printf("Yes\n");
	
	double x = sx, y = sy;
	
	double wx = 0, wy = 0;
	
	int nextChange = 0;
	for (int i = 1; i <= totalSeconds; i++)
	{
		// travel i-1 -> i
		if (nextChange < nChanges && i - 1 >= changes[nextChange].tStart)
		{
			wx = changes[nextChange].wx;
			wy = changes[nextChange].wy;
			nextChange++;
		}
		
		x += vx + wx;
		y += vy + wy;
		
		printf("%.6f %.6f\n", x, y);
	}

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
