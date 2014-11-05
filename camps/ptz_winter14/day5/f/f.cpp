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

typedef vector< vector<i64> > matrix;

int mod;

inline i64 power(i64 x, int p)
{
    i64 ans = 1, cur = x;
    for (; p; p >>= 1, cur = cur * cur % mod)
        if (p & 1) ans = ans * cur % mod;
    return ans;
}

inline i64 inv(i64 x)
{
    assert(x != 0);
    return power(x, mod - 2);
}

int gaussrow(int it, matrix &a)
{
    int cur = -1, sgn = 1;
    int n = a.size(), m = a[0].size();
    fore(j, it, n - 1)
        if (a[j][it] != 0)
        {
            cur = j;
            break;
        }
    if (cur == -1)
        return sgn = 0;
        
    if (cur != it)
    {
        sgn *= -1;
        forn(i, m) swap(a[cur][i], a[it][i]);
    }
    i64 k = inv(a[it][it]);
    forn(i, m) a[it][i] = (a[it][i] * k) % mod;
    forn(i, n)
    {
        if (i == it) continue;
        k = a[i][it];
        forn(j, m)
        {
            a[i][j] -= (a[it][j] * k) % mod;
            if (a[i][j] < 0) a[i][j] += mod;
        }
    }
    return sgn;
}

int gauss(matrix &a)
{
    int n = a.size(), m = a[0].size(), sgn = 1;
    forn(it, n) sgn *= gaussrow(it, a);
    return sgn;
}

i64 det(matrix &a)
{
    int n = a.size();
    int ans = gauss(a);
    if (ans < 0) ans += mod;
    forn(i, n) ans = (a[i][i] * ans) % mod;
    return ans;
}

const int maxn = 110, maxk = 5, iters = 100;

struct token
{
    i64 a;
    bool isVar;
    
    token(): a(0), isVar(true) {}
    token(i64 na): a(na), isVar(false) {}
};

int n, k;
token data[maxn][maxn];
i64 poly[1 << maxk], need;

i64 apply(int msk)
{
    int cnt = 0;
    matrix m(n, vector<i64>(n));
    forn(i, n)
        forn(j, n)
        {
            if (!data[i][j].isVar) m[i][j] = data[i][j].a;
            else
            {
                m[i][j] = (msk >> cnt) & 1;
                ++cnt;
            }
        }
    return det(m);
}

void countPoly()
{
    matrix m(1 << k, vector<i64>((1 << k) + 1));
    forn(msk, 1 << k)        
    {
        forn(m1, 1 << k)
            if ((m1 & msk) == m1)
                m[msk][m1] = 1;
        m[msk][1 << k] = apply(msk);
    }
    gauss(m);
    forn(msk, 1 << k)
        poly[msk] = m[msk][1 << k];
}

inline i64 toInt(const string &s)
{
    i64 val = 0;
    forn(i, s.length())
        val = val * 10 + s[i] - '0';
    return val;
}

token readToken()
{
    string str;
    cin >> str;
    if (str != "*") return token(toInt(str));
    else 
    {
        ++k;
        return token();
    }
}

void read()
{
    cin >> n >> mod >> need;
    forn(i, n) forn(j, n)
        data[i][j] = readToken();
}

void printAns(const vector<i64> &ans)
{
    cout << "Yes" << endl;
    int cnt = 0;
    for (int i = 0; i < n; ++i, cout << endl)
        forn(j, n)
            cout << (data[i][j].isVar ? ans[cnt++] : data[i][j].a) << " ";
    exit(0);
}

i64 getvalue(const vector<i64> &ans)
{
    i64 val = 0;
    forn(msk, 1 << k)
    {
        i64 cur = poly[msk];
        forn(j, k) 
            if (((msk >> j) & 1))
                cur = cur * ans[j] % mod;
        val = (val + cur) % mod;
    }
    return val;
}

vector<i64> cans;

void rec(int n)
{
    if (n == k)
    {
        if (getvalue(cans) == 0)   
            printAns(cans);
        return;
    }
    cans.pb(0);
    for (cans.back() = 0; cans.back() < mod; ++cans.back())
        rec(n + 1);
    cans.pop_back();
}

vector<i64> makePoly(const vector<i64> &coeff)
{
    vector<i64> v(k + 1);
    forn(msk, 1 << k)
    {
        int d = __builtin_popcount(msk);
        i64 cur = poly[msk];
        forn(j, k) 
            if (((msk >> j) & 1))
                cur = cur * coeff[j] % mod;
        v[d] = (v[d] + cur) % mod;
    }
    reverse(v.begin(), v.end());
    return v;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    
    read();
    countPoly();
    poly[0] = poly[0] - need;
    if (poly[0] < 0) poly[0] += mod;
    
    if (mod < 3)
    {
        rec(0);
        printf("No\n");
        return 0;
    }
    
    int it = 0;
    for (int j = 0; j < k; ++j)
    {
        matrix cur;
        vector<i64> coeff(k);
        int winr = -1;
        while (it < iters)
        {
            forn(i, k) coeff[i] = rand() % (mod - 1) + 1;
            coeff[j] = 1;
            
            cur.pb(makePoly(coeff));
            gauss(cur);
            //if ( == 0) cur.pop_back();
            
            forn(i, cur.size())
            {
                bool ok = true;
                forn(j, k)
                    ok &= (cur[i][j] == 0) ^ (j == 1);
                if (ok) 
                {
                    winr = i;
                    goto win;
                }
            }
        }
        //if ((int) cur.size() < k) continue;
        win:;
        i64 x = -cur[winr][k] * inv(cur[winr][1]) % mod;
        if (x < 0) x += mod;
        vector<i64> ans;
        forn(i, k) ans.pb(coeff[i] * x % mod);
        printAns(ans);
    }
    printf("No\n");
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
