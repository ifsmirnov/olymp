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

typedef long long ll;
const long double PI = acosl((long double)-1.0);

ll x[3], y[3], r[2];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	for (int i = 0; i < 3; i++)
		cin >> x[i] >> y[i];
	for (int i = 0; i < 2; i++)
	{
		x[i] -= x[2]; y[i] -= y[2];
		r[i] = x[i] * x[i] + y[i] * y[i];
	}
	ll scal = x[0] * x[1] + y[0] * y[1];
	long double r0 = sqrtl((long double)r[0]), r1 = sqrtl((long double)r[1]);
	long double angle = acosl((long double)scal / (r0 * r1));
	long double ans;
	if (r[0] == r[1])
		ans = angle * r0;
	else
	{
		long double tau = angle / logl(r1 / r0);
		ans = sqrtl(tau * tau + 1.0) * fabsl(r1 - r0);
	}
	cout.precision(12);
	cout << fixed << ans << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
