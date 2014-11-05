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

set<int> r;

long long res[100];

int get(long long a, long long r) {
    res[0] = 1;
    res[1] = a;
    for (int i = 0; i < 2; ++i) {
        if (res[i] > r) {
            return i;
        }
    }
    for (int i = 2; ; ++i) {
        double z = (double)res[i - 1] * a - res[i - 2];
        res[i] = res[i - 1] * a - res[i - 2];
        if (z > 2 * r || res[i] > r) {
            return i;
        }
    }
}

#include <cmath>

long long solve(i64 l, i64 r) 
{
    i64 ans = 0;
    ans += r - l; 
    i64 cura = 3;
    double x = log(l);
    double y = log(r);
    vector<i64> bor;
    
    cura = 3;
    int sta = get(cura, l - 1);
    bor.pb(cura);
    for (int it = 0; cura <= r; ++it)
    {
        i64 left = cura, right = r;
        if (it < 10 && get(cura + 1, l - 1) != sta) right = left;
        else
        { 
            if (sta != 0 && sta > 6)
                right = min(right, 2 * (i64) (exp(x / sta) + 200));
            //if (stb != 0 && stb > 6)
            //    right = min(right, 2 * (i64) (exp(y / stb) + 200));
        }
        //cerr << left << " " << right << " " << sta << " " << stb << endl;
        assert(left <= right);
        while (left < right)
        {
            i64 middle = ((left + right) >> 1) + 1;
            if (get(middle, l - 1) == sta /*&& get(middle, r) == stb*/) left = middle;
            else right = middle - 1;
        }
        left = min(left, r);
        //ans += (left - cura + 1) * max(0, stb - sta - 1);
        cura = left + 1;
        bor.pb(cura);
        sta = get(cura, l - 1);
        //stb = get(cura, r);
    }
    cura = 3;
    int stb = get(cura, r);
    for (int it = 0; cura <= r; ++it)
    {
        i64 left = cura, right = r;
        if (it < 10 && get(cura + 1, r) != stb) right = left;
        else
        { 
            //if (sta != 0 && sta > 6)
            //    right = min(right, 2 * (i64) (exp(x / sta) + 200));
            if (stb != 0 && stb > 6)
                right = min(right, 2 * (i64) (exp(y / stb) + 200));
        }
        //cerr << left << " " << right << " " << sta << " " << stb << endl;
        assert(left <= right);
        while (left < right)
        {
            i64 middle = ((left + right) >> 1) + 1;
            if (/*get(middle, l - 1) == sta &&*/ get(middle, r) == stb) left = middle;
            else right = middle - 1;
        }
        left = min(left, r);
        //ans += (left - cura + 1) * max(0, stb - sta - 1);
        cura = left + 1;
        bor.pb(cura);
        stb = get(cura, r);
        //stb = get(cura, r);
    }
    sort(all(bor));
    bor.erase(unique(bor.begin(), bor.end()), bor.end());
    
    for (size_t i = 0; i + 1 < bor.size(); ++i)
    {
        sta = get(bor[i], l - 1), stb = get(bor[i], r);
        ans += (bor[i + 1] - bor[i]) * max(0, stb - sta - 1);
    }
    
    if (l == 1) return ans * 2 + 1;
    return ans * 2;
}

long long stress(i64 l, i64 r)
{
    i64 ans = 0;
    for (i64 a = l; a <= r; ++a) {
        for (i64 b = l; b <= r; ++b) {
            i64 aa = a * a - 1;
            i64 bb = b * b - 1;
            
            if (aa % b == 0 && bb % a == 0) {
                ++ans;
            }
        }
    }
    return ans;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    
    int n;
    scanf("%d", &n);
    
    n = 10000;
#ifdef HOME
    //for (int i = 1; i <= 100; ++i)
      //  for (int j = i; j <= 100; ++j)
        //    assert(solve(i, j) == stress(i, j));
#endif
    while (n--) {
        long long l, r;
       // scanf("%lld%lld", &l, &r);
        l = 1e15, r = 1e18;
        printf("%lld\n", solve(l, r));
    }
    
    return 0;
    
    
    

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}