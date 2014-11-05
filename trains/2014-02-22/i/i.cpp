#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
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
const int maxn = 100500;

struct TPoint {
    double x, y;
    
    TPoint(double x = 0, double y = 0)
        : x(x)
        , y(y)
    {
    }
    
    TPoint operator-(const TPoint &p) const {
        return TPoint(x - p.x, y - p.y);
    }
    
    TPoint operator+(const TPoint &p) const {
        return TPoint(x + p.x, y + p.y);        
    }
    
    TPoint operator*(const double a) const {
        return TPoint(a * x, a * y);
    }
    
    double operator*(const TPoint &p) const {
        return x * p.x + y * p.y;
    }
    
    double operator%(const TPoint &p) const {
        return x * p.y - y * p.x;
    }
    
    TPoint rotate(double alpha) const {
        return TPoint(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
    }
    
    double operator~() const {
        return sqrt(*this * *this);
    }
    
    TPoint norm() const {
         return *this * (1 / ~*this);
    }
};

double dist(TPoint a, TPoint b, TPoint c) {
    if ((c - a) * (b - a) > 0 && (c - b) * (a - b) > 0) {
        return fabs((b - a) % (c - a)) / ~(b - a);
    } else {
        return min(~(c - a), ~(c - b));
    }
}

TPoint a[50], c[50];
double r[50];
int N, K;
vector<TPoint> vert;
vector<int> okr;
vector< vector< pair<int, double> > > edges;

double PI = atan2(0, -1);

int addVertex(TPoint p, int oi) {
    vert.pb(p);
    okr.pb(oi);
    edges.resize(edges.size() + 1);
    return vert.size() - 1;
}

void addEdge(int i, int j) {
    forn(k, K) {
        double d =  dist(vert[i], vert[j], c[k]);
        //cout << i << ' ' << j << ' ' << k << ' ' << d << '\n';
        if (d + 1e-7 < r[k]) return;
    }
    edges[i].pb(mp(j, ~(vert[i] - vert[j])));
    edges[j].pb(mp(i, ~(vert[i] - vert[j])));    
}

template<class T>
pair<T, T> dod(const pair<T, T> p, bool sw) {
    return sw ? mp(p.second, p.first) : p;
}

void tangents(TPoint c1, double r1, TPoint c2, double r2, vector<pair<TPoint, TPoint> > &res) {
    bool sw = false;
    if (r1 > r2) {
        sw = true;
        swap(c1, c2);
        swap(r1, r2);
    }
    
    {
        double d = ~(c2 - c1);
        double r = r2 - r1;
        double alpha = asin(r / d);
        TPoint v = (c2 - c1).norm() * sqrt(d * d - r * r);
        TPoint u1 = v.rotate(alpha), u2 = v.rotate(-alpha);
        res.pb(dod(mp(c1 + u1.norm().rotate(PI / 2) * r1, c1 + u1 + u1.norm().rotate(PI / 2) * r1), sw));
        res.pb(dod(mp(c1 + u2.norm().rotate(-PI / 2) * r1, c1 + u2 + u2.norm().rotate(-PI / 2) * r1), sw));
    }
    
    if (r1 > 1e-9) {
        double d = ~(c2 - c1);
        double r = r2 + r1;
        double alpha = asin(r / d);
        TPoint v = (c2 - c1).norm() * sqrt(d * d - r * r);
        TPoint u1 = v.rotate(alpha), u2 = v.rotate(-alpha);
        res.pb(dod(mp(c1 + u1.norm().rotate(-PI / 2) * r1, c1 + u1 + u1.norm().rotate(-PI / 2) * r1), sw));
        res.pb(dod(mp(c1 + u2.norm().rotate(PI / 2) * r1, c1 + u2 + u2.norm().rotate(PI / 2) * r1), sw));
    }
}

void printGraph() {
    cout << vert.size() << '\n';
    forn(i, vert.size()) {
        cout << vert[i].x << ' ' << vert[i].y << '\n';
    }
    forn(i, vert.size()) {
        cout << i << ": ";
        forn(j, edges[i].size()) {
            cout << edges[i][j].first << ", " << edges[i][j].second << " ";
        }
        cout << '\n';
    }
}

double way[100][100];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("shire.in", "rt", stdin);
    freopen("shire.out", "wt", stdout);

