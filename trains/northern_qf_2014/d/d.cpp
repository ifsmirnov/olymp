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

int n, qt[100];
ll ans[100];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	for (int i = 1; i <= 10000000; i++)
	{
		int sum = 0, val = i;
		while (val > 0)
			sum += val % 10, val /= 10;
		if (qt[sum] < n) ans[sum] += (ll)i, qt[sum]++;
	}
	ll best = 1000000000000000000ll;
	for (int i = 0; i < 100; i++)
		if (qt[i] == n && ans[i] < best) best = ans[i];
	printf("%lld\n", best);
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
