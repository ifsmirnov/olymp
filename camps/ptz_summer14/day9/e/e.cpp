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
#include <cstring>
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

bool prime(int x)
{
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}

const int maxn = 200200;
const int mod = 1000000007;
int madd(int x, int y) { return (x+y)%mod; }
int mmul(int x, int y) { return (i64)x*y%mod; }


struct node {
    int l, r;
    node *L, *R;
    int s;
    int add;
    node(int l, int r) : l(l), r(r) {
        s = add = 0;
        if (l == r) L = R = NULL;
        else L = new node(l, (l+r)/2), R = new node((l+r)/2+1, r);
    }
    int get() {
        return madd(s, mmul(add, r-l+1));
    }
    void push() {
        if (add) {
            s = madd(s, mmul(add, r-l+1));
            if (L) {
                L->add = madd(L->add, add);
                R->add = madd(R->add, add);
            }
            add = 0;
        }
    }
    void norm() {
        if (L) s = madd(L->get(), R->get());
    }
    void update(int lq, int rq, int val) {
        if (lq <= l && rq >= r) add = madd(add, val);
        else if (lq > r || rq < l) ;
        else {
            L->update(lq, rq, val);
            R->update(lq, rq, val);
            norm();
        }
    }
    int get(int lq, int rq) {
        if (lq <= l && rq >= r) return get();
        else if (lq > r || rq < l) return 0;
        else {
            push();
            return madd(L->get(lq, rq), R->get(lq, rq));
        }
    }
};

int mind[maxn], a, b;
vector<int> primes;
node* tree;
int dp[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("jumping.in", "r", stdin);
    freopen("jumping.out", "w", stdout);
#endif
    scanf("%d%d", &a, &b);
    for (int i = 2; i * i <= b; ++i)
        if (prime(i)) primes.pb(i);
    for (int i = 0; i < b - a + 1; ++i)
        mind[i] = i + a;
    for (int p : primes)
    {
        int left = (a / p) * p, right = (b / p) * p;
        while (left < a) left += p;
        for (; left <= right; left += p)
            mind[left - a] = min(mind[left - a], p);
    }
    int len = b - a + 1;

    tree = new node(0, len - 1);
    dp[0] = 1;
    for (int i = 0; i < len; ++i)
    {
        // Pasha
        {
            int l = i - (a + i) / mind[i], r = i - mind[i];
            if (l <= r && r >= 0)
            {
                l = max(l, 0);
                dp[i] = (dp[i] + tree->get(l, r)) % mod;
//                 cerr << i << " " << dp[i] << endl;
            }
        }
        // Rita
        {
            int l = i + mind[i], r = i + (a + i) / mind[i];
            if (l <= r && l < len)
            {
//                 cerr << l << " " << r << " " << dp[i] << endl;
                r = min(r, len - 1);
                tree->update(l, r, dp[i]);
            }
        }
//         for (int j = 0; j < len; ++j)
//             cout << tree->get(j, j) << " ";
//         cout << endl;
//         return 0;
    }
    cout << (tree->get(len - 1, len - 1) + dp[len - 1]) % mod << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
