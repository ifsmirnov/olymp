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

const int maxN = 100500;

struct edge
{
    int to;
    int length;
    int cost;
    int id;
    
    bool operator==(const edge& e)
    {
        return id == e.id;
    }
};

vector<edge> edgesTo[maxN];

int n;
 
vector<int> d;
vector<int> previous;
    
void buildDistances(int v)
{
    deque<int> q;
    q.push_back(v);
    d.assign(n, -1);
    d[v] = 0;
    previous.assign(n, -1);
    
    while (!q.empty())
    {
        v = q.front();
        q.pop_front();
        
        for (auto e: edgesTo[v])
            if (d[e.to] == -1)
            {
                d[e.to] = d[v] + e.length;
                previous[e.to] = v;
                q.push_back(e.to);
            }
    }
}

int findFurthest()
{
    int f = 0;
    for (int i = 0; i < n; i++)
        if (d[i] > d[f])
            f = i;
    
    return f;
}

struct solution
{
    int cost;
    vector<int> edges;
    
    void print()
    {
        printf("%d\n%d\n", cost, (int)edges.size());
        for (auto it: edges)
            printf("%d ", it);
        printf("\n");
    }
};

int rmEdge(int v, int u)
{
    for (int i = 0; i < (int)edgesTo[v].size(); i++)
        if (edgesTo[v][i].to == u)
        {
            int id = edgesTo[v][i].id;
            swap(edgesTo[v][i], edgesTo[v][edgesTo[v].size() - 1]);
            edgesTo[v].pop_back();
            return id;
        }
        
    assert(false);
    return -1;
}

solution bestOf(const solution& a, const solution& b)
{
    if (a.cost < b.cost)
        return a;
    else
        return b;
}

bool minRelax(int& a, int b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    
    return false;
}

int ans[maxN][2];

// -1: do nothing, already ok
int action[maxN][2];

vector<edge> okEdges[maxN];

bool dfs(int v, int maxPathLength, int prev = -1)
{
    if (maxPathLength < 0) return false;
    
    //printf("dfs %d, %d\n", v + 1, maxPathLength);
    
    ans[v][0] = 0;
    ans[v][1] = inf;
    
    for (auto it: edgesTo[v])
        if (it.to != prev)
        {
            if (!dfs(it.to, maxPathLength - it.length, v)) continue;
            okEdges[v].push_back(it);
            
            ans[v][0] += min(ans[it.to][0], it.cost);
        }
        
    for (auto it: okEdges[v])
    {
        int other = ans[v][0] - min(ans[it.to][0], it.cost);
        if (minRelax(ans[v][1], other + min(ans[it.to][1], it.cost)))
        {
            // update answer
        }
    }
    
    if (okEdges[v].empty())
    {
        ans[v][0] = inf;
        ans[v][1] = 0;
    }
        
    //printf("%d: ans[0] = %d, ans[1] = %d\n", v + 1, ans[v][0], ans[v][1]);
    
    return true;
}

void restoreDfsOne(int v, vector<int>& answer)
{
    for (auto it: okEdges[v])
    {
        if (ans[it.to][0] < it.cost)
            restoreDfsOne(it.to, answer);
        else
            answer.push_back(it.id);
    }
}

void restoreDfsTwo(int v, vector<int>& answer)
{
    for (auto it: okEdges[v])
    {
        int other = ans[v][0] - min(ans[it.to][0], it.cost);
        if (ans[v][1] == other + min(ans[it.to][1], it.cost))
        {
            // update answer
            
            if (ans[it.to][1] < it.cost)
                restoreDfsTwo(it.to, answer);
            else
                answer.push_back(it.id);
                         
            for (auto x: okEdges[v])
            {
                if (x == it) continue;
                
                if (ans[x.to][0] < it.cost)
                    restoreDfsOne(x.to, answer);
                else
                    answer.push_back(x.id);
            }
        }
    }
}

// remove all or leave one?
solution getSolution(int v, bool removeAll, int maxPathLength)
{
    dfs(v, maxPathLength, -1);
    
    solution s;
    s.cost = (removeAll ? ans[v][0] : ans[v][1]);
    
    if (removeAll)
        restoreDfsOne(v, s.edges);
    else
        restoreDfsTwo(v, s.edges);
        
    sort(s.edges.begin(), s.edges.end());
    s.edges.erase(unique(s.edges.begin(), s.edges.end()), s.edges.end());
    
    #ifdef HOME
    printf("solve(%d, %d, %d): %d\n", v + 1, removeAll ? 1 : 0, maxPathLength, s.cost);
    #endif
    return s;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scanf("%d", &n);
    
    vector<int> costs(n - 1);
    
    for (int i = 0; i < n - 1; i++)
    {
        int a, b, length, cost;
        scanf("%d %d %d %d", &a, &b, &length, &cost);
        
        a--; b--;
        
        edgesTo[a].push_back(edge { b, length, cost, i + 1 });
        edgesTo[b].push_back(edge { a, length, cost, i + 1 });
        
        costs[i] = cost;
    }
    
    buildDistances(0);
    
    int a = findFurthest();
    buildDistances(a);
    
    int b = findFurthest();
    
    vector<int> path;
    
    int now = b;
    while (now != a)
    {
        path.push_back(now);
        now = previous[now];
    }
    path.push_back(a);
    reverse(path.begin(), path.end());
    
    #ifdef HOME
    printf("furthest %d => %d\n", a + 1, b + 1);
    for (auto x: path)
        printf("%d ", x + 1);
    printf("\n\n");
    #endif
    
    int pathLength = d[b];
    
    for (int i = 0; i < (int)path.size() - 1; i++)
        if (pathLength - d[path[i]] == d[path[i]])
        {
            // center is vertex path[i]
            
            #ifdef HOME
            printf("center is %d\n", path[i] + 1);
            #endif
            
            solution s = getSolution(path[i], false, pathLength / 2);
            s.print();
            break;
        }
        else if (d[path[i + 1]] > pathLength - d[path[i + 1]])
        {
            // center lies on edge path[i]..path[i + 1]
            
            int edgeId = rmEdge(path[i], path[i + 1]);
            rmEdge(path[i + 1], path[i]);
            
            solution a = getSolution(path[i], true, d[path[i]]);
            solution b = getSolution(path[i + 1], true, pathLength - d[path[i + 1]]);
            solution c;
            c.cost = costs[edgeId - 1];
            c.edges.push_back(edgeId);
            
            //printf("edge id %d\n", edgeId);
            
            #ifdef HOME
            printf("center lies on %d..%d, solutions %d %d %d\n", path[i] + 1, path[i + 1] + 1, a.cost, b.cost, c.cost);
            #endif
            
            bestOf(bestOf(a, b), c).print();
            break;
        }

    // one of longest paths built: path (a => b)

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