    cin >> N >> K;
    if (N == 0) {
        cout << 0 << '\n';
        return 0;
    }
    forn(i, N) {
        cin >> a[i].x >> a[i].y;
        addVertex(a[i], -1);
    }
    forn(i, K) cin >> c[i].x >> c[i].y >> r[i];
    
    forn(i, N) forn(j, N) {
        if (i < j) addEdge(i, j);
    }
    forn(i, K) {
        for (int j = i + 1; j < K; ++j) {
            vector< pair<TPoint, TPoint> > tang;
            tangents(c[i], r[i], c[j], r[j], tang);
            forn(k, tang.size()) {
                int v = addVertex(tang[k].first, i);
                int u = addVertex(tang[k].second, j);
                addEdge(v, u);
            }
        }
    }
    forn(i, N) forn(j, K) {
        vector< pair<TPoint, TPoint> > tang;
        tangents(a[i], 0, c[j], r[j], tang);
        forn(k, tang.size()) {
            int u = addVertex(tang[k].second, j);
            addEdge(i, u);
        }
    }
    forn(i, K) {
        vector< pair<double, int> > v;
        forn(j, vert.size()) {
            if (okr[j] == i) {
                TPoint q = vert[j] - c[i];
                v.pb(mp(atan2(q.y, q.x), j));
            }
        }
        sort(all(v));
        forn(j, v.size()) {
            int n = v[j].second;
            TPoint p = vert[n] - c[i];
            {
                int m = v[(j + 1) % v.size()].second;
                TPoint q = vert[m] - c[i];
                edges[n].pb(mp(m, r[i] * fabs(atan2(q % p, q * p))));
            }
            {
                int m = v[(j + v.size() - 1) % v.size()].second;
                TPoint q = vert[m] - c[i];
                edges[n].pb(mp(m, r[i] * fabs(atan2(q % p, q * p))));
            }
            
            //e[n].pb(mp(v[(j + 1) % v.size()].second, r[i] * fabs(atan2()));
        }
    }
    
    //printGraph();
    
    forn(i, N) forn(j, N) way[i][j] = 1e9;
    
    forn(i, N) {
        set<pair<double, int> > q;
        vector<double> dis(vert.size(), 1e9);        
        vector<bool> proc(vert.size(), false);
        q.insert(mp(0, i));
        dis[i] = 0;
        while (!q.empty()) {
            pair<double, int> cur = *q.begin();
            q.erase(cur);
            int v = cur.second;
            if (proc[v]) continue;
            forn(j, edges[v].size()) {
                double l = edges[v][j].second;
                int to = edges[v][j].first;
                if (!proc[to] && dis[v] + l < dis[to]) {
                    dis[to] = dis[v] + l;
                    q.insert(mp(dis[to], to));
                }
            }
            proc[v] = true;
        }
        forn(j, N) way[i][j] = dis[j];
    }
    
/*    forn(i, N) {
        forn(j, N) cout << way[i][j] << ' ';
        cout << '\n';
    }*/
    
    double sum = 0.0;
    vector<double> dis(N, 1e9);
    dis[0] = 0;
    vector<bool> proc(N, false);
    while (true) {
        int v = -1;
        forn(i, N) {
            if (proc[i]) continue;
            if (v == -1 || dis[i] < dis[v]) v = i;
        }
        if (v == -1) break;
        sum += dis[v];
        proc[v] = true;
        forn(i, N) {
            if (way[v][i] < dis[i]) {
                dis[i] = way[v][i];
            }
        }
    }
    printf("%.10lf\n", sum);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
