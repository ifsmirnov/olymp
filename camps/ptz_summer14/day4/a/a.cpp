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
typedef double ld;
const ld eps = 1e-9;
const int maxn = 33;
#define eq(x, y) (abs((ld)(x)-(ld)(y))<eps)
#define lt(x, y) ((x)<(y)-eps)
#define le(x, y) ((x)<=(y)+eps)
#define gt(x, y) lt(y, x)
#define ge(x, y) le(y, x)
#define op operator
#define det(a,b,c,d) ((a)*(d)-(b)*(c))
#define nothing

int sign(ld x) {
    if (x < -eps) return -1;
    else if (x > eps) return 1;
    return 0;
}


struct pt {
    ld x, y;
    pt(){}
    pt(ld x, ld y) : x(x), y(y) {}
    pt op+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt op-(const pt& p) const { return pt(x-p.x, y-p.y); }
    pt turn(ld sina, ld cosa) const { return pt(x*cosa - y*sina, x*sina + y*cosa); }
    pt turn(ld alpha) const { return turn(sinl(alpha), cosl(alpha)); }

    ld op*(const pt& p) const { return x*p.y - y*p.x; }
    ld op&(const pt& p) const { return x*p.x + y*p.y; }

    bool op==(const pt& p) const { return eq(x, p.x) && eq(y, p.y); }
    bool op!=(const pt& p) const { return !(*this == p); }
};

