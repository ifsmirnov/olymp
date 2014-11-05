#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

const int maxn = 2500, maxm = 5000;
const int inf = 1000000000LL;

struct edge
{
    int from, to, cost;
    int cap, flow;

	edge() {}
    edge(int nfrom, int nto, int ncap, int ncost): from(nfrom), to(nto), cost(ncost), cap(ncap), flow(0) {}
};

vector<int> graph[maxn];
edge edges[4 * maxm];
int dist[maxn], h[maxn], esz;
int back[maxn], n, m, used[maxn];
int startMoney, wantedCargo;
int q[maxn], qh, qt, x = 0;

void addEdge(int u, int v, int cap)
{
    graph[u].pb(esz);
    edges[esz++] = (edge(u, v, cap, 1));

    graph[v].pb(esz);
    edges[esz++] = (edge(v, u, 0, -1));
}

bool dijkstra()
{
	priority_queue<pii, vector<pii>, greater<pii> > heap;
	fill(dist, dist + n, inf);
    fill(back, back + n, -1);
    fill(used, used + n, 0);
    dist[0] = 0;
    heap.push(mp(0, 0));
    while (!heap.empty())
	{
		pii cur = heap.top();
		heap.pop();
		if (cur.second == n - 1) return true;
		if (cur.first != dist[cur.second]) continue;
		int v = cur.second;
				
		for (size_t i = 0; i < graph[v].size(); ++i)
		{
			const edge &e = edges[graph[v][i]];
			if (e.cap - e.flow <= 0) continue;
			if (dist[e.to] > dist[e.from] + e.cost + h[e.from] - h[e.to])
			{
				dist[e.to] = dist[e.from] + e.cost + h[e.from] - h[e.to];
				heap.push(mp(dist[e.to], e.to));
				back[e.to] = graph[v][i];
			}
		}
	}
	return false;
}

bool bfs()
{
    fill(dist, dist + n, inf);
    fill(back, back + n, -1);
    qh = qt = 0;

    dist[0] = 0;
    q[qt++] = 0;
    while (qh < qt)
    {
        int v = q[qh++];
        for (size_t i = 0; i < graph[v].size(); ++i)
        {
            const edge &e = edges[graph[v][i]];
            if (e.cap - e.flow <= 0 || dist[e.to] != inf) continue;
            dist[e.to] = dist[v] + 1;
            q[qt++] = e.to;
            back[e.to] = graph[v][i];
        }
    }
    return dist[n - 1] != inf;
}

vector<pii> minc;

void mincost()
{
	minc.clear();
	bfs();
    for (int i = 0; i < n; ++i) h[i] = dist[i];
    while (dijkstra())
    {
		int len = dist[n - 1] + h[n - 1] - h[0];
        int canPush = inf;
        
        for (int v = n - 1; v != 0;)
        {
            int id = back[v];
            canPush = min(canPush, edges[id].cap - edges[id].flow);
            v = edges[id].from;
        }
        
        minc.pb(mp(canPush, len));
        for (int v = n - 1; v != 0;)
        {
            int id = back[v];
            edges[id].flow += canPush;
            edges[id ^ 1].flow -= canPush;
            v = edges[id].from;
        }

        for (int i = 0; i < n; ++i) h[i] = dist[i];
	}
}

int howMany(int days)
{
    for (size_t i = 0; i < esz; ++i)
        edges[i].flow = 0;
    int pushed = 0;
    for (size_t i = 0; i < minc.size(); ++i)
    {
		int len = minc[i].second, canPush = minc[i].first;
    	i64 pcost = 0;
        if (len > days) break;
        
        pushed += canPush * (days - len + 1);
        if (pushed >= inf) return pushed;
    }
    return pushed;
}

bool solve()
{
    if (scanf("%d%d%d", &n, &m, &wantedCargo) != 3) return false;
    for (int i = 0; i < n; ++i) graph[i].clear();
    esz = 0;
    for (int i = 0; i < m; ++i)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
    
	mincost();
    int left = 0, right = wantedCargo + n;
    while (right - left > 1)
    {
        int middle = (left + right) >> 1;
        if (howMany(middle) >= wantedCargo) right = middle;
        else left = middle;
    }
    if (howMany(right) >= wantedCargo) printf("%d\n", right);
    else printf("No solution\n");
    return true;
}

void gen(int t, int n, int m, int seed)
{
	freopen("input.txt", "w", stdout);
	srand(seed);
	for (int it = 0; it < t; ++it)
	{
		printf("%d %d %d\n", n, m, rand() % 1000000000 + 1);
		for (int i = 0; i < m; ++i)
		{
			int a = rand() % n, b = rand() % n, c = rand() % 100 + 1;
			if (rand() & 1) swap(a, b);
			printf("%d %d %d\n", a, b, c);
		}
	}
	exit(0);
}

int main() 
{
	//gen(1, 2500, 5000, 13);
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    while (solve());
#ifdef HOME
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
