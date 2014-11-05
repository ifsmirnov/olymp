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

void solve()
{
    

    int n, d;
    scanf("%d %d", &n, &d);
    
    vi x(n), w(n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &x[i], &w[i]);

    int maxFirst = -1;
    int prefMax = -inf;
    int prefMaxIndex = -1;
    
    int answerFirst = -1, answerSecond = 1;
    int answer = -inf;

    for (int two = 0; two < n; two++)
    {
        while (x[two] - x[maxFirst + 1] >= d)
        {
            maxFirst++;
            if (w[maxFirst] > prefMax)
            {
                prefMax = w[maxFirst];
                prefMaxIndex = maxFirst;
            }
        }
        
        if (prefMax != -inf && w[two] + prefMax > answer)
        {
            answer = w[two] + prefMax;
            answerFirst = prefMaxIndex;
            answerSecond = two;
        }
    }
    
    if (answerFirst != -1)
        printf("%d %d\n", answerFirst + 1, answerSecond + 1);
    else
        printf("-1 -1\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    for (int i = 0; i < 2; i++)
#endif

    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
