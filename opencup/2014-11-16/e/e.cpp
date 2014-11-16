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

bool firstWins(int n, int p, int q)
{
	if (n == p)
		return true;
	
	if (n < p)
		return !firstWins(n + p, q, p);
		
	if (p <= q)
		return true;
	
	if (n % p >= q)
		return false;
	
	return (n % p + q - p) % (p - q) == 0;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	int nTests;
	scanf("%d", &nTests);
	
	for (int i = 0; i < nTests; i++)
	{
		int n, p, q;
		scanf("%d %d %d", &p, &q, &n);
		
		int g = __gcd(p, q);
		if (n % g != 0)
		{
			printf("R\n");
			continue;
		}
		
		n /= g;
		p /= g;
		q /= g;
		
		printf("%s\n", firstWins(n, p, q) ? "E" : "P");
	}

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
