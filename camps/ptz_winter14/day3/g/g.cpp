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
const int inf = 1e9+100500;
const int maxn = 1000500;
const int alph = 26;

int dp[maxn][alph], n;
char a[maxn][2];

inline int getv(char c)
{
    return c - 'A';
}

void printAns(int len, int c)
{
    if (len == 0) return;
    printAns(len - 1, dp[len][c]);
    printf("%c", 'A' + c);
}

void solve()
{
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i)
        scanf("%c %c\n", &a[i][0], &a[i][1]);
    
    for (int f = 0; f < 2; ++f)
    {
        for (int i = 0; i <= n; ++i) 
            for (int j = 0; j < alph; ++j)
                dp[i][j] = -1;
        dp[1][getv(a[0][f])] = 0;
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < alph; ++j)
            {
                if (dp[i][j] == -1) continue;
                for (int k = 0; k < 2; ++k)
                    if (getv(a[i][k]) != j)
                        dp[i + 1][getv(a[i][k])] = j;
            }
        for (int i = 0; i < alph; ++i)
            if (dp[n][i] != -1 && i != getv(a[0][f]))
            {
                printAns(n, i);
                printf("\n");
                return;
            }
    }
    printf("-\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    int t;
    scanf("%d\n", &t);
    for (int i = 0; i < t; ++i) solve();
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
