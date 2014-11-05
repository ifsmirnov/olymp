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
const int maxn = 1000500;

const i64 p1 = 424243, m1 = 1000000007;
const i64 p2 = 123457, m2 = 1000000009;

i64 pow1[maxn + 1], pow2[maxn + 1];
char data[2][maxn + 1];
int n;

struct hash_t
{
    i64 h1;
    
    hash_t(): h1(0) {}
    hash_t(i64 nh1): h1(nh1 % m1)
    {
        if (h1 < 0) h1 += m1;
    }
    
    hash_t (char c)
    {
        h1 = c;
    }
    
    hash_t shift(int x)
    {
        return hash_t(h1 * pow1[x]);
    }
    
    hash_t operator - (const hash_t &h) const
    {
        return hash_t(h1 - h.h1);
    }
    
    bool operator == (const hash_t &h) const
    {
        return h1 == h.h1;
    }
    
    hash_t operator + (const char c) const
    {
        return hash_t(h1 * p1 + c);
    }
};

hash_t pref[maxn + 1], suff[maxn + 1];

inline hash_t gethash(int l, int r)
{
    if (l == 0) return pref[r];
    return pref[r] - pref[l - 1].shift(r - l + 1);
}

inline hash_t getrev(int l, int r)
{
    if (r == n - 1) return suff[l];
    return suff[l] - suff[r + 1].shift(r - l + 1);
}

int solveodd()
{
    int ans = 0;
    for (int i = 0; i < n; ++i)
        while (i - ans >= 0 && i + ans < n && 
               gethash(i - ans, i + ans) == getrev(i - ans, i + ans)) ++ans;
    return 2 * ans - 1;
}

int solveeven()
{
    int ans = 0;
    for (int i = 0; i < n; ++i)
        while (i - ans >= 0 && i + ans + 1 < n &&
               gethash(i - ans, i + ans + 1) == getrev(i - ans, i + ans + 1)) ++ans;
    return 2 * ans;
}

void solve()
{
    scanf("%d\n", &n);
    for (int it = 0; it < 2; ++it)
        scanf("%s\n", data[it]);
        
    pref[0] = hash_t(data[0][0]);
    for (int i = 1; i < n; ++i)
        pref[i] = pref[i - 1] + data[0][i];
    
    suff[n - 1] = hash_t(data[1][n - 1]);
    for (int i = n - 2; i >= 0; --i)
        suff[i] = suff[i + 1] + data[1][i];
        
    printf("%d\n", max(solveodd(), solveeven()));
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= maxn; ++i) 
        pow1[i] = (pow1[i - 1] * p1) % m1;

    int t;
    scanf("%d\n", &t);
    for (int i = 0; i < t; ++i) solve();
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
