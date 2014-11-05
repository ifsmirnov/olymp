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

const int mod = 1000000007;
int add(int x, int y) { return (x+y)%mod; }
int mul(int x, int y) { return (i64)x*y%mod; }

struct node {
    int l, r;
    node *L, *R;
    int s, mm;
    node(int l, int r) : l(l), r(r) {
        s = 0;
        mm = 1;
        if (l == r) L = R = NULL;
        else L = new node(l, (l+r)/2), R = new node((l+r)/2+1, r);
    }
    void push() {
        if (mm != 1) {
            s = mul(s,mm);
            if (L) L->mm = mul(L->mm, mm), R->mm = mul(R->mm, mm);
            mm = 1;
        }
    }
    void norm() {
        assert(mm == 1);
        if (L) s = add(mul(L->s, L->mm), mul(R->s, R->mm));
    }
    void mul2(int lq, int rq) {
        if (lq <= l && rq >= r) mm = mul(mm, 2);
        else if (lq > r || rq < l) ;
        else {
            push();
            L->mul2(lq, rq);
            R->mul2(lq, rq);
            norm();
        }
    }
    int get(int lq, int rq) {
        if (lq <= l && rq >= r) return mul(mm, s);
        else if (lq > r || rq < l) return 0;
        else {
            push();
            return add(L->get(lq, rq), R->get(lq, rq));
        }
    }
    void put(int i, int x) {
        push();
        if (l == r) s = add(s, x);
        else {
            push();
            (i<=(l+r)/2 ? L : R)->put(i, x);
            norm();
        }
    }
};
void test_node() {
    node *t = new node(0, 10);
    forn(i, 11) t->put(i, i);
    cout << t->get(0, 5) << " " << t->get(0, 10) << endl;
    t->mul2(0, 5);
    cout << t->get(1,1) << " " << t->get(0, 5) << " " << t->get(0,10) << endl;
}

int pw(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) {
            res = (long long) a * res % mod;
        }
        a = (long long) a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    int n;
    scanf("%d", &n);
    
    pii a[n];
    int yy[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].fi, &a[i].se);
        yy[i] = a[i].se;
    }
    sort(a, a + n);
    sort(yy, yy + n);
    
    int sz = unique(yy, yy + n) - yy;
    
    node t1(0, sz - 1);
    node t2(0, sz - 1);
    
    long long ans = 0;
    
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(yy, yy + sz, a[i].se) - yy;
        int cnt1 = (t1.get(0, pos - 1) + 1) % mod;
        int cnt2 = t2.get(pos, sz - 1);
        ans += (long long)cnt1 * pw(2, a[i].fi) % mod * pw(3, a[i].se) % mod;
        ans += (long long)cnt2 * pw(2, a[i].fi) % mod;
        //cout << cnt1 << " " << cnt2 << " " << ans << endl;
        t1.mul2(pos, sz - 1);
        t2.mul2(pos, sz - 1);
        t1.put(pos, cnt1);
        t2.put(pos, (long long)cnt1 * pw(3, a[i].se) % mod);
    }
    
    ans %= mod;
    cout << ans << endl;
    
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
