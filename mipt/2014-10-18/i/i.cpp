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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	const int maxN = 1005;

	char one[maxN], two[maxN];
	scanf("%s %s", one, two);
	
	char* x = one, *y = two;
	
	int answer = 0;
	
	while (true)
	{
		if (!*x && !*y) break;
		
		//printf("%s %s\n", x, y);
		
		if (!*x)
		{
			y++;
		}
		else if (!*y)
		{
			x++;
		}
		else
		{
			char a = *x, b = *y;
			
			if (a == 'L' && b == 'L')
			{
				x++;
				y++;
			}
			else if (a != 'L' && b != 'L')
			{
				x++;
				y++;
			}
			else if (a != 'L')
			{
				x++;
			}
			else
			{
				y++;
			}
		}
		
		answer++;
	}
	
	printf("%d\n", answer);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}