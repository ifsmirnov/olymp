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

const int maxN = 1005;

int n;
vector<int> w, h;
vector<int> to[maxN];
vector<char> used;

int minw, minh;

bool dfs(int v);

bool isLinked(int minw, int minh)
{
	::minw = minw;
	::minh = minh;
	used.assign(n, false);
	
	//printf("linked %d %d\n", minw, minh);
	
	return dfs(0);
}

bool dfs(int v)
{
	if (used[v]) return false;
	used[v] = true;
	
	if (w[v] >= minw && h[v] >= minh)
	{
		if (v == n - 1) return true;
		
		for (int u: to[v])
			if (dfs(u))
				return true;
	}
	
	return false;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	
	vector<int> dims = { a, b, c };
	sort(dims.begin(), dims.end());
	
	a = dims[0];
	b = dims[1];
	c = dims[2];
	
	scanf("%d", &n);
	
	w.assign(n, 0);
	h.assign(n, 0);
	
	for (int i = 0; i < n; i++)
	{
		int nTo;
		scanf("%d %d %d", &w[i], &h[i], &nTo);
		
		to[i].assign(nTo, 0);
		for (int j = 0; j < nTo; j++)
		{
			scanf("%d", &to[i][j]);
			to[i][j]--;
		}
		
		random_shuffle(to[i].begin(), to[i].end());
	}
	
	int maxv = 0, maxw = 0, maxh = 0, maxz = 0;
	
	int w = 0, h = 500;
	
	while (w <= 500)
	{
		while (!isLinked(w, h) && h >= 0) h--;
		if (h < 0) break;
		
		{
		int canw = min(w, a);
		int canh = min(h, b);
		int canz = c;
		
		if (canw * canh * canz > maxv)
		{
			maxv = canw * canh * canz;
			maxw = canw;
			maxh = canh;
			maxz = canz;
		}
		}
		
		{
		int canw = min(h, a);
		int canh = min(w, b);
		int canz = c;
		
		if (canw * canh * canz > maxv)
		{
			maxv = canw * canh * canz;
			maxw = canw;
			maxh = canh;
			maxz = canz;
		}
		}
		
		w++;
	}
	
	printf("%d %d %d\n", maxw, maxh, maxz);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
