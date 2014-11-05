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

const long double eps = 1e-12;

struct event
{
    long double val; int bal, num;
    event() { val = 0.0; bal = 0; num = 0; }
    event(const long double& pval, const int& pbal, const int& pnum)
    { val = pval; bal = pbal; num = pnum; }
};

bool operator<(const event& a, const event& b)
{
    if (a.val + eps < b.val) return false;
    if (b.val + eps < a.val) return true;
    return (a.bal != b.bal ? a.bal > b.bal : a.num < b.num);
}

int n, s, bal = 0;
long double vn, vx;
vector<event> ev;
bool used[20020];

void create(int k)
{
    int x, r, g, d;
    cin >> x >> r >> g >> d;
    if (0 < d && d <= g)
        ev.push_back(event(40000.0, 1, k));
    d -= g;
    while (true)
    {
        if (d > 2000) break;
        if (d > 0) ev.push_back(event((long double)x / (long double)d, 1, k));
        if (d + g > 2000) break;
        if (d + g > 0) ev.push_back(event((long double)x / (long double)(d + g), -1, k));
        d += r + g; 
    }
}

void modify(int k)
{
    if (used[k]) bal--;
    else bal++;
    used[k] ^= true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> s >> vn >> vx;
    for (int i = 0; i < n; i++)
        create(i);
    ev.push_back(event(vn, 0, 0));
    ev.push_back(event(vx, 2, 0));
    sort(ev.begin(), ev.end());
    bal = 0; bool active = false;
    int bbal = -1, bpos = -1; 
    for (int i = 0; i < (int)ev.size(); i++)
    {
        if (ev[i].bal == 2)
        {
            active = true;
            if (bal > bbal)
                bbal = bal, bpos = i;

        }
        else if (ev[i].bal == 1)
        {
            modify(ev[i].num);
            if (active && bal > bbal)
                bbal = bal, bpos = i;
        }
        else if (ev[i].bal == 0)
        {
            active = false;
        }
        else if (ev[i].bal == -1)
        {
            modify(ev[i].num);
        }
    }
    fill(used, used + n, false);
    bal = 0;
    for (int i = 0; i <= bpos; i++)
        if (ev[i].bal == 1) modify(ev[i].num);
        else if (ev[i].bal == -1) modify(ev[i].num);
    cout.precision(12); cout << fixed;
    cout << ev[bpos].val << endl;
    cout << n - bal << endl;
    for (int i = 0; i < n; i++)
        if (!used[i]) cout << i + 1 << ' ';
    cout << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
