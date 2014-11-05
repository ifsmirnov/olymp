#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstring>
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
typedef long long ll;
typedef unsigned long long u64;
const int inf = 1e9+100500;

const int mod1 = 2000000011;
const int mod2 = 32749;
const int mul1 = 849241;
const int mul2 = 483;
const int maxn = 5000000;
const ll mod12 = (ll) mod1 * mod1;
const int mod22 = (int) mod2 * mod2;

char data[maxn + 1];
int n;
int len[maxn];
int pref1[maxn + 1];
short pref2[maxn + 1];
int power1[maxn + 1];
short power2[maxn + 1];

// 40 + 20 + 20 + 5 MB

int geth1(int l, int r)
{
    ll ans = ((ll) pref1[r + 1] - (ll) pref1[l] * power1[r - l + 1]);
    if (ans < 0) ans += mod12;
    if (ans >= mod1) ans %= mod1;
    return ans;
}

int geth2(int l, int r)
{
    int ans = ((int) pref2[r + 1] - (int) pref2[l] * power2[r - l + 1]);
    if (ans < 0) ans += mod22;
    if (ans >= mod2) ans %= mod2;
    return ans;
}


struct PartOne
{
    int suff1[maxn + 1];
    short suff2[maxn + 1];
    int q[maxn];
    int qh, qt, qadd;
    // + 50 MB


    void precalc()
    {
        qh = qt = qadd = 0;
        pref1[0] = 0;
        power1[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            pref1[i] = ((ll) pref1[i - 1] * mul1 + data[i - 1]) % mod1;
            power1[i] = ((ll) power1[i - 1] * mul1) % mod1;
        }

        suff1[n] = 0;
        for (int i = n - 1; i >= 0; --i)
            suff1[i] = ((ll) suff1[i + 1] * mul1 + data[i]) % mod1;

        pref2[0] = 0;
        power2[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            pref2[i] = ((ll) pref2[i - 1] * mul2 + data[i - 1]) % mod2;
            power2[i] = ((ll) power2[i - 1] * mul2) % mod2;
        }

        suff2[n] = 0;
        for (int i = n - 1; i >= 0; --i)
            suff2[i] = ((ll) suff2[i + 1] * mul2 + data[i]) % mod2;
    }

    int getrh1(int l, int r)
    {
        ll ans = ((ll) suff1[l] - (ll) suff1[r + 1] * power1[r - l + 1]);
        if (ans < 0) ans += mod12;
        if (ans >= mod1) ans %= mod1;
        return ans;
    }

    int getrh2(int l, int r)
    {
        int ans = ((ll) suff2[l] - (ll) suff2[r + 1] * power2[r - l + 1]);
        if (ans < 0) ans += mod22;
        if (ans >= mod2) ans %= mod2;
        return ans;
    }

    bool ispal(int l, int r)
    {
        if (l < 0) return false;
    //     cerr << "ispal " << l << " " << r << endl;
    //     cerr << geth1(l, r) << " " << getrh1(l, r) << endl;
        if (geth1(l, r) != getrh1(l, r)) return false;
    //     cerr << "true1" << endl;
    //     cerr << geth2(l, r) << " " << getrh2(l, r) << endl;
    //     cerr << suff2[0] << " " << suff2[1] << endl;
        if (geth2(l, r) != getrh2(l, r)) return false;
    //     cerr << "true2" << endl;
        return true;
    }

    int append(int i)
    {
        qadd += 2;
        if (i > 0 && data[i - 1] == data[i])
        {
            q[qt++] = 2 - qadd;
            if (qt == n) qt = 0;
        }
        q[qt++] = 1 - qadd;
        if (qt == n) qt = 0;
        while (!ispal(i - (q[qh] + qadd) + 1, i))
        {
            if (++qh == n) qh = 0;
        }
//         if (qh == qt) assert(false);
        return q[qh] + qadd;
    }
};

// typedef struct node* pnode;

struct node
{
    int h1;
    short h2;
//     pnode nxt;

    node(): h1(-1), h2(-1) {}
    node (int nh1, int nh2): h1(nh1), h2(nh2) {}
};

const int hsize = 1 << 23, hmsk = hsize - 1;

struct PartTwo
{

    node table[hsize];
    // + 16 MB + 40 MB

    void init()
    {
//         memset(table, 0, sizeof(table));
    }

    bool add(int l, int r)
    {
        int h1 = geth1(l, r);
        int h2 = geth2(l, r);
//         cerr << l << " " << r << ": " << h1 << " " << h2 << endl;
        int pos = ((h1 << 1) + (h2 >> 1)) & hmsk;
//         for (pnode p = table[pos]; p; p = p->nxt)
//             if (p->h1 == h1 && p->h2 == h2)
//                 return false;
//         table[pos] = new node(h1, h2, table[pos]);
//         cerr << h1 << " " << h2 << " " << pos << endl;
        for (; table[pos].h1 != -1;)
        {
            if (table[pos].h1 == h1 && table[pos].h2 == h2)
                return false;
            pos = (pos + 17) & hmsk;
        }
        table[pos] = node(h1, h2);
        return true;
    }
};

void gen()
{
    freopen("input.txt", "w", stdout);
    for (int i = 0; i < 5000000; ++i)
        putchar('a');
    fclose(stdin);
    exit(0);
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", data), n = strlen(data);
    n = 5000000;
    for (int i = 0; i < n; ++i) data[i] = 'a';
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    {

        PartOne *p = new PartOne();
        p->precalc();
        for (int i = 0; i < n; ++i)
        {
            len[i] = p->append(i);
//             cerr << len[i] << endl;
        }
        delete p;
    }
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    {
        PartTwo *p = new PartTwo();
        p->init();
        for (int i = 0; i < n; ++i)
        {
//             p.add(i - len[i] + 1, i);
            if (p->add(i - len[i] + 1, i))
                putchar('1');
            else
                putchar('0');
        }
        putchar('\n');
        delete p;
    }
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
