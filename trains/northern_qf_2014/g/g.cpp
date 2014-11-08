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

bool inter(int x0, int x1, int x2, int x3)
{
	return max(x0, x2) < min(x1, x3);
}

bool inter(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
	return inter(x0, x1, x2, x3) && inter(y0, y1, y2, y3);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	// big
	int x1, y1, x2, y2;
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

	// small
	int x3, y3, x4, y4;
	scanf("%d %d %d %d", &x3, &y3, &x4, &y4);
	
	int w, h;
	scanf("%d %d", &w, &h);

	bool can = false;
	
	if (w <= x2 - x1 && h <= y2 - y1)
	{
		if (!inter(x1, y1, x1 + w, y1 + h, x3, y3, x4, y4)) can = true;
		if (!inter(x2 - w, y2 - h, x2, y2, x3, y3, x4, y4)) can = true;
		if (!inter(x1, y2 - h, x1 + w, y2, x3, y3, x4, y4)) can = true;
		if (!inter(x2 - w, y1, x2, y1 + h, x3, y3, x4, y4)) can = true;
	}
	
	printf("%s\n", can ? "Yes" : "No");

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