istream& op>>(istream& in, pt& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& op<<(ostream& out, const pt& p) {
    out << p.x << " " << p.y;
    return out;
}

struct line {
    ld a, b, c;
    line() {}
    line(ld a, ld b, ld c) : a(a), b(b), c(c) {}
    line(const pt& p, const pt& q) {
        a = p.y - q.y;
        b = q.x - p.x;
        ld t = sqrtl(a*a + b*b);
        a /= t;
        b /= t;
        c = - (a * p.x + b * p.y);
    }

    ld dist(const pt& p) const { return a*p.x +  b*p.y + c; }
    pt normal() const { return pt(a, b); }
};

inline ld normalize_angle(ld ang) {
    while (ang < 0) ang += M_PI * 2.0;
    while (ang > M_PI * 2.0) ang -= M_PI * 2.0;
    return ang;
}

pt intersect(const line& p, const line& q) {
    ld den = det(p.a, p.b, q.a, q.b);
    if (eq(den, 0)) return pt(inf, inf);
    ld x = det(-p.c, p.b, -q.c, q.b);
    ld y = det(p.a, -p.c, q.a, -q.c);
    return pt(x/den, y/den);
}

inline ld angle(const pt& p, const pt& q) {
    return normalize_angle(atan2l(p*q, p&q));
}

int n, m;
pt small[maxn], big[maxn];
line sides[maxn]; // positive - inside

inline bool between(const pt& a, const pt& b, const pt& c) {
    // a --- b --- c
    return eq(0, (b-a) * (c-b)) && lt(0, (c-b) & (a-b));
}

void make_general(pt* pp, int& n) {
    vector<pt> p(pp, pp+n);
    unique(all(p));
    while (p.size() > 1u && p.back() == p[0]) {
        p.pop_back();
    }
    n = p.size();
    vector<int> ok(n, 0);
    forn(i, n) {
        int a = (i-1+n)%n, b = (i+1)%n;
        ok[i] = !between(p[a], p[i], p[b]);
    }

    n = 0;
    forn(i, p.size()) if (ok[i])
        pp[n++] = p[i];
    pp[n] = pp[0];
}

void scan() {
    cin >> n >> m;
    forn(i, n) cin >> small[i];
    make_general(small, n);
    forn(i, m) cin >> big[i];
    make_general(big, m);
}

struct Change {
    int side, point;
    ld ang;
    bool operator<(const Change& c) const { return ang > c.ang; }
};

struct Triple {
    int s1, s2, s3;
    int timestamp;
    ld ang;
    bool operator<(const Triple& c) const { return ang > c.ang; }
};

priority_queue<Change> changes;
priority_queue<Triple> triples;

int modify_time[maxn]; // for big
int closest_point[maxn];
ld a0[maxn], a1[maxn], a2[maxn];

bool parallel[maxn][maxn];

void fill_a012(int side) {
    int point = closest_point[side];
    ld a = sides[side].a, b = sides[side].b;
    ld x = small[point].x, y = small[point].y;
    a0[side] = a*x + b*y;
    a1[side] = b*x - a*y;
    a2[side] = sides[side].c;
}

ld angles[10];
int nangle;
void intersection_angle(int i, int j, int k) {
    nangle = 0;
    ld b0 = det(sides[i].a, sides[i].b, sides[j].a, sides[j].b);
    ld b1 = det(sides[k].a, sides[k].b, sides[i].a, sides[i].b);
    ld b2 = det(sides[j].a, sides[j].b, sides[k].a, sides[k].b);
    ld A0 = b0 * a0[i] + b1 * a0[j] + b2 * a0[k];
    ld A1 = b0 * a1[i] + b1 * a1[j] + b2 * a1[k];
    ld A2 = b0 * a2[i] + b1 * a2[j] + b2 * a2[k];
    if (eq(0, A0*A0 + A1*A1)) return;
    ld D = A1*A1 * (A1*A1 + A0*A0 - A2*A2);
    if (D < -eps) return;
    ld res;
    if (D < eps) {
        res = -A0*A2 / (A0*A0 + A1*A1);
        if (lt(res, -1)) return;
        if (gt(res, 1)) return;
        res = max(res, -1.0);
        res = min(res, 1.0);
        int criteria = sign(-A2 - A0 * res) * sign(A1);

        if (criteria >= 0) {
            angles[nangle++] = acosl(res);
        }
        if (criteria <= 0) {
            angles[nangle++] = acosl(res) + M_PI;
        }
    } else {
        pair<ld, ld> RES;
        {
            res = (-A0*A2 - sqrtl(D)) / (A0*A0 + A1*A1);
            if (lt(res, -1)) goto label;
            if (gt(res, 1)) goto label;
            int criteria = sign(-A2 - A0 * res) * sign(A1);

            res = max(res, -1.0);
            res = min(res, 1.0);
            if (criteria >= 0) {
                angles[nangle++] = acosl(res);
            }
            if (criteria <= 0) {
                angles[nangle++] = acosl(res) + M_PI;
            }
        }
        label:;
        {
            res = (-A0*A2 + sqrtl(D)) / (A0*A0 + A1*A1);
            if (lt(res, -1)) return;
            if (gt(res, 1)) return;
            int criteria = sign(-A2 - A0 * res) * sign(A1);

            res = max(res, -1.0);
            res = min(res, 1.0);
            if (criteria >= 0) {
                angles[nangle++] = acosl(res);
            }
            if (criteria <= 0) {
                angles[nangle++] = acosl(res) + M_PI;
            }
        }
        return void(nothing);
    }
}

ld get_C(int id, ld ang) {
    return a0[id] * cosl(ang) + a1[id] * sinl(ang) + a2[id];
}

void add_triples(int k, ld ang, int moscowTime, const bool k_is_the_maximum_index = false) {
    forn(i, m) if (i != k && !parallel[i][k]) {
        if (k_is_the_maximum_index && i > k) {
            break;
        }
        forn(j, i) if (j != k && !parallel[i][j] && !parallel[j][k]) {
            Triple triple;
            triple.s1 = i;
            triple.s2 = j;
            triple.s3 = k;
            triple.timestamp = moscowTime;
            intersection_angle(i, j, k);
            forn(index, nangle) {
                if (angles[index] >= ang) {
                    triple.ang = angles[index];
                    triples.push(triple);
                }
            }
        }
    }
}

bool check_ans(int id1, int id2, ld ang) {
    line a = sides[id1], b = sides[id2];
    a.c = get_C(id1, ang);
    b.c = get_C(id2, ang);
    pt p = intersect(a, b);
    bool ok = true;
    forn(i, m) if (i != id1 && i != id2) {
        if (!le(0, p.x * sides[i].a + p.y * sides[i].b + get_C(i, ang))) {
            ok = false;
        }
    }
    if (ok) {
        printf("YES\n");
        printf("%.10lf %.10lf %.10lf\n", ang, p.x, p.y);
        return true;
    }
    return false;
}

void init() {
    while (!changes.empty()) changes.pop();
    while (!triples.empty()) triples.pop();

//     forn(i, m) forn(j, m) {
//         if (eq(0, sides[i].normal() * sides[j].normal())) {
//             parallel[i][j] = 1;
//         } else {
//             parallel[i][j] = 0;
//         }
//     }

    forn(i, m) modify_time[i] = 0;
    forn(i, m) {
        sides[i] = line(big[i], big[i+1]);
        ld min_dist = sides[i].dist(small[0]);
        int min_idx = 0;
        for (int j = 1; j < n; ++j) {
            ld cur_dist = sides[i].dist(small[j]);
            if (cur_dist < min_dist) {
                cur_dist = min_dist;
                min_idx = j;
            }
        }
        closest_point[i] = min_idx;
        fill_a012(i);
    }
    fore(i, 2, m - 1) {
        add_triples(i, 0.0, 0, true);
    }

    forn(i, n) forn(j, m) {
        Change change;
        change.side = j;
        change.point = i;
        change.ang = angle(small[i+1] - small[i], big[j+1] - big[j]);
        changes.push(change);
    }
}

void solve() {
    int moscowTime = 0;

    init();

    while (!changes.empty() || !triples.empty()) {
        ld time1 = changes.empty() ? 100 : changes.top().ang;
        ld time2 = triples.empty() ? 100 : triples.top().ang;
        if (time1 < time2) { // change
            Change change = changes.top();
            changes.pop();
            closest_point[change.side] = change.point;
            modify_time[change.side] = ++moscowTime;
            fill_a012(change.side);

            add_triples(change.side, moscowTime, change.ang);

        } else { // triple
            Triple triple = triples.top();
            triples.pop();
            if (triple.timestamp < max(modify_time[triple.s1],
                    max(modify_time[triple.s2], modify_time[triple.s3]))) {
                continue;
            }
            if (check_ans(triple.s1, triple.s2, triple.ang)) {
                return;
            }
        }
    }
    printf("NO\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
