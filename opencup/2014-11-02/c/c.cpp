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
#include <cstring>
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

void calcz(char* s, int* z, int n)
{
	z[0] = n;
	
	int l = 0, r = 0;
	for (int i = 1; i < z[0]; i++)
	{	
		z[i] = max(min(r - i, z[i - l]), 0);
		
		while (s[i + z[i]] == s[z[i]])
			z[i]++;
			
		if (i + z[i] > r)
		{
			l = i;
			r = i + z[i];
		}
	}
}

const int maxN = 1000500;
char s[maxN];
int z[maxN];

void solve()
{
	scanf("%s", s);
	int n = strlen(s);
	
	calcz(s, z, n);
	
	/*if (z[1] == n - 1)
	{
		printf("1\n");
		return;
	}*/
	
	//printf("%s\n", s);
	for (int k = 2; k <= n + 1; k++)
	{
		// check if k is possible
		bool fail = false;
		
		i64 kpower = k;
		
		for (int t = 0; ; t++)
		{
			if (n - kpower <= 0) break;
			
			i64 length = kpower - 1;
			
			for (int i = 1; i < k; i++)
				if (i * kpower < n && z[i * kpower] < min(n - i * kpower, length))
				{
					fail = true;
					break;
				}
			
			kpower *= k;
		}
		
		if (!fail)
		{
			printf("%d\n", k);
			break;
		}
	}
	
	//printf("done\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

	char s[] = "abacabaabacaba";
	int z[100];
	
	calcz(s, z, strlen(s));
	//for (int i = 0; i < (int)strlen(s); i++)
	//	printf("z[%d] is %d, %s\n", i, z[i], s + i);

	int nTests;
	scanf("%d", &nTests);
	
	for (int i = 0; i < nTests; i++)
		solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
