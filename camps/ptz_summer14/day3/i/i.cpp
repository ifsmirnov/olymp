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
typedef long long ll;
typedef unsigned long long u64;
const int inf = 1e9+100500;

const int mod = 1000000007;
const int mod2 = 2 * mod;

long long n, m, k;

void solve()
{
    cin >> n >> m >> k;
//     cerr << "k = " << k << endl;
    if (n <= m)
    {
        ll r = k;
        ll ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i & 1)
            {
                ll s = 0;
                if (r <= m) s = 1 + (m - r) / k;
                else s = 0;

//                 cout << "down " << s << endl;
                if (s > 0)
                {
                    ll start = (2 * (m - r)) % mod2;
                    ll diff = (-2 * k) %  mod2;
                    if (diff < 0) diff += 2 * mod;


                    ll add = (((2 * start + (s - 1) % mod2 * diff) % mod2 * s) % mod2) / 2;
                    if ((m - r) % k == 0) add += 2;
                    ans += add;
                    if (i == n - 1 && (m - r) % k == 0) ans -= 2;
//                     cerr << s << " " << start << " " << diff << " " << add << " " << r << endl;
                    r = k - (m - r) % k;
//                     cout << "nr = " << r << endl;
                }
                else r -= m;
            }
            else
            {
                ll s = 0;
                if (r <= m) s = 1 + (m - r) / k;
                else s = 0;

//                 cout << "up " << s << endl;
                if (s > 0)
                {
                    ll start = (2 * r) % mod2;
                    ll diff = (2 * k) % mod2;

                    ll add = (((2 * start + (s - 1) % mod2 * diff) % mod2 * s) % mod2) / 2;
                    ans += add;
                    if (i == n - 1 && (m - r) % k == 0) ans -= 2 * m;
//                     cerr << s << " " << start << " " << diff << " " << add << " " << r << endl;
                    r = k - (m - r) % k;
                }
                else r -= m;
            }
        }
        ans = ans + n * m - 1;
        cout << ans % mod << endl;
    }
    else
    {
        ll ans = 0, x = 0, y = 0;
        for (int i = 0; i < 2 * m; ++i)
        {
            y += k;
            x += y / m;
            y %= m;
            if (x & 1)
                ans += (y == m - 1 ? 2 : (m - y) * 2);
            else
                ans += 2 * y + 2;
        }
        ans %= mod;
        cout << x << " " << y << endl;
        long long count = n / (2 * k) % mod;
        ans *= count;
        x *= count;
        cout << ans << endl;
        while (x < n)
        {
            cout << ans << endl;
            y += k;
            x += y / m;
            y %= m;
            if (x >= n) break;
            if (x & 1)
                ans += (y == m - 1 ? 2 : (m - y) * 2);
            else
                ans += 2 * y + 2;
        }
        ans += n * m - 1;
        cout << ans % mod << endl;
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
        solve();
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
