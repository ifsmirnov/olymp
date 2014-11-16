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

const int maxN = 1050;
pair<int, int> v[maxN][maxN];

void change(int x, int y,  int ox, int oy,  int nx, int ny)
{
	printf("changing %d %d from %d %d\n", x, y, ox, oy);
	assert(v[x][y] == make_pair(ox, oy));
	v[x][y] = { nx, ny };
}

void fixTypeOne(int x, int y)
{
	printf("type one (%d %d)\n", x, y);
	
	change(x, y + 4,  0, -1,  1, 0);
	
	change(x+1, y,    0,  1,  1, 0);
	change(x+1, y+3,  0,  1,  -1, 0);

	change(x+2, y+3,  0, -1,  -1, 0);
	change(x+2, y+4,  0, -1, 1, 0);
	
	change(x+3, y+1,  0, 1, 1, 0);
	change(x+3, y+3,  0, 1, -1, 0);
	
	change(x+4, y+2, 0, -1, -1, 0);
}

void fixTypeTwo(int x, int y)
{
	printf("type two (%d %d)\n", x, y);
	
	if (y > 0)
	{
		change(x, y,   0, 1,  1, 0);
		change(x + 1, y + 1, 0, -1, -1, 0);
		change(x + 2, y + 1, 0, 1, -1, 0);
		change(x + 1, y + 4, 0, -1, 1, 0);
	}
	else
	{
		v[x][y] = 
		
		change(x + 1, y + 4, 0, -1, 1, 0);
	}
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	int rows, columns, pillars;
	scanf("%d %d %d", &columns, &rows, &pillars);
	
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			if (x % 2 == 0)
			{
				v[x][y] = make_pair(0, 1);
				
				if (y == rows - 1)
					v[x][y] = make_pair(1, 0);
			}
			else
			{
				v[x][y] = make_pair(0, -1);
				
				if (y == 1)
				{
					if (x != columns - 1)
						v[x][y] = make_pair(1, 0);
					else
						v[x][y] = make_pair(0, -1);
				}
			}
			
			if (y == 0 && x != 0)
				v[x][y] = make_pair(-1, 0);
		}

	for (int i = 0; i < pillars; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		
		y = rows - y;
		
		v[x][y] = v[x - 1][y] = v[x][y - 1] = v[x - 1][y - 1] = make_pair(0, 0);
		
		if (x % 2 == 1)
			fixTypeOne(x - 2, y - 2);
		else
			fixTypeTwo(x - 2, y - 3);
	}
	
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			if (v[x][y] == make_pair(0, 0)) printf("#");
			if (v[x][y] == make_pair(1, 0)) printf("R");
			if (v[x][y] == make_pair(-1, 0)) printf("L");
			if (v[x][y] == make_pair(0, -1)) printf("U");
			if (v[x][y] == make_pair(0, 1)) printf("D");
		}
		printf("\n");
	}
	
	int x = 0, y = rows - 1;
	
	printf("TAK\n");
	while (true)
	{
		//printf("(%d, %d)\n", x, y);
		assert(v[x][y] != make_pair(0, 0));
		
		int nx = x + v[x][y].first;
		int ny = y + v[x][y].second;
		
		if (v[x][y] == make_pair(0, -1)) printf ("G");
		if (v[x][y] == make_pair(0, +1)) printf ("D");
		if (v[x][y] == make_pair(-1, 0)) printf ("L");
		if (v[x][y] == make_pair(+1, 0)) printf ("P");
		fflush(stdout);
		
		if (nx == 0 && ny == rows - 1) break;
		
		x = nx;
		y = ny;
	}
	printf("\n");

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
