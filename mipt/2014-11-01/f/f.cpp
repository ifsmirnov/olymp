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

char ground[15][15];
bool went[150][150];

vector<int> canGo[150];

int answer;

void go(int v, int length)
{
	//printf("%d %d length %d\n", v / 10, v % 10, length);
	answer = max(answer, length);
	
	for (auto u: canGo[v])
		if (!went[v][u] && !went[u][v])
		{
			went[v][u] = true;
			go(u, length + 1);
			went[v][u] = false;
		}
}

void build()
{
	for (int x = 0; x < 150; x++)
		canGo[x].clear();
	
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			for (int dx = -1; dx < 2; dx += 2)
				for (int dy = -1; dy < 2; dy += 2)
				{
					if (x + 2 * dx >= 10 || x + 2 * dx < 0) continue;
					if (y + 2 * dy >= 10 || y + 2 * dy < 0) continue;
					
					if (ground[x][y] != 'B' && ground[x + dx][y + dy] == 'B' && ground[x + 2 * dx][y + 2 * dy] == '#')
					{
						int to = (x + 2 * dx) * 10 + (y + 2 * dy);
						canGo[x * 10 + y].push_back(to);
						//printf("can go (%d,%d) => (%d,%d)\n", x, y, x + 2 * dx, y + 2 * dy);
					}
				}
}

void solve()
{
	answer = 0;
	
	for (int y = 0; y < 10; y++)
	{
		char line[15];
		scanf("%s", line);
		
		for (int x = 0; x < 10; x++)
			ground[x][y] = line[x];
	}

	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			if (ground[x][y] == 'W')
			{
				ground[x][y] = '#';
				build();
				go(10 * x + y, 0);
				ground[x][y] = 'W';
			}
	
	printf("%d\n", answer);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	int nTests;
	scanf("%d", &nTests);
	
	for (int i = 0; i < nTests; i++)
		solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
