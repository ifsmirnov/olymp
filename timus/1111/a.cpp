#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
typedef long double ld;
using namespace std;
const ld eps = 1e-15;
#define forn(i, n) for (int i = 0; i < n; i++)
const int maxn = 50;

#define sqr(x) ((x)*(x))
#define eq(x, y) (abs((x)-(y))<eps)
#define lt(x, y) ((x)<(y)-eps)

struct point
{
    ld x, y;
    point (ld X = 0, ld Y = 0): x(X), y(Y) {};
    bool operator== (const point &p1) const
    {
        return eq(x, p1.x) && eq(y, p1.y);
    };
};
struct sq
{
    vector<point> p;
    sq () {p.resize(4);};
};
point operator+ (point p1, point p2)
{
    return point (p1.x + p2.x, p1.y + p2.y);
};
point operator- (point p1, point p2)
{
    return point(p1.x - p2.x, p1.y - p2.y);
};
point operator* (point p1, double k)
{
    return point(p1.x * k, p1.y * k);
};
double operator* (point p1, point p2)
{
    return p1.x * p2.y - p1.y * p2.x;
};
double operator& (point p1, point p2)
{
    return p1.x * p2.x + p1.y * p2.y;
};
point turnCW (point p1)
{
    return point(p1.y, -p1.x);
};
double len (point p1)
{
    return sqrtl(sqr(p1.x) + sqr(p1.y));
};
istream& operator>> (istream &in, point &p1)
{
    cin >> p1.x >> p1.y;
    return in;
};
double distseg (point a, point b, point p)
{
    if (a == b || (lt((a-b)&(p-b), 0) || lt((b-a)&(p-a), 0)))
        return min(len(a-p), len(b-p));
    else
        return abs((a-b)*(p-b)/len(a-b));
};
double distsq (sq s1, point p1)
{
    double mn = 1e50, sum = 0, t;
    forn(i, 4)
    {
        t = distseg(s1.p[i], s1.p[(i+1)%4], p1);
        mn = min(mn, t);
        sum += t;
    }
    if (eq(sum, 2 * len(s1.p[0] - s1.p[1])))
        return 0;
    return mn;
};
void completeSquare (sq &s)
{
    point a = s.p[0], b = s.p[2];
    point v = (b-a)*0.5;
    s.p[1] = a + v + turnCW(v);
    s.p[3] = a + v - turnCW(v);
};

double dists[maxn];
bool cmp (int x, int y)
{
    if (eq(dists[x], dists[y]))
        return x < y;
    return dists[x] < dists[y];
};
int n;
point p;
int order[maxn];
void scan()
{
    vector<sq> s;
    cin >> n;
    s.resize(n);
    forn(i, n)
        cin >> s[i].p[0] >> s[i].p[2];
    forn(i, n)
        completeSquare(s[i]);
    cin >> p;
    forn(i, n)
        dists[i] = distsq(s[i], p);
};
void solve()
{
    forn(i, n)
        order[i] = i;
    sort(order, order + n, cmp);
    forn(i, n)
        cout << order[i] + 1 << " ";
    cout << endl;
};

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    scan();
    solve();

    return 0;
};
