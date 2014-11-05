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

struct solution
{
	int rentId; // can be -1
	
	int advantage;
	
	int liveWith; // can be -1
	
	bool isBetterThan(solution& s)
	{
		if (rentId == -1) return false;
		if (advantage > s.advantage) return true;
		
		return false;
	}
	
	void print()
	{
		if (rentId == -1)
		{
			printf("Forget about apartments. Live in the dormitory.\n");
		}
		else if (liveWith == -1)
		{
			printf("You should rent the apartment #%d alone.\n", rentId + 1);
		}
		else
		{
			printf("You should rent the apartment #%d with the friend #%d.\n", rentId + 1, liveWith + 1);
		}
	}
};

void solve()
{
	solution best = { -1, -1, -1 };
	
	int maxPay, advAloneOne, advAloneTwo;
	scanf("%d %d %d", &maxPay, &advAloneOne, &advAloneTwo);
	
	int nFriends;
	scanf("%d", &nFriends);
	
	vector<int> advFriend(nFriends), maxPayFriend(nFriends);
	for (int i = 0; i < nFriends; i++)
		scanf("%d %d", &maxPayFriend[i], &advFriend[i]);
	
	int nVariants;
	scanf("%d", &nVariants);
	
	vector<int> advVariant(nVariants), cost(nVariants), canShare(nVariants);
	
	for (int i = 0; i < nVariants; i++)
	{
		scanf("%d %d %d", &canShare[i], &cost[i], &advVariant[i]);
		
		canShare[i] = (canShare[i] == 2);
	}
	
	for (int i = 0; i < nVariants; i++)
		if (cost[i] <= maxPay)
		{
			solution s = { i, (canShare[i] ? advAloneTwo : advAloneOne) + advVariant[i], -1 };
			if (s.isBetterThan(best))
				best = s;
		}
		
	for (int i = 0; i < nVariants; i++)
		for (int j = 0; j < nFriends; j++)
			if (canShare[i] && cost[i] <= 2 * maxPayFriend[j] && cost[i] <= maxPay * 2)
			{
				solution s = { i, advVariant[i] + advFriend[j], j };
				if (s.isBetterThan(best))
					best = s;
			}
			
	best.print();
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    for (int i = 0; i < 4; i++)
#endif
	solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
