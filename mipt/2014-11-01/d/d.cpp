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
#include <sstream>
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

void cutComma(string& s)
{
	if (s.back() == ',') s.pop_back();
}

const int maxN = 3 * 1100000;
vector<pii> e[maxN]; // to, weight

vector<int> ans;

int nStations;

int dfs(int v, int to)
{
	if (ans[v] != -1) return ans[v];
	
	if (v == to) return 0;
	
	int m = -2;
	for (auto it: e[v])
	{
		int can = dfs(it.first, to);
		if (can == -2) continue;
		
		int w = 1;
		if (v < nStations || it.first < nStations) w = 0;
		
		m = max(m, can + w);
	}
		
	if (m == -2)
		return ans[v] = -2;
		
	return ans[v] = m;
}

void solve()
{
	scanf(" ");
	
	string stops;
	getline(cin, stops);
	//printf("%s\n", stops.c_str());
	
	istringstream stopsParser(stops);
	
	map<string, int> stationToId;
	nStations = 0;
	
	while (true)
	{
		string stop;
		
		if (!(stopsParser >> stop)) break;
		if (stop == "Stops:") continue;
		cutComma(stop);
		
		stationToId[stop] = nStations++;
		//printf("Station %d: %s\n", nStations, stop.c_str());
	}
	
	string routes;
	getline(cin, routes);
	
	int startId = -1, endId = -1;
	
	int nVertices = nStations;
	
	string source;
	
	while (true)
	{
		string s;
		getline(cin, s);
		
		istringstream sParser(s);
		string routeString;
		sParser >> routeString;
		sParser >> routeString;
		
		if (routeString == "route:")
		{
			vector<int> ids;
			
			while (true)
			{
				string current;
				if (!(sParser >> current)) break;
				cutComma(current);
				
				assert(stationToId.find(current) != stationToId.end());
				
				int id = stationToId[current];
				ids.push_back(id);
			}
			
			int base = nVertices;
			nVertices += ids.size();
			
			for (int i = 0; i < (int)ids.size(); i++)
			{
				if (i != (int)ids.size() - 1)
					e[base + i].push_back(make_pair(base + i + 1, 0));
					
				e[base + i].push_back(make_pair(ids[i], 1));
				e[ids[i]].push_back(make_pair(base + i, 0));
			}
			
			base = nVertices;
			nVertices += ids.size();
			
			for (int i = 0; i < (int)ids.size(); i++)
			{
				if (i != 0)
					e[base + i].push_back(make_pair(base + i - 1, 0));
					
				e[base + i].push_back(make_pair(ids[i], 1));
				e[ids[i]].push_back(make_pair(base + i, 0));
			}
		}
		else
		{
			sParser >> source;
			assert(source == "at");
			sParser >> source;
			
			assert(stationToId.find(source) != stationToId.end());
			startId = stationToId[source];
			
			break;
		}
	}
	
	string destination;
	cin >> destination;
	assert(destination == "Michelle");
	cin >> destination;
	assert(destination == "lives");
	cin >> destination;
	assert(destination == "at");
	cin >> destination;
	
	assert(stationToId.find(destination) != stationToId.end());
	endId = stationToId[destination];
	
	vector<int> d(nVertices, 1e9);
	d[startId] = 0;
	
	deque<int> q;
	q.push_back(startId);
	
	while (!q.empty())
	{
		int v = q.front();
		q.pop_front();
		
		for (auto it: e[v])
		{
			int can = d[v] + it.second;
			if (d[it.first] > can)
			{
				d[it.first] = can;
			
				if (it.second == 1)
					q.push_back(it.first);
				else
					q.push_front(it.first);
			}
		}
	}
	
	for (int i = 0; i < nVertices; i++)
		for (int j = 0; j < (int)e[i].size(); j++)
			if (d[i] + e[i][j].second > d[e[i][j].first])
			{
				swap(e[i][j], e[i].back());
				e[i].pop_back();
				j--;
			}
			
	ans.assign(nVertices, -1);
	
	//printf("ready\n");
	int answer = dfs(startId, endId);
	//answer -= d[endId] * 2;
	
	int nLines = d[endId];
	int nMinutes = answer;
	
	printf("optimal travel from %s to %s: %d line%s, %d minute%s\n", source.c_str(), destination.c_str(), nLines, nLines == 1 ? "" : "s", nMinutes, nMinutes == 1 ? "" : "s");
	
	for (int i = 0; i < nVertices; i++)
		e[i].clear();
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
