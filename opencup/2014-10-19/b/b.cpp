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

vector<int> a, b;

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
	freopen("ccf.in", "r", stdin);
	freopen("ccf.out", "w", stdout);
#endif

	int n; cin >> n;
	for (int i = 0; i <= n; i++)
	{
		int x; cin >> x; a.push_back(x);
	}
	cin >> n;
	for (int i = 0; i <= n; i++)
	{
		int x; cin >> x; b.push_back(x);
	}
	a.push_back(1000000001), b.push_back(1000000001);
	int df = -1;
	for (int i = 0; i < (int)a.size(); i++)
		if (a[i] != b[i]) { df = i; break; }
	if (df == -1) cout << '=' << endl;
	else
	{
		df = (df % 2 == 0 ? 1 : -1) * (a[df] < b[df] ? 1 : -1);
		if (df == 1) cout << '<' << endl;
		else cout << '>' << endl;
	}

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
