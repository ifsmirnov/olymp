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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int n;
    scanf("%d", &n);
    
    int answer = inf;
    
    if (n == 21)
        answer = 1;
    else
    {
        for (int x = 1; x <= 6; x++)
            for (int y = 1; y <= 6; y++)
            {
                int r = n - (21 - x + 21 - y);
                if (r < 0) continue;
                
                if (r % 14 == 0)
                    answer = min(answer, r / 14 + 2);
            }
    }
    
    if (answer != inf)
        printf("%d\n", answer);
    else
        printf("-1\n");

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
