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

const int MAXN = 200000;
const long long INF = 1000000000000000ll;

vector<pair<int, int> > graph[MAXN];
int n, x[MAXN], y[MAXN];
pair<int, int> xs[MAXN], ys[MAXN];
long long dist[MAXN];
priority_queue<pair<long long, int> > heap;
bool used[MAXN];

void addEdge(int u, int v)
{
	int dist = min(abs(x[u] - x[v]), abs(y[u] - y[v]));
	graph[u].push_back(make_pair(v, dist));
	graph[v].push_back(make_pair(u, dist));
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &x[i], &y[i]);
		xs[i] = make_pair(x[i], i);
		ys[i] = make_pair(y[i], i);
	}

	sort(xs, xs + n);
	sort(ys, ys + n);
	
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
		{
			addEdge(xs[i].second, xs[i - 1].second);
			addEdge(ys[i].second, ys[i - 1].second);
		}
		if (i < n - 1)
		{
			addEdge(xs[i].second, xs[i + 1].second);
			addEdge(ys[i].second, ys[i + 1].second);
		}
	}

	for (int i = 0; i < n; i++)
	{
		used[i] = false;
		dist[i] = (i == 0 ? 0 : INF);
		heap.push(make_pair(-dist[i], i));
	}
	
	while (true)
	{
		while (!heap.empty() && used[heap.top().second])
			heap.pop();
		if (heap.empty()) break;
		int best = heap.top().second; heap.pop();
		used[best] = true;
		for (int i = 0; i < (int)graph[best].size(); i++)
		{
			int v = graph[best][i].first;
			long long w = graph[best][i].second;
			if (dist[v] > dist[best] + w)
			{
				dist[v] = dist[best] + w;
				heap.push(make_pair(-dist[v], v));
			}
		}
	}
	printf("%lld\n", dist[n - 1]);
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
