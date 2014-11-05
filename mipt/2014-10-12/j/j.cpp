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
#include <cstring>
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

struct state
{
    int link, len, go[26];
    bool term;
    state() { link = -1, len = 0; term = false; fill(go, go + 26, -1); }
    void nullify() { link = -1, len = 0; term = false; fill(go, go + 26, -1); }
    void copy(const state &oth)
    {
        term = oth.term; link = oth.link, len = oth.len;
        for (int i = 0; i < 26; i++)
            go[i] = oth.go[i];
    }
};

state aut[100100], given[100100];
int sz, last, pp[100100];
char s[100100];
bool used[100100];

void init(int n)
{
    sz = 1; last = 0;
    aut[0].nullify();
    for (int i = 0; i < n; i++)
        given[i].nullify();
}

void extend(int c)
{
    int nlast = sz++;
    aut[nlast].copy(aut[last]);
    aut[nlast].len++;
    int p;
    for (p = last; p != -1 && aut[p].go[c] == -1; p = aut[p].link)
        aut[p].go[c] = nlast;
    if (p == -1)
        aut[nlast].link = 0;
    else
    {
        int q = aut[p].go[c];
        if (aut[p].len + 1 == aut[q].len)
            aut[nlast].link = q;
        else
        {
            int clone = sz++;
            aut[clone].copy(aut[q]);
            aut[clone].len = aut[p].len + 1;
            for (; p != -1 && aut[p].go[c] == q; p = aut[p].link)
                aut[p].go[c] = clone;
            aut[q].link = aut[nlast].link = clone;
        }
    }
    last = nlast;
}

void fullify(state* aut, int& sz)
{
    bool full = true;
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < 26; j++)
            full &= (aut[i].go[j] != -1);
    if (!full)
    {
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < 26; j++)
                if (aut[i].go[j] == -1) aut[i].go[j] = sz;
        aut[sz].nullify();
        fill(aut[sz].go, aut[sz].go + 26, sz);
        sz++;
    }
}

bool dfs(int px, int py)
{
    pp[py] = px;
    for (int i = 0; i < 26; i++)
    {
        int nx = aut[px].go[i], ny = given[py].go[i];
        if (pp[ny] == -1)
        {
            bool f = dfs(nx, ny);
            if (!f) return false;
        }
        else if (pp[ny] != nx) return false;
    }
    return true;
}

void udfs(int x)
{
    used[x] = true;
    for (int i = 0; i < 26; i++)
        if (!used[given[x].go[i]])
            udfs(given[x].go[i]);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("suffix.in", "r", stdin);
    freopen("suffix.out", "w", stdout);
#endif

    int test = 0;
    while (true)
    {
        int n, m, t;
        scanf("%d%d%d", &n, &m, &t);
        if (n == 0 && m == 0 && t == 0) break;
        init(n); test++;
        for (int i = 0; i < t; i++)
        {
            int x; scanf("%d", &x);
            given[x - 1].term = true;
        }
        for (int i = 0; i < m; i++)
        {
            int x, y; char c;
            scanf("%d%d %c\n", &x, &y, &c);
            given[x - 1].go[(int)(c - 'a')] = y - 1;
        }
        fullify(given, n);
        fill(used, used + n, false);
        udfs(0);
        
        scanf("%s\n", s); int len = strlen(s);
        for (int i = 0; i < len; i++)
            extend((int)(s[i] - 'a'));
        for (int i = last; i != -1; i = aut[i].link)
            aut[i].term = true;
        fullify(aut, sz);
        
        fill(pp, pp + n, -1);
        bool good = true;
        if (dfs(0, 0))
        {
            for (int i = 0; i < n; i++)
            {
                if (!used[i]) continue;
                if (given[i].term ^ aut[pp[i]].term)
                {
                    good = false;
                    break;
                }
            }
           // for (int i = 0; i < n; i++)
           //     cerr << "asd " << pp[i] << given[i].term << ' ' << aut[pp[i]].term << endl;
            fill(used, used + sz, false);
            for (int i = 0; i < n; i++)
                if (pp[i] != -1)
                    used[pp[i]] = true;
            int cnt = (aut[sz - 1].term ? 0 : !used[sz - 1]); 
            for (int i = 0; i < sz; i++)
                cnt += used[i];
            if (cnt != sz)
                good = false;
        }
        else good = false;
        if (good)
            printf("Automaton %d is a machinegun.\n", test);
        else
            printf("Automaton %d is not a machinegun.\n", test);
            //cout << "Automaton " << test << " is not a machinegun." << endl;
    }
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
