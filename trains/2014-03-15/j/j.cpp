#include <iostream>
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

typedef long double lf;
const lf eps = 1e-7;

inline lf det(lf A, lf B, lf C, lf D) { return A * D - B * C; }

struct pt
{
    lf x, y;

    pt(lf nx = 0, lf ny = 0): x(nx), y(ny) {}

    lf operator * (const pt &p) const
    {
        return x * p.x + y * p.y;
    }

    lf operator % (const pt &p) const
    {
        return x * p.y - y * p.x;
    }

    pt operator + (const pt &p) const
    {
        return pt(x + p.x, y + p.y);
    }

    pt operator - (const pt &p) const
    {
        return pt(x - p.x, y - p.y);
    }

    lf operator ~ () const
    {
        return sqrtl((*this) * (*this));
    }
};

struct line
{
    lf A, B, C;

    line(const pt &a, const pt &b)
    {
        A = -(b - a).y;
        B = (b - a).x;
        C = -A * a.x - B * a.y;
    }

    lf dist(const pt &p) const
    {
        return A * p.x + B * p.y + C;
    }

    void invert()
    {
        A = -A, B = -B, C = -C;
    }
};

struct circle
{
    pt o;
    lf r;
};

void intersect(const line &al, const line &bl, vector<pt> &v)
{
    lf delta = det(al.A, al.B, bl.A, bl.B);
    lf dx = det(-al.C, al.B, -bl.C, bl.B);
    lf dy = det(al.A, -al.C, bl.A, -bl.C);
    if (fabs(delta) > eps) v.pb(pt(dx / delta, dy / delta));
}

pt rotate(const pt &p, lf sina, lf cosa)
{
    return pt(p.x * cosa + p.y * sina, p.x * sina - p.y * cosa);
}

void shift(line &l, lf dist)
{
    l.C += dist / sqrtl(l.A * l.A + l.B * l.B);
}

lf raydist(const pt &p, const pt &o, const pt &v)
{
    if ((o - p) * v > 0) return ~(p - o);
    return fabs((o - p) % v) / ~v;
}

pair<pt, pt> tangents(const circle &c, const pt &p)
{
    lf sina = c.r / ~(c.o - p), cosa = sqrtl(1 - sina * sina);
    pt x = rotate(c.o - p, sina, cosa), y = rotate(c.o - p, -sina, cosa);
    return mp(x, y);
}

pair<line, line> intan(const circle &c1, const circle &c2)
{
    circle c3 = c1;
    c3.r += c2.r;
    pair<pt, pt> tt = tangents(c1, c2.o);
    line l1(c2.o, c2.o + tt.first), l2(c2.o, c2.o + tt.second);
    if (l1.dist(c1.o) < 0) l1.invert();
    if (l2.dist(c1.o) < 0) l2.invert();
    shift(l1, c2.r), shift(l2, c2.r);
    return mp(l1, l2);
}

bool bad(const circle &c1, const circle &c2, const pt &p)
{
    pair<pt, pt> tt = tangents(c1, p);
    return (raydist(c2.o, p, tt.first) <= c1.r + eps ||
            raydist(c2.o, p, tt.second) <= c1.r + eps);
}

const int maxn = 11;

vector<line> lines;
vector<pt> pts;
circle data[maxn];
int n;
lf x, y;

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("zen.in", "r", stdin);
    freopen("zen.out", "w", stdout);
#endif
    cin >> n >> x >> y;
    for (int i = 0; i < n; ++i)
        cin >> data[i].o.x >> data[i].o.y >> data[i].r;
    lines.pb(line(pt(0, 0), pt(x, 0)));
    lines.pb(line(pt(x, 0), pt(x, y)));
    lines.pb(line(pt(x, y), pt(0, y)));
    lines.pb(line(pt(0, y), pt(0, 0)));
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            pair<line, line> tt = intan(data[i], data[j]);
            lines.pb(tt.first);
            lines.pb(tt.second);
        }
    for (size_t i = 0; i < lines.size(); ++i)
        for (size_t j = i + 1; j < lines.size(); ++j)
            intersect(lines[i], lines[j], pts);

    for (const pt &p : pts)
    {
        if (p.x < 0 || p.x > x || p.y < 0 || p.y > y) 
            continue;
        for (int i = 0; i < n; ++i)
            if (~(p - data[i].o) < data[i].r)
                goto next;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j && bad(data[i], data[j], p))
                    goto next;
        cout.precision(15);
        cout << fixed;
        cout << p.x << " " << p.y << endl;
        return 0;

        next:;
    }
    cout << "No Zen" << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
